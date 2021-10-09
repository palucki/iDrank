#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <drinq-lib_global.h>
#include <data/enumeratordecorator.h>
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/dropdown.h>

namespace drinq {
namespace models {

class DRINQLIB_EXPORT Contact : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(drinq::data::EnumeratorDecorator* ui_contactType MEMBER contactType CONSTANT)
    Q_PROPERTY(drinq::data::StringDecorator* ui_address MEMBER address CONSTANT)
    Q_PROPERTY(drinq::data::DropDown* ui_contactTypeDropDown MEMBER dropDown CONSTANT)
public:
    enum eContactType {
        Unknown = 0,
        Telephone,
        Email,
        Fax
    };
    static std::map<int, QString> contactTypeMapper;

    explicit Contact(QObject* parent = nullptr);
    Contact(QObject* parent, const QJsonObject& json);
    drinq::data::EnumeratorDecorator* contactType{nullptr};
    drinq::data::StringDecorator* address{nullptr};
    drinq::data::DropDown* dropDown{nullptr};
};

}}

#endif // CONTACT_H
