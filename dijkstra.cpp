#include <stdio.h>
#include <limits.h>
 
#define V 9

void printPath(int parent[], int j)
{
    if (parent[j] == - 1)
		return;
         
    printPath(parent, parent[j]); 
    printf("%d->", parent[j]);
}

int min_dist(int dist[], bool mstSet[]){
	int min = INT_MAX,min_index;
	for(int i = 0 ; i<V;i++)
		if(mstSet[i] == false && dist[i]<min)
			min = dist[i], min_index = i;
			
	return min_index;
}

int printMST(bool mstSet[], int dist[],int parent[],int src)
{
   for (int i = 0; i < V; i++){
	   		if(i != src){
			printf("\n %d - %d (%d) : ",src, i, dist[i]);
			printPath(parent, i);
			printf("%d",i);
		}
	}
}

void dijkstra(int graph[V][V], int src){
    bool mstSet[V];
    int dist[V];
    int parent[V];
    
	for(int i = 0; i < V; i++)
    	dist[i] = INT_MAX, mstSet[i]=false,parent[i] = -1;
    
	dist[src] = 0;
    
    int current_u = src;
	mstSet[current_u] = true;
	
	for(int count = 0; count<V-1 ; count++){
    	for(int v = 0; v < V; v++){
    		if(graph[current_u][v] && mstSet[v] == false && dist[current_u] != INT_MAX && (dist[current_u] + graph[current_u][v]) < dist[v]){
    			dist[v] = graph[current_u][v] + dist[current_u];
    			parent[v] = current_u;
	    	}
    	}
		current_u = min_dist(dist, mstSet);
		mstSet[current_u] = true;
	}
	
	printMST(mstSet, dist, parent, src);
}
int main(){
int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                   {4, 0, 8, 0, 0, 0, 0, 11, 0},
                    {0, 8, 0, 7, 0, 4, 0, 0, 2},
                    {0, 0, 7, 0, 9, 14, 0, 0, 0},
                    {0, 0, 0, 9, 0, 10, 0, 0, 0},
                    {0, 0, 4, 0, 10, 0, 2, 0, 0},
                    {0, 0, 0, 14, 0, 2, 0, 1, 6},
                    {8, 11, 0, 0, 0, 0, 1, 0, 7},
                    {0, 0, 2, 0, 0, 0, 6, 7, 0}
                    };
  
    dijkstra(graph, 1);
    return 0;
}
