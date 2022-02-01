#include "customchart.h"

#include <QPainter>
#include <QPen>

CustomChart::CustomChart(QQuickItem *parent) : QQuickPaintedItem(parent)
{

}

CustomChart::~CustomChart()
{

}

QString CustomChart::name() const
{
    return m_name;
}

void CustomChart::setName(const QString &name)
{
    m_name = name;
}

QColor CustomChart::color() const
{
    return m_color;
}

void CustomChart::setColor(const QColor &color)
{
    m_color = color;
}

void CustomChart::paint(QPainter* painter)
{
//    static QCustomPlot plot();
    plot.render(painter);

    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);

    painter->drawText(QFontMetrics(painter->font()).size(Qt::TextSingleLine, "One ").width(), 20, "To be implemented");


}
