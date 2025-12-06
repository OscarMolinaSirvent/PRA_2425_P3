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
            int n = 0;
            for(int i = 0; i < max; i++){
                if(table[i] != nullptr){
                    table[i] -> empty();
                    n += 1;
                }
            }
            return n;
        }

        void insert(std::string key, V value) override{
            int index = h(key);
            TableEntry<V> insert(key,value);
            try{
                search(key);
            }catch(std::runtime_error &e){
                table[index] -> append(insert);
                n++;
            }
        }

        V search(std::string key) override{
            int index = h(key);
            TableEntry<V> buscar(key);
            int position = table[index] -> search(buscar);
            if(position == -1){
                throw std::runtime_error("No se pudo encontrar el key.");
            }else{
                return table[index] -> get(position);
            }
        }

        V remove(std::string key) override{
            int index = h(key);
            TableEntry<V> eliminar(key);
            int position = table[index] -> search(eliminar);
            if(position == -1){
                throw std::runtime_error("No se ha podido encontrar el par clave -> valor");
            }else{
                table[index] -> remove(position);
            }
        }

        int entries(){
            return n;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
            out << "HashTable [entries: " << th.entries() << ", " << "capacity: " << th.capacity() << "]"
            << std::endl;
            out << "==============" << std::endl;
            for(int i = 0; i < th.max ; i++){
                out << "== Cubeta " << i << "==";
                out << th.table[i] ;
            }
            return out;
        }

        V operator[](std::string key){
            int index = h(key);
            if(index >= capacity()){
                throw std::runtime_error("La posicion no existe");
            }else{
                return search(key);
            }
        }
};

#endif