#include <iostream>

#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>

#include "databasecontroller.h"
#include "drink.h"
#include "party.h"
#include "toast.h"
#include "drinktype.h"
#include "userdrink.h"
#include "partyplotter.h"

int main(int argc, char *argv[])
{
    QSettings settings; //HKEY_CURRENT_USER\SOFTWARE\Apps\iDrank
    
    std::cout << "Hello World\n";

    DatabaseController database_controller;
    database_controller.init();
    
    auto drinks = Drink::getDrinksForParty(1);
    auto seconds = Drink::secondsSinceLastDrink();

    std::cout << "Before: found " << drinks.size() << " drinks in database\n";

    // auto drink_id = Drink::add(1, 1, QDateTime::currentDateTime(), 50, 1);

    // if(drink_id)
    // {
    //     std::cout << "Added drink with id " << (*drink_id).toInt() << '\n';
    //     UserDrink::add(1, *drink_id);
    // }

    drinks = Drink::getDrinksForParty(1);
    std::cout << "After: found " << drinks.size() << " drinks in database\n";
    std::cout << "Seconds since last drink: " << (seconds ? *seconds : 0)  << "\n";

    for(auto& d : drinks)
    {
        QStringList user_ids;
        for(const auto& uid : d->m_user_ids)
        {
            user_ids.append(uid.toString());
        }
        std::cout << "drink id: " << d->m_id.toString().toStdString() << " users " << user_ids.join(',').toStdString() << '\n';
    }

    drinks = Drink::getDrinksForUserInParty(1,1);
    std::cout << "Drinks for user party 1, 1\n";
    for(auto& d : drinks)
    {
        std::cout << "drink id: " << d->m_id.toString().toStdString() << '\n';
    }

    if(!Party::isAnyStarted())
    {
        Party::start("TEST");
    }

    std::cout << "Before: any party started: " << Party::isAnyStarted() << '\n';
    Party::end();
    std::cout << "After: any party started: " << Party::isAnyStarted() << '\n';

    auto* t = Toast::getRandomToast(1);
    if(t)
    {
        std::cout << "Random toast for party 1: " << t->m_text.toStdString() << '\n';
    }

    const auto drink_types = DrinkType::getDrinkTypes();
    std::cout << "Found " << drink_types.size() << " drink types\n";
    for(auto* dt : drink_types)
    {
        std::cout << dt->m_id.toInt() << " / "<< dt->m_name.toStdString() << " / " << dt->m_default_amount_ml << "ml\n";
    }

    // std::cout << "Number of users for drink 2: " << UserDrink::getUserDrinks(2).size() << '\n';

    PartyPlotter party_plotter;

    QCoreApplication::setOrganizationName("Salka");
    QCoreApplication::setOrganizationDomain("palucki.github.io");
    QCoreApplication::setApplicationName("iDrank");

    //qrc:/qt/qml/app/

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("party_plotter", &party_plotter);
    // engine.addImportPath("qrc:/qt/qml/app/qml/");
    // engine.addImportPath(":/");
    
    //for Android?
    engine.addImportPath(":/");
    const QUrl url(QStringLiteral("qrc:/qt/qml/MyQml/MasterView.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, 
        [url](QObject *obj, const QUrl &objUrl) 
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}