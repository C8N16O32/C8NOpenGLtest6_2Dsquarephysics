#include "stdafx.h"
#include "math.h"
struct	__VECTOR__ {
	double x;
	double y;
	double z;
};
struct	__VECTOR__ operator * (double a, struct __VECTOR__ b) {
	return{ a*b.x,a*b.y,a*b.z };
}
struct	__VECTOR__ operator * (struct __VECTOR__ a, struct __VECTOR__ b) {
	return{ a.y*b.z - a.z*b.y,a.z*b.x - a.x*b.z ,a.x*b.y - a.y*b.x };
}
struct	__VECTOR__ operator + (struct __VECTOR__ a, struct __VECTOR__ b) {
	return{ a.x + b.x,a.y + b.y,a.z + b.z };
}
struct	__VECTOR__ operator - (struct __VECTOR__ a, struct __VECTOR__ b) {
	return{ a.x - b.x,a.y - b.y,a.z - b.z };
}
/*约化*/
double numprocess(double a, double left, double size) {
	int powi = 0;
	while (a > (left + size / 2) + size / 2 * pow(10, powi) || a<(left + size / 2) - size / 2 * pow(10, powi)) {
		while (a >(left + size / 2) + size / 2 * pow(10, powi + 1) || a<(left + size / 2) - size / 2 * pow(10, powi + 1))powi++;
		if (a >(left + size)*pow(10, powi))a -= size*pow(10, powi);
		if (a < left*pow(10, powi))a += size*pow(10, powi);
		if (powi > 0)powi--;
	}
	return a;
}
/*向量的角度*/
double vector_angle(double x, double y) {
	double angle;
	if (x == 0)angle = PI / 2 * (y >= 0 ? 1 : -1);
	else angle = atan(y / x);
	if (x < 0) {
		angle = angle + PI;
		if (angle > PI)angle -= PI * 2;
	}
	return angle;
}
/*向量点乘*/
double vm(struct __VECTOR__ a, struct __VECTOR__ b) {
	return a.x*b.x + a.y*b.y;
}
/*计算碰撞*/
int collision_calculation(struct __OBJECTS__ *p, int n, int i, double ramod, double raphi, double rnphi) {
	double I = 1.0 / 6 * mass*pow(Osize, 2);//转动惯量
	double x, y;//接触点坐标
	x = (p + i)->phy.x + cos(raphi)*ramod; y = (p + i)->phy.y + sin(raphi)*ramod;
	//输入主要矢量
	struct __VECTOR__
		iv = { (p + i)->phy.vx ,(p + i)->phy.vy,0 }, nv = { (p + n)->phy.vx,(p + n)->phy.vy,0 },
		iva = { 0,0,(p + i)->phy.va }, nva = { 0,0,(p + n)->phy.va },
		ra = { ramod*cos(raphi),ramod*sin(raphi),0 }, rb = { x - (p + n)->phy.x,y - (p + n)->phy.y,0 },
		rn = { cos(rnphi),sin(rnphi),0 };
	double vr = 0;//撞击速度
	vr = vm(iv + iva*ra - (nv + nva*rb), rn);
	if (vr > 0) return 0;
	double J;//撞击动量
	J = -(re + 1)*vr / (
		1 / mass + 1 / mass +
		vm(((1 / I)*(ra*rn))*ra, rn) + vm(((1 / I)*(rb*rn))*rb, rn)
		);
	//根据J修改速度与转速
	iv = iv + (J / mass)*rn; (p + i)->phy.vx = iv.x; (p + i)->phy.vy = iv.y;
	nv = nv + (-J / mass)*rn; (p + n)->phy.vx = nv.x; (p + n)->phy.vy = nv.y;
	iva = iva + (1 / I)*ra*(J*rn); (p + i)->phy.va = iva.z;
	nva = nva + (1 / I)*rb*(-J*rn); (p + n)->phy.va = nva.z;
}
/*将化简的角度还原*/
double cdr(double x, double y, double rc, double mir) {
	double temp;
	temp = vector_angle(x, y);
	if (mir == 1)temp *= -1;
	temp += rc;
	numprocess(temp, -PI, PI * 2);
	return temp;
}
/*检测碰撞*/
int collision_detection(struct __OBJECTS__ *p, int n, int i) {
	//计算i对于n的位矢 读取两个物体的原始朝向
	double x, y, d;
	x = (p + i)->phy.x - (p + n)->phy.x;
	y = (p + i)->phy.y - (p + n)->phy.y;
	d = sqrt(pow(x, 2) + pow(y, 2)); if (d > sqrt(2)*Osize)return 0;
	double sitar0, an0, ai0;
	sitar0 = vector_angle(x, y);
	ai0 = (p + i)->phy.a; an0 = (p + n)->phy.a;
	//找出最接近位矢的面的角度 旋转坐标系使这个面朝向0度 减少计算量
	double sitar, rc;
	sitar = numprocess(sitar0 - an0, -PI / 4, PI / 2);
	rc = numprocess(sitar0 - sitar, -PI, PI * 2);
	ai0 = numprocess(ai0 - rc, -PI, PI * 2); an0 = numprocess(an0 - rc, -PI, PI * 2);
	//将另一个物体朝向调整至容易处理的范围
	double ai;
	ai = numprocess(ai0, -PI / 4, PI / 2);
	//根据位矢情况反褶 减少计算量
	int mir = 0;
	if (sitar < 0) { sitar *= -1; mir = 1; ai *= -1; an0 *= -1; }
	x = d*cos(sitar);
	y = d*sin(sitar);
	//碰撞情况1
	double x1, y1, d1 = 0;
	x1 = x - cos(ai + PI / 4)*sin(PI / 4)*Osize;
	y1 = y - sin(ai + PI / 4)*sin(PI / 4)*Osize;
	if (x1 < Osize / 2.0&& y1 < Osize / 2.0)
		d1 = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
	//碰撞情况2
	double x2, y2, xi, yi, d2 = 0;
	x2 = Osize / 2.0 - x; y2 = Osize / 2.0 - y;
	xi = cos(ai); yi = sin(ai);
	if (fabs(xi*x2 + yi*y2)<Osize / 2.0 && fabs(-yi*x2 + xi*y2)<Osize / 2.0)
		d2 = sqrt(pow(Osize / 2.0, 2) * 2);
	if (d1 != 0 || d2 != 0) {
		if (d1>d2)collision_calculation(p, n, i, d1, cdr(x1 - x, y1 - y, rc, mir), rc);
		else collision_calculation(p, i, n, d2, cdr(Osize / 2.0, Osize / 2.0, rc, mir), (ai - PI)*(mir == 1 ? -1 : 1) + rc);
		return 1;
	}
	return 0;
}