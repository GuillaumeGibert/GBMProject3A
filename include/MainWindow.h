#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QSignalMapper>

#include "TemporalSignalDisplay.h"
#include "BufferedSignalDisplay.h"

class MainWindow: public QWidget
{
    Q_OBJECT

    public:
        MainWindow();
        virtual ~MainWindow();

    public slots:
        void setSignalValues(std::vector<float> vSignalValues);
        void setFilteredSignalValues(std::vector<float> vFilteredSignalValues);
        void setBufferedSignalValues(std::vector<std::deque<float>> vBufferedSignalValues);

    private:
        TemporalSignalDisplay* m_pSignalDisplay;
        TemporalSignalDisplay* m_pFilteredSignalDisplay;
        BufferedSignalDisplay* m_pBufferedSignalDisplay;
        QHBoxLayout* m_pMainLayout;

};

#endif
