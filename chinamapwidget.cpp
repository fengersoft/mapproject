#include "chinamapwidget.h"
#include "ui_chinamapwidget.h"

ChinaMapWidget::ChinaMapWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ChinaMapWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

ChinaMapWidget::~ChinaMapWidget()
{
    delete ui;
}

void ChinaMapWidget::paintEvent(QPaintEvent* event)
{
    double x, y, geoX, geoY;
    QPointF pt = mapFromGlobal(cursor().pos());
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.fillRect(rect(), QBrush(Qt::white));
    for (int i = 0; i < m_mapobjects.count(); i++) {
        ChinaMapWidgetObject* obj = m_mapobjects.at(i);
        obj->setIsHover(false);
        QList<QPolygonF> areas = obj->areas();
        areas.clear();
        for (int j = 0; j < obj->coordinates().count(); j++) {
            Coordinate coordinate = obj->coordinates().at(j);
            QVector<QPointF> pts;
            getLines(coordinate, pts);
            QPen pen = painter.pen();

            if (obj->name() == "") {
                pen.setWidth(1);
                pen.setColor(QColor(97, 97, 97));
            } else {
                pen.setWidth(2);
                pen.setColor(QColor(Qt::white));
            }

            painter.setPen(pen);
            painter.drawPolyline(pts);
            QPainterPath path;
            QPolygonF pol;
            pol.append(pts);
            path.addPolygon(pol);
            areas << pol;
            QColor color;
            QPointF ptf(pt.x(), pt.y());
            if (obj->selected()) {
                color = obj->selectedColor();
            } else if ((pol.containsPoint(ptf, Qt::WindingFill))
                || (obj->isHover() == true)) {
                color = obj->hoverColor();
                obj->setIsHover(true);
            } else {
                color = obj->color();
            }
            painter.fillPath(path, QBrush(color));
        }
        obj->setAreas(areas);
    }
    for (int i = 0; i < m_mapobjects.count(); i++) {
        ChinaMapWidgetObject* obj = m_mapobjects.at(i);
        geoPointToScreenPoint(obj->geoCenter().x(), obj->geoCenter().y(), x, y);
        QFont font = painter.font();
        font.setPointSize(6);
        painter.setFont(font);
        QPen pen = painter.pen();
        pen.setWidth(1);
        pen.setColor(QColor(197, 197, 197));
        painter.setPen(pen);
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.width(obj->name());
        QRect objNameRc;
        if (obj->name() == "澳门") {
            painter.drawLine(x, y, x - 10, y + 10);
            x -= 15;
            y += 15;
        } else if (obj->name() == "香港") {
            painter.drawLine(x, y, x + 10, y + 10);
            x += 15;
            y += 15;
        }
        objNameRc.setRect(x - w / 2, y - fm.height() / 2, w, fm.height());
        painter.setPen(QColor(97, 97, 97));
        painter.drawText(objNameRc, Qt::AlignCenter, obj->name());
    }

    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(11);
    painter.setFont(font);
    screenPointToGeoPoint(pt.x(), pt.y(), geoX, geoY);
    QRect rc;
    rc.setRect(16, 0, 300, 24);
    painter.setPen(Qt::black);
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, QString("%1,%2").arg(geoX).arg(geoY));
    painter.end();
}

void ChinaMapWidget::loadJson(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    file.close();
    QJsonDocument jdoc = QJsonDocument::fromJson(ba);
    QJsonObject keys = jdoc.object();
    QJsonArray features = keys.value("features").toArray();
    QVariantList list = features.toVariantList();
    for (int i = 0; i < list.count(); i++) {
        QJsonObject feature = list.at(i).toJsonObject();
        QJsonObject properties = feature.value("properties").toObject();
        QString name = properties.value("name").toString();
        QJsonArray center = properties.value("centroid").toArray();
        ChinaMapWidgetObject* obj = new ChinaMapWidgetObject(this);
        obj->setName(name);
        QPointF centerPt(center.at(0).toDouble(), center.at(1).toDouble());
        obj->setGeoCenter(centerPt);
        QJsonObject geometry = feature.value("geometry").toObject();
        QJsonArray coordinates = geometry.value("coordinates").toArray();

        for (int j = 0; j < coordinates.count(); j++) {
            QJsonArray arr1 = coordinates.at(j).toArray();
            for (int k = 0; k < arr1.count(); k++) {
                Coordinate coordinate;
                QJsonArray arr2 = arr1.at(k).toArray();
                for (int l = 0; l < arr2.count(); l++) {
                    ChinaMapWidgetObjectPoint* pt = new ChinaMapWidgetObjectPoint();
                    QJsonArray arr3 = arr2.at(l).toArray();
                    pt->setGeoX(arr3.at(0).toDouble());
                    pt->setGeoY(arr3.at(1).toDouble());
                    coordinate << pt;
                }
                obj->coordinates().append(coordinate);
            }
        }
        m_mapobjects << obj;
    }
    getGeoCenter();
    calScreenPoint();
    update();
}

void ChinaMapWidget::getGeoCenter()
{
    double minX = 360;
    double minY = 360;
    double maxX = -360;
    double maxY = -360;
    for (int i = 0; i < m_mapobjects.count(); i++) {
        ChinaMapWidgetObject* obj = m_mapobjects.at(i);
        for (int j = 0; j < obj->coordinates().count(); j++) {
            Coordinate coordinate = obj->coordinates().at(j);
            for (int k = 0; k < coordinate.count(); k++) {
                ChinaMapWidgetObjectPoint* pt = coordinate.at(k);
                double x = pt->geoX();
                if (x < minX) {
                    minX = x;
                } else if (x > maxX) {
                    maxX = x;
                }
                double y = pt->geoY();
                if (y < minY) {
                    minY = y;
                } else if (y > maxY) {
                    maxY = y;
                }
            }
        }
    }
    m_geoCenter.setX((minX + maxX) / 2);
    m_geoCenter.setY((minY + maxY) / 2);
    m_center.setX(width() / 2);
    m_center.setY(height() / 2);
    m_scaleX = width() / ((maxX - minX) * 3600);
    m_scaleY = height() / ((maxY - minY) * 3600);
    m_minX = minX * 3600 / m_scaleX;
    m_minY = minY * 3600 / m_scaleY;
    m_minLon = m_minX;
    m_minLat = m_minY;
    m_maxLat = maxY;
    double a = (maxX - minX) / width();
    double b = (maxY - minY) / height();
    m_resloution = a > b ? a : b;
    m_resloution *= 1.1;
}

void ChinaMapWidget::calScreenPoint()
{
    for (int i = 0; i < m_mapobjects.count(); i++) {
        ChinaMapWidgetObject* obj = m_mapobjects.at(i);
        for (int j = 0; j < obj->coordinates().count(); j++) {
            Coordinate coordinate = obj->coordinates().at(j);
            for (int k = 0; k < coordinate.count(); k++) {
                ChinaMapWidgetObjectPoint* pt = coordinate.at(k);

                double x, y;
                geoPointToScreenPoint(pt->geoX(), pt->geoY(), x, y);
                pt->setScreenX(x);
                pt->setScreenY(y);
            }
        }
    }
}

void ChinaMapWidget::getLines(Coordinate& coordinate, QVector<QPointF>& pts)
{
    for (int i = 0; i < coordinate.count(); i++) {
        ChinaMapWidgetObjectPoint* cpt = coordinate.at(i);
        QPointF pt(cpt->screenX(), cpt->screenY());
        pts << pt;
    }
}

void ChinaMapWidget::resizeEvent(QResizeEvent* event)
{
    getGeoCenter();
    calScreenPoint();
    update();
}

void ChinaMapWidget::mouseMoveEvent(QMouseEvent* event)
{
    update();
}

void ChinaMapWidget::mousePressEvent(QMouseEvent* event)
{
    QPointF pt = mapFromGlobal(cursor().pos());
    for (int i = 0; i < m_mapobjects.count(); i++) {
        ChinaMapWidgetObject* obj = m_mapobjects.at(i);
        obj->setSelected(false);
        QList<QPolygonF> areas = obj->areas();
        for (int j = 0; j < areas.count(); j++) {
            QPolygonF pol = areas.at(j);

            QPointF ptf(pt.x(), pt.y());
            if (pol.containsPoint(ptf, Qt::WindingFill)) {
                obj->setSelected(true);
            }
        }
    }
    update();
}

void ChinaMapWidget::geoPointToScreenPoint(double geoX, double geoY, double& x, double& y)
{
    x = m_center.x() + ((geoX - m_geoCenter.x()) / m_resloution);
    y = m_center.y() - ((geoY - m_geoCenter.y()) / m_resloution);
}

void ChinaMapWidget::screenPointToGeoPoint(double x, double y, double& geoX, double& geoY)
{
    geoX = (x - m_center.x()) * m_resloution + m_geoCenter.x();
    geoY = m_geoCenter.y() - (y - m_center.y()) * m_resloution;
}
