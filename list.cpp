#include "list.h"
#include <iostream>

using namespace std;

template<typename T>
List<T>::List():head(NULL){}

template<typename T>
List<T>::~List() {
    while(head) {
        remove();
    }
}


template<typename T>
void List<T>::append(const T &t) {
   if(searchElement(t) == -1){
        Node* node = new Node(t);
        node->next = head;
        head->prev = node;
        head = node;
   }
}

template<typename T>
void List<T>::remove() {
    if(!isEmpty()) {
        Node* newHead = head->next;
        delete head;
        head = newHead;
        head->prev = nullptr;
    }
}
template<typename T>
int List<T>::size() const{
    int s = 0;
    for(Iterator it = begin(); it != end(); ++it) {
        ++s;
    }
    return s;
}

template<typename T>
typename List<T>::Iterator List<T>::searchElement(const T& t){
     if(!isEmpty()) {
         int s = 0;
         Iterator it = begin();
         while(it != end()){
             if(it.getData() == t){
                 return it;
             }
             ++s;
             ++it;
         }
     }
     return end();
}

template<typename T>
void List<T>::removeElement(const T &t) {
    if(!isEmpty()) {
        Iterator it = searchElement(t);
        if(it){
            if(size() == 1){
                head = nullptr;
                delete it;
            }else if(!(it->next)){
                it->prev = nullptr;
                delete it;
            }else if(!(it->prev)){
                head = it->next;
                delete it;
            }else{
                it->prev->next = it->next;
                delete it;
            }
        }
    }
}

template<typename T>
bool List<T>::isEmpty(){
    return !head;
}

template<typename T>
T List<T>::getElementByIndex(int index){
    if(index >= size()){
        throw "Index is out of bounds";
    }
    Iterator it = begin();
    for(int s = 0; s <= index; ++s) {
       ++it;
    }
    return it.getData();
}

template<typename T>
T List<T>::getHead() const{
    return head;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(NULL);
}

template<typename T>
List<T>& List<T>::operator|=(const T& t){
    append(t);
    return *this;
}

template<typename T>
List<T>& List<T>::operator/=(const T& t){
    removeElement(t);
    return *this;
}

template<typename T>
std::istream& operator>>(std::istream& is, List<T>& l){
    T t;
    is >> t;
    l.append(t);
    return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, List<T>& l){
    l.print(os);
    return os;
}
