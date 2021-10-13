#include "recentactivity.h"
#include <QDebug>

using namespace drinq::controllers;
using namespace drinq::data;

namespace drinq {
namespace models {

class RecentActivity::Implementation
{
public:
    Implementation(RecentActivity* _recentActivity, DatabaseControllerInterface* _databaseController)
        : recentActivity(_recentActivity)
        , databaseController(_databaseController)
    {
    }

    RecentActivity* recentActivity{nullptr};
    DatabaseControllerInterface* databaseController{nullptr};
    data::EntityCollection<Drink>* recentDrinks{nullptr};
};

RecentActivity::RecentActivity(QObject *parent, controllers::DatabaseControllerInterface *databaseController)
    : Entity(parent, "RecentActivity")
{
    implementation.reset(new Implementation(this, databaseController));
    implementation->recentDrinks = static_cast<EntityCollection<Drink>*>(
                addChildCollection(new EntityCollection<Drink>(this, "recentDrinks")));

    connect(implementation->recentDrinks, &EntityCollection<Drink>::collectionChanged, this,
            &RecentActivity::recentActivitiesChanged);
}

RecentActivity::~RecentActivity()
{
}

QQmlListProperty<Drink> RecentActivity::ui_recentActivity()
{
    return QQmlListProperty<Drink>(this, implementation->recentDrinks->derivedEntities());
}

void RecentActivity::load()
{
    qDebug() << "Loading recent activities";
    auto resultsArray = implementation->databaseController->find("drink", "");
    implementation->recentDrinks->update(resultsArray);
    qDebug() << "Found " << implementation->recentDrinks->baseEntities().size() << " matches";
}

}
}
