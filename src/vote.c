#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../header/vote.h"

Vote createVote(int id, Person voter, Topic topic, int topicOptionIndex){
    Vote vote;
    vote.id = id;
    vote.voter = voter;
    vote.topic = topic;
    vote.topicOptionIndex = topicOptionIndex;
    return vote;
}