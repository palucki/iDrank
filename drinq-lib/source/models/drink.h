#ifndef DRINK_H
#define DRINK_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <drinq-lib_global.h>
#include <data/stringdecorator.h>
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

}
}
#endif // DRINK_H
