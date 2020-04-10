#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
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
        void setSignalValues(float, std::vector<float> vSignalValues);
        void setFilteredSignalValues(std::vector<float> vFilteredSignalValues);
        void setBufferedSignalValues(std::vector<std::deque<float>> vBufferedSignalValues);
        void setPowerSpectrumValues(std::vector<std::deque<float>> vPowerSpectrumValues);

    protected:
        TemporalSignalDisplay* m_pSignalDisplay;
        TemporalSignalDisplay* m_pFilteredSignalDisplay;
        BufferedSignalDisplay* m_pBufferedSignalDisplay;
        BufferedSignalDisplay* m_pPowerSpectrumDisplay;
        QHBoxLayout* m_pMainLayout;
        QHBoxLayout* m_pSignalLayout;
        QVBoxLayout* m_pMainVLayout;

};

#endif
