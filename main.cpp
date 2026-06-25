#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "hashtable.hpp"
#include "linear_probing.hpp"
#include "separate_chaining.hpp"
#include "robin_hood.hpp"
#include "quadratic_probing.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(NULL));
    vector<int> sizes = {1000, 2000, 5000, 10000, 20000, 50000, 100000};

    ofstream file("wyniki.csv");
    file << "Rozmiar,Metoda,Operacja,Przypadek,Czas_ns\n";

    for (int size : sizes) {
        
        // tworzenie polimorficznej listy tablic hashujacych
        vector<HashTable*> tables;
        tables.push_back(new LinearProbingHT(size));
        tables.push_back(new SeparateChainingHT(size));
        tables.push_back(new RobinHoodHT(size));
        tables.push_back(new QuadraticProbingHT(size));

        // zapelnienie do czterdziestu procent
        int items_to_insert = size * 0.4;

        for (HashTable* ht : tables) {
            vector<int> inserted_keys;
            for (int i = 0; i < items_to_insert; i++) {
                int k = rand() % 10000000;
                ht->insert(k);
                inserted_keys.push_back(k);
            }

            // poszukiwanie skrajnych przypadkow dla istniejacych
            int opt_exist = inserted_keys[0];
            int pes_exist = inserted_keys[0];
            int min_pr = 999999;
            int max_pr = -1;

            for (int k : inserted_keys) {
                int pr = ht->get_search_probes(k);
                if (pr < min_pr) { min_pr = pr; opt_exist = k; }
                if (pr > max_pr) { max_pr = pr; pes_exist = k; }
            }
            int avg_exist = inserted_keys[inserted_keys.size() / 2];

            // poszukiwanie skrajnych przypadkow dla nowych
            vector<int> found_new_keys;
            while (found_new_keys.size() < 100) {
                int k = rand() % 10000000;
                if (!ht->search(k)) {
                    found_new_keys.push_back(k);
                }
            }

            int opt_new = found_new_keys[0];
            int pes_new = found_new_keys[0];
            min_pr = 999999;
            max_pr = -1;

            for (int k : found_new_keys) {
                int pr = ht->get_insert_probes(k);
                if (pr < min_pr) { min_pr = pr; opt_new = k; }
                if (pr > max_pr) { max_pr = pr; pes_new = k; }
            }
            int avg_new = found_new_keys[found_new_keys.size() / 2];

            // zmienne przechowujace zsumowany czas
            long long time_add_opt = 0, time_add_avg = 0, time_add_pes = 0;
            long long time_search_opt = 0, time_search_avg = 0, time_search_pes = 0;
            long long time_remove_opt = 0, time_remove_avg = 0, time_remove_pes = 0;

            // wykonanie testow tysiac razy
            for (int i = 0; i < 1000; i++) {
                
                // testowanie szukania nie modyfikuje stanu
                auto start = high_resolution_clock::now();
                ht->search(opt_exist);
                auto stop = high_resolution_clock::now();
                time_search_opt += duration_cast<nanoseconds>(stop - start).count();

                start = high_resolution_clock::now();
                ht->search(avg_exist);
                stop = high_resolution_clock::now();
                time_search_avg += duration_cast<nanoseconds>(stop - start).count();

                start = high_resolution_clock::now();
                ht->search(pes_exist);
                stop = high_resolution_clock::now();
                time_search_pes += duration_cast<nanoseconds>(stop - start).count();

                // testowanie dodawania na swiezych kopiach
                HashTable* clone_add_opt = ht->clone();
                start = high_resolution_clock::now();
                clone_add_opt->insert(opt_new);
                stop = high_resolution_clock::now();
                time_add_opt += duration_cast<nanoseconds>(stop - start).count();
                delete clone_add_opt;

                HashTable* clone_add_avg = ht->clone();
                start = high_resolution_clock::now();
                clone_add_avg->insert(avg_new);
                stop = high_resolution_clock::now();
                time_add_avg += duration_cast<nanoseconds>(stop - start).count();
                delete clone_add_avg;

                HashTable* clone_add_pes = ht->clone();
                start = high_resolution_clock::now();
                clone_add_pes->insert(pes_new);
                stop = high_resolution_clock::now();
                time_add_pes += duration_cast<nanoseconds>(stop - start).count();
                delete clone_add_pes;

                // testowanie usuwania na swiezych kopiach
                HashTable* clone_rem_opt = ht->clone();
                start = high_resolution_clock::now();
                clone_rem_opt->remove(opt_exist);
                stop = high_resolution_clock::now();
                time_remove_opt += duration_cast<nanoseconds>(stop - start).count();
                delete clone_rem_opt;

                HashTable* clone_rem_avg = ht->clone();
                start = high_resolution_clock::now();
                clone_rem_avg->remove(avg_exist);
                stop = high_resolution_clock::now();
                time_remove_avg += duration_cast<nanoseconds>(stop - start).count();
                delete clone_rem_avg;

                HashTable* clone_rem_pes = ht->clone();
                start = high_resolution_clock::now();
                clone_rem_pes->remove(pes_exist);
                stop = high_resolution_clock::now();
                time_remove_pes += duration_cast<nanoseconds>(stop - start).count();
                delete clone_rem_pes;
            }

            // zapis obliczonych srednich wartosci do pliku
            string name = ht->get_name();
            file << size << "," << name << ",dodawanie,optymistyczny," << (time_add_opt / 1000) << "\n";
            file << size << "," << name << ",dodawanie,sredni," << (time_add_avg / 1000) << "\n";
            file << size << "," << name << ",dodawanie,pesymistyczny," << (time_add_pes / 1000) << "\n";

            file << size << "," << name << ",szukanie,optymistyczny," << (time_search_opt / 1000) << "\n";
            file << size << "," << name << ",szukanie,sredni," << (time_search_avg / 1000) << "\n";
            file << size << "," << name << ",szukanie,pesymistyczny," << (time_search_pes / 1000) << "\n";

            file << size << "," << name << ",usuwanie,optymistyczny," << (time_remove_opt / 1000) << "\n";
            file << size << "," << name << ",usuwanie,sredni," << (time_remove_avg / 1000) << "\n";
            file << size << "," << name << ",usuwanie,pesymistyczny," << (time_remove_pes / 1000) << "\n";
        }
        
        // czyszczenie pamieci po testach
        for(HashTable* ht : tables) {
            delete ht;
        }
    }

    file.close();
    cout << "zakonczono testy" << endl;
    return 0;
}
