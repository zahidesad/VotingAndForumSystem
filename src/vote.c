#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../header/vote.h"
#include "../Colors/color.h"

Vote createVote(int id, Person voter, Topic topic, int topicOptionIndex)
{
    // Check if the user has already voted for this topic
    for (int i = 0; i < voteCount; i++)
    {
        if ((votes[i].topic.id == topic.id) && (votes[i].voter.id == voter.id))
        {
            Color_Red();
            printf("\nYou have already voted for this topic!\n");
            Color_Reset();
            Vote emptyVote;
            emptyVote.id = -1;
            return emptyVote;
        }
    }
    if (topicOptionIndex >= 0 && topicOptionIndex <= topic.optionLength-1)
    {
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
    else
    {
        Color_Red();
        printf("\nPlease write valid input!\n");
        Color_Reset();
    }
}
