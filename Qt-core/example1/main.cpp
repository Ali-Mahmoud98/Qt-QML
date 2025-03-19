#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // Use QApplication for GUI apps

    MainWindow window;
    window.show(); // Display the window

    return app.exec(); // Start the event loop
}
