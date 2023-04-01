// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// account database 

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;
// stores all accounts in a notepad file and when you sign in, it checks the file.
// accoutn class 
class Account {
public:
    string username;
    string password;
    string name;
    string email;
    Account(string username, string password, string name, string email) {
        this->username = username;
        this->password = password;
        this->name = name;
        this->email = email;
    }
private:
};

// system including vectors to initialize accounts
class AccountSystem {
public:
    vector<Account> accounts;
    AccountSystem(vector<Account>& accounts) {
        this->accounts = accounts;
    }
    bool validate(string password, string username) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].username == username && accounts[i].password == password) {
                return true;
            }
        }
        return false;
    }

private:

};

// main
int main()
{
    vector<Account> accounts = vector<Account>();
    AccountSystem as = AccountSystem(accounts);
    fstream file;
    string line;
    Account ac = Account("", "", "", "");
    file.open("accounts.txt", fstream::in);
    while (getline(file, line)) {
        int colon_pose = line.find(':');
        string type = line.substr(0, colon_pose);
        string info = line.substr(colon_pose + 1);
        if (type == "name") {
            ac = Account(info, "", "", "");
        }
        else if (type == "email") {
            ac.email = info;
        }
        else if (type == "username") {
            ac.username = info;
        }
        else if (type == "password") {
            ac.password = info;
            as.accounts.push_back(ac);
        }
    }
    file.close();
    file.open("accounts.txt", fstream::app);
    file.seekg(0, ios::end);
    long pose = file.tellp();
    cout << "Do you want to log in or sign up?" << endl;
    string choice;
    getline(cin, choice);
    string username;
    string password;
    string email;
    string name;
    if (choice == "sign up") {
        cout << "Enter your name" << endl;
        getline(cin, name);
        cout << "Enter your email" << endl;
        getline(cin, email);
        cout << "Enter your username" << endl;
        getline(cin, username);
        cout << "Enter your password" << endl;
        getline(cin, password);
        Account acc = Account(username, password, name, email);
        as.accounts.push_back(acc);
        file << "name:" + name << endl;
        file << "email:" + email << endl;
        file << "username:" + username << endl;
        file << "password:" + password << endl;
        
    }
    else if (choice == "log in") {
        cout << "What's your username?" << endl;
        getline(cin, username);
        cout << "What's your password?" << endl;
        getline(cin, password);
        if (as.validate(password, username) == true) {
            cout << "You're signed in" << endl;
        }
        else {
            cout << "Account not found" << endl;
        }

    }
    file.close();
    
}

