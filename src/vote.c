#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../header/vote.h"

Vote createVote(int id, Person voter, Topic topic, int topicOptionIndex){
    // Check if the user has already voted for this topic
    for (int i = 0; i < voteCount; i++) {
        if ((votes[i].topic.id == topic.id) && (votes[i].voter.id == voter.id)) {
            printf("You have already voted for this topic!\n");
            Vote emptyVote;
            emptyVote.id = -1; 
            return emptyVote;
        }
    }
    Vote vote;
    vote.id = id;
    vote.voter = voter;
    vote.topic = topic;
    vote.topicOptionIndex = topicOptionIndex;
    insertVote(vote);
    votes[voteCount] = vote;
    voteCount++;
    return vote;
}
