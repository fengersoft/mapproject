#ifndef CHINAMAPWIDGET_H
#define CHINAMAPWIDGET_H

#include "chinamapwidgetobject.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QWidget>
#include <QtDebug>

namespace Ui {
class ChinaMapWidget;
}

class ChinaMapWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChinaMapWidget(QWidget* parent = nullptr);
    ~ChinaMapWidget();
    void paintEvent(QPaintEvent* event);
    void loadJson(QString path);
    void getGeoCenter();
    void calScreenPoint();
    void getLines(Coordinate& coordinate, QVector<QPointF>& pts);
    void resizeEvent(QResizeEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void geoPointToScreenPoint(double geoX, double geoY, double& x, double& y);
    void screenPointToGeoPoint(double x, double y, double& geoX, double& geoY);

private:
    Ui::ChinaMapWidget* ui;
    QList<ChinaMapWidgetObject*> m_mapobjects;
    QPointF m_geoCenter;
    QPointF m_center;
    double m_scaleX;
    double m_scaleY;
    double m_minX;
    double m_minY;
    double m_minLon;
    double m_minLat;
    double m_maxLat;
    double m_resloution;
};

#endif // CHINAMAPWIDGET_H
