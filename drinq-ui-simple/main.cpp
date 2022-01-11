#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "controllers/databasecontroller.h"
#include "controllers/drinkcontroller.h"
#include "controllers/partycontroller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    qmlRegisterType<drinq::controllers::DrinkController>("DrinQ", 1, 0, "DrinkController");
    qmlRegisterType<PartyController>("DrinQ", 1, 0, "PartyController");
    qmlRegisterType<drinq::models::DrinkType>("DrinQ", 1, 0, "DrinkType");
    qmlRegisterType<drinq::models::Drink2>("DrinQ", 1, 0, "Drink2");
    drinq::controllers::DatabaseController db;
    drinq::controllers::DrinkController drinkController(&app, &db);
    PartyController partyController(&app, &db, &drinkController);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("drinkController", &drinkController);
    engine.rootContext()->setContextProperty("partyController", &partyController);
    const QUrl url(QStringLiteral("qrc:/MasterView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}