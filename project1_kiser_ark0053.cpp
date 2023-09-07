/*
 * Author: Aidan Kiser
 * UserID: ark0053
 * Filename: project1_kiser_ark0053.cpp
 * Compile: g++ project1_kiser_ark0053.cpp -o Project1.out
 * Run: ./Project1.out
 * Resources:
 * Version: 7 September 2023
 * Resources: Ppt notes & online resources for syntax, etc.
 */

 #include <iostream>
 #include <limits>
 using namespace std;
 
 int main() {
    // variables
    double loan = 0;
    double monthlyPay = 0;
    double interestRate = -1;
    double interestRateDec;
    double interest;
    double principal;
    double interestPaid;

    // formatting for currency
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    while (loan <= 0) {
        // user input
        cout << "\nLoan amount: ";
        cin >> loan;

        if (!cin) {
            cout << "\nInvalid Loan";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        if (loan < 0) {
            cout << "\nInvalid Loan";
        }
    }
    
    while (interestRate < 0) {
        // user input
        cout << "\nInterest rate (% per year): ";
        cin >> interestRate;

        if (!cin) {
            cout << "\nInvalid interest rate";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            interestRate = -1;
        }

        else if (interestRate < 0) {
            cout << "\nInvalid interest rate";
        }
    }

    // interest rate calculation
    interestRate /= 12;
    interestRateDec = interestRate / 100;

    while (monthlyPay <= 0) {
        //user input
        cout << "\nMonthly payments: ";
        cin >> monthlyPay;

        if (!cin) {
            cout << "\nInvalid monthly pay";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (monthlyPay < 0) {
            cout << "\nInvalid monthlyPay";
        }
    }

    int currentMonth = 0;
    // amortization table
    cout << "\n*****************************************************************\n"  
         << "\tAmortization Table\n" 
         << "*****************************************************************\n"  
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n"
         << currentMonth << "\t$" << loan << "\tN/A\tN/A\tN/A\t\tN/A\n";

    while (loan > 0) {
        interest = loan * interestRateDec;
        principal = monthlyPay - interest;
        loan = loan - principal;
        currentMonth++;

        if (interest > monthlyPay || monthlyPay - interest == 0) {
            cout << "\nInsufficent payment";
            break;
        }

        if (loan < 0) {
            monthlyPay = monthlyPay + loan;
            principal += loan;
            loan = 0;
        }

        interestPaid += interest;
        cout << currentMonth << "\t$" << loan << "   \t$" << monthlyPay << "\t" 
             << interestRate << "\t$" << interest << "\t\t$" << principal << "\n";
    }

    if (interest > monthlyPay || monthlyPay - interest == 0) {
        cout << endl;
    }

    else {
        cout << "*****************************************************************\n"
             << "It takes " << currentMonth << " months to pay off the loan.\n"
             << "Total interest paid: $" << interestPaid << "\n";
    }
    
    return 0;
 }