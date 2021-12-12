#pragma once

#include <memory>
#include <QObject>
#include <QVariant>
#include <drinq-lib_global.h>

namespace drinq::controllers {
class DatabaseControllerInterface;
}

namespace drinq::models {
class Party2;
}

class DRINQLIB_EXPORT PartyController : public QObject
{
    Q_OBJECT
public:
    explicit PartyController(QObject *parent = nullptr, drinq::controllers::DatabaseControllerInterface* db = nullptr);
    virtual ~PartyController();

public slots:
    bool isPartyStarted();
    void startParty();
    void endParty();
    void setPartyName(const QString& name);
    QVariant currentPartyId();

signals:

private:
    drinq::controllers::DatabaseControllerInterface* m_db;
    std::unique_ptr<drinq::models::Party2> m_current_party;
};
