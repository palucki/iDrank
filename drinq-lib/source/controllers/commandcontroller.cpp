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
                   _databaseController, Client* _newClient, ClientSearch* _clientSearch,
                   NavigationControllerInterface* _navController)
        : databaseController(_databaseController)
        , newClient(_newClient)
        , clientSearch(_clientSearch)
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
    }

    DatabaseControllerInterface* databaseController{nullptr};
    Client* newClient{nullptr};
    ClientSearch* clientSearch{nullptr};
    Client* selectedClient{nullptr};
    NavigationControllerInterface* navigationController{nullptr};
    CommandController* commandController{nullptr};
    QList<Command*> createClientViewContextCommands{};
    QList<Command*> findClientViewContextCommands{};
    QList<Command*> editClientViewContextCommands{};
};

CommandController::CommandController(QObject* parent,
                                     DatabaseControllerInterface* databaseController,
                                     Client* newClient,
                                     ClientSearch* clientSearch,
                                     NavigationControllerInterface* _navigationController)
    : CommandControllerInterface(parent, databaseController, newClient, clientSearch, _navigationController)
{
    implementation.reset(new Implementation(this, databaseController, newClient, clientSearch, _navigationController));
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

void CommandController::onCreateClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";
    implementation->databaseController->createRow(implementation->newClient->key(),
                                                  implementation->newClient->id(),
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

void CommandController::setSelectedClient(Client *client)
{
    implementation->selectedClient = client;
}

}}
