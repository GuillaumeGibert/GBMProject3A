#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QSignalMapper>

#include "TemporalSignalDisplay.h"

class MainWindow: public QWidget
{
    Q_OBJECT

    public:
        MainWindow();
        virtual ~MainWindow();

    public slots:
        void setSignalValues(std::vector<float> vSignalValues);
        void setFilteredSignalValues(std::vector<float> vFilteredSignalValues);

    private:
        TemporalSignalDisplay* m_pSignalDisplay;
        TemporalSignalDisplay* m_pFilteredSignalDisplay;
        QHBoxLayout* m_pMainLayout;

};

#endif
