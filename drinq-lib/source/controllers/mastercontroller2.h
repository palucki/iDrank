#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <drinq-lib_global.h>
#include <controllers/databasecontrollerinterface.h>
#include <models/drink.h>

#include <memory>

class PartyController;

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT MasterController2 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<drinq::models::Party2> ui_parties READ ui_parties NOTIFY ui_partiesChanged )
    Q_PROPERTY(bool ui_party_started MEMBER m_party_started NOTIFY ui_party_startedChanged)
    Q_PROPERTY(QString ui_party_title MEMBER m_party_title NOTIFY ui_party_titleChanged)
public:
    explicit MasterController2(QObject *parent = nullptr,
                               drinq::controllers::DatabaseControllerInterface* dbController = nullptr,
                               PartyController* partyController = nullptr);
    ~MasterController2();

    Q_INVOKABLE QQmlListProperty<drinq::models::Party2> ui_parties();

public slots:
    void startParty(const QString& name);
    void endParty();

signals:
    void ui_partiesChanged();
    void ui_party_startedChanged();
    void ui_party_titleChanged();

private:
    void setPartyName(const QString& name);
    bool isPartyStarted();

    bool m_party_started = false;
    QString m_party_title;

    DatabaseControllerInterface* databaseController{nullptr};
    QList<drinq::models::Party2*> m_parties;
    drinq::models::Party2* m_current_party;
    PartyController* partyController{nullptr};
};

}
}
#endif // MASTERCONTROLLER_H
