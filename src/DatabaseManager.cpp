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
        QString l_sRequest = "SELECT * FROM " + m_sTableName + " WHERE Nom LIKE '" +sKeyword + "%'" ;
        qDebug() << "l_sRequest = " << l_sRequest;
        if(l_oRequest.exec(l_sRequest))
        {
            m_bIsRequestSuccessfull = true;

            qDebug() << "[INFO] (DatabaseManager::search) Request sent successfully!";

            // Boucle qui permet de parcourir les enregistrements renvoy?s par la requ?te
            while(l_oRequest.next())
            {
                qDebug()    << l_oRequest.value("Nom").toString() << " " << l_oRequest.value("Prenom").toString() << " "
                            << l_oRequest.value("Age").toInt() << " " << l_oRequest.value("Taille").toFloat()
                            << l_oRequest.value("Poids").toFloat();
            }
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
    /*if (!m_bIsDatabseOpened)
	{
		qDebug() << "(DatabaseManager::search) Could not request beacuse database is not open!";
		return m_bIsDatabseOpened;
    }*/
    /*
	QString l_sRequest = "SELECT " + sKeyword + "FROM " + m_sTableName;
    qDebug() << "l_sRequest = " << l_sRequest;
    m_bIsRequestSuccessfull = m_oDatabaseRequest.exec("SELECT * FROM Patient");
	
	if (!m_bIsRequestSuccessfull)
	{
		qDebug() << "[ERROR] (DatabaseManager::search) Failed to perform request!";
                qDebug() << m_oDatabaseRequest.lastError();
	}
    else
    {
        while(m_oDatabaseRequest.next())
        {
           qDebug()    << m_oDatabaseRequest.value("Nom").toString() << " " << m_oDatabaseRequest.value("Prenom").toString() << " "
                        << m_oDatabaseRequest.value("Age").toInt() << " " << m_oDatabaseRequest.value("Taille").toFloat()
                        << m_oDatabaseRequest.value("Poids").toFloat();
        }
    }
    */
	return m_bIsRequestSuccessfull;
}

