/************************************************************
* Menu Structure:
* 1. Download the file into a folder
* 2. Open the folder with a text editor and compiler for c++
* 3. Run the program
* 4. The test cased will be displayed in the console
*************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;

vector<string> takePath(string a, char slash = '/');
string addTwoStrings(vector<string> &pathDir, string sSlash = "/");

vector<string> takePath(string a, char slash)
{
    string sub_string;
    stringstream ss(a);
    vector<string> pathDir;
    while (getline(ss, sub_string, slash))
    {
        pathDir.push_back(sub_string);
    }
    return pathDir;
}

string addTwoStrings(vector<string> &pathDir, string sSlash)
{
    if (!pathDir.size())
        return "";
    string result(pathDir[0]);
    for (int i = 1; i < pathDir.size(); i++)
    {
        result += sSlash + pathDir[i];
    }
    return result;
}

const string H(getenv("HOME"));
const string PWD(getenv("PWD"));

string cononicalize(string filename)
{
    vector<string> *canon = NULL;
    if (!filename.length())
    {
        return "/";
    }
    vector<string> pathDir(takePath(filename));
    if (filename[0] == '~')
    {
        canon = new vector<string>(takePath(H));
    }
    else if (filename[0] == '/')
    {
        canon = new vector<string>;
    }
    else
        canon = new vector<string>(takePath(PWD));
    for (int i = 0; i < pathDir.size(); i++)
    {
        string token(pathDir[i]);
        if (token == ".")
            ;
        else if (token == "..")
            canon->erase(canon->end() - 1);
        else
            canon->push_back(token);
    }
    string canon2 = addTwoStrings(*canon);
    return canon2;
}

bool compareHomographPaths(string file1, string file2)
{
    if (cononicalize(file1) == cononicalize(file2))
    {
        return true;
    }
    return false;
}

void testHomographs(string x, string y, bool expectedResult, int testNumber)
{
    if (compareHomographPaths(x, y) == expectedResult)
    {
        cout << "Test " << testNumber << " Pass!" << endl;
    }
    else
    {
        cout << "Test " << testNumber << " Fail..." << endl;
    }
}

// Run Test
void runTestCases()
{
    string first_file;
    string second_file;
    cout << "Running the Test Cases...." << endl << endl;
    // /Users/aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt

    cout << "Homograph Test Cases: " << endl;
    // . & .. (Dot and Double Dots)
    testHomographs("a.txt", "a.txt", true, 1);
    testHomographs("../Week 5/a.txt", "a.txt", true, 2);
    testHomographs("../../Computer Security/Week 5/a.txt", "a.txt", true, 3);
    testHomographs("../../././././././././Computer Security/Week 5/a.txt", "a.txt", true, 4);
    testHomographs("./a.txt", "a.txt", true, 5);
    testHomographs("././././././././a.txt", "a.txt", true, 6);
    testHomographs("./../././././Week 5/././././a.txt", "a.txt", true, 7);
    testHomographs("../../././Computer Security/././Week 5/././././a.txt", "a.txt", true, 8);
    testHomographs("Computer Security/./././Week 5/././a.txt", "Computer Security/Week 5/a.txt", true, 9);
    testHomographs("a.txt/./.", "a.txt", true, 10);
    testHomographs("../Computer Security/Week 5/a.txt", "a.txt", false, 11);
    testHomographs("Computer Security/../Computer Security/Week 5/a.txt", "Computer Security/Week 5/a.txt", true, 12);
    testHomographs("../../../aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt", "Week 5/a.txt", false, 13);
    testHomographs("Week 5/../Week 5/../Week 5/a.txt", "Week 5/a.txt", true, 14);
    testHomographs("Computer Security/../Week 5/../Week 5/Week 5/a.txt", "Computer Security/Week 5/a.txt", false, 15);

    // / (Slash)
    testHomographs("Week 5/", "Week 5", true, 16);
    testHomographs("a.txt", "Week 5/a.txt", false, 17);
    testHomographs("Week 5/a.txt", "Week 5/a.txt", true, 18);

    // ~
    testHomographs("~/Week 5/a.txt", "a.txt", false, 19);
    testHomographs("~/../~", "~", true, 20);

    cout << endl;
    // None-Homograph Test Cases
    // // /Users/aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt
    cout << "None-HomoGraph Test Cases: " << endl;
    testHomographs("Users/aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt", "a.txt", false, 21);
    testHomographs(".././../Week 5/a.txt", "", false, 22);
    testHomographs("../.././Users/aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt", "a.txt", false, 23);
    testHomographs("../././Users/aska/Computer Security/Week 5/text.txt", "a.txt", false, 24);
    testHomographs("./././Users/aska/Week 5/a.txt", "a.txt", false, 25);
    testHomographs("../../Users/aska/Week 5/a.txt", "a.txt", false, 26);
    testHomographs("../aska/Week 5/a.txt", "a.txt", false, 27);
    testHomographs(".././aska/Week 5/a.txt", "a.txt", false, 28);
    testHomographs("../../Week 5/a.txt", "a.txt", false, 29);
    testHomographs("../a.txt", "a.txt", false, 30);
    testHomographs("~/Week 5/a.txt", "/Users/aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt", false, 31);
    testHomographs("~/Computer Security/Week 5/a.txt", "/Users/aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt", false, 32);
    testHomographs("~/Winter 2021/Computer Security/Week 5/a.txt", "/Users/aska/Desktop/Winter 2021/Computer Security/Week 5/a.txt", false, 33);
}

int main()
{
    string first_file;
    string second_file;

    cout << "Specify the first filename: ";
    getline(cin, first_file);
    cout << "Specify the second filename: ";
    getline(cin, second_file);

    string first_path = cononicalize(first_file);
    string second_path = cononicalize(second_file);

    if (first_path == second_path)
    {
        cout << "The path are homographs" << endl;
    }
    else
    {
        cout << "The path are not homogrpahs" << endl;
    }
    runTestCases();
    return 0;
}
