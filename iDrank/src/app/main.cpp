#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

#include "databasecontroller.h"
#include "drink.h"

int main(int argc, char *argv[])
{
    QSettings settings; //HKEY_CURRENT_USER\SOFTWARE\Apps\iDrank
    
    std::cout << "Hello World\n";

    DatabaseController database_controller;
    database_controller.init();
    
    auto drinks = Drink::getDrinksForParty(1);
    auto seconds = Drink::secondsSinceLastDrink();

    std::cout << "Before: found " << drinks.size() << " drinks in database\n";

    auto drink_id = Drink::add(1, 1, QDateTime::currentDateTime(), 50, 1);

    if(drink_id)
        std::cout << "Added drink with id " << (*drink_id).toInt() << '\n';

    drinks = Drink::getDrinksForParty(1);
    std::cout << "After: found " << drinks.size() << " drinks in database\n";
    std::cout << "Seconds since last drink: " << (seconds ? *seconds : 0)  << "\n";

    return 0;
}