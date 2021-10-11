#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <drinq-lib_global.h>

#include "commandcontrollerinterface.h"
#include "navigationcontrollerinterface.h"

using namespace drinq::models;

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT CommandController : public CommandControllerInterface
{
    Q_OBJECT
public:
    explicit CommandController(QObject* _parent = nullptr,
                               DatabaseControllerInterface* _databaseController = nullptr,
                               Client* newClient = nullptr,
                               ClientSearch* clientSearch = nullptr,
                               RecentActivity* recentActivity = nullptr,
                               NavigationControllerInterface* _navigationController = nullptr);
    ~CommandController();

    QQmlListProperty<framework::Command> ui_createClientViewContextCommands() override;
    QQmlListProperty<framework::Command> ui_findClientViewContextCommands() override;
    QQmlListProperty<framework::Command> ui_editClientViewContextCommands() override;
    QQmlListProperty<framework::Command> ui_dashboardViewContextCommands() override;

public slots:
    void onCreateClientSaveExecuted() override;
    void onFindClientSearchExecuted() override;
    void onEditClientSaveExecuted() override;
    void onEditClientDeleteExecuted() override;
    void onDashboardLoadExecuted() override;
    void setSelectedClient(drinq::models::Client* client) override;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}
#endif // COMMANDCONTROLLER_H
