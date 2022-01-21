#include "databasetoastprovider.h"
#include "controllers/databasecontrollerinterface.h"

#include <QDebug>
#include <QString>
#include <QRandomGenerator>

DatabaseToastProvider::DatabaseToastProvider(drinq::controllers::DatabaseControllerInterface& db)
    : m_db(db),
      m_toasts{"Piłka, bramka, gol", "Co by nam się!", "Pije Kuba do Jakuba"}
{

}

DatabaseToastProvider::~DatabaseToastProvider()
{

}

Toast* DatabaseToastProvider::randomToast()
{
    auto index = QRandomGenerator::global()->bounded(m_toasts.size());
    QString text = m_toasts[index];

    return new Toast(text, this);
}
