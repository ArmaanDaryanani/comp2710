/*
 * FILE NAME:project1_Daryanani_ajd0101.cpp
 * AUTHOR: Daryanani, Armaan (ajd0101)
 * VERSION: 06/02/2023
 * DESCRIPTION: COMP2710 Software Construction Project 1
 * COMPILE: g++ project1_Daryanani_ajd0101.cpp -o Project1.out
 * RUN: ./Project1.out
 */

#include <iostream>

using namespace std;

int main() {
    // Variable initialization
    double loan;
    double interestRate;
    double interestRateC;
    double monthlyPaid;

    // Currency Formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // USER INPUT
    cout << "\nLoan Amount: ";
    cin >> loan;

    // GET PROPER INTEREST RATES FOR CALCULATIONS
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;

    interestRate /= 12;
    interestRateC = interestRate / 100;

    cout << "Monthly Payments: ";
    cin >> monthlyPaid;

    cout << endl;

    // AMORTIZATION TABLE
    cout << "***********************************************************\n"
         << "\tAmortization Table\n"
         << "***********************************************************\n"
         << "Month\tBalance\t  Payment\tRate\tInterest  Principal\n";

    int currentMonth = 0;
    double balance = loan;
    double payment = monthlyPaid;
    double interest = 0;
    double principal = 0;
    double interestTotal = 0;

    cout << currentMonth++ << "\t$" << balance << "  " << "N/A\t\tN/A\tN/A\t  N/A" << endl;

    // LOOP TO FILL TABLE
    while (balance > 0 && payment >= interest) {
        if (balance < monthlyPaid) {
            interest = balance * interestRateC;
            principal = balance;

            payment = balance + interest;

            interestTotal += interest;

            balance = 0;

            cout << currentMonth++ << "\t$" << balance << "   $" << payment << "\t\t";
            cout << interestRate << "\t$" << interest << "\t$" << principal << endl;
            break;
        }
        interest = balance * interestRateC;
        principal = monthlyPaid - interest;

        if (interestRate < 0) {
            interestRate = 0;
        }

        balance -= principal;
        payment = monthlyPaid;

        cout << currentMonth++ << "\t$" << balance << "  $" << payment << "\t";
        cout << interestRate << "\t$" << interest << "\t  $" << principal << endl;

        interestTotal += interest;
    }

    cout << "***********************************************************\n";
    cout << "\nIt takes " << currentMonth - 1 << " months to pay off the loan.\n";
    cout << "Total interest paid is: $" << interestTotal << endl << endl;

    return 0;
}
