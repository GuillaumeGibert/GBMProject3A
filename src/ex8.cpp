#include <QApplication>

#include "DatabaseManager.h"
#include "MainWindowEx8.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseManager dbManager;
    dbManager.setHostName("127.0.0.1"); // @ip serveur MySQL
    dbManager.setDatabaseName("GBMProject3A"); // Nom de la base
    dbManager.setUserName("root"); // Nom utilisateur
    dbManager.setPassword(""); // Mot de passe
    dbManager.setTableName("Patient");

    dbManager.search("Dupond");

    //=======MainWindow=========
    // creates the Main Window
    MainWindowEx8 window;
    // shows the main window
    window.show();

    //=======Qt CONNECTIONS=========
    QObject::connect(&window,       SIGNAL(sigBroadcastSearchField(QString)),                               &dbManager,     SLOT(setSearchField(QString)));
    QObject::connect(&dbManager,    SIGNAL(sigBroadcastSearchInfos(QString, QString, int, float, float)),   &window,        SLOT(setSearchInfos(QString, QString, int, float, float)));
    QObject::connect(&window,       SIGNAL(sigBroadcastAddPatient(QString, QString, int, float, float)),    &dbManager,     SLOT(addEntry(QString, QString, int, float, float)));
    QObject::connect(&window,       SIGNAL(sigBroadcastRemovePatient(QString)),                             &dbManager,     SLOT(removeEntry(QString)));

    return app.exec();
}
