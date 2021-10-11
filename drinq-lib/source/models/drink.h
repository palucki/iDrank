#ifndef DRINK_H
#define DRINK_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <drinq-lib_global.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>
#include <models/address.h>
#include <models/appointment.h>
#include <models/contact.h>

#include "drinq-lib_global.h"

namespace drinq {
namespace models {

class DRINQLIB_EXPORT Client : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY( drinq::data::StringDecorator* ui_reference MEMBER reference CONSTANT )
    Q_PROPERTY( drinq::data::StringDecorator* ui_name MEMBER name CONSTANT )
    Q_PROPERTY( drinq::models::Address* ui_supplyAddress MEMBER supplyAddress CONSTANT )
    Q_PROPERTY( drinq::models::Address* ui_billingAddress MEMBER billingAddress CONSTANT )
    Q_PROPERTY( QQmlListProperty<drinq::models::Appointment> ui_appointments  READ ui_appointments NOTIFY appointmentsChanged )
    Q_PROPERTY( QQmlListProperty<drinq::models::Contact> ui_contacts READ ui_contacts NOTIFY contactsChanged )


public:
    explicit Client(QObject* parent = nullptr);
    Client(QObject* parent, const QJsonObject& json);
    ~Client();

    data::StringDecorator* reference{nullptr};
    data::StringDecorator* name{nullptr};
    Address* supplyAddress{nullptr};
    Address* billingAddress{nullptr};
    data::EntityCollection<Appointment>* appointments{nullptr};
    data::EntityCollection<Contact>* contacts{nullptr};

    Q_INVOKABLE QQmlListProperty<drinq::models::Appointment> ui_appointments();
    Q_INVOKABLE QQmlListProperty<drinq::models::Contact> ui_contacts();

public slots:
    void addContact();

signals:
    void appointmentsChanged();
    void contactsChanged();
};

//party

class DRINQLIB_EXPORT Party : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(drinq::data::StringDecorator* ui_title MEMBER title CONSTANT)
    Q_PROPERTY(drinq::data::StringDecorator* ui_notes MEMBER notes CONSTANT)
    Q_PROPERTY(drinq::data::DateTimeDecorator* ui_started MEMBER ended CONSTANT)
    Q_PROPERTY(drinq::data::DateTimeDecorator* ui_ended MEMBER ended CONSTANT)
public:
    explicit Party(QObject* parent = nullptr);
    Party(QObject* parent, const QJsonObject& json);
    ~Party();

    data::StringDecorator* id{nullptr};
    data::StringDecorator* title{nullptr};
    data::StringDecorator* notes{nullptr};
    data::DateTimeDecorator* started{nullptr};
    data::DateTimeDecorator* ended{nullptr};
};

//beverage

class DRINQLIB_EXPORT Beverage : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(drinq::data::StringDecorator* ui_name MEMBER name CONSTANT)
public:
    explicit Beverage(QObject* parent = nullptr);
    Beverage(QObject* parent, const QJsonObject& json);
    ~Beverage();

    data::StringDecorator* id{nullptr};
    data::StringDecorator* name{nullptr};
};

//player

class DRINQLIB_EXPORT Player : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(drinq::data::StringDecorator* ui_name MEMBER name CONSTANT)
    Q_PROPERTY(drinq::data::StringDecorator* ui_photo MEMBER photo CONSTANT)
public:
    explicit Player(QObject* parent = nullptr);
    Player(QObject* parent, const QJsonObject& json);
    ~Player();

    data::StringDecorator* id{nullptr};
    data::StringDecorator* name{nullptr};
    data::StringDecorator* photo{nullptr};
};

//drink

class DRINQLIB_EXPORT Drink : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY( drinq::data::IntDecorator* ui_amount_ml MEMBER amount_ml CONSTANT )
    Q_PROPERTY( drinq::data::DateTimeDecorator* ui_consumed MEMBER consumed CONSTANT )

public:
    explicit Drink(QObject* parent = nullptr);
    Drink(QObject* parent, const QJsonObject& json);
    ~Drink();

    data::StringDecorator* id{nullptr};
    data::StringDecorator* party_id{nullptr};
    data::StringDecorator* beverage_id{nullptr};
    data::StringDecorator* player_id{nullptr};
    data::IntDecorator* amount_ml{nullptr};
    data::DateTimeDecorator* consumed{nullptr};
};


}
}
#endif // DRINK_H
