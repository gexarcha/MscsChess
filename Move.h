#ifndef MOVE_H
#define MOVE_H

class Move {
public:
    Move(int from, int to) : from(from), to(to) {}
    int From() const { return from; }
    int To() const { return to; }
private:
    int from;
    int to;
};

#endif

