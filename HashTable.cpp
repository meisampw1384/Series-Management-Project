#include "HashTable.h"
#include <iostream>

void bubbleSort(Media ** arr, int n, int mode) 
{

    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (!mode)
            {
                if (arr[j]->getRating() > arr[j + 1]->getRating()) 
                {
                    auto tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
            else
            {
                if (arr[j]->getReleaseYear() > arr[j + 1]->getReleaseYear()) 
                {
                    auto tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
    }
}

HashTable::HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        table[i] = nullptr;
    }
}

void HashTable::insert(const string& key, Media* media) 
{
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current) 
    {
        if (current->key == key) 
        {
            current->mediaList[current->count++] = media;
            return;
        }
        current = current->next;
    }

    HashNode* newNode = new HashNode(key);
    newNode->mediaList[newNode->count++] = media;
    newNode->next = table[index];
    table[index] = newNode;
}

void HashTable::search(const string& key_country,const string& key_language,const string& key_genre, const int& key_year, const int& key_score) 
{
    HashNode* current;
    Media * list[100];
    int choose_way = 0;
    int count = 0;
    if (key_country != "NAN")
    {
        int index_c = hashFunction(key_country);
        current =  table[index_c];

        while (current) 
        {
            if (current->key == key_country) 
            {
                if (count < current->count)
                {
                    count = current->count;
                    choose_way = 1;
                    break;
                }
            }
            current = current->next;
        }
    }
    if (key_language != "NAN")
    {
        int index_c = hashFunction(key_language);
        current =  table[index_c];

        while (current) 
        {
            if (current->key == key_language) 
            {
                if (count < current->count)
                {
                    choose_way = 2;
                    count = current->count;
                    break;
                }
            }
            current = current->next;
        }
    }
    if (key_genre != "NAN")
    {
        int index_c = hashFunction(key_genre);
        current =  table[index_c];

        while (current) 
        {
            if (current->key == key_genre) 
            {
                if (count < current->count)
                {
                    choose_way = 3;
                    count = current->count;
                    break;
                }
            }
            current = current->next;
        }
    }

    count = 0;
    if (choose_way == 1)
    {
        int index_c = hashFunction(key_country);
        current =  table[index_c];
        
        while (current) 
        {
            if (current->key == key_country) 
            {
                for (int i = 0; i < current->count; i++)
                {
                    if ((key_genre == "NAN" or current->mediaList[i]->getGenre() == key_genre) and (key_language == "NAN" or current->mediaList[i]->getLanguage() == key_language) and (key_score == -1 or current->mediaList[i]->getRating() == key_score) and (key_year == -1 or current->mediaList[i]->getReleaseYear() == key_year))
                    {
                        list[count] = current->mediaList[i];
                        count++;
                    }
                }
                break;
            }
            current = current->next;
        }
    }
    else if(choose_way == 2)
    {
        int index_c = hashFunction(key_language);
        current =  table[index_c];
        
        while (current) 
        {
            if (current->key == key_language) 
            {
                for (int i = 0; i < current->count; i++)
                {
                    if ((key_genre == "NAN" or current->mediaList[i]->getGenre() == key_genre) and (key_country == "NAN" or current->mediaList[i]->getCountryOfOrigin() == key_country) and (key_score == -1 or current->mediaList[i]->getRating() == key_score) and (key_year == -1 or current->mediaList[i]->getReleaseYear() == key_year))
                    {
                        list[count] = current->mediaList[i];
                        count++;                    
                    }
                }
                break;
            }
            current = current->next;
        }
    }
    else if(choose_way == 3)
    {
        int index_c = hashFunction(key_genre);
        current =  table[index_c];
        
        while (current) 
        {
            if (current->key == key_genre) 
            {
                for (int i = 0; i < current->count; i++)
                {
                    if ((key_language == "NAN" or current->mediaList[i]->getLanguage() == key_language) and (key_country == "NAN" or current->mediaList[i]->getCountryOfOrigin() == key_country) and (key_score == -1 or current->mediaList[i]->getRating() == key_score) and (key_year == -1 or current->mediaList[i]->getReleaseYear() == key_year))
                    {
                        list[count] = current->mediaList[i];
                        count++;
                    }
                }
                break;
            }
            current = current->next;
        }
    }

    if (key_score == -1 and key_year == -1)
    {
        bubbleSort(list,count,0);
        for (int i = 0; i < count; i++)
        {
            cout << list[i]->getName() << "...." << list[i]->getReleaseYear() << "...." << list[i]->getRating() << endl;
        }
        return;
    }
    if (key_score == -1)
    {
        bubbleSort(list,count,0);
        for (int i = 0; i < count; i++)
        {
            cout << list[i]->getName() << "...." << list[i]->getReleaseYear() << "...." << list[i]->getRating() << endl;
        }
        return;
    }
    if (key_year == -1)
    {
        bubbleSort(list,count,1);
        for (int i = 0; i < count; i++)
        {
            cout << list[i]->getName() << "...." << list[i]->getReleaseYear() << "...." << list[i]->getRating() << endl;
        }
        return;
    }
}

void HashTable::delete_media(const string& key, Media* media)
{
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current) 
    {
        if (current->key == key) 
        {
            int i = 0;
            for (i; i < current->count; i++)
            {
                if(current->mediaList[i] == media)
                {
                    break;
                }
            }
            if (i < current->count)
            {
                for (i; i < current->count; i++)
                {
                    current->mediaList[i] = current->mediaList[i+1];
                }
                current->count--;
                return;
            }
        }
        current = current->next;
    }
    
}