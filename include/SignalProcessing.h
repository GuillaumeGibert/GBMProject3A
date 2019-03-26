#ifndef SIGNALPROCESSING_H
#define SIGNALPROCESSING_H

#include <QObject>
#include <QDebug>


class SignalProcessing : public QObject
{
    Q_OBJECT

public:
    SignalProcessing();
    ~SignalProcessing();

public slots:
    void setInputData(std::vector<float>);

};

#endif // SIGNALPROCESSING_H
