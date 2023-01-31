#include "Player.h"
#include <string>
#include <cmath>

using namespace std;

Player::Player(string name, int H, int O, int K, int W, int P, int S)
{
    this->name = name;
    this->H = H;
    this->O = O;
    this->K = K;
    this->W = W;
    this->P = P;
    this->S = S;
}

double Player::getBattingAverage()
{
    if (this->getAtBats() == 0) return 0;
    double value = this->H / ((double)this->getAtBats());
    return round( value * 1000.0 ) / 1000.0;
}

double Player::getOnBasePercentage()
{
    if (this->getAppearances() == 0) return 0;
    double value = (this->H + this->W + this->P) / ((double) this->getAppearances());
    return round( value * 1000.0 ) / 1000.0;
}

int Player::getAtBats()
{
    return this->H + this->O + this->K;
}

int Player::getAppearances()
{
    return this->H + this->O + this->K + this->W + this->P + this->S;
}
