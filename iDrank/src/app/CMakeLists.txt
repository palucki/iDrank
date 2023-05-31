cmake_minimum_required(VERSION 3.16)

project(iDrank VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Qml Sql)
qt_standard_project_setup()

qt_add_executable(iDrank
    main.cpp
    # replace the following when .cpp is in place:
    databasecontroller.h
    drink.h
    party.h
)

qt_add_resources(iDrank dbresources
    PREFIX "/db"
    BASE ../../
    FILES ../../iDrank.db
)

target_link_libraries(iDrank PRIVATE Qt6::Widgets Qt6::Gui Qt6::Qml Qt6::Sql)

set_target_properties(iDrank PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)