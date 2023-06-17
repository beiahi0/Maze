#include "myThread.h"
#include "MazeSearch.h"
#include "mainwindow.h"
#include "maze.h"
#include "mazeMake.h"
#include <QDebug>
#include <QThread>
#include <queue>
#include <vector>

myThread::myThread(QObject *parent) : QObject(parent)
{
    M = new Maze();
    mazeMaking = new MazeMaking();
    mazeSearch = new MazeSearch();

    M->reset();
    mazeMaking->setFlag();
}

myThread::~myThread()
{
    delete M;
    delete mazeMaking;
    delete mazeSearch;
}
bool myThread::check()
{
    if (M->isMaking == true)
        return false;
    
    return true;
}