#pragma once

#include <vector>
#include "Party.h"
using std::vector;
class Party;

class Coalition
{
public:
    Coalition(int partyId, int cId, int partyMandates);
    void addParty(Party &party);
    int getMembersCounter();
    vector<int> getParties() const;
    int getCoalitionId() const;

private:
    int membersCounter;
    vector<int> parties;
    int cId;
};