#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
#include <direct.h>
#include <QFileDialog>
#include <opencv.hpp>
#include "svm.h"
#include <dlib\image_processing\shape_predictor.h>
#include "FaceDetector.h"

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

class Actions
{
	public:
		virtual void scrittura(string filepath, string a1, string a2, string a3, string a4, string a5, string a6, string a7, string a8, string a9, string a10, string a11, string sg) abstract;
		virtual void action(int webcam) abstract;

	protected:
		std::string GetCurrentWorkingDir(void);
		int num_cifre(int numero);
};

#endif