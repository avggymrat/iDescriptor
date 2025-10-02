#ifndef DISKUSAGEBAR_H
#define DISKUSAGEBAR_H

#include <QTimer>
#include <QWidget>

class DiskUsageBar : public QWidget
{
    Q_OBJECT

public:
    explicit DiskUsageBar(QWidget *parent = nullptr);

    void setUsageInfo(const QString &type, const QString &formattedSize,
                      const QString &color, double percentage);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void showPopover();

private:
    QString m_type;
    QString m_formattedSize;
    QString m_color;
    double m_percentage;
    QTimer *m_hoverTimer;
};

#endif // DISKUSAGEBAR_H