#include "JoinPolicy.h"
#include "Offer.h"

JoinPolicy::~JoinPolicy() {}

Offer &MandatesJoinPolicy::join(vector<Coalition> coalitions, vector<Offer> &allOffers)
{
    int max = coalitions[allOffers[0].getOfferCoalitionId()].getMembersCounter();
    int indexOfMaxOffer = 0;
    for (int i = 0; i < (int)allOffers.size(); i++)
    {
        Offer &currOffer = allOffers[i];
        if (coalitions[currOffer.getOfferCoalitionId()].getMembersCounter() > max)
        {
            max = coalitions[currOffer.getOfferCoalitionId()].getMembersCounter();
            indexOfMaxOffer = i;
        }
    }
    return allOffers[indexOfMaxOffer];
}

char MandatesJoinPolicy::kind()
{
    return 'M';
}

MandatesJoinPolicy::~MandatesJoinPolicy() {}

Offer &LastOfferJoinPolicy::join(vector<Coalition> coalitions, vector<Offer> &allOffers)
{
    return allOffers[allOffers.size() - 1];
}

char LastOfferJoinPolicy::kind()
{
    return 'L';
}

LastOfferJoinPolicy::~LastOfferJoinPolicy() {}