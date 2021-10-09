#include "appointment.h"

using namespace drinq::data;
namespace drinq {
namespace models {
Appointment::Appointment(QObject* parent)
    : Entity(parent, "appointment")
{
    startAt  = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "startAt", "Start at")));
    endAt  = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "endAt", "End at")));
    notes = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "notes", "Notes")));
}

Appointment::Appointment(QObject* parent, const QJsonObject& json)
    : Appointment(parent)
{
    update(json);
}

}
}
