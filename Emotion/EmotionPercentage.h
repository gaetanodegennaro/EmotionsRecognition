#pragma once
#ifndef EMOTIONPERCENTAGE_H
#define EMOTIONPERCENTAGE_H
#include <string>

class EmotionPercentage
{
	private:
		int coeff;
		float emotionPercentage;
		std::string stringEmotionPercentage;

	public:
		EmotionPercentage(int coeff);
		void calculateEmotionPercentage(float emotionValue, int num_cifre);
		float getEmotionPercentage();
		std::string getStringEmotionPercentage();

};
#endif
