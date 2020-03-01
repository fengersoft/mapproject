#ifndef CHINAMAPWIDGETOBJECT_H
#define CHINAMAPWIDGETOBJECT_H

#include "chinamapwidgetobjectpoint.h"
#include <QColor>
#include <QObject>
#include <QPolygonF>
#include <QSet>
using Coordinate = QList<ChinaMapWidgetObjectPoint*>;

class ChinaMapWidgetObject : public QObject {
    Q_OBJECT
public:
    explicit ChinaMapWidgetObject(QObject* parent = nullptr);
    void setName(QString name);
    QString name();
    QList<Coordinate>& coordinates();
    QColor& color();
    QColor& hoverColor();
    QColor& selectedColor();
    QList<QPolygonF>& areas();
    void setAreas(QList<QPolygonF>& areas);
    void setIsHover(bool m_isHover);
    bool isHover();
    void setGeoCenter(QPointF geoCenter);
    QPointF& geoCenter();
    void setSelected(bool selected);
    bool selected();

private:
    QString m_name;
    QList<Coordinate> m_coordinates;
    QColor m_color;
    QColor m_hoverColor;
    QColor m_selectedColor;
    QList<QPolygonF> m_areas;
    bool m_isHover;
    QPointF m_geoCenter;
    QPointF m_center;
    bool m_selected;

signals:

public slots:
};

#endif // CHINAMAPWIDGETOBJECT_H
