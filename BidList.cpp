#include "BidList.h"

Node::Node(const word& data) : data(data), next(nullptr) {}

BidList::BidList() : head(nullptr), size(0) {}

void BidList::push_back(const word& data) {
    auto newNode = std::make_unique<Node>(data) ;
    size++ ;

    if (!head) {
        head = std::move(newNode);
        return;
    }

    Node* current = head.get();
    while (current->next) {
        current = current->next.get();
    }
    current->next = std::move(newNode);
}

word BidList::at(int index) const {
    Node* current = head.get();
    for (int i = 0; i < index; i++) {
        if (!current) {
            throw std::out_of_range("Index out of range");
        }
        current = current->next.get();
    }
    if (!current) {
        throw std::out_of_range("Index out of range");
    }
    return current->data ;
}

unsigned int BidList::length() const {
    return size ;
}

bool BidList::empty() const {
    return size == 0 ;
}