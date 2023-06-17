#include "maze.h"
#include "mainwindow.h"
#include <QVector>
#include <iostream>

QVector<QVector<int>> Maze::maze = {{}};

int MAZE_HEIGHT;
int MAZE_WIDTH;
std::pair<int, int> Maze::beginPos = {1, 1};
std::pair<int, int> Maze::endPos = {MAZE_HEIGHT - 2, MAZE_WIDTH - 2};
std::pair<int, int> Maze::cur = {1, 1};
bool Maze::isMaking = false;
int GRID_SIZE = 30;


Maze::Maze(QObject *parent) : QObject(parent)
{
    MAZE_HEIGHT = 20;
    MAZE_WIDTH = 20;
    beginPos = {1, 0};
    endPos = {MAZE_HEIGHT, MAZE_WIDTH - 1};

    cur = {-1, -1};
    maze.resize(MAZE_HEIGHT + 1);
    for (int i = 0; i <= MAZE_HEIGHT; ++i)
        maze[i].resize(MAZE_WIDTH + 1);
}

Maze::~Maze() {}

void Maze::reset()
{
    cur = {-1, -1};
    for (int i = 0; i <= MAZE_HEIGHT; ++i)
        for (int j = 0; j <= MAZE_WIDTH; ++j)
            if (maze[i][j] != int(MazeEleMents::WALL))
                maze[i][j] = 0;
    updateMaze(TIMEDELAY);
}

void Maze::setSize(int h, int w)
{
    MAZE_HEIGHT = h - 1;
    MAZE_WIDTH = w - 1;

    beginPos = {1, 0};
    endPos = {MAZE_HEIGHT, MAZE_WIDTH - 1};

    qDebug() << h << ' ' << w;
    

    maze.resize(MAZE_HEIGHT + 1);
    for (int i = 0; i <= MAZE_HEIGHT; ++i)
        maze[i].resize(MAZE_WIDTH + 1);
    
    reset();
    updateMaze(TIMEDELAY);
}
void Maze::updateMaze(int mSec)
{
    sendMaze(maze);
    QThread::msleep(mSec);
}