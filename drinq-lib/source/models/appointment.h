#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QObject>
#include <drinq-lib_global.h>
#include <data/datetimedecorator.h>
#include <data/stringdecorator.h>
#include <data/entity.h>

namespace drinq {
namespace models {

class DRINQLIB_EXPORT Appointment : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(drinq::data::DateTimeDecorator* ui_startAt MEMBER startAt CONSTANT)
    Q_PROPERTY(drinq::data::DateTimeDecorator* ui_endAt MEMBER endAt CONSTANT)
    Q_PROPERTY(drinq::data::StringDecorator* ui_notes MEMBER notes CONSTANT)
public:
    explicit Appointment(QObject* parent = nullptr);
    Appointment(QObject* parent, const QJsonObject& json);
    data::DateTimeDecorator* startAt{nullptr};
    data::DateTimeDecorator* endAt{nullptr};
    data::StringDecorator* notes{nullptr};
};

}}

#endif // APPOINTMENT_H
