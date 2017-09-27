#include <iostream>

using namespace std;


double *ptr; 	//	Points to the next space in memory for cleaner code
double *v;
double *nv;
int size;
int elem_num;  	//	(COUNT VARIABLE) I had problems with using count
				//	as a variable because it is a function in the standard
				//	libraries.  Otherwise I would need to write "std::"
				//	so it just seemed neater this way.
				//	Hope that's ok! c:


//Defines the variables for the vector
void Initialize(){
	size = 2;										//Allocates memory for the size 
	v = (double *)malloc(size * sizeof(double));  	//of the vector times the size of
	elem_num = 0;									//a double.
	ptr = v;										//New element pointer at head
}


//Deallocates memory used for the vector
void Finalize(){
	free(v);
}


//Main options menu
int Op_menu() {
	int option = 0;
	while (option > 5 or option < 1) {		//Checks for right option
		cout <<
			"Main menu:\n\n"
			
			"1. Print the array\n"
			"2. Append element at the end\n"
			"3. Remove last element\n"
			"4. Insert element one element\n"
			"5. Exit\n\n"
			
			"Select an option: ";
		cin >> option;						//Input option choice
		cout << "\n";
			
		if (option > 5 or option < 1) {		//Try again if not correct
			cout << "Not a valid option. Please try again:\n\n";
		}
	}
	return option;
}


//Doubles the size of the vector if it is full
void Grow() {
	size *= 2;
	nv = (double *)malloc(size * sizeof(double));	//Allocate larger memory
	
	for (int i = 0;  i < elem_num; i++) {
		*(nv + i) = *(v + i);						//Moves data to new vector
	}
	
	free(v);										//Deallocates old vector
	v = nv;											//Points to new vector
	ptr = v;
	ptr += elem_num;								//Points to next entry
	
	//Debug Information
	cout << "\nVector grown\n"
			"Previous capacity: " << size / 2 << " elements\n"
			"New capacity: " << size << " elements\n\n";
}


//Halves the size of the vector if elements compose less than 30% of the 
//size of the vector
void Shrink() {
	size /= 2;
	nv = (double *)malloc(size * sizeof(double));	//Halves size
	
	for (int i = 0;  i < elem_num; i++) {			//Moves data
		*(nv + i) = *(v + i);
	}
	
	free(v);
	v = nv;											//Points to new vector
	ptr = v;
	ptr += elem_num;								//Points to next entry
	
													//Debug Information
	cout << "\nVector shrunk\n"
			"Previous capacity: " << size * 2 << " elements\n"
			"New capacity: " << size << " elements\n\n";
}


//Prints the vector
void PrintVector() {
	if (elem_num == 0){
		cout << "No elements to print.\n\n";
	} else {
		cout << "Vector Elements:\n"				//Some nice formatting
				"__________________\n";
				
		for (int i = 0;  i < elem_num; i++) {		//Tells which index data points are at
			cout << "V[" << i << "] : " << *(v + i) << "\n";
		}
	}
	cout << "\n";
}


//Appends a new element to the vector
void AddElement() {
	double new_elem;
	
	if (elem_num == size){						//If vector is too small, let it grow
		Grow();
	}

	cout << "Enter the new element: ";			//New element
	cin >> new_elem;
	cout << "\n";
	
	*ptr = new_elem;							//Appends element
	ptr++;										//Next space in memory
	elem_num++;
}


//Removes and prints the last element of the vector
void RemoveElement() {
	if (elem_num == 0){										//No elements to remove
		cout << "YOU'VE TAKEN ALL I HAVE! I HAVE NOTHING LEFT TO GIVE! :'c\n\n";
	} else {
		ptr--;												//Decrement tail
		elem_num--;
		
		cout << "The last element is: " << *ptr << "\n";	//Print last element
		
		if (elem_num == 1) {								//Grammar is important!
			cout << "There is now 1 element left.\n\n";
		} else {
			cout << "There is now " << elem_num << " elements left.\n\n";
		}
	}
	
	if (elem_num < (size * 0.3) && size > 2) {				//Check for wastefulness
		Shrink();
	}
}


//Inserts a new element to an inputted index
void InsertElement() {
	int elem_loc;
	double new_elem;

	
	if (elem_num == size){							//Not the most efficient time to grow
		Grow();										//but it does its job
	}
	
	cout << "Enter the index of the new element: ";
	cin >> elem_loc;
	cout << "\n";
	
	while (elem_loc < 0 || elem_loc > elem_num) {	//Gets index
		if (elem_num == 0) {
			cout << "I'm sorry, the index must 0.\n";
		} else {
			cout << "I'm sorry, the index must between 0 and "
				 <<	elem_num << ". \n";
		}
		cout << "Please try again.\n\n"
				"Enter the index of the new element: ";
		cin >> elem_loc;
		cout << "\n";
	}
	
	cout << "Enter the new element: ";				//Gets number
	cin >> new_elem;
	cout << "\n";

	for (int i = elem_num; i > elem_loc; i--) {		//Reindexing from the tail
		*(v + i) = *(v + i - 1);
	}	
	
	*(v + elem_loc) = new_elem;						//Inserts new element
	
	ptr++;											//Shifts the tail
	elem_num++;
}


//Chooses which action to take
void PickOption (int option) {
	
	switch (option) {
		case 1:	PrintVector();
				break;
		case 2: AddElement();
				break;
		case 3:	RemoveElement();
				break;
		case 4: InsertElement();
				break;
		case 5: cout << "Goodbye, you will be missed my friend!\n\n";  //Exits
				break;
	}
}

int main() {
	int option;
	Initialize(); 					//0 elements, size 2
	while (option != 5) {
		option = Op_menu(); 		//Options menu choice
		PickOption(option); 		//Pick option
	}
	Finalize();						//Free memory
	return 0;
}

