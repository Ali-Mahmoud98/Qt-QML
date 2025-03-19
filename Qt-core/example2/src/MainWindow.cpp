#include "MainWindow.h"
#include "ContactDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    updateContactList();
}

void MainWindow::setupUI() {
    // Widgets initialization
    m_contactList = new QListWidget(this);
    m_nameLabel = new QLabel("Name:", this);
    m_phoneLabel = new QLabel("Phone:", this);
    m_emailLabel = new QLabel("Email:", this);
    m_addButton = new QPushButton("Add Contact", this);
    m_removeButton = new QPushButton("Remove Contact", this);

    // Layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    mainLayout->addWidget(m_contactList);
    mainLayout->addWidget(m_nameLabel);
    mainLayout->addWidget(m_phoneLabel);
    mainLayout->addWidget(m_emailLabel);
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_removeButton);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);
    setWindowTitle("Contact Manager");
    resize(400, 300);

    // Connections
    connect(m_contactList, &QListWidget::itemClicked, this, &MainWindow::showContactDetails);
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::addContact);
    connect(m_removeButton, &QPushButton::clicked, this, &MainWindow::removeContact);
}

void MainWindow::updateContactList() {
    m_contactList->clear();
    for (const auto& contact : m_contacts) {
        new QListWidgetItem(contact->name(), m_contactList);
    }
}

void MainWindow::showContactDetails(QListWidgetItem* item) {
    if (auto contact = m_contactsHash.value(item->text())) {
        m_nameLabel->setText("Name: " + contact->name());
        m_phoneLabel->setText("Phone: " + contact->phone());
        m_emailLabel->setText("Email: " + contact->email());
    }
}

void MainWindow::addContact() {
    QScopedPointer<ContactDialog> dialog(new ContactDialog(this));
    if (dialog->exec() == QDialog::Accepted) {
        auto contact = dialog->getContact();
        if (!m_contactsHash.contains(contact->name())) {
            m_contacts.append(contact);
            m_contactsHash.insert(contact->name(), contact);
            updateContactList();
        } else {
            QMessageBox::warning(this, "Duplicate", "Contact already exists!");
        }
    }
}

void MainWindow::removeContact() {
    if (auto currentItem = m_contactList->currentItem()) {
        QString name = currentItem->text();
        m_contactsHash.remove(name);
        m_contacts.erase(std::remove_if(m_contacts.begin(), m_contacts.end(),
            [&](const ContactPtr& c) { return c->name() == name; }), m_contacts.end());
        updateContactList();
    }
}
