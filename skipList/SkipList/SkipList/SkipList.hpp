//
//  SkipList.hpp
//  SkipList
//
//  Created by 付代超 on 2019/12/22.
//  Copyright © 2019 付代超. All rights reserved.
//

#ifndef SkipList_hpp
#define SkipList_hpp

#include <stdio.h>
#include <vector>
using namespace std;
//跳跃表节点
template<typename T>
struct SkipListNode{
    int key;
    T value;
    vector<SkipListNode<T>*> next;//存放指向每层下个节点的指针
    SkipListNode(int k, T v, int level):key(k), value(v)
    {
        for(int i = 0; i < level; i++){
            next.push_back(nullptr);
        }
    }
};

//跳跃表
template<typename T>
class SkipList
{
public:
    SkipListNode<T> *head;
    int maxLevel;
    const int minInt = numeric_limits<int>::min();
    const int maxInt = numeric_limits<int>::max();
public:
    SkipList(int maxLevel, T iniValue);
    ~SkipList();
    int randomLevel();
    
    SkipListNode<T>* insert(int k, T v);
    SkipListNode<T>* find(int k);
    SkipListNode<T>* deleteNode(int k);
    void printNode();
    
private:
    SkipListNode<T>* tail;
    int nodeLevel(vector<SkipListNode<T>*> p);
};

#endif /* SkipList_hpp */
