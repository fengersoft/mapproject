#include "chinamapwidgetobject.h"

ChinaMapWidgetObject::ChinaMapWidgetObject(QObject* parent)
    : QObject(parent)
{
    m_color = QColor(173, 214, 254);
    m_hoverColor = QColor(205, 230, 254);
    m_selectedColor = QColor(22, 137, 252);
    m_selected = false;
}

void ChinaMapWidgetObject::setName(QString name)
{
    m_name = name;
}

QString ChinaMapWidgetObject::name()
{
    return m_name;
}

QList<Coordinate>& ChinaMapWidgetObject::coordinates()
{
    return m_coordinates;
}

QColor& ChinaMapWidgetObject::color()
{
    return m_color;
}

QColor& ChinaMapWidgetObject::hoverColor()
{
    return m_hoverColor;
}

QColor& ChinaMapWidgetObject::selectedColor()
{
    return m_selectedColor;
}

QList<QPolygonF>& ChinaMapWidgetObject::areas()
{
    return m_areas;
}

void ChinaMapWidgetObject::setAreas(QList<QPolygonF>& areas)
{
    m_areas = areas;
}

void ChinaMapWidgetObject::setIsHover(bool isHover)
{
    m_isHover = isHover;
}

bool ChinaMapWidgetObject::isHover()
{
    return m_isHover;
}

void ChinaMapWidgetObject::setGeoCenter(QPointF geoCenter)
{
    m_geoCenter = geoCenter;
}

QPointF& ChinaMapWidgetObject::geoCenter()
{
    return m_geoCenter;
}

void ChinaMapWidgetObject::setSelected(bool selected)
{
    m_selected = selected;
}

bool ChinaMapWidgetObject::selected()
{
    return m_selected;
}
