
// This program demonstrates the use of linked lists, adding nodes, deleting nodes, and finding nodes.
// The head of the Train is the engine, and each node is a car connected to that train.
// You may add cars, delete cars, or locate cars.
// Christopher K. Dierolf
// 2/17/2018

#include <iostream>
#include <string>

using namespace std;

//Class Definition
class Train {
private:
	struct TrainNode {
		string owner_name, car_contents;
		int car_number;
		TrainNode *next;
		TrainNode(string owner_name1, string car_contents1, int car_number1, TrainNode *next1 = nullptr)
		{
			owner_name = owner_name1;
			car_contents = car_contents1;
			car_number = car_number1;
			next = next1;
		}
	};

	TrainNode *head, *tail;
	const int MAX_TRAINS = 50;

public:
	// Constructor
	Train();
	~Train(); // Dee-struc-tor

	int display_menu();
	void handle_selection(int selection);
	bool validate_selection(int n, int upper, int lower); //check if in range
	string add_car(string name, string contents, int num);
	bool remove_car(int);
	int get_num_cars();
	void find_car(int num);
	void display_train();

};

//Class Implementation
//Constructor - Create a train
Train::Train()
{

	head = nullptr;
	// Add the engine
	add_car("R&R Railroad", "TRAIN ENGINE", 0);
	add_car("Eric Cartman", "Scott Tennerman's Famous Parent-Chili", 1);
	add_car("Kyle Broflofski", "Human Centipads", 2);
	add_car("Randy Marsh", "Lorde's Mustache", 3);
	add_car("Sheila Broflofski", "Weird Political Stances", 4);
	add_car("Ike Broflofski", "Canadian Survival Kit", 5);
	add_car("Stan Marsh", "Emesis Bags for Meeting Wendy Testaburger", 6);


}
// Destructor
Train::~Train()
{
	TrainNode *nodePtr = head;
	while (nodePtr != nullptr)
	{
		TrainNode *garbage = nodePtr;
		nodePtr = nodePtr->next;
		delete garbage;
	}
}

// Display the menu and return the selection back to the calling method.
int Train::display_menu()
{
	int selection;
	cout << endl;
	cout << "Select an option from the menu below: \n";
	cout << "\t 1. Display the train configuration\n";
	cout << "\t 2. Add a train car.\n";
	cout << "\t 3. Remove a train car.\n";
	cout << "\t 4. Find a train car.\n";
	cout << "\t 0. Exit.\n";
	cout << "Option (1-4 or 0 to quit.): ";
	cin >> selection;

	return selection;
}
// Handle the selection from display_menu
void Train::handle_selection(int selection)
{
	Train t;
	// Display the train
	if (selection == 1)
	{
		cout << "\nDisplaying the train cars: \n";
		display_train();
		cout << endl;

		handle_selection(display_menu());

	}
	// Add a car
	else if (selection == 2)
	{
		char add_more;
		bool train_full = false;
		// Only ten cars are allowed for the train not including the engine.
		do {
			if (get_num_cars() < 11)
			{
				string name, contents;
				string buffer;
				int number = 1;
				cout << "Which space in the train should be car be? (1-50): ";
				cin >> number;


				// Validate the number
				while (!validate_selection(number, 51, 0)) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << "Invalid Entry\n";
					cout << "Which space in the train should the car be? (1-50): ";
					cin >> number;
					cin.ignore();
				}

				cin.ignore();
				cout << "What is the owner of the train car's name? : ";
				getline(cin, name);

				cout << "What are the contents of the train car? : ";
				getline(cin, contents);

				// Add a new car to the train by creating a new node.
				add_car(name, contents, number);
				cout << "Car added at position " << number << " containing " << contents << endl;
				// Add more cars.
				cout << "\n\nDo you need to add another car? (Y/N): ";
				cin >> add_more;

				// Reset name and contents so weird things don't happen.
				name = "";
				contents = "";
			}
			// Train is full...no more cars.
			else
			{
				cout << "You cannot add anymore cars to this train.\n";
				train_full = true;
			}

		} while (add_more == 'Y' || add_more == 'y' && train_full == false);

	}
	else if (selection == 3)
	{
		int car_num;
		int num_cars;
		num_cars = get_num_cars();

		if (get_num_cars() == 0)
		{
			cout << "There are no cars to remove from this train.\n";
		}
		else
		{
			display_train();
			cout << endl;
			cout << "Select the car you would like to remove from the train: (1-" << num_cars - 1 << "): ";
			cin >> car_num;
			while (car_num < 1)
			{
				cout << "You can't remove the engine from the train. Make another selection: (1-" << num_cars - 1 << "): ";
				cin >> car_num;
			}
			remove_car(car_num);
		}
	}
	else if (selection == 4)
	{
		int find_car_num;
		int num_cars = get_num_cars();
		char search_again;
		do {
			cout << "What is the car number you would like to search for and, if applicable, display the information of?: (1-" << num_cars - 1 << "): ";
			cin >> find_car_num;
			while (!validate_selection(find_car_num, num_cars, 0))
			{
				cout << "Invalid entry. The train has only " << num_cars - 1 << " cars.\n";
				cout << "Enter a valid car number: 1-" << num_cars - 1 << ": ";
				cin >> find_car_num;
			}
			find_car(find_car_num);
			cout << "Would you like to search again? (Y/N): ";
			cin >> search_again;
		} while (search_again == 'Y' || search_again == 'y');

	}
	else
	{
		exit(0);
	}
}
//Validate numeric selections for range
bool Train::validate_selection(int n, int upper, int lower)
{
	if (n > lower && n < upper)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Add a train car (node) in sorted order based on the car_number
string Train::add_car(string name, string contents, int num)
{
	TrainNode *nodePtr = nullptr, *previousNodePtr = nullptr;

	if (head == nullptr || head->car_number >= num)
	{
		head = new TrainNode(name, contents, num);
	}
	else
	{
		//Append the list
		previousNodePtr = head;
		nodePtr = head->next;

		while (nodePtr != nullptr && nodePtr->car_number < num)
		{
			previousNodePtr = nodePtr;
			nodePtr = nodePtr->next;
		}
		previousNodePtr->next = new TrainNode(name, contents, num, nodePtr);
	}
	return "Added!";
}
bool Train::remove_car(int number)
{
	TrainNode *nodePtr, *previousNodePtr = nullptr;

	// list is empty
	if (!head)
	{
		return false;
	}
	// Check if number equals the car_number at the head
	else if (head->car_number == number)
	{
		nodePtr = head;
		head = head->next;	// Make the next node the head
		delete nodePtr;
		return true;
	}
	else
	{
		// Put the nodePtr at the head of the list
		nodePtr = head;
		//Traverse list skipping car_numbers that don't equal number
		while (nodePtr != nullptr && nodePtr->car_number != number)
		{
			previousNodePtr = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr)
		{
			previousNodePtr->next = nodePtr->next;
			delete nodePtr;
		}
		cout << "Car Removed!\n";
		return true;
	}
}
int Train::get_num_cars()
{
	int count = 0;
	TrainNode *nodePtr = head;
	while (nodePtr != NULL)
	{
		count++;
		nodePtr = nodePtr->next;
	}

	return count;
}
// Find a car, display it, and ask if they want to remove it.
void Train::find_car(int car_num)
{
	TrainNode *nodePtr = head;
	while (nodePtr)
	{
		while (nodePtr->car_number != car_num)
		{
			nodePtr = nodePtr->next;
		}
		cout << "Car found! Here is the information: \n";
		cout << "Car number: " << nodePtr->car_number << endl << "Car owner: " << nodePtr->owner_name << endl << "Car contents: " << nodePtr->car_contents << endl;
		return;
	}

	cout << "Car not found.\n";


}
//Display a list of cars to the user
void Train::display_train()
{
	TrainNode *nodePtr = head;

	while (nodePtr)
	{
		cout << endl << "Car number: " << nodePtr->car_number << endl;
		cout << "Owners Name: " << nodePtr->owner_name << endl;
		cout << "Car's Contents: " << nodePtr->car_contents << endl << endl;
		nodePtr = nodePtr->next;
	}
}

//Main

int main()
{
	Train t;
	char go_again;
	int selection;
	cout << "Hello and welcome to the train-creator-thingy.";
	cout << "\nYou can create a train with up to 50 cars, not including the engine\n\n";
	do {
		selection = t.display_menu();
		t.handle_selection(selection);
		cout << "Do you need to modify this train further? (Y/N): ";
		cin >> go_again;
	} while (go_again == 'Y' || go_again == 'y');
	return 0;
}
