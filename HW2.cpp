#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
    for (int i=0; i<3; i++)
        {
            cout << "Wow, a process!" << endl;
            fork();
            
        }
    
    return 0;
}
