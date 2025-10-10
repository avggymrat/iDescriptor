#pragma once

#include <QApplication>
#include <QLineEdit>

class ZLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit ZLineEdit(QWidget *parent = nullptr);
    explicit ZLineEdit(const QString &text, QWidget *parent = nullptr);

private slots:
    void updateStyles();

private:
    void setupStyles();
};