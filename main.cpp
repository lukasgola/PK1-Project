#include "functions.h"
#include "structures.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <utility> 
#include <cstring>

using namespace std;

int main(int argc, char** argv){	

	string source;
	string destination;
	
	bool param = check_parameters(source, destination, argc, argv);
	
	if(param){	
		vector <int> data;
	    vector <int> vertex;
	    vector <vector<int> > edges;
	    vector <vector<int> > org_edges;
	    vector <Vertex> vertex_struct_Arr;
	
	    vector <pair <int,int> > dict;

	    load_graph(source, data,vertex);
	    if(data.size() == 1){
	    	cout << "Plik jest pusty" << endl;
	    	return 0;
		}
	    edges = find_edges(data);
	    org_edges = find_edges(data);
	
	    int n = vertex.size();
	    int m = edges.size();
	    
	    vertex_struct_Arr = vertex_Arr(n);
	
	    quick_sort(vertex, 0, n-1);
	
	    for(int i=0;i<n;i++){
	        pair <int, int> p (i,vertex[i]);
	        dict.push_back(p);
	    }
	    
	
	    for(int i=0;i<m;i++){
	        for(int j=0;j<2;j++){
	            for(int k=0;k<n;k++){
	                if(edges[i][j] == dict[k].second){
	                    edges[i][j] = dict[k].first;
	                    break;
	                }
	            }
	        }
	    }
	
	    vector <vector<int> > adj_matrix = create_matrix(edges, n, m);
	
	    bool result = isBipartite(adj_matrix, n, 0, vertex_struct_Arr);
	    
	    
	    
	    for(int i=0;i<vertex_struct_Arr.size();i++){
	    	for(int j=0;j<n;j++){
	    		if(vertex_struct_Arr[i].number == dict[j].first){
	                    vertex_struct_Arr[i].number = dict[j].second;
	                break;
	        	}
			}      
	    }
	    
	    showAnswer(destination, result, org_edges, vertex_struct_Arr);
	}
}
