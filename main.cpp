#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#define PATH "1st.jpg"
#define PATH2 "2nd.jpg"
#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include "histogram.h"

void Histogram(Mat img);

using namespace cv;

int main(int argc, char** argv) {


	Mat Color1, Color2;
	Mat Gray1, Gray2;
	
	Color1 = imread(PATH, IMREAD_COLOR);
	Color2 = imread(PATH2, IMREAD_COLOR);
	Gray1 = imread(PATH, IMREAD_GRAYSCALE);
	Gray2 = imread(PATH2, IMREAD_GRAYSCALE);

	if (Color1.empty() || Color2.empty() || Gray1.empty() || Gray2.empty()) {
		printf("오류 발생함");
		return -1;
	}

	Mat harris;
	cornerHarris(Gray1, harris, 3, 3, 0.04);

	Mat harris_norm;
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);

	Mat dst;
	cvtColor(Gray1, dst, COLOR_GRAY2BGR);

	for (int j = 1; j < harris.rows - 1; j++) {
		for (int i = 1; i < harris.cols - 1; i++) {
			if (harris_norm.at<uchar>(j, i) > 120) {
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j + 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j, i - 1) &&
					harris.at<float>(j, i) > harris.at<float>(j, i + 1)) {
					circle(dst, Point(i, j), 5, Scalar(0, 0, 255), 2);
				}
			}
		}
	}
	Mat img_small;	

	//imshow("First", Gray1);
	imshow("harris_norm", img_small);
	//imshow("dst", img_small);

	waitKey(0);

	return 0;
}


void Histogram(Mat img) {
	DWORD width = img.cols;
	DWORD height = img.rows;
	uchar* img_data = img.data;

	for (DWORD y = 0; y < height; y++) {
		for (DWORD x = 0; x < width; x++) {
			uchar RGBBlue = img_data[y * img.cols * 3 * x * 3];
			uchar RGBGreen = img_data[y * img.cols * 3 * x * 3 + 1];
			uchar RGBRed = img_data[y * img.cols * 3 * x * 3 + 2];
			m_histogramRed[RGBRed] += 1;
			m_histogramGreen[RGBGreen] += 1;
			m_histogramBlue[RGBBlue] += 1;
			m_histogramGray[(RGBRed + RGBBlue + RGBGreen) / 3] += 1;
		}
	}



	m_histogramMax = 0;
	for (int i = 0; i < 256; i++) {
		m_histogramMax = max(m_histogramMax, m_histogramRed[i]);
		m_histogramMax = max(m_histogramMax, m_histogramGreen[i]);
		m_histogramMax = max(m_histogramMax, m_histogramBlue[i]);
		m_histogramMax = max(m_histogramMax, m_histogramGray[i]);
	}
}
