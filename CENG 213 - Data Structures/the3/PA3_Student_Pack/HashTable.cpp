#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    // TODO

    int sum = 0, x = 1;

    for(int a = 0; a < key.size(); ++a)
    {
        sum += (int)key[a] * PRIME_LIST[a];
    }

    int orgId = sum % tableSize, Id = sum % tableSize;

    while(table[Id].key != "" && table[Id].key != "__DELETED__")
    {
        Id = (orgId + x*x) % tableSize;
        ++x;
    }
    return Id;
}

void KeyedHashTable::ReHash()
{
    // TODO

    int newCap = FindNearestLargerPrime(this->tableSize * 2);
    int prevCap = this->tableSize;
    HashData *prevH = this->table;
    this->table = new HashData[newCap];
    this->tableSize = newCap;

    for(int a = 0; a < prevCap; ++a)
    {
        if(prevH[a].key == "" || prevH[a].key == "__DELETED__"){continue;}
        else
        {
            (this->table)[Hash(prevH[a].key)] = prevH[a];
        }
    }
    delete [] prevH;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    // TODO

    for(int a = 0; a < PRIME_TABLE_COUNT; ++a)
    {
        if(requestedCapacity < PRIME_LIST[a]){return PRIME_LIST[a];}
    }
}

KeyedHashTable::KeyedHashTable()
{
    // TODO

    table = new HashData[2];
    tableSize = 2;
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    // TODO

    tableSize = FindNearestLargerPrime(requestedCapacity);
    table = new HashData[tableSize];
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    // TODO
    this->table = NULL;
    *this = other;
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    // TODO

    delete [] table;
    table = new HashData[other.tableSize];
    this->tableSize = other.tableSize;

    if(!(other.occupiedElementCount))
    {
        occupiedElementCount = 0;
        return *this;
    }

    this->occupiedElementCount = other.occupiedElementCount;

    for(int a = 0; a < this->tableSize; ++a)
    {
        (this->table)[a].key = (other.table)[a].key;
        (this->table)[a].intArray = (other.table)[a].intArray;
    }
    return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    // TODO
    delete [] table;
    table = NULL;
}

HashData *KeyedHashTable::findKey(const std::string& key) const
{
    if(key == ""){return NULL;}

    for(int a = 0; a < this->tableSize; ++a)
    {
        if((this->table)[a].key == key){return &((this->table)[a]);}
    }
    return NULL;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    // TODO

    if(findKey(key)){return false;}

    HashData newData;
    newData.key = key;
    newData.intArray = intArray;
    (this->table)[Hash(newData.key)] = newData;
    ++(this->occupiedElementCount);
    
    if(occupiedElementCount * EXPAND_THRESHOLD >= tableSize){ReHash();}
    return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    // TODO

    HashData* d = findKey(key);

    if(!d){return false;}

    d->key = "__DELETED__";
    (d->intArray).clear();
    --occupiedElementCount;
    return true;
}

void KeyedHashTable::ClearTable()
{
   // TODO

   for(int a = 0; a < tableSize; ++a)
   {
        if(table[a].key == ""){continue;}
        Remove(table[a].key);
        table[a].key = "";
   }
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    // TODO

    HashData* d = findKey(key);
    if(d){valueOut = d->intArray; return true;}
    return false;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}