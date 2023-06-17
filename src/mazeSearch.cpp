#include "mazeSearch.h"
#include "mainwindow.h"

#include <QThread>

#include <iostream>
#include <math.h>
#include <queue>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, PII>> PIIII;

extern int MAZE_HEIGHT;
extern int MAZE_WIDTH;
MazeSearch::MazeSearch(QObject *A) : Maze(A)
{
}

MazeSearch::~MazeSearch()
{
}

bool MazeSearch::dfs(const int x, const int y)
{
    maze[x][y] = int(MazeEleMents::EXPLORED);
    cur.first = x, cur.second = y;
    updateMaze(TIMEDELAY);
    if (x == endPos.first && y == endPos.second)
    {
        maze[x][y] = int(MazeEleMents::END);
        cur.first = -1, cur.second = -1;
        updateMaze(TIMEDELAY);
        return true;
    }
    for (int i = 0; i < 4; i++)
    {
        int a = x + dx[i], b = y + dy[i];

        if (a < 0 || a > MAZE_HEIGHT || b < 0 || b > MAZE_WIDTH)
            continue;
        if (maze[a][b] == (int)MazeEleMents::EXPLORED)
            continue;
        if (maze[a][b] == (int)MazeEleMents::WALL)
            continue;
        if (dfs(a, b))
        {
            return true;
        }
    }
    maze[x][y] = (int)MazeEleMents::GROUND;
    return false;
} // end MazeSearch::dfs

void MazeSearch::bfs()
{
    std::queue<std::pair<int, int>> q;

    cur = beginPos;
    q.push({cur});

    vector<vector<pair<int, int>>> path(MAZE_HEIGHT + 10, vector<pair<int, int>>(MAZE_WIDTH + 10));

    qDebug() << "bfs is working";

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        int x = t.first, y = t.second;
        if (maze[x][y] == (int)MazeEleMents::EXPLORED)
            continue;
        maze[x][y] = (int)MazeEleMents::EXPLORED;
        cur = {x, y};

        if (x == endPos.first && y == endPos.second)
        {
            maze[x][y] = int(MazeEleMents::END);
            cur.first = -1, cur.second = -1;
            qDebug() << "bfs find the end";
            updateMaze(TIMEDELAY);
            break;
        }
        updateMaze(TIMEDELAY);

        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a > MAZE_HEIGHT || b < 0 || b > MAZE_WIDTH)
                continue;

            if (maze[a][b] == (int)MazeEleMents::EXPLORED)
                continue;
            if (maze[a][b] == (int)MazeEleMents::WALL)
                continue;
            path[a][b] = {x, y};
            q.push({a, b});
        }
    }
    cur = endPos;
    updateMaze(TIMEDELAY);

    reset();
    updateMaze(TIMEDELAY);

    PII begin = endPos;

    qDebug() << "bfs path ";
    while (begin != beginPos)
    {
        int x = begin.first, y = begin.second;
        maze[x][y] = (int)MazeEleMents::EXPLORED;
        updateMaze(1);
        begin = path[x][y];
    }
}

void MazeSearch::aStar()
{
    vector<vector<int>> dis(MAZE_HEIGHT + 10, vector<int>(MAZE_WIDTH + 10));
    vector<vector<pair<int, int>>> path(MAZE_HEIGHT + 10, vector<pair<int, int>>(MAZE_WIDTH + 10));

    for (int i = 0; i < dis.size(); i++)
        for (int j = 0; j < dis[i].size(); j++)
            dis[i][j] = -1;

    auto dijkstra = [&]()
    {
        queue<PII> q;
        q.push({endPos});
        dis[endPos.first][endPos.second] = 0;

        while (q.size())
        {
            auto t = q.front();
            q.pop();

            int x = t.first, y = t.second;

            for (int i = 0; i < 4; i++)
            {
                int a = x + dx[i], b = y + dy[i];
                if (a < 0 || a > MAZE_HEIGHT || b < 0 || b > MAZE_WIDTH)
                    continue;
                if (maze[a][b] == (int)MazeEleMents::WALL)
                    continue;
                if (dis[a][b] != -1)
                    continue;
                dis[a][b] = dis[x][y] + 1;
                q.push({a, b});
            }
        }
    };

    dijkstra();

    struct Node
    {
        int distance1, distance2;
        int x, y;
        bool operator<(const Node &N) const
        {
            return N.distance1 < distance1;
        }
    };

    priority_queue<Node> heap;

    int sx = beginPos.first, sy = beginPos.second;
    heap.push({dis[sx][sy], 0, sx, sy});

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int x = t.x, y = t.y, distance = t.distance1;

        if (maze[x][y] == (int)MazeEleMents::EXPLORED)
            continue;
        maze[x][y] = (int)MazeEleMents::EXPLORED;
        cur = {x, y};

        updateMaze(TIMEDELAY);

        if (endPos == (PII){x, y})
        {
            maze[x][y] = int(MazeEleMents::END);
            cur.first = -1, cur.second = -1;
            qDebug() << "bfs find the end";
            updateMaze(TIMEDELAY);

            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a > MAZE_HEIGHT || b < 0 || b > MAZE_WIDTH)
                continue;

            if (maze[a][b] == (int)MazeEleMents::EXPLORED)
                continue;
            if (maze[a][b] == (int)MazeEleMents::WALL)
                continue;
            path[a][b] = {x, y};
            heap.push({distance + dis[a][b] + 1, distance + 1, a, b});
        }
    }

    cur = endPos;
    updateMaze(TIMEDELAY);

    reset();
    updateMaze(TIMEDELAY);

    PII begin = endPos;

    qDebug() << "bfs path ";
    while (begin != beginPos)
    {
        int x = begin.first, y = begin.second;
        maze[x][y] = (int)MazeEleMents::EXPLORED;
        updateMaze(1);
        begin = path[x][y];
    }
}