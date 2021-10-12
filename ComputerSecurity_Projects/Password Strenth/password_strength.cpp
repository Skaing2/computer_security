#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <iomanip>
using namespace std;

int main()
{
    char password[54];
    cout << "Please enter the password: ";
    cin >> password;
   
    int numbers = 0;
    int uppers =0;
    int lowers =0;
    int symbol =0;
    for (int i = 0; i < strlen(password); i++)
    {
        if (isdigit(password[i]))
        {
         numbers = 10; // from 0 - 9
        }
        if(isupper(password[i]))
        {
         uppers = 26; // A to Z
        }
        if(islower(password[i]))
        {
         lowers = 26; // a to z
        }
        
    if(!islower(password[i]) && !isupper(password[i]) && !isdigit(password[i]) )
        {
            symbol = 32;
        }
    }
    
    double long all = numbers + uppers + lowers + symbol;

    // pow(base, power);
    cout << "There are " << pow(all ,strlen(password)) << " combinations" << endl;
    
    cout << "That is equivalent to a key of " << floor(log2(pow(all, strlen(password)))) << " bits" <<endl;

    return 0;
}