#ifndef TOPIC_H
#define TOPIC_H

typedef struct Topic
{
    int id;
    char topicName[200];
    char *topicOptions[40]; 
    int optionLength; // şık sayısı

}Topic;

Topic createTopic(int id, char *topicName, char *topicOptions[], int optionLength);



#endif