#include "TemporalSignalDisplay.h"

TemporalSignalDisplay::TemporalSignalDisplay()
{
	// inits parameters
	m_bDrawCurves = false;
	m_bInitialization = false;
	m_i32ScrollingOffsetXTic = 0;
	m_i32ScrollingOffsetXLegend = 0;

	// inits curves colors
	QColor l_aCol[] = 
	{ 	
		Qt::red,  Qt::blue, Qt::magenta, 
		Qt::cyan, Qt::green, Qt::yellow,
		Qt::black, Qt::darkRed, Qt::darkBlue,
		Qt::darkMagenta, Qt::darkCyan, Qt::darkGreen,
		Qt::darkYellow,Qt::white,
	};

    m_i32MaxNumberofSignals = sizeof(l_aCol) / sizeof(l_aCol[0]);
	m_vColors = std::vector<QColor>(l_aCol, l_aCol + sizeof(l_aCol) / sizeof(QColor));
	
	// sets default offset settings
    std::vector<std::string> aSCurvesLabel = std::vector<std::string>();
    setSignalLabels(aSCurvesLabel);
    QSize oSize = QSize(300, 200);
    setWidgetSize(oSize);
    QSize oXRange = QSize(0, 20);
    QSize oYRange = QSize(-200, 200);
    setXYRange(oXRange, oYRange);
    setLegends("Time (s)", "Signal (V)");
	setFps(30.f);
	setTicks(5, 5);
	setXTickLabelOffsets(10, -10);
	setYTickLabelOffsets(10, 10);
	setSignalLabelOffsets(20, 20);
	setXLegendOffsets(-50, -20);
	setYLegendOffsets(10, 10);
	setDrawLine(true);
}


TemporalSignalDisplay::~TemporalSignalDisplay()
{
	
}

void TemporalSignalDisplay::checkSettings()
{
	// checks for bad settings values
    if (m_i32NumberOfSignals == 0 || m_i32NumberOfSignals > m_i32MaxNumberofSignals)
	{
        std::cerr << "[ERROR] (TemporalSignalDisplay::checkSettings) Bad input values for Curves labels! " << std::endl;
		// throw
		m_bInitialization = false;
		return;
	}

	if (m_oSize.width() == 0 || m_oSize.height() == 0)
	{
        std::cerr << "[ERROR] (TemporalSignalDisplay::checkSettings) Bad input values for widget size! " << std::endl;
		// throw
		m_bInitialization = false;
		return;
	}

	if (m_oXRange.height() - m_oXRange.width() == 0 || m_oYRange.height() - m_oYRange.width() == 0)
	{
        std::cerr << "[ERROR] (TemporalSignalDisplay::checkSettings) Bad input values for x- or y- axis range! " << std::endl;
		// throw
		m_bInitialization = false;
		return;
	}
	
	if (m_i32XTic == 0 || m_i32YTic == 0)
	{
        std::cerr << "[ERROR] (TemporalSignalDisplay::checkSettings) Bad input values for x- or y-axis tick interval! " << std::endl;
		// throw
		m_bInitialization = false;
		return;
	}

    if (m_fFps == 0.0)
	{
        std::cerr << "[ERROR] (TemporalSignalDisplay::checkSettings) Bad input values for sampling rate (FPS)! " << std::endl;
		// throw
		m_bInitialization = false;
		return;
	}
	
	m_bInitialization = true;
}

void TemporalSignalDisplay::setSignalLabels(std::vector<std::string> vSignalLabels)
{
    m_i32NumberOfSignals = static_cast<uint>(vSignalLabels.size());
	
	// inits list of curves values
	for (uint ii = 0; ii < vSignalLabels.size(); ++ii)
	{
        std::list<float> l_lCurveValue;
		m_vSignalValues.push_back(l_lCurveValue);
		m_vSignalLabels.push_back(vSignalLabels[ii].c_str());
		m_vSignalEnabled.push_back(true);
	}
}

void TemporalSignalDisplay::setWidgetSize(QSize oSize)
{
	m_oSize = oSize;
	resize(m_oSize);
}

void TemporalSignalDisplay::setXYRange(QSize oXRange, QSize oYRange)
{
	m_oXRange = oXRange;
	m_oYRange = oYRange;
	
	// computes rescaling factors y = Ax + B
	// x-axis
	m_fXRescaleFactorA = (float)(m_oSize.width()) / ((m_oXRange.height() - m_oXRange.width()) * m_fFps);
	m_fXRescaleFactorB = -m_fXRescaleFactorA * m_oXRange.width();
	// y-axis
	m_fYRescaleFactorA = (float)(-m_oSize.height()) / (m_oYRange.height() - m_oYRange.width());
	m_fYRescaleFactorB = -m_fYRescaleFactorA * m_oYRange.height();
}

void TemporalSignalDisplay::setLegends(std::string sXLegend, std::string sYLegend)
{
	m_sXLegend = sXLegend;
	m_sYLegend = sYLegend;
}

void TemporalSignalDisplay::setFps(float fFps)
{
	m_fFps = fFps;
}

void TemporalSignalDisplay::setTicks(int i32Xtic, int i32Ytic)
{
	m_i32XTic = i32Xtic;
	m_i32YTic = i32Ytic;
}

void TemporalSignalDisplay::setXTickLabelOffsets(int i32XTickLabelOffsetX, int i32XTickLabelOffsetY)
{
	m_i32XTickLabelOffsetX = i32XTickLabelOffsetX;
	m_i32XTickLabelOffsetY = i32XTickLabelOffsetY;
}

void TemporalSignalDisplay::setYTickLabelOffsets(int i32YTickLabelOffsetX, int i32YTickLabelOffsetY)
{
	m_i32YTickLabelOffsetX = i32YTickLabelOffsetX;
	m_i32YTickLabelOffsetY = i32YTickLabelOffsetY;
}

void TemporalSignalDisplay::setSignalLabelOffsets(int i32SignalLabelOffsetX, int i32SignalLabelOffsetY)
{
	m_i32SignalLabelOffsetX = i32SignalLabelOffsetX;
	m_i32SignalLabelOffsetY = i32SignalLabelOffsetY;
}

void TemporalSignalDisplay::setXLegendOffsets(int i32XLegendOffsetX, int i32XLegendOffsetY)
{
	m_i32XLegendOffsetX = i32XLegendOffsetX;
	m_i32XLegendOffsetY = i32XLegendOffsetY;
}

void TemporalSignalDisplay::setYLegendOffsets(int i32YLegendOffsetX, int i32YLegendOffsetY)
{
	m_i32YLegendOffsetX = i32YLegendOffsetX;
	m_i32YLegendOffsetY = i32YLegendOffsetY;
}

void TemporalSignalDisplay::setDrawLine(bool bDrawLines)
{
	m_bDrawLines = bDrawLines;
}

void TemporalSignalDisplay::setNewValues(std::vector<float> aFCurvesValues)
{
	if (!m_bInitialization)
		checkSettings();
	else
	{
        if (aFCurvesValues.size() != m_i32NumberOfSignals)
		{
			if (m_bVerbose)
                std::cerr << "[ERROR] (TemporalSignalDisplay::setNewValues) the size of the vector doesn't match the predefined number of curves! " << std::endl;
			m_bDrawCurves = false;
			return;
		}
		else
		{
			bool l_bIsSroll = false;
			m_bDrawCurves = true;

            for (uint ii = 0; ii < m_i32NumberOfSignals; ++ii)
			{
                if (m_vSignalValues[ii].size() == (m_oXRange.height() - m_oXRange.width()) * m_fFps)
				{
                    m_vSignalValues[ii].pop_front();
					l_bIsSroll = true;
				}

                m_vSignalValues[ii].push_back(aFCurvesValues[ii]);
			}

			// apply scrolling offset
			if (l_bIsSroll)
			{
				++m_i32ScrollingOffsetXTic;

				if (m_i32ScrollingOffsetXTic % (int)(m_i32XTic * m_fFps) == 0)
				{
					++m_i32ScrollingOffsetXLegend;
				}

				m_i32ScrollingOffsetXTic = m_i32ScrollingOffsetXTic % (int)(m_i32XTic * m_fFps);
			}
		}

		update();
	}
}


void TemporalSignalDisplay::paintEvent(QPaintEvent *)
{
	QPainter l_oPainter(this);

	if (m_bDrawCurves)
	{
		// draw background
		l_oPainter.fillRect(0, 0, m_oSize.width(), m_oSize.height(), Qt::lightGray);

		// draw tics
		l_oPainter.setPen(Qt::white);

		// x-ticks
		for (uint l_xTick = 0; l_xTick < (m_oXRange.height() - m_oXRange.width()) / m_i32XTic + 1; ++l_xTick)
		{
			if (l_xTick * (m_fFps * m_i32XTic) - m_i32ScrollingOffsetXTic > 0 && l_xTick * (m_fFps * m_i32XTic) - m_i32ScrollingOffsetXTic < m_oSize.width())
				l_oPainter.drawLine(	QPoint((l_xTick * (m_fFps * m_i32XTic) - m_i32ScrollingOffsetXTic) * m_fXRescaleFactorA + m_fXRescaleFactorB, 0),
										QPoint((l_xTick * (m_fFps * m_i32XTic) - m_i32ScrollingOffsetXTic) * m_fXRescaleFactorA + m_fXRescaleFactorB, m_oSize.height()));
		}

		// y-ticks > 0
		for (uint l_yTick = 0; l_yTick < m_oYRange.height() / m_i32YTic; ++l_yTick)
		{
			l_oPainter.drawLine(	QPoint(0, (l_yTick * m_i32YTic) * m_fYRescaleFactorA + m_fYRescaleFactorB),
									QPoint(m_oSize.width(), (l_yTick * m_i32YTic) * m_fYRescaleFactorA + m_fYRescaleFactorB));
		}

		// y-ticks < 0
		for (int l_yTick = 0; l_yTick > m_oYRange.width() / m_i32YTic; --l_yTick)
		{
			l_oPainter.drawLine(	QPoint(0, (l_yTick * m_i32YTic) * m_fYRescaleFactorA + m_fYRescaleFactorB),
									QPoint(m_oSize.width(), (l_yTick * m_i32YTic) * m_fYRescaleFactorA + m_fYRescaleFactorB));
		}
		
		// draw legends
		// x-axis
		for (uint l_xTick = 0; l_xTick < (m_oXRange.height() - m_oXRange.width()) / m_i32XTic + 1; ++l_xTick)
		{
			if (l_xTick * (m_fFps * m_i32XTic) - m_i32ScrollingOffsetXTic > 0 && l_xTick * (m_fFps * m_i32XTic) - m_i32ScrollingOffsetXTic < m_oSize.width())
			{
                std::ostringstream l_osXLegend;
				l_osXLegend << (l_xTick + m_i32ScrollingOffsetXLegend) * m_i32XTic;
				l_oPainter.drawText(QPoint((l_xTick * (m_fFps * m_i32XTic) - m_i32ScrollingOffsetXTic) * m_fXRescaleFactorA + m_fXRescaleFactorB + m_i32XTickLabelOffsetX,
					m_oSize.height() + m_i32XTickLabelOffsetY),
					l_osXLegend.str().c_str()
				);
			}
		}

		// y-axis > 0
		for (uint l_yTick = 0; l_yTick < m_oYRange.height() / m_i32YTic; ++l_yTick)
		{
            std::ostringstream l_osYLegend;
			l_osYLegend << l_yTick * m_i32YTic;
			l_oPainter.drawText(	QPoint(0 + m_i32YTickLabelOffsetX,
									(l_yTick * m_i32YTic) * m_fYRescaleFactorA + m_fYRescaleFactorB + m_i32YTickLabelOffsetY),
									l_osYLegend.str().c_str()
								);
		}

		// y-axis < 0
		for (int l_yTick = 0; l_yTick > m_oYRange.width() / m_i32YTic; --l_yTick)
		{
            std::ostringstream l_osYLegend;
			l_osYLegend << l_yTick * m_i32YTic;
			l_oPainter.drawText(QPoint(0 + m_i32YTickLabelOffsetX,
				(l_yTick * m_i32YTic) * m_fYRescaleFactorA + m_fYRescaleFactorB + m_i32YTickLabelOffsetY),
				l_osYLegend.str().c_str()
			);
		}
		
		// curve names
        uint l_i32LegendTextWidth = (m_oSize.width() / 2) / static_cast<uint>(m_vSignalValues.size());

        for (uint l_curveNumber = 0; l_curveNumber < m_vSignalValues.size(); l_curveNumber++)
		{
            if (m_vSignalEnabled[l_curveNumber]) {
				if(m_bVerbose)
					std::cout << "curve " <<  l_curveNumber << "is active (curve names)" << std::endl;

                l_oPainter.setPen(m_vColors[l_curveNumber%m_vColors.size()]);

                l_oPainter.drawText(	QPoint((m_oSize.width() / 2) + (l_curveNumber * l_i32LegendTextWidth) + m_i32SignalLabelOffsetX,
                                                0 + m_i32SignalLabelOffsetY),
                                                m_vSignalLabels[l_curveNumber]
									);
			}
		}

		// x- and y-axis legend
		l_oPainter.setPen(Qt::white);
		l_oPainter.drawText(QPoint(m_oSize.width() + m_i32XLegendOffsetX,
			m_oSize.height() + m_i32XLegendOffsetY),
			QString::fromStdString(m_sXLegend)
		);

		l_oPainter.drawText(QPoint(m_i32YLegendOffsetX,
			m_i32YLegendOffsetY),
			QString::fromStdString(m_sYLegend)
		);


		// draw values
		std::vector<std::vector<QPoint> > l_aAP3fPointsToDraw;
        for (uint ii = 0; ii < m_vSignalValues.size(); ++ii)
		{

			std::vector<QPoint> l_aP3fCurvePoints;

			uint jj = 0;
            for (std::list<float>::iterator it = m_vSignalValues[ii].begin(); it != m_vSignalValues[ii].end(); ++it, ++jj)
			{
				float l_fVal = (*it);

				// checks extreme values
				if (l_fVal > m_oYRange.height())
				{
					l_fVal = m_oYRange.height();
				}
				else if (l_fVal < m_oYRange.width())
				{
					l_fVal = m_oYRange.width();
				}

				int l_fValToPlot = l_fVal * m_fYRescaleFactorA + m_fYRescaleFactorB;

				l_aP3fCurvePoints.push_back(QPoint(jj*m_fXRescaleFactorA + m_fXRescaleFactorB, (int)l_fValToPlot));
			}

			l_aAP3fPointsToDraw.push_back(l_aP3fCurvePoints); 
		}

		for (uint ii = 0; ii < l_aAP3fPointsToDraw.size(); ++ii)
		{
            if (m_vSignalEnabled[ii])
            {
                l_oPainter.setPen(m_vColors[ii%m_vColors.size()]);

				if (m_bDrawLines)
				{
					if (l_aAP3fPointsToDraw[ii].size() > 1) // 2 points are necessary to draw a line!
					{
						for (uint jj = 0; jj < l_aAP3fPointsToDraw[ii].size() - 1; ++jj)
						{
							l_oPainter.drawLine(l_aAP3fPointsToDraw[ii].at(jj), l_aAP3fPointsToDraw[ii].at(jj + 1));
						}
					}
				}
				else
				{
					for (uint jj = 0; jj < l_aAP3fPointsToDraw[ii].size(); ++jj)
					{
						l_oPainter.drawPoint(l_aAP3fPointsToDraw[ii].at(jj));
					}
				}
			}
		}
	}
}
