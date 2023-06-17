#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>


class Maze;
class MazeSearch;
class MazeMaking;

class MainWindow;

class myThread : public QObject
{
    Q_OBJECT
public:
    myThread(QObject *parent = nullptr);
    ~myThread();
public:

    Maze *M;
    MazeMaking *mazeMaking;
    MazeSearch *mazeSearch;
    bool check();

signals:
    void sendMaze(QVector<QVector<int>> maze);

private:
};

#endif // MYTHREAD_H