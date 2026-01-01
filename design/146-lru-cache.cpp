// 146. LRU Cache
// Problem Link: https://leetcode.com/problems/lru-cache/description/

// Approach:

// HashMap + Doubly Linked List (DLL)
// - We need O(1) for both get() and put()
// - HashMap gives O(1) lookup: key -> Node* in DLL
// - Doubly Linked List maintains usage order:
//   - Most Recently Used (MRU) near the front (right after head)
//   - Least Recently Used (LRU) near the back (right before tail)
//
// Core Operations (all O(1)):
// 1) removeNode(node): detach a node from DLL
// 2) addToFront(node): insert node right after head
// 3) moveToFront(node): remove + addToFront
// 4) popLRU(): remove and return the node before tail
//
// get(key):
// - If key not found -> return -1
// - Else move node to front and return its value
//
// put(key, value):
// - If key exists: update value + move to front
// - Else:
//   - If cache full: evict LRU (tail->prev), erase from map, delete node
//   - Insert new node at front, store in map
//
// Time Complexity: O(1) for get and put
// Space Complexity: O(capacity)

#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {

private:
    struct Node{
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k, int v){
            key = k;
            value = v;
            prev = nullptr;
            next = nullptr;
        }
    };

    int cap;
    unordered_map<int, Node*> mp;

    Node* head;
    Node* tail;

    void removeNode(Node* node){
        Node* p = node->prev;
        Node* n = node->next;
        p->next = n;
        n->prev = p;
    }

    void addToFront(Node* node){
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void moveToFront(Node* node){
        removeNode(node);
        addToFront(node);
    }

    Node* popLRU(){
        Node* lru = tail->prev;
        removeNode(lru);
        return lru;
    }

public:
    LRUCache(int capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        cap = capacity;

        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        // if key not in the map, return -1
        auto it = mp.find(key);
        if(it == mp.end()) return -1;

        // if key in the map, 
        // fetch node from map,
        Node* node = it->second; 
        // move node to front to dll
        moveToFront(node);
        // return value
        return node->value;
    }
    
    void put(int key, int value) {
        // if key already exist
        // update the value and 
        // move node to front
        auto it = mp.find(key); 
        if(it != mp.end()){
            Node* node = it->second;
            node->value = value;

            moveToFront(node);
            return;
        }
        

        // if key does not exist,

        // if cache is full,
        // remove the tail node
        // remove the key from the map
        if((int)mp.size() == cap){
            Node* lru = popLRU();
            mp.erase(lru->key);
            delete lru;
        }

        // insert new node at front
        // add key node in the map
        Node* node = new Node(key, value);
        addToFront(node);
        mp[key] = node;   
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << "\n"; // 1

    cache.put(3, 3);             // evicts key 2
    cout << cache.get(2) << "\n"; // -1

    cache.put(4, 4);             // evicts key 1
    cout << cache.get(1) << "\n"; // -1
    cout << cache.get(3) << "\n"; // 3
    cout << cache.get(4) << "\n"; // 4

    return 0;
}
