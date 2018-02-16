
#include <stdio.h>
#include <time.h>
#include <iostream>

/*

  Program został stworzony z celu porównania swojego tempa nauki na mature,
z idealnym sposobem nauki( w każdym dniu jest tyle samo stron do nauki)

  Z biologi i chemi były po 3 książki z określonymi ilościami stron, a program
wyliczał na której stronie miałeś być, w momencie w którym go włączyłeś. Deadline
był ustawiony na początek matury



*/

int main()
{

	int biol[3] { 426, 450, 372 };
	int chem[3] { 496, 460, 516 };
	tm start = { 0, 0, 0, 9, 8, 116, 5, 0, 0 };//{ 0, 0, 0, 10, 8, 116, 5, 0, 0 };
	tm end = { 0, 0, 0, 1, 5, 117, 5, 0, 0 };

	time_t start_time_t = mktime(&start);
	time_t end_time_t = mktime(&end);


	time_t done_days = ((time(NULL) - start_time_t) / (60 * 60 * 24));
	if (done_days < 0) done_days = 0;
	std::cout << "Ilosc zakonczonych dni wynosi: " << done_days << std::endl;
	++done_days;
	done_days -= int(done_days/7*2);
	time_t all_days = (end_time_t - start_time_t) / (60 * 60 * 24);
	all_days -= int(all_days/ 7 * 2);
	time_t upcoming_days = (end_time_t - time(NULL)) / (60 * 60 * 24);
	std::cout << "Ilosc pozostalych dni wynosi: " << upcoming_days << std::endl;
	upcoming_days -= int(upcoming_days / 7 * 2);

	




	



	std::cout << "Powinnas byc na: \n ";
	{ // biologia
		int book;
		int resultat = ((biol[0]+biol[1]+biol[2])/all_days)*done_days;
		if (resultat > biol[0] + biol[1])	{ resultat -= biol[0] + biol[1] ; book = 3; }
		else if (resultat > biol[0])		{ resultat -= biol[0] ; book = 2; }
		else								book = 1;
		
		std::cout << resultat << " stronie biologi w tomie: " << book << "\n";

		for (book--; book >0; book--)
			resultat += biol[book];

		std::cout << "  Pozostalo: " << (biol[0] + biol[1] + biol[2]) - resultat << " stron. \n ";
	}


	{ // chemia
		int book;
		int resultat = ((chem[0] + chem[1] + chem[2]) / all_days) * done_days;
		if (resultat > chem[0] + chem[1])	{ resultat -= chem[0] + chem[1]; book = 3; }
		else if (resultat > chem[0])		{ resultat -= chem[0]; book = 2; }
		else								book = 1;

		std::cout << resultat << " stronie chemi   w tomie: " << book << std::endl;
		
		for (book--; book >0; book--)
			resultat += chem[book];
		std::cout << "  Pozostalo: " << (chem[0] + chem[1] + chem[2])-resultat << " stron. \n ";
	}

	while (1);
	return 0;
}