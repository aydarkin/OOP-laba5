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
		cout << "óńňđîĺí destroyed Figure" << endl;
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

	void PrintInfo() { //ďĺđĺîďđĺäĺë˙ĺň ěĺňîä đîäčňĺë˙
		printf("Square { x = %d, y = %d, width = %d }\n", this->x, this->y, this->width);
	}

	virtual ~Square() override { //ďĺđĺęđűâŕĺň
		cout << "óńňđîĺí destroyed Square" << endl;
	}

	virtual string ClassName() override { //ďĺđĺęđűâŕĺň
		return "Square";
	}

	virtual bool isA(string className) override { //ďĺđĺęđűâŕĺň
		return className == ClassName() || Figure::isA(className);
	}

	int GetArea() { //ńâîé ěĺňîä
		return width * width;
	} 
};

class OffsetSuperMaster
{
public:
	void TryOffset1(Figure figure, int dx, int dy) {
		//ďĺđĺäŕĺňń˙ îáúĺęň ďîëíîńňüţ
		printf("TryOffset1(Figure) x = %d, y=%d, dx=%d, dy=%d\n", figure.x, figure.y, dx, dy);
		figure.x += dx;
		figure.y += dy;
	}
	void TryOffset2(Figure* figure, int dx, int dy) {
		//ďĺđĺäŕĺňń˙ óęŕçŕňĺëü íŕ îáúĺęň
		printf("TryOffset2(Figure*) x = %d, y=%d, dx=%d, dy=%d\n", figure->x, figure->y, dx, dy);
		figure->x += dx;
		figure->y += dy;
	}
	void TryOffset3(Figure& figure, int dx, int dy) {
		//ďĺđĺäŕĺňń˙ ŕäđĺń îáúĺęňŕ
		printf("TryOffset3(Figure&) x = %d, y=%d, dx=%d, dy=%d\n", figure.x, figure.y, dx, dy);
		figure.x += dx;
		figure.y += dy;
	}
};



int main() {
	setlocale(LC_ALL, "Rus");

	cout << endl << endl << "Ęîíńňđóęňîđű, äĺńňđóęňîđű" << endl;
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
	f1->PrintInfo(); //âűçűâŕĺňń˙ ěĺňîä ďđĺäęŕ, ň.ę. â Square îí ďĺđĺîďđĺäĺëĺí, íĺ ďĺđĺęđűň
	
	delete s1;
	delete f1;

	cout << endl << endl << "Ďđîâĺđęŕ ěĺőŕíčçěŕ ďĺđĺäŕ÷č îáúĺęňîâ" << endl;

	{
		Figure f2;
		f2.x = 5;
		f2.y = 5;
		f2.PrintInfo();

		OffsetSuperMaster wonderwafla;
		wonderwafla.TryOffset1(f2, 10, 10); //ńęîďčđîâŕí îáúĺęň
		f2.PrintInfo();//îáúĺęň íĺ čçěĺíčëń˙

		wonderwafla.TryOffset2(&f2, 10, 10); //ďĺđĺäŕí óęŕçŕňĺëü íŕ îáúĺęň
		f2.PrintInfo(); //îáúĺęň čçěĺíčëń˙

		wonderwafla.TryOffset3(f2, 10, 10); //ďĺđĺäŕí ńŕě îáúĺęň
		f2.PrintInfo(); //îáúĺęň čçěĺíčëń˙
	}
	
	cout << endl << endl << "Ďđčâĺäĺíčĺ ňčďîâ" << endl;

	Figure* kvadrat = new Square();

	if (kvadrat->isA("Square")) {
		((Square*)kvadrat)->width = 16;
		cout << "1)Ďëîůŕäü ęâŕäđŕňŕ = " << ((Square*)kvadrat)->GetArea() << endl;
	}
		

	Square* realKvadrat = dynamic_cast<Square*>(kvadrat);
	if (realKvadrat) // != nullptr
	{
		realKvadrat->width = 17;
		cout << "2)Ďëîůŕäü ęâŕäđŕňŕ = " << realKvadrat->GetArea() << endl;
	}
		

	cout << "Ęîíĺö ďđîăđŕěěű" << endl;
	delete kvadrat; 
	//delete realKvadrat; //ďî ŕäđĺńó â óęŕçŕňĺëĺ kvadrat îáúĺęň óćĺ óäŕëĺí
}
