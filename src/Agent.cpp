#include "Agent.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include "Party.h"
#include "Offer.h"
#include "JoinPolicy.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mCoalitionId(-1)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
    int party_to_offer_id = mSelectionPolicy->select(sim.getGraph(), mPartyId, getCoalitionId());
    if (party_to_offer_id != -1)
    {
        State state = sim.getParty(party_to_offer_id).getState();
        sim.addOfferToParty(getCoalitionId(), mAgentId, party_to_offer_id);
        if (state == Waiting)
        {
            sim.setPartyState(party_to_offer_id, 1);
            sim.startTimer(party_to_offer_id);
        }
    }
}

char Agent::getSelectionPolicyKind() const
{
    return mSelectionPolicy->kind();
}

int Agent::getCoalitionId() const
{
    return mCoalitionId;
}

void Agent::setCoalitionId(int id) { mCoalitionId = id; }

// Rule of 5 :

// Destructor
Agent::~Agent()
{
    if (mSelectionPolicy)
        delete mSelectionPolicy;
}

// copy Constructor
Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(nullptr), mCoalitionId(other.mCoalitionId)
{
    if (other.getSelectionPolicyKind() == 'M')
        mSelectionPolicy = new MandatesSelectionPolicy();
    if (other.getSelectionPolicyKind() == 'E')
        mSelectionPolicy = new EdgeWeightSelectionPolicy();
}

// copy assignment operator
Agent &Agent::operator=(const Agent &other)
{
    if (this != &other)
    {
        if (mSelectionPolicy)
            delete mSelectionPolicy;
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        if (other.getSelectionPolicyKind() == 'M')
            mSelectionPolicy = new MandatesSelectionPolicy();
        if (other.getSelectionPolicyKind() == 'E')
            mSelectionPolicy = new EdgeWeightSelectionPolicy();
        mCoalitionId = other.mCoalitionId;
    }
    return *this;
}

// Move Constructor
Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), mCoalitionId(other.mCoalitionId)
{
    other.mSelectionPolicy = nullptr;
}

// Move Assignment Operator
Agent &Agent::operator=(Agent &&other)
{

    if (mSelectionPolicy)
        delete mSelectionPolicy;
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
    mCoalitionId = mCoalitionId;
    return *this;
}