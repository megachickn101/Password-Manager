#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> get_account(string input) {
    ifstream account_info_file;
    account_info_file.open("accounts.csv");
    string line;
    while(getline(account_info_file, line)){
        string account;
        string email;
        string password;
        
        stringstream input_string(line);

        getline(input_string, account, ',');
        getline(input_string, email, ',');
        getline(input_string, password, ',');

        transform(input.begin(), input.end(), input.begin(), ::tolower);
        string compare_account = account;
        transform(compare_account.begin(), compare_account.end(), compare_account.begin(), ::tolower);
        
        if(compare_account == input){
            vector<string> output;
            output.push_back("1");
            output.push_back(account);
            output.push_back(email);
            output.push_back(password);
            account_info_file.close();
            return output;
        }
        line = "";
    }
    vector<string> output;
    output.push_back("0");
    account_info_file.close();
    return output;
}

void read_accounts(){
    ifstream account_info_file;
    account_info_file.open("accounts.csv");
    string line;
    while(getline(account_info_file, line)){
        string account;
        string email;
        string password;
        
        stringstream input_string(line);

        getline(input_string, account, ',');
        getline(input_string, email, ',');
        getline(input_string, password, ',');
        
        cout << "Account: " << account << endl << "Email: " << email << endl << "Password: " << password << endl << endl;

        line = "";
    }
    account_info_file.close();
}

void write_list(vector<vector<string>> account_info_input){
    ofstream account_info_file;
    account_info_file.open("accounts.csv");
    for(int i=0; i < account_info_input.size(); i++){
        account_info_file << account_info_input[0][i] << ',' << account_info_input[1][i] << ',' << account_info_input[2][i] << endl;
    }
    account_info_file.close();
}

void update_list(string account_input, string email_input, string password_input){
    ofstream account_info_file;
    account_info_file.open("accounts.csv", ios::app);
    account_info_file << account_input<< ',' << email_input << ',' << password_input << endl;
    account_info_file.close();
}

int main() {
    cout << "A Basic Password Manager \nGet the source code at https://www.github.com/megachickn101";
    while(true){
        string mode;
        cout << "\n \nSelect a mode: \n \n0 - List all accounts \n1 - Register new account \n2 - Search for account \n3 - Exit\n";
        cin >> mode;
        system("cls");
        if(mode == "0"){
            read_accounts();
        }else if(mode == "1"){
            string account_input;
            string email_input;
            string password_input;
            cout << "\nWebsite Name: \n";
            cin >> account_input;
            cout << "\nEmail: \n";
            cin >> email_input;
            cout << "\nPassword: \n";
            cin >> password_input;
            update_list(account_input, email_input, password_input);
            cout << "\nAccount Registered!";
        }else if(mode == "2"){
            string search_input;
            cout << "\nWhich account are you looking for? \n";
            cin >> search_input;
            vector<string> search_output = get_account(search_input);
            if(search_output[0] == "1"){
                cout << "\nAccount: " << search_output[1] << "\nEmail: " << search_output[2] << "\nPassword: " << search_output[3];
            }else{
                cout << "\nAccount not found :(";
            }
        }else if(mode == "3"){
            break;
        }else{
            cout << "\nNot a valid option";
        }
    }

}