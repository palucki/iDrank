#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>

class DatabaseController : public QObject 
{
   Q_OBJECT

public:
    explicit DatabaseController(QObject* parent = 0) : QObject(parent) { }
    virtual ~DatabaseController() {}

    bool init()
    {
        QDir app_data;
        app_data.mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
        QString dbPath = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("iDrank.db");
        QFile databaseFile{dbPath};

        // in the future we may need to add some "force update" option here (e.g. major version changed)
        if(!databaseFile.exists())
        {
            qDebug() << "Creating new database from template";
            if(!QFile::copy(":/db/iDrank.db", dbPath))
            {
                qDebug() << "Unable to create a new database from template";
                exit(-1);
            }

            if(!QFile::setPermissions(dbPath, QFileDevice::ReadOwner|QFileDevice::WriteOwner))
            {
                qDebug() << "Unable to set permissions for newly created db";
                exit(-1);
            }
        }

        qDebug() << "Database in path " << dbPath;

        m_database = QSqlDatabase::addDatabase("QSQLITE");
        m_database.setDatabaseName(dbPath);
        return m_database.open();
    }
private: 
    QSqlDatabase m_database;
};