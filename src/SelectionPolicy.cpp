#include "SelectionPolicy.h"
#include "Party.h"
#include "Graph.h"
#include "Offer.h"

SelectionPolicy::~SelectionPolicy() {}

// A function that checks if the list of coalitions contain coalId
bool SelectionPolicy::inCoalitionsList(vector<int> listCoalitionsById, int coalId)
{
    bool ans = false;
    for (unsigned int i = 0; i < listCoalitionsById.size(); i++)
    {
        if (listCoalitionsById[i] == coalId)
            ans = true;
    }
    return ans;
}

int EdgeWeightSelectionPolicy::select(Graph graph, int partyId, int AgentCoalId)
{
    int max = 0;
    int party = -1;
    for (int i = 0; i < graph.getNumVertices(); i++)
    {
        bool condition1 = graph.getEdgeWeight(partyId, i) != 0;
        bool condition2 = graph.getParty(i).getState() != Joined;
        bool condition3 = !inCoalitionsList(graph.getParty(i).getOfferdCoalitionsIds(), AgentCoalId);
        if (condition1 && condition2 && condition3)
        {
            if (graph.getEdgeWeight(partyId, i) > max)
            {
                max = graph.getEdgeWeight(partyId, i);
                party = i;
            }
        }
    }
    return party;
}

char EdgeWeightSelectionPolicy::kind() { return 'E'; }

EdgeWeightSelectionPolicy::~EdgeWeightSelectionPolicy() {}

int MandatesSelectionPolicy::select(Graph graph, int partyId, int AgentCoalId)
{
    int max = 0;
    int party = -1;
    for (int i = 0; i < graph.getNumVertices(); i++)
    {
        bool condition1 = graph.getEdgeWeight(partyId, i) != 0;
        bool condition2 = graph.getParty(i).getState() != Joined;
        bool condition3 = !inCoalitionsList(graph.getParty(i).getOfferdCoalitionsIds(), AgentCoalId);
        if (condition1 && condition2 && condition3)
        {
            if (graph.getParty(i).getMandates() > max)
            {
                max = graph.getParty(i).getMandates();
                party = i;
            }
        }
    }
    return party;
}

char MandatesSelectionPolicy::kind() { return 'M'; }

MandatesSelectionPolicy::~MandatesSelectionPolicy() {}