#pragma once

#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>

//#include <qqml.h>

class CustomChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor)
//    QML_ELEMENT

public:
    explicit CustomChart(QQuickItem* parent = nullptr);
    ~CustomChart() override;
    QString name() const;
    void setName(const QString &name);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter) override;

private:
    QString m_name;
    QColor m_color;

};
