#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player
{
public:
    std::string name;
    std::string team;
    int H; // hits
    int O; // outs
    int K; // strikeouts
    int W; // walks
    int P; // hit by pitches
    int S; // sacrifices
    int E; // errors

    Player();
    Player(std::string name, std::string team);

    int getAtBats();
    int getAppearances();
    double getBattingAverage();
    double getOnBasePercentage();
    void toString();
};

#endif
