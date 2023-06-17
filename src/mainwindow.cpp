#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "maze.h"
#include "myThread.h"
#include <QDebug>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include "mazeMake.h"
#include <QMessageBox>
#include "mazeSearch.h"
#include <QFormLayout>
#include <QInputDialog>
#include <QColorDialog>

class Maze;
class MazeSearch;
extern int MAZE_HEIGHT;
extern int MAZE_WIDTH;
extern int GRID_SIZE;

#define SIDE 22.5

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (int x = 0; x <= MAZE_HEIGHT; ++x)
        for (int y = 0; y <= MAZE_WIDTH; ++y)
        {
            {
                switch (m_maze[x][y])
                {
                case 0: // GROUND
                    painter.fillRect(y * GRID_SIZE, x * GRID_SIZE + SIDE, GRID_SIZE, GRID_SIZE, QColor(qRgb(255, 255, 255)));
                    break;
                case 1: // WALL
                    painter.fillRect(y * GRID_SIZE, x * GRID_SIZE + SIDE, GRID_SIZE, GRID_SIZE, QColor(qRgb(136, 74, 57)));
                    break;
                case 2: // EXPLORED
                    painter.fillRect(y * GRID_SIZE, x * GRID_SIZE + SIDE, GRID_SIZE, GRID_SIZE, QColor(qRgb(255, 194, 111)));
                    break;
                case 3: // BEGIN
                    painter.fillRect(y * GRID_SIZE, x * GRID_SIZE + SIDE, GRID_SIZE, GRID_SIZE, QColor(qRgb(155, 171, 184)));
                    break;
                case 4: // END
                    painter.fillRect(y * GRID_SIZE, x * GRID_SIZE + SIDE, GRID_SIZE, GRID_SIZE, QColor(qRgb(215, 192, 174)));
                // case 5: // IMPOSSIBLE
                //     painter.fillRect(y * GRID_SIZE, x * GRID_SIZE + SIDE, GRID_SIZE, GRID_SIZE, QColor(qRgb(21, 29, 41)));
                //     break;
                default: break;
                }

                painter.fillRect(myth->M->beginPos.second * GRID_SIZE + 1, myth->M->beginPos.first * GRID_SIZE + SIDE + 1, GRID_SIZE - 1, GRID_SIZE - 1, QColor(qRgb(58, 79, 122)));
                painter.fillRect(myth->M->endPos.second * GRID_SIZE + 1, myth->M->endPos.first * GRID_SIZE + SIDE + 1, GRID_SIZE - 1, GRID_SIZE - 1, QColor(qRgb(231, 70, 70)));
                painter.fillRect(myth->M->cur.second * GRID_SIZE + 1, myth->M->cur.first * GRID_SIZE + SIDE + 1, GRID_SIZE - 1, GRID_SIZE - 1, QColor(qRgb(76, 128, 69)));

            }
            painter.drawRect(y * GRID_SIZE, x * GRID_SIZE + SIDE, GRID_SIZE, GRID_SIZE);
        }
} 

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);

    qRegisterMetaType<QVector<QVector<int>>>("QVector");

    QThread *sub = new QThread;
    QThread *sub2 = new QThread;

    myth = new myThread;

    auto &M = myth->M;
    auto &mazeSearch = myth->mazeSearch;
    auto &mazeMaking = myth->mazeMaking;

    
    myth->moveToThread(sub);
    M->moveToThread(sub);
    mazeSearch ->moveToThread(sub);
    mazeMaking ->moveToThread(sub);

    m_maze = myth->M->maze;


    this->setWindowTitle("Maze");
    this->setFixedSize(GRID_SIZE * (MAZE_WIDTH + 1) + 3, GRID_SIZE *  (MAZE_HEIGHT + 1) + 25);


    connect(mazeMaking, &Maze::sendMaze, this,  [=](QVector<QVector<int>> maze)
    {
        m_maze = maze;
        this->update();
    });


    connect(mazeSearch, &Maze::sendMaze, this,  [=](QVector<QVector<int>> maze)
    {
        m_maze = maze;
        this->update();
    });

    connect(M, &Maze::sendMaze, this,  [=](QVector<QVector<int>> maze)
    {
        m_maze = maze;
        this->update();
    });


    // -------------------------------Making Map--------------------------------------

    connect(ui->emptyMap, &QAction::triggered, this, [=]()
    {
        if (myth->check() == false)
            return;
        if (sub->isRunning())
            sub->terminate();
        M->reset();
        // qDebug() << "emptyMap is running";
        myth->mazeMaking->setFlag();
        m_maze = myth->M->maze;
        M->updateMaze(TIMEDELAY);
    });

    // -------------------- make Main Road Map------------------------------


    connect(this, &MainWindow::makeMainRoadBendMap, mazeMaking, &MazeMaking::mainRoadBend);
    connect(ui->MainRoadBendMap, &QAction::triggered, this, [=]()
    {
        if (sub->isRunning())
            sub->terminate();
        emit makeMainRoadBendMap();
        M->reset();
        qDebug() << "sub is running";
        sub->start();
    });

    // ---------------  search --------------------------
    
    // ------------------------ dfs -----------------------------
    connect(this, &MainWindow::startDfs, mazeSearch, &MazeSearch::dfs);

    connect(ui->dfs, &QAction::triggered, this, [=]()
    {
        if (myth->check() == false)
            return;
        if (sub->isRunning())
        {
            qDebug() << "sub is running when dfs start";
            sub->terminate();
        }
        int x = M->beginPos.first, y = M->beginPos.second;
        qDebug() << "dfs is working";
        M->reset();
        emit startDfs(x, y);

        myth->mazeMaking->setFlag();
        sub->start();
    });


    // -------------------------- bfs ---------------------------------

    connect(this, &MainWindow::startBfs, mazeSearch, &MazeSearch::bfs);

    connect(ui->bfs, &QAction::triggered, this, [=]()
    {
        if (myth->check() == false)
            return;
        
        if (sub->isRunning())
        {
            sub->terminate();
        }
        M->reset();
        mazeMaking->setFlag();
        qDebug() << "bfs is working";

        emit startBfs();
        sub->start();
    });


    // -----------------------   Astar ---------------------------------
    connect(this, &MainWindow::startAStar, mazeSearch, &MazeSearch::aStar);

    connect(ui->aStar, &QAction::triggered, this, [=]()
    {
        if (myth->check() == false)
            return;
        
        if (sub->isRunning())
            sub->terminate();
        M->reset();
        mazeMaking->setFlag();
        qDebug() << "astar is working";

        emit startAStar();
        sub->start();
    });



    connect(ui->setSize, &QAction::triggered, this, [=]
    {
        if (myth->check() == false)
            return;
        QDialog dialog(this);
        QFormLayout form(&dialog);
        form.addRow(new QLabel("User input:"));
        form.addRow(new QLabel("行和列请设置为奇数"));
        // mazeHeight

        QString heigh, width;
        QString value1 = QString("mazeHeight: ");
        QSpinBox *spinbox1 = new QSpinBox(&dialog);
        form.addRow(value1, spinbox1);
        // mazeWeight
        QString value2 = QString("mazeWidth: ");
        QSpinBox *spinbox2 = new QSpinBox(&dialog);
        form.addRow(value2, spinbox2);
        // Add Cancel and OK button
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
            Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
        // Process when OK button is clicked
    
        spinbox1->setValue(MAZE_HEIGHT + 1);
        spinbox2->setValue(MAZE_WIDTH + 1);

        
        if (dialog.exec() == QDialog::Accepted) {

            int h = spinbox1->value();
            int w = spinbox2->value();

            if (h % 2 == 0 || w % 2 == 0 ||  h > 33 || w > 50 || h <= 2 || w <= 2)
            {
                int ret3 = QMessageBox::warning(this, tr("警告对话框"),tr("请输入合法的长和宽, 长最大33， 宽最大49"), QMessageBox::Abort);
                if(ret3 == QMessageBox::Abort)
                {
                    qDebug() << tr("提示");
                }
                return;
            }
            M->setSize(h, w);
            mazeMaking->setFlag();
            qDebug() << h << ' ' << w;
            qDebug() << MAZE_HEIGHT << ' ' << MAZE_WIDTH;
            
            mazeMaking->emptyMap();
            m_maze = M->maze;
            this->setFixedSize(GRID_SIZE * (MAZE_WIDTH + 1) + 1, GRID_SIZE *  (MAZE_HEIGHT + 1) + 25);
        }
    });

    int w = this->width();

    // -------------------------- destroy -----------------------------
    connect(this, &MainWindow::destroyed, this, [=]() {
        sub->quit();
        sub->wait();

        M->deleteLater();
        myth->deleteLater();
        mazeMaking->deleteLater();
        mazeSearch->deleteLater();

        myth->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myth;
}


// void MainWindow::resizeEvent(QResizeEvent *event)
// {
//     int w = this->width();
//     int h = this->height();

//     // this->setFixedSize(GRID_SIZE * (MAZE_WIDTH + 1) + 1, GRID_SIZE *  (MAZE_HEIGHT + 1) + 25);
//     qDebug() << "resizeEvent is running";
// }

