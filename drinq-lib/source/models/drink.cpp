#include "drink.h"
#include <QDebug>

using namespace drinq::data;

namespace drinq {
namespace models {

Client::Client(QObject* parent)
    : Entity(parent, "client")
{
    reference = static_cast<StringDecorator*>(addDataItem(new
                                                          StringDecorator(this, "reference", "Client Ref")));
    name = static_cast<StringDecorator*>(addDataItem(new
                                                     StringDecorator(this, "name", "Name")));
    supplyAddress = static_cast<Address*>(addChild(new Address(this),
                                                   "supplyAddress"));
    billingAddress = static_cast<Address*>(addChild(new Address(this),
                                                    "billingAddress"));
    appointments = static_cast<EntityCollection<Appointment>*>
            (addChildCollection(new EntityCollection<Appointment>(this,
                                                                  "appointments")));
    contacts = static_cast<EntityCollection<Contact>*>(addChildCollection(new EntityCollection<Contact>(this, "contacts")));

    setPrimaryKey(reference);
}

Client::Client(QObject* parent, const QJsonObject& json)
    : Client(parent)
{
    update(json);
}

Client::~Client()
{
}

void Client::addContact()
{
    contacts->addEntity(new Contact(this));
    emit contactsChanged();
}

QQmlListProperty<Appointment> Client::ui_appointments()
{
    return QQmlListProperty<Appointment>(this, appointments->derivedEntities());
}
QQmlListProperty<Contact> Client::ui_contacts()
{
    return QQmlListProperty<Contact>(this, contacts->derivedEntities());
}

Party::Party(QObject *parent) : Entity(parent, "party")
{
    reference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "ref", "Ref")));
    title = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "title", "Title")));
    notes = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "notes", "Notes")));
    started = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "started", "Started")));
    ended = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "ended", "Started")));
    drinks = static_cast<EntityCollection<Drink>*>(addChildCollection(new EntityCollection<Drink>(this, "drinks")));

//    setPrimaryKey(reference);
}

Party::Party(QObject *parent, const QJsonObject &json) : Party(parent)
{
    update(json);
}

Party::~Party()
{
}

QQmlListProperty<Drink> Party::ui_drinks()
{
    return QQmlListProperty<Drink>(this, drinks->derivedEntities());
}

int Party::ui_amount_consumed()
{
    const auto add_amount = [](int sum, drinq::models::Drink* d) {
        return sum + d->amount_ml->value();
    };

    const int amount = std::accumulate(drinks->derivedEntities().begin(), drinks->derivedEntities().end(), 0, add_amount);
    return amount;
}

void Party::addDrink()
{
    drinks->addEntity(new Drink(this));
    emit drinksChanged();
}

//Beverage::Beverage(QObject *parent) : Entity(parent, "beverage")
//{
//    id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "id", "Id")));
//    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Name")));

//    setPrimaryKey(id);
//}

//Beverage::Beverage(QObject *parent, const QJsonObject &json) : Beverage(parent)
//{
//    update(json);
//}

//Beverage::~Beverage()
//{
//}

//Player::Player(QObject *parent) : Entity(parent, "player")
//{
//    id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "id", "Id")));
//    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Name")));
//    photo = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "photo", "Photo")));

//    setPrimaryKey(id);
//}

//Player::Player(QObject *parent, const QJsonObject &json) : Player(parent)
//{
//    update(json);
//}

//Player::~Player()
//{
//}

std::map<int, QString> Drink::beverageMapper = std::map<int, QString>
{
    //TODO: add default amount here, always in ml and calculate later!!!
      { Drink::eBeverage::Other, "Other" }
    , { Drink::eBeverage::Beer, "Beer" }
    , { Drink::eBeverage::Vodka, "Vodka" }
    , { Drink::eBeverage::Wine, "Wine" }
};


Drink::Drink(QObject *parent) : Entity(parent, "drink")
{
    reference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "ref", "Ref")));
    beverage = static_cast<EnumeratorDecorator*>(addDataItem(new EnumeratorDecorator(this, "beverage", "Beverage", Drink::eBeverage::Beer, beverageMapper)));
    amount_ml = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "amount_ml", "Amount")));
    consumed = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "consumed", "Consumed")));
    dropDown = new DropDown(this, beverageMapper);
//    setPrimaryKey(reference);
}

Drink::Drink(QObject *parent, const QJsonObject &json) : Drink(parent)
{
    update(json);
}

Drink::~Drink()
{
}

int Drink::ui_defaultAmount(eBeverage beverageType)
{
    switch(beverageType)
    {
        case eBeverage::Beer: return 500;
        case eBeverage::Vodka: return 25;
        case eBeverage::Wine: return 100;
        case eBeverage::Other: return 0;
        default: return 0;
    }
}

Drink2::Drink2(QObject* parent) : EntityLite("drink", parent), m_timestamp(QDateTime::currentDateTime())
{
    addField("drink_type_id", m_drink_type_id);
    addField("party_id", m_party_id);
    addField("timestamp", m_timestamp);
    addField("amount_ml", m_amount_ml);
}

Drink2::Drink2(const QJsonObject &json, QObject* parent) : Drink2(parent)
{
    update(json);
}

Drink2::~Drink2()
{
}

void Drink2::update(const QJsonObject &src)
{
    setDrinkTypeId(src["drink_type_id"]);
    setPartyId(src["party_id"]);
    setAmountMl(src["amount_ml"].toInt());
    setTimestamp(QDateTime::fromString(src["timestamp"].toString(), Qt::ISODate));
}

Party2::Party2(QObject *parent) : EntityLite("party", parent), m_started(QDateTime::currentDateTime())
{
    addField("name", m_name);
    addField("started", m_started);
    addField("ended", m_ended);
}

Party2::Party2(const QJsonObject &json, QObject *parent) : Party2(parent)
{
   update(json);
}

Party2::~Party2()
{

}

void Party2::update(const QJsonObject &src)
{
    setName(src["name"].toString());
    setStarted(QDateTime::fromString(src["started"].toString(), Qt::ISODate));
    setEnded(QDateTime::fromString(src["ended"].toString(), Qt::ISODate));
}

DrinkType::DrinkType(QObject *parent) : EntityLite("drink_type", parent)
{
    addField("name", m_name);
    addField("default_amount_ml", m_default_amount_ml);
}

DrinkType::DrinkType(const QJsonObject &json, QObject *parent) : DrinkType(parent)
{
    qDebug() << "JSON " << json;
    update(json);
}

DrinkType::~DrinkType()
{
}

void DrinkType::update(const QJsonObject &src)
{
    setName(src["name"].toString());
    setDefaultAmountMl(src["default_amount_ml"].toInt());
}

}}

