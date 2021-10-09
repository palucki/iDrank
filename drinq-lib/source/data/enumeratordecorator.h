#ifndef ENUMERATORDECORATOR_H
#define ENUMERATORDECORATOR_H

#include <map>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QScopedPointer>
#include <drinq-lib_global.h>
#include <data/datadecorator.h>

namespace drinq {
namespace data {

class DRINQLIB_EXPORT EnumeratorDecorator : public DataDecorator
{
    Q_OBJECT
    Q_PROPERTY(int ui_value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString ui_valueDescription READ valueDescription NOTIFY valueChanged)

public:
    using DescriptionMapper = std::map<int, QString>;

    EnumeratorDecorator(Entity* parentEntity = nullptr, const QString& key = "SomeItemKey",
                        const QString& label = "", int value = 0,
                        const DescriptionMapper& descriptionMapper = DescriptionMapper());
    ~EnumeratorDecorator();
    EnumeratorDecorator& setValue(int value);
    int value() const;
    QString valueDescription() const;
    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;

signals:
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // ENUMERATORDECORATOR_H
