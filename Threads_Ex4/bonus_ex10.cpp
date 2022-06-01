#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include "helpFunc.cpp"
#define MAX 10


void push(char **arr, char *item, int *pfront, int *prear) {
  int i, k;

  //If the queue is full it is impossible to insert an value
  if (*pfront == 0 && *prear == MAX - 1) {
    printf("\nDeque is full.\n");
    return;
  }

  //If there are no value in the queue
  if (*pfront == -1) {
    *prear = *pfront = 0;
    arr[*prear] = item;
    return;
  }

  //Insert the value in the appropriate place
  if (*prear == MAX - 1) {
    k = *pfront - 1;
    for (i = *pfront - 1; i < *prear; i++) {
      k = i;
      if (k == MAX - 1)
        arr[k] = 0;
      else
        arr[k] = arr[i + 1];
    }
    (*prear)--;
    (*pfront)--;
  }
  (*prear)++;
  arr[*prear] = item;
}

char* top(char**arr, int *pfront, int *prear) {
  char* item;

  //If there are no values in the queue
  if (*pfront == -1) {
    printf("\nDeque is empty.\n");
    return 0;
  }

  item = arr[*pfront];
  arr[*pfront] = (char*)"(null)";

  //If there is one value in the queue
  if (*pfront == *prear)
    *pfront = *prear = -1;
  else
    (*pfront)++;

  return item;
}

char* pop(char**arr, int *pfront, int *prear) {
  char* item;

  //If there are no values in the queue
  if (*pfront == -1) {
    printf("\nDeque is empty.\n");
    return 0;
  }

  item = arr[*prear];

  //Updating the place to be null
  arr[*prear] = (char*)"(null)";
  (*prear)--;
  if (*prear == -1)
    *pfront = -1;
  return item;
}

void array(char **arr) {
  int i;
  //Prints the queue as an array
  printf("front:  ");
  for (i = 0; i < MAX; i++)
    printf("  %s", arr[i]);
  printf("  :rear\n");
}

int count(char **arr) {
  //c is the counter
  int c = 0, i;
  //If there is a value other than null count it
  for (i = 0; i < MAX; i++) {
    if (strcmp(arr[i],"(null)") != 0)
      c++;
  }
  return c;
}

int main() {
  char* arr[MAX];
  int front, rear, n;
  //the front of the queue
  front = rear = -1;
  //set all values to be null
  for (int i = 0; i < MAX; i++){
    arr[i] = (char*)"(null)";
  }
  char promp[1024];
  int f = 1;
  int i = 0;
  printf("Write down the command, type 'EXIT' to exit:\n");
  //Receives input from the user
  while(f){
      scanf("%c", &promp[i]);
      if(promp[i] == '\n'){
          f= 0;
      }
      else{
          i++;
      }  
  }

// If the EXIT command is received - exit what shell you are writing.
  char* exit = (char*)"EXIT";
  while (!compareStr(promp, exit, 4))
  {
    f = 1;
    i = 0;
    if(compareStr(promp, (char*)"ENQUEUE", 7)){
        int j = 0;
        //Sends to "push" only the text you want to add to the queue without the command. Put the text in "wordS".
        char * wordS = (char*)malloc(j*sizeof(char));
        int n=0;
        for(size_t i = 8; i<strlen(promp); i++){
            if (promp[i] != ' ' && promp[i] != '\n' && ((int)i)-8 == j)
            {
                wordS[n++] = promp[i];
                j++;
            } 
        }
        push(arr, (char*) wordS, &front, &rear);
        printf("ENQUEUE: %s insert to the tail. \n",(char*)wordS);
    }else if(compareStr(promp, (char*)"DEQUEUE", 7)){
      //Sends the command "pop" and prints the element removed from the queue
        char* popW = pop(arr, &front, &rear);
        printf("DEQUEUE: %s remove the tail. \n", popW);
    }else if(compareStr(promp, (char*)"TOP", 3)){
      //Sends the command "top" to top function. print the top element.
        char* topW = top(arr, &front, &rear);
        printf("Top element is %s\n",topW);
    }else if(compareStr(promp, (char*)"ARRAY", 5)){
      //Prints the queue as an array
        array(arr);

    }else if(compareStr(promp, (char*)"COUNT", 5)){
      //print the total number of elements in the queue
        printf("Total number of elements in deque: %d\n", count(arr));
    }else{
      //If no valid command was received
        printf("ERROR: ");
        int i = 0;
        while (promp[i] != ' ' && promp[i] != '\n')
        {
            printf("%c",promp[i]);
            i++;
        }
        printf("\n");
    }
    //init the promp
    bzero(promp, sizeof(promp));
    printf("Write down the command, type 'EXIT' to exit:\n");
    //Receives input from the user
    while(f){
      scanf("%c", &promp[i]);
      if(promp[i] == '\n'){
        f= 0;
      }
      else{
        i++;
      }  
    }
  }
}
