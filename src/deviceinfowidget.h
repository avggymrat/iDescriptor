#ifndef DEVICEINFOWIDGET_H
#define DEVICEINFOWIDGET_H
#include "batterywidget.h"
#include "iDescriptor.h"
#include <QLabel>
#include <QTimer>
#include <QWidget>

class DeviceInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceInfoWidget(iDescriptorDevice *device,
                              QWidget *parent = nullptr);

private slots:
    void onBatteryMoreClicked();

private:
    QPixmap getDeviceIcon(const std::string &productType);
    iDescriptorDevice *m_device;
    QTimer *m_updateTimer;
    void updateBatteryInfo();
    QLabel *m_chargingStatusLabel;
    QLabel *m_chargingWattsLabel;
    QLabel *m_cableTypeLabel;
    BatteryWidget *m_batteryWidget;
};

#endif // DEVICEINFOWIDGET_H
