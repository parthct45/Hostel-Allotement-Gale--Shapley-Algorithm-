#include<stdio.h>
#include<stdlib.h>
//#include"graph.h" 


struct prefArray{
	int *arr ;
}; 
struct prefMatrix{
	struct prefArray *prefArr; 
	int size ;
};

int wPrefersm1Overm(struct prefMatrix *matrix , int w , int m , int m1){
	for(int i = 0 ; i<(matrix->size)/2 ; i++){
	    if(matrix->prefArr[w].arr[i] == m1){
	    	return 1 ;
		}
		if(matrix->prefArr[w].arr[i] == m){
			return 0 ;
		}
	}
}

struct Graph * galeShapley(struct prefMatrix *matrix , int N){
	struct Graph *result = createGraph(2*N) ;
	int freeCount = N ;
	
	while(freeCount>0){
		int m ;
		for( m = 0 ; m<N ; m++){
			if(result->array[m].head == NULL) break ; 
		} 
		for(int i =0 ; i<N  ; i++){
			int w = matrix->prefArr[m].arr[i] ;
			if(result->array[w].head == NULL){
				addEdge(result,w,m) ;
				freeCount-- ;
                break ;
			} 
			else{
				int m1 = result->array[w].head->vertex ;
				if(wPrefersm1Overm(matrix,w,m,m1) == 0){
					deleteEdge(result,w,m1) ;
					addEdge(result,w,m) ; 
					break ; 
				}
				
			}
		} 
		
	} 
//    printGraph(result);
	return result;
} 


