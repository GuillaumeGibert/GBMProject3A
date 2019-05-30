#include "SineGenerator.h"

SineGenerator::SineGenerator():
	m_pTimer(new QBasicTimer),m_pElapsedTimer(new QElapsedTimer),
	m_bWorkStarted(false)
{
	// default values
	m_i32NbSignals = 1;
	m_fFps = 10.0;
	m_vFrequencies.push_back(1.0);
	m_vAmplitudes.push_back(1.0);
	m_vPhases.push_back(0.0);
}


SineGenerator::~SineGenerator()
{
	m_vFrequencies.clear();
	m_vAmplitudes.clear();
	m_vPhases.clear();
	
	if (nullptr != m_pTimer)
		delete m_pTimer;
	
	if(nullptr != m_pElapsedTimer)
		delete m_pElapsedTimer;
}

void SineGenerator::setNbSignals(int i32NbSignals)
{
    m_i32NbSignals = i32NbSignals;
}

void SineGenerator::setFps(float fFps)
{
	m_fFps = fFps;
}

void SineGenerator::setFrequencies(std::vector<float> vFrequencies)
{
	m_vFrequencies = vFrequencies;
}

void SineGenerator::setAmplitudes(std::vector<float> vAmplitudes)
{
	m_vAmplitudes = vAmplitudes;
}

void SineGenerator::setPhases(std::vector<float> vPhases)
{
	m_vPhases = vPhases;
}

void SineGenerator::timerEvent(QTimerEvent *e)
{
	Q_UNUSED(e);

	doWork();
}

void SineGenerator::doWork()
{
	std::vector<float> vSignalValues;
	
	// amplitude * sin (2 * pi * frequency * time + phase)
    for (int l_signal = 0; l_signal < m_i32NbSignals; l_signal++)
        vSignalValues.push_back(m_vAmplitudes[l_signal] * sin (2.0f * M_PI * m_vFrequencies[l_signal] * (float)m_pElapsedTimer->elapsed() / 1000.0 + m_vPhases[l_signal]));

	emit sigBroadcastSignalValues(vSignalValues);
}

void SineGenerator::startWork()
{
	if (!m_bWorkStarted)
	{
		m_bWorkStarted = true;
		m_pTimer->start(1000.0 / m_fFps, this);
		m_pElapsedTimer->start();
	}
}

void SineGenerator::stopWork()
{
	if (m_bWorkStarted)
	{
		m_bWorkStarted = false;
		m_pTimer->stop();
	}
}


