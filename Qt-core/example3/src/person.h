#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>
#include <QDate>

class Person : public QObject
{
    Q_OBJECT
    
    // Define properties with READ, WRITE, and NOTIFY
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QDate birthDate READ birthDate WRITE setBirthDate NOTIFY birthDateChanged)
    Q_PROPERTY(int age READ age NOTIFY birthDateChanged)
    Q_PROPERTY(QString fullName READ fullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    
    // Custom property that can be toggled
    Q_PROPERTY(bool vip READ isVip WRITE setVip NOTIFY vipChanged)
    
public:
    explicit Person(QObject *parent = nullptr);
    Person(const QString &firstName, const QString &lastName, QObject *parent = nullptr);
    ~Person();
    
    // Getters for properties
    QString firstName() const;
    QString lastName() const;
    QDate birthDate() const;
    int age() const;
    QString fullName() const;
    QString email() const;
    QString phone() const;
    bool isVip() const;
    
    // Setters for properties
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setBirthDate(const QDate &birthDate);
    void setEmail(const QString &email);
    void setPhone(const QString &phone);
    void setVip(bool vip);
    
    // Custom method to print person info
    void printInfo() const;
    
signals:
    // Notification signals for property changes
    void firstNameChanged(const QString &firstName);
    void lastNameChanged(const QString &lastName);
    void birthDateChanged(const QDate &birthDate);
    void fullNameChanged(const QString &fullName);
    void emailChanged(const QString &email);
    void phoneChanged(const QString &phone);
    void vipChanged(bool vip);
    
private:
    // Private data members
    QString m_firstName;
    QString m_lastName;
    QDate m_birthDate;
    QString m_email;
    QString m_phone;
    bool m_vip;
};

#endif // PERSON_H
