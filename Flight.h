#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Passenger{
private:
    string name;
    string surname;
    char gender;
    string seat;
public:
    Passenger(string n=" ",string s=" ",char gen= 'U',string st=""):
        name(n),surname(s),gender(gen),seat(st) {}
    
    void setName(string s){ name = s;}
    void setSurname(string s){ surname = s;}
    void setGender(char s){ gender = s;}
    void setSeat(string s) { seat = s;}

    string getName(void) const { return name; }
    string getSurname(void) const { return surname; }
    char getGender(void) const { return gender; }
    string getSeat(void) const { return seat;}

    bool operator==(const Passenger& pass) const {
        return (name == pass.getName() && 
        surname == pass.getSurname() && 
        gender == pass.getGender() && 
        seat == pass.getSeat());
    }

    friend ostream& operator<<(ostream& out,const Passenger& pass);
};

    ostream& operator<<(ostream& out,const Passenger& pass) {
        out << "Name: " << pass.getName() 
            << " | Surname: " << pass.getSurname() 
            << " | Gender: " << pass.getGender() 
            << " | Seat: " << pass.getSeat() << endl;

        return out;
    }

class Flight{
private: 
    string flightNo;
    string destination;
    size_t maxSeats=40;
    vector<Passenger> passengers;
public:

    Flight(string no="", string dest="", size_t seats=40)
    : flightNo(no), destination(dest), maxSeats(seats){}

    void setFligtNo(string g) { flightNo = g; }
    void setDestination(string d) { destination = d; }
    void setMaxSeats(size_t m) { maxSeats = m; }

    string getFlightNo(void) const { return flightNo; }
    string getDestination(void) const { return destination; }
    size_t getMaxSeats(void) const { return maxSeats; }
    int getNumberOfPassengers(void) const { return passengers.size(); }

    bool isSeatOccupied(const string& seat) const {
        size_t i = passengers.size();

        for(size_t j = 0; j<i; j++){
            if(passengers.at(j).getSeat() == seat) return true;
        }
        return false;
    }

    void reserveSeat(Passenger& pass, const string& seat) {
        if(passengers.size() >= maxSeats) {
            cout << "Capacity is full. Reservation failed.\n";
            return;
        }

        size_t j = passengers.size();
        for(size_t i=0; i<j; i++){
            if(passengers[i] == pass){
                cout << "Passenger already exists.\n";
                return;
            }
        }

        if(isSeatOccupied(seat)){
            cout << "Seat is already taken.\n";
            return;
        }

        pass.setSeat(seat);

        passengers.push_back(pass);

        cout << "Reservation successful.\n";
    }

    void cancelReservation(const Passenger& pass){
        if(passengers.empty()){
            cout << "No passengers to cancel.\n";
            return;
        }
        
        size_t i = passengers.size();
        for(size_t j=0; j<i; j++){
           if(passengers[j] == pass){
                passengers.erase(passengers.begin() + j);
                cout << "Reservation canceled successfully.\n";
            return;
            }
        }
        cout << "Reservation not found.\n";
    }

    void printPassengers(void) const {
        if(passengers.empty()){
            cout << "No passenger." << endl;
            return;
        }

        cout << "Seat | Passenger Name | Gender\n";
        cout << "-----|----------------|------\n";

        int j = passengers.size();

        for(int i=0; i<j; i++){
        string fullName = passengers.at(i).getName() + " " + passengers.at(i).getSurname();
        if(fullName.length() > 15)
            fullName = fullName.substr(0,14) + ".";
        cout.width(5); cout << left << passengers.at(i).getSeat() << "|";
        cout.width(16); cout << left << fullName << "|";
        cout.width(1); cout << left << passengers.at(i).getGender() << "\n";
        }
    }

    bool isFlyingTo(const string& dest) const {
        return (destination == dest);
    }

    bool operator==(const Flight& f) const {
        return (f.flightNo == flightNo);
    }

    void printSeatingPlan(void) const {
        int rows = maxSeats / 4;

        cout << "-------------Front------------\n";
        
        for(int i=1; i <= rows; i++){
            for(char c = 'A'; c <= 'D'; c++){
                string seat = to_string(i) + c;

                if(isSeatOccupied(seat))
                    cout << "| " << seat << " X ";
                else
                    cout << "| " << seat << " O ";

                if(c == 'B') cout << "| ";
            }
            cout << "|\n";
        }
    }
};

bool isValidSeat(const string& seat, int maxSeats){
    if(seat.length() < 2) return false;

    char col = seat.back();
    if(col < 'A' || col > 'D') return false;

    int row = stoi(seat.substr(0, seat.length()-1));
    int maxRow = maxSeats / 4;

    return (row >= 1 && row <= maxRow);
}

bool isValidFlightNo(const string& fn){
    if(fn.length() < 3 || fn.length() > 6) return false;

    string code = fn.substr(0,2);
    if(code != "TK" && code != "PG") return false;

    for(size_t i=2; i<fn.length(); i++){
        if(!isdigit(fn[i])) return false;
    }

    return true;
}

class FlightManager{
private:
    vector<Flight> flights;
public:
    void addFlight(const Flight& f){
        size_t i = flights.size();
        for(size_t j=0; j<i; j++){
            if(f == flights.at(j)){
                cout << "Flight is already exist." << endl;
                return;
            }
        }
        flights.push_back(f);
        cout << "Flight is added." << endl;
    }

    void removeFlight(const string& flightNum){
        if(flights.empty()) {
            cout << "No flights.";
            return;
        }
        size_t i = flights.size();
        for(size_t j=0; j<i; j++){
            if(flights.at(j).getFlightNo( ) == flightNum){
                flights.erase(flights.begin() + j);
                cout << "Flight " << flightNum << " removed.\n" << endl;
                return;
            }
        }
        cout << "Flight " << flightNum << " doesnt exist.\n";
    }

    void listAllFlights() const {
        if(flights.empty()) {
            cout << "No flights available.\n";
            return;
        }

        cout << left << setw(10) << "FlightNo" 
         << " | " << left << setw(12) << "Destination" 
         << " | " << left << setw(16) << "Seats Available" << endl;

        cout << "-----------|--------------|-----------------\n";

        int j = flights.size();
        for(int i=0; i<j; i++){
            cout << left << setw(10) << flights.at(i).getFlightNo() 
                << " | " << left << setw(12) << flights.at(i).getDestination() 
                << " | " << left << setw(16) << flights.at(i).getMaxSeats() - flights.at(i).getNumberOfPassengers() 
                << endl;
        }
    }

    Flight* getFlightByDestination(const string& destination){
        size_t j = flights.size();
        for(size_t i=0; i<j; i++){
            if(flights.at(i).getDestination() == destination){
                return &flights.at(i);
            }
        }
        return nullptr;
    }

    Flight* getFlightByFlightNo(const string& flightNumber){
        size_t j = flights.size();
        for(size_t i=0; i<j; i++){
            if(flights.at(i).getFlightNo() == flightNumber){
                return &flights.at(i);
            }
        }
        return nullptr;
    }

};  