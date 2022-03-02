/*
 Build and procees a sorted linked list of Patient objects.
 The list is sorted in ascending order by name.
 Assume that the name is unique.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "LinkedList.h"

using namespace std;

void buildList(const string &filename, LinkedList &list);
void deleteManager(LinkedList &list);
void searchManager(const LinkedList &list);
void displayManager(const LinkedList &list);

int main()
{
    string inputFileName;
    LinkedList list;

    cout << "Enter file name: ";
    getline(cin, inputFileName);

    buildList(inputFileName, list);
    displayManager(list);
    searchManager(list);
    deleteManager(list);
    displayManager(list);
    return 0;
}

/* 
 This function reads data from a file and inserts them
 into a sorted linked list. The list is sorted in ascending order by name
 */
void buildList(const string &filename, LinkedList &list)
{
    ifstream inFile(filename);
    cout << "Reading data from \"" << filename << "\"\n";

    if(!inFile)
    {
        cout << "Error opening the input file: \""<< filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

   string id;
   int year;
   string name;
   int amount;
   
   string line;
   while (getline(inFile, line) )
   {
      stringstream temp(line);
      temp >> id >> year;
      temp.ignore();
      getline(temp, name, ';');
      temp >> amount;
        // create a Sales object and initialize it with data from file
        Sales s = Sales(id, year, name, amount);
        
        // call insert to insert this new Sales object into the sorted list
        list.insertNode(s);
    }

    inFile.close();
}

/* 
 Delete manager: delete items from the list until the user enters Q to quit
 deleting
 Input Parameter: list
 */
void deleteManager(LinkedList &list)
{
    string target = "";

    cout << " Delete" << endl;
    cout << "========" << endl;

    while(target != "Q")
    {
        cout << "Enter a name (or Q to stop deleting):" << endl;
        getline(cin, target);
        target[0] = toupper(target[0]);
        if(target != "Q")
        {
            if(list.deleteNode(target))
                cout << target << " has been deleted!" << endl;
            else
                cout << target << " not found!" << endl;
        }
    }
    cout << "___________________END DELETE SECTION_____" << endl;
}

/* 
 Search manager: search the list until the user enters Q to quit searching
 Input Parameter: list
 */
void searchManager(const LinkedList &list)
{
    string target = "";
    Sales obj;

    cout << " Search" << endl;
    cout << "========" << endl;

   /* Write your code here */
    while(target != "Q")
    {
        cout << "Enter a name (or Q to stop searching):" << endl;
        getline(cin, target);
        target[0] = toupper(target[0]);
        if(target != "Q")
        {
            if(list.searchList(target)){
                list.displayListInfo(target);
            }
            else{
                cout << target << " not found!" << endl;
            }
        }
    }
    cout << "___________________END SEARCH SECTION _____" << endl;
}


/*
Display manager: all, average, or year hired reports including header and footer where appropriate,
 depending on the user's choice;
 displays the number of nodes (always)
Input Parameter: list
*/
void displayManager(const LinkedList &list)
{
    // Sub-functions of displayManager()
    void showMenu(void);
    string getOption(void);
    void showHeader(string line);
   
    
    string line = "==== ==================== =============\n";
    string option;
    
    showMenu();
    option = getOption();
    while(option[0] != 'Q')
    {
        switch (option[0])
        {
            case 'A':
                showHeader(line);
                list.displayList();
                cout << line;
                break;
            case 'G':
                cout << "Average (amount sold) $";
                cout << setprecision(2) << fixed;
                cout << list.average() << endl;
                break;
            case 'Y':
                int year;
                cout << "Enter year: " << endl;
                cin >> year;
                showHeader(line);
                list.displayList(year);
                cout << line;
                break;
        }
        option = getOption();
    }
    cout << "Number of salespeople: " << list.getLength() << endl;
}

/*
Displays the header of the list - used in displayManager()
Input Parameter: line
*/
void showHeader(string line)
{
    cout << line;
    cout << "Year" << " " << left << setw(20) << "Name"
         << " Amount Earned" << endl;
    cout << line;
}

/*
Gets and returns the user's option - used in displayManager()
*/
string getOption(void)
{    
    string option;
    cout << "What is your option [A/G/Y/Q]?" << endl;
    cin >> option;
    cin.ignore();
    option[0] = toupper(option[0]);
    while (option != "A" && option != "G" && option != "Y" && option != "Q")
    {
        cout << "Invalid Option: Try again!";
        cout << "What is your option [A/G/Y/Q]?" << endl;
        cin >> option;
        cin.ignore();
        option[0] = toupper(option[0]);
    }
    return option;
}

/*
Displays the menu - used in displayManager()
*/
void showMenu(void)
{
    cout << "The following reports are available: " << endl;
    cout << "[A] - All" << endl
         << "[G] - Average" << endl
         << "[Y] - Year Hired" << endl
         << "[Q] - Quit" << endl;
}
