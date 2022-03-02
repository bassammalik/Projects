
#include "Sales.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* Write your code here */
/*~*~*~*~*~*~
 This is the default constructor; it sets everything to 0 or "".
 */
Sales::Sales()
{
   this->id = "";
   this->year = 0;
   this->name = "";
   this->amountSold = 0;
   this->amountEarned = 0.0;
   /* Write your code here */
}

/*~*~*~*~*~*~
This is an overloaded constructor.
 It sets the variables according to the parameters.
*/
Sales::Sales(string id, int year, string name, int amountSold)
{
   this->id = id;
   this->year = year;
   this->name = name;
   this->amountSold = amountSold;
   this->amountEarned = amountEarned;
    /* Write your code here */
}


/*~*~*~*~*~*~
This function displays the member variables,
 the commision percent and amount earned
 in a neat format.
*/
   
void Sales::display() const{
   cout << "           ID: " << id << endl;
   cout << "         Year: " << year << endl;
   cout << "         Name: " << name << endl;
   cout << "  Amount Sold: " << "$" << amountSold << endl;
   cout << "   Commission: " << detCommissionPercent() << "%" << endl;
   cout << "Amount Earned: " << "$" << detAmountEarned() << endl;
}

/*~*~*~*~*~*~
 This function determines the commision percent based on the following table:
    Sales        Commission
   $0 - 1000        3%
 1001 - 5000        4.5%
 5001 - 10,000      5.25%
 over 10,000        6%
*/
double Sales::detCommissionPercent() const
{
    double commission = 0;
    
    if (amountSold > 0)
    {
       if(amountSold <= 1000){
          commission = 3;
       }
       else if(amountSold <= 5000){
          commission = 4.5;
       }
       else if (amountSold <= 10000){
          commission = 5.25;
       }
       else{
          commission = 6;
       }
        /* Write your code here */
    }
    
    return commission;
}

/*~*~*~*~*~*~
 This function determines the amount earned:
 it calls the detCommisionPercent) function.
 */
double Sales::detAmountEarned() const
{
    double amountEarned = 0;
    amountEarned = (detCommissionPercent() * amountSold)/100.0;
    /* Write your code here */
    
    return amountEarned;
}

void Sales::setId(string givenId){
   id = givenId;
}
void Sales::setYear(int givenYear){
   year = givenYear;
}
void Sales::setName(string givenName){
   name = givenName;
}
void Sales::setAmount(int givenAmount){
   amountSold = givenAmount;
}

string Sales::getId(){
   return id;
}
int Sales::getYear(){
   return year;
}
string Sales::getName(){
   return name;
}
int Sales::getAmount(){
   return amountSold;
}

bool Sales::operator< (const Sales &right){
   return name < right.name;
}

ostream& operator << (ostream &out, const Sales &obj){
   out << setw(4) << left << obj.year << " ";
   out << setw(20) << left << obj.name << " ";
   out << setw(9) << right << setprecision(2) << fixed << obj.detAmountEarned() << endl;
   return out;
}