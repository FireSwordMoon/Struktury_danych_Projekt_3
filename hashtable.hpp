#pragma once

#include <vector>
#include <string>

// glowna klasa bazowa dla wszystkich tablic mieszajacych
class HashTable {
protected:
    int capacity;
public:
    HashTable(int cap) : capacity(cap) {}
    virtual ~HashTable() {}
    
    // metoda do poprawnego klonowania stanu tablicy przy pomiarach
    virtual HashTable* clone() const = 0;
    
    // podstawowe operacje do testowania
    virtual void insert(int key) = 0;
    virtual bool search(int key) = 0;
    virtual void remove(int key) = 0;
    
    // funkcje zliczajace ilosc prob
    virtual int get_insert_probes(int key) = 0;
    virtual int get_search_probes(int key) = 0;
    
    // zwraca nazwe metody mieszania
    virtual std::string get_name() = 0;
};