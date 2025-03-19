#ifndef DASHBOARDMANAGER_H
#define DASHBOARDMANAGER_H

#include <QObject>
#include <QTimer>

class DashboardManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(int currentSpeed READ currentSpeed WRITE setCurrentSpeed NOTIFY speedChanged)
    Q_PROPERTY(int fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    Q_PROPERTY(bool engineWarning READ engineWarning WRITE setEngineWarning NOTIFY engineWarningChanged)
    Q_PROPERTY(QString currentGear READ currentGear WRITE setCurrentGear NOTIFY gearChanged)

public:
    explicit DashboardManager(QObject *parent = nullptr);

    int currentSpeed() const;
    void setCurrentSpeed(int speed);

    int fuelLevel() const;
    void setFuelLevel(int level);

    bool engineWarning() const;
    void setEngineWarning(bool warning);

    QString currentGear() const;
    void setCurrentGear(const QString &gear);

    Q_INVOKABLE void simulateDriving();

signals:
    void speedChanged();
    void fuelLevelChanged();
    void engineWarningChanged();
    void gearChanged();

private:
    int m_currentSpeed;
    int m_fuelLevel;
    bool m_engineWarning;
    QString m_currentGear;
    QTimer m_simulationTimer;
};

#endif // DASHBOARDMANAGER_H
