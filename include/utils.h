#ifndef UTILS_H
#define UTILS_H

//includes and namespaces
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class StringIntHash {
    public:
        map<string, int>::iterator it;
        map<string, int> hash;
        StringIntHash() {}
        StringIntHash(map<string, int> initialHash) {
            hash = initialHash;
        }
        void addToHash(string symbol, int value) {
            hash.insert(pair<string,int>(symbol, value));
        }
        int getCorrespondent(string command) {
            it = hash.find(command);
            if(it == hash.end()) {
                return -1;
            }
            else {
                return it->second;
            }
        }
};

#endif