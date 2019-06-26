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

    dbManager.search("Dupont");

    //=======MainWindow=========
    // creates the Main Window
    MainWindowEx8 window;
    // shows the main window
    window.show();

    return app.exec();
}
