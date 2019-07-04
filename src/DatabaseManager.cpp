#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(): m_bIsDatabseOpened(false), m_bIsRequestSuccessfull(false)
{
	m_oPatientDatabase = QSqlDatabase::addDatabase("QMYSQL");
}

DatabaseManager::~DatabaseManager()
{
	
}

void DatabaseManager::setHostName(QString sHostName)
{
	m_oPatientDatabase.setHostName(sHostName);
}

void DatabaseManager::setDatabaseName(QString sDatabaseName)
{
	m_oPatientDatabase.setDatabaseName(sDatabaseName);
}

void DatabaseManager::setUserName(QString sUserName)
{
	m_oPatientDatabase.setUserName(sUserName);
}

void DatabaseManager::setPassword(QString sPassword)
{
	m_oPatientDatabase.setPassword(sPassword);
}

void DatabaseManager::setTableName(QString sTableName)
{
	m_sTableName = sTableName;
}

bool DatabaseManager::search(QString sKeyword)
{
    if (m_oPatientDatabase.open())
    {
        qDebug() << "[INFO] (DatabaseManager::search) Database opened successfully!";

        QSqlQuery l_oRequest;
        QString l_sRequest = "SELECT * FROM " + m_sTableName + " WHERE Nom = '" +sKeyword + "'" ;
        //qDebug() << "l_sRequest = " << l_sRequest;

        if(l_oRequest.exec(l_sRequest))
        {
            m_bIsRequestSuccessfull = true;

            qDebug() << "[INFO] (DatabaseManager::search) Request sent successfully!";
            l_oRequest.next();
            emit sigBroadcastSearchInfos(l_oRequest.value("Nom").toString(), l_oRequest.value("Prenom").toString(), l_oRequest.value("Age").toInt(), l_oRequest.value("Taille").toFloat(), l_oRequest.value("Poids").toFloat());
        }
        else
        {
            qDebug() << "[ERROR] (DatabaseManager::search) Failed to perform request!";
            qDebug() << l_oRequest.lastError();

            m_bIsRequestSuccessfull = false;
        }

        m_oPatientDatabase.close(); // Fermeture de la base de donn?es
    }
    else
    {
        qDebug() << "[ERROR] (DatabaseManager::search) Failed to open database!";
        qDebug() << m_oPatientDatabase.lastError();

         m_bIsRequestSuccessfull = false;
    }

	return m_bIsRequestSuccessfull;
}


void DatabaseManager::setSearchField(QString sNameToLookFor)
{
    search(sNameToLookFor);
}


void DatabaseManager::addEntry(QString sName, QString sFirstName, int i32Age, float fSize, float fWeight)
{
    if (m_oPatientDatabase.open())
    {
        qDebug() << "[INFO] (DatabaseManager::search) Database opened successfully!";

        QSqlQuery l_oRequest;
        QString l_sRequest = "INSERT INTO `" + m_sTableName +"` (`Nom`, `Prenom`, `Age`, `Taille`, `Poids`) VALUES ('" + sName + "', '" + sFirstName + "', '" + QString::number(i32Age) + "', '" + QString::number(fSize) + "', '" + QString::number(fWeight) + "')"  ;
        //qDebug() << "l_sRequest = " << l_sRequest;

        if(l_oRequest.exec(l_sRequest))
        {
            m_bIsRequestSuccessfull = true;

            qDebug() << "[INFO] (DatabaseManager::search) Request sent successfully!";

        }
        else
        {
            qDebug() << "[ERROR] (DatabaseManager::search) Failed to perform request!";
            qDebug() << l_oRequest.lastError();

            m_bIsRequestSuccessfull = false;
        }

        m_oPatientDatabase.close(); // Fermeture de la base de donn?es
    }
    else
    {
        qDebug() << "[ERROR] (DatabaseManager::search) Failed to open database!";
        qDebug() << m_oPatientDatabase.lastError();

         m_bIsRequestSuccessfull = false;
    }
}

void DatabaseManager::removeEntry(QString sName)
{
    if (m_oPatientDatabase.open())
    {
        qDebug() << "[INFO] (DatabaseManager::search) Database opened successfully!";

        QSqlQuery l_oRequest;
        QString l_sRequest = "DELETE FROM `" + m_sTableName +"` WHERE `Nom` = '" + sName +"'";
        //qDebug() << "l_sRequest = " << l_sRequest;

        if(l_oRequest.exec(l_sRequest))
        {
            m_bIsRequestSuccessfull = true;

            qDebug() << "[INFO] (DatabaseManager::search) Request sent successfully!";

        }
        else
        {
            qDebug() << "[ERROR] (DatabaseManager::search) Failed to perform request!";
            qDebug() << l_oRequest.lastError();

            m_bIsRequestSuccessfull = false;
        }

        m_oPatientDatabase.close(); // Fermeture de la base de donn?es
    }
    else
    {
        qDebug() << "[ERROR] (DatabaseManager::search) Failed to open database!";
        qDebug() << m_oPatientDatabase.lastError();

         m_bIsRequestSuccessfull = false;
    }
}
