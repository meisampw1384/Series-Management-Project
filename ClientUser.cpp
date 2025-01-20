#include "ClientUser.h"

ClientUser::ClientUser() : User(), trie(nullptr)
{
}

ClientUser::ClientUser(const string &uname, const string &pwd) : User(uname, pwd)
{
}

void ClientUser::setUname(const string &uname)
{
    username = uname;
}
void ClientUser::setPwd(const string &pwd)
{
    password = pwd;
}
void ClientUser::setTrie(CompressedTrie *trie)
{
    this->trie = trie;
}
void ClientUser::displayMenu()
{
    int choice;

    while (true)
    {
        cout << "\n--- Client Menu ---" << endl;
        cout << "1. Search for Media" << endl;
        cout << "2. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            searchMedia();
            break;

        case 2:
            cout << "Logging out..." << endl;
            return;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}
void ClientUser::searchMedia()
{
    if (!trie)
    {
        cout << "Media database is not available!" << endl;
        return;
    }

    string prefix;
    cout << "Enter the prefix of the media name: ";
    cin >> prefix;

    Media *results[100];
    int count = 0;
    trie->searchPrefix(prefix, results, count);

    if (count == 0)
    {
        cout << "No media found matching the prefix \"" << prefix << "\"." << endl;
    }
    else
    {
        cout << "Found " << count << " result(s):" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "- " << results[i]->getName() << " (" << results[i]->getReleaseYear() << ")" << endl;
        }
    }
}
ClientUser::~ClientUser()
{
}
