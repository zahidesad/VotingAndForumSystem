#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../Colors/color.h"
#include "../header/person.h"
#include "../header/topic.h"
#include "../header/vote.h"

#define MAX 1000

static Person users[MAX];
static int userCount = 0;
static Vote votes[MAX];
static int voteCount = 0;
static Topic topics[MAX];
static int topicCount = 0;

static const char *const categories_names[];

Person *login(char *username, char *password)
{

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return &users[i];
        }
    }
    Person *nullP = NULL;
    return nullP;
}

int insertPerson(Person person)
{
    FILE *file = fopen("../txtFiles/person.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    fprintf(file, "%d\n", person.id);
    fprintf(file, "%s\n", person.name);
    fprintf(file, "%s\n", person.username);
    fprintf(file, "%s\n", person.password);
    fprintf(file, "%s\n", person.mail);
    fprintf(file, "%d\n", person.isAdmin);

    fclose(file);
    return 0;
}

int insertTopic(Topic topic)
{
    FILE *file = fopen("../txtFiles/topic.txt", "a");
    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    fprintf(file, "%d\n", topic.id);
    fprintf(file, "%s\n", topic.topicName);
    fprintf(file, "%d\n", topic.optionLength);
    fprintf(file, "%d\n", topic.isOpen);
    fprintf(file, "%d\n", topic.category);
    for (int i = 0; i < topic.optionLength; i++)
    {
        fprintf(file, "%s\n", topic.topicOptions[i]);
    }
    fclose(file);
    return 0;
}

int insertVote(Vote vote)
{
    FILE *file = fopen("../txtFiles/vote.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    fprintf(file, "%d\n", vote.id);
    fprintf(file, "%d\n", vote.voter.id);
    fprintf(file, "%d\n", vote.topic.id);
    fprintf(file, "%d\n", vote.topicOptionIndex);

    fclose(file);
    return 0;
}

int readPerson()
{
    FILE *file = fopen("../txtFiles/person.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    Person *person;
    char chunk[128];
    int lineNum = 0;
    int personCount = 0;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {

        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n"); // \n kesmeye çalışıyoruz yoksa değerlerin için \n eklenir
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 6 == 0)
        {
            person = (Person *)malloc(sizeof(Person));
            person->id = atoi(chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 1)
        {
            strcpy(person->name, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 2)
        {
            strcpy(person->username, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 3)
        {
            strcpy(person->password, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 4)
        {
            strcpy(person->mail, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 5)
        {
            person->isAdmin = atoi(chunk);
            lineNum++;
            users[personCount] = *person;
            personCount++;
        }
    }
    userCount = personCount;
    fclose(file);
    return 0;
}

int readTopic()
{
    FILE *file = fopen("../txtFiles/topic.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Topic *topic;
    char chunk[200];
    int lineNum = 0;
    topicCount = 0;
    int optionCount = 0;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum == 0)
        {
            topic = (Topic *)malloc(sizeof(Topic));
            if (topic == NULL)
            {
                printf("Memory allocation failed!");
                return 1;
            }
            topic->id = atoi(chunk);
        }
        else if (lineNum == 1)
        {
            strcpy(topic->topicName, chunk);
        }
        else if (lineNum == 2)
        {
            topic->optionLength = atoi(chunk);
            optionCount = topic->optionLength;
        }
        else if (lineNum == 3)
        {
            topic->isOpen = atoi(chunk);
        }
        else if (lineNum == 4)
        {
            topic->category = atoi(chunk);
        }
        else if (lineNum <= optionCount + 5 && optionCount != 0)
        {
            topic->topicOptions[lineNum - 5] = malloc(strlen(chunk) + 1);
            if (topic->topicOptions[lineNum - 5] == NULL)
            {
                printf("Memory allocation failed!");
                return 1;
            }
            strcpy(topic->topicOptions[lineNum - 5], chunk);
        }

        lineNum++;

        if (lineNum == optionCount + 5)
        {
            topic->findVoteCountForTopic = findVoteCountForTopic;
            topic->findVoteCountForTopicOption = findVoteCountForTopicOption;
            topics[topicCount] = *topic;
            topicCount++;
            lineNum = 0;
            optionCount = 0;
        }
    }
    fclose(file);
    return 0;
}

int readVote()
{
    FILE *file = fopen("../txtFiles/vote.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    Vote *vote;
    char chunk[128];
    int lineNum = 0;
    int tempVoteCount = 0;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {

        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n"); // \n kesmeye çalışıyoruz yoksa değerlerin için \n eklenir
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 4 == 0)
        {
            vote = (Vote *)malloc(sizeof(Vote));
            vote->id = atoi(chunk);
            lineNum++;
        }
        else if (lineNum % 4 == 1)
        {
            int voterId = atoi(chunk);
            for (int i = 0; i < userCount; i++)
            {
                if (users[i].id == voterId)
                {
                    vote->voter = users[i];
                }
            }
            lineNum++;
        }
        else if (lineNum % 4 == 2)
        {
            int topicId = atoi(chunk);
            for (int i = 0; i < topicCount; i++)
            {
                if (topics[i].id == topicId)
                {
                    vote->topic = topics[i];
                }
            }
            lineNum++;
        }
        else if (lineNum % 4 == 3)
        {
            vote->topicOptionIndex = atoi(chunk);
            lineNum++;
            votes[tempVoteCount] = *vote;
            tempVoteCount++;
        }
    }
    voteCount = tempVoteCount;
    fclose(file);
    return 0;
}

int deletePerson(int id)
{
    FILE *file = fopen("../txtFiles/person.txt", "r");
    FILE *temp = fopen("../txtFiles/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Person *person;
    Person *tempUsers[userCount - 1];
    char chunk[128];
    int lineNum = 0;
    int personCount = 0;
    bool skipPerson = false;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 6 == 0)
        {
            person = (Person *)malloc(sizeof(Person));
            person->id = atoi(chunk);
            if (person->id == id)
            {
                skipPerson = true;
            }
            else
            {
                fprintf(temp, "%d\n", person->id);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 1)
        {
            strcpy(person->name, chunk);
            if (!skipPerson)
            {
                fprintf(temp, "%s\n", person->name);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 2)
        {
            strcpy(person->username, chunk);
            if (!skipPerson)
            {
                fprintf(temp, "%s\n", person->username);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 3)
        {
            strcpy(person->password, chunk);
            if (!skipPerson)
            {
                fprintf(temp, "%s\n", person->password);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 4)
        {
            strcpy(person->mail, chunk);
            if (!skipPerson)
            {
                fprintf(temp, "%s\n", person->mail);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 5)
        {
            person->isAdmin = atoi(chunk);
            if (!skipPerson)
            {
                fprintf(temp, "%d\n", person->isAdmin);
                tempUsers[personCount] = person;
                personCount++;
            }
            skipPerson = false;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../txtFiles/person.txt");
    rename("../txtFiles/temp.txt", "../txtFiles/person.txt");

    // Clear and update users array
    memset(users, 0, sizeof(users));
    for (int i = 0; i < personCount; i++)
    {
        users[i] = *tempUsers[i];
    }
    userCount = personCount;

    return 0;
}

int deleteTopic(int id)
{
    FILE *file = fopen("../txtFiles/topic.txt", "r");
    FILE *temp = fopen("../txtFiles/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Topic *topic;
    Topic *tempTopics[topicCount - 1];
    char chunk[200];
    int lineNum = 0;
    int tempTopicCount = 0;
    bool skipTopic = false;
    int optionCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum == 0)
        {
            topic = (Topic *)malloc(sizeof(Topic));
            topic->id = atoi(chunk);
            if (topic->id == id)
            {
                skipTopic = true;
            }
            else
            {
                fprintf(temp, "%d\n", topic->id);
            }
            lineNum++;
        }
        else if (lineNum == 1)
        {
            strcpy(topic->topicName, chunk);
            if (!skipTopic)
            {
                fprintf(temp, "%s\n", topic->topicName);
            }
            lineNum++;
        }
        else if (lineNum == 2)
        {
            topic->optionLength = atoi(chunk);
            optionCount = topic->optionLength;
            if (!skipTopic)
            {
                fprintf(temp, "%d\n", topic->optionLength);
            }
            lineNum++;
        }
        else if (lineNum == 3)
        {
            topic->isOpen = atoi(chunk);
            if (!skipTopic)
            {
                fprintf(temp, "%d\n", topic->isOpen);
            }
            lineNum++;
        }
        else if (lineNum == 4)
        {
            topic->category = atoi(chunk);
            if (!skipTopic)
            {
                fprintf(temp, "%d\n", topic->category);
            }
            lineNum++;
        }
        else if (lineNum <= optionCount + 5 && optionCount != 0)
        {
            topic->topicOptions[lineNum - 5] = malloc(strlen(chunk) + 1);
            if (topic->topicOptions[lineNum - 5] == NULL)
            {
                printf("Memory allocation failed!");
                return 1;
            }
            strcpy(topic->topicOptions[lineNum - 5], chunk);
            if (!skipTopic)
            {
                fprintf(temp, "%s\n", topic->topicOptions[lineNum - 5]);
            }
            lineNum++;
        }

        if (lineNum == optionCount + 5)
        {
            if (!skipTopic)
            {
                topic->findVoteCountForTopic = findVoteCountForTopic;
                topic->findVoteCountForTopicOption = findVoteCountForTopicOption;
                tempTopics[tempTopicCount] = topic;
                tempTopicCount++;
            }
            skipTopic = false;
            lineNum = 0;
            optionCount = 0;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../txtFiles/topic.txt");
    rename("../txtFiles/temp.txt", "../txtFiles/topic.txt");

    // Clear and update topics array
    memset(topics, 0, sizeof(topics));
    for (int i = 0; i < tempTopicCount; i++)
    {
        topics[i] = *tempTopics[i];
    }
    topicCount = tempTopicCount;

    return 0;
}

int deleteVote(int voteId)
{
    FILE *file = fopen("../txtFiles/vote.txt", "r");
    FILE *temp = fopen("../txtFiles/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Vote *vote;
    Vote *tempVotes[voteCount - 1];
    char chunk[128];
    int lineNum = 0;
    int tempVoteCount = 0;
    bool skipVote = false;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 4 == 0)
        {
            vote = (Vote *)malloc(sizeof(Vote));
            vote->id = atoi(chunk);
            if (vote->id == voteId)
            {
                skipVote = true;
            }
            else
            {
                fprintf(temp, "%d\n", vote->id);
            }
            lineNum++;
        }
        else if (lineNum % 4 == 1)
        {
            int voterId = atoi(chunk);
            if (!skipVote)
            {
                for (int i = 0; i < userCount; i++)
                {
                    if (users[i].id == voterId)
                    {
                        vote->voter = users[i];
                        fprintf(temp, "%d\n", vote->voter.id);
                    }
                }
            }
            lineNum++;
        }
        else if (lineNum % 4 == 2)
        {
            int topicId = atoi(chunk);
            if (!skipVote)
            {
                for (int i = 0; i < topicCount; i++)
                {
                    if (topics[i].id == topicId)
                    {
                        vote->topic = topics[i];
                        fprintf(temp, "%d\n", vote->topic.id);
                    }
                }
            }
            lineNum++;
        }
        else if (lineNum % 4 == 3)
        {
            vote->topicOptionIndex = atoi(chunk);
            if (!skipVote)
            {
                fprintf(temp, "%d\n", vote->topicOptionIndex);
                tempVotes[tempVoteCount] = vote;
                tempVoteCount++;
            }
            skipVote = false;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../txtFiles/vote.txt");
    rename("../txtFiles/temp.txt", "../txtFiles/vote.txt");

    // Clear and update votes array
    memset(votes, 0, sizeof(votes));
    for (int i = 0; i < tempVoteCount; i++)
    {
        votes[i] = *tempVotes[i];
    }
    voteCount = tempVoteCount;

    return 0;
}

int updatePersonInformation(int id, char *newName, char *newUsername, char *newPassword, char *newMail)
{
    FILE *file = fopen("../txtFiles/person.txt", "r");
    FILE *temp = fopen("../txtFiles/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Person *person;
    Person *tempUsers[userCount];
    char chunk[128];
    int lineNum = 0;
    int personCount = 0;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 6 == 0)
        {
            person = (Person *)malloc(sizeof(Person));
            person->id = atoi(chunk);
            if (person->id == id)
            {
                person->id = id;
                strcpy(person->name, newName);
                strcpy(person->username, newUsername);
                strcpy(person->password, newPassword);
                strcpy(person->mail, newMail);
                if (person->id == 0) // Checking for admin
                {
                    person->isAdmin = 1;
                }
                else // If he/she isn't admin, he/she is a user.
                {
                    person->isAdmin = 0;
                }
            }
            fprintf(temp, "%d\n", person->id);
            lineNum++;
        }
        else if (lineNum % 6 == 1)
        {
            if (person->id != id)
            {
                strcpy(person->name, chunk);
            }
            fprintf(temp, "%s\n", person->name);
            lineNum++;
        }
        else if (lineNum % 6 == 2)
        {
            if (person->id != id)
            {
                strcpy(person->username, chunk);
            }
            fprintf(temp, "%s\n", person->username);
            lineNum++;
        }
        else if (lineNum % 6 == 3)
        {
            if (person->id != id)
            {
                strcpy(person->password, chunk);
            }
            fprintf(temp, "%s\n", person->password);
            lineNum++;
        }
        else if (lineNum % 6 == 4)
        {
            if (person->id != id)
            {
                strcpy(person->mail, chunk);
            }
            fprintf(temp, "%s\n", person->mail);
            lineNum++;
        }
        else if (lineNum % 6 == 5)
        {
            if (person->id != id)
            {
                person->isAdmin = atoi(chunk);
            }
            fprintf(temp, "%d\n", person->isAdmin);
            tempUsers[personCount] = person;
            personCount++;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../txtFiles/person.txt");
    rename("../txtFiles/temp.txt", "../txtFiles/person.txt");

    // Clear and update users array
    memset(users, 0, sizeof(users));
    for (int i = 0; i < personCount; i++)
    {
        users[i] = *tempUsers[i];
    }
    userCount = personCount;

    return 0;
}

int updateTopicInformation(int id, char *newTopicName, char *newTopicOptions[], int newOptionLength, Categories newCategory, bool isOpen)
{
    char *topicName = malloc(sizeof(newTopicName));
    strcpy(topicName, newTopicName);
    deleteTopic(id);
    createTopic(id, topicName, newTopicOptions, newOptionLength, newCategory, isOpen);
    return 0;
}

void showAllTopics()
{
    int choice = 0;
    int countCategory1 = 0; // If there are no votes in this category, use them to determine
    int countCategory2 = 0; // If there are no votes in this category, use them to determine
    int countCategory3 = 0; // If there are no votes in this category, use them to determine
    int countCategory4 = 0; // If there are no votes in this category, use them to determine
    printf("\n1- TECHNOLOGY\n");
    printf("2- ECONOMY\n");
    printf("3- POLITICS\n");
    printf("4- FSMVU\n");
    Color_White();
    printf("\nPlease choose which category of topics you want to view : ");
    Color_Reset();
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        Color_Green();
        printf("\n--------------- TECHNOLOGY ---------------\n\n");
        Color_Reset();
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].category == 0)
            {
                countCategory1++;
                printf("ID of the topic : %d\n", topics[i].id);
                printf("Name of the topic : %s\n", topics[i].topicName);
                printf("Number of option of the topic : %d\n", topics[i].optionLength);
                printf("Category of the topic : %s\n", categories_names[topics[i].category]);
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
                Color_Blue();
                printf("-------------------------------\n");
                Color_Reset();
            }
        }
        if (countCategory1 == 0)
        {
            Color_Red();
            printf("\nYou don't have a topic in this category\n");
            Color_Reset();
        }
        return;
    case 2:
        Color_Green();
        printf("\n--------------- ECONOMY ---------------\n\n");
        Color_Reset();
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].category == 1)
            {
                countCategory2++;
                printf("ID of the topic : %d\n", topics[i].id);
                printf("Name of the topic : %s\n", topics[i].topicName);
                printf("Number of option of the topic : %d\n", topics[i].optionLength);
                printf("Category of the topic : %s\n", categories_names[topics[i].category]);
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
                Color_Blue();
                printf("-------------------------------\n");
                Color_Reset();
            }
        }
        if (countCategory2 == 0)
        {
            Color_Red();
            printf("\nYou don't have a topic in this category\n");
            Color_Reset();
        }
        return;
    case 3:
        Color_Green();
        printf("\n--------------- POLITICS ---------------\n\n");
        Color_Reset();
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].category == 2)
            {
                countCategory3++;
                printf("ID of the topic : %d\n", topics[i].id);
                printf("Name of the topic : %s\n", topics[i].topicName);
                printf("Number of option of the topic : %d\n", topics[i].optionLength);
                printf("Category of the topic : %s\n", categories_names[topics[i].category]);
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
                Color_Blue();
                printf("-------------------------------\n");
                Color_Reset();
            }
        }
        if (countCategory3 == 0)
        {
            Color_Red();
            printf("\nYou don't have a topic in this category\n");
            Color_Reset();
        }
        return;

    case 4:
        Color_Green();
        printf("\n--------------- FSMVU ---------------\n\n");
        Color_Reset();
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].category == 3)
            {
                countCategory4++;
                printf("ID of the topic : %d\n", topics[i].id);
                printf("Name of the topic : %s\n", topics[i].topicName);
                printf("Number of option of the topic : %d\n", topics[i].optionLength);
                printf("Category of the topic : %s\n", categories_names[topics[i].category]);
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
                Color_Blue();
                printf("-------------------------------\n");
                Color_Reset();
            }
        }
        if (countCategory4 == 0)
        {
            Color_Red();
            printf("\nYou don't have a topic in this category\n");
            Color_Reset();
        }
        return;
    default:
        Color_Red();
        printf("Invalid option. Please select [1-4]\n");
        Color_Reset();
        while (getchar() != '\n')
            ; // To prevent it from going into an infinite loop when I enter data of String type.
        break;
    }
}

void readAllData()
{
    readPerson();
    readTopic();
    readVote();
}

int changeOpenStatus(int id)

{
    char *newTopicName;
    char *newTopicOptions[40];
    int newOptionLength;
    bool isOpen;
    Categories newCategory;

    for (int i = 0; i < topicCount; i++)
    {
        if (topics[i].id == id)
        {
            newTopicName = topics[i].topicName;
            printf("Inside of changeOpenStatus : %s\n", newTopicName);
            newOptionLength = topics[i].optionLength;
            for (int j = 0; j < newOptionLength; j++)
            {
                newTopicOptions[j] = topics[i].topicOptions[j];
            }
            newCategory = topics[i].category;
            isOpen = !topics[i].isOpen;
            updateTopicInformation(id, newTopicName, newTopicOptions, newOptionLength, newCategory, isOpen);
            break;
        }
    }

    return 0;
}

void voteOperation(Person *account)
{
    int categoryOption = 0;
    int topicID = 0;
    int countCategory1 = 0; // If there are no votes in this category, use them to determine
    int countCategory2 = 0; // If there are no votes in this category, use them to determine
    int countCategory3 = 0; // If there are no votes in this category, use them to determine
    int countCategory4 = 0; // If there are no votes in this category, use them to determine
    int optionIndex = 0;
    bool flag = 0;

    printf("\n1- TECHNOLOGY\n");
    printf("2- ECONOMY\n");
    printf("3- POLITICS\n");
    printf("4- FSMVU\n");
    Color_White();
    printf("\nPlease choose which category of topics you want to vote : ");
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
            if (topics[i].category == 0 && topics[i].isOpen == 1)
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
        printf("\nPlease enter the ID of the topic you want to vote on : ");
        Color_Reset();
        scanf("%d", &topicID);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 0)
            {
                flag = 1;
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
            }
        }
        if (flag == 0)
        {
            Color_Red();
            printf("\nPlease enter valid ID!\n");
            Color_Reset();
            break;
        }
        Color_White();
        printf("\nPlease enter which option you want to vote for : ");
        Color_Reset();
        scanf("%d", &optionIndex);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 0)
            {
                createVote(voteCount, *account, topics[i], optionIndex - 1);
                Color_Green();
                printf("\nYou have voted successfully.\n");
                Color_Reset();
                break;
            }
        }
        break;
    case 2:
        Color_Green();
        printf("\n--------------- ECONOMY ---------------\n\n");
        Color_Reset();
        flag = 0;
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].category == 1 && topics[i].isOpen == 1)
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
        printf("\nPlease enter the ID of the topic you want to vote on : ");
        Color_Reset();
        scanf("%d", &topicID);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 1)
            {
                flag = 1;
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
            }
        }
        if (flag == 0)
        {
            Color_Red();
            printf("\nPlease enter valid ID!\n");
            Color_Reset();
            break;
        }
        Color_White();
        printf("\nPlease enter which option you want to vote for : ");
        Color_Reset();
        scanf("%d", &optionIndex);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 1)
            {
                createVote(voteCount, *account, topics[i], optionIndex - 1);
                Color_Green();
                printf("\nYou have voted successfully.\n");
                Color_Reset();
                break;
            }
        }
        break;

    case 3:
        Color_Green();
        printf("\n--------------- POLITICS ---------------\n\n");
        Color_Reset();
        flag = 0;
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].category == 2 && topics[i].isOpen == 1)
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
        printf("\nPlease enter the ID of the topic you want to vote on : ");
        Color_Reset();
        scanf("%d", &topicID);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 2)
            {
                flag = 1;
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
            }
        }
        if (flag == 0)
        {
            Color_Red();
            printf("\nPlease enter valid ID!\n");
            Color_Reset();
            break;
        }
        Color_White();
        printf("\nPlease enter which option you want to vote for : ");
        Color_Reset();
        scanf("%d", &optionIndex);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 2)
            {
                createVote(voteCount, *account, topics[i], optionIndex - 1);
                Color_Green();
                printf("\nYou have voted successfully.\n");
                Color_Reset();
                break;
            }
        }
        break;

    case 4:
        Color_Green();
        printf("\n--------------- FSMVU ---------------\n\n");
        Color_Reset();
        flag = 0;
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].category == 3 && topics[i].isOpen == 1)
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
        printf("\nPlease enter the ID of the topic you want to vote on : ");
        Color_Reset();
        scanf("%d", &topicID);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 3)
            {
                flag = 1;
                for (int j = 0; j < topics[i].optionLength; j++)
                {
                    printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
                }
            }
        }
        if (flag == 0)
        {
            Color_Red();
            printf("\nPlease enter valid ID!\n");
            Color_Reset();
            break;
        }
        Color_White();
        printf("\nPlease enter which option you want to vote for : ");
        Color_Reset();
        scanf("%d", &optionIndex);
        for (int i = 0; i < topicCount; i++)
        {
            if (topics[i].id == topicID && topics[i].category == 3)
            {
                createVote(voteCount, *account, topics[i], optionIndex - 1);
                Color_Green();
                printf("\nYou have voted successfully.\n");
                Color_Reset();
                break;
            }
        }
        break;
    default:
        Color_Red();
        printf("\nInvalid option. Please select [1-4]\n");
        Color_Reset();
        break;
    }
}
