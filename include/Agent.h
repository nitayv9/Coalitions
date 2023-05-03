#pragma once
#include <vector>
#include "Graph.h"
#include "Coalition.h"

class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    char getSelectionPolicyKind() const;
    int getCoalitionId() const;
    void setCoalitionId(int id);

    // Rule of 5 :
    virtual ~Agent();
    Agent(const Agent &other);
    Agent &operator=(const Agent &other);
    Agent(Agent &&other);
    Agent &operator=(Agent &&other);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mCoalitionId;
};