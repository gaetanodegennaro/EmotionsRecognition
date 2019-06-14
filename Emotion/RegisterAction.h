#pragma once
#ifndef REGISTERACTION_H
#define REGISTERACTION_H

#include "Actions.h"

#include "UI.h"

class RegisterAction : public Actions
{
	public:
		void action(int webcam);
		void scrittura(string filepath, string a1, string a2, string a3, string a4, string a5, string a6, string a7, string a8, string a9, string a10, string a11, string sg) {};
};

#endif