#pragma once           //宏保护
#include <optional>

struct Point3D
{
    double x;
    double y;
    double z;
};                     //三维点坐标的定义
struct Point2D
{
    double m;
    double n;
};                    //二维点坐标的定义
struct CameraIntrinsic
{
    double fx;
    double fy;
    double cx;
    double cy;
};                   //相机内参的定义
struct CameraExtrinsic
{
    double R[3][3];  //旋转矩阵
    double t[3];     //平移向量
};                   //相机外参的定义
std::optional<Point2D> projectPoint(
    const Point3D& WorldPoint,
    const CameraIntrinsic& K,
    const CameraExtrinsic& T
);                  //世界点坐标投影到图像平面上的函数声明
double calculatePixelDistance(const Point2D& point1, const Point2D& point2);  //计算像素点间的欧氏距离
