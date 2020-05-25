#include <iostream>
#include <cmath>
#include <vector>

//-----------------------------------------------------------------------------

class Shape
{
public:
	virtual double area() const = 0;
};

class Square : public Shape
{
public:
	Square(double size = 1.0) :
		_side(size)
	{
	}

	virtual double area() const
	{
		return _side * _side;
	}

private:
	double _side;
};

//-----------------------------------------------------------------------------

class Triangle : public Shape
{
public:
	Triangle(double side_a = 3.0, double side_b = 4.0, double side_c = 5.0) :
		_side_a(side_a),
		_side_b(side_b),
		_side_c(side_c)
	{
	}

	virtual double area() const
	{
		double p = (_side_a + _side_b + _side_c) / 2.0;

		return sqrt(p * (p - _side_a) * (p - _side_b) * (p - _side_c));
	}

private:
	double _side_a;
	double _side_b;
	double _side_c;
};
class Rectangle : public Shape
{
public:
	Rectangle(double side_a = 3.0, double side_b = 4.0) :
		_side_a(side_a),
		_side_b(side_b)
	{
	}

	virtual double area() const
	{
		return _side_a * _side_b;
	}

private:
	double _side_a;
	double _side_b;
};
//-----------------------------------------------------------------------------

class Circle : public Shape
{
	static const double Pi;

public:
	Circle(double radius = 1.0) :
		_radius(radius)
	{
	}

	virtual double area() const
	{
		return Pi * _radius * _radius;
	}

private:
	double _radius;
};

const double Circle::Pi = 3.14159265358979323;

//-----------------------------------------------------------------------------

int main()
{
	setlocale(LC_ALL, "Rus");

	std::vector< Shape* > shapes;
	size_t choise;

	do
	{
		std::cout << "Меню" << std::endl
			<< "1. Создать квадрат" << std::endl
			<< "2. Создать треугольник" << std::endl
			<< "3. Создать круг" << std::endl
			<< "4. Создать прямоугльник" << std::endl
			<< "5. Рассчитать площади созданных фигур и выйти" << std::endl;
		std::cin >> choise;

		switch (choise)
		{
		case 1:
		{
			double side;

			std::cout << "Квадрат:" << std::endl;
			std::cout << "Введите длину стороны: ";
			std::cin >> side;
			std::cout << "Рисуется квадрат " << std::endl;

			shapes.push_back(new Square(side));

			break;
		}

		case 2:
		{
			double side_a, side_b, side_c;

			std::cout << "Треугольник:" << std::endl;
			std::cout << "Введите длину стороны a: ";
			std::cin >> side_a;
			std::cout << "Введите длину стороны b: ";
			std::cin >> side_b;
			std::cout << "Введите длину стороны c: ";
			std::cin >> side_c;
			std::cout << "Рисуется треугольник " << std::endl;

			shapes.push_back(new Triangle(side_a, side_b, side_c));

			break;
		}

		case 3:
		{
			double radius;

			std::cout << "Круг:" << std::endl;
			std::cout << "Введите длину радиуса: ";
			std::cin >> radius;
			std::cout << "Рисуется круг " << std::endl;

			shapes.push_back(new Circle(radius));

			break;
		}
		
		case 4:
		{
			double side_a, side_b;

			std::cout << "Прямоугольник:" << std::endl;
			std::cout << "Введите длину стороны a: ";
			std::cin >> side_a;
			std::cout << "Введите длину стороны b: ";
			std::cin >> side_b;
			std::cout << "Рисуется прямоугольник " << std::endl;

			shapes.push_back(new Rectangle(side_a, side_b));

			break;
		}

		case 5:
		{
			Square* square_pointer;
			Triangle* triangle_pointer;
			Circle* circle_pointer;
			Rectangle* rectangle_pointer;
			size_t size = shapes.size();

			for (size_t i = 0; i < size; ++i)
			{
				square_pointer = dynamic_cast<Square*>(shapes[i]);
				triangle_pointer = dynamic_cast<Triangle*>(shapes[i]);
				circle_pointer = dynamic_cast<Circle*>(shapes[i]);
				rectangle_pointer = dynamic_cast<Rectangle*>(shapes[i]);

				if (square_pointer != 0)
					std::cout << "Квадрат.     Площадь = ";

				if (triangle_pointer != 0)
					std::cout << "Треугольник. Площадь = ";

				if (circle_pointer != 0)
					std::cout << "Круг.        Площадь = ";
				
				if (rectangle_pointer != 0)
					std::cout << "Прямоугольник. Площадь = ";

				std::cout << shapes[i]->area() << std::endl;
			}

			break;
		}

		default:
		{
			std::cout << "Недопустимое действие! Попробуйте снова." << std::endl;

			break;
		}
		};
	} while (choise != 5);

	size_t size = shapes.size();

	for (size_t i = 0; i < size; ++i)
		delete shapes[i];

	return 0;
}