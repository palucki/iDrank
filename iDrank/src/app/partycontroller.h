#pragma once 

#include <optional>
#include <QObject>

#include "user.h"

class PartyController : public QObject
{
    Q_OBJECT
    
public:
    explicit PartyController(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~PartyController() override {}

public slots:
    QList<User*> getUsersForParty(const QVariant& party_id)
    {
        Q_UNUSED(party_id);
        return User::getUsers();
    } 
};