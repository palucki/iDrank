#include "databasetoastprovider.h"
#include "controllers/databasecontrollerinterface.h"

#include <QDebug>
#include <QString>
#include <QRandomGenerator>

//Inspired by https://teksty.jeja.pl/266,okrzyki-pijackie-toasty.html

DatabaseToastProvider::DatabaseToastProvider(drinq::controllers::DatabaseControllerInterface& db)
    : m_db(db)
{
}

DatabaseToastProvider::~DatabaseToastProvider()
{
}

Toast* DatabaseToastProvider::randomToast(QVariant partyId)
{
    qDebug() << "Random toast for party " << partyId;

    const auto sql = QString("SELECT id, text "
                             "FROM toast "
                             "WHERE id NOT IN (SELECT COALESCE(toast_id,0) FROM drink WHERE party_id = %1) "
                             "ORDER BY RANDOM() LIMIT 1;").arg(partyId.toInt());

    bool ok = false;
    const auto result = m_db.execQuery(sql, ok);
    if(ok && !result.isEmpty())
    {
        QVariant toast_id{result[0][0]};
        QString toast_text{result[0][1].toString()};

        return new Toast(toast_text, toast_id, this);
    }

    return new Toast(tr("Toasty się skończyły..."), {}, this);
}
