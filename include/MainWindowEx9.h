#ifndef MAIN_WINDOW_EX9_H
#define MAIN_WINDOW_EX9_H

#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
#include <QLabel>


class MainWindowEx9: public MainWindow
{
    Q_OBJECT

    public:
        MainWindowEx9();
        virtual ~MainWindowEx9();

    signals:
        void searchBtServer();

private slots:
        void searchBtServerClicked();

    private:
        QPushButton* m_pSearchBtServer;
        QPushButton* m_pQuit;
        QLabel* m_pLabel;

};

#endif
