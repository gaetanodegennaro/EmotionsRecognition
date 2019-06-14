#include "LoadAction.h"

void LoadAction::action(int webcam)
{
	std::string v = GetCurrentWorkingDir();
	std::string cc = v + "/secondary_emotions_multiClassSVM.model";
	const char* cstr = cc.c_str();
	svm_model* model = svm_load_model(cstr);

	double predictions;
	double* prob_est = new double[11];   // 11 è il numero di classi

	int c = 0;
	int fine;

	std::string video = UI::apriFile();
	std::string analisi = UI::salvaRisultati();

	const char* perc;
	perc = video.c_str();

	cv::VideoCapture cap(perc);
	fine = cap.get(CV_CAP_PROP_FRAME_COUNT);

	c = 0;

	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;
	std::string percors = v + "/shape_predictor_68_face_landmarks.dat";
	std::string nn2 = ReplaceAll(percors, "\\", "/");

	deserialize(nn2) >> pose_model;

	cv::Mat original, img_gray;
	cv::Mat sfondo = cv::imread("sfondo.jpg");

	EmotionPercentage emotionEntusiasmo(150);
	EmotionPercentage emotionInteresse(150);
	EmotionPercentage emotionSorpresa(150);
	EmotionPercentage emotionCuriosita(150);
	EmotionPercentage emotionConcentrazione(150);
	EmotionPercentage emotionAttenzione(150);
	EmotionPercentage emotionDelusione(150);
	EmotionPercentage emotionNoia(150);
	EmotionPercentage emotionPerplessita(150);
	EmotionPercentage emotionFastidio(150);
	EmotionPercentage emotionFrustrazione(150);
	FaceDetector faceDetector;
	while(1)
	{
		cv::Mat visualizza = sfondo.clone();
		// legge un frame da cap
		cap >> original;
		if (original.empty()) fine = c ;
		
		putText(visualizza, "Premi ESC per interrompere l'analisi", cv::Point(10, 20), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 1);
		putText(visualizza, "Analisi in corso...", cv::Point(10, 50), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);

		int alt = original.rows;
		int largh = original.cols;
		int centro =  largh / 2;
		
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

			if (punto_altezza_y > alt || punto_partenza_x<0 || punto_larghezza_x>largh || y20 - 15 < 0 || y25 - 15 < 0)
			{
				putText(visualizza, "Volto non rilevato..!!", cv::Point(10, 75), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
				imshow("Carica e Analizza", visualizza);
				char k = cvWaitKey(20);
				if (k == 27) break;
			}
			else
			{
				//imwrite("C:/Users/Giuseppe/Desktop/1.immagine_originale.jpg",frame);
				cv::Mat faccia = original(r);

				cv::Rect rectROI(0, 0, faccia.cols, faccia.rows);
				cv::Mat mask(faccia.rows, faccia.cols, CV_8UC1, cv::Scalar(0));


				cv_image<bgr_pixel> cimg2(faccia);

				// Detect faces 
				std::vector<rectangle> faces2 = detector(cimg2);
				// Find the pose of each face.
				std::vector<full_object_detection> shapes2;
				full_object_detection shape2;
				for (unsigned long i = 0; i < faces2.size(); ++i)
				{
					shape2 = pose_model(cimg2, faces2[i]);
					shapes2.push_back(pose_model(cimg2, faces2[i]));
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

					cv::resize(img_gray, img_gray, cv::Size(48, 64));

					//extract feature
					cv::HOGDescriptor d(cv::Size(48, 64), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 7);
					std::vector<float> descriptorsValues;
					std::vector<cv::Point> locations;
					d.compute(img_gray, descriptorsValues, cv::Size(0, 0), cv::Size(0, 0), locations);

					//2d vector to Mat
					int row = descriptorsValues.size();
					int col = descriptorsValues.size();

					cv::Mat fm = cv::Mat(descriptorsValues);

					cv::Mat B = fm.t();

					float** mat = new float* [B.rows];
					for (int i = 0; i < B.rows; i++) {
						mat[i] = new float[B.cols];
					}


					for (int i = 0; i < B.rows; i++) {
						for (int j = 0; j < B.cols; j++) {
							mat[i][j] = B.at<float>(i, j);
						}
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

					std::string p1 = std::to_string(predictions);
					putText(visualizza, "Prediction: " + p1, cv::Point(10, 75), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string e1 = std::to_string(prob_est[0]);
					putText(visualizza, "Entusiasmo: " + e1, cv::Point(10, 100), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string i1 = std::to_string(prob_est[1]);
					putText(visualizza, "Interesse: " + i1, cv::Point(10, 120), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string s1 = std::to_string(prob_est[2]);
					putText(visualizza, "Sorpresa: " + s1, cv::Point(10, 140), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string c1 = std::to_string(prob_est[3]);
					putText(visualizza, "Curiosita': " + c1, cv::Point(10, 160), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string cc1 = std::to_string(prob_est[4]);
					putText(visualizza, "Concentrazione: " + cc1, cv::Point(10, 180), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string a1 = std::to_string(prob_est[5]);
					putText(visualizza, "Attenzione: " + a1, cv::Point(10, 200), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string d1 = std::to_string(prob_est[6]);
					putText(visualizza, "Delusione: " + d1, cv::Point(10, 220), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string n1 = std::to_string(prob_est[7]);
					putText(visualizza, "Noia: " + n1, cv::Point(10, 240), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string pp1 = std::to_string(prob_est[8]);
					putText(visualizza, "Perplessita': " + pp1, cv::Point(10, 260), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string f1 = std::to_string(prob_est[9]);
					putText(visualizza, "Fastidio: " + f1, cv::Point(10, 280), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
					std::string ff1 = std::to_string(prob_est[10]);
					putText(visualizza, "Frustrazione: " + ff1, cv::Point(10, 300), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);

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

					emotionEntusiasmo.calculateEmotionPercentage(entusiasmo, num_cifre((int)entusiasmo));
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

					string sg;

					std::vector<cv::Point2d> nose_end_point2D = faceDetector.getNose_end_point2D();
					if (nose_end_point2D[0].x >= centro) sg = "sinistra";
					else sg = "destra";

					putText(visualizza, "Sguardo: " + sg, cv::Point(10, 330), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);

					scrittura(analisi, emotionEntusiasmo.getStringEmotionPercentage(),
						emotionInteresse.getStringEmotionPercentage(), emotionSorpresa.getStringEmotionPercentage(), 
						emotionCuriosita.getStringEmotionPercentage(), emotionConcentrazione.getStringEmotionPercentage(),
						emotionAttenzione.getStringEmotionPercentage(), emotionDelusione.getStringEmotionPercentage(),
						emotionNoia.getStringEmotionPercentage(), emotionPerplessita.getStringEmotionPercentage(), 
						emotionFastidio.getStringEmotionPercentage(), emotionFrustrazione.getStringEmotionPercentage(), sg);
				}
			}
		}
		else
		{
			putText(visualizza, "Volto non rilevato..!!", cv::Point(10, 75), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
			imshow("Carica e Analizza", visualizza);
			char k = cvWaitKey(20);
			if (k == 27) break;
		}

		c++;

		std::string cccc = std::to_string(c);
		std::string finee = std::to_string(fine);

		putText(visualizza, "Frame (" + cccc + "/" + finee + ")", cv::Point(10, 370), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);

		imshow("Carica e Analizza", visualizza);
		char k = cvWaitKey(20);
		if (k == 27) break;

		if (c == fine)
		{
			putText(visualizza, "Fine Analisi..!!", cv::Point(10, 410), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 255), 1);
			imshow("Carica e Analizza", visualizza);
			cv::waitKey(20);
			break;
		}
	}
}

std::string LoadAction::ReplaceAll(std::string str, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

void LoadAction::scrittura(string filepath, string a1, string a2, string a3, string a4, string a5, string a6, string a7, string a8, string a9, string a10, string a11, string sg)
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

	fprintf(fd, "entusiasmo;interesse;sorpresa;curiosita';concentrazione;attenzione;delusione;noia;perplessita';fastidio;frustrazione;\n");
	fprintf(fd, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, sg);

	fclose(fd);
}
