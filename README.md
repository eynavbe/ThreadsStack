# ThreadsStack
- The code is written in c but the file name will be named * .cpp.
To implement a stack using POSIX methods, your stack must contain a null variable of length.
The commands requested from client- as input to server, the stack is in server-.
  - PUSH command - will push <text> into the stack.
  - POP command - will bounce text from the stack.
  - TOP command - will display (output) the top of the stack. After sending TOP to the server will send to the client-output so that it starts with the OUTPUT prefix ":".
  - EXIT command - exits the server and client.
  - If a non-existent command is sent, it will be printed on the screen in the ERROR server ":" and the name of the command sent.
  - If there is a runtime error then send will be printed on the screen "DEBUG:" then place the error type.
 - That the server will receive a number of clients that transmit the stack command, all that a lock application because they may receive several commands to stack on different connections.
 - This is a permission clause and an email will be sent from the lecturer that is not mandatory to do.
 - Apply other methods to operate the stack, implement malloc, free, calloc command without using POSIX. The file name is mallocCalloc.cpp.
It has been proven to work by using it in the mystack.cpp file.
 Explanation of submission.
 - Apply a double queue instead of a stack. Attached is the file named bonus_ex10.cpp.
Commands required as input:
  - ENQUEUE command - will push <text> into the queue like a push, will be printed on the screen
 "ENQUEUE: <text> insert to the tail".
  - DEQUEUE command - will bounce text from the queue like pop. Will be printed on the screen
"DEQUEUE: <text> remove the tail."
  - TOP command - will display (output) the top of the queue.
  - COUNT command - will print the amount of values ​​in the queue.
  - ARRAY command - will print the queue as an array.
  - EXIT command - exits the input.
  - If an existing command is sent, ERROR will be printed on the screen ":" and the name of the command sent.
