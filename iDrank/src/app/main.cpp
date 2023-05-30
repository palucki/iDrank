#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "databasecontroller.h"
#include "drink.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello World\n";

    DatabaseController database_controller;
    database_controller.init();
    
    auto drinks = Drink::getDrinksForParty(0);

    std::cout << "Found " << drinks.size() << " drinks in database\n";
    std::cout << "Seconds since last drink " << Drink::secondsSinceLastDrink() << "\n";

    return 0;
}