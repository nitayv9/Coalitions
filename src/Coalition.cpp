#include "Coalition.h"
#include "Party.h"
#include <vector>
using std::vector;

Coalition::Coalition(int partyId, int cId, int partyMandate) : membersCounter(partyMandate), parties(vector<int>()), cId(cId)
{
    parties.push_back(partyId);
}

void Coalition::addParty(Party &party)
{
    parties.push_back(party.getPartyId());
    membersCounter = membersCounter + party.getMandates();
}

int Coalition::getMembersCounter()
{
    return membersCounter;
}

vector<int> Coalition::getParties() const
{
    return parties;
}

int Coalition::getCoalitionId() const
{
    return cId;
}