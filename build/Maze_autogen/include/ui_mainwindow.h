/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *emptyMap;
    QAction *dfs;
    QAction *bfs;
    QAction *MainRoadBendMap;
    QAction *setSize;
    QAction *aStar;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *Map_Making;
    QMenu *menusearch;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1094, 729);
        emptyMap = new QAction(MainWindow);
        emptyMap->setObjectName(QString::fromUtf8("emptyMap"));
        dfs = new QAction(MainWindow);
        dfs->setObjectName(QString::fromUtf8("dfs"));
        bfs = new QAction(MainWindow);
        bfs->setObjectName(QString::fromUtf8("bfs"));
        MainRoadBendMap = new QAction(MainWindow);
        MainRoadBendMap->setObjectName(QString::fromUtf8("MainRoadBendMap"));
        setSize = new QAction(MainWindow);
        setSize->setObjectName(QString::fromUtf8("setSize"));
        aStar = new QAction(MainWindow);
        aStar->setObjectName(QString::fromUtf8("aStar"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1094, 25));
        Map_Making = new QMenu(menubar);
        Map_Making->setObjectName(QString::fromUtf8("Map_Making"));
        menusearch = new QMenu(menubar);
        menusearch->setObjectName(QString::fromUtf8("menusearch"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(Map_Making->menuAction());
        menubar->addAction(menusearch->menuAction());
        Map_Making->addAction(emptyMap);
        Map_Making->addAction(MainRoadBendMap);
        Map_Making->addAction(setSize);
        menusearch->addAction(dfs);
        menusearch->addAction(bfs);
        menusearch->addAction(aStar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        emptyMap->setText(QApplication::translate("MainWindow", "\347\251\272\345\233\276", nullptr));
        dfs->setText(QApplication::translate("MainWindow", "Dfs", nullptr));
        bfs->setText(QApplication::translate("MainWindow", "Bfs", nullptr));
        MainRoadBendMap->setText(QApplication::translate("MainWindow", "\351\232\217\346\234\272\347\224\237\346\210\220\345\234\260\345\233\276", nullptr));
        setSize->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\345\244\247\345\260\217", nullptr));
        aStar->setText(QApplication::translate("MainWindow", "A-star", nullptr));
        Map_Making->setTitle(QApplication::translate("MainWindow", "\345\234\260\345\233\276", nullptr));
        menusearch->setTitle(QApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
