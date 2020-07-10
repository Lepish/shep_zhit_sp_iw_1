#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template<typename T>
class List
{
private:
    struct Node;
public:
    class Iterator{
    public:
        Iterator(Node* node):iNode(node){}

        bool operator==(const Iterator& other) const{
            if(this == &other){
                return true;
            }
            return iNode == other.iNode;
        }

        bool operator!=(const Iterator& other) const{
            return  !operator==(other);
        }

        T operator*() const{
            if(iNode){
                return iNode->data;
            }
            return T();
        }

        void operator++(){
            if(iNode){
                iNode = iNode->next;
            }
        }

        void operator--(){
            if(iNode){
                iNode = iNode->prev;
            }
        }

        T getData() {
            if(!iNode) {
                throw "Index is out of bounds";
            }
            return iNode->data;
        }
    private:
        Node* iNode;
    };
public:
    List();

    ~List();

    void append(const T& t);

    void remove();

    void removeElement(const T& t);

    bool isEmpty();

    Iterator searchElement(const T& t);

    T getElementByIndex(int index);

    T getHead() const;

    Iterator end() const;

    Iterator begin() const;

    int size() const;

    List& operator|=(const T& t);

    List& operator/=(const T& t);

    void print(ostream& os){
        for(Iterator it = begin(); it != end(); ++it){
            os << it.getData() << " ";
        }
        os << endl;
    }

    friend std::istream& operator>>(std::istream& is, List<T>& l);

    List& operator||(const List& l){
        List resl;
        for(Iterator it = begin(); it != end(); ++it){
            resl.append(it.getData());
        }
        for(Iterator it = l.begin(); it != l.end(); ++it){
            resl.append(it.getData());
        }
        return resl;
    }

    List& operator&&(const List& l){
        List resl;
        for(Iterator it1 = begin(); it1 != end(); ++it1){
            for(Iterator it2 = l.begin(); it2 != l.end(); ++it2){
                if(it1.getData() == it2.getData()){
                    resl.append(it1.getData());
                }
            }
        }
        return resl;
    }

    bool operator==(const List<T>& l){
       if(size() != l.size()){
           return false;
       }
       for(Iterator it = begin(); it != end(); ++it){
           if(!l.searchElement(it.getData())){
               return false;
           }
       }
       return true;
    }

    bool operator!=(const List<T>& l){
        return !(*this == l);
    }
private:
    struct Node{
        T data;

        Node *prev;

        Node *next;

        Node() : prev(nullptr), next(nullptr){}

        Node(const T& t) : data(t), next(nullptr), prev(nullptr){}
    };

    Node* head;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l);

#endif // LIST_H
