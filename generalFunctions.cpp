#include <iostream>
#include "generalFunctions.h"
using namespace std;


int menu(const char** str, int NofOptions)
{
    int option;
    cout << "\n\n";
    cout << "Please choose one of the following options\n";
    for (int i = 0; i < NofOptions; i++)
        cout << i << " - " << str[i] << "\n";
    cout << -1 << "- Quit\n";
    cin >> option;
    cleanBuffer();
    return option;
}

void cleanBuffer()
{
	int c;
	do {
		c = getchar();
	} while (c != EOF && c != '\n');
}