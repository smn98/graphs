#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#define v 4

void printSol(int dist[][v]){
	printf("The following matrix shows the shortest distances"
            " between every pair of vertices \n"); 
    for (int i = 0; i < v; i++) 
    { 
        for (int j = 0; j < v; j++) 
        { 
            if (dist[i][j] == INT_MAX) 
                printf("%7s", "INF"); 
            else
                printf("%7d", dist[i][j]); 
        } 
        printf("\n"); 
    } 
}

void floydWarshall(int graph[][v]){
	int dist[v][v];
	
	for(int i = 0; i<v; i++)
		for(int j = 0; j<v; j++)
			dist[i][j] = graph[i][j];
			
	for(int k=0; k<v;k++)
		for(int i=0;i<v;i++)
			for(int j=0;j<v;j++)
				if(dist[i][k]!=INT_MAX && dist[k][j]!=INT_MAX && dist[i][k]+dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k]+dist[k][j];
					
	printSol(dist);
			
}

int main() 
{ 
    int graph[v][v] = { {0,   5,  INT_MAX, 10}, 
                        {INT_MAX, 0,   3, INT_MAX}, 
                        {INT_MAX, INT_MAX, 0,   1}, 
                        {INT_MAX, INT_MAX, INT_MAX, 0} 
                      }; 
  
    floydWarshall(graph); 
    return 0; 
}  
