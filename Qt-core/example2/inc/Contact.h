#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QString>
#include <QSharedPointer>

class Contact : public QObject {
    Q_OBJECT
public:
    explicit Contact(QObject* parent = nullptr);
    Contact(const QString& name, const QString& phone, const QString& email, QObject* parent = nullptr);

    QString name() const;
    QString phone() const;
    QString email() const;

private:
    QString m_name;
    QString m_phone;
    QString m_email;
};

using ContactPtr = QSharedPointer<Contact>;

#endif // CONTACT_H