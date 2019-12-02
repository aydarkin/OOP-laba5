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
		cout << "устроен destroyed Figure" << endl;
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

	void PrintInfo() { //переопределяет метод родителя
		printf("Square { x = %d, y = %d, width = %d }\n", this->x, this->y, this->width);
	}

	virtual ~Square() override { //перекрывает
		cout << "устроен destroyed Square" << endl;
	}

	virtual string ClassName() override { //перекрывает
		return "Square";
	}

	virtual bool isA(string className) override { //перекрывает
		return className == ClassName() || Figure::isA(className);
	}

	int GetArea() { //свой метод
		return width * width;
	}
};

class OffsetSuperMaster
{
public:
	void TryOffset1(Figure figure, int dx, int dy) {
		//передается объект полностью
		printf("TryOffset1(Figure) x = %d, y=%d, dx=%d, dy=%d\n", figure.x, figure.y, dx, dy);
		figure.x += dx;
		figure.y += dy;
	}
	void TryOffset2(Figure* figure, int dx, int dy) {
		//передается указатель на объект
		printf("TryOffset2(Figure*) x = %d, y=%d, dx=%d, dy=%d\n", figure->x, figure->y, dx, dy);
		figure->x += dx;
		figure->y += dy;
	}
	void TryOffset3(Figure& figure, int dx, int dy) {
		//передается адрес объекта
		printf("TryOffset3(Figure&) x = %d, y=%d, dx=%d, dy=%d\n", figure.x, figure.y, dx, dy);
		figure.x += dx;
		figure.y += dy;
	}
};



int main() {
	setlocale(LC_ALL, "Rus");

	cout << endl << endl << "Конструкторы, деструкторы" << endl;
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
	f1->PrintInfo(); //вызывается метод предка, т.к. в Square он переопределен, не перекрыт
	
	delete s1;
	delete f1;

	cout << endl << endl << "Проверка механизма передачи объектов" << endl;

	{
		Figure f2;
		f2.x = 5;
		f2.y = 5;
		f2.PrintInfo();

		OffsetSuperMaster wonderwafla;
		wonderwafla.TryOffset1(f2, 10, 10); //скопирован объект
		f2.PrintInfo();//объект не изменился

		wonderwafla.TryOffset2(&f2, 10, 10); //передан указатель на объект
		f2.PrintInfo(); //объект изменился

		wonderwafla.TryOffset3(f2, 10, 10); //передан сам объект
		f2.PrintInfo(); //объект изменился
	}
	
	cout << endl << endl << "Приведение типов" << endl;

	Figure* kvadrat = new Square();

	if (kvadrat->isA("Square")) {
		((Square*)kvadrat)->width = 16;
		cout << "1)Площадь квадрата = " << ((Square*)kvadrat)->GetArea() << endl;
	}
		

	Square* realKvadrat = dynamic_cast<Square*>(kvadrat);
	if (realKvadrat) // != nullptr
	{
		realKvadrat->width = 17;
		cout << "2)Площадь квадрата = " << realKvadrat->GetArea() << endl;
	}
		

	cout << "Конец программы" << endl;
	delete kvadrat; 
	//delete realKvadrat; //по адресу в указателе kvadrat объект уже удален
}