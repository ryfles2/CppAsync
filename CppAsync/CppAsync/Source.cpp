#include <future>
#include <chrono>
#include <random>
#include <iostream>
#include <array>


int doSmething(char c)
{
	//generator liczb locowych c-ziarno
	std::default_random_engine dre(c);
	std::uniform_int_distribution<int>	id(10, 1000);
	//wyswitlanie znaku po up³ywie losowego czasu
	for (auto i = 0; i < 10; ++i)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(id(dre)));
		std::cout.put(c).flush();
	}
	std::cout << std::endl;
	return c;
}
int func1()
{
	return  doSmething('.');
}
int func2()
{
	return  doSmething('+');
}
int r(int x, int y)
{
	return x + y;
}

int main(int argc, char* argv[])
{
	std::cout << "func1 w tle func2 na pierwszym planie" << std::endl;
	// rozne sposoby zapisu
	//std::future<int> result1(std::async(func1));
	//auto result1(std::async(func1));
	auto result1 = (std::async(func1));

	int result2 = func2();

	//get podaje wynik je¿li takowy juz jest | czeka jesli nie | wywo³uje funkcje jesli jeszcze sie nie wywo³a³a i czeka na wynik
	int result = result1.get() + result2;
	std::cout << "Wynik sumy func1 i func 2= " << result << std::endl;



	//leniwe wartosci | lazy evaluation
	//wykonujemy w¹tek dopiero wtedy gdy u¿yjemy '.get()' np:
	auto f1 = std::async(std::launch::deferred, func1);
	auto f2 = std::async(std::launch::deferred, func2);

	//dopiero teraz watek sie wykonuje
	auto fResult = (result < 80) ? f1.get() : f2.get();

	auto d = std::async(r, 1, 2);
	auto e = std::async(std::launch::async, r, 1, 2);
	std::cout << e.get() << std::endl;

	std::array<int, 4> tablica;
	tablica.fill(0);

	tablica[1] = 4;
	std::cout << tablica[1] << std::endl;

	return 0;
}
