
/*
 Specification file for the Sales class
  - Overloaded stream insertion operator (<<)
  - Overloaded relational operator (<)
 */

#ifndef SALES_H
#define SALES_H
#include <string>

using std::ostream;
using std::string;

/* Write your code here */
class Sales; // Forward Declaration
// Function Prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Sales &);

class Sales
{
    private:
    string id;
    int year;
    string name;
    int amountSold;
    double amountEarned;
    /* Write your code here*/
    
    public:
    // constructors
    Sales();
    Sales(string id, int year, string name, int amountSold);
      /* Write your code here*/
    
    // setters
    void setId(string givenId);
    void setYear(int givenYear);
    void setName (string givenName);
    void setAmount(int givenAmount);
    void setAmountEarned(double);
     /* Write your code here*/
    
    // getters
    string getId();
    int getYear();
    string getName();
    int getAmount();
    double getAmountEarned();
     /* Write your code here*/
    
    
    // other functions
    void display() const;
    double detCommissionPercent() const;
    double detAmountEarned() const;
     /* Write your code here*/
    
    // overloaded operators
      /* Write your code here*/                      // Overloaded <
    bool operator < (const Sales &);
    friend ostream &operator << (ostream &, const Sales &);
     /* Write your code here*/                      // Overloaded <<
};


#endif
