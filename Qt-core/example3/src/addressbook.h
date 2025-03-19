#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QObject>
#include <QList>
#include <QMap>
#include "person.h"

class AddressBook : public QObject
{
    Q_OBJECT
    
    // Define a property for the total number of contacts
    Q_PROPERTY(int contactCount READ contactCount NOTIFY contactCountChanged)
    
    // Define a property for the number of VIP contacts
    Q_PROPERTY(int vipCount READ vipCount NOTIFY vipCountChanged)
    
public:
    explicit AddressBook(QObject *parent = nullptr);
    ~AddressBook();
    
    // Property getters
    int contactCount() const;
    int vipCount() const;
    
    // Add a new person to the address book
    void addPerson(Person *person);
    
    // Remove a person from the address book
    void removePerson(Person *person);
    
    // Get a person by their full name
    Person* getPersonByName(const QString &fullName) const;
    
    // Get all people in the address book
    QList<Person*> getAllPeople() const;
    
    // Get all VIP people
    QList<Person*> getAllVips() const;
    
    // Print all contacts to the console
    void printAllContacts() const;
    
signals:
    // Notification signals for property changes
    void contactCountChanged(int count);
    void vipCountChanged(int count);
    void personAdded(Person *person);
    void personRemoved(Person *person);
    
private slots:
    // Slot to handle when a person's VIP status changes
    void onPersonVipChanged(bool vip);
    
private:
    // Private data members
    QList<Person*> m_people;
    QMap<QString, Person*> m_nameIndex;
    int m_vipCount;
    
    // Update VIP count
    void updateVipCount();
};

#endif // ADDRESSBOOK_H
