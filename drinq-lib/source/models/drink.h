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



//beverage

//class DRINQLIB_EXPORT Beverage : public data::Entity
//{
//    Q_OBJECT
//    Q_PROPERTY(drinq::data::StringDecorator* ui_name MEMBER name CONSTANT)
//public:
//    explicit Beverage(QObject* parent = nullptr);
//    Beverage(QObject* parent, const QJsonObject& json);
//    ~Beverage();

//    data::StringDecorator* id{nullptr};
//    data::StringDecorator* name{nullptr};
//};

//player

//class DRINQLIB_EXPORT Player : public data::Entity
//{
//    Q_OBJECT
//    Q_PROPERTY(drinq::data::StringDecorator* ui_name MEMBER name CONSTANT)
//    Q_PROPERTY(drinq::data::StringDecorator* ui_photo MEMBER photo CONSTANT)
//public:
//    explicit Player(QObject* parent = nullptr);
//    Player(QObject* parent, const QJsonObject& json);
//    ~Player();

//    data::StringDecorator* id{nullptr};
//    data::StringDecorator* name{nullptr};
//    data::StringDecorator* photo{nullptr};
//};

//drink

class DRINQLIB_EXPORT Drink2 : public data::EntityLite
{
    Q_OBJECT
    Q_PROPERTY(QDateTime ui_timestamp MEMBER m_timestamp CONSTANT)
    Q_PROPERTY(unsigned int ui_amount_ml MEMBER m_amount_ml CONSTANT)

public:
    explicit Drink2(QObject* parent = nullptr);
    Drink2(const QJsonObject& json, QObject* parent = nullptr);
    ~Drink2();

    void setDrinkTypeId(const QVariant& id) { m_data["drink_type_id"] = id; m_drink_type_id = id; }
    void setPartyId(const QVariant& id) { m_data["party_id"] = id; m_party_id = id;}
    void setAmountMl(unsigned int a) { m_data["amount_ml"] = a; m_amount_ml = a;}
    void setTimestamp(const QDateTime& ts) { m_data["timestamp"] = ts; m_timestamp = ts;}

    void update(const QJsonObject& src) override;

private:
    QVariant m_drink_type_id{};
    QVariant m_party_id{};
    QDateTime m_timestamp{};
    unsigned int m_amount_ml{0};
};

class DRINQLIB_EXPORT DrinkType : public data::EntityLite
{
    Q_OBJECT
    Q_PROPERTY(QString ui_name MEMBER m_name CONSTANT)
    Q_PROPERTY(unsigned int ui_default_amount_ml MEMBER m_default_amount_ml CONSTANT)
public:
    explicit DrinkType(QObject* parent = nullptr);
    DrinkType(const QJsonObject& json, QObject* parent = nullptr);
    ~DrinkType();

    void setName(const QString& name) { m_data["name"] = name; m_name = name;}
    void setDefaultAmountMl(unsigned int a) { m_data["default_amount_ml"] = a; m_default_amount_ml = a; }

    void update(const QJsonObject& src) override;

public:
    QString m_name{};
    unsigned int m_default_amount_ml{0};
};


class DRINQLIB_EXPORT Party2 : public data::EntityLite
{
    Q_OBJECT
    Q_PROPERTY(QString ui_name MEMBER m_name CONSTANT)
    Q_PROPERTY(QDateTime ui_started MEMBER m_started CONSTANT)
    Q_PROPERTY(QDateTime ui_ended MEMBER m_ended CONSTANT)

public:
    explicit Party2(QObject* parent = nullptr);
    Party2(const QJsonObject& json, QObject* parent = nullptr);
    ~Party2();

    void setName(const QString& name) { m_data["name"] = name; m_name = name; }
    void setStarted(QDateTime ts) { m_data["started"] = ts; m_started = ts;}
    void setEnded(QDateTime ts) { m_data["ended"] = ts; m_ended = ts;}

    void update(const QJsonObject& src) override;
public:
    QString m_name{};
    QDateTime m_started{};
    QDateTime m_ended{};
};

class DRINQLIB_EXPORT Drink : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(drinq::data::EnumeratorDecorator* ui_beverage MEMBER beverage CONSTANT )
    Q_PROPERTY(drinq::data::IntDecorator* ui_amount_ml MEMBER amount_ml CONSTANT )
    Q_PROPERTY(drinq::data::DateTimeDecorator* ui_consumed MEMBER consumed CONSTANT )
    Q_PROPERTY(drinq::data::DropDown* ui_beverageDropDown MEMBER dropDown CONSTANT)

public:
    enum eBeverage {
        Other = 0,
        Beer,
        Vodka,
        Wine
    };
    Q_ENUM(eBeverage)

    static std::map<int, QString> beverageMapper;

    explicit Drink(QObject* parent = nullptr);
    Drink(QObject* parent, const QJsonObject& json);
    ~Drink();

    Q_INVOKABLE int ui_defaultAmount(eBeverage beverageType);

    data::StringDecorator* reference{nullptr};
    data::EnumeratorDecorator* beverage{nullptr};
    drinq::data::DropDown* dropDown{nullptr};
    data::IntDecorator* amount_ml{nullptr};
    data::DateTimeDecorator* consumed{nullptr};
};

class DRINQLIB_EXPORT Party : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(drinq::data::StringDecorator* ui_title MEMBER title CONSTANT)
    Q_PROPERTY(drinq::data::StringDecorator* ui_notes MEMBER notes CONSTANT)
    Q_PROPERTY(drinq::data::DateTimeDecorator* ui_started MEMBER started CONSTANT)
    Q_PROPERTY(drinq::data::DateTimeDecorator* ui_ended MEMBER ended CONSTANT)
    Q_PROPERTY(QQmlListProperty<drinq::models::Drink> ui_drinks READ ui_drinks NOTIFY drinksChanged )

    Q_PROPERTY(int ui_amount_consumed READ ui_amount_consumed CONSTANT )

public:
    explicit Party(QObject* parent = nullptr);
    Party(QObject* parent, const QJsonObject& json);
    ~Party();

    data::StringDecorator* reference{nullptr};
    data::StringDecorator* title{nullptr};
    data::StringDecorator* notes{nullptr};
    data::DateTimeDecorator* started{nullptr};
    data::DateTimeDecorator* ended{nullptr};
    data::EntityCollection<drinq::models::Drink>* drinks{nullptr};

    Q_INVOKABLE QQmlListProperty<drinq::models::Drink> ui_drinks();
    Q_INVOKABLE int ui_amount_consumed();

public slots:
    void addDrink();

signals:
    void drinksChanged();
};

}
}
#endif // DRINK_H
