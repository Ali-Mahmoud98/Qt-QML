#include "Contact.h"

Contact::Contact(QObject* parent) : QObject(parent) {}

Contact::Contact(const QString& name, const QString& phone, const QString& email, QObject* parent)
    : QObject(parent), m_name(name), m_phone(phone), m_email(email) {}

QString Contact::name() const { return m_name; }
QString Contact::phone() const { return m_phone; }
QString Contact::email() const { return m_email; }