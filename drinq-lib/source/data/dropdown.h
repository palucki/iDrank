#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <drinq-lib_global.h>
#include <data/dropdownvalue.h>

namespace drinq {
namespace data {

class DRINQLIB_EXPORT DropDown : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<drinq::data::DropDownValue> ui_values READ ui_values CONSTANT)
public:
    explicit DropDown(QObject* _parent = nullptr, const std::map<int,
                      QString>& values = std::map<int, QString>());
    ~DropDown();
public:
    QQmlListProperty<DropDownValue> ui_values();

public slots:
    QString findDescriptionForDropdownValue(int valueKey) const;
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // DROPDOWN_H
