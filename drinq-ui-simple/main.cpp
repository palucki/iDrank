#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QSettings>

#include "controllers/mastercontroller2.h"
#include "controllers/databasecontroller.h"
#include "controllers/drinkcontroller.h"
#include "controllers/partycontroller.h"

#include "framework/databasetoastprovider.h"

#include "components/customchart.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QCoreApplication::setOrganizationName("Apps");
    QCoreApplication::setOrganizationDomain("palucki.github.io");
    QCoreApplication::setApplicationName("iDrank");

    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    qmlRegisterType<drinq::controllers::DrinkController>("DrinQ", 1, 0, "DrinkController");
    qmlRegisterType<PartyController>("DrinQ", 1, 0, "PartyController");
    qmlRegisterType<drinq::controllers::MasterController2>("DrinQ", 1, 0, "MasterController");
    qmlRegisterType<drinq::models::DrinkType>("DrinQ", 1, 0, "DrinkType");
    qmlRegisterType<drinq::models::Drink2>("DrinQ", 1, 0, "Drink2");
    qmlRegisterType<drinq::models::Party2>("DrinQ", 1, 0, "Party2");
    qmlRegisterType<drinq::models::Party2>("DrinQ", 1, 0, "Party2");
    qmlRegisterType<Toast>("DrinQ", 1, 0, "Toast");
    qmlRegisterType<CustomChart>("DrinQ", 1, 0, "CustomChart");

    QSettings settings; //HKEY_CURRENT_USER\SOFTWARE\Apps\iDrank
    drinq::controllers::DatabaseController db;
    drinq::controllers::MasterController2 masterController(&app, &db);
    drinq::controllers::DrinkController drinkController(&app, &db, &settings);
    PartyController partyController(&app, &db, &drinkController);
    DatabaseToastProvider toastProvider(db);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("drinkController", &drinkController);
    engine.rootContext()->setContextProperty("partyController", &partyController);
    engine.rootContext()->setContextProperty("masterController", &masterController);
    engine.rootContext()->setContextProperty("toastProvider", &toastProvider);
    engine.addImportPath("qrc:/");
    const QUrl url(QStringLiteral("qrc:/MasterView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
