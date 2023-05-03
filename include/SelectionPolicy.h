#pragma once
#include "Graph.h"

class SelectionPolicy
{
public:
    virtual int select(Graph graph, int partyId, int AgentCoalId) = 0;
    virtual char kind() = 0;
    virtual ~SelectionPolicy(); // Destructor
    bool inCoalitionsList(vector<int> listCoalitionsById, int coalId);
};

class MandatesSelectionPolicy : public SelectionPolicy
{
public:
    virtual int select(Graph graph, int partyId, int AgentCoalId);
    virtual char kind();
    virtual ~MandatesSelectionPolicy(); // Destructor
};

class EdgeWeightSelectionPolicy : public SelectionPolicy
{
public:
    virtual int select(Graph graph, int partyId, int AgentCoalId);
    virtual char kind();
    virtual ~EdgeWeightSelectionPolicy(); // Destructor
};