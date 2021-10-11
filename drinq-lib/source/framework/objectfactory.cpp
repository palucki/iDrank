#include "objectfactory.h"

#include <controllers/commandcontroller.h>
#include <controllers/navigationcontroller.h>
#include <controllers/databasecontroller.h>

using namespace drinq::controllers;

namespace drinq {
namespace framework {

ObjectFactory::~ObjectFactory()
{
}

Client *ObjectFactory::createClient(QObject *parent) const
{
    return new Client(parent);
}

ClientSearch *ObjectFactory::createClientSearch(QObject *parent, controllers::DatabaseControllerInterface *databaseController) const
{
    return new ClientSearch(parent, databaseController);
}

RecentActivity *ObjectFactory::createRecentActivity(QObject *parent, controllers::DatabaseControllerInterface *databaseController) const
{
    return new RecentActivity(parent, databaseController);
}

controllers::CommandControllerInterface* ObjectFactory::createCommandController(QObject *parent,
                                                                                controllers::DatabaseControllerInterface *databaseController,
                                                                                controllers::NavigationControllerInterface *navigationController,
                                                                                Client *newClient,
                                                                                ClientSearch *clientSearch,
                                                                                RecentActivity* recentActivity) const
{
    return new CommandController(parent, databaseController, newClient, clientSearch, recentActivity, navigationController);
}

controllers::DatabaseControllerInterface *ObjectFactory::createDatabaseController(QObject *parent) const
{
    return new DatabaseController(parent);
}

controllers::NavigationControllerInterface *ObjectFactory::createNavigationController(QObject *parent) const
{
    return new NavigationController(parent);
}

}
}
