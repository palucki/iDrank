#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <drinq-lib_global.h>
#include "objectfactoryinterface.h"

namespace drinq {
namespace framework {

class DRINQLIB_EXPORT ObjectFactory : public ObjectFactoryInterface
{

public:
    virtual ~ObjectFactory() override;
    models::Client* createClient(QObject* parent) const override;
    models::Party* createParty(QObject* parent) const override;
    models::Drink* createDrink(QObject* parent) const override;
    models::ClientSearch* createClientSearch(QObject* parent,
                                             controllers::DatabaseControllerInterface* databaseController) const override;

    models::RecentActivity* createRecentActivity(QObject* parent,
                                               controllers::DatabaseControllerInterface* databaseController) const override;

    controllers::CommandControllerInterface* createCommandController(QObject* parent,
                                                                     controllers::DatabaseControllerInterface* databaseController,
                                                                     controllers::NavigationControllerInterface* navigationController,
                                                                     models::Client* newClient,
                                                                     models::Party* newParty,
                                                                     models::ClientSearch*  clientSearch,
                                                                     models::RecentActivity* recentActivity
                                                                     /*, networking::IWebRequest* rssWebRequest*/) const override;
    controllers::DatabaseControllerInterface* createDatabaseController(QObject* parent) const override;
    controllers::NavigationControllerInterface* createNavigationController(QObject* parent) const override;
};

}}

#endif // OBJECTFACTORY_H
