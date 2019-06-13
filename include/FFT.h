#ifndef FFT_H
#define FFT_H

#include <QObject>
#include <QDebug>

#include <deque>

#define _USE_MATH_DEFINES
#include <math.h>


class FFT: public QObject
{
    Q_OBJECT

public:
    FFT();
    ~FFT();

public:
    void compute();
    void setNbSignals(int);
    void setFps(float);

public slots:
    void setBufferedSignalValues(std::vector<std::deque<float>> vBufferedSignalValues);

private:
    void transformRadix2(std::vector<double> &real, std::vector<double> &imag);
    std::size_t reverseBits(std::size_t x, unsigned int n);
    void powerSpectrum();
    void phaseSpectrum();
    void hannWindow(std::vector<double>& inSignal, std::vector<double>& outSignal);
    void findPowerSpectrumPeak(int low, int high);


private:
    std::vector<double> m_vf64InSignal; /**< signal values to be processed */
    std::vector<double> m_vf64InSignalPadded; /**< padded signal (legnth=power of 2) to be processed */
    int m_i32InSignalLength; /**< padded signal (legnth=power of 2) to be processed */
    std::vector<double> m_vf64cosTable; /**< the cosine table  */
    std::vector<double> m_vf64sinTable; /**< the sine table  */

    std::vector<double> m_vf64RealDFT;	/**< the real part of the Discrete Fourier Transform of m_vf64InSignal  */
    std::vector<double> m_vf64ImagDFT;	/**< the imag part of the Discrete Fourier Transform of m_vf64InSignal  */

    std::vector<double> m_vf64PowerSpectrum; /**< the power of the Discrete Fourier Transform of m_vf64InSignal  */
    std::vector<double> m_vf64PhaseSpectrum; /**< the phase of the Discrete Fourier Transform of m_vf64InSignal  */

    double m_f64PowerSpectrumPeak; /**< the peak of the power spectrum of m_vf64InSignal  */
    int m_i32PowerSpectrumPeakIndex; /**< the index of the peak of the power spectrum of m_vf64InSignal  */

    bool m_bTrigoTablesComputed;/**<  a boolean to check if we need to compute the trigonometric tables  */

    int m_i32NbSignals;
    float m_fFps;

};

#endif

