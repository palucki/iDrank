#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <drinq-lib_global.h>
#include <controllers/databasecontrollerinterface.h>
#include <models/drink.h>
#include <models/user.h>

#include <memory>

class PartyController;
class QSettings;

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT MasterController2 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<drinq::models::Party2> ui_parties READ ui_parties NOTIFY ui_partiesChanged )
    Q_PROPERTY(bool ui_party_started MEMBER m_party_started NOTIFY ui_party_startedChanged)
    Q_PROPERTY(QString ui_party_title MEMBER m_party_title NOTIFY ui_party_titleChanged)
    Q_PROPERTY(bool ui_user_missing MEMBER m_user_missing NOTIFY ui_user_missing_changed)
    Q_PROPERTY(QStringList ui_involved_users READ getInvolvedUsers NOTIFY ui_involved_users_changed)
public:
    explicit MasterController2(QObject *parent = nullptr,
                               drinq::controllers::DatabaseControllerInterface* dbController = nullptr,
                               PartyController* partyController = nullptr,
                               QSettings* settings = nullptr);
    ~MasterController2();

    Q_INVOKABLE QQmlListProperty<drinq::models::Party2> ui_parties();

public slots:
    void startParty(const QString& name);
    void endParty();
    qint64 secondsSinceLastDrink();

    void registerUser(const QString& username, const QString& email);

    QVariantList getUsers();
    void addUser(const QString& name);
    void deleteUser(const int id);

    void setInvolvedUsers(const QVariantList& users);
    QStringList getInvolvedUsers();

signals:
    void ui_partiesChanged();
    void ui_party_startedChanged();
    void ui_party_titleChanged();
    void ui_user_missing_changed();
    void ui_involved_users_changed();

private:
    void setPartyName(const QString& name);
    bool isPartyStarted();

    bool m_party_started = false;
    bool m_user_missing = true;
    QString m_party_title;

    DatabaseControllerInterface* databaseController{nullptr};
    QList<drinq::models::Party2*> m_parties;
    drinq::models::Party2* m_current_party;
    PartyController* partyController{nullptr};
    QSettings* m_settings{nullptr};
};

}
}
#endif // MASTERCONTROLLER_H
