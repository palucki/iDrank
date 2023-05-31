#pragma once 

#include <optional>
#include <QObject>

class Toast : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant id MEMBER m_id CONSTANT)
    Q_PROPERTY(QString ui_text MEMBER m_text CONSTANT)

public:
    Toast(QObject* parent = nullptr) : QObject(parent) {};
    virtual ~Toast() override {};

    static Toast* getRandomToast(const QVariant& party_id) 
    {
        QSqlQuery query;
        query.prepare("SELECT id, text FROM toast WHERE id NOT IN (SELECT COALESCE(toast_id,0) FROM drink WHERE party_id = :party_id) ORDER BY RANDOM() LIMIT 1");
        query.bindValue(":party_id", party_id);

        if(!query.exec())
        {
            qWarning() << "Toast::getRandomToast - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
        }

        if(query.next())
        {
            auto t = new Toast;
            t->m_id = query.value(0);
            t->m_text = query.value(1).toString();
            return t;
        }

        return nullptr;
    }

public:
    QVariant m_id;
    QString m_text;
};