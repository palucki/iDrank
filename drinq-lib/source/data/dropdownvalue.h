#ifndef DROPDOWNVALUE_H
#define DROPDOWNVALUE_H

#include <QObject>
#include <drinq-lib_global.h>

namespace drinq {
namespace data {

class DRINQLIB_EXPORT DropDownValue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ui_key READ key CONSTANT)
    Q_PROPERTY(QString ui_description READ description CONSTANT)
public:
    explicit DropDownValue(QObject *parent = nullptr, int key = 0, const QString& description = "");
    ~DropDownValue();
    int key();
    QString description();

private:
    int m_key{0};
    QString m_description{""};

};

}
}

#endif // DROPDOWNVALUE_H
