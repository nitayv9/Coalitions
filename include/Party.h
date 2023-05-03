#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class JoinPolicy;
class Simulation;
class Offer;
class Agent;
class Coalition;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *);
    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    int getPartyId() const;
    JoinPolicy &getJoinPolicy() const;
    void startTimer();
    void addOffer(int coal, int agentId);
    vector<Offer> &getOffers();
    char getJoinPolicyKind() const;
    vector<int> getOfferdCoalitionsIds() const;

    // Rule of 5:
    virtual ~Party();
    Party(const Party &other);
    Party &operator=(const Party &other);
    Party(Party &&other);
    Party &operator=(Party &&other);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    vector<Offer> mOffers;
    int mTimer;
};