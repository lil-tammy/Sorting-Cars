// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.
//
// ANSWER: I used Hash by Division for my Hash function.
//
//			Essentially, my function takes in the string input of model, make and vin.
//			I concatenate model, make, and vin into a single string, no spaces in
//			between unless they originally had spaces, then that can be kept.
//
//			I traverse through each character of the new string and turn each 
//			character into an ASCII value and add it to get the sum of all
//			ASCII values. 
//			
//			The sum will be my key value, which I will % modulus it by the table size m,
//			giving me the index to hash at.
//
// ***Also note, for some reason, intentionally concatenating with spaces in-between
//			lead to a worse performance, and I suspect it's due adding something in common between
//			all keys leads to less random distribution, so omitting the space actually helped
//			distribute the elements more uniformly.
//
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
//
//	ANSWER: The hash function worked well for all four test cases.
//
//		Test Case 1:
//			My Longest LinkedList Size: 6.00
//			My Performance Ratio: 1.88
//
//			Case's Longest LinkedList Size: 5.00
//			Case's Performance Ratio: 1.56
//
//		Test Case 2:
//			My Longest LinkedList Size: 9.00 to 9.00
//			My Performance Ratio: 1.66 to 1.75	
//
//			Case's Longest LinkedList Size: 9.00 to 8.00
//			Case's Performance Ratio: 1.66 to 1.56
//
//		Test Case 3:
//			My Longest LinkedList Size: 8.00 to 8.00
//			My Performance Ratio: 1.69 to 1.83
//
//			Case's Longest LinkedList Size: 7.00 to 7.00
//			Case's Performance Ratio: 1.48 to 1.60
//
//		Test Case 4:
//			My Longest LinkedList Size: 25.00 to 25.00
//			My Performance Ratio: 1.44 to 1.48
//
//			Case's Longest LinkedList Size: 26.00 to 24.00
//			Case's Performance Ratio: 1.50 to 1.42
//
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
//
//	ANSWER: I would try to incorporate more randomization in determining my string's key value.
//			
//			Some ways I could implement that is to shift the bits of the key value to the right,
//			since I know the string is long so the key will have a large value.
//			Shifting to the left might not be preferable, since it could lead to
//			a common factor between the other keys.
//			
//			Another way is to get the radix conversion (multiply by a base to the power) of the key, which could help randomize the key value
//			and lead to a better performance.
//
//			The division method seemed good since we're doing % by a prime number, so I would keep to that method.
//			It would be interesting to try other methods though, like Hash by Multiplication and see how it goes.
//
********************************************************************************/

#include "Hash.h"
#include <sstream>

using namespace std;

//This function used to get a Car key which is the combination of model, make and vin
void getKey(string oneLine, string& model, string& make, int& vin);

// ADDED HELPER FUNCTION HERE
void getKeyInsert(string oneLine, string& model, string& make, int& vin, double& price);	// Helps with inserting car by including the price

string getKeyCommand(string oneLine, string& model, string& make, int& vin);	// Helps obtain the command of the key, and updates the model, make, vin.


int main()
{
   int size = 0 ;
   int numOfCommand = 0;
   string model, make;
   int vin;
   double price;

   //declare any other necessary variables here
   //----
   string userCarInput;
   bool continueInsert = true;

   
   string firstToken;
   string command;
   double idealLoadFactor;
   double actualLoadFactor;
   double performanceRatio;

   //

   cout << "Enter the size of the hash table: ";
   cin >> size;
   cin.ignore(20, '\n');

   //Instantiate the hash table with the relevant number of slots
   //----
   Hash* table1 = new Hash(size);


   do {
         //use this do..while loop to repeatly get one line Car info. and extract tokens
         //create one Car object and insert it inside the hashTable until seeing the message
         //"InsertionEnd" to terminate
         //----
         //----

		//cout << "Please enter the Car information:";
		getline(cin, userCarInput);
		
		//cout << "userCarInput stores: " << userCarInput;

		// As long as InsertionEnd isn't inputted, then we keep inserting.
		if (userCarInput == "InsertionEnd") {	// Input == to stopping condition, set condition to false
			continueInsert = false;

		}
		else {
			getKeyInsert(userCarInput, model, make, vin, price);	// retrieves the car info, now we can insert
			table1->hashInsert(model, make, vin, price);			// Inserts the car into the Hash Table

		}



   } while(continueInsert == true);


   //cout << "\nEnter number of commands: ";   //***need to comment out in submitting
   cin >> numOfCommand;
   cin.ignore(20, '\n');

   for(int i= 0; i < numOfCommand; i++)
   {
	   //cout << "\nEnter first command: ";   //***need to comment out in submitting
	   getline(cin, firstToken);

   	//get one line command, extract the first token, if only one token
      if(firstToken.compare("hashDisplay") == 0)
      {
         
		  // Calls the hashDisplay() to display the table's contents
		  table1->hashDisplay();
      }
	  else if (firstToken.compare("hashLoadFactor") == 0) {	// Also only has one token as a command

		  // WHAT DOES THIS DO?
		  // 1) Compute the ideal load factor here in this file
		  //		idealLoadFactor = numer_of_Cars_in_data_set/hashTableSize;
		  // 
		  // 2) Call hashLoadFactor() to get the table's actual load factor
		  // 
		  // 3) Compute Hash Table's performance
		  //		performance_ratio = actualLoadFactor/idealLoadFactor;
		  //		NOTE:you need to make sure the ratio is <= 2.3
		  //
		  // EXAMPLE FORMAT: 
		  //				The ideal load factor is: 5.14
		  //				My hash table real load factor is : 8.00
		  //				My hash table performance ratio is : 1.56

		  // Part 1: Compute Ideal Load Factor
		  idealLoadFactor = double(table1->getDataSize()) / table1->getTableSize();

		  cout << "\nThe ideal load factor is: " << fixed << setprecision(2) << idealLoadFactor << endl;

		  // Part 2: Call hashLoadFactor() to get the table's actual load factor
		  actualLoadFactor = table1->hashLoadFactor();

		  cout << "My hash table real load factor is: " << fixed << setprecision(2) << actualLoadFactor << endl;

		  // Part 3: Compute Hash Table's performance
		  performanceRatio = actualLoadFactor / idealLoadFactor;

		  cout << "My hash table performance ratio is: " << fixed << setprecision(2) << performanceRatio << endl;

	  }
      else  //more than one tokens, check the command name, extract the remaining tokens
      {
		  command = getKeyCommand(firstToken, model, make, vin);	// this will extract command name, model, make, vin
       
		  if (command.compare("hashSearch") == 0) {
		  
			// WHAT DOES THIS DO
			// FORMAT: hashSearch,model,make,vin
			// Example: hashSearch,Mustang,Ford,137178
			//
			// X1) Call getKeyCommand() to extract the values  ** already done above this if statement
			// 2) Call hashSearch() to find the car and it'll print the info accordingly
			//
			// Sample Output:
			// Mustang           Ford              137178   is found inside the hash table.
			// Charger           Dodge             123456   is NOT found inside the hash table.

			  // Part 2: Call hashSearch()

			  table1->hashSearch(model, make, vin);


		  }
         else  if(command.compare("hashDelete")==0) {

			  // WHAT DOES THIS DO
			  // FORMAT: hashDelete,model,make,vin
			  // EXAMPLE: hashDelete,Mustang,Ford,137178
			  //
			  // This is where we use the getKey() function to extract those values
			  //
			  // X1) Call getKeyCommand() to extract the values  ** already done above this if statement
			  // 2) Call hashDelete() and displays the following:
			  //	Mustang           Ford              137178   is deleted from hash table.
			  //	WhateverModel     WhateverMake      123456   is NOT deleted from hash table.


			  // Part 2: Call hashDelete()
			  table1->hashDelete(model, make, vin);

		 }
         else{
			 cout << "Invalid command" << endl;
		 }
            
      }
   } //end for loop
   return 0;
}

//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
//This function is completed and given here as a study guide for extracting tokens
void getKey(string oneLine, string& model, string& make, int& vin)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   string command = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
}


//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
// Used to help insert the car in this file.
void getKeyInsert(string oneLine, string& model, string& make, int& vin, double& price)
{
	string delimiter = ",";
	int pos = oneLine.find(delimiter);
	string token = oneLine.substr(0, pos);
	model = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	make = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	vin = stoi(token);
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	price = stoi(token);
	oneLine.erase(0, pos + delimiter.length());

	// Extracted the car string parts, now we can add the car.
	// Call insertCar outside of this function

}

//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
// This returns the command as a string, while also extracting model, make, vin
string getKeyCommand(string oneLine, string& model, string& make, int& vin)
{
		string delimiter = ",";
		int pos = oneLine.find(delimiter);
		string token = oneLine.substr(0, pos);
		string command = token;
		oneLine.erase(0, pos + delimiter.length());

		pos = oneLine.find(delimiter);
		token = oneLine.substr(0, pos);
		model = token;
		oneLine.erase(0, pos + delimiter.length());

		pos = oneLine.find(delimiter);
		token = oneLine.substr(0, pos);
		make = token;
		oneLine.erase(0, pos + delimiter.length());

		pos = oneLine.find(delimiter);
		token = oneLine.substr(0, pos);
		vin = stoi(token);
		oneLine.erase(0, pos + delimiter.length());

		return command;
}
