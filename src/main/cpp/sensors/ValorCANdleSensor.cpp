#include "sensors/ValorCANdleSensor.h"
#include "ctre/phoenix/led/ColorFlowAnimation.h"
#include "ctre/phoenix/led/FireAnimation.h"
#include "ctre/phoenix/led/LarsonAnimation.h"
#include "ctre/phoenix/led/RainbowAnimation.h"
#include "ctre/phoenix/led/RgbFadeAnimation.h"
#include "ctre/phoenix/led/SingleFadeAnimation.h"
#include "ctre/phoenix/led/StrobeAnimation.h"
#include "ctre/phoenix/led/TwinkleAnimation.h"
#include "ctre/phoenix/led/TwinkleOffAnimation.h"
#define VALOR_GOLD 0xEEA800

ValorCANdleSensor::ValorCANdleSensor(frc::TimedRobot *_robot, int _ledCount, int _canID, std::string _canbus):
    ValorSensor(_robot, std::string("ID ").append(std::to_string(_canID)).c_str()),
    candle(_canID, _canbus),
    ledCount(_ledCount),
    currentColor(toRGB(VALOR_GOLD)),
    activeAnimation(NULL),
    activeAnimationType(AnimationType::None)
{
    wpi::SendableRegistry::AddLW(this, "ValorDebounceSensor", sensorName);

    reset();

    ctre::phoenix::led::CANdleConfiguration config;
    // Should match the type of LED strip connected to the CANdle
    config.stripType = ctre::phoenix::led::LEDStripType::GRB;
    config.brightnessScalar = 1.0;
    config.statusLedOffWhenActive = true;
    config.disableWhenLOS = false;
    // If the 12V line should be on, off, or modulated (for single LED colors)
    config.vBatOutputMode = ctre::phoenix::led::VBatOutputMode::Off;
    candle.ConfigFactoryDefault(100);
    candle.ConfigAllSettings(config, 100);
}