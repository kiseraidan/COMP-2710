/*
 * Author: Aidan Kiser
 * UserID: ark0053
 * Filename: project4_kiser_ark0053.cpp
 * Compile: g++ project4_kiser_ark0053.cpp -o Project4.out
 * Run: ./Project4.out
 * Version: 26 October 2023
 * Resources: Ppt notes & online resources for syntax, & information from PDF.
 */

#include <iostream>
#include <string>
using namespace std;

int num_of_questions = 0;

// node structure with pointer

struct TriviaNode {
	string question;
	string answer;
	int points;
	TriviaNode *next;
};

typedef TriviaNode* pointer_node;

// function

void Unit_Test();
int ask_question(pointer_node q_list, int num_ask);
void init_question_list(pointer_node& q_list);
void add_question(pointer_node& q_list);

// debug

//#define UNIT_TESTING
#define trivia_quiz

int main() {

#ifdef trivia_quiz
	pointer_node node_list = new TriviaNode;
	init_question_list(node_list);

	// user inputed questions
	cout << "*** Welcome to Aidan's trivia quiz game ***\n";
	string input;
	do {
		add_question(node_list);
		cout << "Continue? (Yes/No): ";
		getline(cin, input);
	} while (input.compare("Yes") == 0 || input.compare("yes") == 0);
	cout << endl;

	ask_question(node_list, num_of_questions);
	cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***";
	return 0;
}
#endif

	// debug

#ifdef UNIT_TESTING
	Unit_Test();
	return 0;
}
#endif

// definitions

void init_question_list(pointer_node& q_list) {
	pointer_node curr_ptr = new TriviaNode;

	// sample question 1
	curr_ptr->question = "How long was the shortest war on record? (Hint: how many minutes)";
	curr_ptr->answer = "38";
	curr_ptr->points = 100;
	curr_ptr->next = new TriviaNode;

	// initialize q_list to be first question
	q_list = curr_ptr;
	curr_ptr = q_list->next;

	// sample question 2
	curr_ptr->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
	curr_ptr->answer = "Bank of Italy";
	curr_ptr->points = 50;
	curr_ptr->next = new TriviaNode;
	curr_ptr = curr_ptr->next;

	// sample question 3
	curr_ptr->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
	curr_ptr->answer = "Wii Sports";
	curr_ptr->points = 20;
	curr_ptr->next = NULL;

	num_of_questions += 3;
}

void add_question(pointer_node& q_list) {
	
    // initialize new pointer
	pointer_node new_ptr = new TriviaNode;

	// get the user input for questions, answers, and points
	cout << "Enter a question: ";
	getline(cin, new_ptr->question);
	cout << "Enter an answer: ";
	getline(cin, new_ptr->answer);
	cout << "Enter award points: ";
	cin >> new_ptr->points;
	cin.ignore(); 
	new_ptr->next = NULL;

	// add to back of list
	TriviaNode* last = q_list;
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = new_ptr;

	// add to top of list
	num_of_questions++;
}

int ask_question(pointer_node q_list, int num_ask) {
	pointer_node curr_ptr = q_list;
	string user_answer;
	int total_points = 0;

	// make sure its not null
	if (q_list == NULL) {
		return 0;
	}

	// make sure its not 0
	if (num_ask <= 0) {
		cout << "Warning - the number of trivia to be asked must equal to or be larger than 1." << endl;
		return 1;
	} else if (num_of_questions < num_ask) {
		cout << "Warning - there is only " << num_of_questions << " trivia in the list." << endl;
		return 1;

    // ask the questions and answer
	// adds the points together
	} else {
		for (int i = 0; i < num_ask; i++) {
			cout << "Question: " << curr_ptr->question << endl;
			cout << "Answer: ";
			getline(cin, user_answer);
			if (user_answer.compare(curr_ptr->answer) == 0) {
				cout << "Your answer is correct. You receive " << curr_ptr->points << " points." << endl;
				total_points += curr_ptr->points;
			} else {
				cout << "Your answer is wrong. The correct answer is: " << curr_ptr->answer << endl;
			}
			cout << "Your total points: " << total_points << endl << endl;

			// Debugging '\n'
			//cout << user_answer << "    " << curr_ptr->answer << endl;

			curr_ptr = curr_ptr->next;
		}
	}
	return 0;
}

void Unit_Test() {
	cout << "*** This is a debugging version ***\n";

	pointer_node node_list = new TriviaNode;
	init_question_list(node_list);

	cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
	ask_question(node_list, 0);
	cout << "Case 1 passed\n\n";

	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
	ask_question(node_list,1);
	cout << "Case 2.1 passed\n\n";

	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
	ask_question(node_list,1);
	cout << "Case 2.2 passed\n\n";

	cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
	ask_question(node_list,3);
	cout << "Case 3 passed\n\n";

	cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
	ask_question(node_list,5);
	cout << "Case 4 passed\n\n";

	cout << "*** End of the Debugging Version ***";
}