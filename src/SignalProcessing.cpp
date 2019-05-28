#include "SignalProcessing.h"

SignalProcessing::SignalProcessing()
{
    m_pFilter = new TemporalFilter();

    // butterworth low-pass, 6th order, Sampling rate = 100 Hz, Cutoff Frequency = 0.5 Hz
    //std::vector<float> l_aFilterCoefs = {  1.00000f,   -5.87862f,   14.40044f,  -18.81529f,   13.82942f,   -5.42165f,    0.88569f};
    //std::vector<float> l_bFilterCoefs = { 0.000000000014144f,   0.000000000084864f,   0.000000000212161f,   0.000000000282881f,   0.000000000212161f,   0.000000000084864f,   0.000000000014144f};

    // butterworth low-pass, 6th order, Sampling rate = 100 Hz, Cutoff Frequency = 5 Hz
   // std::vector<float> l_aFilterCoefs = {  1.00000f,   -4.78714f,    9.64952f,  -10.46908f,    6.44111f,   -2.12904f,    0.29517f};
    //std::vector<float> l_bFilterCoefs = { 0.0000085766f,   0.0000514593f,   0.0001286484f,   0.0001715311f,   0.0001286484f,   0.0000514593f,   0.0000085766f};


    // butterworth low-pass, 6th order, Sampling rate = 100 Hz, Cutoff Frequency = 1 Hz
    //std::vector<float> l_aFilterCoefs = {   1.0000000000000000000000000000000000000000f,	-3.8358255406473480420004307234194129705429f,	5.5208191366222276741382302134297788143158f,	-3.5335352194630145206133420288097113370895f,	0.8485559992664769568548877032299060374498f};
    //std::vector<float> l_bFilterCoefs = { 0.0000008984861463970645773386694207807146f,	0.0000035939445855882583093546776831228584f,	0.0000053909168783823870405155428975341181f,	0.0000035939445855882583093546776831228584f,	0.0000008984861463970645773386694207807146f};

    // butterworth low-pass, 6th order, Sampling rate = 100 Hz, Cutoff Frequency = 3 Hz
    std::vector<float> l_aFilterCoefs = { 1.00000f,   -5.27192f,   11.61993f,  -13.70270f,    9.11607f,   -3.24342f,    0.48207f};
    std::vector<float> l_bFilterCoefs = { 0.00000049535f,   0.00000297211f,   0.00000743028f,   0.00000990704f,   0.00000743028f,   0.00000297211f,   0.00000049535f};


    m_pFilter->setAFilterCoefficients(l_aFilterCoefs);
    m_pFilter->setBFilterCoefficients(l_bFilterCoefs);

    m_vBufferedSignals.resize(1);
    m_vBufferedFilteredSignals.resize(1);
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
