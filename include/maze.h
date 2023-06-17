#ifndef MAZE_H
#define MAZE_H

#define TIMEDELAY 25
#include <QObject>
#include <QVector>
#include <utility>

const std::pair<int, int> GROUND_Direction[4]{{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

class Maze : public QObject
{
    Q_OBJECT
public:
    Maze(QObject *parent = nullptr);
    ~Maze();
    void reset();
    static QVector<QVector<int>> maze;
    static std::pair<int, int> beginPos;
    static std::pair<int, int> endPos;
    static std::pair<int, int> cur;
    void setSize(int h, int w);
    void updateMaze(int m_sec);
    static bool isMaking;

signals:
    void sendMaze(QVector<QVector<int>> maze);

public:
    enum class MazeEleMents : int
    {
        GROUND = 0,
        WALL = 1,
        EXPLORED = 2,
        BEGIN = 3,
        END = 4,
        IMPOSSIBLE = 5,
        VISTED = 8
    };
};

#endif // MAZE_H