#include "Party.h"
#include "Offer.h"
#include "JoinPolicy.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include "Coalition.h"
#include <vector>
using std::vector;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mOffers(), mTimer(0)
{
    // You can change the implementation of the constructor, but not the signature!
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string &Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    // TODO: implement this method
    if (mState == CollectingOffers)
    {
        if (mTimer == 3)
        {
            Offer &acceptedOffer = mJoinPolicy->join(s.getCoalitionsVector(), mOffers);
            Coalition &acceptedCoal = s.getCoalitionsVector()[acceptedOffer.getOfferCoalitionId()];
            acceptedCoal.addParty(*this);
            if (acceptedCoal.getMembersCounter() > 60)
                s.setIs61();
            s.increaseJoinedCounter();
            setState(Joined);

            // clone the agent
            char kind = s.getAgents()[acceptedOffer.getOfferAgentId()].getSelectionPolicyKind();
            int new_id = s.getAgents().size();
            int new_party = getPartyId();
            SelectionPolicy *new_sp;
            if (kind == 'M')
                new_sp = new MandatesSelectionPolicy;
            if (kind == 'E')
                new_sp = new EdgeWeightSelectionPolicy;
            int coalId = acceptedOffer.getOfferCoalitionId();
            s.addNewAgent(new_id, new_party, new_sp, coalId);
        }
        mTimer++;
    }
}

int Party::getPartyId() const
{
    return mId;
}

JoinPolicy &Party::getJoinPolicy() const
{
    return *mJoinPolicy;
}

void Party::startTimer()
{
    mTimer = 1;
}

char Party::getJoinPolicyKind() const
{
    return mJoinPolicy->kind();
}

void Party::addOffer(int coalId, int agentId)
{
    mOffers.push_back(Offer(coalId, agentId));
}

vector<Offer> &Party::getOffers() { return mOffers; }

vector<int> Party::getOfferdCoalitionsIds() const
{
    vector<int> output;
    for (unsigned int j = 0; j < mOffers.size(); j++)
    {
        int num = mOffers[j].getOfferCoalitionId();
        output.push_back(num);
    }
    return output;
}

// Rule of 5:

// Destructor
Party::~Party()
{
    if (mJoinPolicy)
        delete mJoinPolicy;
}

// copy Constructor
Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(nullptr), mState(other.mState), mOffers(other.mOffers), mTimer(other.mTimer)
{
    if (other.getJoinPolicyKind() == 'M')
        mJoinPolicy = new MandatesJoinPolicy;
    if (other.getJoinPolicyKind() == 'L')
        mJoinPolicy = new LastOfferJoinPolicy;
}

// Assignment Operator
Party &Party::operator=(const Party &other)
{
    if (this != &other)
    {
        if (mJoinPolicy)
            delete mJoinPolicy;
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        if (other.getJoinPolicyKind() == 'M')
            mJoinPolicy = new MandatesJoinPolicy;
        if (other.getJoinPolicyKind() == 'L')
            mJoinPolicy = new LastOfferJoinPolicy;
        mState = other.mState;
        mOffers = other.mOffers;
        mTimer = other.mTimer;
    }
    return *this;
}

// Move Constructor
Party::Party(Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mOffers(other.mOffers), mTimer(other.mTimer)
{
    other.mJoinPolicy = nullptr;
}

Party &Party::operator=(Party &&other) // Move Assignment Operator
{
    if (mJoinPolicy)
        delete mJoinPolicy;
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mJoinPolicy = other.mJoinPolicy;
    mState = other.mState;
    mOffers = other.mOffers;
    mTimer = other.mTimer;
    other.mJoinPolicy = nullptr;
    return *this;
}