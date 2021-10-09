#ifndef CLIENTSEARCH_H
#define CLIENTSEARCH_H

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

class DRINQLIB_EXPORT ClientSearch : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY( drinq::data::StringDecorator* ui_searchText READ
                searchText CONSTANT )
    Q_PROPERTY( QQmlListProperty<drinq::models::Client> ui_searchResults
                READ ui_searchResults NOTIFY searchResultsChanged )
public:
    ClientSearch(QObject* parent = nullptr, controllers::DatabaseControllerInterface* databaseController = nullptr);
    ~ClientSearch();
    data::StringDecorator* searchText();
    QQmlListProperty<Client> ui_searchResults();
    void search();
signals:
    void searchResultsChanged();
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};
}}
#endif // CLIENTSEARCH_H
