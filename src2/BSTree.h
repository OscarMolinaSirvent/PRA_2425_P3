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
                throw std::runtime_error("No se encontró el nodo.");
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

        BSNode<T>* insert(BSNode<T>* n, T e){
            if(n == nullptr){
                return new BSNode<T>*(e);
            }
            else if(n->elem == e){
                throw std::runtime_error("Elemento duplicado.");
            }
            else if(n->elem < e){
                n->right = insert(n->right, e);
            }
            else{
                n->left = insert(n->left,e);
            }

            return n;
        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            if(n != nullptr){
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out,n->right);
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

        T operator[](T e ) const{
            return search(e) -> elem;
        }

        void insert(T e){
            insert(root,e);
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out,bst.root);
            return out;
        }
    
};

#endif