#ifndef MAIN_WINDOW_EX7_H
#define MAIN_WINDOW_EX7_H

#include <QPushButton>

#include "MainWindow.h"

class MainWindowEx7: public MainWindow
{
    Q_OBJECT

    public:
        MainWindowEx7();
        virtual ~MainWindowEx7();
    
    public slots:
	void setStartButton();
	void setStopButton();
	
    
    signals:
    void sigSendButtonPressed(const QByteArray);
	    
    private:
	QPushButton* m_pStartButton;
	QPushButton* m_pStopButton;

};

#endif
