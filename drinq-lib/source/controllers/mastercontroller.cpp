#include "mastercontroller.h"

#include <models/drink.h>
#include <models/clientsearch.h>
#include <models/recentactivity.h>
#include "databasecontroller.h"

using namespace drinq::models;

namespace drinq {
namespace controllers {

class MasterController::Implementation
{
public:
    Implementation(MasterController* _masterController,  drinq::framework::ObjectFactoryInterface* _factory)
        : objectFactory(_factory)
        , masterController(_masterController)
    {
        databaseController = objectFactory->createDatabaseController(masterController);
        navigationController = objectFactory->createNavigationController(masterController);
        newClient = objectFactory->createClient(masterController);
        clientSearch = objectFactory->createClientSearch(masterController, databaseController);
        recentActivity = objectFactory->createRecentActivity(masterController, databaseController);
        commandController = objectFactory->createCommandController(masterController, databaseController, navigationController,
                                                                   newClient, clientSearch, recentActivity);
    }

    drinq::framework::ObjectFactoryInterface* objectFactory{nullptr};
    MasterController* masterController{nullptr};
    DatabaseControllerInterface* databaseController{nullptr};
    NavigationControllerInterface* navigationController{nullptr};
    Client* newClient{nullptr};
    ClientSearch* clientSearch{nullptr};
    RecentActivity* recentActivity{nullptr};
    CommandControllerInterface* commandController{nullptr};
    QString welcomeMessage = "Welcome to the Client Management system!";
};

MasterController::MasterController(QObject *parent, framework::ObjectFactoryInterface *factory) : QObject(parent)
{
    implementation.reset(new Implementation(this, factory));
}

MasterController::~MasterController()
{
}

NavigationControllerInterface *MasterController::navigationController()
{
    return implementation->navigationController;
}

CommandControllerInterface* MasterController::commandController()
{
    return implementation->commandController;
}

DatabaseControllerInterface *MasterController::databaseController()
{
    return implementation->databaseController;
}

Client* MasterController::newClient()
{
    return implementation->newClient;
}

drinq::models::ClientSearch *MasterController::clientSearch()
{
    return implementation->clientSearch;
}

drinq::models::RecentActivity *MasterController::recentActivity()
{
    return implementation->recentActivity;
}

const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

void MasterController::selectClient(Client *client)
{
    emit implementation->navigationController->goEditClientView(client);
}

}
}
