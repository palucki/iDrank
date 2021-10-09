#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <drinq-lib_global.h>
//#include <models/clientsearch.h>
#include <controllers/navigationcontroller.h>
#include <controllers/commandcontroller.h>
#include <controllers/databasecontrollerinterface.h>
#include <framework/objectfactoryinterface.h>

namespace drinq {
namespace models {
class ClientSearch;
}
}

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_welcomeMessage READ welcomeMessage CONSTANT)
    Q_PROPERTY(drinq::controllers::NavigationControllerInterface* ui_navigationController READ navigationController CONSTANT)
    Q_PROPERTY(drinq::controllers::CommandControllerInterface* ui_commandController READ commandController CONSTANT)
    Q_PROPERTY(drinq::controllers::DatabaseControllerInterface* ui_databaseController READ databaseController CONSTANT)
    Q_PROPERTY(drinq::models::Client* ui_newClient READ newClient CONSTANT )
    Q_PROPERTY(drinq::models::ClientSearch* ui_clientSearch READ clientSearch CONSTANT )
public:
    explicit MasterController(QObject *parent = nullptr, drinq::framework::ObjectFactoryInterface* factory = nullptr);
    ~MasterController();
    NavigationControllerInterface* navigationController();
    CommandControllerInterface* commandController();
    DatabaseControllerInterface* databaseController();
    drinq::models::Client* newClient();
    drinq::models::ClientSearch* clientSearch();
    const QString& welcomeMessage() const;

public slots:
    void selectClient(drinq::models::Client* client);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}
#endif // MASTERCONTROLLER_H
