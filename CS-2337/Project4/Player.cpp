#include "Player.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

Player::Player()
{
    this->name = "";
    this->team = "";
    this->H=0;
    this->O=0;
    this->K=0;
    this->W=0;
    this->P=0;
    this->S=0;
    this->E=0;
}

Player::Player(string name, string team)
{
    this->name = name;
    this->team = team;
    this->H=0;
    this->O=0;
    this->K=0;
    this->W=0;
    this->P=0;
    this->S=0;
    this->E=0;
}

double Player::getBattingAverage()
{
    if (this->getAtBats() == 0)
        return 0;
    double value = this->H / ((double)this->getAtBats());
    return round(value * 1000.0) / 1000.0;
}

double Player::getOnBasePercentage()
{
    if (this->getAppearances() == 0)
        return 0;
    double value = (this->H + this->W + this->P) / ((double)this->getAppearances());
    return round(value * 1000.0) / 1000.0;
}

int Player::getAtBats()
{
    return this->H + this->O + this->K + this->E;
}

int Player::getAppearances()
{
    return this->H + this->O + this->K + this->W + this->P + this->S + this->E;
}

void Player::toString()
{
    cout << fixed << setprecision(3);
    cout << name << "\t" << getAtBats() << "\t" << H << "\t" << W << "\t" << K << "\t" << P << "\t" << S << "\t" << getBattingAverage() << "\t" << getOnBasePercentage() << endl;
}
