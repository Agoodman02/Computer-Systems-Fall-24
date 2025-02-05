#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
      char*  array[3];                            // create an array with 3 slots
      array[0]=new char[10];       // create an oversized array of characters in slot 0 
      strcpy( array[0] , "ls");       // the array in slot 0 will contain ls
      array[1]=new char[10];       // create an oversized array  of characters in slot 1
      strcpy( array[1] , "-la");     // the array in slot 1 will contain -la
      array[2] = NULL;                      // point to null so it knows it is the end of the array
      
      execvp(array[0], array);    // SEE CHAPTER 3 SLIDES
      
      cout << "if we get here, execvp did not work!" << endl;
      return 0;
}
