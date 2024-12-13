#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//this function for pass validation.
bool Password_Validity(const string &password) {
    if(password.length()<8){
        cout <<"Password must be at least 8 characters long.\n";
        return false;
    }
   bool Upper = false, Lower = false, Digit = false, SpecialChar = false;


    for (int i=0;i<password.length();i++){
        char ch=password[i];
        if(ch>='A'&& ch<='Z') {
            Upper =true;
        }
        else if(ch>='a'&&ch<='z'){
            Lower =true;
        }
        else if(ch>='0'&&ch<='9') {
            Digit =true;
        }
        else {
            SpecialChar =true; 
        }
    }

    if(!Upper){
        cout <<"Password must include at least one uppercase letter.\n";
        return false;
    }
    if (!Lower) {
        cout << "Password must include at least one lowercase letter.\n";
        return false;
    }
    if (!Digit) {
        cout << "Password must include at least one digit.\n";
        return false;
    }
    if (!SpecialChar) {
        cout << "Password must include at least one special character.\n";
        return false;
    }
    return true;
}

class save_file {
public:
    void save_user_to_file(long account_number, const string &full_name, const string &dob,const string &nationality, const string &gender, const string &password) {
        ofstream write("customer_data.txt", ios::app);
        if (!write) {
            cout << "Error: Unable to open file for writing.\n";
            return;
        }
        write << account_number << " " << full_name << " " << dob << " "<< nationality << " " << gender << " " << password << endl;
        write.close();
    }

    void save_transaction(long account_number, const double &balance, const string &type) {
    ofstream write("transactions.txt", ios::app);
    if (!write) {
        cout << "Error: Unable to open file for writing.\n";
        return;
    }
    write << account_number << " | " << type << ": " << balance << endl;
    write.close();
}


    void update_balance(long account_number, double new_balance) {
    ifstream file("balances.txt");
    ofstream temp("temp.txt");
    bool found = false;

    long acc;
    double bal;
    while (file >> acc >> bal) {
        if (acc == account_number) {
            temp << acc << " " << new_balance << endl;
            found = true;
        } else {
            temp << acc << " " << bal << endl;
        }
    }

    if (!found) {
        temp << account_number << " " << new_balance << endl;
    }

    file.close();
    temp.close();
    remove("balances.txt");
    rename("temp.txt", "balances.txt");
}


    double get_balance(long account_number) {
    ifstream file("balances.txt");
    if (!file) {
        cout << "Error";
    }

    long acc;
    double bal;
    while (file >> acc >> bal) {
        if (acc == account_number) {
            return bal;
        }
    }
    return 0.0;
}
};



class display_chart{
public:
string name;
void show_first_chart(){
    cout<<"\n---->>Bank System<<----"<<endl;
    cout << "1: Customer Section"<<endl;
    cout << "2: Employee Section"<<endl;
    cout << "3: Help Section"<<endl;
    cout << "4: Exit"<<endl;
    cout << "Enter your choice: >>";
}
void ask_for_login() {
    cout<<"----->>Bank Manu<<-----"<<endl;
    cout << "1: Sign Up"<<endl;
    cout << "2: Login"<<endl;
    cout << "3: View All Users (Admin only)"<<endl;
    cout << "4: Back"<<endl;//exit cilo
    cout << "Enter your choice: >>";
    }
    void show_user_chart() {
        cout << "1: Deposit"<<endl;
        cout << "2: Withdraw"<<endl;
        cout << "3: Show Details"<<endl;
        cout << "4: Loan Request"<<endl;
        cout << "5: Exit"<<endl;
        cout << "Enter your choice: >>";
    }
void employee_login()
{
    cout<<"...Login..."<<endl;
}

void show_exit(){
    cout << "Thank you for using our service. Goodbye!"<<endl;
}


};


class user1 {
public:
 long account_number;
    string full_name, dob, nationality, gender, login_pass;

    // Login method
      

    void signup() {
    cout << "1. Personal Information>>\n";
    cout << "\n\tFull Name: ";
    cin.ignore();
    getline(cin, full_name);
    cout << "\n\tDate of Birth (DD/MM/YYYY): ";
    getline(cin, dob);
    cout << "\n\tNationality and Residency: ";
    getline(cin, nationality);
    cout << "\n\tGender: ";
    getline(cin, gender);

    while (true) {
        cout << "Set a strong password: ";
        getline(cin, login_pass);
        if (Password_Validity(login_pass)) {
            cout << "\nPassword is valid.\n";
            break;
        } else {
            cout << "Invalid password. Please try again.\n";
        }
    }

    account_number = generate_unique_account_number();

    cout << "Your Account Number: " << account_number << endl;

    save_file s;
    s.save_user_to_file(account_number, full_name, dob, nationality, gender, login_pass);
}

long generate_unique_account_number() {
    long last_account_number = 10000000; // Default if no accounts exist
    long new_account_number;

    // Open the file and find the last account number
    ifstream inFile("customer_data.txt");
    if (inFile) {
        long account_number;
        while (inFile >> account_number) {
            string dummy;
            getline(inFile, dummy); // Skip the rest of the line
            last_account_number = account_number; // Update with the last number read
        }
        inFile.close();
    }

    // Generate a new account number
    new_account_number = last_account_number + 1;

    return new_account_number;
}



    void show_details() const {
        cout << "\nSignup successful! Here is your information:\n";
        cout << "\tFull Name: " << full_name << "\n";
        cout << "\tDate of Birth: " << dob << "\n";
        cout << "\tNationality and Residency: " << nationality << "\n";
        cout << "\tGender: " << gender << "\n";
        cout << "\tAccount Number: " << account_number << "\n";
    }
};


class after_login {
public:
    save_file s;

    void deposit(long account_number) {
        double deposit_amount;
        cout << "Enter deposit amount: ";
        cin >> deposit_amount;

        if (deposit_amount <= 0) {
            cout << "Invalid deposit amount. Please try again.\n";
            return;
        }
        else{
        double current_balance = s.get_balance(account_number);
        current_balance += deposit_amount;
        s.update_balance(account_number, current_balance);

        s.save_transaction(account_number, deposit_amount, "Deposit");
        cout << "Deposit successful. Current balance: " << current_balance << "\n";
    }}

    void withdraw(long account_number) {
        double withdraw_amount;
        cout << "Enter withdrawal amount: ";
        cin >> withdraw_amount;

        double current_balance = s.get_balance(account_number);
        if (withdraw_amount <= 0 || withdraw_amount > current_balance) {
            cout << "Invalid withdrawal amount. Available balance: " << current_balance << "\n";
            return;
        }
        else{
        current_balance -= withdraw_amount;
        s.update_balance(account_number, current_balance);

        s.save_transaction(account_number, withdraw_amount, "Withdrawal");
        cout << "Withdrawal successful. Remaining balance: " << current_balance << "\n";
    }}

    void show_transaction_history(long account_number) {
        ifstream file("transactions.txt");
        if (!file) {
            cerr << "Error: Unable to open transactions file.\n";
            return;
        }
        else{
        string record;
        bool found = false;
        cout << "\n--- Transaction History ---\n";
        while (getline(file, record)) {
            if (record.find(to_string(account_number)) == 0) {
                cout << record << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No transactions found.\n";
        }
        file.close();
    }}
};




class employee{
    public:
    long id;
    string password;
     int count_enter;

     void login_id() {
        for (int i = 0; i < 3; i++) {
            cout << "Enter your ID number: ";
            cin >> id;
            cin.ignore();
            cout << "Enter your password: ";
            getline(cin, password);
            if (id == 23303137 && password == "sum01*#") {
                cout << ">> Login Successful\n";
                return;
            } else {
                cout << ">> Wrong ID / Pin\n>> Please try again\n";
            }
        }
        cout << ">> Too many failed attempts. Go to help center.\n";
    }
};

class bank_lone{
    public:
    string name,address,profession,problem;
    string university_name,department;
    string office,rank_position;
    int age,income,lone_amount,id,semester;

    void customer_details()
    {
        cout<<"Enter your name= ";
        getline(cin,name);
        cout<<"Enter your age= ";
        cin>>age;
        cin.ignore();
        cout<<"Enter your address= ";
        getline(cin,address);
        cout<<"Enter your profession student/working person= ";
        getline(cin,profession);
    }
    void occupation()
    {
        if(profession=="student"||profession=="Student"){
        cout<<"Enter your university name= ";
        getline(cin,university_name);
        cout<<"Enter your department= ";
        getline(cin,department);
        cout<<"Enter your id= ";
        cin>>id;
        cout<<"Enter your income= ";
        cin>>income;
        cout<<"Enter your lone amount= ";
        cin>>lone_amount;
        cin.ignore();
        cout<<"Why do you want to take a loan= ";
        getline(cin,problem);

        cout<<endl;
        cout<<"name= "<<name<<endl;
        cout<<"University name= "<<university_name<<endl;
        cout<<"Department = "<<department<<endl;
        cout<<"your id = "<<id<<endl;
        cout<<"Your income= "<<income<<endl;
        cout<<"your want "<<lone_amount<<"tk lone."<<endl;
        cout<<"problem= "<<problem<<endl;
        }
        else{
            cout<<"Enter your office name= ";
            getline(cin,office);
            cout<<"Enter your position= ";
            getline(cin,rank_position);cout<<"Enter your income= ";
            cin>>income;
            cout<<"Enter your lone amount= ";
            cin>>lone_amount;
            cin.ignore();
            cout<<"Why do you want to take a loan= ";
            getline(cin,problem);

            cout<<endl;
            cout<<"name= "<<name<<endl;
            cout<<"Office name is = "<<office<<endl;
            cout<<"Your position= "<<rank_position<<endl;
            cout<<"Your income= "<<income<<endl;
            cout<<"your want "<<lone_amount<<"tk lone."<<endl;
            cout<<"problem= "<<problem;

            
        }
    }
};




class help{
public:
    
void help_menu(){
  cout << "---->> Help Menu <<----" << endl;
  cout << "-----------------------" << endl << endl;
  
  cout << "1. How to Create an Account" << endl;
  cout << "2. Password Requirements" << endl;
  cout << "3. Login Issues" << endl;
  cout << "4. How to Reset Password" << endl;
  cout << "5. Transaction Guidelines" << endl;
  cout << "6. Account Management" << endl;
  cout << "7. Loan Applications" << endl;
  cout << "8. Security Tips" << endl;
  cout << "9. Contact Support" << endl;
  cout << "10. Exit" << endl;
}

void problem_1(){
            int choice;
    cout << "--->>How to Create an Account<<---" << endl;
    cout << "----------------------------------" << endl << endl;
    
        do {
    cout << "Welcome to the Bank System!" << endl;
    cout << "Follow these steps to create an account:" << endl << endl;
    cout << "1. Choose 'Customer Section' from the main menu" << endl;
    cout << "2. Select 'Sign Up' from the Customer Menu" << endl;
    cout << "3. Provide the following details when prompted:" << endl;
    cout << "   - Your full name." << endl;
    cout << "   - Date of Birth (format: DD/MM/YYYY)." << endl;
    cout << "   - Your nationality and residency." << endl;
    cout << "   - Gender (Male/Female/Other)." << endl;
    cout << "4. Set a strong password following these rules:" << endl;
    cout << "   - At least 8 characters long." << endl;
    cout << "   - Must include uppercase and lowercase letters, at least one digit, and one special character." << endl;
    cout << "5. Once the information is submitted, your account number will be generated." << endl;
    cout << "6. Save your account number securely." << endl << endl;
    cout << "--->>Thank you for staying with us<<---" << endl << endl;

        cout << "\n--->>How to Create an Account<<---" << endl;
        cout << "1. Again" << endl;
        cout << "2. Back" << endl;
        cout << "Enter your choice (1-2): ";
        cin >> choice;
        cout << endl;
        
        if (choice == 2);
        } while (choice == 1);
}

void problem_2(){
    int choice;
    cout << "--->>Password Requirements<<---" << endl;
    cout << "----------------------------------" << endl << endl;
    
        do {
    cout << "1. Password must be at least 8 characters long." << endl;
    cout << "2. Password must include at least one uppercase letter (A-Z)." << endl;
    cout << "3. Password must include at least one lowercase letter (a-z)." << endl;
   cout << "4. Password must include at least one digit (0-9)." << endl;
   cout << "5. Password must include at least one special character (@, #, $, %, &, *)." << endl << endl;
   
   cout << "--->>Here are some examples of strong passwords<<---" << endl;
   cout << "----------------------------------------------------" << endl;
    cout << "- Summer2024@# " << endl;
    cout << "- SecureP@ssw0rd123 " << endl;
    cout << "- P@ssw0rD!567 " << endl;
    cout << "- MyStrongPass!2024 " << endl;
    cout << "- Safe&Sound#123 " << endl;
    
    cout << "\n---->>Passwords that should NOT be used<<---" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "- 12345678" << endl;
    cout << "- password" << endl;
    cout << "- abc12345" << endl;
    cout << "- qwerty12" << endl;
    cout << "- letmein@" << endl;
    cout << "- admin123" << endl;
    cout << "- welcome1" << endl;
    cout << "- iloveyou" << endl << endl;

    cout << "--->>Thank you for staying with us<<---" << endl << endl;

        cout << "\n--->>Password Requirements<<---" << endl;
        cout << "1. Again" << endl;
        cout << "2. Back" << endl;
        cout << "Enter your choice (1-2): ";
        cin >> choice;
        cout << endl;
        
        if (choice == 2);
        } while (choice == 1);
}

void problem_3(){
    
}

void problem_4(){
   
}

void problem_5(){
    
}

void problem_6(){
  
}

void problem_7(){
     int choice;
    do{
        cout << "--->>Types of Bank Loans<<---" << endl;
        cout << "-----------------------------" << endl << endl;
        
        cout << "1. Home Loan" << endl;
        cout << "2. Car Loan" << endl;
        cout << "3. Student Loan" << endl;
        cout << "4. Personal Loan" << endl;
        cout << "5. Agriculture Loan" << endl;
        cout << "6. Business Loan" << endl;
        cout << "7. More details" << endl;
        cout << "8. Exit" << endl;
        
        cout << "Enter your choice: ";
        cin>> choice;
        cout << endl << endl;
        
        switch(choice){
            
        case 1:
        cout << "--->>Home Loan<<---" << endl;
        cout << "- Interest Rate: 7%" << endl;
        cout << "- Maximum Tenure: 20 years" << endl;
        cout << "- Minimum Amount: 5,00,000"<< endl;
        break;
            
        case 2:
        cout << "--->>Car loan<<---" << endl;
        cout << "- Interest Rate: 9%" << endl;
        cout << "- Maximum Tenure: 7 years" << endl;
        cout << "- Minimum Amount: 1,00,000" << endl;
        break;
            
        case 3:
        cout << "--->>Student Loan<<---" << endl;
        cout << "- Interest Rate: 4%\n";
        cout << "- Maximum Tenure: 15 years\n";
        cout << "- Minimum Amount: 50,000\n";
        break;
            
        case 4:
        cout << "--->>Personal Loan<<---" << endl;
        cout << "- Interest Rate: 12%\n";
        cout << "- Maximum Tenure: 5 years\n";
        cout << "- Minimum Amount: 50,000\n";
            break;
            
        case 5:
        cout << "--->>Agriculture Loan<<---" << endl;
        cout << "- Interest Rate: 5%" << endl;
        cout << "- Maximum Tenure: 10 years" << endl;
        cout << "- Minimum Amount: 1,00,000" << endl;
        break;
        
        case 6:
        cout <<"--->>Business Loan<<---" << endl;
        cout << "- Interest Rate: 10%";
        cout << "- Maximum Tenure: 15 years";
        cout << "- Minimum Amount: 2,00,000";
        
        case 7:
        cout << "--->>More details<<---" << endl;
        cout << "-->>Contruct us.." << endl << endl;
        cout << "Email: -bankmanagement@gmil.com" <<endl;
        cout << "Phone: \n-01727**** \n-01610******" << endl;
        cout << "\nThank you" << endl;
        break;
        
        case 8:{
        cout << "Thank you for visiting us." << endl << endl;
        return;
        }
        break;
        
        default:
        cout << "Error.Try Again" << endl;
        cout << "xxxxxxxxxxxxxxx" << endl << endl;
        problem_7();
        break;
        }
        
        cout << "\n--->>Types of Bank Loans<<---" << endl;
        cout << "1. Again" << endl;
        cout << "2. Back" << endl;
        cout << "Enter your choice (1-2): ";
        cin >> choice;
        cout << endl;
        
        if (choice == 2);
        } while (choice == 1);
    
}

void problem_8(){
    
}

void problem_9(){
    
}

void problem_10(){

}


};

void access_help(){
     int choice;
             help  h;

    while (true) {

        h.help_menu();

        cout << "\nEnter your choice: >> ";
        cin >> choice;
        cout << endl;

        switch(choice){

            case 1:
            h.problem_1();
            break;

            case 2:
            h.problem_2();
            break;

            case 3:
            h.problem_3();
            break;

            case 4:
            h.problem_4();
            break;

            case 5:
            h.problem_5();
            break;

            case 6:
            h.problem_6();
            break;

            case 7:
            h.problem_7();
            break;

            case 8:
            h.problem_8();
            break;

            case 9:
            h.problem_9();
            break;

            case 10:
            cout << "Exiting help section." << endl;
            return;
            break;

            default:
            cout << "Error. Try Again" << endl << endl;

            }
          }
}

class login_conditions{
    public:
     bank_lone loan;
      user1 user;
       display_chart chart;
       after_login log;
    save_file file_manager;
bool is_valid;

    login_conditions(){
        is_valid=false;
    }
void login_conditionn(){

     long entered_account;
    string entered_password;

    cout << "Enter Account Number: ";
    cin >> entered_account;
    cin.ignore();
    cout << "Enter Password: ";
    getline(cin, entered_password);
    cout << endl;
    ifstream file("customer_data.txt");
    if (!file) {
        cerr << "Error: Unable to open customer data file.\n";
    }


    while (file >> user.account_number) {
        file.ignore(); 
        getline(file, user.full_name, ' ');
        getline(file, user.dob, ' ');
        getline(file, user.nationality, ' ');
        getline(file, user.gender, ' ');
        getline(file, user.login_pass);

        if (user.account_number == entered_account && user.login_pass == entered_password) {
            cout << "\nLogin successful! Welcome, " << user.full_name << ".\n";
            is_valid = true;

            int second_chart;
            while (true) {
                chart.show_user_chart();
                cin >> second_chart;
                cout << endl;

                if (second_chart == 1) {
                    log.deposit(user.account_number);
                    cout<<endl;
                } else if (second_chart == 2) {
                    log.withdraw(user.account_number);
                    cout<<endl;
                } else if (second_chart == 3) {
                    cout<<"1: Show biodata\n2: Show transection history"<<endl;
                    int b;
                    cin>>b;
                    if(b==1){
                    double balance = file_manager.get_balance(user.account_number);
                    cout << "Account Details:\n";
                    user.show_details();
                    cout << "Current Balance: " << balance << endl;}
                    else if (b==2){
                       log. show_transaction_history(entered_account);
                    }
                } else if (second_chart == 4) {
                    int  openion;
                    cout << "Are you withdrawing a loan? \n1: Yes\n2: No): ";
                    cin >> openion;
                    cin.ignore();
                    cout << endl;
                    if (openion == 1 || openion ==2) {
                        loan.customer_details();
                        loan.occupation();
                    }
                } else if (second_chart == 5) {
                    cout << "Logging out...\n";
                    break;
                } else {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
            break;
        }
    }

    if (!is_valid) {
        cout << "Invalid account number or password. Please try again.\n";
    }

    file.close();
}
};

void continue_code() {
    display_chart chart;
    employee emp;
    user1 user;
   login_conditions loginC;
    string openion;
    after_login log;
    save_file file_manager;
    int option,second_chart,log_option,a;

    while (true) {
        chart.show_first_chart();
        cin >> option;
        cin.ignore();
        cout<<endl;
        if (option == 4) {
          chart.show_exit();
            break;
        }
        if (option == 1) {
             chart.ask_for_login(); 
            cin>>log_option;
            cout<<endl;

            if(log_option==1){
                user.signup();
                user.show_details();
            }
               
            else if (log_option == 2) {
                loginC.is_valid=false;
               for(int i=0;i<3;i++){
               if(loginC.is_valid==false){
               loginC. login_conditionn();
                // break;
               }
               else{
               cout<<"Please go to help section.";}}
}

        else if (log_option==3){
             cout << "Help Section: Please contact customer support.\n";
        }
        else if(log_option==4){
            continue;
           
        }      
        }
        else if (option == 2) {
            cout<<"\n1: Employee"<<endl;
            cout<<"2: Back\n>>>Choice an option: ";
            int b;
            cin>>b;
            if (b==1){
            chart.employee_login();
            emp.login_id();}
            else if(b==1){
                continue;
            }
            else{
                //letter
            }
        } 
        else if (option == 3) {
            access_help();

        } 
        else {
            cout << "Invalid option. Try again.\n";
        }
        cout<<endl;
    }   
}



int main(){
   continue_code();
    
   return 0;
}
