#pragma once
#ifndef REALTIMEACTION_H
#define REALTIMEACTION_H

#include "Actions.h"
#include <EmotionPercentage.h>
#include "UI.h"

class RealTimeAction :	public Actions
{
	private:
		const std::string currentDateTime();

	public:
		void scrittura(string filepath, string a1, string a2, string a3, string a4, string a5, string a6, string a7, string a8, string a9, string a10, string a11, string sg);
		void action(int webcam);
};

#endif