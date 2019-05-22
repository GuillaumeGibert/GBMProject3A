#ifndef SIGNALPROCESSING_H
#define SIGNALPROCESSING_H

#include <QObject>
#include <QDebug>
#include "TemporalFilter.h"
#include <deque>

class SignalProcessing : public QObject
{
    Q_OBJECT

public:
    SignalProcessing();
    ~SignalProcessing();

public slots:
    void setInputData(std::vector<float>);

protected:
    void bufferSignals(std::vector<float>);

signals:
    void sigBroadcastFilteredValues(std::vector<float>);

private:
    TemporalFilter* m_pFilter;
    std::vector<std::deque<float>> m_vBufferedSignals;
};

#endif // SIGNALPROCESSING_H
