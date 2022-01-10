#pragma once

#include <memory>
#include <QObject>
#include <QVariant>
#include <drinq-lib_global.h>

namespace drinq::controllers {
class DatabaseControllerInterface;
class DrinkController;
}

namespace drinq::models {
class Party2;
}

class DRINQLIB_EXPORT PartyController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ui_drinks_count MEMBER m_current_drinks_count NOTIFY ui_drinks_countChanged)
public:
    explicit PartyController(QObject *parent = nullptr,
                             drinq::controllers::DatabaseControllerInterface* db = nullptr,
                             drinq::controllers::DrinkController* drinksController = nullptr);
    virtual ~PartyController();

public slots:
    bool isPartyStarted();
    void startParty();
    void endParty();
    void setPartyName(const QString& name);
    QVariant currentPartyId();
    void setDrinksCount(int count);

signals:
    void ui_drinks_countChanged(int count);

private:
    drinq::controllers::DatabaseControllerInterface* m_db;
    std::unique_ptr<drinq::models::Party2> m_current_party;
    int m_current_drinks_count = 0;
};
