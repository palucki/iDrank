#include "stringdecoratortests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace drinq {
namespace data {

static StringDecoratorTests instance;

StringDecoratorTests::StringDecoratorTests() : TestSuite("StringDecoratorTests")
{
}

}

namespace data { // Tests
void
StringDecoratorTests::constructor_givenNoParameters_setsDefaultProperties()
{
    StringDecorator decorator;
    QCOMPARE(decorator.parentEntity(), nullptr);
    QCOMPARE(decorator.key(), QString("SomeItemKey"));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), "");
}
void StringDecoratorTests::constructor_givenParameters_setsProperties()
{
    Entity parentEntity;
    StringDecorator decorator(&parentEntity, "Test Key", "Test Label", "VALUE");
    QCOMPARE(decorator.parentEntity(), &parentEntity);
    QCOMPARE(decorator.key(), QString("Test Key"));
    QCOMPARE(decorator.label(), QString("Test Label"));
    QCOMPARE(decorator.value(), QString("VALUE"));
}
void StringDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal()
{
    StringDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator,
                               &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), "");
    decorator.setValue("TEST");
    QCOMPARE(decorator.value(), QString("TEST"));
    QCOMPARE(valueChangedSpy.count(), 1);
}
void StringDecoratorTests::setValue_givenSameValue_takesNoAction()
{
    Entity parentEntity;
    StringDecorator decorator(&parentEntity, "Test Key", "Test Label", "TST");
    QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), "TST");
    decorator.setValue("TST");
    QCOMPARE(decorator.value(), "TST");
    QCOMPARE(valueChangedSpy.count(), 0);
}

void StringDecoratorTests::jsonValue_whenDefaultValue_returnsJson()
{
    StringDecorator decorator;
    QCOMPARE(decorator.jsonValue(), QJsonValue(""));
}
void StringDecoratorTests::jsonValue_whenValueSet_returnsJson()
{
    StringDecorator decorator;
    decorator.setValue("STRING");
    QCOMPARE(decorator.jsonValue(), QJsonValue("STRING"));
}
void StringDecoratorTests::update_whenPresentInJson_updatesValue()
{
    Entity parentEntity;
    StringDecorator decorator(&parentEntity, "Test Key", "Test Label", "INITIAL");
    QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), "INITIAL");
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Test Key", "AAA");
    jsonObject.insert("Key 3", "BBB");
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), "AAA");
    QCOMPARE(valueChangedSpy.count(), 1);
}
void StringDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault()
{
    Entity parentEntity;
    StringDecorator decorator(&parentEntity, "Test Key", "Test Label", "INIT");
    QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), "INIT");
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Key 2", 123);
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), "");
    QCOMPARE(valueChangedSpy.count(), 1);
}

}
}
