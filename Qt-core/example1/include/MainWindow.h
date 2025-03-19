#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "Counter.h"

class MainWindow : public QWidget {
    Q_OBJECT // Required for Qt widgets
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void updateDisplay(int value);

private:
    Counter m_counter;
    QLabel* m_label;
    QPushButton* m_button;
};

#endif // MAINWINDOW_H