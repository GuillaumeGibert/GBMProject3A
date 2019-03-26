#include "SignalProcessing.h"

SignalProcessing::SignalProcessing()
{

}


SignalProcessing::~SignalProcessing()
{

}

void SignalProcessing::setInputData(std::vector<float> vInputData)
{
    if (vInputData.size()>0)
        qDebug() << "(SignalProcessing::setInputData): (" << vInputData[0] << ", " << vInputData[1] << ", " << vInputData[2] << ", " << vInputData[3] << ", " << vInputData[4] << ")";
}
