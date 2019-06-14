#include "EmotionPercentage.h"
#include <opencv.hpp>

EmotionPercentage::EmotionPercentage(int coeff)
{
	EmotionPercentage::coeff = coeff;
}

void EmotionPercentage::calculateEmotionPercentage(float emotionVaue, int num_cifre)
{
	std::stringstream oss2;
	if (num_cifre == 1)
	{
		oss2 << std::setprecision(3) << emotionVaue;
	}
	else
	{
		oss2 << std::setprecision(4) << emotionVaue;
	}
	EmotionPercentage::stringEmotionPercentage = " " + oss2.str() + "%";
	EmotionPercentage::emotionPercentage = (emotionVaue * coeff) / 100;
}

float EmotionPercentage::getEmotionPercentage() { return EmotionPercentage::emotionPercentage; }
std::string EmotionPercentage::getStringEmotionPercentage() { return EmotionPercentage::stringEmotionPercentage; }