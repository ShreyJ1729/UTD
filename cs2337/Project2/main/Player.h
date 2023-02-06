#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player
{
public:
    string name;
    int H;
    int O;
    int K;
    int W;
    int P;
    int S;

    Player(string name, int H, int O, int K, int W, int P, int S);

    int getAtBats();
    int getAppearances();
    double getBattingAverage();
    double getOnBasePercentage();
};

#endif
