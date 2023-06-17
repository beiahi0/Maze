#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAction>
#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QPainter>
#include <QThread>

#include <utility>

class myThread;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void startDfs(int x, int y);
    void startBfs();
    void startAStar();
    void makeMainRoadBendMap();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    // void resizeEvent(QResizeEvent *event);
    myThread *myth;
    
    QVector<QVector<int>> m_maze;

};

#endif // MAINWINDOW_H
