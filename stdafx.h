// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//
#pragma once
#define PI (atan(1)*4)//����pi
#define On 81//��������
#define dt 0.002 //ʱ����s
#define lognum 2//��ӡ
#define re 1.0//�ָ�ϵ��
#define Osize 1.0//����߳�m
#define mass 500.0//�������� kg
//����������
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
//��������������Ƿ���ײ��������ݸ���
int collision_detection(struct __OBJECTS__ *p, int n, int i);
//Լ��������ָ����Χ
double numprocess(double a, double left, double size);
//������
void physical_main(struct __OBJECTS__ *p, double timelimit);

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
