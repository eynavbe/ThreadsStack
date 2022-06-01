#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "helpFunc.cpp"
#include "mystack.cpp"
#include <pthread.h>
#include <limits.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>

#define PORT 8080
//lock and unlock a mutex
pthread_mutex_t lock;
void* HelloWorld(void *vargp)
{
    //Initializes the beginning of the stack
    struct StackNode* root = NULL;
    char client_message[1024];
    //create socket to recive message from the client
    int new_socket = *((int*)vargp);
    //recive a message from the client and put him into "client_message"
    if(recv(new_socket , client_message , 1024 , 0) < 0)
    {
        puts("DEBUG: recv failed");
    }
    //while the message is not an exit message
    while(!compareStr(client_message, (char*)"EXIT", 4)){	
        /*
        Before touching the stack we lock the program so that another customer
        does not change the stack at the same time
        */	
        pthread_mutex_lock(&lock);
        //Sleep for 5 seconds so we can see the thread action
        sleep(5);
        if(compareStr(client_message, (char*)"PUSH", 4)){
            int j = 0;
            char * wordS = (char*)malloc(j*sizeof(char));
            int n=0;
            //Sends to "push" only the text you want to add to the stack without the command. Put the text in "wordS".
            for(size_t i = 5; i<strlen(client_message); i++){
                if (client_message[i] != ' ' && client_message[i] != '\n' && ((int)i)-5 == j)
                {
                    wordS[n++] = client_message[i];
                    j++;
                } 
            }
            push(&root, (char*) wordS);
        }else if(compareStr(client_message, (char*)"POP", 3)){
            //Sends the command "pop" and prints the element removed from the stack
            printf("%s popped from stack\n", pop(&root));
        }else if(compareStr(client_message, (char*)"TOP", 3)){
            //Sends the command "top" to peek function. print the top element.
            char * top_w = peek(root);
            printf("Top element is %s\n",top_w);
            //sent the top element to the client
            send(new_socket, top_w, strlen(top_w), 0);
            printf("%s message sent\n",top_w);
        }else{
            //If no valid command was received: "pop", "top" or "push", send error
            printf("ERROR: ");
            int i = 0;
            while (client_message[i] != ' ' && client_message[i] != '\n')
            {
                printf("%c",client_message[i]);
                i++;
            }
            printf("\n");
        }
        //unlock the program
        pthread_mutex_unlock(&lock);
        //receive the message from the client and put him into "client_message"
        if(recv(new_socket , client_message , 1024 , 0) < 0)
        {
            puts("DEBUG: recv failed");
            break;
        }
    }
    return 0;  
}

int main(int argc, char const* argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    //The socket() call creates a socket in the specified domain and of the specified type.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        perror("DEBUG: socket failed");
        exit(EXIT_FAILURE);
    }
    //Set socket option.
     if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("DEBUG: setsockopt");
        exit(EXIT_FAILURE);
    }

    //Provide needed information about destination.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //associates an address with the socket descriptor.
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("DEBUG: bind failed");
        exit(EXIT_FAILURE);
    }
    // prepares a connection-oriented server to accept client connections.
    if (listen(server_fd, 3) < 0) {
        perror("DEBUG: listen");
        exit(EXIT_FAILURE);
    }
    //Initializes 10 thread so we can connect with 10 clients in parallel
    pthread_t thread_id[10];
    //Pointer to the threads
    int i = 0;
    while(1){
        //accept the connection of the new client
        new_socket = accept(server_fd, (struct sockaddr*)&address,
                (socklen_t*)&addrlen);
        if (new_socket == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
        }
        //Creates a new tread called "HelloWorld" for the current client
        pthread_create(&thread_id[i++], NULL, HelloWorld, &new_socket);
        //After reaching 10 thrreads, reuse them 
        if(i == 9){
            i=0;
        }
    }
    return 0;
}