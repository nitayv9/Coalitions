#pragma once
#include "Offer.h"
#include <vector>
using std::vector;

class JoinPolicy
{
public:
    virtual Offer &join(vector<Coalition> coalitions, vector<Offer> &allOffers) = 0;
    virtual char kind() = 0;
    virtual ~JoinPolicy();
};

class MandatesJoinPolicy : public JoinPolicy
{
public:
    virtual Offer &join(vector<Coalition> coalitions, vector<Offer> &allOffers);
    virtual char kind();
    virtual ~MandatesJoinPolicy();
};

class LastOfferJoinPolicy : public JoinPolicy
{
public:
    virtual Offer &join(vector<Coalition> coalitions, vector<Offer> &allOffers);
    virtual char kind();
    virtual ~LastOfferJoinPolicy();
};