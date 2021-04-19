#include "stdafx.h"
#include "math.h"

//全局变量
double t = 0;
struct __OBJECTS__ obj_coll[2] = { 0 };
/*计算平均动量和平均转动惯量*/
double sum_pingdong(struct __OBJECTS__ *p)
{
	double sum = 0;
	int i = 0;
	for (i = 0; i < On; i++)sum += sqrt(pow((p+i)->phy.vx, 2) + pow((p + i)->phy.vy, 2));
	return sum / On;
}
double sum_zhuandong(struct __OBJECTS__ *p) {
	double sum = 0;
	int i = 0;
	double I = 1.0 / 6 * mass*pow(Osize, 2);
	for (i = 0; i < On; i++)sum += fabs((p + i)->phy.va);
	sum *= I;
	return sum / On;
}
/*打印*/
void printlog(struct __OBJECTS__ *p, int num) {
	printf("t:%.3lf秒 |%2d| 位置:(%.1lf,%.1lf) 速度:(%.1lf,%.1lf) 角度:(%.1lf,%.1lf)\n",
		t, num, p->phy.x, p->phy.y, p->phy.vx, p->phy.vy, p->phy.a, p->phy.va);
}
/*物理主函数*/
void physical_procession(struct __OBJECTS__ *d, struct __OBJECTS__ *s, int time) {
	d->phy.x = s->phy.x + dt*time*s->phy.vx;
	d->phy.y = s->phy.y + dt*time*s->phy.vy;
	d->phy.a = numprocess(s->phy.a + dt*time*s->phy.va, -PI, PI * 2);
	if (d != s) {
		d->phy.vx = s->phy.vx;
		d->phy.vy = s->phy.vy;
		d->phy.va = s->phy.va;
	}
}
/*碰撞主函数*/
int collision_procession(struct __OBJECTS__ *p) {
	int n, i, c, r;
	for (n = 0; n < On; n++)for (i = 0; i < On; i++)if (i != n) {
		physical_procession(obj_coll + 0, p + n, 2);
		physical_procession(obj_coll + 1, p + i, 2);
		r = collision_detection(obj_coll, 0, 1);
		if (r != 0) {
			if (n == lognum) {
				printlog(p + n, n);
				printlog(p + i, i);
				printlog(obj_coll + 0, n);
				printlog(obj_coll + 1, i);
				printf("\n");
			}
			physical_procession(p + n, obj_coll + 0, -2);
			physical_procession(p + i, obj_coll + 1, -2);
		}
	}
	return 0;
}
/**********/
void physical_main(struct __OBJECTS__ *p,double timelimit)
{
	int i; double t0 = 0;
	while (t0<timelimit) {
		//碰撞检测
		collision_procession(p);
		//物理
		for (i = 0; i < On; i++)
		{
			physical_procession(p + i, p + i, 1);
			if ((p+i)->phy.x > 20 && (p+i)->phy.vx > 0 || (p+i)->phy.x < 0 && (p+i)->phy.vx < 0)(p+i)->phy.vx *= -1;
			if ((p+i)->phy.y > 5 && (p+i)->phy.vy > 0 || (p+i)->phy.y < -15 && (p+i)->phy.vy < 0)(p+i)->phy.vy *= -1;
		}
		//打印
		t0 += dt; t += dt;
		if (int(t / dt + 0.2*dt) % int(0.2/dt) == 0)printf("t:%.3lf秒 位置:(%.1lf,%.1lf) 速度:(%.1lf,%.1lf) 角度:(%.1lf,%.1lf)\n",
			t, (p+lognum)->phy.x, (p+lognum)->phy.y, (p+lognum)->phy.vx, (p+lognum)->phy.vy, (p+lognum)->phy.a, (p+lognum)->phy.va);
	};
}
