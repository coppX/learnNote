//
//  SkipList.cpp
//  SkipList
//
//  Created by 付代超 on 2019/12/22.
//  Copyright © 2019 付代超. All rights reserved.
//

#include "SkipList.hpp"
#include <random>
#include <iostream>

template<typename T> SkipList<T>::SkipList(int maxLevel, T iniValue)
    :maxLevel(maxLevel)
{
    head = new SkipListNode<T>(minInt, iniValue, maxLevel);
    tail = new SkipListNode<T>(maxInt, iniValue, maxLevel);
    
    for(int i = 0; i < maxLevel; i++){
        head->next[i] = tail;
    }
}

template<typename T> SkipList<T>::~SkipList(){
    delete head;
    delete tail;
}

template<typename T> int SkipList<T>::randomLevel(){
    int random_level = 1;
    int seed = time(NULL);
    static default_random_engine e(seed);
    static uniform_int_distribution<int> u(0, 1);
    while(u(e) && random_level < maxLevel)
    {
        random_level++;
    }
    return random_level;
}

template<typename T> int SkipList<T>::nodeLevel(vector<SkipListNode<T> *> next)
{
    int node_level = 0;
    if(next[0]->key == maxInt){
        return node_level;
    }
    
    for(int i = 0; i < next.size(); i++)
    {
        if(next[i] != nullptr && next[i]->key != maxInt)
        {
            node_level++;
        }else{
            break;
        }
    }
    return node_level;
}

template<typename T> SkipListNode<T>* SkipList<T>::insert(int k, T v){
    int x_level = randomLevel();
    SkipListNode<T>* new_node = nullptr;
    SkipListNode<T>* tmp = head;
    
    new_node = find(k);
    if(new_node){
        new_node->value = v;
        return head;
    }
    
    new_node = new SkipListNode<T>(k, v, x_level);
    for(int i = x_level - 1; i > -1; i--)
    {
        while(tmp->next[i] && tmp->next[i]->key < k)
        {
            tmp = tmp->next[i];
        }
        
       new_node->next[i] = tmp->next[i];
       tmp->next[i] = new_node;
    }
    return head;
}

template<typename T> SkipListNode<T>* SkipList<T>::find(int x)
{
    SkipListNode<T>* tmp = head;
    int current_level = nodeLevel(tmp->next);
    for(int i = current_level - 1; i > -1; i--)
    {
        while(tmp->next[i] && tmp->next[i]->key < x)
        {
            tmp = tmp->next[i];
        }
    }
    tmp = tmp->next[0];
    if(tmp->key == x){
        return tmp;
    }else{
        return nullptr;
    }
}

template<typename T> SkipListNode<T>* SkipList<T>::deleteNode(int x)
{
    SkipListNode<T>* node = find(x);
    if(node){
        SkipListNode<T>* tmp = head;
        int x_level = node->next.size();
        for(int i = (x_level - 1); i > -1; i--)
        {
            while(tmp->next[i] && tmp->next[i]->key < x){
                tmp = tmp->next[i];
            }
            tmp->next[i] = tmp->next[i]->next[i];
        }
        return head;
    }
}

template<typename T> void SkipList<T>::printNode(){
    for(int i = 0; i < maxLevel; i++){
        SkipListNode<T>* tmp = head;
        int lineLen = 1;
        if(tmp->next[i]->key != maxInt){
            cout <<"\n";
            cout <<"This is level "<< i << ":" << endl;
            cout <<"{";
            while(tmp->next[i] && tmp->next[i]->key != maxInt){
                cout << "(" << "Key: " << tmp->next[i]->key<<", ";
                cout << "Value: " << tmp->next[i]->value << ")";
                tmp = tmp->next[i];
                if(tmp->next[i] && tmp->next[i]->key != maxInt){
                    cout <<", ";
                }
                if(lineLen++ % 5 == 0)cout << "\n";
            }
            cout << "}\n";
        }
    }
}
