#ifndef COMMANDCONTROLLERINTERFACE_H
#define COMMANDCONTROLLERINTERFACE_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <drinq-lib_global.h>

#include <framework/command.h>
#include <models/drink.h>
#include <models/clientsearch.h>
#include <models/recentactivity.h>
#include "databasecontrollerinterface.h"
#include "navigationcontrollerinterface.h"

using namespace drinq::models;

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT CommandControllerInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<drinq::framework::Command>
               ui_createClientViewContextCommands READ
               ui_createClientViewContextCommands CONSTANT)

    Q_PROPERTY(QQmlListProperty<drinq::framework::Command>
               ui_findClientViewContextCommands READ
               ui_findClientViewContextCommands CONSTANT)

    Q_PROPERTY(QQmlListProperty<drinq::framework::Command>
               ui_editClientViewContextCommands READ
               ui_editClientViewContextCommands CONSTANT)

    Q_PROPERTY(QQmlListProperty<drinq::framework::Command>
               ui_dashboardViewContextCommands READ
               ui_dashboardViewContextCommands CONSTANT)

public:
    explicit CommandControllerInterface(QObject* _parent = nullptr,
                               DatabaseControllerInterface* _databaseController = nullptr,
                               Client* newClient = nullptr,
                               ClientSearch* clientSearch = nullptr,
                               RecentActivity* recentActivity = nullptr,
                               NavigationControllerInterface* _navigationController = nullptr)
        : QObject(_parent)
        {
            Q_UNUSED(_databaseController);
            Q_UNUSED(newClient);
            Q_UNUSED(clientSearch);
            Q_UNUSED(recentActivity);
            Q_UNUSED(_navigationController);
        }

    virtual ~CommandControllerInterface() {}
    virtual QQmlListProperty<framework::Command> ui_createClientViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_findClientViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_editClientViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_dashboardViewContextCommands() = 0;

public slots:
    virtual void onCreateClientSaveExecuted() = 0;
    virtual void onFindClientSearchExecuted() = 0;
    virtual void onEditClientSaveExecuted() = 0;
    virtual void onEditClientDeleteExecuted() = 0;
    virtual void onDashboardLoadExecuted() = 0;
    virtual void onDashboardAddExecuted() = 0;
    virtual void setSelectedClient(drinq::models::Client* client) = 0;
    virtual void setSelectedParty(drinq::models::Party* party) = 0;

};

}}

#endif // COMMANDCONTROLLERINTERFACE_H
