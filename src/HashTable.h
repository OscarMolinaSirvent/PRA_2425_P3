#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdexcept>
#include <ostream>
#include "Dict.h"
#include "TableEntry.h"

#include "../../PRA_2425_P1/Parte1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n, max;
        ListLinked<TableEntry<V>>* table;
        int h(std::string key){
            int suma = 0;
            int ret = 0;
            for(int i = 0; i < key.size(); i++){
                suma += int(key.at(i));
            }
            return suma % table->size();
        }
    public:
        HashTable(int size){
            if(size <= 0){
                throw std::runtime_error("El tamaño no puede ser 0 o inferior.");
            }
            n = 0;
            max = size;
            table = new ListLinked<TableEntry<V>>**[size];
            for(int i = 0; i < max; i++){
                table[i] = new ListLinked<TableEntry<V>>();
            }
        }

        ~HashTable(){
            delete[] table;
        }
        
        int capacity(){
            return n;
        }

        /*void insert(std::string key, V value) override{
            
        }*/

        V search(std::string key){
            int index = h(key);
            TableEntry<V> buscar(key);
            int position = table[index] -> search(buscar);
            if(position != 0){
                throw std::runtime_error("No se pudo encontrar el key.");
            }else{
                return table[index] -> get(position);
            }
        }

        V remove
};

#endif