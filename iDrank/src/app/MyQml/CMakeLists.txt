# qt_add_qml_module(Ui
#     URI example.mylib
#     VERSION 1.0
#     SOURCES
#         mytype.h mytype.cpp
#     QML_FILES
#         MyQmlType.qml
# )

# qt_add_library(MyQml STATIC)

qt_add_qml_module(MyQml
    URI MyQml
    VERSION 1.0
    QML_FILES
        MasterView.qml
        DashboardView.qml
        HistoryMasterView.qml
        PartyMasterView.qml
        PartyDashboardMasterView.qml
        AboutView.qml
        RegisterUserView.qml
        StartPartyView.qml
        TextFieldDialog.qml
        PartyStatisticsView.qml
        LabelDialog.qml
        ConfirmationDialog.qml
        PartiesView.qml
        PartyDashboardView.qml
        DrinkPropertiesView.qml
        PlayersView.qml
    STATIC 
)

# qt_add_qml_module(custom
#     URI custom
#     VERSION 1.0
#     QML_FILES A.qml B.qml C.qml
#     STATIC
# )