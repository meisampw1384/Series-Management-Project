#include "HashTable.h"

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

void HashTable::search(const string& key_country,const string& key_language,const string& key_genre) 
{
    HashNode* current;
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
                    if ((key_genre == "NAN" or current->mediaList[i]->getGenre() == key_genre) and (key_language == "NAN" or current->mediaList[i]->getLanguage() == key_language))
                    {
                        cout << current->mediaList[i]->getName() << "...." << current->mediaList[i]->getReleaseYear() << endl;
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
                    if ((key_genre == "NAN" or current->mediaList[i]->getGenre() == key_genre) and (key_country == "NAN" or current->mediaList[i]->getCountryOfOrigin() == key_country))
                    {
                        cout << current->mediaList[i]->getName() << "...." << current->mediaList[i]->getReleaseYear() << endl;
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
                    if ((key_language == "NAN" or current->mediaList[i]->getLanguage() == key_language) and (key_country == "NAN" or current->mediaList[i]->getCountryOfOrigin() == key_country))
                    {
                        cout << current->mediaList[i]->getName() << "...." << current->mediaList[i]->getReleaseYear() << endl;
                    }
                }
                break;
            }
            current = current->next;
        }
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