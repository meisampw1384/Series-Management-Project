#include "ClientUser.h"
#include <algorithm>

ClientUser::ClientUser() : User(), trie(nullptr), splayTree(nullptr) {}

ClientUser::ClientUser(const string &uname, const string &pwd) : User(uname, pwd), trie(nullptr), splayTree(nullptr) {}

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

void ClientUser::setSplayTree(SplayTree *splayTree)
{
    this->splayTree = splayTree;
}

void ClientUser::displayMenu(HashTable& hashTable)
{
    int choice;

    while (true)
    {
        cout << "\n--- Client Menu ---" << endl;
        cout << "1. Search for Media" << endl;
        cout << "2. Advanced Search" << endl;
        cout << "3. filter" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            searchMedia();
            break;
        case 2:
            advancedSearch();  
            break;
        case 3:
            filterMedia(hashTable);
        case 4:
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

int ClientUser::levenshteinDistance(const string &a, const string &b)
{
    int m = a.size();
    int n = b.size();

    int **dp = new int *[m + 1];
    for (int i = 0; i <= m; i++)
    {
        dp[i] = new int[n + 1];
    }

    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; i++)
    {
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

void ClientUser::advancedSearch()
{
    string query;
    cout << "Enter media name (or part of it): ";
    cin >> query;

 
    if (splayTree && splayTree->search(query))
    {
        cout << "Found \"" << query << "\" in frequently searched items!" << endl;
        return;
    }

   
    Media *prefixResults[100];
    int prefixCount = 0;
    if (trie)
    {
        trie->searchPrefix(query, prefixResults, prefixCount);
    }

    if (prefixCount > 0)
    {
        cout << "Found " << prefixCount << " result(s) for \"" << query << "\":" << endl;
        for (int i = 0; i < prefixCount; i++)
        {
            cout << "- " << prefixResults[i]->getName() << " (" << prefixResults[i]->getReleaseYear() << ")" << endl;
        }
    }
    else
    {
        cout << "No exact matches found. Suggesting similar names..." << endl;

        Media *allMedia[10000];
        int mediaCount = 0;
        if (trie)
        {
            mediaCount = trie->getAllMedia(allMedia); 
        }

        string suggestions[100];
        int distances[100];
        int suggestionCount = 0;

        for (int i = 0; i < mediaCount; i++)
        {
            int distance = levenshteinDistance(query, allMedia[i]->getName());
            if (distance <= 2) 
            {
                suggestions[suggestionCount] = allMedia[i]->getName();
                distances[suggestionCount] = distance;
                suggestionCount++;
            }
        }

        if (suggestionCount == 0)
        {
            cout << "No suggestions found." << endl;
        }
        else
        {
            cout << "Suggestions:" << endl;

            for (int i = 0; i < suggestionCount - 1; i++)
            {
                for (int j = 0; j < suggestionCount - i - 1; j++)
                {
                    if (distances[j] > distances[j + 1])
                    {
                        int tempDist = distances[j];
                        distances[j] = distances[j + 1];
                        distances[j + 1] = tempDist;

                        string tempName = suggestions[j];
                        suggestions[j] = suggestions[j + 1];
                        suggestions[j + 1] = tempName;
                    }
                }
            }

            for (int i = 0; i < suggestionCount; i++)
            {
                cout << "- " << suggestions[i] << endl;
            }
        }
    }

    
    if (splayTree)
    {
        splayTree->insert(query);
    }
}

void ClientUser::filterMedia(HashTable& hashTable) 
{
    string genreFilter, languageFilter, countryFilter;

    cout << "Do you want to filter by genre? (y/n): ";
    string choice;
    cin >> choice;
    if (choice == "y") {
        cout << "Enter genre: ";
        cin >> genreFilter;
    }
    else
    {
        genreFilter = "NAN";
    }

    cout << "Do you want to filter by language? (y/n): ";
    cin >> choice;
    if (choice == "y") 
    {
        cout << "Enter language: ";
        cin >> languageFilter;
    }
    else
    {
        languageFilter = "NAN";
    }

    cout << "Do you want to filter by country? (y/n): ";
    cin >> choice;
    if (choice == "y") 
    {
        cout << "Enter country: ";
        cin >> countryFilter;
    }
    else
    {
        countryFilter = "NAN";
    }    

    hashTable.search(countryFilter, languageFilter, genreFilter);
}

ClientUser::~ClientUser()
{
}
