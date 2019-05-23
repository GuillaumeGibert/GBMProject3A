#include "SignalProcessing.h"

SignalProcessing::SignalProcessing()
{
    m_pFilter = new TemporalFilter();

    // butterworth low-pass, 6th order, Sampling rate = 100 Hz, Cutoff Frequency = 0.5 Hz
    std::vector<float> l_aFilterCoefs = {  1.00000f,   -5.87862f,   14.40044f,  -18.81529f,   13.82942f,   -5.42165f,    0.88569f};
    std::vector<float> l_bFilterCoefs = { 0.000000000014144f,   0.000000000084864f,   0.000000000212161f,   0.000000000282881f,   0.000000000212161f,   0.000000000084864f,   0.000000000014144f};

    // butterworth low-pass, 6th order, Sampling rate = 100 Hz, Cutoff Frequency = 5 Hz
    l_aFilterCoefs = {  1.00000f,   -4.78714f,    9.64952f,  -10.46908f,    6.44111f,   -2.12904f,    0.29517f};
    l_bFilterCoefs = { 0.0000085766f,   0.0000514593f,   0.0001286484f,   0.0001715311f,   0.0001286484f,   0.0000514593f,   0.0000085766f};



    m_pFilter->setAFilterCoefficients(l_aFilterCoefs);
    m_pFilter->setBFilterCoefficients(l_bFilterCoefs);

    m_vBufferedSignals.resize(5);
    m_vBufferedFilteredSignals.resize(5);
}


SignalProcessing::~SignalProcessing()
{
    if (nullptr != m_pFilter)
    {
        delete m_pFilter;
        m_pFilter = nullptr;
    }
}

void SignalProcessing::setInputData(std::vector<float> vInputData)
{
    //if (vInputData.size()>0)
    //    qDebug() << "(SignalProcessing::setInputData): (" << vInputData[0] << ", " << vInputData[1] << ", " << vInputData[2] << ", " << vInputData[3] << ", " << vInputData[4] << ")";

    bufferSignals(vInputData);

    std::vector<float> vOutputSignal;

    for (int l_signal=0; l_signal < vInputData.size(); l_signal++)
    {
        //std::deque<float> vFilteredSignal(m_vBufferedSignals[l_signal].size());
        m_vBufferedFilteredSignals[l_signal].push_back(0.0);
        if (m_vBufferedFilteredSignals[l_signal].size()>7)
            m_vBufferedFilteredSignals[l_signal].pop_front();


        m_pFilter->filt(m_vBufferedSignals[l_signal], m_vBufferedFilteredSignals[l_signal]);
        vOutputSignal.push_back(m_vBufferedFilteredSignals[l_signal][m_vBufferedFilteredSignals[l_signal].size()-1]);
    }

    emit sigBroadcastFilteredValues(vOutputSignal);

}

void SignalProcessing::bufferSignals(std::vector<float> vInputData)
{
    for (int l_signal=0; l_signal < vInputData.size(); l_signal++)
    {
        m_vBufferedSignals[l_signal].push_back(vInputData[l_signal]);

        if ( m_vBufferedSignals[l_signal].size()>7)
            m_vBufferedSignals[l_signal].pop_front();

        /* qDebug() << "===================="  ;
        qDebug() << "m_vBufferedSignals[" <<l_signal << "] = " ;
        for (int i=0; i<m_vBufferedSignals[l_signal].size(); i++ )
            qDebug() << m_vBufferedSignals[l_signal][i];
*/

    }
}
