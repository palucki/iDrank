#pragma once

#include "toastproviderinterface.h"
#include <drinq-lib_global.h>

namespace drinq::controllers {
class DatabaseControllerInterface;
}

class DRINQLIB_EXPORT DatabaseToastProvider : public ToastProviderInterface
{
public:
    DatabaseToastProvider(drinq::controllers::DatabaseControllerInterface& db);
    virtual ~DatabaseToastProvider() override;

    Q_INVOKABLE Toast *randomToast(QVariant partyId) override;

private:
    drinq::controllers::DatabaseControllerInterface& m_db;
};

