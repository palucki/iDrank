#ifndef DRINKCONTROLLER_H
#define DRINKCONTROLLER_H

#include <QObject>
#include <drinq-lib_global.h>

namespace drinq::controllers {
class DatabaseControllerInterface;
}

class DRINQLIB_EXPORT DrinkController : public QObject
{
    Q_OBJECT
public:
    explicit DrinkController(QObject *parent = nullptr, drinq::controllers::DatabaseControllerInterface* db = nullptr);
    virtual ~DrinkController();

public slots:
    bool addDrink();
    bool resetCounter();

signals:


private:
    drinq::controllers::DatabaseControllerInterface* m_db;
};

#endif // DRINKCONTROLLER_H
