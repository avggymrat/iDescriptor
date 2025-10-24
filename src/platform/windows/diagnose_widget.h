#ifndef DIAGNOSE_WIDGET_H
#define DIAGNOSE_WIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>


class DependencyItem : public QWidget
{
    Q_OBJECT

public:
    explicit DependencyItem(const QString &name, const QString &description,
                            QWidget *parent = nullptr);
    void setInstalled(bool installed);
    void setChecking(bool checking);

signals:
    void installRequested(const QString &name);

private slots:
    void onInstallClicked();

private:
    QString m_name;
    QLabel *m_nameLabel;
    QLabel *m_descriptionLabel;
    QLabel *m_statusLabel;
    QPushButton *m_installButton;
    QProgressBar *m_progressBar;
};

class DiagnoseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DiagnoseWidget(QWidget *parent = nullptr);

public slots:
    void checkDependencies();

private slots:
    void onInstallRequested(const QString &name);

private:
    void setupUI();
    void addDependencyItem(const QString &name, const QString &description);

    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_itemsLayout;
    QPushButton *m_checkButton;
    QLabel *m_summaryLabel;
    QScrollArea *m_scrollArea;
    QWidget *m_itemsWidget;

    QList<DependencyItem *> m_dependencyItems;
};

#endif // DIAGNOSE_WIDGET_H