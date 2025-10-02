#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

class CustomTab : public QPushButton
{
    Q_OBJECT

public:
    explicit CustomTab(const QString &text, QWidget *parent = nullptr);
    void setIcon(const QIcon &icon);
};

class CustomTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTabWidget(QWidget *parent = nullptr);
    void finalizeStyles();
    int addTab(QWidget *widget, const QString &label);
    int addTab(QWidget *widget, const QIcon &icon, const QString &label);
    void setCurrentIndex(int index);
    int currentIndex() const;
    QWidget *widget(int index) const;

signals:
    void currentChanged(int index);

private slots:
    void onTabClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QHBoxLayout *m_tabLayout;
    QVBoxLayout *m_mainLayout;
    QWidget *m_tabBar;
    QStackedWidget *m_stackedWidget;
    QButtonGroup *m_buttonGroup;
    QWidget *m_glider;
    QPropertyAnimation *m_gliderAnimation;
    QList<CustomTab *> m_tabs;
    QList<QWidget *> m_widgets;
    int m_currentIndex;

    void setupGlider();
    void animateGlider(int index);
    void updateTabStyles();
};

#endif // CUSTOMTABWIDGET_H