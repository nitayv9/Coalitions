#pragma once
#include "Agent.h"
#include "Coalition.h"

class Offer
{
public:
    Offer(int coalitionId,int agentId);  
    int getOfferAgentId() const;
    int getOfferCoalitionId() const;

private:
    int oCoalitionId;
    int oAgentId;
};