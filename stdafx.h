// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//
#pragma once
#define PI (atan(1)*4)//定义pi
#define On 81//物体数量
#define dt 0.002 //时间间隔s
#define lognum 2//打印
#define re 1.0//恢复系数
#define Osize 1.0//物体边长m
#define mass 500.0//物体质量 kg
//定义正方形
struct __OBJECTS__ {
	struct _physical_ {
		double x;
		double vx;
		double y;
		double vy;
		double a;
		double va;
	}phy;
};
//检测两个正方形是否碰撞并完成数据更改
int collision_detection(struct __OBJECTS__ *p, int n, int i);
//约化数据至指定范围
double numprocess(double a, double left, double size);
//主函数
void physical_main(struct __OBJECTS__ *p, double timelimit);

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  在此处引用程序需要的其他头文件
