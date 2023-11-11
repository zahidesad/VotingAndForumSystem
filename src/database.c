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
        }else if (lineNum == 4)
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
    char chunk[128];
    int lineNum = 0;
    int topicCount = 0;
    int optionIndex = 0;
    bool skipTopic = false;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % (40 + 2) == 0)
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
        else if (lineNum % (40 + 2) == 1)
        {
            strcpy(topic->topicName, chunk);
            if (!skipTopic)
            {
                fprintf(temp, "%s\n", topic->topicName);
            }
            lineNum++;
        }
        else if (lineNum % (40 + 2) >= 2 && lineNum % (40 + 2) < 42)
        {
            topic->topicOptions[optionIndex] = (char *)malloc(strlen(chunk) + 1);
            strcpy(topic->topicOptions[optionIndex], chunk);
            if (!skipTopic)
            {
                fprintf(temp, "%s\n", topic->topicOptions[optionIndex]);
            }
            optionIndex++;
            lineNum++;
        }
        else if (lineNum % (40 + 2) == 42)
        {
            topic->optionLength = atoi(chunk);
            if (!skipTopic)
            {
                fprintf(temp, "%d\n", topic->optionLength);
                tempTopics[topicCount] = topic;
                topicCount++;
            }
            skipTopic = false;
            optionIndex = 0;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../txtFiles/topic.txt");
    rename("../txtFiles/temp.txt", "../txtFiles/topic.txt");

    // Clear and update topics array
    memset(topics, 0, sizeof(topics));
    for (int i = 0; i < topicCount; i++)
    {
        topics[i] = *tempTopics[i];
    }
    topicCount = topicCount;

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

void showAllTopics()
{
    
    for (int i = 0; i < topicCount; i++)
    {
        Color_Blue();
        printf("------ %d. Topic ------\n", i + 1);
        Color_Reset();
        printf("ID of the topic : %d\n", topics[i].id);
        printf("Name of the topic : %s\n", topics[i].topicName);
        printf("Number of option of the topic : %d\n", topics[i].optionLength);
        printf("Category of the topic : %s\n", categories_names[topics[i].category]);
        for (int j = 0; j < topics[i].optionLength; j++)
        {
            printf("%d. Option of the topic : %s\n", j + 1, topics[i].topicOptions[j]);
        }
    }
}
