#include "addressbook.h"
#include <QDebug>

AddressBook::AddressBook(QObject *parent)
    : QObject(parent), m_vipCount(0)
{
}

AddressBook::~AddressBook()
{
    // Clean up all Person objects
    qDeleteAll(m_people);
    m_people.clear();
    m_nameIndex.clear();
}

int AddressBook::contactCount() const
{
    return m_people.size();
}

int AddressBook::vipCount() const
{
    return m_vipCount;
}

void AddressBook::addPerson(Person *person)
{
    if (!person || m_people.contains(person)) {
        return;
    }
    
    // Connect to the person's signals
    connect(person, &Person::vipChanged, this, &AddressBook::onPersonVipChanged);
    connect(person, &Person::fullNameChanged, [this, person](const QString &oldName) {
        // Update the name index when a person's name changes
        m_nameIndex.remove(oldName);
        m_nameIndex[person->fullName()] = person;
    });
    
    // Add the person to our collections
    m_people.append(person);
    m_nameIndex[person->fullName()] = person;
    
    // Update VIP count if needed
    if (person->isVip()) {
        m_vipCount++;
        emit vipCountChanged(m_vipCount);
    }
    
    // Emit signals
    emit contactCountChanged(contactCount());
    emit personAdded(person);
}

void AddressBook::removePerson(Person *person)
{
    if (!person || !m_people.contains(person)) {
        return;
    }
    
    // Disconnect from the person's signals
    disconnect(person, &Person::vipChanged, this, &AddressBook::onPersonVipChanged);
    
    // Remove the person from our collections
    m_people.removeOne(person);
    m_nameIndex.remove(person->fullName());
    
    // Update VIP count if needed
    if (person->isVip()) {
        m_vipCount--;
        emit vipCountChanged(m_vipCount);
    }
    
    // Emit signals
    emit contactCountChanged(contactCount());
    emit personRemoved(person);
}

Person* AddressBook::getPersonByName(const QString &fullName) const
{
    return m_nameIndex.value(fullName, nullptr);
}

QList<Person*> AddressBook::getAllPeople() const
{
    return m_people;
}

QList<Person*> AddressBook::getAllVips() const
{
    QList<Person*> vips;
    for (Person *person : m_people) {
        if (person->isVip()) {
            vips.append(person);
        }
    }
    return vips;
}

void AddressBook::printAllContacts() const
{
    qDebug() << "Address Book Contents:";
    qDebug() << "Total Contacts:" << contactCount();
    qDebug() << "VIP Contacts:" << vipCount();
    qDebug() << "------------------------";
    
    for (const Person *person : m_people) {
        person->printInfo();
        qDebug() << "------------------------";
    }
}

void AddressBook::onPersonVipChanged(bool vip)
{
    // Get the person who emitted the signal
    Person *person = qobject_cast<Person*>(sender());
    if (!person) {
        return;
    }
    
    // Update VIP count
    if (vip) {
        m_vipCount++;
    } else {
        m_vipCount--;
    }
    
    emit vipCountChanged(m_vipCount);
}

void AddressBook::updateVipCount()
{
    int count = 0;
    for (const Person *person : m_people) {
        if (person->isVip()) {
            count++;
        }
    }
    
    if (m_vipCount != count) {
        m_vipCount = count;
        emit vipCountChanged(m_vipCount);
    }
}
