//Starting! 
// COMSC-210 | Lab 19 | Anthony R. Sarabia
// IDE used: Visual Studio

#include <iostream>
#include <iomanip>
#include <cstdlib>   // For rand()
#include <string>    // For string operations
#include <limits>    // For numeric_limits
#include <cctype>    // For toupper()
#include <vector>     // For vector container
#include <fstream>    // For file operations
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

//Function Prototypes (modified)
void output(Review*& h, float& avg);
void addReviewHead(Review*& h, float rating, string comments);
void addReviewTail(Review*& h, float rating, string comments);
void deleteReview(Review*& h);
string randomRating();
bool readingFile(const string& filename, vector<string>& comments);


//main()
int main() {



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

string randomRating() {

};
// readingFile() reads comments from an external file and stores them in a vector
// arguments: filename as string, reference to vector<string> to store comments
// returns: boolean indicating success or failure
bool readingFile(const string& filename, vector<string>& comments) {
	//open the file for reading
	ifstream inFile(filename);

	if (!inFile) { // Checks if the file was opened successfully
		cerr << "Error: Unable to open file '" << filename << "'." << endl;
		return false; // Indicates failure
	}

}


