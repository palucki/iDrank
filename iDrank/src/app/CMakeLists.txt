# cmake_minimum_required(VERSION 3.16)

# project(iDrank VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Qml Sql Quick Charts)

# qt_standard_project_setup(REQUIRES 6.5)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(iDrank
    main.cpp
    # replace the following when .cpp is in place:
    databasecontroller.h
    partycontroller.h
    userscontroller.h
    drink.h
    party.h
    toast.h
    drinktype.h
    user.h
    userdrink.h
    partyplotter.cpp
)

qt_add_resources(iDrank dbresources
    PREFIX "/db"
    BASE assets/db/
    FILES assets/db/iDrank.db
)

qt_add_resources(iDrank img
    PREFIX "/img"
    BASE assets/img/
    FILES 
        assets/img/logo_yellow.svg
        assets/img/history_icon_grey.svg
        assets/img/home.png
        assets/img/info.png
        assets/img/users.png
)

# set_source_files_properties(../../../images/button-types.png PROPERTIES
#     QT_RESOURCE_ALIAS button-types.png
# )

qt_add_resources(iDrank js
    PREFIX "/js"
    BASE js/
    FILES js/common.js
)

add_subdirectory(MyQml)

target_link_libraries(iDrank PRIVATE Qt6::Widgets Qt6::Gui Qt6::Qml Qt6::Sql Qt6::Quick Qt6::Charts
                      MyQmlplugin)                   
#   MyQml) this is if we link dynamically 

set_target_properties(iDrank PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)