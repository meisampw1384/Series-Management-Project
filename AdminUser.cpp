
#include "AdminUser.h"
#include "Movie.h"
#include "Series.h"
#include "HashTable.h"

AdminUser::AdminUser() : User("admin", "admin")
{
}

AdminUser::~AdminUser()
{
}

void AdminUser::displayMenu(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable, SplayTree &splayTree)
{
    int choice;
    while (true)
    {
        cout << "\n--- Admin Menu ---" << endl;
        cout << "1. Add Movie" << endl;
        cout << "2. Add Series" << endl;
        cout << "3. Delete Movie" << endl;
        cout << "4. Delete Series" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addMovie(mediaList, mediaCount, compressedTrie, hashTable);
            break;

        case 2:
            addSeries(mediaList, mediaCount, compressedTrie, hashTable);
            break;

        case 3:
            cout << "\n--- Delete Movie ---" << endl;
            deleteMedia(mediaList, mediaCount, compressedTrie, hashTable, splayTree, "Movie");
            break;

        case 4:
            cout << "\n--- Delete Series ---" << endl;
            deleteMedia(mediaList, mediaCount, compressedTrie, hashTable,splayTree, "Series");
            break;

        case 5:
            cout << "Logging out..." << endl;
            return;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
}

void AdminUser::addMovie(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable)
{
    string name, country, genre, language, plot;
    int releaseYear, duration;

    cout << "Enter movie name: ";
    cin >> name;
    cout << "Enter release year: ";
    cin >> releaseYear;
    cout << "Enter duration (in minutes): ";
    cin >> duration;
    cout << "Enter country of origin: ";
    cin >> country;
    cout << "Enter genre: ";
    cin >> genre;
    cout << "Enter language: ";
    cin >> language;
    cout << "Enter plot summary: ";
    cin.ignore();
    getline(cin, plot);
    Movie *newMovie = new Movie(name, releaseYear, duration, country, genre, language, 0, plot);

    mediaList[mediaCount] = newMovie;
    compressedTrie.insert(name, newMovie);

    hashTable.insert(genre, mediaList[mediaCount]);
    hashTable.insert(language, mediaList[mediaCount]);
    hashTable.insert(country, mediaList[mediaCount]);

    mediaCount++;

    cout << "Movie added successfully!" << endl;
}

void AdminUser::addSeries(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable)
{
    string name, country, genre, language, plot;
    int releaseYear, episodeDuration, seasons, episodes;
    float rating;

    cout << "Enter series name: ";
    cin >> name;
    cout << "Enter release year: ";
    cin >> releaseYear;
    cout << "Enter episode duration (in minutes): ";
    cin >> episodeDuration;
    cout << "Enter number of seasons: ";
    cin >> seasons;
    cout << "Enter number of episodes: ";
    cin >> episodes;
    cout << "Enter country of origin: ";
    cin >> country;
    cout << "Enter genre: ";
    cin >> genre;
    cout << "Enter language: ";
    cin >> language;
    cout << "Enter plot summary: ";
    cin.ignore();
    getline(cin, plot);
    Series *newSeries = new Series(name, releaseYear, episodeDuration, country, genre, language, rating, plot, seasons, episodes);

    mediaList[mediaCount] = newSeries;
    compressedTrie.insert(name, newSeries);
    hashTable.insert(genre, mediaList[mediaCount]);
    hashTable.insert(language, mediaList[mediaCount]);
    hashTable.insert(country, mediaList[mediaCount]);
    mediaCount++;

    cout << "Series added successfully!" << endl;
}

void AdminUser::deleteMedia(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable, SplayTree &splayTree, const string &type)
{
    string name;
    cout << "Enter the name of the " << type << " to delete: ";
    cin >> name;

    Media *results[100];
    int resultCount = 0;

    
    for (int i = 0; i < mediaCount; i++)
    {
        if (mediaList[i] && mediaList[i]->getName() == name)
        {
            if ((type == "Movie" && dynamic_cast<Movie *>(mediaList[i])) ||
                (type == "Series" && dynamic_cast<Series *>(mediaList[i])))
            {
                results[resultCount++] = mediaList[i];
            }
        }
    }

    if (resultCount == 0)
    {
        cout << "No " << type << " found with the name \"" << name << "\"." << endl;
        return;
    }

    cout << "Found the following " << type << "(s):" << endl;
    for (int i = 0; i < resultCount; i++)
    {
        cout << i + 1 << ". " << results[i]->getName() << " (" << results[i]->getReleaseYear() << ")" << endl;
    }

    int choice;
    cout << "Enter the number of the " << type << " to delete: ";
    cin >> choice;

    if (choice < 1 || choice > resultCount)
    {
        cout << "Invalid choice! Aborting deletion." << endl;
        return;
    }

    Media *mediaToDelete = results[choice - 1];

   
    for (int i = 0; i < mediaCount; i++)
    {
        if (mediaList[i] == mediaToDelete)
        {
            mediaList[i] = nullptr;

           
            compressedTrie.remove(mediaToDelete->getName(),mediaToDelete);

            
            hashTable.delete_media(mediaToDelete->getGenre(), mediaToDelete);
            hashTable.delete_media(mediaToDelete->getLanguage(), mediaToDelete);
            hashTable.delete_media(mediaToDelete->getCountryOfOrigin(), mediaToDelete);


            int remainingCount = 0;
            for (int j = 0; j < mediaCount; j++)
            {
                if (mediaList[j] && mediaList[j]->getName() == name)
                {
                    remainingCount++;
                }
            }

            if (remainingCount == 0)
            {
                splayTree.remove(mediaToDelete->getName());
            }

           
            delete mediaToDelete;

            
            for (int j = i; j < mediaCount - 1; j++)
            {
                mediaList[j] = mediaList[j + 1];
            }
            mediaCount--;

            cout << type << " deleted successfully!" << endl;
            return;
        }
    }
}

