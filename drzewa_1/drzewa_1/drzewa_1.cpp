// drzewa_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cmath>

class wezel {
private:
	int wartosc;
	wezel* ojciec;
	wezel* lewy_syn;
	wezel* prawy_syn;
	int poziom; //badanie drzewa binarnego

public:
	wezel(int wartosc_, wezel* lewy_syn_ = nullptr, wezel* prawy_syn_ = nullptr) {
		wartosc = wartosc_;
		lewy_syn = lewy_syn_;
		prawy_syn = prawy_syn_;
	}

	int get_wartosc() { return wartosc; }
	wezel* get_lewy_syn() { return lewy_syn; }
	wezel* get_prawy_syn() { return prawy_syn; }
	wezel* get_ojciec() { return ojciec; }

	void setPoziom(int poziom_) { poziom = poziom_; }
	int getPoziom() { return poziom; }

	friend class drzewo_binarne;
};

class drzewo {
protected:
	int dlugosc_najdluzszej_sciezki_od_korzenia_do_liscia = -1;
	int dlugosc_najkrotszej_sciezki_od_korzenia_do_liscia = INT_MAX;
	std::vector<int> liczba_wezlow_na_poziomach_vector;
	wezel* korzen;
	int number_of_leaves = 0;
	int liczba_wezlow_z_tylko_jednym_synem = 0;
	int suma_wartosci_wszystkich_wezlow = 0;

public:
	drzewo(wezel* korzen_) {
		korzen = korzen_;
		korzen->setPoziom(0);
	}
	/*void dodaj_wezel(int wartosc_) {
		wezel* wezel_ = new wezel(wartosc_);
		dodaj_wezel(wezel_);
	}
	void dodaj_wezel(wezel* wezel_, wezel* baza_do_nastepnej_iteracji = nullptr) {
		return;
	}*/

	void print_tree_BFS(){ //breath-first search (POZIOM PO POZIOMIE)
		std::queue<wezel*> q;
		q.push(korzen);
		while (!q.empty()) {
			std::cout << q.front()->get_wartosc() << " ";
			if (q.front()->get_lewy_syn())
				q.push(q.front()->get_lewy_syn());
			if (q.front()->get_prawy_syn())
				q.push(q.front()->get_prawy_syn());
			q.pop();
		}
		std::cout << std::endl;
	}
};

class drzewo_binarne : public drzewo {

public:
	drzewo_binarne(int wartosc_): drzewo(new wezel(wartosc_)) {}

	void dodaj_wezel_do_drzewa_binarnego(int wartosc_) {
		if (korzen != nullptr) {
			wezel* nowy_wezel = new wezel(wartosc_);
			dodaj_wezel(nowy_wezel, korzen);
		}
		else {
			// TODO: jesli nie istnieje korzen (chyba jakos zostal usuniety) to przy dodawaniu nowego wezla trzeba ustawic korzen = nowy_wezel chyba
			std::cout << "Nie istnieje korzen, wiec nie udalo siê dodaæ elementu do drzewa." << std::endl;
		}
	}
	void dodaj_wezel(wezel* wezel_, wezel* next_base){
		if (wezel_->get_wartosc() < next_base->get_wartosc()) {
			if (next_base->lewy_syn == nullptr) {
				wezel_->ojciec = next_base; //dodane 29.05-2020
				next_base->lewy_syn = wezel_;
				wezel_->setPoziom(next_base->getPoziom() + 1);
			}
			else {
				return dodaj_wezel(wezel_, next_base->lewy_syn);
			}
		}
		else{
			if (next_base->prawy_syn == nullptr) {
				wezel_->ojciec = next_base; //dodane 29.05-2020
				next_base->prawy_syn = wezel_;
				wezel_->setPoziom(next_base->getPoziom() + 1);
			}
			else {
				return dodaj_wezel(wezel_, next_base->prawy_syn);
			}
		}
	}
	wezel* getKorzen() { return korzen; }

	void print_drzewo_binarne_DFS_PRE_ORDER(wezel* poczatkowy_wezel) { //przejscie wzdluzne
		//std::cout << "Wartosc:  " << poczatkowy_wezel->get_wartosc() << ", znajduje sie pod adresem: " << poczatkowy_wezel << std::endl;
		std::cout << poczatkowy_wezel->get_wartosc() << " ";
		if (poczatkowy_wezel->lewy_syn)
			print_drzewo_binarne_DFS_PRE_ORDER(poczatkowy_wezel->lewy_syn);
		if (poczatkowy_wezel->prawy_syn)
			print_drzewo_binarne_DFS_PRE_ORDER(poczatkowy_wezel->prawy_syn);
	}

	void print_drzewo_binarne_DFS_IN_ORDER(wezel* poczatkowy_wezel) { // przejscie poprzeczne
		
		if (poczatkowy_wezel->lewy_syn)
			print_drzewo_binarne_DFS_IN_ORDER(poczatkowy_wezel->lewy_syn);

		std::cout << poczatkowy_wezel->get_wartosc() << " ";

		if (poczatkowy_wezel->prawy_syn)
			print_drzewo_binarne_DFS_IN_ORDER(poczatkowy_wezel->prawy_syn);
	}

	void print_drzewo_binarne_DFS_POST_ORDER(wezel* poczatkowy_wezel) { // przejscie poprzeczne

		if (poczatkowy_wezel->lewy_syn)
			print_drzewo_binarne_DFS_POST_ORDER(poczatkowy_wezel->lewy_syn);

		if (poczatkowy_wezel->prawy_syn)
			print_drzewo_binarne_DFS_POST_ORDER(poczatkowy_wezel->prawy_syn);

		std::cout << poczatkowy_wezel->get_wartosc() << " ";
	}

	void print_drzewo_binarne_DFS_PRE_ORDER_Z_LEWELAMI(wezel* poczatkowy_wezel) {
		std::cout <<"["<< poczatkowy_wezel->get_wartosc() << ", lvl:"<<poczatkowy_wezel->getPoziom()<<"] ";
		if (poczatkowy_wezel->lewy_syn)
			print_drzewo_binarne_DFS_PRE_ORDER_Z_LEWELAMI(poczatkowy_wezel->lewy_syn);
		if (poczatkowy_wezel->prawy_syn)
			print_drzewo_binarne_DFS_PRE_ORDER_Z_LEWELAMI(poczatkowy_wezel->prawy_syn);
	}
	
	int get_dlugosc_najdluzszej_sciezki_od_korzenia_do_liscia() {
		traverse_DFS_PRE_ORDER(korzen);
		return dlugosc_najdluzszej_sciezki_od_korzenia_do_liscia;
	}
	int get_dlugosc_najkrotszej_sciezki_od_korzenia_do_liscia() {
		traverse_DFS_PRE_ORDER(korzen);
		return dlugosc_najkrotszej_sciezki_od_korzenia_do_liscia;
	}
	std::vector<int> get_Liczba_wezlow_na_kazdym_poziomie() {
		liczba_wezlow_na_poziomach_vector.clear();
		int najdl_sciezka = get_dlugosc_najdluzszej_sciezki_od_korzenia_do_liscia();
		liczba_wezlow_na_poziomach_vector = std::vector<int>(najdl_sciezka+1, 0); // najdluzsza_sciezka + 1 bo najdluzsza sciezka jest o 1 krotsza od maksymalnej liczby poziomow (poziom 0, poziom 1, poziom 2 ...)
		traverse_DFS_PRE_ORDER_check_vector(korzen);
		for (auto& liczba_na_jednym_poziomie : liczba_wezlow_na_poziomach_vector)
			std::cout << liczba_na_jednym_poziomie << " ";
		std::cout<<std::endl;
		// TODO: dodac sprawdzenie liczby wezlow na kazdym poziomie (wykorzystac traverse_DFS_PRE_ORDER_check_vector)
		return liczba_wezlow_na_poziomach_vector;
	}
	int get_number_of_leaves() {
		traverse_DFS_PRE_ORDER_count_leaves(korzen);
		return number_of_leaves;
	}
	int get_liczba_wezlow_z_tylko_jednym_synem() { 
		traverse_DFS_PRE_ORDER_count_nodes_with_one_child(korzen);
		return liczba_wezlow_z_tylko_jednym_synem;
	}
	
	int get_suma_wartosci_wszystkich_wezlow() {
		traverse_DFS_PRE_ORDER_sum_node_values(korzen);
		return suma_wartosci_wszystkich_wezlow;
	}

	void print_binary_tree_in_console() {
		
		
		traverse_DFS_IN_ORDER_REVERSED_print_in_console("","",korzen);
	}
	
	wezel* search_value_BST(wezel* start_node, int szukana_wartosc) {
		int start_node_wartosc = start_node->get_wartosc();
		if (start_node_wartosc == szukana_wartosc) {
			return start_node;
		}
		if (start_node->get_lewy_syn() && szukana_wartosc < start_node_wartosc)
			return search_value_BST(start_node->get_lewy_syn(), szukana_wartosc);
		if (start_node->get_prawy_syn() && szukana_wartosc > start_node_wartosc)
			return search_value_BST(start_node->get_prawy_syn(), szukana_wartosc);
		return nullptr;
	}
	wezel* search_min_value_node_BST(wezel* start_node) {
		//auto start_node = korzen;
		if (start_node == nullptr)
			return nullptr;
		while (true) {
			wezel* child = start_node->get_lewy_syn();
			if (child == nullptr)
				return start_node;
			start_node = child;
		}
		return nullptr;
	}
	wezel* search_max_value_node_BST(wezel* start_node) { //wezel* search_max_value_node_BST() {
		//auto start_node = korzen;
		if (start_node == nullptr)
			return nullptr;
		while (start_node->get_prawy_syn() != nullptr) {
			start_node = start_node->get_prawy_syn();
		}
		return start_node;
	}

	wezel* find_successor_BST(wezel* wezel_poczatkowy) {
		if (wezel_poczatkowy->prawy_syn != nullptr) { //PRZYPADEK 1, istnieje prawy syn elementu, którego szukamy
			std::cout << "przypadek 1" << std::endl;
			return search_min_value_node_BST(wezel_poczatkowy->prawy_syn);
		}
		else { //nie ma prawego syna
			// 1 szukamy pierwszego ojca, dla którego nasz wêze³ le¿y w lewym poddrzewie
			wezel* potentcjalny_ojciec =  znajdz_pierwszego_ojca_dla_ktorego_nasz_wezel_lezy_w_lewym_poddrzewie(wezel_poczatkowy);
			//napisalem potencjalny bo moze byc nullem. I tak go zwracamy
			return potentcjalny_ojciec;
		}
	}
	wezel* find_predecessor_BST(wezel* wezel_poczatkowy) {
		if (wezel_poczatkowy->lewy_syn != nullptr) { //jest lewy syn
			return search_max_value_node_BST(wezel_poczatkowy->lewy_syn);
		}
		else { //nie ma lewego syna. idziemy w gore i szukamy ojca, dla ktorego obecny wezel 
			return znajdz_pierwszego_ojca_dla_ktorego_nasz_wezel_lezy_prawym_poddrzewie(wezel_poczatkowy);
		}
	}
	void usuwanie_wezla_z_drzewa_BST(int wartosc_klucza) { // BST = binary search tree
		
		wezel* wezel_do_usuniecia = search_value_BST(korzen, wartosc_klucza);
		if (wezel_do_usuniecia == nullptr) {
			std::cout << "wezel, ktory chcesz usunac nie istnieje" << std::endl;
			return;
		}
		//przypadek 1 - usuwany wezel nie ma synow (czyli jest lisciem drzewa)
		//wtedy po prostu usuwamy go i zwalniamy pamiec
		if (wezel_do_usuniecia->prawy_syn == nullptr && wezel_do_usuniecia->lewy_syn == nullptr) {
			if (wezel_do_usuniecia->ojciec) {//jesli ma ojca to zmien ze wskazanie jego ojca na ten wezel bedzie nullptr
				if (wezel_do_usuniecia->ojciec->lewy_syn == wezel_do_usuniecia) {
					wezel_do_usuniecia->ojciec->lewy_syn = nullptr;
				}
				else
				{
					wezel_do_usuniecia->ojciec->prawy_syn = nullptr;
				}
			}
			delete wezel_do_usuniecia;
		}
		//przypadek 2 - usuwamy wezel, ktory ma tylko jednego syna
		//wtedy wystarczy, ze zrobimy podmianke ze synem ojca aktualnego wezla jest syn aktualnego wezla
		else if ((wezel_do_usuniecia->prawy_syn && wezel_do_usuniecia->lewy_syn == nullptr) ||
			(wezel_do_usuniecia->lewy_syn && wezel_do_usuniecia->prawy_syn == nullptr)){
			wezel* syn = (wezel_do_usuniecia->prawy_syn) ? wezel_do_usuniecia->prawy_syn : wezel_do_usuniecia->lewy_syn; //sprawdzenie ktory syn jest aktywny (nie jest nullptr)
			if (wezel_do_usuniecia->ojciec) { //jesli istnieje ojciec obecnie sprawdzanego wezla:
				if (wezel_do_usuniecia->ojciec->lewy_syn == wezel_do_usuniecia) {
					wezel_do_usuniecia->ojciec->lewy_syn = syn;
				}
				else {
					wezel_do_usuniecia->ojciec->prawy_syn = syn;
				}
			}
			delete wezel_do_usuniecia;
		}
		else { //wezel ma 2 synow
			// TODO: dopisac usuwanie wezla gdy ten ma 2 synow
		}
	}

private:
	wezel* znajdz_pierwszego_ojca_dla_ktorego_nasz_wezel_lezy_prawym_poddrzewie(wezel* ojciec){
		//znajduje pierwszy wezel (ojca), do ktorego przyszlo sie z prawej strony
	    //jesli taki ojciec nie istnieje to zwracamy nullptr
		if (ojciec == nullptr)
			return nullptr;
		while (true) {
			if (ojciec->ojciec == nullptr) { //jezeli nie istnieje ojciec obecnie sprawdzanego wezla
				return nullptr;
			}
			else
			{
				if (ojciec->ojciec->prawy_syn == ojciec) //jesli prawym synem obecnie sprawdzanego ojca jest obecnie sprawdzany wezel
					return ojciec->ojciec;
				else {
					ojciec = ojciec->ojciec;
				}
			}
		}
	}

	wezel* znajdz_pierwszego_ojca_dla_ktorego_nasz_wezel_lezy_w_lewym_poddrzewie(wezel* ojciec){
		//znajduje pierwszy wezel (ojca), do ktorego przyszlo sie z lewej strony
		//jesli taki ojciec nie istnieje to zwracamy nullptr
		if (ojciec == nullptr)
			return nullptr;
		while (true) {
			if (ojciec->ojciec == nullptr) { //jezeli nie istnieje ojciec obecnie sprawdzanego wezla
				return nullptr;
			}
			else
			{
				if (ojciec->ojciec->lewy_syn == ojciec) //jesli lewym synem obecnie sprawdzanego ojca jest obecnie sprawdzany wezel
					return ojciec->ojciec;
				else {
					ojciec = ojciec->ojciec;
				}
			}
		}
	}
	void traverse_DFS_IN_ORDER_REVERSED_print_in_console(std::string sp, std::string sn, wezel* first_node) {
		/*if (first_node == nullptr)
			return;*/
		std::string cr{ "  " }, cl{ "  " }, cp{ "  " };
		cr[0] = 218; cr[1] = 196;
		cl[0] = 192; cl[1] = 196;
		cp[0] = 179;
		 /* sp	 – 	tekst do wyœwietlenia w wierszu poœrednim
			sn	 – 	tekst do wyœwietlenia przed wêz³em
			v	 – 	wskazanie bie¿¹cego wêz³a drzewa */
		std::string s(sp); //TODO: dokonczyc funckje (testowanko w main)
		if (sn == cr) {
			s[s.size() - 2] = ' ';
		}
		if (first_node->prawy_syn != nullptr)
			traverse_DFS_IN_ORDER_REVERSED_print_in_console(s+ cp,cr,first_node->prawy_syn);
		s = s.substr(0, s.size() - 2);
		std::cout << s << sn << first_node->get_wartosc() << std::endl;
		s = sp;
		if (sn == cl) {
			s[s.size() - 2] = ' ';
		}

		if (first_node->lewy_syn != nullptr)
			traverse_DFS_IN_ORDER_REVERSED_print_in_console(s+ cp,cl,first_node->lewy_syn);
	}

	void traverse_DFS_PRE_ORDER(wezel* poczatkowy_wezel) {
		if (poczatkowy_wezel->getPoziom() > dlugosc_najdluzszej_sciezki_od_korzenia_do_liscia) {
			dlugosc_najdluzszej_sciezki_od_korzenia_do_liscia = poczatkowy_wezel->getPoziom();
		}
		if (poczatkowy_wezel->lewy_syn == nullptr && poczatkowy_wezel->prawy_syn == nullptr) {
			if (poczatkowy_wezel->getPoziom() < dlugosc_najkrotszej_sciezki_od_korzenia_do_liscia) {
				dlugosc_najkrotszej_sciezki_od_korzenia_do_liscia = poczatkowy_wezel->getPoziom();
			}
		}
		if (poczatkowy_wezel->lewy_syn)
			traverse_DFS_PRE_ORDER(poczatkowy_wezel->lewy_syn);
		if (poczatkowy_wezel->prawy_syn)
			traverse_DFS_PRE_ORDER(poczatkowy_wezel->prawy_syn);
	}
	void traverse_DFS_PRE_ORDER_check_vector(wezel* poczatkowy_wezel) {
		//std::cout << "wezel na poziomie: " << poczatkowy_wezel->getPoziom() << std::endl;
		liczba_wezlow_na_poziomach_vector[poczatkowy_wezel->getPoziom()] += 1;
		if (poczatkowy_wezel->lewy_syn)
			traverse_DFS_PRE_ORDER_check_vector(poczatkowy_wezel->lewy_syn);
		if (poczatkowy_wezel->prawy_syn)
			traverse_DFS_PRE_ORDER_check_vector(poczatkowy_wezel->prawy_syn);
	}
	void traverse_DFS_PRE_ORDER_count_leaves(wezel* poczatkowy_wezel) { 
		if (poczatkowy_wezel != korzen
			&& poczatkowy_wezel->get_lewy_syn() == nullptr
			&& poczatkowy_wezel->get_prawy_syn() == nullptr)
			number_of_leaves += 1;
		if (poczatkowy_wezel->lewy_syn)
			traverse_DFS_PRE_ORDER_count_leaves(poczatkowy_wezel->lewy_syn);
		if (poczatkowy_wezel->prawy_syn)
			traverse_DFS_PRE_ORDER_count_leaves(poczatkowy_wezel->prawy_syn);
	}
	void traverse_DFS_PRE_ORDER_count_nodes_with_one_child(wezel* poczatkowy_wezel) {
		if ((poczatkowy_wezel->get_lewy_syn() == nullptr && poczatkowy_wezel->get_prawy_syn() != nullptr
			|| poczatkowy_wezel->get_lewy_syn() != nullptr && poczatkowy_wezel->get_prawy_syn() == nullptr)) {
			liczba_wezlow_z_tylko_jednym_synem += 1;
		}

		if (poczatkowy_wezel->lewy_syn)
			traverse_DFS_PRE_ORDER_count_nodes_with_one_child(poczatkowy_wezel->lewy_syn);
		if (poczatkowy_wezel->prawy_syn)
			traverse_DFS_PRE_ORDER_count_nodes_with_one_child(poczatkowy_wezel->prawy_syn);
	}
	void traverse_DFS_PRE_ORDER_sum_node_values(wezel* poczatkowy_wezel) {
		suma_wartosci_wszystkich_wezlow += poczatkowy_wezel->get_wartosc();

		if (poczatkowy_wezel->lewy_syn)
			traverse_DFS_PRE_ORDER_sum_node_values(poczatkowy_wezel->lewy_syn);
		if (poczatkowy_wezel->prawy_syn)
			traverse_DFS_PRE_ORDER_sum_node_values(poczatkowy_wezel->prawy_syn);
	}
};

class kopiec {
public:
	std::vector<int> kopiec_vec;
	
	//methods
	void push(int wartosc) {
		kopiec_vec.push_back(wartosc);
		//dopoki rodzic jest mniejszy od dziecka. Zamien rodzica i syna
		int syn_index = kopiec_vec.size() - 1;
		int ojciec_index = (syn_index - 1) / 2;
		while (syn_index > 0 &&
			kopiec_vec[syn_index] > kopiec_vec[ojciec_index]) {
			int temp = kopiec_vec[ojciec_index];
			kopiec_vec[ojciec_index] = kopiec_vec[syn_index];
			kopiec_vec[syn_index] = temp;
			syn_index = ojciec_index;
			ojciec_index = (syn_index - 1) / 2;
		}
	}

	/**
	 usuwa korzen z kopca
	*/
	void pop() {
		if (kopiec_vec.empty())
			return;
		kopiec_vec[0] = kopiec_vec[kopiec_vec.size() - 1];
		kopiec_vec.pop_back();
		
		//znajdz wiekszego z 2 synow i porownaj go z obecnym nodem (rodzicem)
		// jesli dziecko jest wieksze to zamien z rodzicem
		// kontynuuj dopoki kolejne dziecko jest wieksze lub gdy brakuje juz dzieci

		int current_node_index = 0;
		int lewy_syn = 1;
		int prawy_syn = 2;

		while (true) {
			int bigger_syn_index;
			if (lewy_syn < kopiec_vec.size() && prawy_syn < kopiec_vec.size()) { //jesli istnieje lewy syn i prawy syn
				bigger_syn_index = (kopiec_vec[lewy_syn] >= kopiec_vec[prawy_syn]) ? lewy_syn : prawy_syn;
				//std::cout << "porownywanie lewy: " << kopiec_vec[lewy_syn] << ", prawy: " << kopiec_vec[prawy_syn] << std::endl;
			}
			else if (lewy_syn < kopiec_vec.size()) { // jesli lewy istnieje, a prawy nie
				bigger_syn_index = lewy_syn;
				//std::cout << "nie ma prawego" << std::endl;
			}
			else if (prawy_syn < kopiec_vec.size()) { //jesli prawy istnieje, a lewy nie
				bigger_syn_index = prawy_syn;
			}
			else { //nie istnieje zaden syn
				break;
			}
			//std::cout<<"Ojciec: index: " << current_node_index << " -> " << kopiec_vec[current_node_index] << " " << std::endl;
			//std::cout << "wiekszy syn index: " << bigger_syn_index << " -> " << kopiec_vec[bigger_syn_index] << " " << std::endl << std::endl;
			if (kopiec_vec[bigger_syn_index] > kopiec_vec[current_node_index]) {
				int temp_wartosc = kopiec_vec[bigger_syn_index];
				kopiec_vec[bigger_syn_index] = kopiec_vec[current_node_index];
				kopiec_vec[current_node_index] = temp_wartosc;

				current_node_index = bigger_syn_index;
				lewy_syn = 2 * current_node_index + 1;
				prawy_syn = 2 * current_node_index + 2;
			}
			else
			{
				break;
			}
		}

	}

	void print_kopiec_elements() {
		int iter = 0;
		for(int i=0;i<kopiec_vec.size();i++){
		//for (auto& i : kopiec_vec) {
			//std::cout << "iter: " << iter;
			std::cout << kopiec_vec[i] << " ";
			if (i == iter) {
				std::cout << "-- ";
				iter = 2 * iter + 2;
			}

			
		}
		std::cout << std::endl;
	}
	void print_koniec_poziomu(int node_number) {
		for (int i = 0; i <= node_number/2; i++) {
			if (i == 0 && node_number == 0)
				std::cout << "--";
			else if (i != 0 && node_number == 2 * i + 2)
				std::cout << "--";
		}
	}
	void print_pretty_kopiec() {
		
		printBT("", "", 0);
	}
private:
	void printBT(std::string sp, std::string sn, int v) {
		std::string cr{ "  " }, cl{ "  " }, cp{ "  " };
		cr[0] = 218; cr[1] = 196;
		cl[0] = 192; cl[1] = 196;
		cp[0] = 179;

		std::string s;

		int n = kopiec_vec.size();

		if (v < n)
		{
			s = sp;
			if (sn == cr) s[s.length() - 2] = ' ';
			printBT(s + cp, cr, 2 * v + 2);

			s = s.substr(0, sp.length() - 2);

			std::cout << s << sn << kopiec_vec[v] << std::endl;

			s = sp;
			if (sn == cl) s[s.length() - 2] = ' ';
			printBT(s + cp, cl, 2 * v + 1);
		}
	}
};

int main()
{
    std::cout << "Hello World!\n";
	drzewo_binarne drzewo_bin(10);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(5);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(3);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(7);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(6);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(13);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(15);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(11);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(12);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(13);
	drzewo_bin.dodaj_wezel_do_drzewa_binarnego(12);
	std::cout << "Wyswietlanie drzewa binarnego PRE_ORDER" << std::endl;
	drzewo_bin.print_drzewo_binarne_DFS_PRE_ORDER(drzewo_bin.getKorzen());
	std::cout<<std::endl;
	std::cout << "Wyswietlanie drzewa binarnego IN_ORDER" << std::endl;
	drzewo_bin.print_drzewo_binarne_DFS_IN_ORDER(drzewo_bin.getKorzen());
	std::cout << std::endl;
	std::cout << "Wyswietlanie drzewa binarnego POST_ORDER" << std::endl;
	drzewo_bin.print_drzewo_binarne_DFS_POST_ORDER(drzewo_bin.getKorzen());
	std::cout << std::endl;
	std::cout << "Wyswietlanie drzewa binarnego zgodnie z poziomami (BFS)" << std::endl;
	drzewo_bin.print_tree_BFS();
	std::cout << std::endl;
	std::cout << "Wyswietlanie drzewa binarnego PRE_ORDER z poziomami" << std::endl;
	drzewo_bin.print_drzewo_binarne_DFS_PRE_ORDER_Z_LEWELAMI(drzewo_bin.getKorzen());

	std::cout << std::endl << "Najdluzsza sciezka od korzenia do liscia: " << drzewo_bin.get_dlugosc_najdluzszej_sciezki_od_korzenia_do_liscia() << std::endl;
	std::cout << "Najkrotsz sciezka od korzenia do liscia: " << drzewo_bin.get_dlugosc_najkrotszej_sciezki_od_korzenia_do_liscia() << std::endl;

	std::cout << "Liczba wezlow na kazdym poziomie: ";
	drzewo_bin.get_Liczba_wezlow_na_kazdym_poziomie();

	std::cout << "Liczba lisci: " << drzewo_bin.get_number_of_leaves() << std::endl;

	std::cout << "Liczba wezlow z tylko 1 dzieckiem: " << drzewo_bin.get_liczba_wezlow_z_tylko_jednym_synem() << std::endl;

	std::cout << "Suma wszystkich wartosci w wezlach: " << drzewo_bin.get_suma_wartosci_wszystkich_wezlow() << std::endl;

	drzewo_bin.print_binary_tree_in_console();
	std::cout << "_________________" << std::endl <<"TERAZ KOPCE" << std::endl;
	//----
	//KOPIEC
	kopiec k;
	k.push(12);

	k.push(11);
	k.push(9);

	k.push(8);
	k.push(10);
	k.push(6);
	k.push(3);

	k.push(6);
	k.push(7);
	k.push(9);
	k.push(3);
	k.push(5);
	k.push(4);
	k.push(26);
	k.print_pretty_kopiec();

	k.pop();
	k.print_pretty_kopiec();

	k.pop();
	k.print_pretty_kopiec();
	//-------------
	std::cout << "_______________" << std::endl << "TERAZ BINARY SEARCH" << std::endl;
	auto found_node = drzewo_bin.search_value_BST(drzewo_bin.getKorzen(), 111);
	if (found_node) {
		std::cout << "Znaleziono: " << found_node->get_wartosc() <<
			" na poziomie: " << found_node->getPoziom() << std::endl;
	}
	else {
		std::cout << "nie znaleziono wezla o tej wezla" << std::endl;
	}
	auto found_min_node = drzewo_bin.search_min_value_node_BST(drzewo_bin.getKorzen());
	if (found_min_node) {
		std::cout << "Najmniejsza wartosc to: " << found_min_node->get_wartosc() <<
			" na poziomie: " << found_min_node->getPoziom() << std::endl;
	}
	else {
		std::cout << "nie ma minimalnego wezla" << std::endl;
	}

	auto found_max_node = drzewo_bin.search_max_value_node_BST(drzewo_bin.getKorzen());
	if (found_max_node) {
		std::cout << "Nawieksza wartosc to: " << found_max_node->get_wartosc() <<
			" na poziomie: " << found_max_node->getPoziom() << std::endl;
	}
	else {
		std::cout << "nie ma minimalnego wezla" << std::endl;
	}
	std::cout << std::endl << "Znajdowanie nastepnikow w binary seach tree __________" << std::endl;
	//Znajdowanie nastepnikow:
	wezel* wezel_wartosc_10 = drzewo_bin.search_value_BST(drzewo_bin.getKorzen(), 10);
	std::cout << "Korzen o wartosci: " << wezel_wartosc_10->get_wartosc() << std::endl;

	wezel* nastepnik_wezla_10 = drzewo_bin.find_successor_BST(wezel_wartosc_10);
	std::cout << "Nastepnikiem wezla o wartosci: " << wezel_wartosc_10->get_wartosc() << " jest wezel o wartosci: "<<nastepnik_wezla_10->get_wartosc()<< std::endl;
	std::cout<<std::endl;
	wezel* wezel_wartosc_7 = drzewo_bin.search_value_BST(drzewo_bin.getKorzen(), 7);
	std::cout << "Korzen o wartosci: " << wezel_wartosc_7->get_wartosc() << std::endl;

	wezel* nastepnik_wezla_7 = drzewo_bin.find_successor_BST(wezel_wartosc_7);
	std::cout << "Nastepnikiem wezla o wartosci: " << wezel_wartosc_7->get_wartosc() << " jest wezel o wartosci: " << nastepnik_wezla_7->get_wartosc() << std::endl;
	if (drzewo_bin.find_successor_BST(drzewo_bin.search_value_BST(drzewo_bin.getKorzen(),15)) == nullptr) {
		std::cout << "Wezel o wartosci 15 nie ma nastepnika" << std::endl;
	}

	//Znajdowanie poprzednikow
	std::cout << std::endl << "Znajdowanie poprzednikow w binary seach tree __________" << std::endl;
	wezel* wezel_wartosc_11 = drzewo_bin.search_value_BST(drzewo_bin.getKorzen(), 11);
	

	wezel* poprzednich_wezla_11 = drzewo_bin.find_predecessor_BST(wezel_wartosc_11);
	std::cout << "Poprzednikiem wezla o wartosci: " << wezel_wartosc_11->get_wartosc() << " jest wezel o wartosci: " << poprzednich_wezla_11->get_wartosc() << std::endl;

	wezel* wezel_wartosc_3 = drzewo_bin.search_value_BST(drzewo_bin.getKorzen(), 3);
	wezel* poprzednich_wezla_3 = drzewo_bin.find_predecessor_BST(wezel_wartosc_3);
	if (poprzednich_wezla_3 == nullptr) {
		std::cout << "wezel " << wezel_wartosc_3->get_wartosc() << " nie ma poprzednika" << std::endl;
	}
	
	//usuwanie wezlow
	std::cout << std::endl << "_________________" << std::endl << "Usuwanie wezlow" << std::endl;
	std::cout << "BST przed usuwaniem:" << std::endl;
	drzewo_binarne drzewo_BST_1(5);//                   
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(10);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(9);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(12);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(11);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(15);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(3);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(14);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(2);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(1);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(6);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(13);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(4);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(8);
	drzewo_BST_1.dodaj_wezel_do_drzewa_binarnego(7);
	drzewo_BST_1.print_binary_tree_in_console();

	drzewo_BST_1.usuwanie_wezla_z_drzewa_BST(13);
	std::cout << "Wyglad drzewa BST po usuniecia wezla 13 to: " << std::endl;
	drzewo_BST_1.usuwanie_wezla_z_drzewa_BST(15);
	std::cout << "Wyglad drzewa BST po usuniecia wezla 15 to: " << std::endl;
	drzewo_BST_1.print_binary_tree_in_console();
	//std::cout << static_cast<void*>(nullptr);
}


//class c_abstract {
//	virtual void funkcja() = 0;
//};
//
//class a : public c_abstract {
//	void funkcja() {
//		std::cout << "aaa" << std::endl;
//	}
//};
//
//class b : public c_abstract {
//	void funckja() {
//		//......//
//		// html -> wyslwiel" b"
//	}
//};
//
//c_abstract * pisac_konsoli = new a[10];
//#include <exception>
//
//class moj_wyjatek_przelewu : public std::exception {
//	const char* what() {
//		return "zla wartosc w polu wartosc przelewu";
//	}
//};
//
//class poza_tablica : pu
//
