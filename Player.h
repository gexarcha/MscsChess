#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:

    virtual void Init(std::string fenString) = 0;
    virtual void DoMove(std::string canString) = 0;
    virtual std::string NextMove() = 0;
    virtual bool IsGameOver() = 0;
    virtual std::string Result() = 0;

protected:
    std::string result;
};

#endif

