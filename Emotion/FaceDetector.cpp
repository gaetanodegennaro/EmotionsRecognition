#include "FaceDetector.h"

//IMPLEMENTAZIONI
void FaceDetector::setOriginal(cv::Mat original) { FaceDetector::original = original; }
cv::Mat FaceDetector::getOriginal() { return original; }
std::vector<cv::Point2d> FaceDetector::getNose_end_point2D() { return nose_end_point2D; }
std::vector<cv::Point2d> FaceDetector::getImagePoints() { return image_points; }
std::vector<full_object_detection> FaceDetector::getShapes() { return shapes; }
full_object_detection FaceDetector::getShape() { return shape; }

bool FaceDetector::hasEmptyShapes()
{
	return FaceDetector::shapes.empty();
}

void FaceDetector::detectFaces(shape_predictor pose_model, cv::Mat original, frontal_face_detector detector)
{
	cv_image<bgr_pixel> cimg(original);
	std::vector<cv::Point3d> model_points = get_3d_model_points();
	
	// Detect faces 
	std::vector<rectangle> faces = detector(cimg);
	
	for (unsigned long i = 0; i < faces.size(); ++i)
	{
		shape = pose_model(cimg, faces[i]);

		//cout << "number of parts: "<< shape.num_parts() << endl;
		//cout << "pixel position of first part:  " << shape.part(0) << endl;
		//cout << "pixel position of second part: " << shape.part(1) << endl;
		shapes.push_back(pose_model(cimg, faces[i]));

		//cout<< shape.part(0).x() << " " << shape.part(0).y() << endl;
		//cout<< shape.part(1).x() << " " << shape.part(1).y() << endl;

		image_points = get_2d_image_points(shape);
		double focal_length = original.cols;
		cv::Mat camera_matrix = get_camera_matrix(focal_length, cv::Point2d(original.cols / 2, original.rows / 2));
		cv::Mat rotation_vector;
		cv::Mat rotation_matrix;
		cv::Mat translation_vector;
		cv::Mat dist_coeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type);

		cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

		std::vector<cv::Point3d> nose_end_point3D;
		nose_end_point3D.push_back(cv::Point3d(0, 0, 1000.0));

		cv::projectPoints(nose_end_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, nose_end_point2D);
	}
	FaceDetector::original = original;
}

std::vector<cv::Point3d> FaceDetector::get_3d_model_points()
{
	std::vector<cv::Point3d> modelPoints;

	modelPoints.push_back(cv::Point3d(0.0f, 0.0f, 0.0f)); //The first must be (0,0,0) while using POSIT
	modelPoints.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));
	modelPoints.push_back(cv::Point3d(-225.0f, 170.0f, -135.0f));
	modelPoints.push_back(cv::Point3d(225.0f, 170.0f, -135.0f));
	modelPoints.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f));
	modelPoints.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));

	return modelPoints;
}

std::vector<cv::Point2d> FaceDetector::get_2d_image_points(full_object_detection& d)
{
	std::vector<cv::Point2d> image_points;
	image_points.push_back(cv::Point2d(d.part(30).x(), d.part(30).y()));    // Nose tip
	image_points.push_back(cv::Point2d(d.part(8).x(), d.part(8).y()));      // Chin
	image_points.push_back(cv::Point2d(d.part(36).x(), d.part(36).y()));    // Left eye left corner
	image_points.push_back(cv::Point2d(d.part(45).x(), d.part(45).y()));    // Right eye right corner
	image_points.push_back(cv::Point2d(d.part(48).x(), d.part(48).y()));    // Left Mouth corner
	image_points.push_back(cv::Point2d(d.part(54).x(), d.part(54).y()));    // Right mouth corner

	return image_points;
}

cv::Mat FaceDetector::get_camera_matrix(float focal_length, cv::Point2d center)
{
	cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << focal_length, 0, center.x, 0, focal_length, center.y, 0, 0, 1);
	return camera_matrix;
}
