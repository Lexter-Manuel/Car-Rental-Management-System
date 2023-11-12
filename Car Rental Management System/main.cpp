#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <limits>
#include <cctype>
#include <algorithm>
#include <iomanip>

using namespace std;
int mainScreen(const string& username);
int main();
int admin();
void newCar();
bool isLoggedIn();
void deleteCar();
void dispCar();
void listAvailableCars();
void rentCar();
void deleteCar();
void searchCar();

void displayUserInfo(const string& username);


bool isLoggedIn(string username, string password, string checkUn, string checkPw){


    if(checkUn == username && checkPw == password){
        return true;
    }
    else {
        return false;
    }
}

string padTo(string str, const size_t num, const char paddingChar = ' ') {
    int str_size = str.size();
    for (int i=str_size; i<=num; i++) {
        str = str + paddingChar;
    }
    return str;
}

string replaceto(string text,char frm, char to){
    for(int i = 0; i< text.length();i++){
        string newtext;
            if(text[i] == frm){
                text[i] = to;
            }
    }
    return text;
}



void dispCar() {
    ifstream showCars("listOfCars.txt");
    string brand, model, fuel, type, isAvailable;
    double pricePerDay;
    int recno, seat, totalrec = 0;
    system ("CLS");
    cout << "List Of Cars in Car Rental System: "<< endl;
    cout << "   ____________________________________________________________________________________________________________" << endl ;
    cout << "   | No. |Brand                |Model                |Seat |Fuel       |Type       |Price      |Availability  |" <<" " << endl ;
    cout << "   ------------------------------------------------------------------------------------------------------------" << endl ;
    while (showCars >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable){
        brand = replaceto(brand,'_',' ');
        model = replaceto(model,'_',' ');
        isAvailable = replaceto(isAvailable,'_',' ');
        stringstream formattedPrice;
        formattedPrice << std::fixed << std::setprecision(2) << pricePerDay;
          cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
          cout << "   ------------------------------------------------------------------------------------------------------------" << endl ;
          totalrec++;

     }
     cout << "\ntotal number of Cars: "<< totalrec << endl;
}

void newCar(){
    ofstream newrec("listOfCars.txt", ios::app);
    ifstream recread("listOfCars.txt");
    string brand, model, fuel, type, newFuel, newType, newBrand, newModel;
    double pricePerDay, newPricePerDay;
    int recNo = 0, totalRec = 1, newRecNo, fuelChoice, typeChoice, seat, newSeat;
    string isAvailable, newIsAvailable;
    char availChoice;
    while (recread >> recNo >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable){
        totalRec++;
    }
    recread.close();

    system("CLS");

    cout << "\tADDING NEW CAR";
    cout << "\nEnter Car Brand : ";
    getline(cin>>ws,newBrand);
    cout << "\nEnter Brand Model : ";
    getline(cin>>ws,newModel);
    cout << "\nEnter Number of Seat(s): ";
    cin >> newSeat;
    fChoice:
    cout << "\nEnter Fuel([1]Diesel [2]Gasoline): ";
    cin >> fuelChoice;
    if (fuelChoice == 1){
        newFuel = "Diesel";
    }
    else if (fuelChoice == 2){
        newFuel = "Gasoline";
    }
    else {
        cout << "Invalid input";
        goto fChoice;
    }
    tChoice:
    cout << "\nEnter Type([1]Automatic [2]Manual): ";
    cin >> typeChoice;
    if (typeChoice == 1){
        newType = "Automatic";
    }
    else if (typeChoice == 2){
        newType = "Manual";
    }
    else {
        cout << "Invalid input";
        goto tChoice;
    }
    cout << "\nEnter Car's Price per day : ";
    cin >> newPricePerDay;
    carAvail:
    cout << "\nWill it be available for rent(y/n) : ";          //Manual or automatic, diesel,
    cin >> availChoice;
    if(availChoice == 'y' || availChoice == 'Y'){
        newIsAvailable = "Available";
    }
    else if (availChoice == 'n' || availChoice == 'N'){
        newIsAvailable = "Not_Available";
    }
    else {
        cout << "Invalid Input!";
        goto carAvail;
    }
    system("CLS");
    newBrand = replaceto(newBrand,' ','_');
    newModel = replaceto(newModel,' ','_');
    newRecNo = totalRec++;
    newrec << endl << newRecNo << "   " << newBrand << "   " << newModel << "   " << newSeat << "   " << newFuel << "   " << newType << "   " << fixed << setprecision(2) << newPricePerDay << "   " << newIsAvailable;
    newrec.close();
}

void deleteCar() {
    system("cls");
    dispCar();
    int recno;
    cout << "Enter the record number of the car you want to delete: ";
    cin >> recno;

    ifstream carData("listOfCars.txt");
    ofstream tempFile("temp.txt");

    string brand, model, fuel, type, isAvailable;
    double pricePerDay;
    int currentRecno, seat;
    bool carFound = false;

    while (carData >> currentRecno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
        if (currentRecno == recno) {
            carFound = true;
            cout << "Car with record number " << recno << " has been deleted." << endl;
        } else {
             tempFile << currentRecno - (currentRecno > recno) << "   " << brand << "  " << model << "   " << seat << "   " << fuel << "   " << type << "   " << fixed << setprecision(2) << pricePerDay << "   " << isAvailable << endl;
        }
    }

    carData.close();
    tempFile.close();

    if (carFound) {
        remove("listOfCars.txt");
        rename("temp.txt", "listOfCars.txt");
    } else {
        cout << "Car not found." << endl;
    }
}

int pickNumberToChange;

void chooseChange(){
    cout << "\nEnter what you want to change: ";
    cout << "\n1. Brand";
    cout << "\n2. Model";
    cout << "\n3. Seat";
    cout << "\n4. Fuel";
    cout << "\n5. Type";
    cout << "\n6. Price";
    cout << "\n7. Availability";
    cout << "\n---------------------------\nChoice: ";
    cin >> pickNumberToChange;

    while (pickNumberToChange < 1 || pickNumberToChange > 7) {
        cout << "Invalid input. Please choose a number between 1 and 7: ";
        cin >> pickNumberToChange;
    }
}

void updateCar(){
    dispCar();

    string brand, model, fuel, type, newFuel, newType, newBrand, newModel, isAvailable, newIsAvailable, change, fBrand, fModel;
    bool found = false;
    double pricePerDay, newPricePerDay;
    int recno, upNum, pick, fuelChoice, typeChoice, seat, newSeat;
    char availChoice;

    ifstream carRead("listOfCars.txt");
    ofstream editCar("temp.txt", ios::app);

    while(true){
        cout << endl << "Search for what you want to update by: " << endl;
        cout << "1. Record number" << endl;
        cout << "2. Brand and model" << endl;
        pickChoice:
        cout << "--------------------------------";
        cout << endl << "Choice: ";
        while (!(cin >> pick)) {
            cout << "Invalid input. Please enter a numeric choice: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        switch(pick){
    case 1:
        cout << "Enter record number to update: ";
            while (!(cin >> upNum)) {
                cout << "Invalid input. Please enter a numeric value: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        break;
    case 2:
        cout << "Enter the brand and model of the car you want to update: ";
        cout << "\nEnter brand: "; cin >> fBrand;
        cout << "\nEnter model: "; cin >> fModel;
        break;
    default: cout << "Invalid Choice" << endl;
            continue;
        }

    while(carRead >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable){
        if((pick == 1 && recno == upNum) || (pick == 2 && brand == fBrand && model == fModel)){
            found = true;
            chooseChange();
            switch(pickNumberToChange){
        case 1:
            cout << "Enter new brand: ";
            cin >> newBrand;
            newModel = model;
            newSeat = seat;
            newFuel = fuel;
            newType = type;
            newPricePerDay = pricePerDay;
            newIsAvailable = isAvailable;

            break;
        case 2:
            cout << "Enter new model: ";
            cin >> newModel;
            newBrand = brand;
            newSeat = seat;
            newFuel = fuel;
            newType = type;
            newPricePerDay = pricePerDay;
            newIsAvailable = isAvailable;

            break;
        case 3:
            cout << "Enter new seat(s): ";
            cin >> newSeat;
            newBrand = brand;
            newModel = model;
            newFuel = fuel;
            newType = type;
            newPricePerDay = pricePerDay;
            newIsAvailable = isAvailable;
            break;
        case 4:
            fChoice:
            cout << "\nEnter new Fuel([1]Diesel [2]Gasoline): ";
            cin >> fuelChoice;
            if (fuelChoice == 1){
                newFuel = "Diesel";
            }
            else if (fuelChoice == 2){
                newFuel = "Gasoline";
            }
            else {
                cout << "Invalid input";
                goto fChoice;
            }
            newBrand = brand;
            newModel = model;
            newSeat = seat;
            newType = type;
            newPricePerDay = pricePerDay;
            newIsAvailable = isAvailable;

            break;
        case 5:
            tChoice:
            cout << "\nEnter new Type([1]Automatic [2]Manual): ";
            cin >> typeChoice;
            if (typeChoice == 1){
                newType = "Automatic";
            }
            else if (typeChoice == 2){
                newType = "Manual";
            }
            else {
                cout << "Invalid input";
                goto tChoice;
            }
            newBrand = brand;
            newModel = model;
            newSeat = seat;
            newFuel = fuel;
            newPricePerDay = pricePerDay;
            newIsAvailable = isAvailable;
            break;
        case 6:
            cout << "Enter new price: ";
            cin >> newPricePerDay;
            newBrand = brand;
            newModel = model;
            newSeat = seat;
            newFuel = fuel;
            newType = type;
            newIsAvailable = isAvailable;

            break;
        case 7:
            carAvail:
            cout << "\nWill it be available for rent(y/n) : ";
            cin >> availChoice;
            if(availChoice == 'y' || availChoice == 'Y'){
                newIsAvailable = "Available";
            }
            else if (availChoice == 'n' || availChoice == 'N'){
                newIsAvailable = "Not_Available";
            }
            else {
                cout << "Invalid Input!";
                goto carAvail;
            }
            newBrand = brand;
            newModel = model;
            newSeat = seat;
            newFuel = fuel;
            newType = type;
            newPricePerDay = pricePerDay;
            break;
        default:
            cout << "Invalid input" << endl;
        }

        newModel = replaceto(newModel,' ','_');
        newBrand = replaceto(newBrand,' ','_');
        editCar << recno << "   " << newBrand << "   " << newModel << "   " << newSeat << "   " << newFuel << "   " << newType << "   " << fixed << setprecision(2) << newPricePerDay << "   " << newIsAvailable << "\n";
       }
        else{
            newModel = replaceto(newModel,' ','_');
            newBrand = replaceto(newBrand,' ','_');
            editCar << recno << "   " << brand << "   " << model << "   " << seat << "   " << fuel << "   " << type << "   " << fixed << setprecision(2) << pricePerDay << "   " << isAvailable << "\n";
        }
    }

    carRead.close();
    editCar.close();

    ifstream carRead2("temp.txt",ios::in);
    ofstream editCar2("listOfCars.txt", ios::binary);
    while (carRead2 >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable){
            editCar2 << "\n" <<recno << "   " << brand << "   " << model << "   " << seat << "   "  << fuel << "   " << type << "   " << fixed << setprecision(2) << pricePerDay << "   " << isAvailable << "\n";
    }
    carRead2.close();
    editCar2.close();
    if(found){
        cout << "Successfully updated!\n";
    }
    else {
        cout << "Unit not found" << endl;
    }
    if (remove("listOfCars.txt") != 0) {
            perror("Error deleting file");
        }
    if (rename("temp.txt", "listOfCars.txt") != 0) {
            perror("Error renaming file");
        }
        cout << "Do you want to continue updating? (yes/no): ";
        string userChoice;
        cin >> userChoice;

        if (userChoice != "yes" && userChoice != "Yes") {
            break;
        }
    }
}

int main(){
    char yn;
    do {
    int choice, endReg, license;
    string uname, pass, un, pw, fn, mn, ln, email, cNum;
    cout << " ________________________________________________\n";
    cout << "|          Car Rental System Login Page          |\n";
    cout << " ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "| 1: Register an account                         |\n";
    cout << "| 2. Login account                               |\n";
    cout << "| 3. Admin Login                                 |\n";
    cout << "| 4. Exit Program                                |\n";
    cout << "|                                                |\n";
    cout << " ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "  Enter Choice: "; cin >> choice; cin.ignore();
    cout << "|                                                |\n";
    cout << " ________________________________________________\n";
    if(choice == 1){
        cout << "Enter your desired username: ";
        getline(cin >> ws, uname);
        cout << "Enter your password: ";                    //First name, middle name, last name, driver's license id number, contact number, email
        getline(cin >> ws, pass);
        if (uname == "admin" || pass == "admin"){
            cout << "You entered an admin account or exclusive admin password. Please enter valid user account username and password.\n\n";
            system("PAUSE");
            system("CLS");
            main();
        }
        else{
            system("CLS");
            cout << "Enter your First Name: ";
            getline(cin >> ws, fn);
            cout << "Enter your Middle Initial: ";
            getline(cin >> ws, mn);
            cout << "Enter your Last Name: ";
            getline(cin >> ws, ln);
            cout << "Enter your Driver License's Number: ";
            cin >> license;
            cout << "Enter your Email Address: ";
            getline(cin >> ws, email);
            while(true){
                cout << "Enter your Contact Number: ";
                cin >> cNum;
                if (cNum.length() == 11 && all_of(cNum.begin(), cNum.end(), ::isdigit)) {
                    break;
                    } else {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid 11-digit contact number." << endl;
                    }
                }
            }
            ofstream file;
            file.open(uname + ".txt");
            file << uname << endl << pass << endl << fn << endl << mn << endl << ln << endl << license << email << endl << cNum;
            file.close();
            cout << "\nHere are your informations: " << endl;
            cout << "Full Name: " << fn << " " << mn << " " << ln << endl;
            cout << "Driver License's Number: " << license << endl;
            cout << "Email Address: " << email << endl;
            cout << "Contact Number: " << cNum << endl;
            cout << " ________________________________________________\n";
            cout << "|        ACCOUNT SUCCESSFULLY REGISTERED!        |\n";
            cRep:
            cout << " ________________________________________________\n";
            cout << "|1. Go back to Login/Registraion Page            |\n";
            cout << "|2. Exit Program                                 |\n";
            cout << " ________________________________________________\n";
            cout << "Your choice: ";
            cin >> endReg;
            if(endReg == 1){
                system("CLS");
                main();
            }
            else if (endReg == 2){
                cout << "Thank you for using our program!\n\n";
                return 0;
            }
            else {
                cout << "Invalid choice\n\n";
                goto cRep;
            }
        }
    else if (choice == 2){
    cout << "\nEnter username: ";
    getline(cin >> ws, uname);
    cout << "Enter password: ";
    getline(cin >> ws, pass);
    cout << " ________________________________________________\n";
    ifstream read(uname + ".txt");
    getline(read, un);
    getline (read, pw);
        bool status = isLoggedIn(uname, pass, un, pw);
        if (!status){
            if(un == "admin"){
                cout << "You entered an admin account. Please enter a valid user account.\n\n";
                system("PAUSE");
                system("CLS");
                main();
            }
            else{
                cout << "\nPlease check if you entered your username and password correctly." << endl;
                system("PAUSE");
                system("CLS");
                main();
            }
        }

        else {
                cout << "\nSuccessfully logged in!" << endl;
                system("PAUSE");
                system("CLS");
                mainScreen(uname);
            }
    }
else if (choice == 3) {
    cout << "Please enter username: ";
    getline(cin >> ws, uname);
    cout << "Please enter password: ";
    getline(cin >> ws, pass);
    if (uname == "admin" && pass == "admin"){
        admin();
    }
    else {
        cout << "Login Failed!\n";
        system("PAUSE");
        system("CLS");
        main();
    }
}
else if (choice == 4) {
    return 0;
}
else {
    cout << "Invalid choice! \n";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Do you want to continue(y/n)? ";
    cin >> yn;
    system("CLS");
    }

    }while(yn == 'y' || yn == 'Y');
}


void listAvailableCars() {
    system("cls");
    ifstream carData("listOfCars.txt");
    string brand, model, fuel, type, isAvailable;
    double pricePerDay;
    int recno, totalrec = 0, seat;

    system("CLS");
    cout << "List Of Available Cars in Car Rental System: " << endl;
    cout << "   ____________________________________________________________________________________________________________" << endl ;
    cout << "   | No. |Brand                |Model                |Seat |Fuel       |Type       |Price      |Availability  |" <<" " << endl ;
    cout << "   ------------------------------------------------------------------------------------------------------------" << endl ;
    while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
        if (isAvailable == "Available") {
        brand = replaceto(brand,'_',' ');
        model = replaceto(model,'_',' ');
        isAvailable = replaceto(isAvailable,'_',' ');
        stringstream formattedPrice;
        formattedPrice << std::fixed << std::setprecision(2) << pricePerDay;
          cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
          cout << "   ------------------------------------------------------------------------------------------------------------" << endl ;
          totalrec++;
        }
    }

    cout << "\ntotal number of Cars: " << totalrec << endl;
}

void rentCar() {
    int recno;
    cout << "Enter the record number of the car you want to rent: ";
    cin >> recno;

    ifstream carData("listOfCars.txt");
    ofstream tempFile("temp.txt");

    string brand, model, fuel, type, isAvailable;
    double pricePerDay;
    int currentRecno, seat;
    bool carFound = false;

    while (carData >> currentRecno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
        if (currentRecno == recno) {
            if (isAvailable == "Available") {
                isAvailable = "Not_Available";
                carFound = true;
            } else {
                cout << "This car is already rented." << endl;
            }
        }

        tempFile << currentRecno << "   " << brand << "   " << model << "   " << seat << "   " << fuel << "   " << type << "   " << fixed << setprecision(2) << pricePerDay << "   " << isAvailable << endl;
    }

    carData.close();
    tempFile.close();

    if (carFound) {
        remove("listOfCars.txt");
        rename("temp.txt", "listOfCars.txt");
        cout << "Car rented successfully." << endl;
    } else {
        cout << "Car not found or is already rented." << endl;
    }
}

void listRentedCars() {
    ifstream carData("listOfCars.txt");
    string brand, model, fuel, type, isAvailable;
    double pricePerDay;
    int recno, totalrec = 0, seat;

    system("CLS");
    cout << "List Of Rented Cars in Car Rental System: " << endl;
    cout << "   ____________________________________________________________________________________________________________" << endl ;
    cout << "   | No. |Brand                |Model                |Seat |Fuel       |Type       |Price      |Availability  |" <<" " << endl ;
    cout << "   ------------------------------------------------------------------------------------------------------------" << endl ;
    while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
        if (isAvailable == "Not_Available") {
        brand = replaceto(brand,'_',' ');
        model = replaceto(model,'_',' ');
        isAvailable = replaceto(isAvailable,'_',' ');
        stringstream formattedPrice;
        formattedPrice << std::fixed << std::setprecision(2) << pricePerDay;
          cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
          cout << "   ------------------------------------------------------------------------------------------------------------" << endl ;
          totalrec++;
        }
    }

    cout << "\ntotal number of Rented Cars: " << totalrec << endl;
}

void returnCar() {
    int recno;
    system("cls");
    listRentedCars();
    cout << "Enter the record number of the car you want to return: ";
    cin >> recno;

    ifstream carData("listOfCars.txt");
    ofstream tempFile("temp.txt");

    string brand, model, fuel, type, isAvailable;
    double pricePerDay;
    int currentRecno, seat;
    bool carFound = false;

    while (carData >> currentRecno >> brand >> model >>  seat >> fuel >> type >> pricePerDay >> isAvailable) {
        if (currentRecno == recno) {
            if (isAvailable == "Not_Available") {
                isAvailable = "Available";
                carFound = true;
            } else {
                cout << "This car is already available." << endl;
            }
        }

        tempFile << currentRecno << "   " << brand << "   " << model << "   " <<  seat << "   " << fuel << "   " << type << "   " << fixed << setprecision(2) << pricePerDay << "   " << isAvailable << endl;
    }

    carData.close();
    tempFile.close();

    if (carFound) {
        remove("listOfCars.txt");
        rename("temp.txt", "listOfCars.txt");
        cout << "Car returned successfully." << endl;
    } else {
        cout << "Car not found or is already available." << endl;
    }
}

int mainScreen(const string& username)
{
    system("cls");
    listAvailableCars();
    int choose;
    cout << " ________________________________________________\n";
    cout << "|-     Car Rental Management System             -|" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "|-               Please choose                  -|" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "| 1. Display All Cars in the List                |" << endl;
    cout << "| 2. Search for Specific Attribute of the Car    |" << endl;
    cout << "| 3. Rent A Car                                  |" << endl;
    cout << "| 4. Display User Information                    |" << endl;
    cout << "| 5. Exit Program                                |" << endl;
    cout << " ________________________________________________\n";
    cout << "Enter choice: ";
    cin >> choose;

    switch(choose){
case 1:
    dispCar();
    system("pause");
    mainScreen(username);
    break;
/*case 2:
    listAvailableCars();
    system("pause");
    mainScreen();
    break;*/
case 2:
    searchCar();
    system("pause");
    mainScreen(username);
    break;
case 3:
    listAvailableCars();
    rentCar();
    system("pause");
    mainScreen(username);
    break;
case 4:
    {
    displayUserInfo(username);
    system("pause");
    mainScreen(username);
    break;
    }
case 5:
    return 0;
default:
    cout << "Invalid Input!";
    }

    return 0;
}

int admin(){
    adminScreen:
    system("CLS");
    int adminChoose;
    cout << " ________________________________________________\n";
    cout << "|                     ADMIN                      |\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "|    Welcome Admin, what do you want to do?      |\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "| 1. Add Car(s) For Car Rental System            |\n";
    cout << "| 2. Display Car(s) for Car Rental System        |\n";
    cout << "| 3. Update Car(s) for Car Rental System         |\n";
    cout << "| 4. Delete Car(s) for Car Rental System         |\n";
    cout << "| 5. Return a Car                                |\n";
    cout << "| 6. Go Back to Login/Registration Page          |\n";
    cout << "| 7. Exit Program                                |\n";
    cout << " ________________________________________________\n";
    cout << " Please Choose: ";
    cin >> adminChoose;

    switch(adminChoose){
case 1:
    newCar();
    system("pause");
    admin();
    break;
case 2:

    dispCar();
    int yesno;
    do{
    cout << endl << "Do you want to search for specific attribute?\n1.Yes\n2.No\nYour Choice: ";
        if (!(cin >> yesno)) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            continue;
        }
    }while (yesno != 1 && yesno != 2);;
        if(yesno == 1){
        system("cls");
        searchCar();
        system("pause");
        admin();
        break;
        }else if(yesno == 2) {
            system("pause");
            admin();
            break;
        }else {
            cout << "Invalid input!" << endl;
            system("pause");
            admin();
            break;
        }
case 3:
    updateCar();
    system("pause");
    admin();
    break;
case 4:
    deleteCar();
    system("pause");
    admin();
    break;
case 5:
    returnCar();
    system("pause");
    admin();
    break;
case 6:
    system("cls");
    main();
    break;
case 7:
    return 0;
    break;
default:
    cout << "Invalid Input!";
    goto adminScreen;
    }
}


void displayUserInfo(const string& username)
{
    ifstream userFile(username + ".txt");
    string uname, pass, fn, mn, ln, email, cNum;
    int license;

    if (userFile.is_open()) {
        system("cls");
        getline(userFile, uname);
        getline(userFile, pass);
        getline(userFile, fn);
        getline(userFile, mn);
        getline(userFile, ln);
        userFile >> license;
        userFile.ignore();
        getline(userFile, email);
        getline(userFile, cNum);

        cout << "\nUser Information for: " << username << endl;
        cout << "Full Name: " << fn << " " << mn << " " << ln << endl;
        cout << "Driver License's Number: " << license << endl;
        cout << "Email Address: " << email << endl;
        cout << "Contact Number: " << cNum << endl;
        userFile.close();
    } else {
        cout << "Error: Unable to open user file." << endl;
    }
}

void searchCar() {
    int searchChoice;
    cout << " ________________________________________________\n";
    cout << "|             Search for Cars                     |\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "|    Choose attribute to search:                  |\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "| 1. Brand                                       |\n";
    cout << "| 2. Model                                       |\n";
    cout << "| 3. Seat                                        |\n";
    cout << "| 4. Fuel                                        |\n";
    cout << "| 5. Type                                        |\n";
    cout << "| 6. Price                                       |\n";
    cout << "| 7. Availability                                |\n";
    cout << "| 8. Back to Main Menu                           |\n";
    cout << " ________________________________________________\n";
    cout << " Your choice: ";
    cin >> searchChoice;

    ifstream carData("listOfCars.txt");
    string brand, model, fuel, type, isAvailable;
    double pricePerDay;
    int recno, seat;
    stringstream formattedPrice;
    formattedPrice << std::fixed << std::setprecision(2) << pricePerDay;

    switch (searchChoice) {
        case 1: {
            string searchBrand;
            cout << "Enter Brand to search: ";
            cin >> searchBrand;

            while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
                if (brand.find(searchBrand) != string::npos) {
                    cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
                    }
            }
            break;
        }
        case 2: {
            string searchModel;
            cout << "Enter Model to search: ";
            cin >> searchModel;

            while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
                if (model.find(searchModel) != string::npos) {
                    cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
                    }
            }
            break;
        }
        case 3: {
            int searchSeat;
            cout << "Enter Seat to search: ";
            cin >> searchSeat;

            while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
                if (seat == searchSeat) {
                    cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
                    }
            }
            break;
        }
        case 4: {
            string searchFuel;
            cout << "Enter Fuel to search: ";
            cin >> searchFuel;

            while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
                if (fuel.find(searchFuel) != string::npos) {
                    cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
                    }
            }
            break;
        }
        case 5: {
            string searchType;
            cout << "Enter Type to search: ";
            cin >> searchType;

            while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
                if (type.find(searchType) != string::npos) {
                   cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
                 }
            }
            break;
        }
        case 6: {
            double searchPrice;
            cout << "Enter Price to search: ";
            cin >> searchPrice;

            while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
                if (pricePerDay == searchPrice) {
                    cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
                    }
            }
            break;
        }
        case 7: {
            string searchAvail;
            cout << "Enter Availability to search: ";
            cin >> searchAvail;

            while (carData >> recno >> brand >> model >> seat >> fuel >> type >> pricePerDay >> isAvailable) {
                if (isAvailable == searchAvail) {
                    cout << "   |" << padTo(to_string(recno),3) << " " <<  padTo("|"+brand,20) <<" " << padTo("|"+model,20) <<" " << padTo("|"+to_string(seat), 5)
                 << padTo("|"+fuel,10) << " " << padTo("|"+type,10) <<" " << padTo("|"+formattedPrice.str(),10)  << " " << padTo("|"+isAvailable,14) <<"|" << endl ;
                }
            }
            break;
        }


        case 8:
            break;

        default:
            cout << "Invalid Choice!" << endl;
    }

    carData.close();
}
