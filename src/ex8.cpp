#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    //QApplication app(argc, argv);

    QSqlDatabase dbPatient;
    // Instanciation de la variable membre dbPatient
    dbPatient = QSqlDatabase::addDatabase("QMYSQL");

	// D�finition des param�tres de connexion � la base de donn�es
    dbPatient.setHostName("127.0.0.1"); // @ip serveur MySQL
    dbPatient.setDatabaseName("GBMProject3A"); // Nom de la base
    dbPatient.setUserName("root"); // Nom utilisateur
    dbPatient.setPassword(""); // Mot de passe

    if(dbPatient.open())
    {
        qDebug() << "Ok - ouverture de la base de donn�e";

        // Ex�cution d'une requ�te
        QSqlQuery requete;

        if(requete.exec("SELECT * FROM Patient"))
        {
            qDebug() << "Ok - requete";

            // Boucle qui permet de parcourir les enregistrements renvoy�s par la requ�te
            while(requete.next())
            {
                // On acc�de ici aux diff�rents champs par leurs nom, il est �galement possible
                // d'y acc�der par leur index : requete.value(0)
                qDebug()    << requete.value("Nom").toString() << " " << requete.value("Prenom").toString() << " "
                            << requete.value("Age").toInt() << " " << requete.value("Taille").toFloat()
                            << requete.value("Poids").toFloat();
            }
        }
        else
        {
            qDebug() << "Echec de la requ�te";
            // La m�thode lastError permet d'afficher un message
            // plus explicite sur les causes de l'erreur
            qDebug() << requete.lastError();
        }

        dbPatient.close(); // Fermeture de la base de donn�es
	}
    else
    {
        qDebug() << "Echec d'ouverture de la base de donn�e";
        qDebug() << dbPatient.lastError();
	}

    //return app.exec();
}
