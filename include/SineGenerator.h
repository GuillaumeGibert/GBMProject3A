#ifndef SINE_GENERATOR_H
#define SINE_GENERATOR_H

#include <QObject>
#include <QDebug>
#include <QBasicTimer>
#include <QElapsedTimer>

#define _USE_MATH_DEFINES
#include "math.h"

class SineGenerator : public QObject
{
    Q_OBJECT

public:
    SineGenerator();
    ~SineGenerator();

protected:
	void timerEvent(QTimerEvent *e);
	virtual void doWork();

public slots:
	void setNbSignals(int);
	void setFps(float);
	void setFrequencies(std::vector<float>);
	void setAmplitudes(std::vector<float>);
	void setPhases(std::vector<float>);

	void startWork();
	void stopWork();


signals:
    void sigBroadcastSignalValues(float, std::vector<float>);

private:
	int m_i32NbSignals;
	float m_fFps;
	std::vector<float> m_vFrequencies;
	std::vector<float> m_vAmplitudes;
	std::vector<float> m_vPhases;

	QBasicTimer* m_pTimer;                  /**< qt timer */
	QElapsedTimer* m_pElapsedTimer;

	bool m_bWorkStarted;

};

#endif // SINE_GENERATOR_H
