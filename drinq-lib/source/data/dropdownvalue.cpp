#include "dropdownvalue.h"

namespace drinq {
namespace data {

DropDownValue::DropDownValue(QObject *parent, int key, const QString &description)
 : QObject(parent)
 , m_key(key)
 , m_description(description)
{

}

DropDownValue::~DropDownValue()
{
}

int DropDownValue::key()
{
    return m_key;
}

QString DropDownValue::description()
{
    return m_description;
}

}
}
