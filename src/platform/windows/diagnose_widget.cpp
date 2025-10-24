#include "diagnose_widget.h"
#include "check_deps.h"
#include <QApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include <QTimer>
#include <QUrl>


DependencyItem::DependencyItem(const QString &name, const QString &description,
                               QWidget *parent)
    : QWidget(parent), m_name(name)
{
    setFixedHeight(80);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 5, 10, 5);

    // Left side - info
    QVBoxLayout *infoLayout = new QVBoxLayout();

    m_nameLabel = new QLabel(name);
    QFont nameFont = m_nameLabel->font();
    nameFont.setBold(true);
    nameFont.setPointSize(nameFont.pointSize() + 1);
    m_nameLabel->setFont(nameFont);

    m_descriptionLabel = new QLabel(description);
    m_descriptionLabel->setWordWrap(true);

    infoLayout->addWidget(m_nameLabel);
    infoLayout->addWidget(m_descriptionLabel);

    // Middle - status
    m_statusLabel = new QLabel("Checking...");
    m_statusLabel->setMinimumWidth(100);
    m_statusLabel->setAlignment(Qt::AlignCenter);

    // Right side - actions
    QVBoxLayout *actionLayout = new QVBoxLayout();

    m_installButton = new QPushButton("Install");
    m_installButton->setMinimumWidth(80);
    m_installButton->setVisible(false);
    connect(m_installButton, &QPushButton::clicked, this,
            &DependencyItem::onInstallClicked);

    m_progressBar = new QProgressBar();
    m_progressBar->setRange(0, 0); // Indeterminate
    m_progressBar->setVisible(false);
    m_progressBar->setMaximumHeight(20);

    actionLayout->addWidget(m_installButton);
    actionLayout->addWidget(m_progressBar);
    actionLayout->addStretch();

    layout->addLayout(infoLayout, 1);
    layout->addWidget(m_statusLabel);
    layout->addLayout(actionLayout);
}

void DependencyItem::setInstalled(bool installed)
{
    setChecking(false);

    if (installed) {
        m_statusLabel->setText("✓ Installed");
        m_statusLabel->setStyleSheet("color: green; font-weight: bold;");
        m_installButton->setVisible(false);
    } else {
        m_statusLabel->setText("✗ Not Installed");
        m_statusLabel->setStyleSheet("color: red; font-weight: bold;");
        m_installButton->setVisible(true);
    }
}

void DependencyItem::setChecking(bool checking)
{
    if (checking) {
        m_statusLabel->setText("Checking...");
        m_statusLabel->setStyleSheet("color: gray;");
        m_installButton->setVisible(false);
        m_progressBar->setVisible(false);
    }
}

void DependencyItem::onInstallClicked() { emit installRequested(m_name); }

DiagnoseWidget::DiagnoseWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();

    // Add dependency items
    addDependencyItem("Apple Mobile Device Support",
                      "Required for iOS device communication");
    addDependencyItem("WinFsp",
                      "Required for filesystem operations and mounting");

    // Auto-check on startup
    QTimer::singleShot(100, this, &DiagnoseWidget::checkDependencies);
}

void DiagnoseWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(10);

    // Title and summary
    QLabel *titleLabel = new QLabel("Dependency Check");
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 2);
    titleLabel->setFont(titleFont);

    m_summaryLabel = new QLabel("Checking system dependencies...");

    // Check button
    m_checkButton = new QPushButton("Refresh Check");
    m_checkButton->setMaximumWidth(150);
    connect(m_checkButton, &QPushButton::clicked, this,
            &DiagnoseWidget::checkDependencies);

    // Scroll area for dependency items
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(true);
    // m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarNever);
    m_scrollArea->setMinimumHeight(200);

    m_itemsWidget = new QWidget();
    m_itemsLayout = new QVBoxLayout(m_itemsWidget);
    m_itemsLayout->setSpacing(5);
    m_itemsLayout->addStretch();

    m_scrollArea->setWidget(m_itemsWidget);

    // Layout assembly
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_checkButton);

    m_mainLayout->addLayout(headerLayout);
    m_mainLayout->addWidget(m_summaryLabel);
    m_mainLayout->addWidget(m_scrollArea, 1);
}

void DiagnoseWidget::addDependencyItem(const QString &name,
                                       const QString &description)
{
    DependencyItem *item = new DependencyItem(name, description);
    item->setProperty("name", name); // Set the name property for identification
    connect(item, &DependencyItem::installRequested, this,
            &DiagnoseWidget::onInstallRequested);

    m_dependencyItems.append(item);

    // Insert before the stretch
    m_itemsLayout->insertWidget(m_itemsLayout->count() - 1, item);
}

void DiagnoseWidget::checkDependencies()
{
    m_summaryLabel->setText("Checking system dependencies...");
    m_checkButton->setEnabled(false);

    // Reset all items to checking state
    for (DependencyItem *item : m_dependencyItems) {
        item->setChecking(true);
    }

    // Simulate async checking with timer
    QTimer::singleShot(500, [this]() {
        int installedCount = 0;
        int totalCount = m_dependencyItems.size();

        for (DependencyItem *item : m_dependencyItems) {
            bool installed = false;
            QString itemName = item->property("name").toString();

            if (itemName == "Apple Mobile Device Support") {
                installed = IsAppleMobileDeviceSupportInstalled();
            } else if (itemName == "WinFsp") {
                installed = IsWinFspInstalled();
            }

            item->setInstalled(installed);
            if (installed)
                installedCount++;
        }

        // Update summary
        if (installedCount == totalCount) {
            m_summaryLabel->setText(
                QString("All dependencies are installed (%1/%2)")
                    .arg(installedCount)
                    .arg(totalCount));
            m_summaryLabel->setStyleSheet("color: green; font-weight: bold;");
        } else {
            m_summaryLabel->setText(
                QString("Missing dependencies (%1/%2 installed)")
                    .arg(installedCount)
                    .arg(totalCount));
            m_summaryLabel->setStyleSheet("color: red; font-weight: bold;");
        }

        m_checkButton->setEnabled(true);
    });
}

void DiagnoseWidget::onInstallRequested(const QString &name)
{
    QString url;
    QString message;

    if (name == "Apple Mobile Device Support") {
        url = "https://support.apple.com/downloads/itunes";
        message = "Apple Mobile Device Support is typically installed with "
                  "iTunes.\n\n"
                  "Would you like to open the iTunes download page?";
    } else if (name == "WinFsp") {
        url = "https://winfsp.dev/rel/";
        message = "WinFsp can be downloaded from the official website.\n\n"
                  "Would you like to open the WinFsp download page?";
    }

    if (!url.isEmpty()) {
        int ret = QMessageBox::question(this, "Install " + name, message,
                                        QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::Yes) {
            QDesktopServices::openUrl(QUrl(url));
        }
    }
}
