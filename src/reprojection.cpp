#include "reprojection.h"       //包含头文件
#include <cmath>                //包含数学库
using namespace std;
optional<Point2D> projectPoint(
    const Point3D& WorldPoint,
    const CameraIntrinsic& K,
    const CameraExtrinsic& T)
{
    double xc=T.R[0][0]*WorldPoint.x+T.R[0][1]*WorldPoint.y+T.R[0][2]*WorldPoint.z+T.t[0];  //x坐标
    double yc=T.R[1][0]*WorldPoint.x+T.R[1][1]*WorldPoint.y+T.R[1][2]*WorldPoint.z+T.t[1];  //y坐标
    double zc=T.R[2][0]*WorldPoint.x+T.R[2][1]*WorldPoint.y+T.R[2][2]*WorldPoint.z+T.t[2];  //z坐标
    constexpr double kMinDepth=1e-6;  //最小深度阈值（阈值扫描实验只改这一行的数值）
    if (zc <= kMinDepth){
        return nullopt;  //深度不大于阈值时返回空值
    }


    double m=K.fx*(xc/zc)+K.cx;  //计算像素坐标m
    double n=K.fy*(yc/zc)+K.cy;  //计算像素坐标n
    return Point2D{m,n};         //返回二维点坐标

}
double calculatePixelDistance(const Point2D& point1, const Point2D& point2) {
    double dx = point1.m - point2.m;  //计算x方向的差值
    double dy = point1.n - point2.n;  //计算y方向的差值
    return sqrt(dx * dx + dy * dy);    //返回欧氏距离
}
