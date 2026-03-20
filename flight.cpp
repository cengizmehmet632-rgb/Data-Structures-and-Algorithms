#include "Flight.h"

using namespace std;

int main(){
    FlightManager manager;
    int choice;

    while(true){
        cout << "\n===== Flight Management System =====\n";
        cout << "\n1. Add Flight\n2. Remove Flight\n3. List Flights\n4. Select Flight\n5. Exit\n";
        cin >> choice;

        if(choice == 1){
            string no, dest;
            cout << "Flight No: "; cin >> no;
            cout << "Destination: "; cin >> dest;

            if(!isValidFlightNo(no)){
                cout << "Invalid flight number!\n";
                continue;
            }

            Flight f(no, dest);
            manager.addFlight(f);
        }

        else if(choice == 2){
            string no;
            cout << "Enter flight number: ";
            cin >> no;

            manager.removeFlight(no);
        }

        else if(choice == 3){
            manager.listAllFlights();
        }

        else if(choice == 4){
            string no;
            cout << "Enter flight number: ";
            cin >> no;

            Flight* f = manager.getFlightByFlightNo(no);

            if(!f){
                cout << "Flight not found!\n";
                continue;
            }

            int sub;
            while(true){
                cout << "\n1. Reserve\n2. Cancel\n3. List\n4. Back\n";
                cin >> sub;

                if(sub == 1){
                    f->printSeatingPlan();

                    string name, surname, seat;
                    char gender;

                    cout << "Name: "; cin >> name;
                    cout << "Surname: "; cin >> surname;
                    cout << "Gender: "; cin >> gender;
                    
                    do{
                        cout << "Seat: "; cin >> seat;
                        for(size_t i=0; i<seat.length(); i++) seat[i] = toupper(seat[i]);

                    }while(!isValidSeat(seat,f->getMaxSeats()));

                    Passenger p(name, surname, gender, seat);
                    f->reserveSeat(p, seat);
                }

                else if(sub == 2){
                    string name, surname, seat;
                    char gender;

                    cout << "Name: "; cin >> name;
                    cout << "Surname: "; cin >> surname;
                    cout << "Gender: "; cin >> gender;
                    
                    do{
                        cout << "Seat: "; cin >> seat;
                        for(size_t i=0; i<seat.length(); i++) seat[i] = toupper(seat[i]);

                    }while(!isValidSeat(seat,f->getMaxSeats()));

                    Passenger p(name, surname, gender, seat);
                    f->cancelReservation(p);
                }

                else if(sub == 3){
                    f->printPassengers();
                }

                else break;
                }
                }

                else if(choice == 5){
                    cout << "Exit the flight management system.\n";
                    break;
                }
    }
    return 0;
}