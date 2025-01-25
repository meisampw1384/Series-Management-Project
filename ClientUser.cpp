#include "ClientUser.h"
#include <vector>
#include <unordered_set>
#include <algorithm>

ClientUser::ClientUser() : User(), trie(nullptr), splayTree(nullptr), favoriteCount(0) {}

ClientUser::ClientUser(const string &uname, const string &pwd) : User(uname, pwd), trie(nullptr), splayTree(nullptr), favoriteCount(0) {}

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
void ClientUser::setSuggestionTree(SplayTree *SuggestionTree)
{
    this->SuggestionTree = SuggestionTree;
}

void ClientUser::displayMenu(HashTable *hashTable, Media *mediaList[], int &media_count)
{
    int choice;

    while (true)
    {
        cout << "\n--- Client Menu ---" << endl;
        cout << "1. Search for Media" << endl;
        cout << "2. Advanced Search" << endl;
        cout << "3. Filter Media" << endl;
        cout << "4. Display All Media" << endl;
        cout << "5. Add Media to Favorites" << endl;
        cout << "6. Display Favorites" << endl;
        cout << "7. Remove Media from Favorites" << endl;
        cout << "8. Rate Media" << endl;
        cout << "9. surprise me!" << endl;
        cout << "10. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string prefix;
            cout << "Enter the prefix of the media name: ";
            cin >> prefix;
            searchMedia(prefix);
        }
        break;
        case 2:
            advancedSearch();
            break;
        case 3:
            filterMedia(hashTable);
            break;
        case 4:
            displayAllMedia(mediaList, media_count);
            break;
        case 5:
        {
            string mediaName;
            cout << "Enter the name of the media to add to favorites: ";
            cin >> mediaName;

            vector<Media *> matchingMedia;

            for (int i = 0; i < media_count; i++)
            {
                if (mediaList[i]->getName() == mediaName)
                {
                    matchingMedia.push_back(mediaList[i]);
                }
            }

            if (matchingMedia.empty())
            {
                cout << "Media not found!" << endl;
            }
            else if (matchingMedia.size() == 1)
            {

                addToFavorites(matchingMedia[0]);
                cout << "Media added to favorites!" << endl;
            }
            else
            {

                cout << "Multiple media found with the name \"" << mediaName << "\". Please choose one:\n";
                for (int i = 0; i < matchingMedia.size(); i++)
                {
                    cout << i + 1 << ". " << matchingMedia[i]->getName() << "(" << matchingMedia[i]->getReleaseYear() << ")" << endl;
                }

                int choice;
                cout << "Enter the number of your choice: ";
                cin >> choice;

                if (choice >= 1 && choice <= matchingMedia.size())
                {
                    addToFavorites(matchingMedia[choice - 1]);
                    cout << "Media added to favorites!" << endl;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        break;

        case 6:
            displayFavorites();
            break;
        case 7:
        {
            string mediaName;
            cout << "Enter the name of the media to delete from favorites: ";
            cin >> mediaName;

            vector<Media *> matchingMedia;

            for (int i = 0; i < favoriteCount; i++)
            {
                if (favoriteList[i]->getName() == mediaName)
                {
                    matchingMedia.push_back(favoriteList[i]);
                }
            }

            if (matchingMedia.empty())
            {
                cout << "Media not found in favorites!" << endl;
            }
            else if (matchingMedia.size() == 1)
            {
                removeFromFavorites(matchingMedia[0]);
                cout << "Media removed from favorites!" << endl;
            }
            else
            {
                cout << "Multiple media found with the name \"" << mediaName << "\" in favorites. Please choose one to delete:\n";
                for (size_t i = 0; i < matchingMedia.size(); i++)
                {
                    cout << i + 1 << ". " << matchingMedia[i]->getName() << "(" << matchingMedia[i]->getReleaseYear() << ")" << endl;
                }

                int choice;
                cout << "Enter the number of your choice: ";
                cin >> choice;

                if (choice >= 1 && choice <= matchingMedia.size())
                {
                    removeFromFavorites(matchingMedia[choice - 1]);
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        break;

        case 8:
        {
            string mediaName;
            float rating;

            cout << "Enter the name of the media to rate: ";
            cin >> mediaName;
            Media *results[100];
            int resultCount = 0;

            for (int i = 0; i < media_count; i++)
            {
                if (mediaList[i] && mediaList[i]->getName() == mediaName)
                {
                    results[resultCount++] = mediaList[i];
                }
            }

            if (resultCount == 0)
            {
                cout << "No media found with the name \"" << mediaName << "\"." << endl;
                break;
            }

            cout << "Found the following media(s):" << endl;
            for (int i = 0; i < resultCount; i++)
            {
                cout << i + 1 << ". " << results[i]->getName()
                     << " (" << results[i]->getReleaseYear() << ") - Rating: "
                     << results[i]->getRating() << endl;
            }

            int choice;
            cout << "Enter the number of the media to rate: ";
            cin >> choice;

            if (choice < 1 || choice > resultCount)
            {
                cout << "Invalid choice! Aborting rating process." << endl;
                break;
            }

            Media *mediaToRate = results[choice - 1];

            cout << "Enter your rating (0 to 10): ";
            cin >> rating;

            if (rating >= 0 && rating <= 10)
            {
                mediaToRate->setRating(rating);
                cout << "New average rating: " << mediaToRate->getRating() << endl;
                cout << "Rating added successfully!" << endl;
            }
            else
            {
                cout << "Invalid rating! Please enter a value between 0 and 10." << endl;
            }
        }
        break;

        case 9:
            surpriseme(hashTable);
            break;
        case 10:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
}

void ClientUser::surpriseme(HashTable *hashTable)
{
    cout << "lets surprise you!" << endl;
    if (SuggestionTree->root != nullptr)
    {
        string sug = SuggestionTree->root->mediaName;
        while (!(hashTable->search("NAN", "NAN", sug, -1, -1, 0)))
        {
            SuggestionTree->remove(sug);
            if (SuggestionTree->root)
            {
                sug = SuggestionTree->root->mediaName;
            }
            else
            {
                cout << "sorry, there is no enough data to surprise!" << endl;
                return;
            }
        }
        if (SuggestionTree->max and ((SuggestionTree->max_count) / 2) + 1 > SuggestionTree->root->count)
        {
            sug = SuggestionTree->max->mediaName;
            if (!(hashTable->search("NAN", "NAN", sug, -1, -1, 0)))
            {
                SuggestionTree->remove(sug);
                sug = SuggestionTree->root->mediaName;
            }
        }

        cout << "the trend genre is now : " << sug << endl;
        hashTable->search("NAN", "NAN", sug, -1, -1, 1);
    }
    else
    {
        cout << "sorry, there is no enough data to surprise!" << endl;
        return;
    }
}

void ClientUser::searchMedia(string prefix)
{
    if (!trie)
    {
        cout << "Media database is not available!" << endl;
        return;
    }

    Media *results[100];
    int count = 0;
    trie->searchPrefix(prefix, results, count);

    if (count == 0)
    {
        cout << "No media found matching the prefix \"" << prefix << "\"." << endl;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (results[i]->getName() != "")
            {
                if (!SuggestionTree->search(results[i]->getGenre()))
                {
                    SuggestionTree->insert(results[i]->getGenre());
                }

                cout << "- " << results[i]->getName() << " (" << results[i]->getReleaseYear() << ")" << endl;
            }
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

    if (splayTree)
    {
        if (trie)
        {

            Media *prefixResults[100];
            int prefixCount = 0;

            trie->searchPrefix(query, prefixResults, prefixCount);

            if (prefixCount > 0)
            {
                bool foundInSplay = false;
                unordered_set<string> flag;

                for (int i = 0; i < prefixCount; i++)
                {
                    string mediaName = prefixResults[i]->getName();
                    if (mediaName != "")
                    {
                        foundInSplay = splayTree->search(mediaName);

                        if (foundInSplay && flag.find(mediaName) == flag.end())
                        {
                            searchMedia(mediaName);
                        }
                        flag.insert(mediaName);
                    }
                }
                if (foundInSplay)
                {
                    return;
                }
            }
        }
    }

    Media *prefixResults[100];
    int prefixCount = 0;
    if (trie)
    {
        trie->searchPrefix(query, prefixResults, prefixCount);
    }

    if (prefixCount > 0)
    {
        for (int i = 0; i < prefixCount; i++)
        {
            if (prefixResults[i]->getName() != "")
            {
                SuggestionTree->insert(prefixResults[i]->getGenre());
                splayTree->insert(prefixResults[i]->getName());
                cout << "- " << prefixResults[i]->getName() << " (" << prefixResults[i]->getReleaseYear() << ")" << endl;
            }
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
            if (allMedia[i]->getName() != "")
            {
                int distance = levenshteinDistance(query, allMedia[i]->getName());
                if (distance <= 2)
                {
                    SuggestionTree->insert(allMedia[i]->getGenre());
                    suggestions[suggestionCount] = allMedia[i]->getName();
                    distances[suggestionCount] = distance;
                    suggestionCount++;
                }
            }
        }

        if (suggestionCount == 0)
        {
            cout << "No suggestions found." << endl;
            return;
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
                splayTree->insert(suggestions[i]);
            }
        }
    }
}

void ClientUser::filterMedia(HashTable *hashTable)
{
    string genreFilter, languageFilter, countryFilter;
    int yearFilter, scoreFilter;

    cout << "Do you want to filter by genre? (y/n): ";
    string choice;
    cin >> choice;
    if (choice == "y")
    {
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

    cout << "Do you want to filter by score? (y/n): ";
    cin >> choice;
    if (choice == "y")
    {
        cout << "Enter score: ";
        cin >> scoreFilter;
    }
    else
    {
        scoreFilter = -1;
    }

    cout << "Do you want to filter by year? (y/n): ";
    cin >> choice;
    if (choice == "y")
    {
        cout << "Enter year: ";
        cin >> yearFilter;
    }
    else
    {
        yearFilter = -1;
    }

    hashTable->search(countryFilter, languageFilter, genreFilter, yearFilter, scoreFilter, 1);
}

void ClientUser::displayAllMedia(Media *mediaList[], int &media_count)
{
    if (mediaList == nullptr)
    {
        cout << "Media list is not available!" << endl;
        return;
    }

    cout << "--- List of All Movies and Series ---" << endl;

    int index = 0;
    for (index = 0; index < media_count; index++)
    {
        cout << "-----------------------------------" << endl;
        mediaList[index]->displayInfo();
    }

    if (index == 0)
    {
        cout << "No media available!" << endl;
    }
    else
    {
        cout << "-----------------------------------" << endl;
        cout << "Total Media Items: " << media_count << endl;
    }
}

void ClientUser::addToFavorites(Media *media)
{
    if (favoriteCount >= 1000)
    {
        cout << "Favorite list is full!" << endl;
        return;
    }

    for (int i = 0; i < favoriteCount; i++)
    {
        if (favoriteList[i] == media)
        {
            cout << "Media is already in the favorite list." << endl;
            return;
        }
    }

    favoriteList[favoriteCount++] = media;
    cout << "Added \"" << media->getName() << "\" to your favorites!" << endl;
    sortFavorites();
}

void ClientUser::removeFromFavorites(Media *media)
{
    for (int i = 0; i < favoriteCount; ++i)
    {
        if (favoriteList[i] == media)
        {
            for (int j = i; j < favoriteCount - 1; ++j)
            {
                favoriteList[j] = favoriteList[j + 1];
            }
            favoriteCount--;
            cout << "Media removed from favorites!" << endl;
            return;
        }
    }
    cout << "Media not found in favorites!" << endl;
}

void ClientUser::displayFavorites()
{
    if (favoriteCount == 0)
    {
        cout << "Your favorite list is empty." << endl;
        return;
    }

    cout << "Your Favorites:" << endl;
    for (int i = 0; i < favoriteCount; i++)
    {
        cout << "- " << favoriteList[i]->getName() << " (" << favoriteList[i]->getReleaseYear() << ")" << endl;
    }
}

void merge(Media *arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Media *leftArr[n1];
    Media *rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i]->getName() <= rightArr[j]->getName())
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(Media *arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void ClientUser::sortFavorites()
{
    mergeSort(favoriteList, 0, favoriteCount - 1);
    cout << "Favorites sorted alphabetically!" << endl;
}

ClientUser::~ClientUser()
{
}
