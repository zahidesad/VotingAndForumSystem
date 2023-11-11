#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/topic.h"

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
        printf("Vote id : %d\n", votes[i].id);
        printf("Topic id : %d\n", self->id);
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
    for (int i = 0; i < voteCount; i++) {
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

Topic createTopic(int id, char *topicName, char *topicOptions[], int optionLength,Categories category){
    Topic topic;
    topic.id = id;
    strcpy(topic.topicName , topicName);
    for (int i = 0; i < optionLength; i++) 
    {
        topic.topicOptions[i] = topicOptions[i];   
    }
    topic.optionLength = optionLength; 
    topic.isOpen = true;
    topic.category = category;
    topic.findVoteCountForTopic = findVoteCountForTopic;
    topic.findVoteCountForTopicOption = findVoteCountForTopicOption;
    insertTopic(topic);
    topics[topicCount] = topic;
    topicCount++;
    return topic;
}

