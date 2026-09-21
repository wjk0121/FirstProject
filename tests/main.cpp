#include <iostream>
#include  "reprojection.h"
#include <cmath>
using namespace std;
namespace {
    int g_failures=0;   //记录失败次数
    bool nearlyEqual(double a,double b,double eps=1e-6){
        return fabs(a-b)<eps;
    }
    void expect(bool ok,const char*what){
        cout<<(ok?"[PASS]":"[FAIL]")<<what<<endl;  //输出测试结果
        if(!ok) ++g_failures;
    }
}
int main(){
    CameraIntrinsic K{100.0,100.0,320.0,240.0};
    CameraExtrinsic T_identity{
        {{1.0,0.0,0.0},
        {0.0,1.0,0.0},
        {0.0,0.0,1.0}},
        {0.0,0.0,0.0}
    };
    {
        auto p=projectPoint(Point3D{1.0,1.0,5.0},K,T_identity);
        expect(p.has_value(),"case1 正深度点应成功");
        if(p){
            expect(nearlyEqual(p->m,340.00)&&nearlyEqual(p->n,260.0),"case1(1,1,5)->(340,260)");
        }
    }
    {
        double d=calculatePixelDistance(Point2D{340.0,260.0},Point2D{341.0,259.0});
        expect(nearlyEqual(d,1.4142135,1e-5),"case2距离计算");
    }
    {
        auto p=projectPoint(Point3D{1.0,1.0,-5.0},K,T_identity);
        expect(!p.has_value(),"case3 Zc<0 应返回 nullopt");
    }
    {
        auto p=projectPoint(Point3D{1.0,1.0,0.0},K,T_identity);
        expect(!p.has_value(),"case4 Zc=0 应返回 nullopt");
    }
    {
        CameraExtrinsic T_rot{
            {{0.0,-1.0,0.0},
            {1.0,0.0,0.0},
            {0.0,0.0,1.0}},
            {0.0,0.0,1.0}
        };
        auto p=projectPoint(Point3D{1.0,0.0,2.0},K,T_rot);
        expect(p.has_value(),"case5 旋转和平移后的点应成功");
        if(p){
            expect(nearlyEqual(p->m,320.0)&&nearlyEqual(p->n,240.0+100.0/3.0),
        "case5 Rz90+t->(320,240+100/3)");
        }
    }
    

    cout<<'\n'<<(g_failures==0?"全部通过":"存在失败案例")<<endl;
    return g_failures==0?0:1;
}
