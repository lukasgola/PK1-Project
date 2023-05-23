#include "functions.h"
#include "structures.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;


bool check_parameters(string & source, string & destination, int argc, char** argv){
	if(argc == 1){
		cout << "Nie podano parametrow" << endl;
		cout << "-i sciezka pliku wejsciowego" << endl;
		cout << "-o sciezka pliku wyjsciowego" << endl;
		
		return false;
	}
	else if(argc > 1){
		if(argc == 2 && strcmp(argv[1], "-h") == 0){
			cout << "-i sciezka pliku wejsciowego" << endl;
			cout << "-o sciezka pliku wyjsciowego" << endl;
			
			return false;
		}
		else if(argc == 5 && strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0){
			source = argv[2];
			destination = argv[4];
			
			return true;
		}
		else if(argc == 5 && strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-i") == 0){
			source = argv[4];
			destination = argv[2];
			
			return true;
		}
		else{
			cout << "Bledne parametry" << endl;
			cout << "-i sciezka pliku wejsciowego" << endl;
			cout << "-o sciezka pliku wyjsciowego" << endl;
			
			return false;
		}
	}
}


bool check_vertex(vector <int> & vertex, int number){
    bool isInArray = false;
    for(int i=0; i<vertex.size();i++){
        if(number == vertex[i]) return true;
    }
    return false;
}

void load_graph(string source, vector <int> & data, vector <int> & vertex){

    int number;

    ifstream plik;
    plik.open(source.c_str());
    
    if(!plik.good()){
    	cout << "Nie ma takiego pliku!" << endl;
	}
	else{
		while(!plik.eof()){
	        plik >> number;
	        data.push_back(number);
	        if(!check_vertex(vertex, number)) vertex.push_back(number);
	    }
	    plik.close();
	}
}

vector <vector <int> > find_edges(vector <int> & data){

    bool test;
    vector <vector<int> > edges;
    vector <int> edge;
    edge.push_back(data[0]);
    edge.push_back(data[1]);
    edges.push_back(edge);

    for(int i=0;i<data.size(); i=i+2){
        int m = data[i];
        int n = data[i+1];
        test = false;
        for(int j=0;j<edges.size();j++){
            if(edges[j][0] == m){
                if(edges[j][1] == n){
                    test = true;
                    break;
                }
            }
            else if(edges[j][1] == m){
                if(edges[j][0] == n){
                    test = true;
                    break;
                }
            }
        }
        if(!test){
            edge[0]=m;
            edge[1]=n;
            edges.push_back(edge);
        }
        
	}	
    return edges;
}

void quick_sort(vector <int> & tab, int left, int right){
	if(right <= left) return;
	
	int i = left;
    int j = right;
    int x = tab[( left + right ) / 2 ];
    do
    {
        while( tab[ i ] < x )
             i++;
       
        while( tab[ j ] > x )
             j--;
       
        if( i <= j )
        {
            swap( tab[ i ], tab[ j ] );
           
            i++;
            j--;
        }
    } while( i <= j );
   
    if( left < j ) quick_sort( tab, left, j );
   
    if( right > i ) quick_sort( tab, i, right );
}

vector <vector<int> > create_matrix(vector <vector<int> > & edges, int n, int m){
    vector <vector<int> > adj_matrix(n, vector<int>(n));

    for(int i = 0; i < n; i++ )
        for(int j = 0; j < n; j++ ) adj_matrix[i][j] = 0;

    for(int i = 0; i < m; i++ )
    {
        int v1 = edges[i][0];
        int v2 = edges[i][1];
        adj_matrix[v1][v2] = 1;
        adj_matrix[v2][v1] = 1;
    }
    return adj_matrix;
}

vector <Vertex> vertex_Arr(int n){
	vector <Vertex> tab(n);
	for (int i = 0; i < n; i++) {
		tab[i].number = i;
		tab[i].visited = false;
		tab[i].type = -1;
	}
	return tab;
}

bool isBipartite(vector <vector<int> > adj_matrix, int n, int start, vector <Vertex>& tab) {
	tab[start].visited = true;
	tab[start].type = 0;
	queue<int> q;
	q.push(start);
	while (q.size() != 0) {
		int u = q.front();
		q.pop();
		int act_type = tab[u].type;
		for (int i = 0; i < n; i++) {
		  if (adj_matrix[i][u] == 0) {
		    continue;
		  }
		  if (tab[i].visited && tab[i].type == act_type) {
		    return false;
		  } else if (!tab[i].visited) {
		    tab[i].visited = true;
		    tab[i].type = 1 - act_type;
		    q.push(i);
		  }
		}
	}
	return true;
}

void showAnswer(string destination, bool result, vector <vector<int> > org_edges, vector <Vertex>& vertex_struct_Arr){

    ofstream plik;
    plik.open(destination.c_str());

	if(result){
		cout << "Graf jest dwudzielny" << endl;
		plik << "Graf jest dwudzielny" << endl;
	}
	else{
		cout << "Graf nie jest dwudzielny" << endl;
		plik << "Graf nie jest dwudzielny" << endl;
	}
	
	for(int i=0;i<org_edges.size();i++){
    	cout << org_edges[i][0] << " " << org_edges[i][1] << endl;
    	plik << org_edges[i][0] << " " << org_edges[i][1] << endl;
	}
	
	if(result){
		cout << "Grupa A: ";
		plik << "Grupa A: ";
	    for(int i=0;i<vertex_struct_Arr.size();i++){
	    	if(vertex_struct_Arr[i].type == 0){
	    		cout << vertex_struct_Arr[i].number << " ";
	    		plik << vertex_struct_Arr[i].number << " ";
			}
		}
		cout << endl;
		plik << endl;
		cout << "Grupa B: ";
		plik << "Grupa B: ";
	    for(int i=0;i<vertex_struct_Arr.size();i++){
	    	if(vertex_struct_Arr[i].type == 1){
	    		cout << vertex_struct_Arr[i].number << " ";
	    		plik << vertex_struct_Arr[i].number << " ";
			}
		}
	}
    
    plik.close();
}
