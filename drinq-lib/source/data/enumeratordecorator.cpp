#include "enumeratordecorator.h"

#include <QVariant>
#include <QDebug>

namespace drinq {
namespace data {

class EnumeratorDecorator::Implementation
{
public:
    Implementation(EnumeratorDecorator* _EnumeratorDecorator, int _value, const DescriptionMapper& dm )
        : enumeratorDecorator(_EnumeratorDecorator), value(_value), descriptionMapper(dm)
    {}

    EnumeratorDecorator* enumeratorDecorator{nullptr};
    int value;
    DescriptionMapper descriptionMapper;
};

EnumeratorDecorator::EnumeratorDecorator(Entity* parentEntity, const QString& key,
                                         const QString& label, int value, const DescriptionMapper &descriptionMapper)
    : DataDecorator(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value, descriptionMapper));
}

EnumeratorDecorator::~EnumeratorDecorator()
{
}

int EnumeratorDecorator::value() const
{
    return implementation->value;
}

QString EnumeratorDecorator::valueDescription() const
{
    if (implementation->descriptionMapper.find(implementation->value) != implementation->descriptionMapper.end())
    {
        return implementation->descriptionMapper.at(implementation->value);
    }
    else
    {
        return {};
    }
}

EnumeratorDecorator& EnumeratorDecorator::setValue(int value)
{
    if(value != implementation->value) {
        // ...Validation here if required...
        implementation->value = value;
        qDebug() << "VALUE CHANGED";
        emit valueChanged();
    }
    return *this;
}

QJsonValue EnumeratorDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void EnumeratorDecorator::update(const QJsonObject& _jsonObject)
{
    if (_jsonObject.contains(key())) {
        setValue(_jsonObject.value(key()).toInt());
    } else {
        setValue(0);
    }
}

}}
