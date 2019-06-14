#include "RegisterAction.h"

void RegisterAction::action(int webcam)
{
	std::string percorso = UI::salvaFile();

	cv::VideoCapture cap(webcam); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "ERROR: Cannot open the video file" << endl;
	}

	cv::namedWindow("Registra", CV_WINDOW_AUTOSIZE); //create a window called "Video"

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

	cv::Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	cv::VideoWriter oVideoWriter(percorso, CV_FOURCC('D', 'I', 'V', 'X'), 25, frameSize, true); //initialize the VideoWriter object 

	if (!oVideoWriter.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video" << endl;
	}

	cv::Mat logo = cv::imread("Logo2.jpg");

	int x = dWidth - 93;

	while (1)
	{
		cv::Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "ERROR: Cannot read a frame from video file" << endl;
			break;
		}

		oVideoWriter.write(frame); //writer the frame into the file
		logo.copyTo(frame(cv::Rect(x, 0, logo.cols, logo.rows)));

		putText(frame, "Registrazione video in corso...", cv::Point(10, 30), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 1.5);
		putText(frame, "Premi ESC per chiudere", cv::Point(10, 60), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 1.5);

		imshow("Registra", frame); //show the frame in "MyVideo" window

		if (cv::waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			cvDestroyWindow("Registra");
			break;
		}
	}
}
