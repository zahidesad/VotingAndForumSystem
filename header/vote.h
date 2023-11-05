#ifndef VOTE_H
#define VOTE_H
#include "../header/person.h"
#include "../header/topic.h"

typedef struct Vote
{
    int id;
    Person voter;    
    Topic topic;
    int topicOptionIndex;  //kaçıncı şıkka oy verdi
}Vote;

Vote createVote(int id, Person voter, Topic topic, int topicOptionIndex);

#endif