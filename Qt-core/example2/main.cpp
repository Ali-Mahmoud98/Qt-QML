#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    // Demonstrate STL smart pointer with Qt object
    std::unique_ptr<MainWindow> mainWindow = std::make_unique<MainWindow>();
    mainWindow->show();
    
    return app.exec();
}
