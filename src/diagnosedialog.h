#ifndef DIAGNOSE_DIALOG_H
#define DIAGNOSE_DIALOG_H

#include "diagnosewidget.h"
#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

class DiagnoseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DiagnoseDialog(QWidget *parent = nullptr);

private slots:
    void onCloseClicked();

private:
    void setupUI();

    DiagnoseWidget *m_diagnoseWidget;
    QPushButton *m_closeButton;
};

#endif // DIAGNOSE_DIALOG_H