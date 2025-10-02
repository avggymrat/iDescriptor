#include <QMainWindow>
#include <QPoint>
#include <QString>
#include <QWidget>

struct UsageInfo {
    QString type;
    QString formattedSize;
    QString color;
    double percentage;
};

void setupMacOSWindow(QMainWindow *window);

void showPopoverForBarWidget(QWidget *widget, const UsageInfo &info);

void hidePopoverForBarWidget();