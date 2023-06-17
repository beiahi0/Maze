#ifndef MAZE_SOLVING_H
#define MAZE_SOLVING_H

#include "maze.h"
#include <QObject>

#include <utility>

class Maze;

class MazeSearch : public Maze
{

    Q_OBJECT

public:
    MazeSearch( QObject *parent = nullptr);
    ~MazeSearch();
    inline bool is_in_maze(const int &y, const int &x);
    inline int pow_two_norm(const int &y, const int &x);
    bool dfs(const int x, const int y);
    void bfs();
    void aStar();

};

#endif // MAZE_SOLVING_H