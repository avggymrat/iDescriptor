#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>

class BatteryWidget : public QWidget
{
    Q_OBJECT
public:
    BatteryWidget(float value, bool isCharging, QWidget *parent);
    bool getChargingState();
    void setChargingState(bool state);
    void updateContext(bool isCharging, float newValue);

    // New methods for value management
    void setValue(float newValue);
    float getValue() const;

private:
    QRectF widgetFrame;
    QRectF mainBatteryFrame;
    QRectF tipBatteryFrame;
    QRectF batteryLevelFrame;

    bool m_isCharging = false;

    float m_value = 0.0f;
    float m_minValue = 0.0f;
    float m_maxValue = 100.0f;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // BATTERYWIDGET_H
