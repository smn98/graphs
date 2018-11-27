#include <stdio.h>
#include <limits.h>
 
#define V 4
 
int min_key(int key[], bool mstSet[]){
	int min = INT_MAX,min_index;
	for(int i = 0 ; i<V;i++)
		if(mstSet[i] == false && key[i]<min)
			min = key[i], min_index = i;
			
	return min_index;
}

int printMST(int parent[],bool mstSet[], int key[])
{
   printf("Edge   Weight\n");
   for (int i = 1; i < V; i++)
      printf("%d - %d    %d (%d) \n", parent[i], i, key[i], mstSet[i]);
}

void primMST(int graph[V][V]){
    int parent[V];
    bool mstSet[V];
    int key[V];
    
	for(int i = 0; i < V; i++)
    	key[i] = INT_MAX, mstSet[i]=false;
    
	key[0] = 0;
    parent[0] = -1;

    int current_u = 0;
	mstSet[0] = true;

    
	for(int count = 0; count<V-1 ; count++){
    	for(int v = 0; v < V; v++)
    		if(graph[current_u][v] && mstSet[v]==false && graph[current_u][v] < key[v])
    			parent[v] = current_u, key[v] = graph[current_u][v];
    
		current_u = min_key(key, mstSet);
		
		mstSet[current_u] = true;
	}
	
	printMST(parent, mstSet, key);
}
int main(){
int graph[V][V] = {{0, 3, 0, 1},
                      {3, 0, 4, 5},
                      {0, 4, 0, 6},
                      {1, 5, 6, 0},
                     };
    primMST(graph);
    return 0;
}
