#ifndef RECENTACTIVITY_H
#define RECENTACTIVITY_H

#include <QtQml/QQmlListProperty>
#include <QScopedPointer>
#include <drinq-lib_global.h>
#include <controllers/databasecontrollerinterface.h>
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entitycollection.h>
#include <models/drink.h>

namespace drinq {
namespace models {

class DRINQLIB_EXPORT RecentActivity : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<drinq::models::Drink> ui_recentActivity READ ui_recentActivity
                                                                        NOTIFY recentActivitiesChanged )
public:
    RecentActivity(QObject* parent = nullptr, controllers::DatabaseControllerInterface* databaseController = nullptr);
    ~RecentActivity();
    QQmlListProperty<Drink> ui_recentActivity();
    void load();
signals:
    void recentActivitiesChanged();
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // RECENTACTIVITY_H
