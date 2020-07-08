//
//  main.cpp
//  SkipList
//
//  Created by 付代超 on 2019/12/22.
//  Copyright © 2019 付代超. All rights reserved.
//

#include <iostream>
#include "SkipList.cpp"
int main(int argc, const char * argv[]) {
    int maxLevel = 6;
    SkipList<int> l(maxLevel, 0);
    for(int i = 0; i < 50; i++){
        l.insert(i, 2*i);
    }
    l.printNode();
    return 0;
}
