#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Edge
{
	int src,dest;
};

struct Graph
{
	int V, E;
	struct Edge* edge;	
};

struct Graph* create_graph(int v, int e)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = v;
	graph->E = e;
	graph->edge = (struct Edge*)malloc(e*sizeof(struct Edge));
	return graph;
}

int find(int parent[], int node)
{
	if(parent[node] == -1)
		return node;
	return find(parent,parent[node]);	
}

void Union(int parent[], int x, int y)
{
	int xset = find(parent, x);
	int yset = find(parent, y);
	parent[yset] = xset;
}

int isCycle(struct Graph* graph)
{
	int* parent = (int*)malloc(graph->V*sizeof(int));
	memset(parent, -1, sizeof(int)*graph->V);
	
	for(int i = 0; i<graph->E ; i++)
	{
		int x = find(parent,graph->edge[i].src);
		int y = find(parent,graph->edge[i].dest);
		
		if(x==y)
			return 1;
		else
			Union(parent,x,y);
	}
	for(int i = 0; i<graph->V ;i++)
		printf("%d %d \n",parent[i],i);
	return 0;
}

int main()
{
	 int V = 3, E = 2;
    struct Graph* graph = create_graph(V, E);
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;
    
 
    if (isCycle(graph))
        printf( "graph contains cycle" );
    else
        printf( "graph doesn't contain cycle" );
 
    return 0;
}
