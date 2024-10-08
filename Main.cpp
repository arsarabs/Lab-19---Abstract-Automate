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
#include <ctime>      // For time()
#include <random>     // For generating random numbers

using namespace std;

//Defining constants
const float minRating = 1.0;
const float maxRating = 5.0;

//Struct
struct Review {
	float rating;
	string comments;
	Review* next; //Points to the next review 
};

//Function Prototypes (modified)
void output(Review* h, float& avg);
void addReviewHead(Review*& h, float rating, string comments);
void addReviewTail(Review*& h, float rating, string comments);
void deleteReview(Review*& h);
string randomRating();
bool readingFile(const string& filename, vector<string>& comments);

//Movie Class
class Movie {
private:
	Review* head; // head of linked list for our movie reviews
	string title;

public:
	//Constructor
	Movie(string movieTitle) : title(movieTitle), head(nullptr){}

	//Destructor
	~Movie() {
		deleteReview(head);
	}

	//Add a review
	void addReview(string comment, float rating) {
		addReviewHead(head, rating, comment);
	}
	 
	//I need a function to display the data (reviews/ratings)
	//Also, will display data in a neat format
	void displayData() const {
		float avgRating = 0.0;
		cout << "Movie: " << title << endl;
		output(const_cast<Review*>(head), avgRating); //we utilize const_cast here to match our function signature 

		if (head) {
			cout << "Average Rating: " << fixed << setprecision(1) << avgRating << endl;
		}
	}

	// Function to get the movie title
	string getTitle() const {
		return title;
	}

};

//main()
int main() {
	//FOR RANDOM SCORE GENERATION
	srand(static_cast<unsigned int>(time(0)));

	
	// Container for Movie objects using vector
	vector<Movie> movies;
	// Vector to hold comments read from the file
	vector<string> comments;

	//Movie objects
	Movie movie1("Whiplash");
	Movie movie2("Arrival");

	// Add movies to  container
	movies.push_back(movie1); 
	movies.push_back(movie2);

	// read comments from external file
	const string filename = "comments.txt";
	if (!readingFile(filename, comments)) {
		cerr << "Failed to read comments from file: " << filename << endl;
		return 1; // Exit with error code
	}


	//assigning reviews here!!!!! (final part!!!!!)

	//movie1
	movies[0].addReview(comments[0], stof(randomRating()));
	movies[0].addReview(comments[1], stof(randomRating()));

	//movie1
	movies[1].addReview(comments[2], stof(randomRating()));
	movies[1].addReview(comments[3], stof(randomRating()));



	// checking to see if there's enough comments
	if (comments.size() < 4) {
		cerr << "Not enough comments in the file. At least 4 comments are required." << endl;
		return 1;
	}

	// Optionally, add more reviews if available
	for (size_t i = 4; i < comments.size(); ++i) {
		// Alternate adding to movies
		movies[i % movies.size()].addReview(comments[i], stof(randomRating()));
	}

	// Display all reviews for each movie
	for (const auto& movie : movies) {
		movie.displayData();
	}

	return 0;
}
 
// outputReviews() displays all reviews in the linked list and calculates the average rating
// arguments: Node pointer to the head of the list, reference to a float to store the average
// returns: void
void output(Review* h, float& avg) {
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
		cout << "> Review #" << count++ << ": " << current->rating << ": " << current->comments << endl;
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
	//We need to generate a random score for our movie
	int randomScore = rand() % static_cast<int>((maxRating - minRating) * 10 + 1) + static_cast<int>(minRating * 10);

	//Now, we convert back to a float with one decmical
	float rating = static_cast<float>(randomScore) / 10.0f;

	//return
	return to_string(rating);
};
// readingFile() reads comments from an external file and stores them in a vector
// arguments: filename as string, reference to vector<string> to store comments
// returns: boolean indicating success or failure
bool readingFile(const string& filename, vector<string>& comments) {
	string line; //define local

	//open the file for reading
	ifstream inFile(filename);

	if (!inFile) { // Checks if the file was opened successfully
		cerr << "Error: Unable to open file '" << filename << "'." << endl;
		return false; // Indicates failure
	}

	//reads file
	while (getline(inFile, line)) { 
		if (!line.empty()) {
			comments.push_back(line);
		}
	}
	inFile.close(); // close file
	return true;
}


