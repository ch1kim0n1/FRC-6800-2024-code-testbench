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

void ValorCANdleSensor::setAnimation(ValorCANdleSensor::AnimationType animation)
{
    int startLED = 8;
    int speed = 1;
    int brightness = 1;

    if (animation != activeAnimationType) {
        clearAnimation();
        activeAnimationType = animation;

        if (animation == AnimationType::ColorFlow)
            activeAnimation = new ctre::phoenix::led::ColorFlowAnimation(currentColor.red,currentColor.green,currentColor.blue,0,speed,ledCount,ctre::phoenix::led::ColorFlowAnimation::Forward, startLED);
        else if (animation == AnimationType::Fire)
            activeAnimation = new ctre::phoenix::led::FireAnimation(brightness,speed,ledCount,1,1,false,startLED);
        else if (animation == AnimationType::Larson)
            activeAnimation = new ctre::phoenix::led::LarsonAnimation(currentColor.red,currentColor.green,currentColor.blue,0,speed,ledCount,ctre::phoenix::led::LarsonAnimation::Front,5,startLED);
        else if (animation == AnimationType::Rainbow)
            activeAnimation = new ctre::phoenix::led::RainbowAnimation(brightness,speed,ledCount,false,startLED);
        else if (animation == AnimationType::RgbFade)
            activeAnimation = new ctre::phoenix::led::RgbFadeAnimation(brightness,speed,ledCount,startLED);
        else if (animation == AnimationType::SingleFade)
            activeAnimation = new ctre::phoenix::led::SingleFadeAnimation(currentColor.red,currentColor.green,currentColor.blue,0,speed,ledCount,startLED);
        else if (animation == AnimationType::Strobe)
            activeAnimation = new ctre::phoenix::led::StrobeAnimation(currentColor.red,currentColor.green,currentColor.blue,0,speed,ledCount,startLED);
        else if (animation == AnimationType::Twinkle)
            activeAnimation = new ctre::phoenix::led::TwinkleAnimation(currentColor.red,currentColor.green,currentColor.blue,0,speed,ledCount,ctre::phoenix::led::TwinkleAnimation::TwinklePercent::Percent100,startLED);
        else if (animation == AnimationType::TwinkleOff)
            activeAnimation = new ctre::phoenix::led::TwinkleOffAnimation(currentColor.red,currentColor.green,currentColor.blue,0,speed,ledCount,ctre::phoenix::led::TwinkleOffAnimation::TwinkleOffPercent::Percent100,startLED);
    }

    if (activeAnimation)
        candle.Animate(*activeAnimation);
}

void ValorCANdleSensor::clearAnimation()
{
    activeAnimationType = AnimationType::None;
    if (activeAnimation != NULL) {
        candle.ClearAnimation(0);
        delete activeAnimation;
    }
}

