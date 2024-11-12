#include <cstdio> // for file io
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
	FILE  *fp = fopen(argv[1],  "r" ); // filename on command line
	
	dup2(fileno(fp), fileno(stdin));   //make cin use file instead
	
	int var;
	cin >> var;
	
	cout << var*var << endl;
}
