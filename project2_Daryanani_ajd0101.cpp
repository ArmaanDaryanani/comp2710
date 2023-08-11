/*
* FILE NAME:project2_Daryanani_ajd0101.cpp
* AUTHOR: Daryanani, Armaan (ajd0101)
* VERSION: 06/16/2023
* DESCRIPTION: COMP2710 Software Construction Project 2
* COMPILE: g++ project2_Daryanani_ajd0101.cpp -o Project2.out
* RUN: ./Project2.out
*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

/*********************PROTOTYPES**********************/
using namespace std;
//Instance Variables on total wins between each player
int a_wins1 = 0;
int a_wins2 = 0;
int b_wins = 0;
int c_wins = 0;
//CONSTANTS
const int TOTAL_RUNS = 10000;
const int A_PROBABILITY = 33;
const int B_PROBABILITY = 50;

/*
* Input: A_alive indicates Aaron is alive true for alive, false for dead
* B_alive indicates Bob is alive
* C_alive indicates Charlie is alive
* Return: true if at least two are alive otherwise return false
*/
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);

/*
* Call by reference
* Strategy 1: Everyone shoots to kill the highest accuracy player alive
* Input: B_alive indicates Bob is alive or dead
* C_alive indicates Aaron is alive or dead
* Return: Change B_alive into false if Bob is killed
* Change C_alive into false if Charlie is killed
*/
void Aaron_shoots1(bool& B_alive, bool& C_alive);

/*
* Call by reference
* Input: A_alive indicates Aaron is alive or dead
* C_alive indicates Charlie is alive or dead
* Return: Change A_alive into false if Aaron is killed
* Change C_alive into false if Charlie is killed
*/
void Bob_shoots(bool& A_alive, bool& C_alive);

/* Call by reference
        * Input: A_alive indicates Aaron is alive or dead
        * B_alive indicates Bob is alive or dead
        * Return: Change A_alive into false if Aaron is killed
        * Change B_alive into false if Bob is killed
*/
void Charlie_shoots(bool& A_alive, bool& B_alive);

/*
* Call by reference
* Strategy 2: Aaron intentionally misses if both are alive
* Input: B_alive indicates Bob is alive or dead
* C_alive indicates Aaron is alive or dead
* Return: Change B_alive into false if Bob is killed
* Change C_alive into false if Charlie is killed
*/
void Aaron_shoots2(bool& B_alive, bool& C_alive);

/*********************TESTING PROTOTYPES**********************/
/*testing for prototype test_at_least_two_alive();*/
void test_at_least_two_alive(void);

/*testing for prototype test_Aaron_shoots1();*/
void test_Aaron_shoots1(void);

/*testing for prototype test_Bob_shoots();*/
void test_Bob_shoots(void);

/*testing for prototype test_Charlie_shoots();*/
void test_Charlie_shoots(void);

/*testing for prototype test_Aaron_shoots2();*/
void test_Aaron_shoots2(void);

/*****************************************************/
/*********************MAIN BLOCK**********************/
/*****************************************************/

int main()
{
    /****cout.setf(ios::fixed | ios::showpoint);****/

    cout << "*** Welcome to Armaan's Duel Simulator ***\n";

    srand(time(0)); //sets randomness seed

    /*RUNNING TESTS*/
    test_at_least_two_alive();
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //pauses

    test_Aaron_shoots1();
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //pauses

    test_Bob_shoots();
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //pauses

    test_Charlie_shoots();
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //pauses

    test_Aaron_shoots2();
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //pauses

    /****Starts strategy 1 and runs 10,000 times****/
    cout << "Ready to test strategy 1 (run 10000 times):\n";
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //pauses
    for(int i = 0; i < TOTAL_RUNS; i++)
    {
        //bool everyone alive.
        bool aaronAlive = true;
        bool bobAlive = true;
        bool charlieAlive = true;
        /*While loop for 2 alive players*/
        while(at_least_two_alive(aaronAlive, bobAlive, charlieAlive))
        {
            if (aaronAlive) //if aaron is alive
            {
                Aaron_shoots1(bobAlive, charlieAlive);
            }
            if (bobAlive) //if bob is alive
            {
                Bob_shoots(aaronAlive, charlieAlive);
            }
            if (charlieAlive) //if charlie is alive
            {
                Charlie_shoots(aaronAlive, bobAlive);
            }
        }
        //checks who is alive after duel
        if (aaronAlive)
        {
            a_wins1++;
        }
        else if (bobAlive)
        {
            b_wins++;
        }
        else
        {
            c_wins++;
        }
    }
    //prints wins for all players
    cout << "Aaron won " << a_wins1 << "/10000 duels or " << static_cast<double>(a_wins1) /
                                                                TOTAL_RUNS * 100 << "%\n"
         << "Bob won " << b_wins << "/10000 duels or " << static_cast<double>(b_wins) /
                                                                TOTAL_RUNS * 100 << "%\n"
         << "Charlie won " << c_wins << "/10000 duels or " << static_cast<double>(c_wins) /
                                                                TOTAL_RUNS * 100 << "%\n"
         << endl;

    //Reinitializes variables and starts strategy 2 to run 10,000 times
    a_wins2 = 0;
    b_wins = 0;
    c_wins = 0;

    cout << "Ready to test strategy 2 (run 10000 times):\n";
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //pauses
    /****Starts strategy 2 and runs 10,000 times****/
    for(int i = 0; i < TOTAL_RUNS; i++)
    {
        //bool everyone alive.
        bool aaronAlive = true;
        bool bobAlive = true;
        bool charlieAlive = true;
        /*While loop for 2 alive players*/
        while(at_least_two_alive(aaronAlive, bobAlive, charlieAlive))
        {
            if (aaronAlive) //if aaron is alive
            {
                Aaron_shoots2(bobAlive, charlieAlive);
            }
            if (bobAlive) //if bob is alive
            {
                Bob_shoots(aaronAlive, charlieAlive);
            }
            if (charlieAlive) //if charlie is alive
            {
                Charlie_shoots(aaronAlive, bobAlive);
            }
        }
        //checks who is alive after duel
        if (aaronAlive)
        {
            a_wins2++;
        }
        else if (bobAlive)
        {
            b_wins++;
        }
        else
        {
            c_wins++;
        }
    }
    //prints wins for all players
    cout << "Aaron won " << a_wins2 << "/10000 duels or " << static_cast<double>(a_wins2) /
                                                            TOTAL_RUNS * 100 << "%\n"
         << "Bob won " << b_wins << "/10000 duels or " << static_cast<double>(b_wins) /
                                                          TOTAL_RUNS * 100 << "%\n"
         << "Charlie won " << c_wins << "/10000 duels or " << static_cast<double>(c_wins) /
                                                              TOTAL_RUNS * 100 << "%\n"
         << endl;

    //compares the aaron win percentage between the two strategies and prints appropriate answer depending on which is higher.
    if (a_wins2/TOTAL_RUNS > a_wins1/TOTAL_RUNS)
    {
        cout << "Strategy 1 is better than strategy 2.\n";
    }
    else
    {
        cout << "Strategy 2 is better than strategy 1.\n";
    }
    return 0;

}

/***************************************************************/
/*********************IMPLEMENTATIONS***************************/
/***************************************************************/

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive)
{
    //when a_alive is true, checks for living others
    if (A_alive)
    {
        if (B_alive || C_alive)
        {
            return true;
        }
    }
        //when a_alive is false, checks for living others
    else if (B_alive)
    {
        if (C_alive)
        {
            return true;
        }
    }
    //if a_alive & b_alive ==false, check for others
    return false;
}
/*implement for prototype test_at_least_two_alive();*/
void test_at_least_two_alive()
{
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";

    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed...\n";

    cout<< "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed...\n";

    cout<< "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed...\n";

    cout<< "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed...\n";

    cout<< "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed...\n";

    cout<< "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed...\n";

    cout<< "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed...\n";
}

void Aaron_shoots1(bool& B_alive, bool& C_alive)
{
    //variables
    int aaronProbability;
    //sets probability
    aaronProbability = A_PROBABILITY;

    //gets rand int
    int shootResult = rand() % 100;

    //equates randint to probability. If true, shoots.
    if (shootResult <= aaronProbability)
    {
        if(C_alive)
        {
            //most accurate dies first
            C_alive = false;
        }
        else
        {
            B_alive = false;
        }
    }
}


/*implement for prototype test_Aaron_shoots1();*/
void test_Aaron_shoots1(void)
{
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";

    //both alive
    bool bob_a = true;
    bool charlie_a = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";

    assert(true == bob_a);
    assert(true == charlie_a);
    Aaron_shoots1(bob_a, charlie_a);
    //checks if charlie is alive. If so, aaron misses (probability)
    if (charlie_a)
    {
        cout << "\t\tAaron misses.\n";
    }
    else
    {
        cout << "\t\tCharlie is dead.\n";
    }

    //only bob dead
    bob_a = false;
    charlie_a = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";

    assert(false == bob_a);
    assert(true == charlie_a);
    Aaron_shoots1(bob_a, charlie_a);
    //checks if charlie is alive. If so, aaron misses (probability)
    if (charlie_a)
    {
        cout << "\t\tAaron misses.\n";
    }
    else
    {
        cout << "\t\tCharlie is dead.\n";
    }

    //only charlie dead
    bob_a = true;
    charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";

    assert(true == bob_a);
    assert(false == charlie_a);
    Aaron_shoots1(bob_a, charlie_a);
    if (bob_a)
    {
        cout << "\t\tAaron misses.\n";
    }
    else
    {
        cout << "\t\tBob is dead.\n";
    }
}
//handles bob shooting given other two alive.
void Bob_shoots(bool& A_alive, bool& C_alive)
{
    //variables
    int bobProbability;
    //sets probability
    bobProbability = B_PROBABILITY;

    //gets rand int
    int shootResult = rand() % 100;

    //equates randint to probability. If true, shoots.
    if (shootResult <= bobProbability)
    {
        //most accurate dies first
        if(C_alive)
        {
            C_alive = false;
        }
        else
        {
            A_alive = false;
        }
    }
}
/*implement for prototype test_Bob_shoots();*/
void test_Bob_shoots(void)
{
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";

    //both alive
    bool aaron_a = true;
    bool charlie_a = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";

    assert(true == aaron_a);
    assert(true == charlie_a);
    Bob_shoots(aaron_a, charlie_a);
    //checks if charlie is alive. If so, bob misses (probability)
    if (charlie_a)
    {
        cout << "\t\tBob misses.\n";
    }
    else
    {
        cout << "\t\tCharlie is dead.\n";
    }

    //only bob dead
    aaron_a = false;
    charlie_a = true;
    cout << "\tCase 2: Aaron dead, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";

    assert(false == aaron_a);
    assert(true == charlie_a);
    Bob_shoots(aaron_a, charlie_a);
    //checks if charlie is alive. If so, bob misses (probability)
    if (charlie_a)
    {
        cout << "\t\tBob misses.\n";
    }
    else
    {
        cout << "\t\tCharlie is dead.\n";
    }

    //only charlie dead
    aaron_a = true;
    charlie_a = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n"
         << "\t\tBob is shooting at Aaron\n";

    assert(true == aaron_a);
    assert(false == charlie_a);
    Bob_shoots(aaron_a, charlie_a);
    if (aaron_a)
    {
        cout << "\t\tBob misses.\n";
    }
    else
    {
        cout << "\t\tAaron is dead.\n";
    }
}

//handles charlie shooting given other two alive.
void Charlie_shoots(bool& A_alive, bool& B_alive)
{
    //random number not needed since probability of hitting a shot is 100%
    //most accurate dies first
    if(B_alive)
    {
        B_alive = false;
    }
    else
    {
        A_alive = false;
    }
}

/*implement for prototype test_Charlie_shoots();*/
void test_Charlie_shoots(void)
{
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";

    //both alive
    bool aaron_a = true;
    bool bob_a = true;
    cout << "\tCase 1: Aaron alive, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";

    assert(true == aaron_a);
    assert(true == bob_a);
    Charlie_shoots(aaron_a, bob_a);
    //bob is dead (100% probability)
    cout << "\t\tBob is dead.\n";

    //only bob dead
    aaron_a = false;
    bob_a = true;
    cout << "\tCase 2: Aaron dead, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";

    assert(false == aaron_a);
    assert(true == bob_a);
    Charlie_shoots(aaron_a, bob_a);
    //bob is dead (100% probability)
    bob_a = false;
    cout << "\t\tBob is dead.\n";

    //only charlie dead
    aaron_a = true;
    bob_a = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n"
         << "\t\tCharlie is shooting at Aaron\n";

    assert(true == aaron_a);
    assert(false == bob_a);
    Charlie_shoots(aaron_a, bob_a);
    //aaron is dead
    aaron_a = false;
    cout << "\t\tAaron is dead.\n";
}

//handles aaron shooting using strategy 2 given other two alive.
void Aaron_shoots2(bool& B_alive, bool& C_alive)
{
    //variables
    int aaronProbability;
    //sets probability
    aaronProbability = A_PROBABILITY;

    /*guaranteed that either bob or charlie is dead
     * since after aaron misses, bob may miss/hit, but
     * charlie has a 100% probability of hitting
     * so either bob or charlie is dead. Of course, if
     * both are dead, aaron wins, so this wouldn't be run.
     */
    if (!B_alive || !C_alive)
    {
       //if either is dead, get rand
        int shootResult = rand() % 100;

        //equates randint to probability. If true, shoots.
        if(shootResult <= aaronProbability)
        {
            //most accurate dies first
            if (C_alive)
            {
                C_alive = false;
            }
            else
            {
                B_alive = false;
            }
        }
    }

}
/*implement for prototype test_Aaron_shoots2();*/
void test_Aaron_shoots2(void)
{
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";

    //both alive
    bool bob_a = true;
    bool charlie_a = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron intentionally misses his first shot\n";

    assert(true == bob_a);
    assert(true == charlie_a);
    Aaron_shoots2(bob_a, charlie_a);
    //both are alive since aaron misses on purpose
    cout << "\t\tBoth Bob and Charlie are alive\n";

    //only bob dead
    bob_a = false;
    charlie_a = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";

    assert(false == bob_a);
    assert(true == charlie_a);
    Aaron_shoots2(bob_a, charlie_a);
    //checks if charlie is alive. If so, bob misses (probability)
    if (charlie_a)
    {
        cout << "\t\tAaron misses.\n";
    }
    else
    {
        cout << "\t\tCharlie is dead.\n";
    }

    //only charlie dead
    bob_a = true;
    charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";

    assert(true == bob_a);
    assert(false == charlie_a);
    Aaron_shoots2(bob_a, charlie_a);
    if (bob_a)
    {
        cout << "\t\tAaron misses.\n";
    }
    else
    {
        cout << "\t\tBob is dead.\n";
    }
}