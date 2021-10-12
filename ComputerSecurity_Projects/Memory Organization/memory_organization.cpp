/***********************************************************************
 * Program:
 *    Week 07 LAB, Memory Organization
 *    Brother Phillips, CSE-453
 * Author:
 *    Martin Vaughn, Lucas Feritas, Fillipe Ferreira, Sedona Tooley, 
 *    Joshua Rolph, Wyatt Nelson and Sengthay Kaing
 * Summary:
 *    For this week's assignment, we want to understand how to compiler utilizes
 *    the stack and the heap segments of memory. We want to be able to display the code,
 *    stack and heap of the Address of Segments and then display the Callstacks as a table.
 *    More importantly, we want to manipulate the stack in the main fucntion.  
 * Estimated: 7 hrs
 * Actual: 10 hrs
 *    The most difficult part would be reading all the stacks or address to find 
 *    strings or number or addresses that we are familar with.
 ************************************************************************/

/**********************************************************
* This program allow us to have accesses to the libraries. 
***********************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

/**********************************************
 * Address of Segments call the Code, Stack and Heap
 **********************************************/
void addresses_Segments(int a)
{
    void *code = NULL;
    code = (long*)&addresses_Segments;
    void *stack = NULL;
    stack = &a;
    void *heap = NULL;
    heap = new string("Memory Organization.");
  
    cout << endl << endl << "1. Addresses of Segments: " << endl;
    cout << "Code:  " << code << endl;
    cout << "Stack: " << stack << endl;
    cout << "Heap:  " << heap << endl << endl;
    return;
}

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   long number = 123456;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   addresses_Segments(1);

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << endl << "3. Manipulate the Stack" << endl;
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < 8; i++)
       output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 345678
{
   // start your display of the stack from this point
   long bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * pLong = NULL;
   char * pChar = NULL;

   // header for our table. Use these setw() offsets in your table
   cout << endl;
   cout << "2. Stack: Display the Callstack" << endl;
   cout << '[' << setw(2) << 'i' << ']'
        << setw(15) << "address" // 0x#######g
        << setw(20) << "hexadecimal" // 0x########
        << setw(20) << "decimal" // ########
        << setw(18) << "characters"
        << endl;
   cout << "----+"
        << "---------------+"
        << "-------------------+"
        << "-------------------+"
        << "-----------------+\n";
   for (long i = 30; i >= -4; i--)   // You may need to change 24 to another number
   {
     pLong = &bow + i;
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      
      if (i <= 30 && i >= 10) {
       cout << "[" << i << "]" << "  " << pLong << setw(20) << hex << *pLong << setw(20) << dec << *pLong << setw(18) << displayCharArray((char *) pLong) << endl;
      } 
      if (i <= -1 && i >= -4) {
        cout << "[" << i << "]" << "  " << pLong << setw(20) << hex << *pLong << setw(20) << dec << *pLong << setw(18) << displayCharArray((char *) pLong) << endl;
      } 
      if (i <= 9 && i >= 0) {
          cout << "[ " << i << "]" << "  " << pLong << setw(20) << hex << *pLong << setw(20) << dec << *pLong << setw(18) << displayCharArray((char *) pLong) << endl;
      }
      //
      ////////////////////////////////////////////////
   }
   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()
   // change text in main() to "*main**"
     // start by looking for *MAIN** 
   char *look = (char *)&bow;
   while (string(look) != "*MAIN**") {
     look++;
   }
   assert(string(look) == "*MAIN**");
   char *newText = (char *)look;
   newText[0] = '*';
   newText[1] = 'm';
   newText[2] = 'a';
   newText[3] = 'i';
   newText[4] = 'n';
   newText[5] = '*';
   newText[6] = '*';
  
  
  // change number in main() to 654321
   // The original long number in main is 123456;
  pLong = (long *)&bow;
  while (*pLong != 123456) {
    pLong++;
  }
  assert(*pLong = 123456);
  *pLong = 654321;
  
  
  // change pointerFunction in main() to point to pass
  pLong = (long *)&bow;
  while (*pLong != (long)fail) {
    pLong++;
  }
  assert(*pLong == (long)fail);
  *pLong = (long)pass;
  
  
  // change message in main() to point to passMessage
  pLong = (long *)&bow;
  while (*pLong != (long)failMessage) {
    pLong++;
  }
  assert(*pLong == (long)failMessage);
  *pLong = (long)passMessage;
   //
   ////////////////////////////////////////////////          
  
}