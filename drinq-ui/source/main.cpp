#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>

#include <data/intdecorator.h>
#include <data/dropdown.h>
#include <data/dropdownvalue.h>
#include <models/address.h>
#include <models/appointment.h>
#include <models/drink.h>
#include <models/contact.h>
#include <models/clientsearch.h>
#include <models/recentactivity.h>
#include <controllers/mastercontroller.h>
#include <controllers/commandcontroller.h>
#include <framework/command.h>
#include <framework/objectfactory.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "drinq-ui_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    qmlRegisterType<drinq::controllers::MasterController>("DrinQ", 1, 0, "MasterController");
    qmlRegisterUncreatableType<drinq::controllers::NavigationControllerInterface>("DrinQ", 1, 0, "NavigationControllerInterface", "Interface");
    qmlRegisterUncreatableType<drinq::controllers::CommandControllerInterface>("DrinQ", 1, 0, "CommandControllerInterface", "Interface");
    qmlRegisterType<drinq::framework::Command>("DrinQ", 1, 0, "Command");
    qmlRegisterType<drinq::data::DateTimeDecorator>("DrinQ", 1, 0, "DateTimeDecorator");
    qmlRegisterType<drinq::data::EnumeratorDecorator>("DrinQ", 1, 0, "EnumeratorDecorator");
    qmlRegisterType<drinq::data::IntDecorator>("DrinQ", 1, 0, "IntDecorator");
    qmlRegisterType<drinq::data::StringDecorator>("DrinQ", 1, 0, "StringDecorator");
    qmlRegisterType<drinq::models::Address>("DrinQ", 1, 0, "Address");
    qmlRegisterType<drinq::models::Appointment>("DrinQ", 1, 0, "Appointment");
    qmlRegisterType<drinq::models::Client>("DrinQ", 1, 0, "Client");
    qmlRegisterType<drinq::models::Contact>("DrinQ", 1, 0, "Contact");
    qmlRegisterType<drinq::models::ClientSearch>("DrinQ", 1, 0, "ClientSearch");
    qmlRegisterType<drinq::data::DropDown>("DrinQ", 1, 0, "DropDown");
    qmlRegisterType<drinq::data::DropDownValue>("DrinQ", 1, 0, "DropDownValue");

    qmlRegisterType<drinq::models::Party>("DrinQ", 1, 0, "Party");
//    qmlRegisterType<drinq::models::Beverage>("DrinQ", 1, 0, "Beverage");
//    qmlRegisterType<drinq::models::Player>("DrinQ", 1, 0, "Player");
    qmlRegisterType<drinq::models::Drink>("DrinQ", 1, 0, "Drink");
    qmlRegisterType<drinq::models::RecentActivity>("DrinQ", 1, 0, "RecentActivity");

    drinq::framework::ObjectFactory factory;
    drinq::controllers::MasterController masterController(&app, &factory);
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("masterController", &masterController);
    const QUrl url(QStringLiteral("qrc:/views/MasterView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
