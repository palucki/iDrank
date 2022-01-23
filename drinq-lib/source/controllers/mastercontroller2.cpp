#include "mastercontroller2.h"

#include <models/drink.h>
#include <models/clientsearch.h>
#include <models/recentactivity.h>
#include "databasecontroller.h"

using namespace drinq::models;

namespace drinq {
namespace controllers {

class MasterController2::Implementation
{
public:
    Implementation(MasterController2* _masterController,  drinq::controllers::DatabaseControllerInterface* dbController)
        : databaseController(dbController)
    {
        auto parties = databaseController->getAll(drinq::models::Party2{_masterController});

        qDebug() << "Found " << parties.size() << " parties";

        for(const auto& p : parties)
        {
    //        qDebug() << drink_type.m_name << " default amount: " << drink_type.m_default_amount_ml;
            m_parties.append(new drinq::models::Party2(p.toJson(), _masterController));
        }

    }

    DatabaseControllerInterface* databaseController{nullptr};
    QList<drinq::models::Party2*> m_parties;
};

MasterController2::MasterController2(QObject *parent, DatabaseControllerInterface *dbController) : QObject(parent)
{
    implementation.reset(new Implementation(this, dbController));
}

MasterController2::~MasterController2()
{
}

QQmlListProperty<Party2> MasterController2::ui_parties()
{
    return QQmlListProperty<drinq::models::Party2>(this, implementation->m_parties);
}

}
}
