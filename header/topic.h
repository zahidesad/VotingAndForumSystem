#ifndef TOPIC_H
#define TOPIC_H

typedef enum{
    TECHNOLOGY,
    ECONOMY,
    POLITICS,
    FSMVU // My university name
}Categories;

typedef struct Topic
{
    int id;
    char topicName[200];
    char *topicOptions[40]; 
    int optionLength; // şık sayısı
    bool isOpen; 
    Categories category;
    int(*findVoteCountForTopic)(struct Topic *);
    int *(*findVoteCountForTopicOption)(struct Topic *);
}Topic;


Topic createTopic(int id, char *topicName, char *topicOptions[], int optionLength, Categories category,bool isOpen);

int findVoteCountForTopic(Topic *self);

int *findVoteCountForTopicOption(Topic *self);


#endif