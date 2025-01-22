#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	int x = 42;
	float y;
	std::string s;

	std::cout << "x = " << x << "\n";

	std::cout << "Enter an integer value for x: ";
	std::cin >> x;
	//if (std::cin.fail())
	//{
		//std::cout << "Invalid integer... Setting x to -1";
		//x = -1;

		//std::cin.ignore(1, '\n');
		//std::cin.clear();
	//}
	std::cout << "Enter a float value for y: ";
	std::cin >> y;
	std::cout << "Enter a string value for s: ";
	std::cin >> s;

	std::cout << "You entered\n\tx= " << x << "\n\ty= " << y << "\n\ts= " << s << "\n";




	return 0;
}