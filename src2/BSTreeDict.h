#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "../src/Dict.h"
#include "BSTree.h"
#include "../src/TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>();
        }

        ~BSTreeDict(){
            delete tree;
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            out << *bs.tree;
            return out;
        }

        V operator[](std::string key){
            return tree -> search(TableEntry<V>(key)).value;
        }

        void insert(std::string key, V value) override{
            TableEntry<V> entry(key, value);
            tree -> insert(entry);
        }

        V search(std::string key) override{
            TableEntry<V> entry = tree->search(TableEntry<V>(key));
            return entry.value;
        }

        V remove(std::string key) override{
            V val = search(key); 
            tree->remove(TableEntry<V>(key)); //
            return val;
        }

        int entries() const override{
            return tree -> size();
        }
        
        
};

#endif