#include "dashboardmanager.h"
#include <QRandomGenerator>

DashboardManager::DashboardManager(QObject *parent)
    : QObject(parent),
    m_currentSpeed(0),
    m_fuelLevel(100),
    m_engineWarning(false),
    m_currentGear("P")
{
    // Setup simulation timer
    connect(&m_simulationTimer, &QTimer::timeout, this, &DashboardManager::simulateDriving);
    m_simulationTimer.start(1000); // Update every second
}

int DashboardManager::currentSpeed() const {
    return m_currentSpeed;
}

void DashboardManager::setCurrentSpeed(int speed) {
    if (m_currentSpeed != speed) {
        m_currentSpeed = qBound(0, speed, 220);
        emit speedChanged();
    }
}

int DashboardManager::fuelLevel() const {
    return m_fuelLevel;
}

void DashboardManager::setFuelLevel(int level) {
    if (m_fuelLevel != level) {
        m_fuelLevel = qBound(0, level, 100);
        emit fuelLevelChanged();
    }
}

bool DashboardManager::engineWarning() const {
    return m_engineWarning;
}

void DashboardManager::setEngineWarning(bool warning) {
    if (m_engineWarning != warning) {
        m_engineWarning = warning;
        emit engineWarningChanged();
    }
}

QString DashboardManager::currentGear() const {
    return m_currentGear;
}

void DashboardManager::setCurrentGear(const QString &gear) {
    if (m_currentGear != gear) {
        m_currentGear = gear;
        emit gearChanged();
    }
}

void DashboardManager::simulateDriving() {
    // Simulate some random driving conditions
    int speedChange = QRandomGenerator::global()->bounded(-10, 15);
    int newSpeed = m_currentSpeed + speedChange;
    setCurrentSpeed(newSpeed);

    // Simulate fuel consumption
    if (newSpeed > 0) {
        int fuelConsumption = newSpeed / 20;
        setFuelLevel(m_fuelLevel - fuelConsumption);
    }

    // Random engine warning
    if (QRandomGenerator::global()->bounded(100) < 5) {
        setEngineWarning(true);
    }

    // Gear shifting simulation
    QStringList gears = {"P", "R", "N", "D"};
    if (QRandomGenerator::global()->bounded(100) < 10) {
        setCurrentGear(gears[QRandomGenerator::global()->bounded(gears.size())]);
    }
}
