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
//������
void physical_main(struct __OBJECTS__ *p, double timelimit);