#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);
    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;

    // We add from here :
    void addNewAgent(int newId, int newParty, SelectionPolicy *new_sp, int coalId);
    vector<Coalition> &getCoalitionsVector();
    void setIs61();
    void increaseJoinedCounter();
    void addOfferToParty(int coalId, int agentId, int pId);
    void setPartyState(int partyId, int stateEnum);
    void startTimer(int partyId);

private:
    Graph mGraph;
    vector<Agent> mAgents;

    int joinedPartiesCounter;
    vector<Coalition> coalitions;
    bool is61;
};