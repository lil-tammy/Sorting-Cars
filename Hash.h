// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

//only include necessary header file here
//----

#include "LinkedList.h"
using namespace std;

class Hash
{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m;                     //slots number of the hash table

	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string model, string make, int vin);
      bool hashInsert(string model, string make, int vin, double price);
      bool hashDelete(string model, string make, int vin);
      int hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);


      // HELPER FUNCTION HERE
      int getDataSize();            // Returns the total elements added throughout the table
      int getTableSize();           // Returns the Table size.
  };

//constructor
Hash::Hash(int size)
{
   
    m = size;            // Size of our Hash Table
    hashTable = new LinkedList[m];  // initializes hashTable as a 1D array of size m, 
                                    // which will contain a Linked List in each array slot
}

//Destructor
Hash::~Hash()
{
   //----
   //----
    LinkedList* curList = hashTable;     // We set our pointer to point at the linkedList array.

    
    // Goes through each array slot and deletes the Linked List
    for (int i = 0; i < m; i++) {
        
        hashTable[i].~LinkedList();     // Deallocate memory for the linkedlist at each slot in the table
    }

    delete [] hashTable;        // Deallocate memory for the hashTable array
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin)
{

    // Searches that slot to see if a car with the vin exists or not.
    // If it exists, returns true and prints a message.
    // Else, returns false and prints a message.

   bool found = false;      // Shows if the car exists or not

   // Computes the index of the key
   string combinedString = model + make + to_string(vin);
   int index = hashFunction(combinedString);

   
   // Must search at that array index slot, and search the linkedlist
   // to do that, lets set the A[index] to a pointer and call the linkedlist function

   LinkedList* curList = &hashTable[index];
   found = curList->searchCar(vin);

   if (found == true) {
       cout << "\n" << left
           << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is found inside the hash table." << endl;

       return true;
   }
   else{
       cout << "\n" << left
           << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is NOT found inside the hash table." << endl;

      return false;
   }
   //----
   //----
}


//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price)
{
   //----
   //----


    // 1) Call hashFunction(key) to find the index/slot of the key.
    // 2) Then, at that slot insert the Car at the head of the linkedlist.
    // 3) Return true if inserted; else false


    // Part 1: Compute the index of the key
    string combinedString = model + make + to_string(vin);

    int index = hashFunction(combinedString);

    // Part 2: Insert the Car at the slot.
    // First, check if the car already exists. If it does return false, else true and insert.
    // To insert, we need to set a pointer to that slot so we can add the car.

    
    LinkedList* curList = &hashTable[index];    // current linkedlist we're iterating through

    // Car already exists, return false and don't insert.

    bool carIsInserted = curList->insertCar(model, make, vin, price);   // inserts the car

    if (carIsInserted == true) {
        return true;
    }
    else {
        return false;
    }
    
}

//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin)
{
   //----
   //----

    // 1) Call hashFunction(key) to compute the index/slot of the key.
    // 2) Search the list to find if the Car's vin exists or not. If it does, 
    //    delete the car, return true, and print the below. 
    //      Else, return false and print the following below.

    LinkedList* curList;    // maybe we don't need this 
    Car* curCar;
    Car* prevCar = nullptr;
    // bool vinFound = curList->searchCar(vin);

    hashSearch(model, make, vin);       // checks if the car already exists
    // Part 1: Compute the index of the key
    string combinedString = model + make + to_string(vin);

    int index = hashFunction(combinedString);

    bool isDeleted = hashTable[index].deleteCar(vin);

    /*curList = &hashTable[index];
    curCar = curList->getHead();*/

    // Part 2: Search the list for the car at that index, and delete if found.
    // 4 Cases for Deletion:
    //      1) Empty Linkedlist
    //      2) Delete Head
    //      3) Delete Middle
    //      4) Delete Tail


    // Out of the loop, the car below is what we want to delete
    // We have 3 cases: It's the head/only node, middle, or end node
    if (isDeleted == true) {
        cout << "\n";
        cout << setw(18) << model
            << setw(18) << make
            << setw(8) << vin
            << " is deleted from hash table." << endl;
        return true;
    }
    else if (isDeleted == false) {
        cout << "\n";
        cout << setw(18) << model
            << setw(18) << make
            << setw(8) << vin
            << " is NOT deleted from hash table." << endl;
        return false;
    }
   //----
   //----

      return false;
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
   //----
   //----

    // Longest linked list / m
    // n / m = load factor
    
    int loadFactor = 0;

    // How?
    // 1) Iterate through the entire list to find the MAX sized linked list
    // 2) Divide that MAX by the M size of the hash table.
    // 3) Return the divided value.

    

    for (int i = 0; i < m; i++) {
        if (hashTable[i].getSize() > loadFactor) { // Set the new max list size
            loadFactor = hashTable[i].getSize();
        }
    }

    return loadFactor;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
   //----
   //----

    // 1) Goes through each HashTable slot and print the size and contents
   
    // EXAMPLE 1: Empty Linked List
    // HashTable[0] is empty, size = 0

    // EXAMPLE 2
    // HashTable[1], size = 2
    // Montclair         Mercury           132829      950.00
    //    N911              Porsche            64287    44000.00


    for (int i = 0; i < m; i++) {
        if (hashTable[i].getSize() == 0) {
            // must print "HashTable[0] is empty, size = 0" if empty
            cout << "\nHashTable[" << i << "] is empty, size = " << hashTable[i].getSize() << endl;
        }
        else {
            // must print "HashTable[1], size = 2"
            cout << "\nHashTable[" << i << "], size = " << hashTable[i].getSize() << endl;

            hashTable[i].displayList();   // prints out the cars in the linkedlist

        }
    }
}


int Hash::hashFunction(string key)
{
    //----
    //----

    // convert each key to a number val
    int keyVal = 0;
    int index;
    int keyLen = key.length() - 1;

    // Add each key's ASCII 
    for (int i = 0; i < key.length(); i++) {
        char c = key.at(i);
        keyVal += int(c) ;
    }

    // Alternative way to convert to ASCII 
    /*for (int i = 0; i < key.length(); i++) {
        keyVal += (int)key[i];
    }*/

    index = keyVal % m;

    //cout << "keyVal is: " << keyVal << "\n";

    return index;


}

// Iterates through each table slot and sums the linkedList sizes
// Returns the total data size in our table
int Hash::getDataSize() {
    int dataSize = 0;

    for (int i = 0; i < m; i++) {
        dataSize += hashTable[i].getSize();
    }

    return dataSize;
}

// Returns the Hash Table Size
int Hash::getTableSize() {
    return m;
}