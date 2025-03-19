#include "person.h"
#include <QDebug>

Person::Person(QObject *parent)
    : QObject(parent), m_vip(false)
{
}

Person::Person(const QString &firstName, const QString &lastName, QObject *parent)
    : QObject(parent), m_firstName(firstName), m_lastName(lastName), m_vip(false)
{
}

Person::~Person()
{
}

QString Person::firstName() const
{
    return m_firstName;
}

QString Person::lastName() const
{
    return m_lastName;
}

QDate Person::birthDate() const
{
    return m_birthDate;
}

int Person::age() const
{
    if (!m_birthDate.isValid()) {
        return 0;
    }
    
    QDate currentDate = QDate::currentDate();
    int age = currentDate.year() - m_birthDate.year();
    
    // Adjust age if birthday hasn't occurred yet this year
    if (currentDate.month() < m_birthDate.month() ||
        (currentDate.month() == m_birthDate.month() && 
         currentDate.day() < m_birthDate.day())) {
        age--;
    }
    
    return age;
}

QString Person::fullName() const
{
    return m_firstName + " " + m_lastName;
}

QString Person::email() const
{
    return m_email;
}

QString Person::phone() const
{
    return m_phone;
}

bool Person::isVip() const
{
    return m_vip;
}

void Person::setFirstName(const QString &firstName)
{
    if (m_firstName != firstName) {
        m_firstName = firstName;
        emit firstNameChanged(m_firstName);
        emit fullNameChanged(fullName());
    }
}

void Person::setLastName(const QString &lastName)
{
    if (m_lastName != lastName) {
        m_lastName = lastName;
        emit lastNameChanged(m_lastName);
        emit fullNameChanged(fullName());
    }
}

void Person::setBirthDate(const QDate &birthDate)
{
    if (m_birthDate != birthDate) {
        m_birthDate = birthDate;
        emit birthDateChanged(m_birthDate);
    }
}

void Person::setEmail(const QString &email)
{
    if (m_email != email) {
        m_email = email;
        emit emailChanged(m_email);
    }
}

void Person::setPhone(const QString &phone)
{
    if (m_phone != phone) {
        m_phone = phone;
        emit phoneChanged(m_phone);
    }
}

void Person::setVip(bool vip)
{
    if (m_vip != vip) {
        m_vip = vip;
        emit vipChanged(m_vip);
    }
}

void Person::printInfo() const
{
    qDebug() << "Person Information:";
    qDebug() << "  Name:" << fullName();
    qDebug() << "  Age:" << age();
    qDebug() << "  Email:" << email();
    qDebug() << "  Phone:" << phone();
    qDebug() << "  VIP:" << (isVip() ? "Yes" : "No");
}
