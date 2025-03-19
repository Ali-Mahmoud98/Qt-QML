#include <QCoreApplication>
#include "Counter.h"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    Counter counter;

    // Connect signal to a lambda slot
    QObject::connect(&counter, &Counter::valueChanged, [](int val) {
        qDebug() << "Current value:" << val;
    });

    // Trigger the increment
    counter.increment();

    return app.exec(); // Start the event loop
}
