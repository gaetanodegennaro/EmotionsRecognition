#pragma once
#ifndef LOADACTION_H
#define LOADACTION_H

#include "Actions.h"
#include <EmotionPercentage.h>
#include "UI.h"

class LoadAction : public Actions
{
	private:
		std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

	public:
		void action(int webcam);
		void scrittura(string filepath, string a1, string a2, string a3, string a4, string a5, string a6, string a7, string a8, string a9, string a10, string a11, string sg);
};

#endif