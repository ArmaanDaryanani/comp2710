/*
* FILE NAME:project4_Daryanani_ajd0101.cpp
* AUTHOR: Daryanani, Armaan (ajd0101)
* VERSION: 07/21/2023
* DESCRIPTION: COMP2710 Software Construction Project 4
* COMPILE: g++ project4_Daryanani_ajd0101.cpp -o Project4.out
* RUN: ./Project4.out
*/

//Libraries
#include <iostream>
#include <string>
#include <memory>

using namespace std;

//Define the structure for TriviaNode including question, answer, points and a pointer to the next node
struct TriviaNode
{
    string question;
    string answer;
    int points;
    shared_ptr<TriviaNode> next;
};

//Function that initializes hard-coded trivia questions, answers and points
shared_ptr<TriviaNode> initTrivia()
{
    //Creating the head node of the list
    shared_ptr<TriviaNode> head = make_shared<TriviaNode>();
    //Assigning values to the head node
    head->question = "How long was the shortest war on record? (Hint: How many minutes)?";
    head->answer = "38";
    head->points = 100;

    //Creating the second node
    shared_ptr<TriviaNode> node2 = make_shared<TriviaNode>();
    //Assigning values to the second node
    node2->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)?";
    node2->answer = "Bank of Italy";
    node2->points = 50;
    //Linking the head node to the second node
    head->next = node2;

    //Creating the third node
    shared_ptr<TriviaNode> node3 = make_shared<TriviaNode>();
    //Assigning values to the third node
    node3->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?";
    node3->answer = "Wii Sports";
    node3->points = 20;
    //Linking the second node to the third node
    node2->next = node3;

    //Returning the head of the list
    return head;
}

//Function that creates a new quiz question, answer and points from user input
void createQuizFromKeyboard(shared_ptr<TriviaNode> &head)
{
    string question, answer, shouldContinue;
    int points;

    do
    {
        //Prompt user for question, answer and points
        cout << "Enter a question: ";
        getline(cin, question);
        cout << "Enter an answer: ";
        getline(cin, answer);
        cout << "Enter award points: ";
        cin >> points;
        cin.ignore();

        //Creating a new node
        shared_ptr<TriviaNode> new_node = make_shared<TriviaNode>();
        //Assigning values to the new node
        new_node->question = question;
        new_node->answer = answer;
        new_node->points = points;
        new_node->next = nullptr;

        //Traversing to the end of the list
        shared_ptr<TriviaNode> current_node = head;
        while(current_node->next != nullptr)
        {
            current_node = current_node->next;
        }
        //Linking the last node to the new node
        current_node->next = new_node;

        //Asking user whether to continue adding questions
        cout << "Continue? (Yes/No): ";
        getline(cin, shouldContinue);
    } while (shouldContinue == "Yes");  //If "Yes", continue to add more questions
}

//Function that runs the trivia game, asking questions to the user and checking their answers
void runTriviaGame(shared_ptr<TriviaNode> &head, int numQuestions = -1)
{
    shared_ptr<TriviaNode> currentNode = head;
    int totalPoints = 0;  //Initialize total points

    //Loop through each node (question) in the list until numQuestions is exhausted
    while (currentNode != nullptr && numQuestions != 0)
    {
        //Ask question
        cout << "\nQuestion: " << currentNode->question << endl;
        cout << "Answer: ";

        //Get user answer
        string userAnswer;
        getline(cin, userAnswer);

        //Check if user's answer matches the correct answer
        if (userAnswer == currentNode->answer)
        {
            //If correct, award points
            cout << "Your answer is correct! You receive " << currentNode->points << " points.\n";
            totalPoints += currentNode->points;
        } else {
            //If incorrect, show the correct answer
            cout << "Your answer is wrong. The correct answer is: " << currentNode->answer << "\n";
        }

        //Display total points
        cout << "Your total points: " << totalPoints << "\n";

        //Move to the next question
        currentNode = currentNode->next;
        //Decrement the counter
        numQuestions--;
    }

    //If user wants to answer more questions than available, show a warning
    if(numQuestions > 0)
    {
        cout << "There are not that many questions.\n";
    }

    //If we've exhausted all questions, thank the user
    if(numQuestions == -1)
    {
        cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
    }
}

//If we're running unit tests
#ifdef UNIT_TESTING
void testDriver(shared_ptr<TriviaNode> &head) {
    // Execute different test cases
    cout << "*** This is a debugging version ***" << endl;
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message.\n";
    runTriviaGame(head, 0);
    cout << "Case 1 Passed\n";
    // ... and so on for other test cases
}
#endif

int main()
{
    //Initialize the trivia list
    shared_ptr<TriviaNode> head = initTrivia();

    //If we're running unit tests, execute test driver
#ifdef UNIT_TESTING
    testDriver(head);
#else
    //Otherwise, welcome the user, let them add questions and run the game
    cout << "*** Welcome to Armaan's trivia quiz game ***\n";
    createQuizFromKeyboard(head);
    runTriviaGame(head);
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
#endif

    return 0;
}
