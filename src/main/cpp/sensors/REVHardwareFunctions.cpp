#include "sensors/ValorCANdleSensor.h"

ValorCANdleSensor::RGBColor ValorCANdleSensor::toRGB(int color)
{
    RGBColor outColor;
    outColor.red = ((color & 0xFF0000) >> 16);
    outColor.green = ((color & 0x00FF00) >> 8);
    outColor.blue = ((color & 0x0000FF));
    return outColor;
}

ValorCANdleSensor::~ValorCANdleSensor()
{
    clearAnimation();
}

void ValorCANdleSensor::setColor(int r, int g, int b)
{
    candle.SetLEDs(r,g,b,0,0,8 + ledCount);
}

void ValorCANdleSensor::setColor(int color)
{
    currentColor = toRGB(color);
    candle.SetLEDs(currentColor.red, currentColor.green, currentColor.blue,0,0,8 + ledCount);
}

void ValorCANdleSensor::reset()
{
    clearAnimation();
    prevState = 0xFFFFFF;
    currState = 0xFFFFFF;
}

void ValorCANdleSensor::calculate()
{
    //add code later on
}

void ValorCANdleSensor::InitSendable(wpi::SendableBuilder& builder)
{
    builder.SetSmartDashboardType("Subsystem");
    builder.AddDoubleProperty(
        "Current State", 
        [this] { return prevState; },
        nullptr);
    builder.AddDoubleProperty(
        "Current State", 
        [this] { return currState; },
        nullptr);
}
