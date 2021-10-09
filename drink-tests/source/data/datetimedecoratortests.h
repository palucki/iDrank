#ifndef DATETIMEDECORATORTESTS_H
#define DATETIMEDECORATORTESTS_H

#include <QTest>

#include <data/datetimedecorator.h>
#include <testsuite.h>

namespace drinq {
namespace data {

class DateTimeDecoratorTests : public TestSuite
{
    Q_OBJECT
public:
    DateTimeDecoratorTests();
private slots:
    void constructor_givenNoParameters_setsDefaultProperties();
    void constructor_givenParameters_setsProperties();
    void setValue_givenNewValue_updatesValueAndEmitsSignal();
    void setValue_givenSameValue_takesNoAction();
    void jsonValue_whenDefaultValue_returnsJson();
    void jsonValue_whenValueSet_returnsJson();
    void update_whenPresentInJson_updatesValue();
    void update_whenNotPresentInJson_updatesValueToDefault();
};

}
}

#endif // DATETIMEDECORATORTESTS_H
