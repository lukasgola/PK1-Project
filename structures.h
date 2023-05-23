#ifndef structures_h
#define structures_h


/// Struktura wykorzystywana do "kolorowania" wierzcholkow w algorytmie BFS
struct Vertex {
	int number; ///< Numer wierzcholka
	bool visited; ///< Zmienna przechowujaca informacje czy wierzcholek juz byl "odwiedzony" przez algorytm BFS
	int type; ///< Kolor wierzcholka
};
  
#endif
