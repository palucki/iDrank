#include "dropdown.h"

namespace drinq {
namespace data {

class DropDown::Implementation
{
public:
    Implementation(DropDown* _dropdown, const std::map<int, QString>&
_values)
        : dropdown(_dropdown)
    {
        for(auto pair : _values) {
             values.append(new DropDownValue(_dropdown, pair.first,
pair.second));
        }
    }
    DropDown* dropdown{nullptr};
    QList<DropDownValue*> values;
};

DropDown::DropDown(QObject *_parent, const std::map<int, QString> &values)
    : QObject(_parent)
{
    implementation.reset(new DropDown::Implementation(this, values));
}

DropDown::~DropDown()
{

}

QQmlListProperty<DropDownValue> DropDown::ui_values()
{
    return QQmlListProperty<DropDownValue>(this, implementation->values);
}

QString DropDown::findDescriptionForDropdownValue(int valueKey) const
{
    for (auto value : implementation->values) {
            if (value->key() == valueKey) {
                if(!value->description().isEmpty()) {
                    return value->description();
                }
                break;
            }
        }
        return "Select >";
}




}
}
