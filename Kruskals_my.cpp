#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Edge
{
	int src,dest,weight;
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

int comp(const void* a, const void* b)
{
	int w1 = ((struct Edge*)a)->weight;
	int w2 = ((struct Edge*)b)->weight;
	return w1 > w2;
}

void Kruskals(struct Graph* graph)
{
	int V = graph->V;
	struct Edge result[V-1];
	int e = 0,i = 0;
	qsort(graph->edge ,graph->E, sizeof(graph->edge[0]), comp);
	
	int* parent = (int*)malloc(graph->V*sizeof(int));
	memset(parent, -1, sizeof(int)*graph->V);
	
	while(e < V-1)
	{
		int x = find(parent,graph->edge[i].src);
		int y = find(parent,graph->edge[i].dest);
		
		if(x != y)
		{
			result[e] = graph->edge[i];
			Union(parent,x,y);
			e++;
		}
		i++; 
	}
	
    for (i = 0; i < e; i++)
        printf("%d - %d  (%d)\n", result[i].src,result[i].dest,result[i].weight);
    return;
}


int main()
{
	 int V = 4; 
    int E = 5;  
    struct Graph* graph = create_graph(V, E);
 
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;
 
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;
 
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;
 
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;
 
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;
 
 	Kruskals(graph);

    return 0;
}
