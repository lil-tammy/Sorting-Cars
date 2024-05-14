# Sorting-Cars

This program utilizes a self-implemented Hash-Table (with an underlying linked-list) that sorts cars based on their model, make, and VIN.
A Hash-Table allows for users to efficiently access a car's information such as model, make, VIN, and price.

When the user inputs the model, make, and VIN, and price of a car, the program will convert the car into a key and store the car's 
information into the hash table if it doesn't already exist.

The key is composed as a single string including the car's model, make, and VIN. When the key is passed to the hash function,
the index where the car will go into the hash-table is given.
