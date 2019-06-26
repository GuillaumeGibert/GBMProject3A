#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QObject>
#include <QDebug>
#include <QtSql>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    DatabaseManager();
    ~DatabaseManager();

public:
	void setHostName(QString);
	void setDatabaseName(QString);
	void setUserName(QString);
	void setPassword(QString);
	void setTableName(QString);
    bool search(QString);

	
	

private:
	QSqlDatabase m_oPatientDatabase;
	QSqlQuery m_oDatabaseRequest;
	bool m_bIsDatabseOpened;
	QString m_sTableName;
	bool m_bIsRequestSuccessfull;
};

#endif
