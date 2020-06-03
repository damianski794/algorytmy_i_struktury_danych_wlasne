// sortowanie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

void print_vector(std::vector<int> v) {
	for (auto i: v) {
		cout << i << "  ";
	}
	cout<<endl;
}

void my_bubble_sort(std::vector<int> v) {
	/*
	Algorytm opiera sie na porownywaniu 2 kolejnych elemtow i ew. zamienianiu ich miejscami
	*/

	/*
	Z³o¿onoœæ obliczeniowa bez printów to O(n^2)

	a dokladniej liczba porownan to:
	n - dlugosc wektora
	suma porownan = (n-1) + (n-2) + (n-3) + ... + 1
	tworzac ciag arytm. dostaje:
	suma porownan = (n-1)*(n)/2
	*/
	for (int i = 0; i < v.size(); i++) {
		print_vector(v);
		for (int j = 0; j < v.size() - i - 1; j++) {
			if (v[j] > v[j+1]) swap(v[j], v[j+1]);
			print_vector(v);
		}
		cout << "---" << std::endl;
	}
	std::cout << "==================" << std::endl;
}

void my_selection_sort(std::vector<int> v) {
	/*algorytm polega na znajdywaniu najwiekszego elementu i zamienieniu go na ostatnim miejscu wektora,
	potem kolejny nawiekszy element jest namieniany z przedostanim itd.*/

	/*z³o¿onoœæ O(n^2)
	
	liczba porownan identyczna jak bubble_sort*/
	for (int i = 0; i < v.size(); i++) {
		print_vector(v);
		int max_index = 0;
		for(int j=0;j<v.size()-i;j++){
			if (v[j] > v[max_index]) max_index = j;
		}
		swap(v[max_index], v[v.size() - i - 1]);
	}
	cout << "final sorted vector: ";
	print_vector(v);
}

void my_insertion_sort(std::vector<int> v) {
	/*sortowanie przez wstawianie polega na tworzeniu coraz to wiekszego posortowanego ci¹gu*/
	//--bool go_to_main_loop = false;
	for (int i = 1; i < v.size(); i++) {
		print_vector(v);
		//--bool first_found = false;

		int k = i - 1;
		int last_value = v[i];
		int where_stopped = i;
		while (k >= 0 && v[k] > last_value) {
			v[k + 1] = v[k];
			where_stopped = k;
			/*if (k == 0) {
				v[k] = last_value;
			}*/
			k--;
		}
		//if(k>0) 
		v[where_stopped] = last_value;
		/*for (int j = i - 1;j >= 0 && !go_to_main_loop; j--) {
			if (v[i] >= v[j] && !first_found) {
				first_found = true;
				int last_value = v[i];
				for (int k = j; k < i; k++) {
					v[k + 1] = v[k];
				}
				v[j] = last_value;
			}
		}*/
		cout << "Przezylem petle nr: " << i << endl;
		cout << "--------------" << std::endl;
		/*cout << " a wektor po petli wyglada tak: ";
		print_vector(v);*/

	}
	print_vector(v);
}

int main()
{
    //std::cout << "Hello World!\n";
	auto v = vector<int>{ 5,4,2,3,6,1 };
	//my_bubble_sort(v);
	//my_selection_sort(v);
	my_insertion_sort(v);


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
