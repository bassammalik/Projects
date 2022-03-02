
#include <iostream>
#include "LinkedList.h"

using namespace std;

/*
 Constructor
 This function allocates and initializes a sentinel node
      A sentinel (or dummy) node is an extra node added before the first data record.
      This convention simplifies and accelerates some list-manipulation algorithms,
      by making sure that all links can be safely dereferenced and that every list
      (even one that contains no data elements) always has a "first" node.
*/ 
LinkedList::LinkedList()
{
    head = new Node; // head points to the sentinel node
    head->next = NULL;
    length = 0;
}

/*
 The insertNode function inserts a new node in a
 sorted linked list
*/
void LinkedList::insertNode(Sales dataIn)
{
 /* Write your code here */
    Node *newNode;  // A new node
    Node *pCur;     // To traverse the list
    Node *pPre;     // The previous node
    
    // Allocate a new node and store dataIn there.
    newNode = new Node;
    newNode->data = dataIn;

    // Initialize pointers
    pPre = head;
    pCur = head->next;
   
    // Find location: skip all nodes whose name is less than dataIn's gpa
    while (pCur != NULL && pCur->data.getName() < dataIn.getName())
    {
        pPre = pCur;
        pCur = pCur->next;
    }

    // Insert the new node between pPre and pCur
    pPre->next = newNode;
    newNode->next = pCur;
    
    // Update the counter
    length++;
}

/*
 The deleteNode function searches for a node
 in a sorted linked list; if found, the node is
 deleted from the list and from memory.
*/
bool LinkedList::deleteNode(string target)
{
  /* Write your code here */
    Node *pCur;       // To traverse the list
    Node *pPre;        // To point to the previous node
    bool deleted = false;
    
   /* Write your code here */
    pPre = head;
    pCur = head->next;

    // Find node containing the target: Skip all nodes whose name is less than the target
    while (pCur != NULL && pCur->data.getName() != target)
    {
        pPre = pCur;
        pCur = pCur->next;
    }
    
    // If found, delte the node
    if (pCur != NULL && pCur->data.getName() == target)
    {
        pPre->next = pCur->next;
        delete pCur;
        deleted = true;
        length--;
    }
    return deleted;
}

/*
 displayList shows the value
 stored in each node of the linked list
 pointed to by head, except the sentinel node
*/
void LinkedList::displayList() const
{
   Node *pCur;
   
   pCur = head->next;
   bool two = false;
   
   while(pCur){
      two = true;
      cout << pCur->data;

      pCur = pCur->next;
   }
   if(!two){
      cout << "N/A" << endl;
   }
 /* Write your code here */
}


/*
  
  
  
*/
void LinkedList::displayList(int year) const
{
    /* Write your code here */
   Node *pCur;
   pCur = head->next;
   bool one = false;
   
   while(pCur){

      if(pCur->data.getYear() == year){
         cout << pCur->data;
         one = true;
      }
      pCur = pCur->next;
   }
   if(!one){
      cout << "N/A" << endl;
   }
}

void LinkedList::displayListInfo(string target) const
{
  
   /* Write your code here */
    Node *pCur;       // To traverse the list
    Node *pPre = head;       // To point to the previous node
    pPre = pPre;
    // Initialize pointers
    pCur = head->next;

    // Find node containing the target: Skip all nodes whose name is less than the target
    while (pCur != NULL && pCur->data.getName() != target)
    {
        pPre = pCur;
        pCur = pCur->next;
    }
    
    // If found, delete the node
    if (pCur != NULL && pCur->data.getName() == target)
    {
        pCur->data.display();
    }

}

/*
  
  
  
*/
double LinkedList::average() const
{
    /* Write your code here */
    double total;
    
    Node *pCur;
    pCur = head->next;
    
    while(pCur){
       total +=pCur->data.getAmount();
       pCur = pCur->next;
    }
    return total/length;
}


/*
 The searchList function looks for a target item
 in the sorted linked list: if found, returns true
 and copies the data in that node to the output parameter
*/
bool LinkedList::searchList(string target) const
{
   bool found = false;
   /* Write your code here */
   Node *pCur;
   Node *pPre = head;
   pPre = pPre;
   pCur = head->next;
   
   while (pCur != NULL && pCur->data.getName() < target){
      pPre = pCur;
      pCur = pCur->next;
   }
   
   if(pCur != NULL && pCur->data.getName() == target){
      found = true;
   }
   
    return found;
}

/*
 Destructor
 This function deletes every node in the list.
*/
LinkedList::~LinkedList()
{
    Node *pCur;     // To traverse the list
    Node *pNext;    // To hold the address of the next node
    
    // Position nodePtr: skip the head of the list
    pCur = head->next;
    // While pCur is not at the end of the list...
    while(pCur != NULL)
    {
        // Save a pointer to the next node.
        pNext = pCur->next;
        
        // Delete the current node.
        delete pCur;
        
         // Position pCur at the next node.
        pCur = pNext;
    }
    
    delete head; // delete the sentinel node
}



