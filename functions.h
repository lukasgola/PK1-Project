#include "structures.h"

#ifndef functions_h
#define functions_h

#include <iostream>
#include <vector>

using namespace std;

/// Funkcja sprawdza poprawnoœæ wprowadzonych parametrów
/// @param source Nazwa pliku wejsciowego
/// @param destination Sciezka pliku wyjsciowego
/// @param argc Liczba parametrow
/// @param argv Tablica parametrow
/// @returns Zwraca true jesli nie wystapil zaden blad przy wprowadzaniu parametrow
bool check_parameters(string & source, string & destination, int argc, char** argv);

/// Funkcja sprawdza czy dany wierzcholek zostal juz wczesniej dodany do tablicy wszystkich wierzcholkow
/// @param vertex Vector zawierajacy numery wierzcholkow
/// @param number Numer wierzcholka do sprawdzenia
/// @returns Zwraca true jesli wiercholek juz jest w vectorze i false jesli nie
bool check_vertex(vector <int> & vertex, int number);

/// Funkcja odczutyje dane z pliku i zapisuje do vectora
/// @param source nazwa pliku wejsciowego
/// @param data Vector do ktorego zapisywane sa dane z pliku
/// @param vertex Vector z wszystkimi wierzcholkami
void load_graph(string source, vector <int> & data, vector <int> & vertex);

/// Funkcja przeszukuje dane pobrane z pliku w celu znalezienia wszystkich krawedzi (bez powtorzen)
/// @param data Vector z danymi z pliku
/// @returns Zwraca tablice vectorow z wszystkimi krawedziami (bez powtorzen)
vector <vector <int> > find_edges(vector <int> & data);

/// Funkcja sortuje wiercholki rosnaco
/// @param tab Vector nieposortowanych wierzcholkow
/// @param left Indeks pierwszego elementu
/// @params right Indeks ostatniego elementu
void quick_sort(vector <int> & tab, int left, int right);

/// Funkcja tworzy macierz sasiedztwa na podstawie tablicy vectorow krawedzi
/// @param edges Tablica vectorow krawedzi
/// @param n Liczba wierzcholkow
/// @param m Liczba krawedzi
/// @returns Zwraca macierz sasiedztwa w postaci tablicy vectorow
vector <vector<int> > create_matrix(vector <vector<int> > & edges, int n, int m);

/// Funkcja tworzy vector struktur
/// @param n Liczba wiercho³kow
vector <Vertex> vertex_Arr(int n);

/// Funkcja sprawdza czy graf jest dwudzielny za pomoca algorytmu BFS
/// @param adj_matrix Macierz sasiedztwa wierzcholkow
/// @param n Liczba wierzcholkow
/// @param start Wierzcholek poczatkowy
/// @returns Zwraca true jesli graf jest dwudzielny i false jesli nie
bool isBipartite(vector <vector<int> > adj_matrix, int n, int start, vector <Vertex>& tab);

/// Funkcja wyswietla wynik na ekrean i zapisuje do pliku
/// @param destination Sciezka pliku wyjsciowego
/// @param result Zmienna zawiera informacje czy graf jest dwudzielny
/// @param org_edges 
void showAnswer(string destination, bool result, vector <vector<int> > org_edges, vector <Vertex>& vertex_struct_Arr);

#endif
