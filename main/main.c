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
    Person *admin = createPerson(0, "Admin", "admin", "123", "admin@gmail.com", true);
    Person *user = createPerson(1, "Emirhan", "emirhan", "123", "emirhan@gmail.com", false);
    Person *user1 = createPerson(2, "Asim", "asim", "123", "asim@gmail.com", false);
    /*readPerson();
    printf("Name of admin : %s\n",users[0].name);
    printf("ID of user : %d\n",users[1].id);
    printf("Name of user : %s\n",users[1].name);
    printf("Username of user : %s\n",users[1].username);
    printf("Mail of user : %s\n",users[1].mail);*/

    /*char *topicOptions[MAX];

    Topic topic = createTopic(0,"DolarTL",topicOptions,4);
    printf("ID of topic : %d\n",topics[0].id);
    printf("Name of topic : %s\n",topics[0].topicName);
    printf("First Option of topic : %s\n", topics[0].topicOptions[0]);
    printf("Second Option of topic : %s\n", topics[0].topicOptions[1]);
    printf("Third Option of topic : %s\n", topics[0].topicOptions[2]);
    printf("Fourth Option of topic : %s\n", topics[0].topicOptions[3]);*/

    // Vote vote = createVote(0,users[1],topics[0],1);
    /*printf("ID of vote : %d\n",vote.id);
    printf("Voter of vote : %s\n",vote.voter.name);
    printf("Topic of vote : %s\n",vote.topic.topicName);
    printf("Topic Option Index of vote : %d\n",vote.topicOptionIndex);
    printf("Vote Count : %d\n", voteCount);*/
     
    //Display();
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

            printf("\n1- Create Topic\n");
            printf("2- Show All Topics\n");
            printf("3- Update Topic\n");
            printf("4- Delete Topic\n");

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

                Topic topic = createTopic(topicCount, topicName, topicOptions, optionLength);
                Color_Green();
                printf("\nTopic created successfully...\n");
                Color_Reset();
                break;

            case 2:
                showAllTopics();
                break;
            default:
                Color_Red();
                printf("\nInvalid option. Please select 1, 2, or 3.\n");
                Color_Reset();
                while (getchar() != '\n'); // To prevent it from going into an infinite loop when I enter data of String type.
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
                while (getchar() != '\n'); // To prevent it from going into an infinite loop when I enter data of String type.
                break;
            }
        }
    }
    return 0;
}