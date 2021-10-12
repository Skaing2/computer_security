/***********************************************************************
 * Program:
 *    Week 06 LAB, SQL INJECTION MITIGATION
 *    Brother Phillips, CSE-453
 * Author:
 *    Martin Vaughn, Lucas Feritas, Fillipe Ferreira, Sedona Tooley, Joshua Rolph, Wyatt Nelson, Sengthay Kaing
 * Summary:
 *    For this week's assignment, we simulated a SQL-Injection attack and explored 
 *    the strategies of a weak mitigation and a strong mitigation by generating a
 *    query with four types of attacks including Tautology, Attack, Union Attack,
 *    Addstate Attack and Comment Attack.
 * Estimated: 7 hrs
 * Actual: 15 hrs
 *    The most difficult portion of this assignment was the coordination
 *    between the team. Eventually, we got it mostly worked out and the 
 *    kinks were resolved.
 ************************************************************************/

/**********************************************************
* This program will simulate a command injection attack 
* and explore a couple mitigation strategies.
***********************************************************/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/***********************************************************************
* A function that accepts two input parameters and returns a SQL string.
************************************************************************/
string genQuery(string username, string password) {
    string a = "SELECT authenticate FROM users WHERE username ='";
    string b = "' and password ='";
    string sql = a + username + b + password + "';";
    return sql;
}


/***********************************************************************
* Cleans a username and password w/ a Weak Mitigation then calls genQuery
************************************************************************/
string genWeakQuery(string username, string password) {
    for (int i = 0; i < username.length(); i++) {
      if (username[i] == ';' || username[i] == '\'' || username[i] == '-' || username[i] == ' ') {
        username = username.substr(0, i);
        break;
      }
    }

    for (int i = 0; i < password.length(); i++) {
      if (password[i] == ';' || password[i] == '\'' || password[i] == '-' || password[i] == ' ') {
        password = password.substr(0, i);
        break;
      } 
    }
    cout << "Weak Mitigation: \n\t";
    return genQuery(username, password);
}


/***********************************************************************
* Cleans a username and password w/ a Strong Mitigation then calls genQuery
************************************************************************/
string genStrongQuery(string username, string password) {
    for(int i=0; i< username.length(); i++)
    {
        if(!isalpha(username[i])) {
          if (!isalnum(username[i])) {
            username = username.substr(0, i);
            break;
          }
        } 
    }
    for(int i=0; i < password.length(); i++)
    {
        if(!isalpha(password[i])) {
          if (!isdigit(password[i])) {
            password = password.substr(0, i);
            break;
          }
        } 
    }
    cout << "Strong Mitigation: \n\t";
    return genQuery(username, password);
}


/*********************************************************************************
* A function to demonstrate the Valid Test Cases.
**********************************************************************************/
void testValid() {
    cout << "\nValid Tests\n";
    cout << "genQuery: " << genQuery("lucas", "Test123") << endl;
    cout << "genQuery: " << genQuery("seng", "pokemon123") << endl;
    cout << "genQuery: " << genQuery("joshypoo", "openSesamee") << endl;
    cout << "genQuery: " << genQuery("todd", "theTodd") << endl;
    cout << "genQuery: " << genQuery("martinee", "yolo234") << endl;
    cout << "genQuery: " << genQuery("sedona", "Arizona") << endl;
    cout << "genQuery: " << genQuery("felipe", "brazeil4ever") << endl;
}

/*********************************************************************************
* A function to demonstrate that the function is vulnerable to the Comment Attack.
**********************************************************************************/
void testComment(string (*query)(string, string)) { 
    cout << "\nComment Tests\n";
    cout << "\t" << query("lucas'; --", "Test123") << endl;
    cout << "\t" << query("seng'; --", "pokemon123") << endl;
    cout << "\t" << query("joshypoo'; --", "openSesamee") << endl;
    cout << "\t" << query("todd'; --", "theToad") << endl;
    cout << "\t" << query("martinee'; --", "yolo234") << endl;
    cout << "\t" << query("sedona'; --", "Arizona") << endl;
    cout << "\t" << query("felipe'; --", "brazil4ever") << endl;
}

/*********************************************************************************
* A function to demonstrate that the function is vulnerable to the Comment Attack.
**********************************************************************************/
void testAddState(string (*query)(string, string)) {
    cout << "\nAdd Statement Tests\n";
    cout << "\t" << query("lucas", "Test123'; INSERT INTO passwordList (password, username) VALUES 'MyAccount', 'AddState1976") << endl;
    cout << "\t" << query("seng", "pokemon123'; DELETE FROM users WHERE username LIKE '%") << endl; 
    cout << "\t" << query("joshypoo", "openSesamee; INSERT INTO passwordList (password, username) VALUES 'evil_man', 'yolo") << endl;
    cout << "\t" << query("todd", "theToad'; UPDATE users SET username = 'you_been_hacked' WHERE username LIKE '%") << endl;
    cout << "\t" << query("martinee", "kkn4nie; INSERT INTO users (password, username) VALUES 'joeSmith', 'goldPl@tes") << endl;
    cout << "\t" << query("sedona", "Arizona; DELETE FROM users WHERE password LIKE '%!") << endl;
    cout << "\t" << query("felipe", "brazil4ever; UPDATE users SET password = '1234' WHERE password LIKE '%") << endl;
}

/***********************************************************************************
* A function to demonstrate that the function is vulnerable to the Tautology Attack.
************************************************************************************/
void testTautology(string (*query)(string, string)) {
    cout << "\nTautology Tests\n";
    cout << "\t" << query("lucas", "Test123' OR '1' = '1") << endl;
    cout << "\t" << query("seng", "pokemon123' OR 'a' = 'a") << endl;
    cout << "\t" << query("joshypoo", "openSesamee' OR 'z' = 'z") << endl;
    cout << "\t" << query("todd", "theToad' OR 'y' = 'y") << endl;
    cout << "\t" << query("martinee", "yolo234' OR 'x' = 'x") << endl;
    cout << "\t" << query("sedona", "Arizona' OR '1' = '1") << endl;
    cout << "\t" << query("felipe", "brazil4ever' OR 'password' = 'password") << endl;
}

/*************************************************************************************
* A function to demonstrate that the function is vulnerable to the Union Query Attack.
**************************************************************************************/
void testUnion(string (*query)(string, string)) {
    cout << "\nUnion Tests\n";
    cout << "\t" << query("lucas", "Test123' UNION SELECT authenticate FROM users WHERE username LIKE '%") << endl;
    cout << "\t" << query("seng", "pokemon' UNION SELECT authenticate FROM users WHERE password = '%") << endl;
    cout << "\t" << query("joshhypoo", "openSesamee' UNION SELECT authenticate FROM users WHERE '1' = '1") << endl;
    cout << "\t" << query("todd", "theToad' UNION SELECT authenticate FROM users WHERE users = '12345") << endl;
    cout << "\t" << query("martinee", "yolo234' UNION SELECT authenticate FROM users WHERE users != 'love") << endl;
    cout << "\t" << query("sedona", "Arizona' UNION SELECT authenticate FROM users WHERE password != 'crazyLove") << endl;
    cout << "\t" << query("felipe", "brazil4ever' UNION SELECT authenticate FROM users WHERE username LIKE '%") << endl;
}

/***************************************************
* The main function to call all the other functions.
****************************************************/
int main() {
    auto query = genQuery;
    auto weakQuery = genWeakQuery;
    auto strongQuery = genStrongQuery;

    cout << endl << "------------------------------------";
    cout << endl << "-------Query Generation Tests-------";
    cout << endl << "------------------------------------\n";
    testValid();
    testAddState(query);
    testComment(query);
    testUnion(query);
    testTautology(query);

    cout << endl << "------------------------------------";
    cout << endl << "-------Weak Mitigation Tests-------";
    cout << endl << "------------------------------------\n";
    testAddState(weakQuery);
    testComment(weakQuery);
    testUnion(weakQuery);
    testTautology(weakQuery);

    cout << endl << "------------------------------------";
    cout << endl << "-------Strong Mitigation Tests-------";
    cout << endl << "------------------------------------\n";
    testAddState(strongQuery);
    testComment(strongQuery);
    testUnion(strongQuery);
    testTautology(strongQuery);

    return 0;
}