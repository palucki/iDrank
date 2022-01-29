#include "databasetoastprovider.h"
#include "controllers/databasecontrollerinterface.h"

#include <QDebug>
#include <QString>
#include <QRandomGenerator>

DatabaseToastProvider::DatabaseToastProvider(drinq::controllers::DatabaseControllerInterface& db)
    : m_db(db),
      m_toasts{"Piłka, bramka, gol", "Co by nam się!", "Pije Kuba do Jakuba"},
      m_unusedToasts(m_toasts)
{

}

DatabaseToastProvider::~DatabaseToastProvider()
{

}

Toast* DatabaseToastProvider::randomToast()
{
    if(m_unusedToasts.isEmpty())
    {
        qDebug() << "No more toasts, resetting";
        m_unusedToasts = m_toasts;
    }

    auto index = QRandomGenerator::global()->bounded(m_unusedToasts.size());
    QString text = m_unusedToasts[index];
    m_unusedToasts.removeAt(index);

    return new Toast(text, this);
}
