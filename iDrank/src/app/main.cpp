#include <iostream>

#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>

#include "databasecontroller.h"
#include "partycontroller.h"
#include "userscontroller.h"
#include "drink.h"
#include "party.h"
#include "toast.h"
#include "drinktype.h"
#include "userdrink.h"
#include "partyplotter.h"

int main(int argc, char *argv[])
{
    QSettings settings; //HKEY_CURRENT_USER\SOFTWARE\Apps\iDrank
    
    DatabaseController database_controller;
    database_controller.init();
    PartyController party_controller;
    UsersController users_controller;
    PartyPlotter party_plotter(users_controller);

    QCoreApplication::setOrganizationName("Salka");
    QCoreApplication::setOrganizationDomain("palucki.github.io");
    QCoreApplication::setApplicationName("iDrank");

    //qrc:/qt/qml/app/

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("party_plotter", &party_plotter);
    engine.rootContext()->setContextProperty("party_controller", &party_controller);
    engine.rootContext()->setContextProperty("users_controller", &users_controller);
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