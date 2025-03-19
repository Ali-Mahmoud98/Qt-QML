#include "ContactDialog.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>

ContactDialog::ContactDialog(QWidget* parent) : QDialog(parent) {
    m_nameEdit = new QLineEdit(this);
    m_phoneEdit = new QLineEdit(this);
    m_emailEdit = new QLineEdit(this);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    QFormLayout* layout = new QFormLayout(this);
    layout->addRow("Name:", m_nameEdit);
    layout->addRow("Phone:", m_phoneEdit);
    layout->addRow("Email:", m_emailEdit);
    layout->addWidget(m_buttonBox);

    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

ContactPtr ContactDialog::getContact() const {
    return QSharedPointer<Contact>::create(
        m_nameEdit->text(),
        m_phoneEdit->text(),
        m_emailEdit->text()
    );
}
