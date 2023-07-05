#include <iostream>

#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>

#include "databasecontroller.h"
#include "partycontroller.h"
// #include "involveduserscontroller.h"
#include "userscontroller.h"
#include "drinktypecontroller.h"
#include "drink.h"
#include "party.h"
#include "toast.h"
#include "drinktype.h"
#include "userdrink.h"
#include "partyplotter.h"

int main(int argc, char *argv[])
{
    //need to declare it before creating settings to propagate the path correctly
    QCoreApplication::setOrganizationName("Salka");
    QCoreApplication::setOrganizationDomain("palucki.github.io");
    QCoreApplication::setApplicationName("iDrank");

    QSettings settings; //HKEY_CURRENT_USER\SOFTWARE\Apps\iDrank / /home/$USER/.config/Salka/iDrank.conf

    DatabaseController database_controller;
    // InvolvedUsersController involved_users_controller{settings};
    DrinkTypeController drink_type_controller{settings};
    PartyController party_controller;
    UsersController users_controller{settings};
    PartyPlotter party_plotter(users_controller);

    qmlRegisterType<DrinkType>("MyQml", 1, 0, "DrinkType");
    qmlRegisterType<Party>("MyQml", 1, 0, "Party");

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("party_plotter", &party_plotter);
    engine.rootContext()->setContextProperty("party_controller", &party_controller);
    // engine.rootContext()->setContextProperty("involved_users_controller", &involved_users_controller);
    engine.rootContext()->setContextProperty("users_controller", &users_controller);
    engine.rootContext()->setContextProperty("drink_type_controller", &drink_type_controller);
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