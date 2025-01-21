#include <iostream>
#include "User.h"
#include "ClientUser.h"
#include "Media.h"
#include "AdminUser.h"
#include "CompressedTrie.h"
#include "HashTable.h"

using namespace std;

AdminUser admin;
ClientUser users[10000];
Media *mediaList[10000];
int media_count = 0;
int number_user = 0;
CompressedTrie mediaTrie;
SplayTree mediaSplayTree;
HashTable hashTable;


void login(string username, string password)
{
    if (username == "admin" && password == "admin")
    {
        cout << "You are logged in as an admin." << endl;
        admin.displayMenu(mediaList, media_count,mediaTrie,hashTable);
    }
    else
    {
        for (int i = 0; i < number_user; i++)
        {
            if (users[i].getUsername() == username && users[i].getPassword() == password)
            {
                cout << "You are logged in as a client." << endl;
                users[i].setTrie(&mediaTrie);
                users[i].setSplayTree(&mediaSplayTree);
                users[i].displayMenu(hashTable);
                return;
            }
        }
        cout << "Invalid username or password!" << endl;
    }
}

void registeration(string username, string password)
{
    if (username != "admin" && password != "admin")
    {
        users[number_user].setUname(username);
        users[number_user].setPwd(password);
        number_user++;
        cout << "Registration successful!" << endl;
    }
    else
    {
        cout << "You cannot register with the username 'admin' and password 'admin'." << endl;
    }
}

void showMenu()
{
    cout << "Welcome to Filimio!" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    int choice;
    string username, password;

    while (true)
    {
        showMenu();

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            login(username, password);
            break;

        case 2:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            registeration(username, password);
            break;

        case 3:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }

    return 0;
}
