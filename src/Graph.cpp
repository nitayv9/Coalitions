#include "Graph.h"
#include "Offer.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

// our methods
void Graph::setPartyState(int partyId, int stateEnum)
{
    if (stateEnum == 0)
        mVertices[partyId].setState(Waiting);
    if (stateEnum == 1)
        mVertices[partyId].setState(CollectingOffers);
    if (stateEnum == 2)
        mVertices[partyId].setState(Joined);
}

vector<Party> &Graph::getmVertices()
{
    return mVertices;
}

void Graph::addOfferToParty(int coalId, int agentId, int pId)
{
    mVertices[pId].addOffer(coalId, agentId);
}

void Graph::startTimer(int partyId)
{
    mVertices[partyId].startTimer();
}

vector<Offer> Graph::getOffersByPartyId(int partyId)
{
    return mVertices[partyId].getOffers();
}