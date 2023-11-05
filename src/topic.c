#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/topic.h"

Topic createTopic(int id, char *topicName, char *topicOptions[], int optionLength){
    Topic topic;
    topic.id = id;
    strcpy(topic.topicName , topicName);
    for (int i = 0; i < optionLength; i++) {
        strcpy(topic.topicOptions[i], topicOptions[i]);   
    }
    topic.optionLength = optionLength; 
    return topic;
}

Topic deleteTopic(int id){

}
