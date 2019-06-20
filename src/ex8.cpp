#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    //QApplication app(argc, argv);

    QSqlDatabase dbPatient;
    // Instanciation de la variable membre dbPatient
    dbPatient = QSqlDatabase::addDatabase("QMYSQL");

	// Définition des paramètres de connexion à la base de données
    dbPatient.setHostName("127.0.0.1"); // @ip serveur MySQL
    dbPatient.setDatabaseName("GBMProject3A"); // Nom de la base
    dbPatient.setUserName("root"); // Nom utilisateur
    dbPatient.setPassword(""); // Mot de passe

    if(dbPatient.open())
    {
        qDebug() << "Ok - ouverture de la base de donnée";

        // Exécution d'une requête
        QSqlQuery requete;

        if(requete.exec("SELECT * FROM Patient"))
        {
            qDebug() << "Ok - requete";

            // Boucle qui permet de parcourir les enregistrements renvoyés par la requête
            while(requete.next())
            {
                // On accède ici aux différents champs par leurs nom, il est également possible
                // d'y accéder par leur index : requete.value(0)
                qDebug()    << requete.value("Nom").toString() << " " << requete.value("Prenom").toString() << " "
                            << requete.value("Age").toInt() << " " << requete.value("Taille").toFloat()
                            << requete.value("Poids").toFloat();
            }
        }
        else
        {
            qDebug() << "Echec de la requête";
            // La méthode lastError permet d'afficher un message
            // plus explicite sur les causes de l'erreur
            qDebug() << requete.lastError();
        }

        dbPatient.close(); // Fermeture de la base de données
	}
    else
    {
        qDebug() << "Echec d'ouverture de la base de donnée";
        qDebug() << dbPatient.lastError();
	}

    //return app.exec();
}
