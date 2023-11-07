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
    for (int i = 0; i < topic.optionLength; i++)
    {
        fprintf(file, "%s\n", topic.topicOptions[i]);
    }
    fprintf(file, "%d\n", topic.optionLength);

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
    fprintf(file, "%s\n", vote.voter.name);
    fprintf(file, "%s\n", vote.topic.topicName);
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
}

int findVoteCountForTopic(Topic topic)
{
    int total;
    for (int i = 0; i < voteCount; i++)
    {
        if (votes[i].topic.id = topic.id)
        {
            total++;
        }
    }
    return total;
}

int *findVoteCountForTopicOption(Topic topic)
{
    int *total = malloc(topic.optionLength * sizeof(int)); // Şık sayısı * integer'ın baytı
    for (int i = 0; i < voteCount; i++)
    {
        if (votes[i].topic.id = topic.id)
        {
            total[votes[i].topicOptionIndex]++;
        }
    }
    return total;
}

void showAllTopics()
{
    for (int i = 0; i < topicCount ; i++)
    {
        Color_Blue();
        printf("------ %d. Topic ------\n",i+1);
        Color_Reset();
        printf("ID of the topic : %d\n", topics[i].id);
        printf("Name of the topic : %s\n", topics[i].topicName);
        printf("Number of option of the topic : %d\n", topics[i].optionLength);
        for (int j = 0; j < topics[i].optionLength; j++)
        {
            printf("%d. Option of the topic : %s\n",j+1,topics[i].topicOptions[j]);
        }
    }
}
