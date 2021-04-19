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
//主函数
void physical_main(struct __OBJECTS__ *p, double timelimit);