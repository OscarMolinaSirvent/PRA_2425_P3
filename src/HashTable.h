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
        ListLinked<TableEntry<V>>** table; 
        int h(std::string key){
            int suma = 0;
            int ret = 0;
            for(int i = 0; i < key.size(); i++){
                suma += int(key.at(i));
            }
            return suma % max;
        }
    public:
        HashTable(int size){
            if(size <= 0){
                throw std::runtime_error("El tamaño no puede ser 0 o inferior.");
            }
            n = 0;
            max = size;
            table = new ListLinked<TableEntry<V>>*[size];
            for(int i = 0; i < max; i++){
                table[i] = new ListLinked<TableEntry<V>>();
            }
        }

        ~HashTable(){
            delete[] table;
        }
        
        int capacity() const{
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
            int position = table[index] -> search(insert);
            
            if(position == -1){
                table[index] -> prepend(insert);
                n++;
            }else{
                throw std::runtime_error("La KEY ya existe.");
            }
        }

        V search(std::string key) override{
            int index = h(key);
            TableEntry<V> buscar(key);
            int position = table[index] -> search(buscar);
            if(position == -1){
                throw std::runtime_error("No se pudo encontrar el KEY.");
            }else{
                return table[index] -> get(position).value;
            }
        }

        V remove(std::string key) override{
            int index = h(key);
            TableEntry<V> eliminar(key);
            int position = table[index] -> search(eliminar);
            if(position == -1){
                throw std::runtime_error("No se ha podido encontrar el par KEY -> VALUE");
            }else{
                V v;
                v = table[index] -> get(position).value;
                table[index] -> remove(position);
                n--;
                return v;
            }
        }

        int entries() const override {
            return n;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
            out << "HashTable [entries: " << th.entries() << ", " << "capacity: " << th.capacity() << "]"
            << std::endl;
            out << "==============" << std::endl;
            for(int i = 0; i < th.max ; i++){
                out << "== Cubeta " << i << "==" << std::endl;
                out << *th.table[i];
                out << std::endl;
            }

            return out;
        }

        V operator[](std::string key){
            int index = h(key);
            if(index >= capacity()){
                throw std::runtime_error("La POSICIÓN no existe");
            }else{
                return search(key);
            }
        }
};

#endif