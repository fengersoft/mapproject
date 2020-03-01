#include "chinamapwidgetobjectpoint.h"

ChinaMapWidgetObjectPoint::ChinaMapWidgetObjectPoint(QObject* parent)
    : QObject(parent)
{
}

void ChinaMapWidgetObjectPoint::setGeoX(double geoX)
{
    m_geoX = geoX;
}

void ChinaMapWidgetObjectPoint::setGeoY(double geoY)
{
    m_geoY = geoY;
}

double ChinaMapWidgetObjectPoint::geoX()
{
    return m_geoX;
}

double ChinaMapWidgetObjectPoint::geoY()
{
    return m_geoY;
}

void ChinaMapWidgetObjectPoint::setScreenX(double screenX)
{
    m_screenX = screenX;
}

void ChinaMapWidgetObjectPoint::setScreenY(double screenY)
{
    m_screenY = screenY;
}

double ChinaMapWidgetObjectPoint::screenX()
{
    return m_screenX;
}

double ChinaMapWidgetObjectPoint::screenY()
{
    return m_screenY;
}
