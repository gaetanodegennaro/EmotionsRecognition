#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <dlib\image_processing\full_object_detection.h>
#include <dlib\image_processing\frontal_face_detector.h>
#include <dlib\image_processing\shape_predictor.h>
#include <dlib\opencv\cv_image.h>

using namespace dlib;
using namespace std;

class FaceDetector
{
	private:
		cv::Mat original;
		std::vector<cv::Point2d> nose_end_point2D;
		std::vector<cv::Point2d> image_points;
		std::vector<full_object_detection> shapes;
		full_object_detection shape;

	public:
		cv::Mat getOriginal();
		void setOriginal(cv::Mat original);
		std::vector<cv::Point2d> getNose_end_point2D();
		std::vector<cv::Point2d> getImagePoints();
		std::vector<full_object_detection> getShapes();
		bool hasEmptyShapes();
		full_object_detection getShape();
		void detectFaces(shape_predictor pose_model, cv::Mat original, frontal_face_detector detector);
		std::vector<cv::Point3d> get_3d_model_points();
		std::vector<cv::Point2d> get_2d_image_points(full_object_detection& d);
		cv::Mat get_camera_matrix(float focal_length, cv::Point2d center);
};

#endif