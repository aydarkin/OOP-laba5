#include <iostream>
#include <locale>
using namespace std;


class Figure
{
public:
	int x, y;

	Figure() {
		cout << "Figure()" << endl;
		x = 0;
		y = 0;
	}
	Figure(Figure* figure) {
		cout << "Figure(Figure* figure)" << endl;
		x = figure->x;
		y = figure->y;
	}
	Figure(Figure& figure) {
		cout << "Figure(Figure& figure)" << endl;
		x = figure.x;
		y = figure.y;
	}
	void PrintInfo() {
		printf("Figure { x = %d, y = %d }\n", this->x, this->y);
	}

	virtual ~Figure() {
		cout << "������� destroyed Figure" << endl;
	}
	
	virtual string ClassName() {
		return "Figure";
	}

	virtual bool isA(string className) { 
		return className == ClassName();
	}
};

class Square : public Figure
{
public:
	int width;
	Square() {
		cout << "Square()" << endl;
		x = 0;
		y = 0;
		width = 0;
	}
	Square(Square* square) {
		cout << "Square(Square* square)" << endl;
		x = square->x;
		y = square->y;
		width = square->width;
	}
	Square(Square& square) {
		cout << "Square(Square& square)" << endl;
		x = square.x;
		y = square.y;
		width = square.width;
	}

	void PrintInfo() { //�������������� ����� ��������
		printf("Square { x = %d, y = %d, width = %d }\n", this->x, this->y, this->width);
	}

	virtual ~Square() override { //�����������
		cout << "������� destroyed Square" << endl;
	}

	virtual string ClassName() override { //�����������
		return "Square";
	}

	virtual bool isA(string className) override { //�����������
		return className == ClassName() || Figure::isA(className);
	}

	int GetArea() { //���� �����
		return width * width;
	}
};

class OffsetSuperMaster
{
public:
	void TryOffset1(Figure figure, int dx, int dy) {
		//���������� ������ ���������
		printf("TryOffset1(Figure) x = %d, y=%d, dx=%d, dy=%d\n", figure.x, figure.y, dx, dy);
		figure.x += dx;
		figure.y += dy;
	}
	void TryOffset2(Figure* figure, int dx, int dy) {
		//���������� ��������� �� ������
		printf("TryOffset2(Figure*) x = %d, y=%d, dx=%d, dy=%d\n", figure->x, figure->y, dx, dy);
		figure->x += dx;
		figure->y += dy;
	}
	void TryOffset3(Figure& figure, int dx, int dy) {
		//���������� ����� �������
		printf("TryOffset3(Figure&) x = %d, y=%d, dx=%d, dy=%d\n", figure.x, figure.y, dx, dy);
		figure.x += dx;
		figure.y += dy;
	}
};



int main() {
	setlocale(LC_ALL, "Rus");

	cout << endl << endl << "������������, �����������" << endl;
	{
		Figure f1;
		Square s1;

		Figure* f2 = new Square(s1);
		Figure f3(f1);

		delete f2;
	}

	Square* s1 = new Square();
	s1->x = 10;
	Figure* f1 = new Square();
	f1->x = 10;

	s1->PrintInfo(); 
	f1->PrintInfo(); //���������� ����� ������, �.�. � Square �� �������������, �� ��������
	
	delete s1;
	delete f1;

	cout << endl << endl << "�������� ��������� �������� ��������" << endl;

	{
		Figure f2;
		f2.x = 5;
		f2.y = 5;
		f2.PrintInfo();

		OffsetSuperMaster wonderwafla;
		wonderwafla.TryOffset1(f2, 10, 10); //���������� ������
		f2.PrintInfo();//������ �� ���������

		wonderwafla.TryOffset2(&f2, 10, 10); //������� ��������� �� ������
		f2.PrintInfo(); //������ ���������

		wonderwafla.TryOffset3(f2, 10, 10); //������� ��� ������
		f2.PrintInfo(); //������ ���������
	}
	
	cout << endl << endl << "���������� �����" << endl;

	Figure* kvadrat = new Square();

	if (kvadrat->isA("Square")) {
		((Square*)kvadrat)->width = 16;
		cout << "1)������� �������� = " << ((Square*)kvadrat)->GetArea() << endl;
	}
		

	Square* realKvadrat = dynamic_cast<Square*>(kvadrat);
	if (realKvadrat) // != nullptr
	{
		realKvadrat->width = 17;
		cout << "2)������� �������� = " << realKvadrat->GetArea() << endl;
	}
		

	cout << "����� ���������" << endl;
	delete kvadrat; 
	//delete realKvadrat; //�� ������ � ��������� kvadrat ������ ��� ������
}