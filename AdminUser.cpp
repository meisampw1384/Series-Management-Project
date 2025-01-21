
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

void AdminUser::displayMenu(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable& hashTable)
{
    int choice;
    while (true)
    {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Add Movie" << endl;
        cout << "2. Add Series" << endl;
        cout << "3. delete Movie" << endl;
        cout << "4. delete Series" << endl;
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
            deleteMovie(mediaList, mediaCount, compressedTrie, hashTable);
            break;
        case 4:
            deleteMovie(mediaList, mediaCount, compressedTrie, hashTable);
            break;
        case 5:
            cout << "Logging out..." << endl;
            return;

        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
}

void AdminUser::addMovie(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable& hashTable)
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

void AdminUser::addSeries(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable& hashTable)
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
    Series* newSeries = new Series(name, releaseYear, episodeDuration, country, genre, language, rating, plot, seasons, episodes);
    
    mediaList[mediaCount] = newSeries;
    compressedTrie.insert(name, newSeries);
    hashTable.insert(genre, mediaList[mediaCount]);
    hashTable.insert(language, mediaList[mediaCount]);
    hashTable.insert(country, mediaList[mediaCount]);
    mediaCount++;

    cout << "Series added successfully!" << endl;
}

void AdminUser::deleteMovie(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie,HashTable& hashTable)
{
    //delete from mediaList and compressedTrie and hashTable
}

void AdminUser::deleteSeries(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie,HashTable& hashTable)
{
    //delete from mediaList and compressedTrie and hashTable
    // hashTable.delete_media(genre, mediaList[mediaCount]);
    // hashTable.delete_media(language, mediaList[mediaCount]);
    // hashTable.delete_media(country, mediaList[mediaCount]);
}