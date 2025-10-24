#include "diagnose_dialog.h"
#include <QApplication>

DiagnoseDialog::DiagnoseDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();

    setWindowTitle("System Dependencies");
    setModal(true);
    resize(500, 400);

    // Set clean close behavior
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void DiagnoseDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Add the main diagnose widget
    m_diagnoseWidget = new DiagnoseWidget();

    // Close button
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    m_closeButton = new QPushButton("Close");
    m_closeButton->setMinimumWidth(80);
    connect(m_closeButton, &QPushButton::clicked, this,
            &DiagnoseDialog::onCloseClicked);

    buttonLayout->addWidget(m_closeButton);

    // Layout assembly
    mainLayout->addWidget(m_diagnoseWidget, 1);
    mainLayout->addLayout(buttonLayout);
}

void DiagnoseDialog::onCloseClicked() { accept(); }