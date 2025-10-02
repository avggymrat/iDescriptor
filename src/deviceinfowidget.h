#ifndef DEVICEINFOWIDGET_H
#define DEVICEINFOWIDGET_H
#include "batterywidget.h"
#include "iDescriptor.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QTimer>
#include <QWidget>
class DeviceInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceInfoWidget(iDescriptorDevice *device,
                              QWidget *parent = nullptr);
    ~DeviceInfoWidget(); // added destructor

private slots:
    void onBatteryMoreClicked();

private:
    QPixmap getDeviceIcon(const std::string &productType);
    iDescriptorDevice *m_device;
    QTimer *m_updateTimer;
    void updateBatteryInfo();
    void updateChargingStatusIcon();
    QLabel *m_chargingStatusLabel;
    QLabel *m_chargingWattsWithCableTypeLabel;
    BatteryWidget *m_batteryWidget;
    QLabel *m_lightningIconLabel;

    QGraphicsView *m_graphicsView = nullptr;
    QGraphicsScene *m_graphicsScene = nullptr;
};

#endif // DEVICEINFOWIDGET_H
