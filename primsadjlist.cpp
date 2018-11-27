#include<stdio.h>
#include<stdlib.h>

//struture for node
struct node
{
	int destination;
	int weight;
	struct node* next;
};

//structure for list for each vertex
struct adj_list
{
	struct node* head; //pointer to the head node
};

//structure for the graph
struct graph
{
	int size;
	struct adj_list* list;
};

struct graph* create_graph(int v)
{
	//allocating memory for new graph
	struct graph* new_graph = (struct graph*)malloc(sizeof(struct graph));
	new_graph->size = v;
	
	//allocating memory for each adj list
	new_graph->list = (struct adj_list*)malloc(v*sizeof(struct adj_list));
		
	//making the head nodes of the list null
	for(int i =0; i < v; i++)
		new_graph->list[i].head = NULL;
		
	return new_graph;
}

struct node* create_node(int destination, int weight)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->destination = destination;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}


void add_edge(struct graph* new_graph, int source, int destination, int weight)
{
	//source to destination
	struct node* new_node = create_node(destination, weight);
	new_node->next = new_graph->list[source].head;
	new_graph->list[source].head = new_node;
	
	//destination to source
	new_node = create_node(source, weight);
	new_node->next = new_graph->list[destination].head;
	new_graph->list[destination].head = new_node;
	
	//new nodes are added at the start of the list
}

void display_graph(struct graph* new_graph)
{
	for(int i = 0; i<new_graph->size ; i++)
	{
		struct node* temp = new_graph->list[i].head;
		printf("%d->",i);
		while(temp != NULL)
		{
			printf("%d->", temp->destination);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

struct minHeapNode
{
	int v;
	int key;
};

struct minHeap
{
	int capacity;
	int size;
	struct minHeapNode** array;
	int* pos; //needed to keep track of the position of the swapped elements in the minHeap
};

struct minHeapNode* createMinHeapNode(int v, int key)
{
	struct minHeapNode* newNode = (struct minHeapNode*)malloc(sizeof(struct minHeapNode));
	newNode->key = key;
	newNode->v = v;
	return newNode;
}
struct minHeap* createMinHeap(int capacity)
{
	struct minHeap* newHeap = (struct minHeap*)malloc(sizeof(minHeap));
	newHeap->capacity = capacity;
	newHeap->size = 0;
	newHeap->pos = (int*)malloc(capacity*sizeof(int));
	newHeap->array = (struct minHeapNode**)malloc(capacity*sizeof(struct minHeapNode*));
	return newHeap;
}

void swapMinHeapNode(struct minHeapNode** a, struct minHeapNode** b)
{
    struct minHeapNode* t = *a;
    *a = *b;
    *b = t;
}


void minHeapify(struct minHeap* newHeap, int i)
{
	int smallest, left, right;
    smallest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
 
    if (left < newHeap->size && newHeap->array[left]->key < newHeap->array[smallest]->key)
        smallest = left;
 
    if (right < newHeap->size && newHeap->array[right]->key < newHeap->array[smallest]->key)
        smallest = right;
 
    if (smallest != i) {
        
		 
        // Swap positions
        newHeap->pos[newHeap->array[smallest]->v] = i;
        newHeap->pos[newHeap->array[i]->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&newHeap->array[smallest], &newHeap->array[i]);
        minHeapify(newHeap, smallest);
    }
	
}

int isEmpty(struct minHeap* newHeap)
{
    return newHeap->size == 0;
}


struct minHeapNode* extractMin(struct minHeap* newHeap)
{
	if(isEmpty(newHeap))
		return NULL;
	
	struct minHeapNode* root = newHeap->array[0];
	struct minHeapNode* last = newHeap->array[newHeap->size - 1];
	
	newHeap->array[0] = last;
	
	newHeap->pos[root->v] = newHeap->size - 1;
	newHeap->pos[last->v] = 0;
	
	--newHeap->size;
	minHeapify(newHeap,0);
	
	return root;
}

void decreaseKey(struct minHeap* newHeap, int v, int key)
{
    int i = newHeap->pos[v];
 
    newHeap->array[i]->key = key;
 
    while (i && newHeap->array[i]->key < newHeap->array[(i - 1) / 2]->key) {
        newHeap->pos[newHeap->array[i]->v] = (i - 1) / 2;
        newHeap->pos[newHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&newHeap->array[i], &newHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(int v, struct minHeap* newHeap)
{
    if (newHeap->pos[v] < newHeap->size)
        return true;
    return false;
}

void printArr(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
        printf("%d - %d\n", arr[i], i);
}


void prims(struct graph* Graph)
{
	int V = Graph->size;
	int parent[V];
	int key[V];
	
	struct minHeap* newHeap = createMinHeap(V);
	
	key[0] = 0;
	newHeap->pos[0] = 0;
	newHeap->array[0] = createMinHeapNode(0,key[0]);
	
	for(int i = 1; i<V; i++)
	{
		parent[i] = -1;
		key[i] = INT_MAX;
		newHeap->array[i] = createMinHeapNode(i, key[i]);
		newHeap->pos[i] = i;
	}
	
	newHeap->size = V;
	
	while(!isEmpty(newHeap))
	{
		struct minHeapNode* minNode = extractMin(newHeap);
		int u = minNode->v;
		
		struct node* Crawl = Graph->list[u].head;
		
		while(Crawl != NULL)
		{
			int v = Crawl->destination;
			
			if(isInMinHeap(v, newHeap) && Crawl->weight < key[v])
			{
				key[v] = Crawl->weight;
				parent[v] = u;
				decreaseKey(newHeap,v,key[v]);
			}
			Crawl = Crawl->next;
		} 
	}
	
	printArr(parent, V);
	  
}

int main()
{
    // Let us create the graph given in above fugure
    int V = 9;
    struct graph* graph1 = create_graph(V);
    add_edge(graph1, 0, 1, 4);
    add_edge(graph1, 0, 7, 8);
    add_edge(graph1, 1, 2, 8);
    add_edge(graph1, 1, 7, 11);
    add_edge(graph1, 2, 3, 7);
    add_edge(graph1, 2, 8, 2);
    add_edge(graph1, 2, 5, 4);
    add_edge(graph1, 3, 4, 9);
    add_edge(graph1, 3, 5, 14);
    add_edge(graph1, 4, 5, 10);
    add_edge(graph1, 5, 6, 2);
    add_edge(graph1, 6, 7, 1);
    add_edge(graph1, 6, 8, 6);
    add_edge(graph1, 7, 8, 7);
 	display_graph(graph1);
	 //prims(graph1);
 
    return 0;
}

