#include "datetimedecoratortests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace drinq {
namespace data {

static DateTimeDecoratorTests instance;

DateTimeDecoratorTests::DateTimeDecoratorTests() : TestSuite("DateTimeDecoratorTests")
{
}

}

namespace data { // Tests
void
DateTimeDecoratorTests::constructor_givenNoParameters_setsDefaultProperties()
{
    DateTimeDecorator decorator;
    QCOMPARE(decorator.parentEntity(), nullptr);
    QCOMPARE(decorator.key(), QString("SomeItemKey"));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), QDateTime{});
}
void DateTimeDecoratorTests::constructor_givenParameters_setsProperties()
{
    Entity parentEntity;
    DateTimeDecorator decorator(&parentEntity, "Test Key", "Test Label", QDateTime{QDate{1999,1,2}, QTime{22,2,3}});
    QCOMPARE(decorator.parentEntity(), &parentEntity);
    QCOMPARE(decorator.key(), QString("Test Key"));
    QCOMPARE(decorator.label(), QString("Test Label"));
    QCOMPARE(decorator.value(), (QDateTime{QDate{1999,1,2}, QTime{22,2,3}}));
}
void DateTimeDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal()
{
    DateTimeDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(), QDateTime());
    decorator.setValue(QDateTime{QDate{2011,1,2}, QTime{22,2,3}});
    QCOMPARE(decorator.value(), (QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
    QCOMPARE(valueChangedSpy.count(), 1);
}
void DateTimeDecoratorTests::setValue_givenSameValue_takesNoAction()
{
    Entity parentEntity;
    DateTimeDecorator decorator(&parentEntity, "Test Key", "Test Label", (QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(), (QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
    decorator.setValue((QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
    QCOMPARE(decorator.value(), (QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
    QCOMPARE(valueChangedSpy.count(), 0);
}

void DateTimeDecoratorTests::jsonValue_whenDefaultValue_returnsJson()
{
    DateTimeDecorator decorator;
    QCOMPARE(decorator.jsonValue(), QJsonValue());
}
void DateTimeDecoratorTests::jsonValue_whenValueSet_returnsJson()
{
    DateTimeDecorator decorator;
    decorator.setValue((QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
//    QCOMPARE(decorator.jsonValue(), (QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
}
void DateTimeDecoratorTests::update_whenPresentInJson_updatesValue()
{
    Entity parentEntity;
    DateTimeDecorator decorator(&parentEntity, "Test Key", "Test Label", (QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(), (QDateTime{QDate{2011,1,2}, QTime{22,2,3}}));
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Test Key", QJsonValue::fromVariant(QDateTime{QDate{1970,1,2}, QTime{22,2,3}}));
    jsonObject.insert("Key 3", "BBB");
    decorator.update(jsonObject);
//    QCOMPARE(decorator.value(), (QDateTime{QDate{1970,1,2}, QTime{22,2,3}}));
    QCOMPARE(valueChangedSpy.count(), 1);
}
void DateTimeDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault()
{
    Entity parentEntity;
    DateTimeDecorator decorator(&parentEntity, "Test Key", "Test Label", QDateTime{QDate{1970,1,2}, QTime{22,2,3}});
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(), (QDateTime{QDate{1970,1,2}, QTime{22,2,3}}));
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Key 2", QJsonValue::fromVariant(QDateTime{QDate{1970,1,2}, QTime{22,2,3}}));
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
//    QCOMPARE(decorator.value(), "");
    QCOMPARE(valueChangedSpy.count(), 1);
}

}
}
