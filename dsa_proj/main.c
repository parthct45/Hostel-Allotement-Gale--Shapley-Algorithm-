#include <mysql.h>
#include <stdio.h>
#include <stdlib.h> 
#include "graph.h"
#include "gale_shapley.h"
#include "hashmap.h"
#define N 25 
#include<string.h> 
#include "mergeSort.h" 



void createArray(struct prefMatrix *matrix ,char *S , int i){
    int u = -1 ;
    char *token = strtok(S, " ");
    while (token != NULL) {
        matrix->prefArr[i].arr[++u] = atoi(token);
        token = strtok(NULL, " ");
    }

}



//find higher scorer of 2 roomates
void findMax(struct Graph *roomate,HashMap * map , float * selectedArr){
    int v;
    float mark1=0.0, mark2=0.0;
    for(v=0;v<(roomate->V)/2;v++){
        mark1=getCgpa(map,v);
        mark2=getCgpa(map,roomate->array[v].head->vertex);
        if(mark1>=mark2){
            selectedArr[v]=mark1;
        }
        else{
            selectedArr[v]=mark2;
        }
    }
    mergeSort(selectedArr , 0 , v) ; 
}

//error in mysql
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

//main function
int main()
{ 
    //prefmatrix for roomate selection
    struct prefMatrix *matrixR = (struct prefMatrix *)malloc(sizeof(struct prefMatrix)) ;
    matrixR->size = 2*N ;
    matrixR->prefArr = (struct prefArray*)malloc(sizeof(struct prefArray)*2*N) ;
    for(int i =0 ; i<2*N ; i++){
    matrixR->prefArr[i].arr = (int *)malloc(sizeof(int)*N) ;
    } 
    struct prefMatrix *matrixH = (struct prefMatrix *)malloc(sizeof(struct prefMatrix)) ;
    matrixH->size = 2*N ;
    matrixH->prefArr = (struct prefArray*)malloc(sizeof(struct prefArray)*2*N) ;
    for(int i =0 ; i<2*N ; i++){
    matrixH->prefArr[i].arr = (int *)malloc(sizeof(int)*N) ;
    }


    //hashmap initialisation
   HashMap * map=(HashMap*)malloc(sizeof(HashMap));

//mysql connection
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "123",
          "student", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "SELECT * FROM main"))
  {
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  int i =0 ;

  //create array for roomate selection
  while ((row = mysql_fetch_row(result)))
  {
          char Temp[400];
          strcpy(Temp,row[3]);
          createArray(matrixR,Temp,i) ;
          insert(map,i,atof(row[2]),row[1]);
          i++ ; 

 //     printf("\n");
  }
  //gale shapley for roomate selction
 struct Graph *roomate = galeShapley(matrixR,N) ; 
  //call function to create array of cgpa of selected students
  float *sortedCgpa = (float *)malloc(sizeof(float)*N) ; 
  findMax(roomate , map , sortedCgpa) ;
  int size = N ;
 
 
 //creating prefmatrix for room allotment 
  for(int l =0 ; l<size ; l++){
     float temp = sortedCgpa[l] ;
   
     int index = getKey(map,temp) ;  
  
     char query[400];
     sprintf(query,"SELECT prefRoom FROM main WHERE id=%d",index);
  if (mysql_query(con,query))  
  {
      finish_with_error(con);
  }

  MYSQL_RES *roompref = mysql_store_result(con);
  MYSQL_ROW r=mysql_fetch_row(roompref);
  if (roompref == NULL)
  {
      finish_with_error(con);
  }
  char temp1[400];
  strcpy( temp1 ,r[0]);
  createArray(matrixH , temp1 , l) ;
 
  }
 for(int z = N ; z<2*N ; z++){
     int h = -1 ;
     for(int l = 0 ; l<size ; l++){
         matrixH->prefArr[z].arr[++h] = l ;
     } 
 }
 
struct Graph *hostel = galeShapley(matrixH , N) ;

printf("%-20s%-20s%-20s\n","ROOMMATE1","ROOMMATE2","ROOM NO.");
printf("---------------------------------------------------------------------")  ; 
printf("\n") ;
for(int l =0 ; l<size ; l++){
     float temp = sortedCgpa[l] ;
     int ref = getKey(map,temp) ;
     char *name = getName(map,ref) ;
     int roompartner = roomate->array[ref].head->vertex  ;
     char *roomie = getName(map,roompartner) ;
     int room = hostel->array[l].head->vertex ;
     
   
     char query[400];
     sprintf(query,"SELECT room_number FROM RoomNum WHERE room_id=%d",room);
  if (mysql_query(con,query))
  {
      finish_with_error(con);
  }

  MYSQL_RES *x = mysql_store_result(con);
  MYSQL_ROW y=mysql_fetch_row(x);
  if (x == NULL)
  {
      finish_with_error(con);
  }
  char temp2[400];
  strcpy( temp2 ,y[0]);

  printf("%-20s%-20s%-20s\n",name,roomie,temp2) ;
     
} 





      



 

  mysql_free_result(result);
  mysql_close(con);
  free(map);
  free(matrixR);
  free(matrixH);
  free(roomate);
  free(sortedCgpa);
  free(hostel);

  exit(0) ;  
}

