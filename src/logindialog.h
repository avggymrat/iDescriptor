#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "qprocessindicator.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedLayout>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);

    QString getEmail() const;
    QString getPassword() const;

private slots:
    void signIn();

private:
    QLineEdit *m_emailEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_signInButton;
    QPushButton *m_cancelButton;
    QProcessIndicator *m_indicator;
    QStackedLayout *m_signInStackedLayout;
};

#endif // LOGINDIALOG_H
