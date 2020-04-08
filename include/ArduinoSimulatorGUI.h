#ifndef ARDUINO_SIMULATOR_GUI_H
#define ARDUINO_SIMULATOR_GUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>


class ArduinoSimulatorGUI : public QWidget
{
    Q_OBJECT

public:
    ArduinoSimulatorGUI();
    ~ArduinoSimulatorGUI();

signals:
    void sendDataFilename(QString sDataFilename);

public slots:
    void openDialog();

private:
    QPushButton* m_pLoadConfigFileButton;

};


#endif
