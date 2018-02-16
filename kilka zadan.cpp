#include <iostream>
#include <cmath>
#include <limits> 


int fib(); // fibonacci
void xx();
int revers(int=0); //revers number
void num_sys(); // change number system
void pal(); // check if number is 
void last_num(); // last number before 0
void find_div(); // find num div in section
void test();

int main()
{
	std::cout << "Wybierz program:\n"
		<< "1. " << "Fibonacci,\n"
		<< "2. " << "Znalezienie rozw dla równanie x^x=n, dla danej liczby n,\n"
		<< "3. " << "rewers liczby,\n"
		<< "4. " << "Zamiana systemu liczbowego,\n"
		<< "5. " << "Sprawdzanie, czy liczba jest palindromem,\n"
		<< "6. " << "Ostatnia liczba silni przed zerami,\n"
		<< "7. " << "Znalezienie liczby podzielnej przez inna w danym przedziale,\n";

	int choice;
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		fib();
		break;

	case 2:
		xx();
		break;

	case 3:
		revers();
		break;

	case 4:
		num_sys();
		break;

	case 5:
		pal();
		break;

	case 6:
		last_num();
		break;

	case 7:
		find_div();
		break;

	case 8:
		test();
		break;

	default:
		break;
	}

	system("PAUSE");

	return 0;
}

int fib()
{
	std::cout << "Możliwe polecenia: \n"
		<< "1. " << "Dobranie 2 pierwszych liczb tak, aby znajdowala się wybrana liczba\n"
		<< "2. " << "Stworzenie ciągu na jednej zmiennej\n";

	int choice;
	std::cin >> choice;

	switch (choice)
	{
	case 1:

	default:
		break;
	}
	return 0;
}

void xx()
{
	std::cout << "Podaj liczbe n: ";

	int n;
	std::cin >> n;
	//n = pow(n,n);
	double x;
	double eps = std::numeric_limits<float>::epsilon();// 0.000000001;
	double min = 0;
	double max = 100;
	while (max - min > eps)
	{
		x = (max + min) / 2.0;
		if (pow(x,x)<n)min=x;
		else max = x;
		//std::cout << pow(x, x);
	}
	std::cout << "x= " << x;
}

int revers(int num)
{
	int rev =0;
	if (num == 0)
	{
		std::cout << "Podaj liczbe: ";
		std::cin >> num;
	}

	while (num > 0)
	{
		rev += num % 10;

		rev *= 10;
		num /= 10;
	}

	rev /= 10;

	std::cout << "Rewers wynosi: " << rev << "\n";

	return rev;
}

void num_sys()
{
	int num, num_sys=10, new_num =0, new_num_sys;
	//std::cout << "Podaj system kodowania: ";
	//std::cin >> num_sys;

	std::cout << "Podaj liczbe: ";
	std::cin >> num;

	std::cout << "Podaj nowy system kodowania: ";
	std::cin >> new_num_sys;
	int n=0;
	while (num>0)
	{
		new_num += num%new_num_sys*pow(10,n++);
		num /= new_num_sys;


	}

	std::cout << "Liczba: " << (new_num) << "\n";
}

void pal()
{
	int num;

	std::cout << "Podaj liczbe: ";
	std::cin >> num;
	

	if (num == revers(num))	std::cout << "To jest palindrom\n";
	else					std::cout << "To nie jest palidrom\n";
}

void last_num()
{
	while (true)
	{

		int num, sum = 1, num_temp,temp =1;

		std::cout << "Podaj liczbe: ";
		std::cin >> num;
		for (; num > 1; num--)
		{
			
			num_temp = num; // make temp because of div num_temp below

			while (num_temp % 5 == 0) num_temp /= 5, temp *= 2; // fucking ugly thing

			while  (num_temp % 2 == 0 && temp > 1) num_temp /= 2, temp /= 2; // fucking ugly thing


			sum *= num_temp;

			sum = sum % 10; // we take care only for last num
		}

		std::cout << "temp: " << temp << "\n";
		std::cout << "Ostatnia liczba wynosi: " << sum % 10 << "\n";
	}
}

void find_div()
{

	int div, min, max;
	bool flag = true;

	std::cout << "Podaj dzielnik: ";
	std::cin >> div;

	std::cout << "Podaj min wartosc: ";
	std::cin >> min;

	std::cout << "Podaj max wartosc: ";
	std::cin >> max, max++;

	for (; min < max; min++)
	{

		if (min%div == 0) std::cout << "Liczba wynosi: " << min << "\n", flag=false;

	}
	if (flag) std::cout << "Nie znaleziono liczby";


}

void test()
{
	//initialization

	int num, num_long = 0, temp_num, temp_num_long, sum;
	bool flag = true;


	// geting number
	std::cout << "Podaj liczbe: "; 
	std::cin >> num;

	//get long
	temp_num = num;
	while (temp_num > 0) temp_num /= 10, num_long += 1;
	

	//main loop for getting every number
	for (temp_num_long = pow(2,num_long); temp_num_long > 0;temp_num_long--)
	{
		//starting data
		temp_num = num;
		sum = 0;
		int print = temp_num_long;
		int position = 0;

		while (print>0)
		{
			if (print % 2)sum += (temp_num % 10)* pow(10, position++);
			temp_num /= 10;
			print /= 2;
		}

		//check %7
		std::cout << "liczba: " << sum << "\n";
		if (sum % 7 == 0) flag = false, std::cout << "liczba jest podzielna przez 7\n";
	}
	if (flag) std::cout << "Nie ma liczby podzielnej przez 7\n";

}