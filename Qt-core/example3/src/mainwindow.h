#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QGroupBox>
#include "addressbook.h"
#include "person.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    // Slots to handle UI interactions
    void addPerson();
    void clearForm();
    void displaySelectedPerson(int row);
    void updatePersonProperty();
    void updateVipStatus(int state);
    void showPropertyDemo();
    
private:
    // Private methods
    void setupUi();
    void updatePersonList();
    void updateContactCountLabel();
    void fillFormFromPerson(Person *person);
    
    // Property-related methods for the demo
    void showPropertyInfo(QObject *obj);
    void dynamicPropertyExample();
    
    // Data
    AddressBook *m_addressBook;
    Person *m_currentPerson;
    
    // UI elements
    QWidget *m_centralWidget;
    QLineEdit *m_firstNameEdit;
    QLineEdit *m_lastNameEdit;
    QDateEdit *m_birthDateEdit;
    QLineEdit *m_emailEdit;
    QLineEdit *m_phoneEdit;
    QCheckBox *m_vipCheckBox;
    QPushButton *m_addButton;
    QPushButton *m_clearButton;
    QPushButton *m_demoButton;
    QListWidget *m_personListWidget;
    QLabel *m_contactCountLabel;
    QLabel *m_vipCountLabel;
    QGroupBox *m_formGroupBox;
};

#endif // MAINWINDOW_H
