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
    data::EntityCollection<Party>* recentParties{nullptr};
};

RecentActivity::RecentActivity(QObject *parent, controllers::DatabaseControllerInterface *databaseController)
    : Entity(parent, "RecentActivity")
{
    implementation.reset(new Implementation(this, databaseController));
    implementation->recentParties = static_cast<EntityCollection<Party>*>(
                addChildCollection(new EntityCollection<Party>(this, "recentParties")));

    connect(implementation->recentParties, &EntityCollection<Party>::collectionChanged, this,
            &RecentActivity::recentActivitiesChanged);
}

RecentActivity::~RecentActivity()
{
}

QQmlListProperty<Party> RecentActivity::ui_recentActivity()
{
    return QQmlListProperty<Party>(this, implementation->recentParties->derivedEntities());
}

void RecentActivity::load()
{
    qDebug() << "Loading recent activities";
    auto resultsArray = implementation->databaseController->find("party", "");
    implementation->recentParties->update(resultsArray);
    qDebug() << "Found " << implementation->recentParties->baseEntities().size() << " matches";
}

}
}
