/***********************************************************************
 * COMPONENT:
 *    MESSAGE
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class stores the notion of a message
 ************************************************************************/

#include <iostream>   // standard input and output
#include <cassert>    // because I am paraniod
#include "message.h"  // for the header file
using namespace std;

/**************************************************
 * MESSAGE DEFAULT CONSTRUCTOR
 * Set a message to empty
 **************************************************/
Message ::  Message()
{
   empty = true;
   text = "Empty";
   id = idNext++;
}

/**************************************************
 * MESSAGE NON-DEFAULT CONSTRUCTOR
 * Create a message and fill it
 **************************************************/
Message::Message(Control textControl, const string & text,
                 const string & author,
                 const string & date, Control userControl)
{
  if (securityConditionWrite(userControl, textControl)) {
   this->text = text;
   this->author = author;
   this->date = date;
   this->id = idNext++;
   empty = false;
  } else {
    cout << "You don't have premission to write this!" << endl;
  }
}

// adding this message 
Message::Message(const string& textControl,
                 const string& text,
                 const string& author,
                 const string& date)
{
    if (textControl == "Public")
    {
        this->textControl = Public;
    }
    if (textControl == "Confidential")
    {
        this->textControl = Confidential;
    }
    if (textControl == "Privileged")
    {
        this->textControl = Privileged;
    }
    if (textControl == "Secret")
    {
        this->textControl = Secret;
    }
    this->text = text;
    this->author = author;
    this->date = date;
    this->id = idNext++;
    empty = false;
}

/**************************************************
 * MESSAGE :: DISPLAY PROPERTIES
 * Display the attributes/properties but not the
 * content of this message
 **************************************************/
void Message::displayProperties(Control userControl) const
{
   // skip this one if there is nothing to see
   if (empty)
      return;
   
   // display the message
   // adding this 
    if (securityConditionRead(userControl, textControl))
    {
        // display the message
        cout << "\t[" << id << "] ";
        cout << "Message from " << author << " at " << date;
        cout << endl;
    }
    else
    {
        cout << "\t[" << id << "] ";
        cout << "You do not have permission to view this."<< endl;
        return;
    }
}

/**************************************************
 * MESSAGE :: DISPLAY TEXT
 * Display the contents or the text of the message
 **************************************************/
void Message::displayText(Control userControl) const
{
    if (securityConditionRead(userControl, textControl))
    {
        cout << "\tMessage: "
             << text
             << endl;
    }
    else
    {
        cout << "You do not have permission to view this."<< endl;
        return;
    }

}

/**************************************************
 * MESSAGE :: UPDATE TEXT
 * Update the contents or text of the message
 **************************************************/
void Message::updateText(const string& newText, Control userControl)
{
    if (securityConditionWrite(userControl, textControl))
    {
        text = newText;
    }
    else
    {
        cout <<"You do not have permission to write at this level."<< endl;
        return;
    }
}

/**************************************************
 * MESSAGE :: CLEAR
 * Delete the contents of a message and mark it as empty
 *************************************************/
void Message::clear(Control userControl)
{
    if (securityConditionWrite(userControl, textControl))
    {
        text = "Empty";
        author.clear();
        date.clear();
        empty = true;
    }
    else
    {
        cout <<"You do not have permission to write at this level." << endl;
        return;
    }

}

int Message::idNext = 100;