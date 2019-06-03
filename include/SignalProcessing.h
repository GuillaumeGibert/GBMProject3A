#ifndef SIGNALPROCESSING_H
#define SIGNALPROCESSING_H

#include <QObject>
#include <QDebug>
#include "TemporalFilter.h"
#include <deque>

#define NBSIGNALS 5

class SignalProcessing : public QObject
{
    Q_OBJECT

public:
    SignalProcessing();
    ~SignalProcessing();

public:
    void setNbSignals(int);

public slots:
    void setInputData(std::vector<float>);

signals:
    void sigBroadcastFilteredValues(std::vector<float>);
    void sigBroadcastBufferedValues(std::vector<std::deque<float>>);

private:
    TemporalFilter* m_pFilter;
    std::vector<std::deque<float>> m_vBufferedSignals;
    std::vector<std::deque<float>> m_vBufferedFilteredSignals;
    std::vector<std::deque<float>> m_vSignalBuffer;
    std::deque<float> m_vTimeBuffer;
    int m_i32FilterOrder;
    int m_i32NbSignals;
};

#endif // SIGNALPROCESSING_H
