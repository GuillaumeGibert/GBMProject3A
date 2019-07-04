#ifndef MAIN_WINDOW_EX8_H
#define MAIN_WINDOW_EX8_H

#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>


#include "MainWindow.h"

class MainWindowEx8: public MainWindow
{
    Q_OBJECT

    public:
        MainWindowEx8();
        virtual ~MainWindowEx8();
    
    public slots:
        void setSearchButton();
        void setSearchInfos(QString, QString, int, float, float);
        void eraseSearchInfos();
        void addPatient();
        void removePatient();
    
    signals:
        void sigBroadcastSearchField(QString);
        void sigBroadcastAddPatient(QString, QString, int, float, float);
        void sigBroadcastRemovePatient(QString);
	    
    private:
        QPushButton* m_pbSEARCH;
        QLineEdit* m_leSearchField;

        QPushButton* m_pbADD;
        QPushButton* m_pbREMOVE;
        QPushButton* m_pbRESET;

        QFormLayout* m_formLayout;
        QLineEdit* m_leName;
        QLineEdit* m_leFirstName;
        QLineEdit* m_leAge;
        QIntValidator* m_ivAgeValidator;
        QLineEdit* m_leSize;
        QDoubleValidator* m_dvSizeValidator;
        QLineEdit* m_leWeight;
        QDoubleValidator* m_dvWeightValidator;

        QVBoxLayout* m_vblRightSide;
        QVBoxLayout* m_vblLeftSide;

};

#endif
