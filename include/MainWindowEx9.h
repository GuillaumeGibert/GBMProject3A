#ifndef MAIN_WINDOW_EX9_H
#define MAIN_WINDOW_EX9_H

#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"


class MainWindowEx9: public MainWindow
{
    Q_OBJECT

    public:
        MainWindowEx9();
        virtual ~MainWindowEx9();

    signals:
        void searchBtServer();
        void quit();

private slots:
        void searchBtServerClicked();
        void quitInterface();

    private:
        QPushButton* m_pSearchBtServer;
        QPushButton* m_pQuit;

};

#endif
