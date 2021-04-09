#ifndef OBJECT_H
#define OBJECT_H
using namespace std;
extern TCHAR* s_t(string& words);

class object{
	public:
		int length; int width;//�ߴ�
		int x; int y;//��������
		int xc; int yc;//��������
		IMAGE* display;//��ӦͼƬ
		IMAGE* backup;//�������ݣ���Ӧ�ƶ��㷨
		string message;//������ʾ
		object(int L = 0, int W = 0, int X = 0, int Y = 0, IMAGE* D = NULL, 
			IMAGE* B =NULL ,string M = "") {
			length = L; width = W;
			x = X; y = Y;
			xc = x + length / 2; yc = y + width / 2;
			backup = B;
			if(backup!=NULL)getimage(backup, x, y, length, width);
			display = D; message = M;
		}//���ι���
		virtual void show(int dx=0,int dy=0,int sx=40,int sy=40) {
			if(display)putimage(x, y, display);
			settextstyle(sx, sy, _T("����"));
			settextcolor(YELLOW);
			outtextxy(x+dx, y+dy, s_t(message));
		}//չʾ��Ϣ
		virtual void update(int dx = 0, int dy = 0) {
			x += dx; y += dy;
			xc += dx; yc += dy;
		}//λ�ø���
		virtual void move(int dx = 0, int dy = 0) {
			putimage(x, y, backup);
			update(dx, dy);
			getimage(backup, x, y, length, width);
			show();
		}//�ֲ�ˢ�µ��ƶ��㷨
		virtual bool click(MOUSEMSG now, void (*func)()) {
			bool x_in = (x <= now.x and now.x <= x + length);
			bool y_in = (y <= now.y and now.y <= y + width);
			if (x_in and y_in and now.uMsg == WM_LBUTTONDOWN) {
				func();
				return true;
			}
			else return false;
		}//�������������һ�ִ������,�����Ƿ������ж�
		virtual void dispair() {
			putimage(x, y, backup);
		}
		~object() {};
};

#endif // !OBJECT_H