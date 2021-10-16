#ifndef OBJECTFACTORYINTERFACE_H
#define OBJECTFACTORYINTERFACE_H


#include <controllers/navigationcontrollerinterface.h>
#include <controllers/commandcontrollerinterface.h>
#include <controllers/databasecontrollerinterface.h>
#include <models/drink.h>
#include <models/clientsearch.h>
#include <models/recentactivity.h>

namespace drinq {
namespace framework {

class DRINQLIB_EXPORT ObjectFactoryInterface
{
public:
    virtual ~ObjectFactoryInterface(){}

    virtual models::Client* createClient(QObject* parent) const = 0;
    virtual models::Party* createParty(QObject* parent) const = 0;
    virtual models::Drink* createDrink(QObject* parent) const = 0;

    virtual models::ClientSearch* createClientSearch(QObject* parent,
                                                     controllers::DatabaseControllerInterface* databaseController) const = 0;

    virtual models::RecentActivity* createRecentActivity(QObject* parent,
                                                         controllers::DatabaseControllerInterface* databaseController) const = 0;


    virtual controllers::CommandControllerInterface* createCommandController(QObject* parent,
                                                                             controllers::DatabaseControllerInterface* databaseController,
                                                                             controllers::NavigationControllerInterface* navigationController,
                                                                             models::Client* newClient,
                                                                             models::ClientSearch*  clientSearch,
                                                                             models::RecentActivity* recentActivity
                                                                             /*, networking::IWebRequest* rssWebRequest*/) const = 0;

    virtual controllers::DatabaseControllerInterface* createDatabaseController(QObject* parent) const = 0;

    virtual controllers::NavigationControllerInterface* createNavigationController(QObject* parent) const = 0;
//    virtual networking::INetworkAccessManager* createNetworkAccessManager(QObject* parent) const = 0;
//    virtual networking::IWebRequest* createWebRequest(QObject* parent, networking::INetworkAccessManager* networkAccessManager, const QUrl& url)
//    const = 0;
};

}
}

#endif // OBJECTFACTORYINTERFACE_H
