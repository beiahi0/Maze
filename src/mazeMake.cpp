#include "mazeMake.h"
#include "mainwindow.h"
#include "maze.h"

#include <QThread>
#include <algorithm>
#include <chrono>
#include <deque>
#include <functional>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;

extern int MAZE_HEIGHT;
extern int MAZE_WIDTH;
MazeMaking::MazeMaking(QObject *parent) : Maze(parent) {}

MazeMaking::~MazeMaking() {}

void MazeMaking::setFlag()
{
    maze[beginPos.first][beginPos.second] = int(MazeEleMents::BEGIN);
    maze[endPos.first][endPos.second] = int(MazeEleMents::END);

    cur.first = -1, cur.second = -1;
    qDebug() << "is set Flag";
    updateMaze(TIMEDELAY);
}


void MazeMaking::emptyMap()
{
    for (int i = 0; i <= MAZE_HEIGHT; i++)
        for (int j = 0; j <= MAZE_WIDTH; ++j)
        {
            maze[i][j] = int(MazeEleMents::GROUND);
        }

    sendMaze(maze);
    // animator->update(1);
} // end emptyMap()

void MazeMaking::initMaze()
{
    for (int i = 0; i <= MAZE_HEIGHT; i++)
        for (int j = 0; j <= MAZE_WIDTH; j++)
        {
            if (i == 0 || j == 0 || i == MAZE_HEIGHT || j == MAZE_WIDTH)
            {
                maze[i][j] = (int)MazeEleMents::WALL;
                continue;
            }
            else if (i % 2 == 0)
            {
                maze[i][j] = (int)MazeEleMents::WALL;
                continue;
            }
            else if (j % 2 == 1)
                maze[i][j] = (int)MazeEleMents::GROUND;
            else
                maze[i][j] = (int)MazeEleMents::WALL;
        }
}

void MazeMaking::mainRoadBend()
{
    isMaking = true;
    qDebug() << "isMakign: in making maze" << isMaking;
    initMaze();

    int sx = beginPos.first, sy = beginPos.second;

    std::mt19937 myrand(rd());
    setBeginPosition(sx, sy);

    updateMaze(TIMEDELAY);
    qDebug() << "making map";


    function<void(int, int)> dfs = [&](int x, int y)
    {
        vector<int> v = {0, 1, 2, 3};

        shuffle(v.begin(), v.end(), myrand);
        shuffle(v.begin(), v.end(), myrand);

        for (int j = 0; j < 4; j++)
        {
            int i = v[j];

            int a1 = x + dx[i], b1 = y + dy[i];
            int a = x + dx[i] * 2, b = y + dy[i] * 2;
            // qDebug() << a << ' ' << b << ' ' << a1 << ' ' << b1;
            if (a < 0 || a >= MAZE_HEIGHT || b < 0 || b >= MAZE_WIDTH)
                continue;
            // if (a1 < 0 || a1 >= MAZE_HEIGHT || b1 < 0 || b1 >= MAZE_WIDTH)
            //     continue;
            if (maze[a][b] != (int)MazeEleMents::GROUND)
                continue;

            if (maze[a][b] == (int)MazeEleMents::VISTED)
                continue;
            if (maze[a1][b1] == (int)MazeEleMents::VISTED)
                continue;
            maze[a][b] = maze[a1][b1] = (int)MazeEleMents::VISTED;
            updateMaze(5);

            dfs(a, b);
        }
    };
    dfs(sx, sy);

    qDebug() << "dfs making is over";

    for (int i = 0; i < MAZE_HEIGHT; i++)
    {
        for (int j = 0; j < MAZE_WIDTH; j++)
        {
            if (maze[i][j] == (int)MazeEleMents::VISTED)
            {
                maze[i][j] = (int)MazeEleMents::GROUND;
            }
        }
        updateMaze(1);
    }
    qDebug() << "mazeMaking over";
    
    isMaking = false;

    qDebug() << "isMakign: in making maze" << isMaking;
}
void MazeMaking::setBeginPosition(int &sx, int &sy)
{
    mt19937 rng(rd());

    uniform_int_distribution<int> xPos(1, MAZE_HEIGHT - 1);
    uniform_int_distribution<int> yPos(1, MAZE_WIDTH - 1);
    int x, y;
    while (1)
    {
        x = xPos(rng);
        y = yPos(rng);
        if (x % 2 == 1 && y % 2 == 1)
        {
            sx = x, sy = y;
            break;
        }
    }
}