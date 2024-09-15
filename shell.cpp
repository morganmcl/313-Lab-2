/****************
LE2: Introduction to Unnamed Pipes
****************/
#include <unistd.h> // pipe, fork, dup2, execvp, close
using namespace std;

int main () {
    // lists all the files in the root directory in the long format
    char* cmd1[] = {(char*) "ls", (char*) "-al", (char*) "/", nullptr};
    // translates all input from lowercase to uppercase
    char* cmd2[] = {(char*) "tr", (char*) "a-z", (char*) "A-Z", nullptr};

    // TODO: add functionality
    // Create pipe
    int pipefd[2]; // file descrip 
    pid_t cpid1;
    pid_t cpid2;
    
    pipe(pipefd);


    // Create child to run first command
    // In child, redirect output to write end of pipe
    // Close the read end of the pipe on the child side.
    // In child, execute the command
    
    cpid1 = fork();
  if(cpid1==0){ //it works child is good n real
    dup2(pipefd[1],1); 
    close(pipefd[0]);
    close(pipefd[1]);

    execvp(cmd1[0],cmd1); 
  }

 // Create another child to run second command
    // In child, redirect input to the read end of the pipe
    // Close the write end of the pipe on the child side.
    // Execute the second command.
    cpid2 = fork();

    if(cpid2==0){
    dup2(pipefd[0],0);
    close(pipefd[0]);
    close(pipefd[1]);

    execvp(cmd2[0],cmd2);
    //we done
    }


 // Reset the input and output file descriptors of the parent.
    close(pipefd[0]);
    close(pipefd[1]);

   

   
}
