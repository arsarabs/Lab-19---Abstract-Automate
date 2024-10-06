//Starting!
// COMSC-210 | Lab 18| Anthony R. Sarabia
// IDE used: Visual Studio

#include <iostream>
#include <iomanip>
#include <cstdlib>   // For rand()
#include <string>    // For string operations
#include <limits>    // For numeric_limits
#include <cctype>    // For toupper()
using namespace std;

//Defining constants
const float minRating = 0.0;
const float maxRating = 5.0;

//Struct
struct Review {
	float rating;
	string comments;
	Review* next; //Points to the next review 
};

//Function Prototypes
void output(Review*& h, float& avg);
void addReviewHead(Review*& h, float rating, string comments);
void addReviewTail(Review*& h, float rating, string comments);
void deleteReview(Review*& h);
int getUserChoice();
float validateRating();
string getComments();
bool getOneMoreReview();


//main()
int main() {

	Review* head = nullptr; //Initlaize head of list to nullptr
	float avg = 0.0;
	int userMethod = getUserChoice();
	bool flag = true;

	while (flag) {
		float rating = validateRating();
		string comments = getComments();

		//Let's add a new review to a specific positon in list
		if (userMethod == 1) {
			addReviewHead(head, rating, comments);
		}
		else {
			addReviewTail(head, rating, comments);
		}
		flag = getOneMoreReview();
	}

	//And finally, for the output!
	cout << "\nOutputting all reviews:\n";
	output(head, avg);
	cout << "AVERAGE: " << fixed << setprecision(5) << avg << endl;

	//Let's be sure to prevent any potential memory leaks
	deleteReview(head);

	return 0;
}

// outputReviews() displays all reviews in the linked list and calculates the average rating
// arguments: Node pointer to the head of the list, reference to a float to store the average
// returns: void
void output(Review*& h, float& avg) {
	//define some local variables
	int count = 1;           // Counter to number each review
	float total = 0.0;       // Variable to accumulate total ratings
	Review* current = h;    // Pointer to traverse the list
	//check to see if list empty
	if (!h) {
		cout << "No reviews!" << endl;
		return;
	}
	//Now, we create a while loop to transverse the list
	while (current) {
		cout << "      > Review #" << count++ << ": " << current->rating << ": " << current->comments << endl;
		total += current->rating; // add current rating to total
		current = current->next; //move to next review
	}
	avg = total / (count - 1); //calculate average
}

void addReviewHead(Review*& h, float rating, string comments) {
	//First, we start by dynamically allocating memory for new review
	Review* newReview = new Review;
	//Next we assign given rating & comments to new review
	newReview->rating = rating;
	newReview->comments = comments;
	//and now point the new review to the current head
	newReview->next = h;
	//update
	h = newReview;
}
// addReviewToHead() adds a new review to the front of the linked list
// arguments: reference to head node, rating to add, comments to add
// returns: void 
void addReviewTail(Review*& h, float rating, string comments) {
	//First, we start by dynamically allocating memory for new review
	Review* newReview = new Review;
	//Next we assign given rating & comments to new review
	newReview->rating = rating;
	newReview->comments = comments;
	//and now point the new review to nullptr
	newReview->next = nullptr;

	//check to see if list empty
	if (!h) {
		h = newReview;
		return;
	}
	//Now, let's transverse the list
	Review* current = h;

	//And now it transverses to last review
	while (current->next) {
		current = current->next;
	}
	current->next = newReview; //This links the new review at the end of list
}
void deleteReview(Review*& h) {
	//Pointer to transverse the list
	Review* current = h;

	while (current) {
		Review* temp = current; // temp varibale for current review
		current = current->next; // move to new review
		delete temp; //deallocate memory to prevent memory leaks
	}
	h = nullptr; //set head to nullptr
}
int getUserChoice() {
	int choice = 0; // Variable to store the user's choice

	// Loop until the user enters a valid choice (1 or 2)
	while (true) {
		cout << "Which linked list method should we use?" << endl;
		cout << "    [1] New nodes are added at the head of the linked list" << endl;
		cout << "    [2] New nodes are added at the tail of the linked list" << endl;
		cout << "Choice: ";
		cin >> choice; // Takes user input for the choice

		if (cin.fail() || (choice != 1 && choice != 2)) { // Validates the input
			cin.clear(); // Clears the error flag on cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Disregards invalid input
			cout << "Invalid choice. Please enter 1 or 2.\n" << endl;
		}
		else { // Valid input received
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Disregards any extra input
			break; // Exits the loop
		}
	}
	return choice;
}
float validateRating() {
	float rating = 0.0; //define
	while (true) {
		cout << "Enter review rating " << minRating << "-" << maxRating << ": ";
		cin >> rating; // Takes user input for the rating

		if (cin.fail() || rating < minRating || rating > maxRating) { // Validates the input
			cin.clear(); // Clears the error flag on cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Disregards invalid input
			cout << "Invalid rating. Please enter a number between " << minRating << " and " << maxRating << "." << endl;
		}
		else { // Valid input received
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Disregards any extra input
			break; // Exits the loop
		}
	}
	return rating; //return here
}
string getComments() {
	string comments;
	cout << "Enter review comments: ";
	getline(cin, comments);
	return comments;
}
bool getOneMoreReview() {
	char response = 'n'; // Variable to store the user's response

	// Loop until the user enters a valid response ('Y' or 'N')
	while (true) {
		cout << "Enter another review? Y/N: ";
		cin >> response; // Takes user input for the response
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Disregards any extra input
		// Converts the response to uppercase for consistency
		response = toupper(response);

		//Basic if/else
		if (response == 'Y') { // User wants to add another review
			return true;
		}
		else if (response == 'N') { // User does not want to add another review
			return false;
		}
		else {
			cout << "Invalid input" << endl;
		}
	}
}