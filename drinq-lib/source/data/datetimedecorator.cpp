#include "datetimedecorator.h"

#include <QVariant>

namespace drinq {
namespace data {

class DateTimeDecorator::Implementation
{
public:
    Implementation(DateTimeDecorator* _DateTimeDecorator, const QDateTime& _value)
        : DateTimeDecorator(_DateTimeDecorator), value(_value)
    {}

    DateTimeDecorator* DateTimeDecorator{nullptr};
    QDateTime value;
};

DateTimeDecorator::DateTimeDecorator(Entity* parentEntity, const QString& key,
                                     const QString& label, const QDateTime& value)
    : DataDecorator(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value));
}

DateTimeDecorator::~DateTimeDecorator()
{
}

const QDateTime& DateTimeDecorator::value() const
{
    return implementation->value;
}

QString DateTimeDecorator::toIso8601String() const
{
    if (implementation->value.isNull())
    {
        return "";
    }
    else
    {
        return implementation->value.toString(Qt::ISODate);
    }
}

QString DateTimeDecorator::toPrettyDateString() const
{
    if (implementation->value.isNull())
    {
        return "Not set";
    }
    else
    {
        return implementation->value.toString( "d MMM yyyy" );
    }
}

QString DateTimeDecorator::toPrettyTimeString() const
{
    if (implementation->value.isNull())
    {
        return "Not set";
    }
    else
    {
        return implementation->value.toString( "HH:mm" );
    }
}

QString DateTimeDecorator::toPrettyString() const
{
    if (implementation->value.isNull())
    {
        return "Not set";
    }
    else
    {
        return implementation->value.toString( "ddd d MMM yyyy @ HH:mm:ss");
    }
}

DateTimeDecorator& DateTimeDecorator::setValue(const QDateTime& value)
{
    if(value != implementation->value)
    {
        // ...Validation here if required...
        implementation->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue DateTimeDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void DateTimeDecorator::update(const QJsonObject& _jsonObject)
{
    if (_jsonObject.contains(key()))
    {
        setValue(_jsonObject.value(key()).toVariant().toDateTime());
    }
    else
    {
        setValue({});
    }
}

}}
