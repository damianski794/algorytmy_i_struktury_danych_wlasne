// lista_dwukierunkowa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

class wezel {
public:
	wezel* nastepny_wezel = nullptr;
	wezel* poprzedni_wezel = nullptr;
	int wartosc;

	wezel(int wartosc) {
		this->wartosc = wartosc;
	}
	wezel(){
	}
};

class lista_dwukierunkowa {
public:
	lista_dwukierunkowa() {
		glowa = new wezel;
		ogon = new wezel;

		glowa->nastepny_wezel = ogon;
		ogon->poprzedni_wezel = glowa;

		dlugosc_listy = 0;
	}

	bool empty() {
		if (dlugosc_listy == 0)
			return true;
		else
			return false;
	}
	int front() { //zwraca wartosc pierwszego elementu
		if (dlugosc_listy != 0)
			return glowa->nastepny_wezel->wartosc;
	}
	int back() { //zwraca wartosc ostatniego elementu
		if (dlugosc_listy != 0)
			return ogon->poprzedni_wezel->wartosc;
	}

	void push_front(int wartosc) {
		dlugosc_listy++;

		wezel *nowy_wezel = new wezel(wartosc);
		glowa->nastepny_wezel->poprzedni_wezel = nowy_wezel;

		nowy_wezel->nastepny_wezel = glowa->nastepny_wezel;
		nowy_wezel->poprzedni_wezel = glowa;

		glowa->nastepny_wezel = nowy_wezel;
		
	}
	void push_back(int wartosc) {
		dlugosc_listy++;

		wezel* nowy_wezel = new wezel(wartosc);
		ogon->poprzedni_wezel->nastepny_wezel = nowy_wezel;

		nowy_wezel->nastepny_wezel = ogon;
		nowy_wezel->poprzedni_wezel = ogon->poprzedni_wezel;

		ogon->poprzedni_wezel = nowy_wezel;
	}
	void pop_front() {
		
		if (dlugosc_listy <= 0) return;
		else if (dlugosc_listy == 1) {
			//dodac zwolnienie pamieci
			wezel* wezel = glowa->nastepny_wezel;
			glowa->nastepny_wezel = ogon;
			ogon->poprzedni_wezel = glowa;
			delete wezel;
			cout << "usunieto pamiec" << endl;
		}
		else {}

		dlugosc_listy--;
	}
	void pop_back() {
		if (dlugosc_listy <= 0) return;
		else if (dlugosc_listy == 1) {
			//dodac zwolnienie pamieci
			wezel* wezel = ogon->poprzedni_wezel;
			glowa->nastepny_wezel = ogon;
			ogon->poprzedni_wezel = glowa;
			delete wezel;
			cout << "usunieto pamiec" << endl;
		}
		else {
			//dodac co robic gdy jest wiecej elementow
		}
	}
	void insert(int pozycja, int wartosc);
	void erase(int pozycja);

	int next(int pozycja); //zwraca nastepna pozycja wzgledem danej
	void print_whole_list() {
		//cout << "ogon->wartosc: " << ogon->wartosc;
		wezel* wezel = glowa;
		while (wezel->nastepny_wezel && wezel->nastepny_wezel != ogon) { //while wezel->nastepny_wezel is not nullptr //sprawdzic czemu to cudo nie dziala bez &&
			cout << wezel->nastepny_wezel->wartosc << "  ";
			wezel = wezel->nastepny_wezel;
		}
		cout << endl;
	}

private:
	wezel* glowa;
	wezel* ogon;
	int dlugosc_listy;
};

int main()
{
	lista_dwukierunkowa lista;
	cout << "czy lista pusta: " << lista.empty() << endl;
	lista.push_front(10);
	lista.print_whole_list();
	lista.pop_front();
	cout << "lista po usuwaniu pierwszego elementu: ";
	lista.print_whole_list();

	lista.push_front(20);
	lista.push_back(30);
	cout << "lista przed usuwaniem ostatniego elementu:  ";
	lista.print_whole_list();
	lista.pop_back();
	cout << "lista po usuwaniu ostatniego elementu:  ";
	lista.print_whole_list();

	cout << "czy lista pusta: " << lista.empty() << endl;
	cout << "wartosc pierwszego elementu: " << lista.front() << endl;
	cout << "wartosc ostatniego elementu: " << lista.back() << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

