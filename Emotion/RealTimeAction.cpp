#include "RealTimeAction.h"

using namespace dlib;
using namespace std;

void RealTimeAction::action(int webcam)
{
	std::string v = GetCurrentWorkingDir();
	string cc = v + "/secondary_emotions_multiClassSVM.model";
	const char* cstr = cc.c_str();
	svm_model* model = svm_load_model(cstr);

	double predictions;
	double pred;
	double* prob_est = new double[11];   // 11 è il numero di classi

	std::string video = UI::salvaFile();
	std::string analisi = UI::salvaRisultati();

	//VideoCapture capture;

	// Get a handle to the Video device:
	cv::VideoCapture cap(webcam);

	// Check if we can use this device at all:
	if (!cap.isOpened()) cerr << "Capture Device ID 0 cannot be opened." << endl;

	//namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	int centro = dWidth / 2;

	//cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

	cv::Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	cv::VideoWriter oVideoWriter(video, CV_FOURCC('D', 'I', 'V', 'X'), 25, frameSize, true); //initialize the VideoWriter object 


	// Load face detection and pose estimation models.
	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;
	string percorso = v + "/shape_predictor_68_face_landmarks.dat";
	deserialize(percorso) >> pose_model;


	cv::Mat original, img_gray;
	cv::Mat risultati(dHeight, 400, CV_8UC3);

	cv::Point pt11;
	cv::Point pt22;
	pt11.x = 0;
	pt11.y = dHeight;
	pt22.x = 400;
	pt22.y = 0;
	cv::rectangle(risultati, pt11, pt22, cv::Scalar(78, 57, 0), -1);

	cv::Point pt111;
	cv::Point pt222;
	pt111.x = 20;
	pt111.y = 440;
	pt222.x = 380;
	pt222.y = 90;

	cv::rectangle(risultati, pt111, pt222, cv::Scalar(210, 210, 210), -1);

	cv::Mat logo = cv::imread("Logo2.jpg");


	EmotionPercentage emotionEntusiasmo(180);
	EmotionPercentage emotionInteresse(180);
	EmotionPercentage emotionSorpresa(180);
	EmotionPercentage emotionCuriosita(180);
	EmotionPercentage emotionConcentrazione(180);
	EmotionPercentage emotionAttenzione(180);
	EmotionPercentage emotionDelusione(180);
	EmotionPercentage emotionNoia(180);
	EmotionPercentage emotionPerplessita(180);
	EmotionPercentage emotionFastidio(180);
	EmotionPercentage emotionFrustrazione(180);
	FaceDetector faceDetector;
	for (;;)
	{
		cap >> original;

		oVideoWriter.write(original); //writer the frame into the file

		logo.copyTo(risultati(cv::Rect(288, 13, logo.cols, logo.rows)));
		faceDetector.detectFaces(pose_model, original, detector);

		if (faceDetector.hasEmptyShapes() == false)
		{
			full_object_detection shape = faceDetector.getShape();

			int x1 = shape.part(0).x();
			int y1 = shape.part(0).y();

			int x9 = shape.part(8).x();
			int y9 = shape.part(8).y();

			int x17 = shape.part(16).x();
			int y17 = shape.part(16).y();

			int x20 = shape.part(19).x();
			int y20 = shape.part(19).y();

			int x25 = shape.part(24).x();
			int y25 = shape.part(24).y();


			int punto_partenza_x = x1 - 15;

			int a[2];
			a[0] = y20;
			a[1] = y25;

			int minimo = *std::min_element(a, a + 2);
			int punto_partenza_y = minimo - 15;
			int punto_altezza_x = punto_partenza_x;
			int punto_altezza_y = y9 + 15;
			int altezza = punto_altezza_y - punto_partenza_y;
			int punto_larghezza_x = x17 + 15;
			int punto_larghezza_y = punto_partenza_y;
			int larghezza = punto_larghezza_x - punto_partenza_x;

			cv::Rect r(punto_partenza_x, punto_partenza_y, larghezza, altezza);

			if (punto_altezza_y > dHeight || punto_partenza_x<0 || punto_larghezza_x>dWidth || y20 - 15 < 0 || y25 - 15 < 0)
				UI::mostra(original, risultati);
			else
			{
				//imwrite("C:/Users/Giuseppe/Desktop/1.immagine_originale.jpg",frame);
				cv::Mat faccia = original(r);
				//imwrite("C:/Users/Giuseppe/Desktop/2.jpg",faccia);

				cv::Mat vis = faccia.clone();
				cv::resize(vis, vis, cv::Size(65, 65));
				vis.copyTo(risultati(cv::Rect(50, 13, vis.cols, vis.rows)));

				cv::Rect rectROI(0, 0, faccia.cols, faccia.rows);
				cv::Mat mask(faccia.rows, faccia.cols, CV_8UC1, cv::Scalar(0));

				/***********************************************/

				cv_image<bgr_pixel> cimg2(faccia);

				// Detect faces 
				std::vector<rectangle> faces2 = detector(cimg2);
				// Find the pose of each face.
				std::vector<full_object_detection> shapes2;
				full_object_detection shape2;
				for (unsigned long i = 0; i < faces2.size(); ++i)
				{
					shape2 = pose_model(cimg2, faces2[i]);

					//cout << "number of parts: "<< shape.num_parts() << endl;
					//cout << "pixel position of first part:  " << shape.part(0) << endl;
					//cout << "pixel position of second part: " << shape.part(1) << endl;
					shapes2.push_back(pose_model(cimg2, faces2[i]));

					//cout<< shape.part(0).x() << " " << shape.part(0).y() << endl;
					//cout<< shape.part(1).x() << " " << shape.part(1).y() << endl;
				}

				if (shapes2.empty() == false)
				{
					int xx1 = shape2.part(0).x();
					int yy1 = shape2.part(0).y();

					int xx2 = shape2.part(1).x();
					int yy2 = shape2.part(1).y();

					int xx3 = shape2.part(2).x();
					int yy3 = shape2.part(2).y();

					int xx4 = shape2.part(3).x();
					int yy4 = shape2.part(3).y();

					int xx5 = shape2.part(4).x();
					int yy5 = shape2.part(4).y();

					int xx6 = shape2.part(5).x();
					int yy6 = shape2.part(5).y();

					int xx7 = shape2.part(6).x();
					int yy7 = shape2.part(6).y();

					int xx8 = shape2.part(7).x();
					int yy8 = shape2.part(7).y();

					int xx9 = shape2.part(8).x();
					int yy9 = shape2.part(8).y();

					int xx10 = shape2.part(9).x();
					int yy10 = shape2.part(9).y();

					int xx11 = shape2.part(10).x();
					int yy11 = shape2.part(10).y();

					int xx12 = shape2.part(11).x();
					int yy12 = shape2.part(11).y();

					int xx13 = shape2.part(12).x();
					int yy13 = shape2.part(12).y();

					int xx14 = shape2.part(13).x();
					int yy14 = shape2.part(13).y();

					int xx15 = shape2.part(14).x();
					int yy15 = shape2.part(14).y();

					int xx16 = shape2.part(15).x();
					int yy16 = shape2.part(15).y();

					int xx17 = shape2.part(16).x();
					int yy17 = shape2.part(16).y();

					int xx18 = shape2.part(17).x();
					int yy18 = shape2.part(17).y();

					int xx19 = shape2.part(18).x();
					int yy19 = shape2.part(18).y();

					int xx20 = shape2.part(19).x();
					int yy20 = shape2.part(19).y();

					int xx21 = shape2.part(20).x();
					int yy21 = shape2.part(20).y();

					int xx22 = shape2.part(21).x();
					int yy22 = shape2.part(21).y();

					int xx23 = shape2.part(22).x();
					int yy23 = shape2.part(22).y();

					int xx24 = shape2.part(23).x();
					int yy24 = shape2.part(23).y();

					int xx25 = shape2.part(24).x();
					int yy25 = shape2.part(24).y();

					int xx26 = shape2.part(25).x();
					int yy26 = shape2.part(25).y();

					int xx27 = shape2.part(26).x();
					int yy27 = shape2.part(26).y();


					cv::Point P1(xx1, yy1);
					cv::Point P2(xx2, yy2);
					cv::Point P3(xx3, yy3);
					cv::Point P4(xx4, yy4);
					cv::Point P5(xx5, yy5);
					cv::Point P6(xx6, yy6);
					cv::Point P7(xx7, yy7);
					cv::Point P8(xx8, yy8);
					cv::Point P9(xx9, yy9);
					cv::Point P10(xx10, yy10);
					cv::Point P11(xx11, yy11);
					cv::Point P12(xx12, yy12);
					cv::Point P13(xx13, yy13);
					cv::Point P14(xx14, yy14);
					cv::Point P15(xx15, yy15);
					cv::Point P16(xx16, yy16);
					cv::Point P17(xx17, yy17);
					cv::Point P18(xx18, yy18);
					cv::Point P19(xx19, yy19);
					cv::Point P20(xx20, yy20);
					cv::Point P21(xx21, yy21);
					cv::Point P22(xx22, yy22);
					cv::Point P23(xx23, yy23);
					cv::Point P24(xx24, yy24);
					cv::Point P25(xx25, yy25);
					cv::Point P26(xx26, yy26);
					cv::Point P27(xx27, yy27);

					std::vector< std::vector<cv::Point> >  co_ordinates;
					co_ordinates.push_back(std::vector<cv::Point>());
					co_ordinates[0].push_back(P1);
					co_ordinates[0].push_back(P2);
					co_ordinates[0].push_back(P3);
					co_ordinates[0].push_back(P4);
					co_ordinates[0].push_back(P5);
					co_ordinates[0].push_back(P6);
					co_ordinates[0].push_back(P7);
					co_ordinates[0].push_back(P8);
					co_ordinates[0].push_back(P9);
					co_ordinates[0].push_back(P10);
					co_ordinates[0].push_back(P11);
					co_ordinates[0].push_back(P12);
					co_ordinates[0].push_back(P13);
					co_ordinates[0].push_back(P14);
					co_ordinates[0].push_back(P15);
					co_ordinates[0].push_back(P16);
					co_ordinates[0].push_back(P17);
					co_ordinates[0].push_back(P27);
					co_ordinates[0].push_back(P26);
					co_ordinates[0].push_back(P25);
					co_ordinates[0].push_back(P24);
					co_ordinates[0].push_back(P23);
					co_ordinates[0].push_back(P22);
					co_ordinates[0].push_back(P21);
					co_ordinates[0].push_back(P20);
					co_ordinates[0].push_back(P19);
					co_ordinates[0].push_back(P18);
					drawContours(mask, co_ordinates, 0, cv::Scalar(255), CV_FILLED, 8);

					cv::Mat srcROI = faccia(rectROI);
					cv::Mat dst1;

					srcROI.copyTo(dst1, mask);

					cvtColor(dst1, img_gray, CV_RGB2GRAY);
					//imwrite("C:/Users/Giuseppe/Desktop/3.jpg",img_gray);

					cv::Mat dst11 = dst1.clone();
					cv::Rect rois(0, 0, dst11.cols, dst11.rows);

					cv::Mat crop = dst11(rois).clone();      // Crop is color CV_8UC3
					cvtColor(crop, crop, cv::COLOR_BGR2GRAY); // Now crop is grayscale CV_8UC1
					cvtColor(crop, crop, cv::COLOR_GRAY2BGR); // Now crop is grayscale, CV_8UC3
					crop.copyTo(dst11(rois));

					cv::resize(dst11, dst11, cv::Size(65, 65));
					dst11.copyTo(risultati(cv::Rect(135, 13, dst11.cols, dst11.rows)));

					cv::resize(img_gray, img_gray, cv::Size(48, 64));

					//imwrite("C:/Users/Giuseppe/Desktop/4.jpg",img_gray);

					//extract feature
					cv::HOGDescriptor d(cv::Size(48, 64), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 7);
					std::vector<float> descriptorsValues;
					std::vector<cv::Point> locations;
					d.compute(img_gray, descriptorsValues, cv::Size(0, 0), cv::Size(0, 0), locations);

					//2d vector to Mat
					int row = descriptorsValues.size();
					int col = descriptorsValues.size();
					printf("descript size row=%d, col=%d\n", row, col);

					printf("descript element %f\n", descriptorsValues[12]);

					cv::Mat fm = cv::Mat(descriptorsValues);
					cv::Mat B = fm.t();

					float** mat = new float* [B.rows];
					for (int i = 0; i < B.rows; i++) mat[i] = new float[B.cols];


					for (int i = 0; i < B.rows; i++)
					{
						for (int j = 0; j < B.cols; j++) mat[i][j] = B.at<float>(i, j);
					}

					svm_node* testnode = Malloc(svm_node, B.cols + 1);
					for (int row = 0; row < B.rows; row++)
					{
						for (int col = 0; col < B.cols; col++)
						{
							testnode[col].index = col;
							testnode[col].value = mat[row][col];
						}
						testnode[B.cols].index = -1;
					}

					predictions = svm_predict_probability(model, testnode, prob_est);
					printf("\nprediction    %f\n", predictions);
					printf("\nentusiasmo      %f\n", prob_est[0]);
					printf("interesse       %f\n", prob_est[1]);
					printf("sorpresa        %f\n", prob_est[2]);
					printf("curiosita'      %f\n", prob_est[3]);
					printf("concentrazione  %f\n", prob_est[4]);
					printf("attenzione      %f\n", prob_est[5]);
					printf("delusione       %f\n", prob_est[6]);
					printf("noia            %f\n", prob_est[7]);
					printf("perplessita'    %f\n", prob_est[8]);
					printf("fastidio        %f\n", prob_est[9]);
					printf("frustrazione    %f\n", prob_est[10]);

					pred = svm_predict(model, testnode);
					printf("%f\n", pred);

					float entusiasmo = prob_est[0] * 100;
					float interesse = prob_est[1] * 100;
					float sorpresa = prob_est[2] * 100;
					float curiosita = prob_est[3] * 100;
					float concentrazione = prob_est[4] * 100;
					float attenzione = prob_est[5] * 100;
					float delusione = prob_est[6] * 100;
					float noia = prob_est[7] * 100;
					float perplessita = prob_est[8] * 100;
					float fastidio = prob_est[9] * 100;
					float frustrazione = prob_est[10] * 100;

					cout << fixed << setprecision(2) << entusiasmo;
					cout << fixed << setprecision(2) << interesse;
					cout << fixed << setprecision(2) << sorpresa;
					cout << fixed << setprecision(2) << curiosita;
					cout << fixed << setprecision(2) << concentrazione;
					cout << fixed << setprecision(2) << attenzione;
					cout << fixed << setprecision(2) << delusione;
					cout << fixed << setprecision(2) << noia;
					cout << fixed << setprecision(2) << perplessita;
					cout << fixed << setprecision(2) << fastidio;
					cout << fixed << setprecision(2) << frustrazione;

					cout << endl << "percentuale completa: " << entusiasmo + interesse + sorpresa + curiosita + concentrazione + attenzione + delusione + noia + perplessita + fastidio + frustrazione << endl;

					emotionEntusiasmo.calculateEmotionPercentage(entusiasmo, num_cifre((int) entusiasmo));
					emotionInteresse.calculateEmotionPercentage(interesse, num_cifre((int)interesse));
					emotionSorpresa.calculateEmotionPercentage(sorpresa, num_cifre((int)sorpresa));
					emotionCuriosita.calculateEmotionPercentage(curiosita, num_cifre((int)curiosita));
					emotionConcentrazione.calculateEmotionPercentage(concentrazione, num_cifre((int)concentrazione));
					emotionAttenzione.calculateEmotionPercentage(attenzione, num_cifre((int)attenzione));
					emotionDelusione.calculateEmotionPercentage(delusione, num_cifre((int)delusione));
					emotionNoia.calculateEmotionPercentage(noia, num_cifre((int)noia));
					emotionPerplessita.calculateEmotionPercentage(perplessita, num_cifre((int)perplessita));
					emotionFastidio.calculateEmotionPercentage(fastidio, num_cifre((int)fastidio));
					emotionFrustrazione.calculateEmotionPercentage(frustrazione, num_cifre((int)frustrazione));

					////////////////////////
					printf("\n\n");

					// Show the result:
					circle(original, cv::Point(shape.part(0).x(), shape.part(0).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(1).x(), shape.part(1).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(2).x(), shape.part(2).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(3).x(), shape.part(3).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(4).x(), shape.part(4).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(5).x(), shape.part(5).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(6).x(), shape.part(6).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(7).x(), shape.part(7).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(8).x(), shape.part(8).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(9).x(), shape.part(9).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(10).x(), shape.part(10).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(11).x(), shape.part(11).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(12).x(), shape.part(12).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(13).x(), shape.part(13).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(14).x(), shape.part(14).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(15).x(), shape.part(15).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(16).x(), shape.part(16).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(17).x(), shape.part(17).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(18).x(), shape.part(18).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(19).x(), shape.part(19).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(20).x(), shape.part(20).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(21).x(), shape.part(21).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(22).x(), shape.part(22).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(23).x(), shape.part(23).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(24).x(), shape.part(24).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(25).x(), shape.part(25).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(26).x(), shape.part(26).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(27).x(), shape.part(27).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(28).x(), shape.part(28).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(29).x(), shape.part(29).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(30).x(), shape.part(30).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(31).x(), shape.part(31).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(32).x(), shape.part(32).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(33).x(), shape.part(33).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(34).x(), shape.part(34).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(35).x(), shape.part(35).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(36).x(), shape.part(36).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(37).x(), shape.part(37).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(38).x(), shape.part(38).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(39).x(), shape.part(39).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(40).x(), shape.part(40).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(41).x(), shape.part(41).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(42).x(), shape.part(42).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(43).x(), shape.part(43).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(44).x(), shape.part(44).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(45).x(), shape.part(45).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(46).x(), shape.part(46).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(47).x(), shape.part(47).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(48).x(), shape.part(48).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(49).x(), shape.part(49).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(50).x(), shape.part(50).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(51).x(), shape.part(51).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(52).x(), shape.part(52).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(53).x(), shape.part(53).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(54).x(), shape.part(54).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(55).x(), shape.part(55).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(56).x(), shape.part(56).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(57).x(), shape.part(57).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(58).x(), shape.part(58).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(59).x(), shape.part(59).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(60).x(), shape.part(60).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(61).x(), shape.part(61).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(62).x(), shape.part(62).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(63).x(), shape.part(63).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(64).x(), shape.part(64).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(65).x(), shape.part(65).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(66).x(), shape.part(66).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
					circle(original, cv::Point(shape.part(67).x(), shape.part(67).y()), 1, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);

					cv::rectangle(original, r, cv::Scalar(0, 255, 0), 1);

					std::vector<cv::Point2d> nose_end_point2D = faceDetector.getNose_end_point2D();
					std::vector<cv::Point2d> image_points = faceDetector.getImagePoints();

					for (int i = 0; i < image_points.size(); i++)
						circle(original, image_points[i], 3, cv::Scalar(0, 0, 255), -1);

					string sguardo;
					string sg;

					cv::line(original, image_points[0], nose_end_point2D[0], cv::Scalar(255, 0, 0), 2);

					cout << nose_end_point2D[0];
					cout << " " << nose_end_point2D[0].x;

					if (nose_end_point2D[0].x >= centro)
					{
						sg = "sinistra";
						sguardo = "Sguardo: sinistra";
					}
					else
					{
						sg = "destra";
						sguardo = "Sguardo: destra";
					}

					cout << " " << sguardo << endl;

					putText(original, "Premi ESC per chiudere", cv::Point(10, 30), cv::FONT_HERSHEY_PLAIN, 1.1, CV_RGB(0, 255, 0), 1);
					putText(original, sguardo, cv::Point(400, 80), cv::FONT_HERSHEY_PLAIN, 1.3, CV_RGB(0, 255, 0), 2);

					scrittura(analisi, emotionEntusiasmo.getStringEmotionPercentage(), 
						emotionInteresse.getStringEmotionPercentage(), emotionSorpresa.getStringEmotionPercentage(),
						emotionCuriosita.getStringEmotionPercentage(), emotionConcentrazione.getStringEmotionPercentage(),
						emotionAttenzione.getStringEmotionPercentage(), emotionDelusione.getStringEmotionPercentage(),
						emotionNoia.getStringEmotionPercentage(), emotionPerplessita.getStringEmotionPercentage(),
						emotionFastidio.getStringEmotionPercentage(), emotionFrustrazione.getStringEmotionPercentage(), sg);

					UI::mostra2(original, risultati, emotionEntusiasmo.getStringEmotionPercentage(), 
						emotionInteresse.getStringEmotionPercentage(), emotionSorpresa.getStringEmotionPercentage(),
						emotionCuriosita.getStringEmotionPercentage(), emotionConcentrazione.getStringEmotionPercentage(),
						emotionAttenzione.getStringEmotionPercentage(), emotionDelusione.getStringEmotionPercentage(), 
						emotionNoia.getStringEmotionPercentage(), emotionPerplessita.getStringEmotionPercentage(),
						emotionFastidio.getStringEmotionPercentage(), emotionFrustrazione.getStringEmotionPercentage(),
						emotionEntusiasmo.getEmotionPercentage(), emotionInteresse.getEmotionPercentage(),
						emotionSorpresa.getEmotionPercentage(), emotionCuriosita.getEmotionPercentage(),
						emotionConcentrazione.getEmotionPercentage(), emotionAttenzione.getEmotionPercentage(),
						emotionDelusione.getEmotionPercentage(), emotionNoia.getEmotionPercentage(),
						emotionPerplessita.getEmotionPercentage(), emotionFastidio.getEmotionPercentage(),
						emotionFrustrazione.getEmotionPercentage());
				}
			}

		}
		else UI::mostra(original, risultati);

		char k = cvWaitKey(20);
		if (k == 27) break;
	}
}

void RealTimeAction::scrittura(string filepath, string a1, string a2, string a3, string a4, string a5, string a6, string a7, string a8, string a9, string a10, string a11, string sg)
{
	FILE* fd;
	int x = -32;
	const char* ppp;

	ppp = filepath.c_str();
	fd = fopen(ppp, "a");
	if (fd == NULL)
	{
		perror("Errore in apertura del file");
		exit(1);
	}

	string time = currentDateTime();

	fprintf(fd, "entusiasmo;interesse;sorpresa;curiosita';concentrazione;attenzione;delusione;noia;perplessita';fastidio;frustrazione;\n");
	fprintf(fd, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, sg, time);

	fclose(fd);
}

const std::string RealTimeAction::currentDateTime()
{
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);

	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1; // Month is 0 – 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime->tm_year + 1900; // Year is # years since 1900
	int hour = aTime->tm_hour;
	int min = aTime->tm_min;
	int sec = aTime->tm_sec;

	stringstream ss_year;
	ss_year << year;
	string x_year = ss_year.str();

	stringstream ss_month;
	ss_month << month;
	string x_month = ss_month.str();

	stringstream ss_day;
	ss_day << day;
	string x_day = ss_day.str();

	stringstream ss_hour;
	ss_hour << hour;
	string x_hour = ss_hour.str();

	stringstream ss_min;
	ss_min << min;
	string x_min = ss_min.str();

	stringstream ss_sec;
	ss_sec << sec;
	string x_sec = ss_sec.str();

	string timestamp = x_year + x_month + x_day + x_hour + x_min + x_sec;

	return timestamp;
}