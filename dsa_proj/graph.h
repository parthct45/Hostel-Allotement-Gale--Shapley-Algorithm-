#include<stdio.h>
#include<stdlib.h>

struct AdjListNode{
	int vertex ;
	struct AdjListNode *next ;
};

struct AdjList{
	struct AdjListNode *head ;
}; 

struct Graph{
	int V ;
	struct AdjList *array ; 
}; 

// Utility function to create a new adjacent ListNode 

struct AdjListNode* newAdjListNode(int dest){
	
	struct AdjListNode* newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode)) ;
	newNode->vertex = dest ;
	newNode->next = NULL ;
	return newNode ; 
} 

// Utility function that creates a graph of vertices V 

struct Graph* createGraph(int v){
	struct Graph *newGraph = (struct Graph*)malloc(sizeof(struct Graph)) ;
	newGraph->V = v ;
	// creating the adjList as NULL initially 
	newGraph->array = (struct AdjList *)malloc(sizeof(struct AdjList)*v) ;
	
	int i ;
	for(i = 0 ; i<v ; i++){
		newGraph->array[i].head = NULL ;
	} 
	
	return newGraph ; 
	
}

void addEdge(struct Graph* graph , int src , int dest){
	// Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the end or beginning ? 
    struct AdjListNode *temp = NULL ;
    struct AdjListNode *newNode = newAdjListNode(dest) ;
    
    if(graph->array[src].head == NULL){
    	newNode->next = graph->array[src].head ; // actually setting it to NULL itself 
    	graph->array[src].head = newNode ;
    		
	}
	else{
		temp = graph->array[src].head ;
		while(temp->next!=NULL){
			temp = temp->next ;
			
		}
		temp->next = newNode ;
		 
		
	} 
	
	// Since undirected graph A newnode should be added at des list also 
	struct AdjListNode *newNode1 = newAdjListNode(src) ;
	if(graph->array[dest].head == NULL){
		newNode1->next = NULL ;
		graph->array[dest].head = newNode1 ;
	}
	else{
		temp = graph->array[dest].head ;
		while(temp->next!=NULL){
			temp = temp->next ;
		} 
		temp->next = newNode1 ;
	}
	 
} 

void deleteEdge(struct Graph *graph ,int src , int dest){
	struct AdjListNode *temp = NULL ;
	temp = graph->array[src].head ;
	graph->array[src].head = NULL ;
	free(temp) ;
	temp = graph->array[dest].head ;
	graph->array[dest].head = NULL ;
	free(temp) ; 
}


void printGraph(struct Graph* graph){
	int v ;
//	for(v =0 ; v<(graph->V)/2 ; v++){
//		struct AdjListNode *pCrawl = graph->array[v].head ;
//		printf("\n Student: %d ",v); 
//		while(pCrawl){
//			printf("-> Student :%d" , pCrawl->vertex) ;
//			pCrawl = pCrawl->next;
//			
//		} 
//		printf("\n") ;  

   for(v =0 ; v<(graph->V)/2 ; v++){
   	printf("%d -> %d\n",v,graph->array[v].head->vertex) ; 
   }
}
