/*
* FILE NAME:project3_Daryanani_ajd0101.cpp
* AUTHOR: Daryanani, Armaan (ajd0101)
* VERSION: 07/07/2023
* DESCRIPTION: COMP2710 Software Construction Project 3
* COMPILE: g++ project3_Daryanani_ajd0101.cpp -o Project3.out
* RUN: ./Project3.out
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
/****************************************************/
/*********************FUNCTIONS**********************/
/****************************************************/

/*******load_numbers_from_file*******/
//function to load numbers from file into a vector, checks if file has been opened correctly
vector<int> load_numbers_from_file(const string& filename)
{
    ifstream file(filename); // Open the file
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl; //checks if its avaliable
        exit(1);
    }
    vector<int> numbers; //vector to hold the numbers
    int number;
    while (file >> number)
    {
        numbers.push_back(number); //read the numbers from the file into the vector
    }
    file.close(); //close the file
    return numbers; //return the vector of numbers
}
/*******sort_vector********/
//function to sort the vector using bubble sort
void sort_vector(vector<int>& numbers)
{
    for (size_t i = 0; i < numbers.size() - 1; i++)
    {
        for (size_t j = 0; j < numbers.size() - i - 1; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                swap(numbers[j], numbers[j + 1]); //swap the numbers if current number is greater than the next one
            }
        }
    }
}

/*******output_to_file********/
//function to output the numbers in a vector to a file
void output_to_file(const vector<int>& numbers, const string& filename)
{
    ofstream file(filename); //opens the file
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl; //check if its avalible
        exit(1);
    }
    for (const int& number : numbers)
    {
        file << number << "\n"; //write each number in the vector to the file, each on a new line
    }
    file.close(); //closes the file
}
/****************************************************/
/***********************MAIN*************************/
/****************************************************/
int main()
{
    cout << "*** Welcome to Armaan's sorting program ***\n";

    /********FIRST FILE*******/
    string filename_1;
    cout << "Enter the first input file name: ";
    cin >> filename_1;

    vector<int> numbers_1 = load_numbers_from_file(filename_1); //load numbers from the first file

    cout << "The list of " << numbers_1.size() << " numbers in file " << filename_1 << " is:\n";
    for (const int& number : numbers_1)
    {
        cout << number << "\n"; //prints the numbers from the first file
    }
    cout << endl;

    /********SECOND FILE*******/
    string filename_2;
    cout << "Enter the second input file name: ";
    cin >> filename_2;

    vector<int> numbers_2 = load_numbers_from_file(filename_2); //loads numbers from the second file

    cout << "The list of " << numbers_2.size() << " numbers in file " << filename_2 << " is:\n";
    for (const int& number : numbers_2)
    {
        cout << number << "\n"; //print the numbers from the second file
    }
    cout << endl;

    /********LETS MERGE EM*******/
    //merge the vectors of numbers
    vector<int> merged_numbers(numbers_1);
    merged_numbers.insert(merged_numbers.end(), numbers_2.begin(), numbers_2.end());

    sort_vector(merged_numbers); //sort the merged vector

    cout << "The sorted list of " << merged_numbers.size() << " numbers is:";
    for (const int& number : merged_numbers)
    {
        cout << " " << number; //print the sorted numbers
    }
    cout << endl;

    /********OUTPUT FILE*******/
    string output_filename;
    cout << "Enter the output file name: ";
    cin >> output_filename;
    output_to_file(merged_numbers, output_filename); //write the sorted numbers to the output file

    cout << "*** Please check the new file - " << output_filename << " ***\n";
    cout << "*** Goodbye. ***" << endl;

    return 0;
}
