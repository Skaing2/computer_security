/***********************************************************************
 * COMPONENT:
 *    INTERACT
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class allows one user to interact with the system
 ************************************************************************/

#include <iostream>   // standard input and output
#include <string>     // for convenience
#include <cassert>    // because I am paraniod
#include <stdlib.h>   // for atoi 
#include "messages.h" // to interact with the collection of messages
#include "control.h"  // all the Bell-LaPadula stuff
#include "interact.h" // the interact class and User structure

using namespace std;

/**************************************************************
 * USERS
 * All the users currently in the system
 *************************************************************/
const User users[] =
{
  // {"username", "password", security level}
   { "AdmiralAbe",     "password", Secret},  
   { "CaptainCharlie", "password", Privileged}, 
   { "SeamanSam",      "password", Confidential},
   { "SeamanSue",      "password", Confidential},
   { "SeamanSly",      "password", Confidential}
};

const int ID_INVALID = -1;

/****************************************************
 * INTERACT constructor
 * Authenticat ethe user and get him/her all set up
 ***************************************************/
Interact::Interact(const string & userName,
                   const string & password,
                   Messages & messages)
{
   authenticate(userName, password);
   this->userName = userName;
   this->pMessages = &messages;
}

/****************************************************
 * INTERACT :: SHOW
 * show a single message
 ****************************************************/
void Interact::show() const
{
   pMessages->show(promptForId("display"), userControl);
}
   
/****************************************************
 * INTERACT :: DISPLAY
 * display the set of messages
 ***************************************************/
void Interact::display() const
{
   pMessages->display(userControl);
}

/****************************************************
 * INTERACT :: ADD
 * add a single message
 ****************************************************/
void Interact::add()
{
  int id = idFromUser(userName);
   pMessages->add(promptForControl(), promptForLine("message"),
                  userName,
                  promptForLine("date"), this->userControl);
}

/****************************************************
 * INTERACT :: UDPATE
 * update a single message
 ****************************************************/
void Interact::update()
{
   int id = promptForId("update");
   pMessages->update(id,
                     promptForLine("message"), userControl);
}

/****************************************************
 * INTERACT :: REMOVE
 * remove one message from the list
 ***************************************************/
void Interact::remove()
{
   pMessages->remove(promptForId("delete"), userControl);
}

/****************************************************
 * INTERACT :: DISPLAY USERS
 * display the set of users in the system
 ***************************************************/
void displayUsers()
{
   for (int idUser = 0; idUser < sizeof(users) / sizeof(users[0]); idUser++)
      cout << "\t" << users[idUser].name << endl;
}
   
/****************************************************
 * INTERACT :: PROMPT FOR LINE
 * prompt for a line of input
 ****************************************************/
string Interact::promptForLine(const char * verb) const
{
   string line;
   cout << "Please provide a " << verb << ": ";
   getline(cin, line);
   return line;
}

/****************************************************
 * INTERACT :: PROMPT FOR ID
 * prompt for a message ID
 ***************************************************/
int Interact::promptForId(const char * verb) const
{
   string id;
   cout << "Select the message ID to " << verb << ": ";
   cin  >> id;
   cin.ignore();
   return atoi(id.c_str());
}

/*************************************************************
 * This is the control Interact prrompt for different levels
 **********************************************************/
Control Interact::promptForControl()
{
        int levels = 0;

        do  {
            cout << "Enter a Confidentiality Level from 0 to 3: ";
            cin >> levels;
            cin.ignore();
            if (levels == 0) {
                return Public;
            }
            else if (levels == 1) {
                return Confidential;
            }
            else if (levels == 2) {
                return Privileged;
            }
            else if (levels == 3) {
                return Secret;
            }
            else {
                cout << "Enter a value between 0 and 3." << endl;
            }
        }
        while (levels < 0 || levels > 3);
    return Public;

}

/****************************************************
 * INTERACT :: AUTHENTICATION
 * authenticate the user: find their control level
 ****************************************************/
void Interact::authenticate(const std::string & userName,
                            const std::string & password)
{
   int id = idFromUser(userName);
   bool authenticated = false;
   if (ID_INVALID != id && password == string(users[id].password))
      authenticated = true;
   if (authenticated) {
     this->userControl = users[id].userControl;
   } else {
     this->userControl = Public;
   }
}

/****************************************************
 * INTERACT :: ID FROM USER
 * Find the ID of a given user
 ****************************************************/
int Interact::idFromUser(const string & userName) const
{
   for (int idUser = 0; idUser < sizeof(users) / sizeof(users[0]); idUser++)
      if (userName == string(users[idUser].name))
         return idUser;
   return ID_INVALID;
}