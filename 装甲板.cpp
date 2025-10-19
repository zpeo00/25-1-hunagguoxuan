#include<iostream>
#include<string>
using namespace std;
struct point {

	double x;
	double y;
};

struct Rect {
	int ID;
	int color;
	point zuoshang ;
	double high;
	double wide;
	
};
class Armor{
private:
	struct Rect shujv;
public:
	Armor(Rect r):shujv(r){}
	void id() {
		cout << "ID:" << shujv.ID << "\n";
	}
	point Center_Point() {
		double X = shujv.zuoshang.x + shujv.wide / 2;
		double Y = shujv.zuoshang.y + shujv.high / 2;
		return { X,Y };
	}
	double Diagonia( ) {
		double djx = sqrt(shujv.wide * shujv.wide + shujv.high * shujv.high);
		int b = djx * 100;
		return b / 100;
	}
	void Armor_Point() {
		point p1 = shujv.zuoshang;
		point p2 = { shujv.zuoshang.x + shujv.wide ,shujv.zuoshang.y};
		point p3 = { shujv.zuoshang.x + shujv.wide,shujv.zuoshang.y + shujv.high };
		point p4 = { shujv.zuoshang.x,shujv.zuoshang.y + shujv.high };
		point arr[4] = { p1,p2,p3, p4 };
		for (int i = 0; i < 4; i++) {
			cout << "point p" << i+1 << "的坐标为： " << "(" << arr[i].x << "," << arr[i].y << ")" << endl;
		}
	}
	void Armor_Color() {
		string a = "装甲板为红色";
		string b = "装甲板为蓝色";
		string c ="";
		c =(shujv.color==1	? a : b);
		cout << c << endl;


	}
};

int main() {
	
	int ID;
	int color;
	cin >> ID >> color;
	double x;
	double y;
	double high;
	double wide;
	cin >> x >> y >> high >> wide;
	Rect shujv = { ID,color,{x,y},high,wide };
	Armor daochu(shujv);
	daochu.id();
	daochu.Armor_Color();
	point center = daochu.Center_Point();
	cout << "中心点坐标：(" << center.x << "," << center.y << ")  ";
	double dia = daochu.Diagonia();
	cout << "对角线长度为：" << dia << endl;
	daochu.Armor_Point();
	
	
	system("pause");
	return 0;
}