#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>
#include "Contact.h"

class QLineEdit;
class QDialogButtonBox;

class ContactDialog : public QDialog {
    Q_OBJECT

public:
    explicit ContactDialog(QWidget* parent = nullptr);
    ContactPtr getContact() const;

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_phoneEdit;
    QLineEdit* m_emailEdit;
    QDialogButtonBox* m_buttonBox;
};
#endif // CONTACTDIALOG_H
