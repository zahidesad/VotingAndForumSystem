#include <stdio.h>
#include <stdlib.h>
#include "../src/database.c"
#include "../src/person.c"
#include "../src/topic.c"
#include "../src/vote.c"
#include "../Colors/color.c"

int Display();
void defaultInformation();

int main()
{
    // defaultInformation(); // Run it once to only write the default data to the txt file.
    readAllData();
    setAllIdNumbers();
    Display();
    return 0;
}

int Display()
{
    Person *account = (Person *)malloc(sizeof(Person));
    ;
    int option;
    int isLoggedIn = 0;
    while (true)
    {
        if (isLoggedIn && account->isAdmin)
        {
            Color_Green();
            printf("\n--------- Welcome Admin ---------\n", account->name);
            Color_Reset();

            int choice;
            char topicName[MAX];
            int optionLength;
            char *topicOptions[MAX];

            char newTopicName[MAX];
            int newOptionLength;
            char *newTopicOptions[MAX];
            bool flag;
            int userIDForDelete = 0;
            bool flagForUser = 0;

            printf("\n1- Create Topic\n");
            printf("2- Show All Topics\n");
            printf("3- Update Topic\n");
            printf("4- Delete Topic\n");
            printf("5- View your vote rates\n");
            printf("6- Open/close topics for voting\n");
            printf("7- Delete User Account\n");
            printf("8- Logout\n");

            Color_White();
            printf("\nSelect an option : ");
            Color_Reset();
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Please enter your topic name : ");
                gets(topicName);
                gets(topicName);
                printf("Please enter your number of options : ");
                scanf("%d", &optionLength);

                for (int i = 0; i < optionLength; i++)
                {
                    printf("Please enter your %d. option: ", i + 1);
                    topicOptions[i] = (char *)malloc(MAX * sizeof(char)); // Allocate memory to each array element
                    if (topicOptions[i] == NULL)
                    {
                        printf("Memory allocation failed. Exiting...\n");
                        return 1;
                    }
                    fflush(stdin);
                    fgets(topicOptions[i], MAX, stdin);

                    topicOptions[i][strcspn(topicOptions[i], "\n")] = '\0'; // Remove newline character
                }

                for (int i = 0; i < 4; i++)
                {
                    printf("%d- %s\n", (i + 1), categories_names[i]);
                }
                Color_White();
                printf("\nPlease choose a category for your topic : ");
                Color_Reset();
                scanf("%d", &choice);
                Categories category = (Categories)(choice - 1);

                Topic topic = createTopic(topicID, topicName, topicOptions, optionLength, category, 1);
                Color_Green();
                printf("\nTopic created successfully...\n");
                Color_Reset();
                topicID++;
                break;
            case 2:
                showAllTopics();
                break;
            case 3:
                for (int i = 0; i < topicCount; i++)
                {
                    printf("\n%d- Name of Topic : %s / ID of Topic : %d\n", (i + 1), topics[i].topicName, topics[i].id);
                }
                Color_White();
                printf("\nPlease write the ID of the topic you want to update :");
                scanf("%d", &option);
                Color_Reset();
                printf("\nPlease enter your new topic name : ");
                fflush(stdin);
                gets(newTopicName);
                printf("Please enter your new number of options : ");
                scanf("%d", &newOptionLength);

                for (int i = 0; i < newOptionLength; i++)
                {
                    printf("Please enter your %d. option: ", i + 1);
                    newTopicOptions[i] = (char *)malloc(MAX * sizeof(char)); // Allocate memory to each array element
                    if (newTopicOptions[i] == NULL)
                    {
                        printf("Memory allocation failed. Exiting...\n");
                        return 1;
                    }
                    fflush(stdin);
                    gets(newTopicOptions[i]);
                    newTopicOptions[i][strcspn(newTopicOptions[i], "\n")] = '\0'; // Remove newline character
                }

                for (int i = 0; i < 4; i++)
                {
                    printf("%d- %s\n", (i + 1), categories_names[i]);
                }
                Color_White();
                printf("\nPlease choose a category for your topic : ");
                Color_Reset();
                scanf("%d", &choice);
                Categories newCategory = (Categories)(choice - 1);

                updateTopicInformation(option, newTopicName, newTopicOptions, newOptionLength, newCategory, 1);
                Color_Green();
                printf("\nTopic has been updated successfully\n");
                Color_Reset();
                break;

            case 4:
                for (int i = 0; i < topicCount; i++)
                {
                    printf("\n%d- Name of Topic : %s / ID of Topic : %d\n", (i + 1), topics[i].topicName, topics[i].id);
                }
                Color_White();
                printf("\nPlease write the ID of the topic you want to delete :");

                scanf("%d", &option);
                Color_Reset();
            comeback:
                flag = 0;
                for (int i = 0; i < voteCount; i++)
                {
                    if (votes[i].topic.id == option)
                    {
                        flag = 1;
                        deleteVote(votes[i].id);
                    }
                }
                if (flag == 1)
                {
                    goto comeback;
                }
                deleteTopic(option);
                Color_Green();
                printf("\nTopic has been deleted successfully\n");
                Color_Reset();

                break;

            case 5:
                for (int i = 0; i < topicCount; i++)
                {
                    printf("\n%d- Name of Topic : %s / ID of Topic : %d\n", (i + 1), topics[i].topicName, topics[i].id);
                }
                int id = 0;
                Color_White();
                printf("\nPlease enter the ID of the topic for which you want to view the vote rate : ");
                scanf("%d", &id);
                Color_Reset();
                calculateVoteRate(id);
                break;
            case 6:
                for (int i = 0; i < topicCount; i++)
                {
                    char *statusName = "Close";
                    if (topics[i].isOpen == 1)
                    {
                        statusName = "Open";
                    }
                    printf("\n%d- Name of Topic : %s / ID of Topic : %d / Open Status Of Topic : %s\n", (i + 1), topics[i].topicName, topics[i].id, statusName);
                }
                int idOpenStatus = 0;
                Color_White();
                printf("\nPlease enter the ID of the topic for which you want to change open status : ");
                Color_Reset();
                scanf("%d", &idOpenStatus);
                changeOpenStatus(idOpenStatus);
                Color_Green();
                printf("\nTopic open status has been changed successfully\n");
                Color_Reset();
                break;
            case 7:
                for (int i = 0; i < userCount; i++)
                {
                    if (users[i].isAdmin == 0)
                    {
                        printf("\n%d- Username : %s / ID of user : %d\n", (i), users[i].username, users[i].id);
                    }
                }
                Color_White();
                printf("\nPlease write the ID of the user you want to delete :");
                scanf("%d", &userIDForDelete);
                Color_Reset();
            returnBack:
                flagForUser = 0;
                for (int i = 0; i < voteCount; i++)
                {
                    if (votes[i].voter.id == userIDForDelete)
                    {
                        flagForUser = 1;
                        deleteVote(votes[i].id);
                    }
                }
                if (flagForUser == 1)
                {
                    goto returnBack;
                }
                deletePerson(userIDForDelete);
                break;
            case 8:
                isLoggedIn = 0;
                break;
            default:
                Color_Red();
                printf("\nInvalid option. Please select [1-8]\n");
                Color_Reset();
                while (getchar() != '\n')
                    ; // To prevent it from going into an infinite loop when I enter data of String type.
                break;
            }
        }
        else if (isLoggedIn && !account->isAdmin)
        {
            int switchOption = 0;
            int categoryOption = 0;
            int topicID = 0;
            int countCategory1 = 0; // If there are no votes in this category, use them to determine
            int countCategory2 = 0; // If there are no votes in this category, use them to determine
            int countCategory3 = 0; // If there are no votes in this category, use them to determine
            int countCategory4 = 0; // If there are no votes in this category, use them to determine
            int optionIndex = 0;
            bool flag = 0;
            char newName[30];
            char newUsername[30];
            char newPassword[30];
            char newMail[50];

            Color_Green();
            printf("\n--------- Welcome %s ---------\n", account->name);
            Color_Reset();

            printf("\n1- Show user information\n");
            printf("2- Update user information\n");
            printf("3- Vote for a topic\n");
            printf("4- View vote rates\n");
            printf("5- Logout\n");

            Color_White();
            fflush(stdin);
            printf("\nSelect an option : ");
            Color_Reset();
            scanf("%d", &switchOption);

            switch (switchOption)
            {
            case 1:
                printf("\nName : %s\n", account->name);
                printf("Username : %s\n", account->username);
                printf("Password : %s\n", account->password);
                printf("Mail : %s\n", account->mail);
                break;
            case 2:
                Color_White();
                printf("\nPlease enter your new name : ");
                Color_Reset();
                fflush(stdin);
                gets(newName);

                Color_White();
                printf("Please enter your new username : ");
                Color_Reset();
                fflush(stdin);
                gets(newUsername);

                Color_White();
                printf("Please enter your new password : ");
                Color_Reset();
                fflush(stdin);
                gets(newPassword);

                Color_White();
                printf("Please enter your new mail : ");
                Color_Reset();
                fflush(stdin);
                gets(newMail);
                strncpy(account->name, newName, sizeof(account->name) - 1);
                account->name[sizeof(account->name) - 1] = '\0';
                strncpy(account->username, newUsername, sizeof(account->username) - 1);
                account->username[sizeof(account->username) - 1] = '\0';
                strncpy(account->password, newPassword, sizeof(account->password) - 1);
                account->password[sizeof(account->password) - 1] = '\0';
                strncpy(account->mail, newMail, sizeof(account->mail) - 1);
                account->mail[sizeof(account->mail) - 1] = '\0';
                updatePersonInformation(account->id, newName, newUsername, newPassword, newMail);
                Color_Green();
                printf("\nAccount updated successfully\n");
                Color_Reset();
                break;
            case 3:
                voteOperation(account);
                break;
            case 4:
                printf("\n1- TECHNOLOGY\n");
                printf("2- ECONOMY\n");
                printf("3- POLITICS\n");
                printf("4- FSMVU\n");
                Color_White();
                printf("\nPlease choose which category you want to look at the vote rate of a topic : ");
                Color_Reset();
                scanf("%d", &categoryOption);

                switch (categoryOption)
                {
                case 1:
                    Color_Green();
                    printf("\n--------------- TECHNOLOGY ---------------\n\n");
                    Color_Reset();
                    flag = 0;
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].category == 0)
                        {
                            countCategory1++;
                            printf("Name of the topic : %s / ID of the topic : %d\n", topics[i].topicName, topics[i].id);
                            Color_Blue();
                            printf("------------------------------------------------------\n");
                            Color_Reset();
                        }
                    }
                    if (countCategory1 == 0)
                    {
                        Color_Red();
                        printf("\nYou don't have a topic in this category\n");
                        Color_Reset();
                        break;
                    }
                    Color_White();
                    printf("\nPlease enter the ID of the topic for which you want to see the vote rate : ");
                    Color_Reset();
                    scanf("%d", &topicID);
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].id == topicID && topics[i].category == 0)
                        {
                            flag = 1;
                        }
                    }
                    if (flag == 1)
                    {
                        calculateVoteRate(topicID);
                    }
                    else
                    {
                        Color_Red();
                        printf("\nPlease enter valid ID!\n");
                        Color_Reset();
                        break;
                    }
                    break;
                case 2:
                    Color_Green();
                    printf("\n--------------- ECONOMY ---------------\n\n");
                    Color_Reset();
                    flag = 0;
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].category == 1)
                        {
                            countCategory2++;
                            printf("Name of the topic : %s / ID of the topic : %d\n", topics[i].topicName, topics[i].id);
                            Color_Blue();
                            printf("------------------------------------------------------\n");
                            Color_Reset();
                        }
                    }
                    if (countCategory2 == 0)
                    {
                        Color_Red();
                        printf("\nYou don't have a topic in this category\n");
                        Color_Reset();
                        break;
                    }
                    Color_White();
                    printf("\nPlease enter the ID of the topic for which you want to see the vote rate : ");
                    Color_Reset();
                    scanf("%d", &topicID);
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].id == topicID && topics[i].category == 1)
                        {
                            flag = 1;
                        }
                    }
                    if (flag == 1)
                    {
                        calculateVoteRate(topicID);
                    }
                    else
                    {
                        Color_Red();
                        printf("\nPlease enter valid ID!\n");
                        Color_Reset();
                        break;
                    }
                    break;
                case 3:
                    Color_Green();
                    printf("\n--------------- POLITICS ---------------\n\n");
                    Color_Reset();
                    flag = 0;
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].category == 2)
                        {
                            countCategory3++;
                            printf("Name of the topic : %s / ID of the topic : %d\n", topics[i].topicName, topics[i].id);
                            Color_Blue();
                            printf("------------------------------------------------------\n");
                            Color_Reset();
                        }
                    }
                    if (countCategory3 == 0)
                    {
                        Color_Red();
                        printf("\nYou don't have a topic in this category\n");
                        Color_Reset();
                        break;
                    }
                    Color_White();
                    printf("\nPlease enter the ID of the topic for which you want to see the vote rate : ");
                    Color_Reset();
                    scanf("%d", &topicID);
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].id == topicID && topics[i].category == 2)
                        {
                            flag = 1;
                        }
                    }
                    if (flag == 1)
                    {
                        calculateVoteRate(topicID);
                    }
                    else
                    {
                        Color_Red();
                        printf("\nPlease enter valid ID!\n");
                        Color_Reset();
                        break;
                    }
                    break;
                case 4:
                    Color_Green();
                    printf("\n--------------- FSMVU ---------------\n\n");
                    Color_Reset();
                    flag = 0;
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].category == 3)
                        {
                            countCategory4++;
                            printf("Name of the topic : %s / ID of the topic : %d\n", topics[i].topicName, topics[i].id);
                            Color_Blue();
                            printf("------------------------------------------------------\n");
                            Color_Reset();
                        }
                    }
                    if (countCategory4 == 0)
                    {
                        Color_Red();
                        printf("\nYou don't have a topic in this category\n");
                        Color_Reset();
                        break;
                    }
                    Color_White();
                    printf("\nPlease enter the ID of the topic for which you want to see the vote rate : ");
                    Color_Reset();
                    scanf("%d", &topicID);
                    for (int i = 0; i < topicCount; i++)
                    {
                        if (topics[i].id == topicID && topics[i].category == 3)
                        {
                            flag = 1;
                        }
                    }
                    if (flag == 1)
                    {
                        calculateVoteRate(topicID);
                    }
                    else
                    {
                        Color_Red();
                        printf("\nPlease enter valid ID!\n");
                        Color_Reset();
                        break;
                    }
                    break;
                }
                break;
            case 5:
                isLoggedIn = 0;
                break;
            default:
                Color_Red();
                printf("\nInvalid option. Please select 1, 2, or 3.\n");
                Color_Reset();
                while (getchar() != '\n')
                    ; // To prevent it from going into an infinite loop when I enter data of String type.
                break;
            }
        }
        else
        {
            Color_Green();
            printf("\n--------- WELCOME TO VOTING SYSTEM ---------\n");
            Color_Reset();
            printf("1- Login\n");
            printf("2- Register\n");
            printf("3- Exit\n");

            Color_White();
            printf("\nSelect an option: ");
            Color_Reset();
            scanf("%d", &option);

            char name[30];
            char username[30];
            char password[30];
            char mail[50];

            switch (option)
            {
            case 1:
                Color_White();
                printf("\nEnter your username: ");
                Color_Reset();
                fflush(stdin);
                gets(username);

                Color_White();
                printf("Enter your password: ");
                Color_Reset();
                fflush(stdin);
                gets(password);

                Color_Yellow();
                printf("\nLogging in...\n\n");
                Color_Reset();
                account = login(username, password);
                if (account != NULL)
                {
                    isLoggedIn = 1;
                    break;
                }
                else
                {
                    Color_Red();
                    printf("User not found! Please try again.\n");
                    Color_Reset();
                    continue;
                }
                break;

            case 2:
                Color_White();
                printf("\nEnter your name: ");
                Color_Reset();
                fflush(stdin);
                gets(name);

                Color_White();
                printf("Enter your username: ");
                Color_Reset();
                fflush(stdin);
                gets(username);

                Color_White();
                printf("Enter your password: ");
                Color_Reset();
                fflush(stdin);
                gets(password);

                Color_White();
                printf("Enter your mail: ");
                Color_Reset();
                fflush(stdin);
                gets(mail);

                account = (createPerson(userID, name, username, password, mail, 0));
                Color_Green();
                printf("\nAccount created succesfully!\n\n");
                Color_Green();
                userID++;
                isLoggedIn = 1;
                break;
            case 3:
                Color_Magenta();
                printf("\n------------ Goodbye! ------------\n");
                Color_Reset();
                return 0;
            default:
                Color_Red();
                printf("Invalid option. Please select 1, 2 or 3.\n");
                Color_Reset();
                while (getchar() != '\n')
                    ; // To prevent it from going into an infinite loop when I enter data of String type.
                break;
            }
        }
    }
    return 0;
}

void defaultInformation()
{
    Person *admin = createPerson(0, "Admin", "admin", "123", "admin@gmail.com", true);
    Person *user = createPerson(1, "Emirhan", "emirhan", "123", "emirhan@gmail.com", false);
    Person *user1 = createPerson(2, "Asim", "asim", "123", "asim@gmail.com", false);

    // About technology
    char *topicOptions1[2] = {"Yes", "No"}; // Will Baykar Technology company grow this year?
    char *topicOptions2[2] = {"Yes", "No"}; // Will Apple company grow this year?

    // About economy
    char *topicOptions3[2] = {"Yes", "No"}; // Will the dollar lose value this year?
    char *topicOptions4[2] = {"Yes", "No"}; // Will the euro lose value this year?

    // About politics
    char *topicOptions5[4] = {"A political party", "B political party", "C political party", "D political party"}; // Who will win this year's elections?

    // About FSMVU
    char *topicOptions6[2] = {"Yes", "No"}; // Will the rector of FSMVU change this year?

    Topic topic1 = createTopic(0, "Will Baykar Technology company grow this year?", topicOptions1, 2, TECHNOLOGY, 1);
    Topic topic2 = createTopic(1, "Will Apple company grow this year?", topicOptions2, 2, TECHNOLOGY, 1);

    Topic topic3 = createTopic(2, "Will the dollar lose value this year?", topicOptions3, 2, ECONOMY, 1);
    Topic topic4 = createTopic(3, "Will the euro lose value this year?", topicOptions4, 2, ECONOMY, 1);

    Topic topic5 = createTopic(4, "Who will win this year's elections?", topicOptions5, 4, POLITICS, 1);

    Topic topic6 = createTopic(5, "Will the rector of FSMVU change this year?", topicOptions6, 2, FSMVU, 1);
}