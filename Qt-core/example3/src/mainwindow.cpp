#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSplitter>
#include <QMessageBox>
#include <QMetaProperty>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_currentPerson(nullptr)
{
    m_addressBook = new AddressBook(this);
    
    // Create some sample data
    Person *john = new Person("John", "Doe", m_addressBook);
    john->setBirthDate(QDate(1980, 5, 15));
    john->setEmail("john.doe@example.com");
    john->setPhone("555-1234");
    m_addressBook->addPerson(john);
    
    Person *jane = new Person("Jane", "Smith", m_addressBook);
    jane->setBirthDate(QDate(1985, 8, 22));
    jane->setEmail("jane.smith@example.com");
    jane->setPhone("555-5678");
    jane->setVip(true);
    m_addressBook->addPerson(jane);
    
    Person *bob = new Person("Bob", "Johnson", m_addressBook);
    bob->setBirthDate(QDate(1975, 3, 10));
    bob->setEmail("bob.johnson@example.com");
    bob->setPhone("555-9876");
    m_addressBook->addPerson(bob);
    
    setupUi();
    updatePersonList();
    updateContactCountLabel();
    
    // Connect AddressBook signals
    connect(m_addressBook, &AddressBook::contactCountChanged, 
            this, &MainWindow::updateContactCountLabel);
    connect(m_addressBook, &AddressBook::vipCountChanged, 
            [this](int count) {
                m_vipCountLabel->setText(QString("VIP Contacts: %1").arg(count));
            });
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    // Set up the central widget
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    // Create the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(m_centralWidget);
    
    // Create a splitter to divide the window
    QSplitter *splitter = new QSplitter(Qt::Horizontal, m_centralWidget);
    mainLayout->addWidget(splitter);
    
    // Left side - Person list
    QWidget *leftWidget = new QWidget(splitter);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    
    m_personListWidget = new QListWidget(leftWidget);
    leftLayout->addWidget(m_personListWidget);
    
    m_contactCountLabel = new QLabel("Total Contacts: 0", leftWidget);
    leftLayout->addWidget(m_contactCountLabel);
    
    m_vipCountLabel = new QLabel("VIP Contacts: 0", leftWidget);
    leftLayout->addWidget(m_vipCountLabel);
    
    m_demoButton = new QPushButton("Property System Demo", leftWidget);
    leftLayout->addWidget(m_demoButton);
    
    // Right side - Person form
    QWidget *rightWidget = new QWidget(splitter);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    
    m_formGroupBox = new QGroupBox("Person Details", rightWidget);
    QFormLayout *formLayout = new QFormLayout(m_formGroupBox);
    
    m_firstNameEdit = new QLineEdit(m_formGroupBox);
    formLayout->addRow("First Name:", m_firstNameEdit);
    
    m_lastNameEdit = new QLineEdit(m_formGroupBox);
    formLayout->addRow("Last Name:", m_lastNameEdit);
    
    m_birthDateEdit = new QDateEdit(m_formGroupBox);
    m_birthDateEdit->setCalendarPopup(true);
    m_birthDateEdit->setDate(QDate::currentDate());
    formLayout->addRow("Birth Date:", m_birthDateEdit);
    
    m_emailEdit = new QLineEdit(m_formGroupBox);
    formLayout->addRow("Email:", m_emailEdit);
    
    m_phoneEdit = new QLineEdit(m_formGroupBox);
    formLayout->addRow("Phone:", m_phoneEdit);
    
    m_vipCheckBox = new QCheckBox("VIP Contact", m_formGroupBox);
    formLayout->addRow("", m_vipCheckBox);
    
    rightLayout->addWidget(m_formGroupBox);
    
    // Button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_addButton = new QPushButton("Add Person", rightWidget);
    m_clearButton = new QPushButton("Clear Form", rightWidget);
    
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_clearButton);
    rightLayout->addLayout(buttonLayout);
    
    // Set up splitter
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    
    // Set window properties
    setWindowTitle("Qt Property System Example");
    resize(800, 500);
    
    // Connect signals/slots
    connect(m_personListWidget, &QListWidget::currentRowChanged, 
            this, &MainWindow::displaySelectedPerson);
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::addPerson);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::clearForm);
    connect(m_demoButton, &QPushButton::clicked, this, &MainWindow::showPropertyDemo);
    
    // Connect form field changes to update property
    connect(m_firstNameEdit, &QLineEdit::textChanged, this, &MainWindow::updatePersonProperty);
    connect(m_lastNameEdit, &QLineEdit::textChanged, this, &MainWindow::updatePersonProperty);
    connect(m_birthDateEdit, &QDateEdit::dateChanged, this, &MainWindow::updatePersonProperty);
    connect(m_emailEdit, &QLineEdit::textChanged, this, &MainWindow::updatePersonProperty);
    connect(m_phoneEdit, &QLineEdit::textChanged, this, &MainWindow::updatePersonProperty);
    connect(m_vipCheckBox, &QCheckBox::stateChanged, this, &MainWindow::updateVipStatus);
}

void MainWindow::addPerson()
{
    // If m_currentPerson is not null, we're editing a person
    if (m_currentPerson) {
        m_currentPerson = nullptr;
        m_addButton->setText("Add Person");
        clearForm();
        return;
    }
    
    // Create a new person with data from the form
    Person *person = new Person(m_addressBook);
    
    person->setFirstName(m_firstNameEdit->text());
    person->setLastName(m_lastNameEdit->text());
    person->setBirthDate(m_birthDateEdit->date());
    person->setEmail(m_emailEdit->text());
    person->setPhone(m_phoneEdit->text());
    person->setVip(m_vipCheckBox->isChecked());
    
    // Add to the address book
    m_addressBook->addPerson(person);
    
    // Update UI
    updatePersonList();
    clearForm();
}

void MainWindow::clearForm()
{
    m_firstNameEdit->clear();
    m_lastNameEdit->clear();
    m_birthDateEdit->setDate(QDate::currentDate());
    m_emailEdit->clear();
    m_phoneEdit->clear();
    m_vipCheckBox->setChecked(false);
    
    m_currentPerson = nullptr;
    m_addButton->setText("Add Person");
    m_personListWidget->clearSelection();
}

void MainWindow::displaySelectedPerson(int row)
{
    if (row < 0 || row >= m_personListWidget->count()) {
        clearForm();
        return;
    }
    
    QString fullName = m_personListWidget->item(row)->text();
    m_currentPerson = m_addressBook->getPersonByName(fullName);
    
    if (m_currentPerson) {
        fillFormFromPerson(m_currentPerson);
        m_addButton->setText("Cancel Edit");
    }
}

void MainWindow::updatePersonProperty()
{
    if (!m_currentPerson) {
        return;
    }
    
    // Block signals to prevent recursive updates
    m_personListWidget->blockSignals(true);
    
    // Update the person with values from the form
    m_currentPerson->setFirstName(m_firstNameEdit->text());
    m_currentPerson->setLastName(m_lastNameEdit->text());
    m_currentPerson->setBirthDate(m_birthDateEdit->date());
    m_currentPerson->setEmail(m_emailEdit->text());
    m_currentPerson->setPhone(m_phoneEdit->text());
    
    // Update list widget
    updatePersonList();
    
    // Restore signals
    m_personListWidget->blockSignals(false);
}

void MainWindow::updateVipStatus(int state)
{
    if (m_currentPerson) {
        m_currentPerson->setVip(state == Qt::Checked);
    }
}

void MainWindow::showPropertyDemo()
{
    // Create a new demo person
    Person *demoPerson = new Person("Demo", "Person", this);
    demoPerson->setBirthDate(QDate(1990, 1, 1));
    demoPerson->setEmail("demo@example.com");
    
    // Show property info for this object
    showPropertyInfo(demoPerson);
    
    // Demonstrate dynamic property system
    dynamicPropertyExample();
    
    // Clean up
    delete demoPerson;
}

void MainWindow::updatePersonList()
{
    m_personListWidget->clear();
    
    for (Person *person : m_addressBook->getAllPeople()) {
        QListWidgetItem *item = new QListWidgetItem(person->fullName());
        
        // Show VIPs in bold
        if (person->isVip()) {
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
        }
        
        m_personListWidget->addItem(item);
    }
}

void MainWindow::updateContactCountLabel()
{
    m_contactCountLabel->setText(QString("Total Contacts: %1").arg(m_addressBook->contactCount()));
}

void MainWindow::fillFormFromPerson(Person *person)
{
    if (!person) {
        return;
    }
    
    // Block signals to prevent recursive updates
    m_firstNameEdit->blockSignals(true);
    m_lastNameEdit->blockSignals(true);
    m_birthDateEdit->blockSignals(true);
    m_emailEdit->blockSignals(true);
    m_phoneEdit->blockSignals(true);
    m_vipCheckBox->blockSignals(true);
    
    // Fill the form with person data
    m_firstNameEdit->setText(person->firstName());
    m_lastNameEdit->setText(person->lastName());
    m_birthDateEdit->setDate(person->birthDate());
    m_emailEdit->setText(person->email());
    m_phoneEdit->setText(person->phone());
    m_vipCheckBox->setChecked(person->isVip());
    
    // Restore signals
    m_firstNameEdit->blockSignals(false);
    m_lastNameEdit->blockSignals(false);
    m_birthDateEdit->blockSignals(false);
    m_emailEdit->blockSignals(false);
    m_phoneEdit->blockSignals(false);
    m_vipCheckBox->blockSignals(false);
}

void MainWindow::showPropertyInfo(QObject *obj)
{
    QString info = "Property Information\n";
    info += "===================\n\n";
    
    const QMetaObject *metaObject = obj->metaObject();
    info += QString("Class: %1\n").arg(metaObject->className());
    info += QString("Property Count: %1\n\n").arg(metaObject->propertyCount());
    
    // List all properties
    info += "Properties:\n";
    for (int i = 0; i < metaObject->propertyCount(); i++) {
        QMetaProperty property = metaObject->property(i);
        info += QString("- %1 (Type: %2)\n").arg(property.name()).arg(property.typeName());
        
        // Property attributes
        QStringList attributes;
        if (property.isReadable()) attributes << "Readable";
        if (property.isWritable()) attributes << "Writable";
        if (property.isResettable()) attributes << "Resettable";
        if (property.hasNotifySignal()) attributes << "Has Notify Signal";
        if (property.isConstant()) attributes << "Constant";
        if (property.isDesignable()) attributes << "Designable";
        if (property.isScriptable()) attributes << "Scriptable";
        if (property.isStored()) attributes << "Stored";
        if (property.isUser()) attributes << "User";
        if (property.isFinal()) attributes << "Final";
        
        info += "  Attributes: " + attributes.join(", ") + "\n";
        
        // Current value
        info += QString("  Current Value: %1\n").arg(property.read(obj).toString());
    }
    
    // Show in a message box
    QMessageBox::information(this, "Property Information", info);
}

void MainWindow::dynamicPropertyExample()
{
    QString info = "Dynamic Property Example\n";
    info += "========================\n\n";
    
    // Create a temporary object
    QObject *tmpObj = new QObject(this);
    
    // Set some dynamic properties
    tmpObj->setProperty("customInt", 42);
    tmpObj->setProperty("customString", "Dynamic Property");
    tmpObj->setProperty("customDate", QDate::currentDate());
    
    // List properties before
    info += "Before removal:\n";
    for (const QByteArray& propName : tmpObj->dynamicPropertyNames()) {
        info += QString("- %1: %2\n")
                .arg(QString(propName))
                .arg(tmpObj->property(propName).toString());
    }
    
    // Remove a property
    tmpObj->setProperty("customInt", QVariant());
    
    // List properties after
    info += "\nAfter removal:\n";
    for (const QByteArray& propName : tmpObj->dynamicPropertyNames()) {
        info += QString("- %1: %2\n")
                .arg(QString(propName))
                .arg(tmpObj->property(propName).toString());
    }
    
    // Universal property access
    info += "\nUniversal Property Access:\n";
    
    // Access Person properties by name
    Person *person = m_addressBook->getAllPeople().first();
    
    info += QString("- person->property(\"firstName\"): %1\n")
            .arg(person->property("firstName").toString());
    
    info += QString("- person->property(\"age\"): %1\n")
            .arg(person->property("age").toInt());
    
    // Clean up
    delete tmpObj;
    
    // Show in a message box
    QMessageBox::information(this, "Dynamic Properties", info);
}
