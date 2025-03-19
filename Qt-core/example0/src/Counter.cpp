#include "Counter.h"

Counter::Counter(QObject* parent) : QObject(parent) {}

int Counter::value() const {
    return m_value;
}

void Counter::increment() {
    m_value++;
    emit valueChanged(m_value); // Emit signal when value changes
}
