#include <stdio.h>
#include <stdlib.h>
#include "../src/database.c"
#include "../src/person.c"
#include "../src/topic.c"
#include "../src/vote.c"
#include "../Colors/color.c"

int Display();

int main()
{
    // Person *admin = createPerson(0, "Admin", "admin", "123", "admin@gmail.com", true);
    // Person *user = createPerson(1, "Emirhan", "emirhan", "123", "emirhan@gmail.com", false);
    // Person *user1 = createPerson(2, "Asim", "asim", "123", "asim@gmail.com", false);
    readPerson();
    /*("Name of admin : %s\n",users[1].name);
    printf("ID of user : %d\n",users[1].id);
    printf("Name of user : %s\n",users[1].name);
    printf("Username of user : %s\n",users[1].username);
    printf("Mail of user : %s\n",users[1].mail);*/

    // char *topicOptions[4] = {"a", "b", "c", "d"};
    // char *topicOptions1[4] = {"e", "f", "g", "h"};
    // char *topicOptions2[4] = {"i", "j", "k", "l"};

    // Topic topic = createTopic(0,"DolarTL",topicOptions,4,TECHNOLOGY);
    // Topic topic1 = createTopic(1,"EuroTL",topicOptions1,4,ECONOMY);
    // Topic topic2 = createTopic(2,"PoundTL",topicOptions2,4,FSMVU);
    readTopic();
    // char *newTopicOptions[4] = {"Artar", "Azalir", "Sabit", "Yorumsuz"};
    // updateTopicInformation(0, "DOLARTL", newTopicOptions, 4, ECONOMY);
    /*for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].id == 0)
        {
            printf("ID of topic : %d\n", topics[i].id);
            printf("Name of topic : %s\n", topics[i].topicName);
            printf("Number of topic option : %d\n", topics[i].optionLength);
            printf("Open status of topic : %d\n", topics[i].isOpen);
            printf("Category of topic : %s\n", categories_names[topics[i].category]);
            printf("First Option of topic : %s\n", topics[i].topicOptions[0]);
            printf("Second Option of topic : %s\n", topics[i].topicOptions[1]);
            printf("Third Option of topic : %s\n", topics[i].topicOptions[2]);
            printf("Fourth Option of topic : %s\n", topics[i].topicOptions[3]);
        }
    }*/
    // printf("Topic Count : %d\n" , topicCount);
    /*deleteTopic(topics[0].id);
    printf("ID of topic : %d\n", topics[2].id);
    printf("Name of topic : %s\n", topics[2].topicName);
    printf("Number of topic option : %d\n", topics[2].optionLength);
    printf("Open status of topic : %d\n", topics[2].isOpen);
    printf("Category of topic : %s\n", categories_names[topics[2].category]);
    printf("First Option of topic : %s\n", topics[2].topicOptions[0]);
    printf("Second Option of topic : %s\n", topics[2].topicOptions[1]);
    printf("Third Option of topic : %s\n", topics[2].topicOptions[2]);
    printf("Fourth Option of topic : %s\n", topics[2].topicOptions[3]);*/
    // printf("Topic Count : %d\n" , topicCount);
    // deletePerson(users[0].id);
    // printf("User Count : %d\n" , userCount);

    // Vote vote1 = createVote(0, users[1], topics[0], 2);
    // Vote vote2 = createVote(1, users[2], topics[0], 3);
    // Vote vote3 = createVote(2, users[1], topics[1], 1);
    readVote();
    // deleteVote(votes[0].id); // 1 2 0 3 2 1 1 1 / 0 1 0 2 2 1 1 1
    /*printf("ID of vote : %d\n", votes[0].id);
    printf("Voter of vote : %s\n", votes[0].voter.name);
    printf("Topic of vote : %s\n", votes[0].topic.topicName);
    printf("Topic Option Index of vote : %d\n", votes[0].topicOptionIndex);
    printf("Vote Count : %d\n", voteCount);
    printf("Test Method : %d\n", topics[0].findVoteCountForTopic(&topics[0]));

    for (int i = 0; i < topics[0].optionLength; i++)
    {
        printf("%d\n", topics[0].findVoteCountForTopicOption(&topics[0])[i]);
    }*/
    Display();
    return 0;
}

int Display()
{
    Person *account;
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

                Topic topic = createTopic(topicCount, topicName, topicOptions, optionLength, category, 1);
                Color_Green();
                printf("\nTopic created successfully...\n");
                Color_Reset();
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
                printf("Please write the ID of the topic you want to update :");
                scanf("%d", &option);
                Color_Reset();

                printf("\nPlease enter your new topic name : ");
                gets(newTopicName);
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
                    fgets(newTopicOptions[i], MAX, stdin);

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
                scanf("%d", &idOpenStatus);
                changeOpenStatus(idOpenStatus);
                break;
            case 7:
                for (int i = 0; i < userCount; i++)
                {
                    printf("\n%d- Username : %s / ID of user : %d\n", (i + 1), users[i].username, users[i].id);
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
                Color_Green();
                printf("\nTopic has been deleted successfully\n");
                Color_Reset();
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
        else if (isLoggedIn && !account->isAdmin)
        {
            Color_Green();
            printf("--------- Welcome %s ---------", account->name);
            Color_Reset();
            printf("\nSelect an option : ");
            scanf("%d", &option);
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
                printf("\nEnter your username: ");
                gets(username);
                gets(username);

                printf("Enter your password: ");
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
                printf("\nEnter your name: ");
                gets(name);
                gets(name);

                printf("Enter your username: ");
                gets(username);

                printf("Enter your password: ");
                gets(password);

                printf("Enter your mail: ");
                gets(mail);

                account = (createPerson(userCount, name, username, password, mail, 0));
                Color_Green();
                printf("\nAccount created succesfully!\n\n");
                Color_Green();
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