# Qt Widgets and Core Concepts

## 1. Signals and Slots

Signals and slots are Qt's mechanism for communication between objects. This system replaces the traditional callback mechanism used in many frameworks.

### Key Concepts:
- **Signals**: Events emitted by objects when something happens
- **Slots**: Functions that are called in response to signals
- **Connections**: Link signals to slots

### Implementation:

#### Header File (widget.h)
```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void handleButtonClick();
    void updateCount(int count);

private:
    QPushButton *m_button;
    QLabel *m_label;
    int m_counter;
};

#endif // WIDGET_H
```

#### Implementation File (widget.cpp)
```cpp
#include "widget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_counter(0)
{
    m_button = new QPushButton("Click Me", this);
    m_label = new QLabel("Button not clicked yet", this);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_label);
    layout->addWidget(m_button);
    
    // Old-style connection syntax
    // connect(m_button, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    
    // New-style connection syntax (preferred)
    connect(m_button, &QPushButton::clicked, this, &Widget::handleButtonClick);
    
    // Connect with lambda expression
    connect(m_button, &QPushButton::clicked, [=]() {
        m_label->setText("Button clicked via lambda");
    });
    
    // Connect a signal to another signal
    connect(this, &Widget::countChanged, this, &Widget::updateCount);
}

Widget::~Widget()
{
}

void Widget::handleButtonClick()
{
    m_counter++;
    m_label->setText(QString("Button clicked %1 times").arg(m_counter));
    
    // Emit a custom signal
    emit countChanged(m_counter);
}

void Widget::updateCount(int count)
{
    qDebug() << "Count updated to:" << count;
}
```

### Creating Custom Signals:
```cpp
class Counter : public QObject
{
    Q_OBJECT
public:
    Counter() : m_value(0) {}
    
    void increment() {
        m_value++;
        emit valueChanged(m_value);
    }
    
signals:
    void valueChanged(int newValue);
    
private:
    int m_value;
};
```

## 2. Qt's Property System

Qt's property system allows for automatic integration with Qt's meta-object system, making properties accessible via QObject::property() and QObject::setProperty().

### Defining Properties:

```cpp
class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    
public:
    Person(QObject *parent = nullptr) : QObject(parent), m_age(0) {}
    
    QString name() const { return m_name; }
    void setName(const QString &name) {
        if (m_name != name) {
            m_name = name;
            emit nameChanged(name);
        }
    }
    
    int age() const { return m_age; }
    void setAge(int age) {
        if (m_age != age) {
            m_age = age;
            emit ageChanged(age);
        }
    }
    
signals:
    void nameChanged(const QString &name);
    void ageChanged(int age);
    
private:
    QString m_name;
    int m_age;
};
```

### Using Properties:

```cpp
Person *person = new Person();

// Using setter methods
person->setName("John");
person->setAge(30);

// Using property system
person->setProperty("name", "Alice");
person->setProperty("age", 25);

// Reading properties
QString name = person->property("name").toString();
int age = person->property("age").toInt();

qDebug() << "Name:" << name << "Age:" << age;
```

## 3. Common Widgets

Qt provides a rich set of pre-built widgets for creating user interfaces.

### Basic Widgets:

```cpp
// Main window components
QMainWindow *mainWindow = new QMainWindow();
QMenuBar *menuBar = mainWindow->menuBar();
QStatusBar *statusBar = mainWindow->statusBar();
QToolBar *toolBar = new QToolBar("Main Toolbar");
mainWindow->addToolBar(toolBar);

// Input widgets
QLineEdit *lineEdit = new QLineEdit("Edit me");
QTextEdit *textEdit = new QTextEdit("Multiple lines of text");
QSpinBox *spinBox = new QSpinBox();
QSlider *slider = new QSlider(Qt::Horizontal);
QComboBox *comboBox = new QComboBox();
comboBox->addItems({"Option 1", "Option 2", "Option 3"});
QCheckBox *checkBox = new QCheckBox("Check me");
QRadioButton *radioButton = new QRadioButton("Select me");

// Button widgets
QPushButton *pushButton = new QPushButton("Click Me");
QToolButton *toolButton = new QToolButton();
toolButton->setIcon(QIcon::fromTheme("document-open"));

// Display widgets
QLabel *label = new QLabel("Label text");
QProgressBar *progressBar = new QProgressBar();
progressBar->setValue(75);
```

### Container Widgets:

```cpp
QTabWidget *tabWidget = new QTabWidget();
QWidget *tab1 = new QWidget();
QWidget *tab2 = new QWidget();
tabWidget->addTab(tab1, "Tab 1");
tabWidget->addTab(tab2, "Tab 2");

QGroupBox *groupBox = new QGroupBox("Options");
QScrollArea *scrollArea = new QScrollArea();
QStackedWidget *stackedWidget = new QStackedWidget();
```

### Dialog Widgets:

```cpp
// Standard dialogs
QMessageBox::information(nullptr, "Information", "This is an information message");
QMessageBox::warning(nullptr, "Warning", "This is a warning message");
QMessageBox::critical(nullptr, "Error", "This is an error message");

bool result = QMessageBox::question(nullptr, "Confirmation", 
                                   "Do you want to proceed?", 
                                   QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;

// File dialogs
QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", 
                                              "", "All Files (*)");

// Input dialogs
QString text = QInputDialog::getText(nullptr, "Input", "Enter your name:");
int value = QInputDialog::getInt(nullptr, "Input", "Enter your age:", 25, 0, 120);
```

## 4. Layouts for UI Organization

Layouts automatically arrange widgets in a way that adapts to different screen sizes and resolutions.

### Basic Layouts:

```cpp
// Vertical layout (widgets arranged vertically)
QWidget *widget1 = new QWidget();
QVBoxLayout *vLayout = new QVBoxLayout(widget1);
vLayout->addWidget(new QPushButton("Button 1"));
vLayout->addWidget(new QPushButton("Button 2"));
vLayout->addWidget(new QPushButton("Button 3"));

// Horizontal layout (widgets arranged horizontally)
QWidget *widget2 = new QWidget();
QHBoxLayout *hLayout = new QHBoxLayout(widget2);
hLayout->addWidget(new QPushButton("Left"));
hLayout->addWidget(new QPushButton("Center"));
hLayout->addWidget(new QPushButton("Right"));

// Grid layout (widgets arranged in a grid)
QWidget *widget3 = new QWidget();
QGridLayout *gridLayout = new QGridLayout(widget3);
gridLayout->addWidget(new QPushButton("1,1"), 0, 0);
gridLayout->addWidget(new QPushButton("1,2"), 0, 1);
gridLayout->addWidget(new QPushButton("2,1"), 1, 0);
gridLayout->addWidget(new QPushButton("2,2"), 1, 1);
```

### Form Layout (Label-Field Pairs):

```cpp
QWidget *formWidget = new QWidget();
QFormLayout *formLayout = new QFormLayout(formWidget);
formLayout->addRow("Name:", new QLineEdit());
formLayout->addRow("Email:", new QLineEdit());
formLayout->addRow("Age:", new QSpinBox());
```

### Nested Layouts:

```cpp
QWidget *mainWidget = new QWidget();
QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

// Add a form at the top
QFormLayout *formLayout = new QFormLayout();
formLayout->addRow("Username:", new QLineEdit());
formLayout->addRow("Password:", new QLineEdit());
mainLayout->addLayout(formLayout);

// Add buttons at the bottom in a horizontal layout
QHBoxLayout *buttonLayout = new QHBoxLayout();
buttonLayout->addStretch(); // Push buttons to the right
buttonLayout->addWidget(new QPushButton("Cancel"));
buttonLayout->addWidget(new QPushButton("OK"));
mainLayout->addLayout(buttonLayout);
```

### Layout Policies:

```cpp
// Setting size policies
QPushButton *button = new QPushButton("Resizable Button");
button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

// Adding spacing and stretching
QHBoxLayout *layout = new QHBoxLayout();
layout->addWidget(new QPushButton("Left"));
layout->addSpacing(20); // Add 20 pixels of space
layout->addStretch(1);  // Add a stretch with stretch factor 1
layout->addWidget(new QPushButton("Right"));

// Setting margins
QVBoxLayout *layoutWithMargins = new QVBoxLayout();
layoutWithMargins->setContentsMargins(10, 10, 10, 10);
```

## Practical Example: Complete Form Application

Here's a practical example combining signals/slots, properties, widgets and layouts:

### Header (formapp.h)
```cpp
#ifndef FORMAPP_H
#define FORMAPP_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>

class FormApp : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    
public:
    FormApp(QWidget *parent = nullptr);
    
    QString username() const;
    void setUsername(const QString &username);
    
signals:
    void usernameChanged(const QString &username);
    void formSubmitted();
    
private slots:
    void validateForm();
    void submitForm();
    void resetForm();
    void updatePreview();
    
private:
    QLineEdit *m_nameEdit;
    QLineEdit *m_emailEdit;
    QSpinBox *m_ageSpinBox;
    QComboBox *m_countryCombo;
    QCheckBox *m_newsletterCheck;
    QPushButton *m_submitButton;
    QPushButton *m_resetButton;
    QLabel *m_previewLabel;
    QLabel *m_statusLabel;
};

#endif // FORMAPP_H
```

### Implementation (formapp.cpp)
```cpp
#include "formapp.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>

FormApp::FormApp(QWidget *parent)
    : QWidget(parent)
{
    // Create widgets
    m_nameEdit = new QLineEdit(this);
    m_emailEdit = new QLineEdit(this);
    m_ageSpinBox = new QSpinBox(this);
    m_countryCombo = new QComboBox(this);
    m_newsletterCheck = new QCheckBox("Subscribe to newsletter", this);
    m_submitButton = new QPushButton("Submit", this);
    m_resetButton = new QPushButton("Reset", this);
    m_previewLabel = new QLabel(this);
    m_statusLabel = new QLabel(this);
    
    // Configure widgets
    m_ageSpinBox->setRange(18, 120);
    m_ageSpinBox->setValue(25);
    
    m_countryCombo->addItems({"United States", "Canada", "United Kingdom", 
                             "Australia", "Germany", "France", "Other"});
    
    // Email validation using regular expression
    QRegularExpression emailRegex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,}\\b", 
                                 QRegularExpression::CaseInsensitiveOption);
    m_emailEdit->setValidator(new QRegularExpressionValidator(emailRegex, this));
    
    m_submitButton->setEnabled(false);
    m_previewLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_previewLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_previewLabel->setMinimumHeight(100);
    m_previewLabel->setWordWrap(true);
    
    m_statusLabel->setStyleSheet("QLabel { color: red; }");
    
    // Create layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Form layout
    QGroupBox *formGroupBox = new QGroupBox("User Information", this);
    QFormLayout *formLayout = new QFormLayout(formGroupBox);
    formLayout->addRow("Name:", m_nameEdit);
    formLayout->addRow("Email:", m_emailEdit);
    formLayout->addRow("Age:", m_ageSpinBox);
    formLayout->addRow("Country:", m_countryCombo);
    formLayout->addRow(m_newsletterCheck);
    
    // Preview group
    QGroupBox *previewGroupBox = new QGroupBox("Preview", this);
    QVBoxLayout *previewLayout = new QVBoxLayout(previewGroupBox);
    previewLayout->addWidget(m_previewLabel);
    
    // Button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_resetButton);
    buttonLayout->addWidget(m_submitButton);
    
    // Add to main layout
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(previewGroupBox);
    mainLayout->addWidget(m_statusLabel);
    mainLayout->addLayout(buttonLayout);
    
    // Connect signals and slots
    connect(m_nameEdit, &QLineEdit::textChanged, this, &FormApp::validateForm);
    connect(m_emailEdit, &QLineEdit::textChanged, this, &FormApp::validateForm);
    connect(m_ageSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &FormApp::updatePreview);
    connect(m_countryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FormApp::updatePreview);
    connect(m_newsletterCheck, &QCheckBox::stateChanged, this, &FormApp::updatePreview);
    
    connect(m_nameEdit, &QLineEdit::textChanged, this, &FormApp::updatePreview);
    connect(m_emailEdit, &QLineEdit::textChanged, this, &FormApp::updatePreview);
    
    connect(m_submitButton, &QPushButton::clicked, this, &FormApp::submitForm);
    connect(m_resetButton, &QPushButton::clicked, this, &FormApp::resetForm);
    
    // Set window properties
    setWindowTitle("Qt Form Application");
    resize(500, 400);
}

QString FormApp::username() const
{
    return m_nameEdit->text();
}

void FormApp::setUsername(const QString &username)
{
    if (m_nameEdit->text() != username) {
        m_nameEdit->setText(username);
        emit usernameChanged(username);
    }
}

void FormApp::validateForm()
{
    bool isValid = !m_nameEdit->text().isEmpty() && 
                  !m_emailEdit->text().isEmpty() &&
                  m_emailEdit->hasAcceptableInput();
    
    m_submitButton->setEnabled(isValid);
    
    if (!isValid) {
        if (m_nameEdit->text().isEmpty()) {
            m_statusLabel->setText("Please enter your name");
        } else if (m_emailEdit->text().isEmpty()) {
            m_statusLabel->setText("Please enter your email");
        } else if (!m_emailEdit->hasAcceptableInput()) {
            m_statusLabel->setText("Please enter a valid email address");
        }
    } else {
        m_statusLabel->clear();
    }
}

void FormApp::submitForm()
{
    QMessageBox::information(this, "Form Submitted", 
                            "Thank you, " + m_nameEdit->text() + 
                            ". Your information has been submitted.");
    
    emit formSubmitted();
    resetForm();
}

void FormApp::resetForm()
{
    m_nameEdit->clear();
    m_emailEdit->clear();
    m_ageSpinBox->setValue(25);
    m_countryCombo->setCurrentIndex(0);
    m_newsletterCheck->setChecked(false);
    m_previewLabel->clear();
    m_statusLabel->clear();
}

void FormApp::updatePreview()
{
    QString previewText = "Name: " + m_nameEdit->text() + "\n";
    previewText += "Email: " + m_emailEdit->text() + "\n";
    previewText += "Age: " + QString::number(m_ageSpinBox->value()) + "\n";
    previewText += "Country: " + m_countryCombo->currentText() + "\n";
    previewText += "Newsletter: " + QString(m_newsletterCheck->isChecked() ? "Yes" : "No");
    
    m_previewLabel->setText(previewText);
}
```

### Main Function (main.cpp)
```cpp
#include "formapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    FormApp form;
    form.show();
    
    return app.exec();
}
```
