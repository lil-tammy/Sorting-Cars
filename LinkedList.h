// Description: A simple linked list that implements a list of Car objects. A user can
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Car
{
   string model, make;
   int vin;
   double price;
   struct Car* next;
};

class LinkedList
{
   private:
     struct Car* head;
     int size;      //a variable represents number of Cars inside the list
   public:
     LinkedList();
     ~LinkedList();
     Car* getHead();
     int getSize();
     bool searchCar(int carVIN);
     bool insertCar(string model, string make, int vin, double price);
     bool deleteCar(int carVIN);
     void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    //----
    //---
    head = nullptr;
    size = 0;
}

//Destructor: Delete all cars in the LinkedList
LinkedList::~LinkedList()
{
    //----
    //--
    Car* curCar = head;     // Helps us traverse the list
    Car* tempCar;           // Use to delete if needed
    
    while (curCar != nullptr) {
        tempCar = curCar;
        curCar = curCar->next;

        delete tempCar;
        size--;
    }

    head = nullptr;         // set Head as nullptr to make sure we aren't accessing memory we aren't allowed to.


}

Car* LinkedList::getHead()
{

    return head;    // Note: even if head is empty, it will return the nullptr stored in it.
                   //           no need to do anything extra. Simply return head

}

//Return number of Cars inside the Linked list
int LinkedList::getSize()
{
    //----
    return size;
}

//This function does a linear search on the Car list with the given Car VIN
//it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN)
{

    Car* curCar = head;

    // Empty List.
    if (head == nullptr) {
        return false;
    }

    // Traverse the list to find the car
    while (curCar != nullptr) {
        if (curCar->vin == carVIN) { return true; }

        curCar = curCar->next;
    }

    return false;
}

//Insert the parameter Car at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price)
{
   
    // Initiailize our Car. Delete this object we don't need to add it.
    Car* newCar = new Car();
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;
    newCar->price = price;
    newCar->next = nullptr;
    
    // If list is empty, set the head.
    if (head == nullptr) {
        head = newCar;
        size++;
        return true;
    }
    // Car VIN already exists, don't add. 
    else if (searchCar(vin) == true) {
        delete newCar;      // de-allocate since not adding car
        return false;   
    }
    // Else, set as head and update next pointer.
    else {
        newCar->next = head;
        head = newCar;
        size++;
        return true;
    }

}

//Delete the Car with the given Car VIN from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(int carVIN)
{
    //----
    //---
    Car* curCar = head;
    Car* prevCar = nullptr;
    
    // 3 Cases for Deletion:
    // * Also, consider empty list.
    //      1) Beginning of list
    //      2) End
    //      3) Middle


    if (head == nullptr) {
        return false; // Empty list
    }


    // Loop through list to delete car and return true.
    while (curCar != nullptr) {
        if (curCar->vin == carVIN) {

            // 1) Delete from head of list
            if (prevCar == nullptr) {
                // simply set head to its next node.

                head = head->next;
                delete curCar;
            }
            // 2) Delete from End
            else if (curCar->next == nullptr) {
                prevCar->next = nullptr;
                delete curCar;
            }
            // 3) Delete from Middle
            else{
                // must update prev's next pointer
                prevCar->next = curCar->next;
                delete curCar;
            }

            size--;             // Decrement size of list
            return true;        // Any of the above conditions delete the car
        }

        prevCar = curCar;       
        curCar = curCar->next;      // traverses the list
    }

    return false; // Return false when list is empty or we found no such car

}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
   struct Car *temp = head;
   if(head == NULL)
   {
   	//empty linked list, print nothing here
       // HashTable[0] is empty, size = 0

   }
   else
   {
      while(temp != NULL)
      {
         cout << left    << setw(18) << temp->model
              << left    << setw(18) << temp->make
              << right   << setw(8)  << temp->vin
              << setw(10) << fixed << setprecision(2) << temp->price << "\n";
         temp = temp->next;
      }
   }
}
