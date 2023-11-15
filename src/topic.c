#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/topic.h"

#define calculateVoteRate(Id) \
    do { \
        int numberOfVote = 0; \
        int voteCountForTopic = 0; \
        for (int i = 0; i < topicCount; i++) { \
            if (topics[i].id == Id) { \
                voteCountForTopic = findVoteCountForTopic(&topics[i]);  \
                for (int j = 0; j < topics[i].optionLength; j++) { \
                    numberOfVote = topics[i].findVoteCountForTopicOption(&topics[i])[j]; \
                    if (voteCountForTopic != 0) { \
                        printf("%d) %s --> Vote Count/Rate : %d (%%%.2f)\n", (j + 1), topics[i].topicOptions[j], numberOfVote, ((float)numberOfVote / voteCountForTopic) * 100); \
                    } else { \
                        printf("%d) %s --> Vote Count/Rate : %d (Undefined)\n", (j + 1), topics[i].topicOptions[j], numberOfVote); \
                    } \
                } \
            } \
        } \
    } while(0)


static const char *const categories_names[] = {
    [TECHNOLOGY] = "TECHNOLOGY",
    [ECONOMY] = "ECONOMY",
    [POLITICS] = "POLITICS",
    [FSMVU] = "FSMVU"};

int findVoteCountForTopic(Topic *self)
{
    int total = 0;
    for (int i = 0; i < voteCount; i++)
    {
        if (votes[i].topic.id == self->id)
        {
            total++;
        }
    }
    return total;
}

int *findVoteCountForTopicOption(Topic *self)
{
    int *total;
    total = malloc(self->optionLength * sizeof(int)); // Şık sayısı * integer'ın baytı
    for (int i = 0; i < self->optionLength; i++) {
        total[i] = 0;
    }

    for (int i = 0; i < voteCount; i++)
    {
        if (votes[i].topic.id == (self->id))
        {
            total[votes[i].topicOptionIndex]++;
        }
    }
    return total;
}

Topic createTopic(int id, char *topicName, char *topicOptions[], int optionLength,Categories category, bool isOpen){
    Topic topic;
    topic.id = id;
    strcpy(topic.topicName , topicName);
    for (int i = 0; i < optionLength; i++) 
    {
        topic.topicOptions[i] = topicOptions[i];   
    }
    topic.optionLength = optionLength; 
    topic.isOpen = isOpen;
    topic.category = category;
    topic.findVoteCountForTopic = findVoteCountForTopic;
    topic.findVoteCountForTopicOption = findVoteCountForTopicOption;
    insertTopic(topic);
    topics[topicCount] = topic;
    topicCount++;
    return topic;
}

