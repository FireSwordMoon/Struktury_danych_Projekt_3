#pragma once
#include "hashtable.hpp"
#include <vector>
#include <string>

// klasa dla sondowania kwadratowego
class QuadraticProbingHT : public HashTable {
private:
    std::vector<int> table;
public:
    QuadraticProbingHT(int cap);
    HashTable* clone() const override;
    void insert(int key) override;
    bool search(int key) override;
    void remove(int key) override;
    int get_insert_probes(int key) override;
    int get_search_probes(int key) override;
    std::string get_name() override;
};