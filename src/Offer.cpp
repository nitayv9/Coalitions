#include "Offer.h"
#include "Coalition.h"
#include "Agent.h"

Offer::Offer(int coalitionId, int agentId) : oCoalitionId(coalitionId), oAgentId(agentId) {}

int Offer::getOfferAgentId() const { return oAgentId; }

int Offer::getOfferCoalitionId() const
{
    return oCoalitionId;
}