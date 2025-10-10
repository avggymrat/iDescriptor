// https://github.com/p-dobrzynski-dev/QtCustomWidgets/blob/master/batterywidget.cpp
#include "batterywidget.h"

#include <QApplication>
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

BatteryWidget::BatteryWidget(float value, bool isCharging, QWidget *parent)
    : QWidget(parent), m_value(value), m_isCharging(isCharging)
{
    setMinimumSize(30, 30);
    setMaximumSize(40, 40);

    connect(qApp, &QApplication::paletteChanged, this, [this]() { update(); });
}

void BatteryWidget::resizeEvent(QResizeEvent *)
{
    widgetFrame = this->rect();

    widgetFrame.setSize(QSize(widgetFrame.width(), widgetFrame.height() / 2));
    widgetFrame.moveTop(widgetFrame.center().y());

    float scaleValue = 0.95;
    QSizeF mainBatteryFrameSize =
        QSizeF(widgetFrame.width() * scaleValue, widgetFrame.height());
    mainBatteryFrame.setSize(mainBatteryFrameSize);

    mainBatteryFrame.moveTopLeft(widgetFrame.topLeft());

    QSizeF tipBatteryFrameSize =
        QSizeF(widgetFrame.width() / 3, widgetFrame.height() / 2);
    tipBatteryFrame.setSize(tipBatteryFrameSize);

    QPointF tipBatteryFramePoint =
        QPointF(widgetFrame.topRight().x() - tipBatteryFrameSize.width(),
                widgetFrame.topRight().y() + tipBatteryFrameSize.height() / 2);
    tipBatteryFrame.moveTopLeft(tipBatteryFramePoint);

    float batteryLevelOffset = mainBatteryFrame.height() / 20;
    QSizeF batteryLevelFrameSize =
        QSizeF(mainBatteryFrame.width() - 2 * batteryLevelOffset,
               mainBatteryFrame.height() - 2 * batteryLevelOffset);
    batteryLevelFrame.setSize(batteryLevelFrameSize);

    QPointF batteryFramePoint =
        QPointF(mainBatteryFrame.topLeft().x() + batteryLevelOffset,
                mainBatteryFrame.topLeft().y() + batteryLevelOffset);
    batteryLevelFrame.moveTopLeft(batteryFramePoint);
}

void BatteryWidget::setValue(float newValue)
{
    m_value = newValue;
    this->update();
}

float BatteryWidget::getValue() const { return m_value; }

void BatteryWidget::setChargingState(bool state)
{
    m_isCharging = state;
    this->update();
    this->repaint();
}

void BatteryWidget::updateContext(bool isCharging, float newValue)
{
    m_isCharging = isCharging;
    m_value = newValue;
    this->update();
    this->repaint();
}

bool BatteryWidget::getChargingState() { return m_isCharging; }

void BatteryWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);

    float widgetCorner = widgetFrame.height() / 15;

    QPainterPath FramePath;
    FramePath.setFillRule(Qt::WindingFill);
    FramePath.addRoundedRect(mainBatteryFrame, widgetCorner, widgetCorner);
    FramePath.addRoundedRect(tipBatteryFrame, widgetCorner, widgetCorner);
    FramePath = FramePath.simplified();

    pen.setColor(Qt::gray);
    pen.setWidth(widgetFrame.width() / 75);
    painter.setPen(pen);
    painter.drawPath(FramePath);

    painter.setBrush(QBrush(QColor("#44bd32")));
    painter.setPen(Qt::NoPen);
    QRectF batteryLevelRect = QRectF();
    QSize batterySizeRect =
        QSize(batteryLevelFrame.width() * m_value / m_maxValue,
              batteryLevelFrame.height());
    batteryLevelRect.setSize(batterySizeRect);
    batteryLevelRect.moveTo(batteryLevelFrame.topLeft());
    painter.drawRoundedRect(batteryLevelRect, widgetCorner, widgetCorner);

    pen.setColor(palette().color(QPalette::Text));
    painter.setPen(pen);
    QFont textFont = QFont();
    textFont.setPixelSize(widgetFrame.height() / 1.65);
    textFont.setWeight(QFont::Bold);
    painter.setFont(textFont);
    QFontMetrics fm(textFont);
    QString percentageLevelString = QString("%1%").arg(m_value);
    float textWidth = fm.horizontalAdvance(percentageLevelString);
    float textHeight = fm.height();

    QPointF textPosition = QPointF(widgetFrame.center().x() - textWidth / 2,
                                   widgetFrame.center().y() + textHeight / 3);
    painter.drawText(textPosition, percentageLevelString);
}