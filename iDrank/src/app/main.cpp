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
    
    auto drinks = Drink::getAllDrinks();

    std::cout << "Found " << drinks.size() << " drinks in database\n";

    return 0;
}