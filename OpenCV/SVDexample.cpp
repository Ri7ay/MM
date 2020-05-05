#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

int main() {
    cv::Mat A(3, 2, cv::DataType<double>::type);
    cv::Mat AtA(2, 2, cv::DataType<double>::type);
    double singular_number[2];
    cv::Mat v1(2, 1, cv::DataType<double>::type),
            v2(2, 1, cv::DataType<double>::type),
            u1(3, 1, cv::DataType<double>::type),
            u2(3, 1, cv::DataType<double>::type),
            u3(3, 1, cv::DataType<double>::type);

    cv::Mat U, Vt, W(3, 2, cv::DataType<double>::type),
            W_tmp(3, 2, cv::DataType<double>::type);

    singular_number[0] = std::sqrt(2);
    singular_number[1] = std::sqrt(3);

    W.at<double>(0, 0) = singular_number[0];
    W.at<double>(0, 1) = 0;
    W.at<double>(1, 0) = 0;
    W.at<double>(1, 1) = singular_number[1];
    W.at<double>(2, 0) = 0;
    W.at<double>(2, 1) = 0;

    A.at<double>(0, 0) = 1;
    A.at<double>(0, 1) = 1;
    A.at<double>(1, 0) = 0;
    A.at<double>(1, 1) = 1;
    A.at<double>(2, 0) = -1;
    A.at<double>(2, 1) = 1;

    v1.at<double>(0, 0) = 1;
    v1.at<double>(1, 0) = 0;

    v2.at<double>(0, 0) = 0;
    v2.at<double>(1, 0) = 1;
    cv::mulTransposed(A, AtA, true);

    cv::SVD svd(A, cv::SVD::FULL_UV);
    W_tmp.at<double>(0, 0) = svd.w.at<double>(0, 0);
    W_tmp.at<double>(0, 1) = 0;
    W_tmp.at<double>(1, 0) = 0;
    W_tmp.at<double>(1, 1) = svd.w.at<double>(1, 0);
    W_tmp.at<double>(2, 0) = 0;
    W_tmp.at<double>(2, 1) = 0;

    u1 = A * v1 / singular_number[0];
    u2 = A * v2 / singular_number[1];
    u1.copyTo(u3);
    u3 = u3.cross(u2);

    cv::transpose(u1, u1);
    cv::transpose(u2, u2);
    cv::transpose(u3, u3);
    U.push_back(u1);
    U.push_back(u2);
    U.push_back(u3);
    cv::transpose(U, U);

    cv::transpose(v1, v1);
    cv::transpose(v2, v2);
    Vt.push_back(v1);
    Vt.push_back(v2);

    std::cout << "----------------------------------" << std::endl;

    std::cout << U << std::endl;
    std::cout << Vt << std::endl;
    std::cout << W << std::endl;

    std::cout << "----------------------------------" << std::endl;

    std::cout << svd.u << std::endl;
    std::cout << svd.vt << std::endl;
    std::cout << svd.w << std::endl;

    std::cout << "----------------------------------" << std::endl;

    std::cout << U * W * Vt << std::endl;
    std::cout << svd.u * W_tmp * svd.vt << std::endl;
    std::cout << A << std::endl;
    return 0;

}
