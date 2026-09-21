# 27 赛季算法组视觉侧第一次培训作业

## 项目简介
使用 C++17 实现理想针孔模型下的重投影计算：输入三维点、相机内参与已知外参（Pc = R·Pw + t），
输出二维像素坐标，并计算与对应观测点之间的像素欧氏距离。包含非正深度异常处理。

## 环境
- Ubuntu 26.04.1 LTS（WSL2）
- g++ 15.2 / CMake 4.2.3（均通过 apt 安装，未使用 Snap）

## 项目结构
- `include/reprojection.h` —— 数据结构（Point3D / Point2D / CameraIntrinsic / CameraExtrinsic）与函数声明
- `src/reprojection.cpp` —— 重投影与像素欧氏距离的实现
- `tests/main.cpp` —— 自造数据验证（期望值全部可手算）

## 构建与运行
```bash
cmake -S . -B build
cmake --build build
./build/test_reprojection
```

## 测试设计
- case1：常规点 (1,1,5) → (340,260)，验证投影公式
- case2：像素欧氏距离 ≈ 1.41421
- case3：Zc < 0（相机后方）→ 返回空值拦截
- case4：Zc = 0（除零边界）→ 返回空值拦截
- case5：非单位旋转 Rz90° + 平移 → (320, 273.333)；单位矩阵是对称的，测不出 R 乘法方向写反，必须用非对称旋转矩阵

## 已知假设
- 深度阈值 kMinDepth = 1e-6：Zc 小于该值视为不可见（防止除零与"相机后方幻影点"）
- 三维坐标与平移量使用相同长度单位
- 理想针孔模型，忽略畸变
