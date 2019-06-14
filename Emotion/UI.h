#ifndef UI_H
#define UI_H

#include <QtWidgets/QMainWindow>
#include "ui_emotion.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <fstream> 
#include <opencv2/ml.hpp>
#include <dlib/queue.h>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>
#include "FaceDetector.h"
#include "RealTimeAction.h"
#include "RegisterAction.h"
#include "LoadAction.h"

class UI : public QMainWindow
{
	Q_OBJECT

public:
	UI(QWidget *parent = 0);
	~UI();
	static std::string salvaFile();
	static std::string apriFile();
	static std::string salvaRisultati();
	static void mostra(cv::Mat original, cv::Mat risultati);
	static void mostra2(cv::Mat original, cv::Mat risultati, cv::String percentuale11, cv::String percentuale22, cv::String percentuale33, cv::String percentuale44, cv::String percentuale55, cv::String percentuale66, cv::String percentuale77, cv::String percentuale88, cv::String percentuale99, cv::String percentuale1010, cv::String percentuale00, float perc_entusiasmo, float perc_interesse, float perc_sorpresa, float perc_curiosita, float perc_concentrazione, float perc_attenzione, float perc_delusione, float perc_noia, float perc_perplessita, float perc_fastidio, float perc_frustrazione);


private:
	Ui::EmotionClass ui;
	int getWebcam();
	private slots:
		void realTime();
		void record();
		void load();

};

#endif // EMOTION_H
