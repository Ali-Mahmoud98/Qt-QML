#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QMetaProperty>

// Custom demonstration of the property system
void demonstratePropertySystem()
{
    qDebug() << "==== Property System Demonstration ====";
    
    // Create a Person object
    Person *person = new Person("Example", "User");
    person->setBirthDate(QDate(1990, 5, 15));
    person->setEmail("example@example.com");
    person->setPhone("555-1234");
    
    // Print initial information
    qDebug() << "Initial Person Information:";
    qDebug() << "  Full Name:" << person->fullName();
    qDebug() << "  Age:" << person->age();
    qDebug() << "  Is VIP:" << (person->isVip() ? "Yes" : "No");
    
    // Use property system to get/set properties
    qDebug() << "\nAccessing properties via property system:";
    qDebug() << "  firstName property:" << person->property("firstName").toString();
    
    // Set property via property system
    qDebug() << "\nChanging lastName via property system:";
    person->setProperty("lastName", "Changed");
    qDebug() << "  Full Name after change:" << person->fullName();
    
    // Accessing a computed property
    qDebug() << "  Reading computed 'age' property:" << person->property("age").toInt();
    
    // Demonstrate dynamic properties
    qDebug() << "\nDynamic property demonstration:";
    person->setProperty("customNote", "This is a dynamic property");
    qDebug() << "  Custom note:" << person->property("customNote").toString();
    
    // List all properties
    qDebug() << "\nAll properties:";
    const QMetaObject *metaObj = person->metaObject();
    for (int i = 0; i < metaObj->propertyCount(); ++i) {
        QMetaProperty property = metaObj->property(i);
        qDebug() << "  " << property.name() << ":" << property.read(person).toString();
    }
    
    // Clean up
    delete person;
    
    qDebug() << "==== End of Demonstration ====\n";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Optional: Uncomment to run the demonstration
    // demonstratePropertySystem();
    
    MainWindow w;
    w.show();
    
    return a.exec();
}
