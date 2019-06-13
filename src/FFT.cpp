#include "FFT.h"

FFT::FFT()
{
    m_vf64InSignal.clear();
    m_bTrigoTablesComputed = false;
    m_i32InSignalLength = 0;
}

FFT::~FFT()
{

}

void FFT::setNbSignals(int nbSignal)
{
    m_i32NbSignals = nbSignal;
    //m_vBufferedSignals.resize(m_i32NbSignals);
    //m_vBufferedFilteredSignals.resize(m_i32NbSignals);
}

void FFT::setFps(float fFps)
{
    m_fFps = fFps;
}

void FFT::setBufferedSignalValues(std::vector<std::deque<float>> vBufferedSignalValues)
{
    for (auto l_signal = 0; l_signal < m_i32NbSignals; l_signal++)
    {
        std::vector<float> l_vCurrentBufferedSignal = {vBufferedSignalValues[l_signal+1].begin(), vBufferedSignalValues[l_signal+1].end()};
    }
}

void FFT::compute()
{
    // sets the real and imag parts of the input signal
    // our input signal is always real
    std::vector<double> l_vf64SignalReal(m_vf64InSignal);
    std::vector<double> l_vf64SignalImag(l_vf64SignalReal.size(), 0.0);

    std::size_t n = l_vf64SignalReal.size();
    if (n == 0)
        return;
    else if ((n & (n - 1)) == 0)  // Is power of 2
        transformRadix2(l_vf64SignalReal, l_vf64SignalImag);
    else  // More complicated algorithm for arbitrary sizes
        //transformBluestein(l_vf64SignalReal, l_vf64SignalImag);

    m_vf64RealDFT = l_vf64SignalReal;
    m_vf64ImagDFT = l_vf64SignalImag;
}

void FFT::transformRadix2(std::vector<double> &real, std::vector<double> &imag)
{
    // Compute levels = floor(log2(n))
    if (real.size() != imag.size())
        throw "Mismatched lengths";

    std::size_t n = real.size();
    unsigned int levels;
    {
        std::size_t temp = n;
        levels = 0;
        while (temp > 1) {
            levels++;
            temp >>= 1;
        }
        if (1u << levels != n)
            throw "Length is not a power of 2";
    }

    // buffer size has changed therefore trigo tables shoud be recomputed
    if (real.size()!=m_i32InSignalLength)
        m_bTrigoTablesComputed = false;

    if (!m_bTrigoTablesComputed)
    {
        // Trignometric tables
        m_vf64cosTable.resize(n/2);
        m_vf64sinTable.resize(n/2);

        for (std::size_t i = 0; i < n / 2; i++)
        {
            m_vf64cosTable[i] = cos(2 * M_PI * i / n);
            m_vf64sinTable[i] = sin(2 * M_PI * i / n);
        }

        m_bTrigoTablesComputed = true;
    }



    // Bit-reversed addressing permutation
    for (std::size_t i = 0; i < n; i++)
    {
        std::size_t j = reverseBits(i, levels);
        if (j > i)
        {
            double temp = real[i];
            real[i] = real[j];
            real[j] = temp;
            temp = imag[i];
            imag[i] = imag[j];
            imag[j] = temp;
        }
    }

    // Cooley-Tukey decimation-in-time radix-2 FFT
    for (std::size_t size = 2; size <= n; size *= 2)
    {
        std::size_t halfsize = size / 2;
        std::size_t tablestep = n / size;
        for (std::size_t i = 0; i < n; i += size)
        {
            for (std::size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep)
            {
                double tpre =  real[j+halfsize] * m_vf64cosTable[k] + imag[j+halfsize] * m_vf64sinTable[k];
                double tpim = -real[j+halfsize] * m_vf64sinTable[k] + imag[j+halfsize] * m_vf64cosTable[k];
                real[j + halfsize] = real[j] - tpre;
                imag[j + halfsize] = imag[j] - tpim;
                real[j] += tpre;
                imag[j] += tpim;
            }
        }
        if (size == n)  // Prevent overflow in 'size *= 2'
            break;
    }
}

std::size_t FFT::reverseBits(std::size_t x, unsigned int n)
{
    std::size_t result = 0;
    unsigned int i;
    for (i = 0; i < n; i++, x >>= 1)
        result = (result << 1) | (x & 1);
    return result;
}

void FFT::powerSpectrum()
{
    std::size_t n = m_vf64RealDFT.size();
    if (n == 0)
        return;

    m_vf64PowerSpectrum.resize(n);
    for (std::size_t i = 0; i < n; i++)
    {
        m_vf64PowerSpectrum[i] = sqrt(pow(m_vf64RealDFT[i],2) + pow(m_vf64ImagDFT[i],2));
    }
}

void FFT::phaseSpectrum()
{
    std::size_t n = m_vf64RealDFT.size();
    if (n == 0)
        return;

    m_vf64PhaseSpectrum.resize(n);
    for (std::size_t i = 0; i < n; i++)
    {
        m_vf64PhaseSpectrum[i] = atan2(m_vf64ImagDFT[i], m_vf64RealDFT[i]);
    }
}

void FFT::hannWindow(std::vector<double>& inSignal, std::vector<double>& outSignal)
{
    std::size_t n = inSignal.size();

    if (n == 0)
        return;

    for (std::size_t i=0; i < n; i++)
    {
        double multiplier = 0.5 * (1 - cos(2*M_PI*i/(n-1)));
        outSignal[i] = multiplier * inSignal[i];
    }
}

void FFT::findPowerSpectrumPeak(int low, int high)
{
    int index = low;
    double biggestValue = 0;

    for (int l_sample=low; l_sample<high; l_sample++)
    {
        if (m_vf64PowerSpectrum[l_sample]>biggestValue)
        {
            biggestValue = m_vf64PowerSpectrum[l_sample];
            index = l_sample;
        }
    }
    m_f64PowerSpectrumPeak = biggestValue;
    m_i32PowerSpectrumPeakIndex = index;
}
