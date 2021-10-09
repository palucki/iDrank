#include "enumeratordecoratortests.h"

#include <QSignalSpy>

#include <data/entity.h>

enum eTestEnum {
    Unknown = 0,
    Value1,
    Value2,
    Value3
};

drinq::data::EnumeratorDecorator::DescriptionMapper testMapper {
    {Unknown, "Unknown"},
    {Value1, "Value 1"},
    {Value2, "Value 2"},
    {Value3, "Value 3"},
};

namespace drinq {
namespace data {



static EnumeratorDecoratorTests instance;

EnumeratorDecoratorTests::EnumeratorDecoratorTests() : TestSuite("EnumeratorDecoratorTests")
{
}

}

namespace data { // Tests
void
EnumeratorDecoratorTests::constructor_givenNoParameters_setsDefaultProperties()
{
    EnumeratorDecorator decorator;
    QCOMPARE(decorator.parentEntity(), nullptr);
    QCOMPARE(decorator.key(), QString("SomeItemKey"));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Unknown));
    QCOMPARE(decorator.valueDescription(), "");
}
void EnumeratorDecoratorTests::constructor_givenParameters_setsProperties()
{
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity, "Test Key", "Test Label", Unknown, testMapper);
    QCOMPARE(decorator.parentEntity(), &parentEntity);
    QCOMPARE(decorator.key(), QString("Test Key"));
    QCOMPARE(decorator.label(), QString("Test Label"));
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Unknown));
    QCOMPARE(decorator.valueDescription(), "Unknown");
}
void EnumeratorDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal()
{
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity, "Test Key", "Test Label", Unknown, testMapper);

    QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Unknown));
    QCOMPARE(decorator.valueDescription(), "Unknown");
    decorator.setValue(Value2);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
    QCOMPARE(decorator.valueDescription(), "Value 2");
    QCOMPARE(valueChangedSpy.count(), 1);
}
void EnumeratorDecoratorTests::setValue_givenSameValue_takesNoAction()
{
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity, "Test Key", "Test Label", Value3, testMapper);
    QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value3));
    QCOMPARE(decorator.valueDescription(), "Value 3");
    decorator.setValue(Value3);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value3));
    QCOMPARE(decorator.valueDescription(), "Value 3");
    QCOMPARE(valueChangedSpy.count(), 0);
}

void EnumeratorDecoratorTests::jsonValue_whenDefaultValue_returnsJson()
{
    EnumeratorDecorator decorator;
    QCOMPARE(decorator.jsonValue(), QJsonValue(Unknown));
}

void EnumeratorDecoratorTests::jsonValue_whenValueSet_returnsJson()
{
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity, "Test Key", "Test Label", Unknown, testMapper);
    decorator.setValue(Value1);
    QCOMPARE(decorator.jsonValue(), QJsonValue(Value1));
}

void EnumeratorDecoratorTests::update_whenPresentInJson_updatesValue()
{
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity, "Test Key", "Test Label", Unknown, testMapper);
    QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Unknown));
    QCOMPARE(decorator.valueDescription(), "Unknown");
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Test Key", Value3);
    jsonObject.insert("Key 3", "BBB");
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value3));
    QCOMPARE(decorator.valueDescription(), "Value 3");
    QCOMPARE(valueChangedSpy.count(), 1);
}

void EnumeratorDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault()
{
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity, "Test Key", "Test Label", Value2, testMapper);
    QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
    QCOMPARE(decorator.valueDescription(), "Value 2");
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Key 2", 123);
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Unknown));
    QCOMPARE(decorator.valueDescription(), "Unknown");
    QCOMPARE(valueChangedSpy.count(), 1);
}

}
}
