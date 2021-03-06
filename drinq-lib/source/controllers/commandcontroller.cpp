#include "commandcontroller.h"

#include <QList>
#include <QDebug>

#include "navigationcontroller.h"

using namespace drinq::framework;
using namespace drinq::models;

namespace drinq {
namespace controllers {

class CommandController::Implementation
{
public:
    Implementation(CommandController* _commandController, DatabaseControllerInterface*
                   _databaseController, Client* _newClient, Party* _newParty, ClientSearch* _clientSearch, RecentActivity* _recentActivity,
                   NavigationControllerInterface* _navController)
        : databaseController(_databaseController)
        , newClient(_newClient)
        , newParty(_newParty)
        , clientSearch(_clientSearch)
        , recentActivity(_recentActivity)
        , navigationController(_navController)
        , commandController(_commandController)
    {
        Command* createClientSaveCommand = new Command(commandController, QChar( 0xf0c7 ), "Save" );
        QObject::connect( createClientSaveCommand, &Command::executed, commandController, &CommandController::onCreateClientSaveExecuted );
        createClientViewContextCommands.append( createClientSaveCommand );

        Command* findClientCommand = new Command(commandController, QChar( 0xf002 ), "Search" );
        QObject::connect( findClientCommand, &Command::executed, commandController, &CommandController::onFindClientSearchExecuted );
        findClientViewContextCommands.append( findClientCommand );

        Command* editClientSaveCommand = new Command(commandController, QChar( 0xf0c7 ), "Save" );
        QObject::connect( editClientSaveCommand, &Command::executed, commandController, &CommandController::onEditClientSaveExecuted );
        editClientViewContextCommands.append( editClientSaveCommand );

        Command* editClientDeleteClientCommand = new Command(commandController, QChar( 0xf235 ), "Delete" );
        QObject::connect( editClientDeleteClientCommand, &Command::executed, commandController, &CommandController::onEditClientDeleteExecuted );
        editClientViewContextCommands.append( editClientDeleteClientCommand );

        Command* dashboardAddCommand = new Command(commandController, QChar( 0xf055 ), "Add" );
        QObject::connect(dashboardAddCommand, &Command::executed, commandController, &CommandController::onDashboardAddExecuted);
        dashboardViewContextCommands.append(dashboardAddCommand);

        Command* editPartyDeleteCommand = new Command(commandController, QChar( 0xf235 ), "Delete" );
        QObject::connect( editPartyDeleteCommand, &Command::executed, commandController, &CommandController::onEditPartyDeleteExecuted );
        editPartyViewContextCommands.append( editPartyDeleteCommand );

        Command* editPartySaveCommand = new Command(commandController, QChar( 0xf0c7 ), "Save" );
        QObject::connect( editPartySaveCommand, &Command::executed, commandController, &CommandController::onEditPartySaveExecuted );
        editPartyViewContextCommands.append( editPartySaveCommand );
    }

    DatabaseControllerInterface* databaseController{nullptr};
    Client* newClient{nullptr};
    Party* newParty{nullptr};
    ClientSearch* clientSearch{nullptr};
    RecentActivity* recentActivity{nullptr};
    Client* selectedClient{nullptr};
    Party* selectedParty{nullptr};
    NavigationControllerInterface* navigationController{nullptr};
    CommandController* commandController{nullptr};
    QList<Command*> createClientViewContextCommands{};
    QList<Command*> findClientViewContextCommands{};
    QList<Command*> editClientViewContextCommands{};
    QList<Command*> dashboardViewContextCommands{};
    QList<Command*> editPartyViewContextCommands{};
};

CommandController::CommandController(QObject* parent,
                                     DatabaseControllerInterface* databaseController,
                                     Client* newClient,
                                     Party* newParty,
                                     ClientSearch* clientSearch,
                                     RecentActivity* recentActivity,
                                     NavigationControllerInterface* _navigationController)
    : CommandControllerInterface(parent, databaseController, newClient, newParty, clientSearch, recentActivity, _navigationController)
{
    implementation.reset(new Implementation(this, databaseController, newClient, newParty, clientSearch, recentActivity, _navigationController));
}

CommandController::~CommandController()
{
}

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->createClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_findClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->findClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_editClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->editClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_dashboardViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->dashboardViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_editPartyViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->editPartyViewContextCommands);
}


void CommandController::onCreateClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";
    implementation->databaseController->createRow(implementation->newClient->key(),
//                                                  implementation->newClient->id(),
                                                  implementation->newClient->toJson());
    qDebug() << "New client saved.";

    implementation->clientSearch->searchText()->setValue(implementation->newClient->id());
    implementation->clientSearch->search();
    emit implementation->navigationController->goFindClientView();
}

void CommandController::onFindClientSearchExecuted()
{
    qDebug() << "You executed the Search command!";
    implementation->clientSearch->search();
}

void CommandController::onEditClientSaveExecuted()
{
    qDebug() << "You executed the Save (update) command!";
    implementation->databaseController->updateRow(implementation->selectedClient->key(),
                                                  implementation->selectedClient->id(),
                                                  implementation->selectedClient->toJson());

    qDebug() << "Client saved!";
}

void CommandController::onEditClientDeleteExecuted()
{
    qDebug() << "You executed the Delete command!";
    implementation->databaseController->deleteRow(implementation->selectedClient->key(),
                                                  implementation->selectedClient->id());

    implementation->selectedClient = nullptr;

    implementation->clientSearch->search();
    emit implementation->navigationController->goDashboardView();

}

void CommandController::onDashboardLoadExecuted()
{
    qDebug() << "You executed the Load command!";
    implementation->recentActivity->load();
}

void CommandController::onDashboardAddExecuted()
{
    qDebug() << "You executed the Add command!";
    qDebug() << "New Party " << implementation->newParty->toJson();

    emit implementation->navigationController->goEditPartyView(implementation->newParty);
}

void CommandController::onEditPartySaveExecuted()
{
    //TODO: Handle create / update here
    //TOOO: If create, make sure next save will use other party and not overwrite

    qDebug() << "selected id: " << implementation->selectedParty->id();
    qDebug() << "json: " << implementation->selectedParty->toJson();

    qDebug() << "new id: " << implementation->newParty->id();
    qDebug() << "json: " << implementation->newParty->toJson();

    //bedziemy sprawdzac .value("id") w toJson()

    if(implementation->selectedParty == implementation->newParty)
    {
        qDebug() << "New";
        implementation->databaseController->createRow(implementation->newParty->key(),
//                                                      implementation->newParty->id(),
                                                      implementation->newParty->toJson());

        auto oldParty = implementation->newParty;
        implementation->newParty = new Party(this);
        delete oldParty;
    }
    else
    {
        qDebug() << "Only update";
        implementation->databaseController->updateRow(implementation->selectedParty->key(),
                                                      implementation->selectedParty->id(),
                                                      implementation->selectedParty->toJson());
    }

    qDebug() << "You executed the Save (update) command!";

//    implementation->selectedParty = nullptr;

    emit implementation->navigationController->goDashboardView();
}

void CommandController::onEditPartyDeleteExecuted()
{
    qDebug() << "You executed the Delete command!";
    implementation->databaseController->deleteRow(implementation->selectedParty->key(),
                                                  implementation->selectedParty->id());

    implementation->selectedParty = implementation->newParty;

//    implementation->clientSearch->search();
    emit implementation->navigationController->goDashboardView();
}

void CommandController::setSelectedClient(Client *client)
{
    implementation->selectedClient = client;
}

void CommandController::setSelectedParty(Party* party)
{
    implementation->selectedParty = party;
}

}}
