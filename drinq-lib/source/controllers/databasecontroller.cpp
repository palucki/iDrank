#include "databasecontroller.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>

namespace drinq {
namespace controllers {

// Introduce this pattern to separate drink from database
//https://martinfowler.com/eaaCatalog/dataMapper.html


class DatabaseController::Implementation
{
public:
    Implementation(DatabaseController* _databaseController)
        : databaseController(_databaseController)
    {
        if (initialise())
        {
            qDebug() << "Database using Sqlite version: " + sqliteVersion();
        }
        else
        {
            qDebug() << "ERROR: Unable to open database";
        }
    }
    DatabaseController* databaseController{nullptr};
    QSqlDatabase database;

private:
    bool initialise()
    {
        QDir app_data;
        app_data.mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
        QString dbPath = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("iDrank.db");
        QFile databaseFile{dbPath};

        //in the future we may need to add some "force update" option here (e.g. major version changed)
        if(!databaseFile.exists())
        {
            qDebug() << "Creating new database from template";
            QFile::copy(":/db/iDrank.db", dbPath);
            QFile::setPermissions(dbPath, QFileDevice::ReadOwner|QFileDevice::WriteOwner);
        }

        qDebug() << "Database in path " << dbPath;

        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(dbPath);
        return database.open();
    }

    QString sqliteVersion() const
    {
        QSqlQuery query(database);
        query.exec("SELECT sqlite_version()");
        if (query.next()) return query.value(0).toString();
        return QString::number(-1);
    }
};

DatabaseController::DatabaseController(QObject* parent) : DatabaseControllerInterface(parent)
{
    implementation.reset(new Implementation(this));
}

DatabaseController::~DatabaseController()
{

}

bool DatabaseController::createRow(const QString& tableName, const QJsonObject& jsonObject) const
{
    if (tableName.isEmpty())
        return false;

    auto fieldList = jsonObject.keys();

    if(fieldList.contains("id"))
        fieldList.removeAll("id");

    QStringList fieldsListForBinding;
    for(const auto& field : fieldList)
    {
        fieldsListForBinding.append(":" + field);
    }

    QSqlQuery query(implementation->database);
    QString sqlStatement = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableName,
                                                                          fieldList.join(","),
                                                                          fieldsListForBinding.join(","));

    qDebug() << sqlStatement;

    if (!query.prepare(sqlStatement))
    {
        qDebug() << "QUERY INCORRECT " << query.lastError().text();
        return false;
    }

    for(const auto& field : fieldList)
    {
        qDebug () << "BINDING " << "field " << field << " to " << jsonObject[field].toVariant();
        query.bindValue(":" + field, jsonObject[field].toVariant());
    }

    if(!query.exec())
    {
        qDebug() << "QUERY ERROR " << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DatabaseController::create(data::EntityLite &e)
{

    auto sqlStatement = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(e.m_tableName,
                                                                                    e.m_fields.join(","),
                                                                                    e.m_bindableFields.join(","));
    qDebug() << sqlStatement;
    QSqlQuery query(implementation->database);
//    if (id != 0)
//    {
//         sqlStatement.append(" WHERE id=:id");
//    }

//    sqlStatement.append("ORDER BY started DESC");

    if (!query.prepare(sqlStatement))
    {
        qDebug() << "QUERY INCORRECT " << query.lastError().text();
        return false;
    }

    for(const auto& f : qAsConst(e.m_fields))
    {
        query.bindValue(":"+f, e.m_data[f]);
    }

    if(!query.exec())
    {
        qDebug() << "QUERY ERROR " << query.lastError().text();
        return false;
    }

    e.setId(query.lastInsertId().toString());

    return true;
}

bool DatabaseController::update(const data::EntityLite &e)
{
    if(e.m_bindableFields.size() != e.m_fields.size())
    {
        return false;
    }

    QStringList updatePart;
    for(const auto& f : qAsConst(e.m_fields))
    {
        updatePart.append(QString("%1=%2").arg(f, ":" + f));
    }

    auto sqlStatement = QString("UPDATE %1 SET %2 WHERE id = %3").arg(e.m_tableName, updatePart.join(","), e.m_id.toString());
    qDebug() << sqlStatement;

    QSqlQuery query(implementation->database);

    if(!query.prepare(sqlStatement))
    {
        qDebug() << "QUERY INCORRECT " << query.lastError().text();
        return false;
    }

    for(const auto& f : qAsConst(e.m_fields))
    {
        qDebug () << "BINDING " << "field " << f << " to " << e.m_data[f];
        query.bindValue(":"+f, e.m_data[f]);
    }

    if(!query.exec())
    {
        qDebug() << "QUERY ERROR " << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseController::get(data::EntityLite &e)
{
    auto sqlStatement = QString("SELECT %1 FROM %2 WHERE id=%3").arg(e.m_fields.join(","),
                                                                     e.m_tableName,
                                                                     e.m_id.toString());
    qDebug() << sqlStatement;

    QSqlQuery query(implementation->database);
    if(!query.prepare(sqlStatement))
    {
        qDebug() << "QUERY INCORRECT " << query.lastError().text();
        return false;
    }

    if(!query.exec() || !query.next())
    {
        qDebug() << "QUERY ERROR " << query.lastError().text();
        return false;
    }

    for(const auto& f : qAsConst(e.m_fields))
    {
        e.m_data[f] = query.value(f);
    }

    return true;
}

bool DatabaseController::remove(data::EntityLite &e)
{
    auto sqlStatement = QString("DELETE FROM %1 WHERE id=%2").arg(e.m_tableName,
                                                                  e.m_id.toString());
    qDebug() << sqlStatement;

    QSqlQuery query(implementation->database);
    if(!query.exec(sqlStatement))
    {
        qDebug() << "QUERY ERROR " << query.lastError().text();
        return false;
    }

    return true;
}

QList<QVariantList> DatabaseController::execQuery(const QString &sql, bool& ok)
{
    QSqlQuery query(implementation->database);

    if(!query.prepare(sql))
    {
        qDebug() << "QUERY INCORRECT " << query.lastQuery();
        ok = false;
        return {};
    }

    if(!query.exec(sql))
    {
        qDebug() << "QUERY " << query.lastQuery() << " ERROR " << query.lastError().text();
        ok = false;
        return {};
    }

    QList<QVariantList> result;
    ok = true;

    while(query.next())
    {
        QVariantList fields;
        const auto record = query.record();
        for(int i = 0; i < record.count(); ++i)
        {
            fields.push_back(record.value(i));
        }
        result.push_back(fields);
    }

    return result;
}

QList<data::EntityLite> DatabaseController::getAll(const data::EntityLite& e, const QString& where)
{
    auto sqlStatement = QString("SELECT %1 FROM %2 ").arg(e.m_fields.join(","), e.m_tableName);

    if(!where.isEmpty())
    {
        sqlStatement.append(" " + where);
    }

    sqlStatement.append(" ORDER BY id DESC");

    qDebug() << sqlStatement;

    QSqlQuery query(implementation->database);
    if(!query.prepare(sqlStatement))
    {
        qDebug() << "QUERY INCORRECT " << query.lastError().text();
        return {};
    }

    if(!query.exec())
    {
        qDebug() << "QUERY ERROR " << query.lastError().text();
        return {};
    }

    QList<data::EntityLite> results;

    while(query.next())
    {
        data::EntityLite added(e.m_tableName, nullptr);
        added.m_fields = e.m_fields;
        added.m_bindableFields = e.m_bindableFields;
        for(const auto& f : qAsConst(e.m_fields))
        {
            added.m_data[f] = query.value(f);
        }

//        qDebug() << "JSON in db controller " << added.toJson();

        results.append(added);
    }

//    for(const auto& r : results)
//    {
//        qDebug() << r.toJson();
//    }

    return results;
}

int DatabaseController::count(const data::EntityLite &e, const QString &where)
{
    auto sqlStatement = QString("SELECT COUNT(*) FROM %1").arg(e.m_tableName);

    if(!where.isEmpty())
    {
        sqlStatement.append(" " + where);
    }

    qDebug() << sqlStatement;

    QSqlQuery query(implementation->database);
    if(!query.prepare(sqlStatement))
    {
        qDebug() << "QUERY INCORRECT " << query.lastError().text();
        return {};
    }

    if(!query.exec() || !query.next())
    {
        qDebug() << "QUERY ERROR " << query.lastError().text();
        return {};
    }

    return query.value(0).toInt();
}

bool DatabaseController::deleteRow(const QString& tableName, const QString& id) const
{
    if (tableName.isEmpty()) return false;
    if (id.isEmpty()) return false;
    QSqlQuery query(implementation->database);
    QString sqlStatement = "DELETE FROM " + tableName + " WHERE id=:id";
    if (!query.prepare(sqlStatement)) return false;
    query.bindValue(":id", QVariant(id));
    if(!query.exec()) return false;
    return query.numRowsAffected() > 0;
}

QJsonObject DatabaseController::readRow(const QString& tableName, const QString& id) const
{
    if (tableName.isEmpty())
        return {};


    QSqlQuery query(implementation->database);

    QString sqlStatement = "SELECT * FROM " + tableName;

    if (!id.isEmpty())
    {
         sqlStatement.append(" WHERE id=:id");
    }

    if (!query.prepare(sqlStatement))
    {
        qDebug() << query.lastError().text();
        return {};
    }

    if (!id.isEmpty())
    {
        query.bindValue(":id", QVariant(id));
    }

    if (!query.exec() || !query.first())
    {
        qDebug() << query.lastError().text();
        return {};
    }

    auto json = query.value(0).toByteArray();
    auto jsonDocument = QJsonDocument::fromJson(json);


    if (!jsonDocument.isObject()) return {};
    return jsonDocument.object();
}

bool DatabaseController::updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const
{
    if (tableName.isEmpty()) return false;
    if (id.isEmpty()) return false;
    if (jsonObject.isEmpty()) return false;
    QSqlQuery query(implementation->database);
    QString sqlStatement = "UPDATE " + tableName + " SET json=:json WHERE id=:id";
    if (!query.prepare(sqlStatement)) return false;
    query.bindValue(":id", QVariant(id));
    query.bindValue(":json",
                    QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));
    if(!query.exec())
    {
        qDebug() << "Query error";
        return false;
    }
    return query.numRowsAffected() > 0;
}

QJsonObject DatabaseController::readParty(unsigned int id)
{
    QSqlQuery query(implementation->database);
    QString sqlStatement = "SELECT id, started FROM party ";

    if (id != 0)
    {
         sqlStatement.append(" WHERE id=:id");
    }

    sqlStatement.append("ORDER BY started DESC");

    if (!query.prepare(sqlStatement))
    {
        qDebug() << query.lastError().text();
        return {};
    }

    if (id != 0)
    {
        query.bindValue(":id", QVariant(id));
    }

    if (!query.exec() || !query.first())
    {
        qDebug() << query.lastError().text();
        return {};
    }

    QJsonObject result;
    result.insert("id", QJsonValue::fromVariant(query.value(0)));
    result.insert("started", QJsonValue::fromVariant(query.value(1)));

    return result;
}

QVariant DatabaseController::getLastId(const QString& tableName)
{
    if (tableName.isEmpty())
        return {};

    QSqlQuery query(implementation->database);
    auto sqlStatement = QString("SELECT MAX(id) FROM %1").arg(tableName);

    if (!query.prepare(sqlStatement) || !query.exec())
    {
        qDebug() << query.lastError().text();
        return {};
    }

    if (!query.first())
        return {};

    return query.value(0);
}

QJsonArray DatabaseController::find(const QString& tableName, const QString& searchText) const
{
    if (tableName.isEmpty())
    {
        qDebug() << "Error! Table name is empty";
        return {};
    }

//    if (searchText.isEmpty())
//    {
//        qDebug() << "Error! Search text is empty";
//        return {};
//    }

    QSqlQuery query(implementation->database);
    QString sqlStatement = "SELECT json FROM " + tableName + " WHERE lower(json) LIKE :searchText";
    if (!query.prepare(sqlStatement))
    {
        qDebug() << "Error! Unable to prepare query: " << sqlStatement;
        return {};
    }

    query.bindValue(":searchText", QVariant("%" + searchText.toLower() + "%"));

    if (!query.exec())
    {
        qDebug() << "Error! Unable to execute query: " << sqlStatement;
        return {};
    }

    qDebug() << "Executed query: " << query.executedQuery();

    QJsonArray returnValue;
    while ( query.next() )
    {
        auto json = query.value(0).toByteArray();
        auto jsonDocument = QJsonDocument::fromJson(json);
        if (jsonDocument.isObject())
        {
            returnValue.append(jsonDocument.object());
        }
    }

    return returnValue;
}

}
}
