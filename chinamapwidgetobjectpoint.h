#ifndef CHINAMAPWIDGETOBJECTPOINT_H
#define CHINAMAPWIDGETOBJECTPOINT_H

#include <QObject>

class ChinaMapWidgetObjectPoint : public QObject {
    Q_OBJECT
public:
    explicit ChinaMapWidgetObjectPoint(QObject* parent = nullptr);
    void setGeoX(double geoX);
    void setGeoY(double geoY);
    double geoX();
    double geoY();
    void setScreenX(double screenX);
    void setScreenY(double screenY);
    double screenX();
    double screenY();

private:
    double m_geoX;
    double m_geoY;
    double m_screenX;
    double m_screenY;
signals:

public slots:
};

#endif // CHINAMAPWIDGETOBJECTPOINT_H
