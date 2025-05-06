/*
Program:Restuarant Management.cpp
Author: Kevin Ramirez
Date: 5/5/2025
Purpose: Takes reservations, assigns to appropriate table and takes order, completes order, and calculates the pay for the order. If all complete then close.
*/

#include <iostream>
#include <string>
#include <cctype> //use for toupper or tolower
#include <limits> //only use is for my fucntion clearBuffer to use cin.ignore(numeric limit)
using namespace std;


enum itemNames{
    VeggieBurger, Hamburger, FriedChickenSliders, HamburgerSliders, VeggieSliders,
    HaddockSandwich, BLT, FauxBLT, ChickenBurrito, FalafelWrap,
    CheesePizza, PepperoniPizza, FauxMeatAndChips, FishAndChips
};


struct reservation{

    string customerName;
    int partySize;
    string time;
    bool checkedIn = false; //if reservation is checked in or not

};

struct reserveTable{

    int tableNumber;
    int maxSize;
    int peopleSeated;
    bool occupied = false; //if table is being used or not
};

struct manageOrder{

    int itemCount;
    int tableNumber;
    string customerName; //to associate with reseration
    itemNames list[10]; // max 10 items for one customer
    bool complete; //if the order is complete or not
    bool paid;  //if its paid or not

};



void displayMenu(){
    
    cout << "1. Veggie Burger $35 \n"
     << "2. Hamburger $45 \n"
     << "3. Fried Chicken Sliders $38 \n"
     << "4. Hamburger Sliders $38 \n"
     << "5. Veggie Sliders $38 \n"
     << "6. Haddock Sandwich $38 \n"
     << "7. BLT $42 \n"
     << "8. Faux BLT $42 \n"
     << "9. Chicken Burrito $42 \n"
     << "10. Falafel Wrap $42 \n"
     << "11. Cheese Pizza $59 \n"
     << "12. Pepperoni Pizza $59 \n"
     << "13. Faux Meat and Chips $77 \n"
     << "14. Fish and Chips $77 \n";
}

//function prototypes
void clearBuffer();
void makeReservation(reservation confirmed[], int& numReservation);
void checkIn(reservation confirmed[], int numReservation, int& checkingIn, reserveTable table[], int numOfTables, int& assignTable, manageOrder orders[], int& orderCount);


int main(){
    //array for table and table list availble depending on party size
    reserveTable table[20];
    int number = 1;
   
    for(int index = 0; index < 20; index++){
        if(index < 8){
            table[index] = {number++, 2, 0, false};
        }
        else if(index < 10){
            table[index] = {number++, 10, 0, false};
        }
        else if(index < 14){
            table[index] = {number++, 6, 0, false};
        }
        else if(index < 20){
            table[index] = {number++, 4, 0, false};
        }
    }
    
    //initializing array and counters
    reservation confirmed[50];
    manageOrder orders[50];
    int entryOption;
    int numReservation = 0, orderCount = 0;
    int checkingIn, assignTable;

    do{
        
            cout << "Welcome to Messijoes \n"
            << "1. Make Reservation \n"
            << "2. Check-in Reservation \n"
            << "3. Enter Order \n"
            << "4. Complete Order \n"
            << "5. Calculate and Pay Order\n";
            //<< "6. Close Restaurant \n"; (make this appear only when there no reservation or orders to complete or pay)
            cin >> entryOption;
            while(!cin || (entryOption == 1 && numReservation == 50) || entryOption < 1 || entryOption > 5)
            {
                clearBuffer();
                if(!cin.fail() || entryOption < 1 || entryOption > 5)
                {
                    cout << "Please enter a value 1-5!" << endl;
                    cin >> entryOption;
                }
                else if(entryOption == 1 && numReservation >= 50){
                    cout << "You've reached the maximun reservation";
                }
            }

        //does switch validation and goes to function
        switch(entryOption){
            case 1:
                makeReservation(confirmed, numReservation);
                cout << endl;
                break;
            case 2:
                checkIn(confirmed, numReservation, checkingIn, table, 20, assignTable, orders, orderCount);
                confirmed[checkingIn - 1].checkedIn == true;
                table[assignTable - 1].occupied == true;
                break;
            case 3: 
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                cout << "Closing the restaurant. Goodbye!" << endl;
            return 0;
        }  
    }while(true);
    
    return 0;
}

void clearBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//function that creates reservation and each that is confirmed gets stores in confirmed[]
void makeReservation(reservation confirmed[], int& numReservation){
    //instance for the struct reservation
    reservation info;

    cout << "Enter a name for the reservation: ";
    cin >> ws;
    getline(cin, info.customerName);

    cout << "Enter the number of people in the party: ";
    cin >> info.partySize;

    while(!cin || info.partySize < 1 || info.partySize > 10){
        cout << "Minimun of people per reservation is 1 and maximun of people is 10. ";
        clearBuffer(); 
        cout << endl; 
        cin >> info.partySize;
    }

    //need to create validation for HH:MM AM/PM
    cout << "Enter the time for the reservation in HH:MM AM/PM: ";
    cin >> ws;
    getline(cin, info.time);

    info.checkedIn = false; //leaves the bool checkedIn in array false

    cout << "Please Confirm the reservation. \n"
        << "Reservation Name: " << info.customerName << endl
        << "Reservation Time: " << info.time << endl
        << "Number in Party: "  << info.partySize << endl;
    
    char answer;

    cout << "Is this information correct [Y]es, [N]o (make changes), [C]ancel? ";
    cin >> answer; 
    answer = toupper(answer);

    if(answer == 'Y'){
        info.checkedIn = false;
        confirmed[numReservation] = info;
        numReservation++;  
    }
    else if(answer == 'N'){
        int change;

        while(answer == 'N')
        {
            cout << "1. Name \n"
            << "2. Number of People \n"
            << "3. Time \n"
            << "4. Cancel \n";
            cin >> change;


            if(change == 1)
            {
                cout << "Enter a name for the reservation: ";
                clearBuffer();
                cin >> ws;
                getline(cin, info.customerName);
            }
            else if(change == 2)
            {
                cout << "Enter the number of people in the party: ";
                cin >> info.partySize;
                while(!cin || info.partySize < 1 || info.partySize > 10){
                    cout << "Minimun of people per reservation is 1 and maximun of people is 10. ";
                    clearBuffer(); 
                    cout << endl; 
                    cin >> info.partySize;
                }
            }
            else if(change == 3)
            {
            cout << "Enter the time for the reservation in HH:MM AM/PM: ";
                clearBuffer();
                cin >> ws;
                getline(cin, info.time);
            }
            else if(change == 4)
            {
                continue;
            }

            cout << "Is this information correct [Y]es, [N]o (make changes), [C]ancel? ";
            cin >> answer; 
            answer = toupper(answer);
        } 
        
        if(answer == 'Y')
        {
            info.checkedIn = false;
            confirmed[numReservation] = info;
            numReservation++;
            
        }
    }

}

//function is to check in reservation and find appropriate table for number of people 
void checkIn(reservation confirmed[], int numReservation, int& checkingIn, reserveTable table[], int numOfTables, int& assignTable, manageOrder orders[], int& orderCount){
    
    //printing out reservation
    cout << "Choose the reservation to check in \n";
    for(int list = 0; list < numReservation; list++){  
        if(!confirmed[list].checkedIn)
        {
            cout << list + 1 << ": " << confirmed[list].customerName << " - " << confirmed[list].time << ", " << confirmed[list].partySize << " people \n";
        }
    }
    cin >> checkingIn;

    while(!cin || checkingIn < 1 || checkingIn > numReservation)
    {
        if(!cin){
            cout << "Invalid Input. \n";
            clearBuffer();
        }
        else if(checkingIn < 1 || checkingIn > numReservation){
            cout << "Please use number 1 through " << numReservation << endl;
        }
        cin >> checkingIn;
    }

    int count = 1;
    for(int index = 0; index < numOfTables; index++){
        table[index].tableNumber == count;
        count++;
    }

    cout << "Please assign a table: \n";
    for(int index = 0; index < numOfTables; index++){
        cout << table[index].tableNumber << ": " << table[index].maxSize << " people \n";
    }
    cin >> assignTable;

    while(!cin || assignTable < 1 || assignTable > numOfTables || confirmed[checkingIn - 1].partySize > table[assignTable - 1].maxSize){

        if(!cin){
            cout << "Invalid Input. \n";
            clearBuffer();
        }
        else if(assignTable < 1 || assignTable > numOfTables){
            cout << "Please use number 1 through " << numOfTables << endl;
        }
        else if(confirmed[checkingIn - 1].partySize > table[assignTable - 1].maxSize){
            cout << "Party size if greater than table size, choose another table. \n";
        }
        cin >> assignTable;
    }
    
}



