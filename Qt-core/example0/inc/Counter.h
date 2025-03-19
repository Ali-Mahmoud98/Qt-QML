#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QDebug>

class Counter : public QObject
{
    Q_OBJECT // Required for signals/slots

public:
    explicit Counter(QObject* parent = nullptr);

    int value() const;

public slots:
    void increment();

signals:
    void valueChanged(int newValue);

private:
    int m_value = 0;
};

#endif // COUNTER_H
