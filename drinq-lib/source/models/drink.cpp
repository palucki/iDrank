#include "drink.h"

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
    id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "id", "Id")));
    title = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "title", "Title")));
    notes = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "notes", "Notes")));
    started = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "started", "Started")));
    ended = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "ended", "Started")));

    setPrimaryKey(id);
}

Party::Party(QObject *parent, const QJsonObject &json) : Party(parent)
{
    update(json);
}

Party::~Party()
{
}

Beverage::Beverage(QObject *parent) : Entity(parent, "beverage")
{
    id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "id", "Id")));
    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Name")));

    setPrimaryKey(id);
}

Beverage::Beverage(QObject *parent, const QJsonObject &json) : Beverage(parent)
{
    update(json);
}

Beverage::~Beverage()
{
}

Player::Player(QObject *parent) : Entity(parent, "player")
{
    id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "id", "Id")));
    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Name")));
    photo = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "photo", "Photo")));

    setPrimaryKey(id);
}

Player::Player(QObject *parent, const QJsonObject &json) : Player(parent)
{
    update(json);
}

Player::~Player()
{
}

Drink::Drink(QObject *parent) : Entity(parent, "drink")
{
    id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "id", "Id")));
    party_id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "party_id", "Party Id")));
    beverage_id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "beverage_id", "Beverage Id")));
    player_id = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "player_id", "Player Id")));
    amount_ml = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "amount_ml", "Amount")));
    consumed = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "consumed", "Consumed")));

    setPrimaryKey(id);
}

Drink::Drink(QObject *parent, const QJsonObject &json) : Drink(parent)
{
    update(json);
}

Drink::~Drink()
{
}

}}

