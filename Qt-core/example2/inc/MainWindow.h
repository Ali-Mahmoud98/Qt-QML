#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QHash>
#include <QSharedPointer>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include "Contact.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void showContactDetails(QListWidgetItem* item);
    void addContact();
    void removeContact();

private:
    void setupUI();
    void updateContactList();

    QList<ContactPtr> m_contacts;
    QHash<QString, ContactPtr> m_contactsHash;

    // UI Elements
    QListWidget* m_contactList;
    QLabel* m_nameLabel;
    QLabel* m_phoneLabel;
    QLabel* m_emailLabel;
    QPushButton* m_addButton;
    QPushButton* m_removeButton;
};
#endif // MAINWINDOW_H
