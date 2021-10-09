#include "clientsearch.h"
#include <QDebug>

using namespace drinq::controllers;
using namespace drinq::data;

namespace drinq {
namespace models {

class ClientSearch::Implementation
{
public:
    Implementation(ClientSearch* _clientSearch, DatabaseControllerInterface*
                   _databaseController)
        : clientSearch(_clientSearch)
        , databaseController(_databaseController)
    {
    }
    ClientSearch* clientSearch{nullptr};
    DatabaseControllerInterface* databaseController{nullptr};
    data::StringDecorator* searchText{nullptr};
    data::EntityCollection<Client>* searchResults{nullptr};
};

ClientSearch::ClientSearch(QObject* parent, DatabaseControllerInterface*  databaseController)
    : Entity(parent, "ClientSearch")
{
    implementation.reset(new Implementation(this, databaseController));
    implementation->searchText =
            static_cast<StringDecorator*>(addDataItem(new StringDecorator(this,
                                                                          "searchText", "Search Text")));
    implementation->searchResults = static_cast<EntityCollection<Client>*>(addChildCollection(new
                                                                      EntityCollection<Client>(this, "searchResults")));
    connect(implementation->searchResults,
            &EntityCollection<Client>::collectionChanged, this,
            &ClientSearch::searchResultsChanged);
}
ClientSearch::~ClientSearch()
{
}
StringDecorator* ClientSearch::searchText()
{
    return implementation->searchText;
}
QQmlListProperty<Client> ClientSearch::ui_searchResults()
{
    return QQmlListProperty<Client>(this,
                                    implementation->searchResults->derivedEntities());
}

void ClientSearch::search()
{
    qDebug() << "Searching for " << implementation->searchText->value() << "...";
    auto resultsArray = implementation->databaseController->find("client", implementation->searchText->value());
    implementation->searchResults->update(resultsArray);
    qDebug() << "Found " << implementation->searchResults->baseEntities().size() << " matches";
}

}
}
