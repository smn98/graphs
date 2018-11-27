#include<stdlib.h>
#include<stdio.h>

//---------------------------------------graph functions and properties-------------------------------------------------------
struct node{
	int vertex;
	struct node* next;
};

struct graph{
	int V;
	struct node** adjList;
	int* visited;
};

struct node* createNode(int v){
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

struct graph* createGraph(int V){
	struct graph* Graph = (struct graph*)malloc(sizeof(struct graph));
	Graph->V = V;
	Graph->adjList = (struct node**)malloc(V*sizeof(struct node*));
	Graph->visited = (int *)malloc(V*sizeof(int));
	
	for(int i=0; i<V; i++){
		Graph->adjList[i] = NULL;
		Graph->visited[i] = false;
	}
	return Graph;
}

void addEdge(struct graph* Graph,int src, int dst){
	//src to dst
	struct node* newNode = createNode(dst);
	newNode->next = Graph->adjList[src];
	Graph->adjList[src] = newNode;
	//dst to src
	newNode = createNode(src);
	newNode->next = Graph->adjList[dst];
	Graph->adjList[dst] = newNode;
}

void printGraph(struct graph* Graph){
	for(int i=0; i<Graph->V;i++){
		struct node* temp = Graph->adjList[i];
		printf("%d->",i);
		while(temp){
			printf("%d -> ",temp->vertex);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

//-------------------------------------------stack,queue data structure-------------------------------------------------------------
struct Node{
	int key;
	struct Node* next;
};

struct Queue{
	struct Node *front,*rear;
};

struct Stack{
	struct Node *top;
};

struct Node* newNode(int key){
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->key = key;
	newnode->next = NULL;
	return newnode;
}

struct Queue* createQueue(){
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->front = queue->rear = NULL;
	return queue;
}

void enQueue(struct Queue* queue,int key){
	struct Node* temp = newNode(key);
	
	if(!queue->rear){
		queue->front = queue->rear = temp;
		return;
	}
	
	queue->rear->next = temp;
	queue->rear = temp;
}

struct Node* deQueue(struct Queue* queue){
	if(!queue->front){
		return NULL;
	}
	
	struct Node* temp = queue->front;
	queue->front = queue->front->next;
	
	if(!queue->front)
		queue->rear = NULL;
	
	return temp;
}

int qIsEmpty(struct Queue* queue){
	if(!queue->front)
		return true;
	return false;
}

int sIsEmpty(struct Stack* stack){
	if(!stack->top)
		return true;
	return false;
}

struct Stack* createStack(){
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->top = NULL;
	return stack;
}

void push(struct Stack* stack, int key){
	struct Node* temp = newNode(key);
	
	if(!stack->top){
		stack->top = temp;
		return;
	}
	
	temp->next = stack->top;
	stack->top = temp;
}

struct Node* pop(struct Stack* stack){
	if(!stack->top){
		return NULL;
	}
	
	struct Node* temp = stack->top;
	stack->top = stack->top->next;

	return temp;
}

//--------------------------------------------------bfs-----------------------------------------------------------------------

void bfs(struct graph* Graph, int strt){
	for(int i=0; i<Graph->V; i++)
		Graph->visited[i] = false;
	
	struct Queue* queue = createQueue();
	
	enQueue(queue,strt);
	
	Graph->visited[strt] = true;
	printf("BFS:\n");
	while(!qIsEmpty(queue)){
		struct Node* current = deQueue(queue);
		printf("%d->",current->key);
		
		struct node* adjacent = Graph->adjList[current->key];
		 
		//printf("adjacent vertex: %d\n", adjacent->vertex);
		while(adjacent){
			int adjacentVertex = adjacent->vertex;
			
			if(!Graph->visited[adjacentVertex]){
				enQueue(queue,adjacentVertex);
				Graph->visited[adjacentVertex] = 1;
				
			}
			
			adjacent = adjacent->next;
		}
	}
	printf("null");
}

//-------------------------------------------------------dfs-------------------------------------------------------------

void dfs(struct graph* Graph, int strt){
	
	for(int i=0; i<Graph->V; i++)
		Graph->visited[i] = false;
		
	struct Stack* stack = createStack();
	
	push(stack,strt);
	
	Graph->visited[strt] = true;
	printf("\nDFS:\n");
	while(!sIsEmpty(stack)){
		struct Node* current = pop(stack);
		printf("%d->",current->key);
		
		struct node* adjacent = Graph->adjList[current->key];
		 
		while(adjacent){
			int adjacentVertex = adjacent->vertex;
			
			if(!Graph->visited[adjacentVertex]){
				push(stack,adjacentVertex);
				Graph->visited[adjacentVertex] = 1;
			}
			adjacent = adjacent->next;
		}
	}
	printf("null");
}

int main()
{
    struct graph* Graph = createGraph(6);
    addEdge(Graph, 0, 1);
    addEdge(Graph, 0, 2);
    addEdge(Graph, 1, 2);
    addEdge(Graph, 1, 4);
    addEdge(Graph, 1, 3);
    addEdge(Graph, 2, 4);
    addEdge(Graph, 3, 4);
 
 	printGraph(Graph);

 	bfs(Graph,0);

 	dfs(Graph,0);
 
	return 0;
}
