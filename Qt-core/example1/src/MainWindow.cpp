#include "MainWindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    // Create widgets
    m_label = new QLabel("Counter: 0", this);
    m_button = new QPushButton("Increment", this);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_label);
    layout->addWidget(m_button);

    // Connect button click to Counter::increment()
    connect(m_button, &QPushButton::clicked, &m_counter, &Counter::increment);

    // Connect Counter's signal to update the label
    connect(&m_counter, &Counter::valueChanged, this, &MainWindow::updateDisplay);

    setWindowTitle("Qt GUI Counter Example");
}

void MainWindow::updateDisplay(int value) {
    m_label->setText(QString("Counter: %1").arg(value));
}
