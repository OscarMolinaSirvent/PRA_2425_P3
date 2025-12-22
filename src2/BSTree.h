#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T> *root;

        BSNode<T>* search(BSNode<T>* n, T e) const{
            if(n == nullptr){
                throw std::runtime_error("No se encontró el nodo.")
            }
            else if(n->elem < e){
                return search(n->right,e);
            }
            else if(n->elem > e){
                return search(n->left,e);
            }
            else{
                return n;
            }
        }
    public:
        BSTree(){
            root = nullptr;
            nelem = 0;
        }

        int size() const{
            return nelem;
        }

        T search(T e) const{
            return search(root,e) -> elem;
        }

    
};

#endif