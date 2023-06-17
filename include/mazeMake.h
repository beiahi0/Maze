#ifndef MazeMaking_H
#define MazeMaking_H

#include "maze.h"
#include <deque>
#include <random>

class Maze;

class MazeMaking : public Maze
{
    Q_OBJECT
public:
    MazeMaking(QObject *parent = nullptr);
    ~MazeMaking();
    void emptyMap();
    void setFlag();
    void mainRoadBend();
    void setBeginPosition(int &x, int &y);

    std::random_device rd;

private:
    void initMaze();
    inline void set_begin_point(int &seed_y, int &seed_x, std::deque<std::pair<int, int>> &re_load);
};

#endif // MazeMaking_H