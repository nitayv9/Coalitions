#include "Simulation.h"
#include <vector>
using std::vector;
#include "Offer.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), joinedPartiesCounter(0), coalitions(vector<Coalition>()), is61(false)
{
    // You can change the implementation of the constructor, but not the signature!
    int coalId = 0;
    for (Agent &curr : mAgents)
    {
        int currId = curr.getPartyId();
        mGraph.setPartyState(currId, 2);
        joinedPartiesCounter++;
        Coalition c(graph.getParty(currId).getPartyId(), coalId, graph.getParty(currId).getMandates());
        coalitions.push_back(c);
        curr.setCoalitionId(coalId);
        coalId++;
    }
}

void Simulation::step()
{
    // TODO: implement this method
    for (Party &currParty : mGraph.getmVertices())
    {
        currParty.step(*this);
    }

    for (Agent &currAgent : mAgents)
    {
        currAgent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    // TODO implement this method
    if (is61 || joinedPartiesCounter == mGraph.getNumVertices())
        return true;
    else
        return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read thefor documentation above.
    vector<vector<int>> output;
    for (const Coalition &currCoalition : coalitions)
    {
        vector<int> currCoalVector;
        vector<int> partiesOfCurrCoalition = currCoalition.getParties();
        for(unsigned int i = 0; i < partiesOfCurrCoalition.size(); i++)
        {
            currCoalVector.push_back(partiesOfCurrCoalition[i]);
        }
        output.push_back(currCoalVector);
    }
    return output;
}

    // our methods

void Simulation::addNewAgent(int newId, int newParty, SelectionPolicy *new_sp, int coalId)
{
    Agent clonedAgent(newId, newParty, new_sp);
    clonedAgent.setCoalitionId(coalId);
    mAgents.push_back(clonedAgent);
}

vector<Coalition> &Simulation::getCoalitionsVector()
{
    return coalitions;
}

void Simulation::setIs61()
{
    is61 = true;
}

void Simulation::increaseJoinedCounter()
{
    joinedPartiesCounter++;
}

void Simulation::addOfferToParty(int coalId, int agentId, int pId)
{
    mGraph.addOfferToParty(coalId, agentId, pId);
}

void Simulation::setPartyState(int partyId, int stateEnum)
{
    mGraph.setPartyState(partyId, stateEnum);
}

void Simulation::startTimer(int partyId)
{
    mGraph.startTimer(partyId);
}