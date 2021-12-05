#include "split.h"

std::vector<std::string> split_str(std::string str, std::vector<std::string> delim) {
    std::vector<std::string> rtn;
    int index;
    int prev = 0;
    int next = str.find(delim.at(0));
    if(next == std::string::npos)
        next = str.size();
    int delim_index = 0;
    for(int i = 1; i < delim.size(); i++) {
        index = str.find(delim.at(i));
        if(index == std::string::npos)
            index = str.size();
        if(index < next) {
            next = index;
            delim_index = i;
        }
    }
    while(next != str.size()) {
        if(next-prev > 0)
            rtn.push_back(str.substr(prev, next-prev));
        prev = next + delim.at(delim_index).size();
        next = str.find(delim.at(0), prev);
        if(next == std::string::npos)
            next = str.size();
        delim_index = 0;
        for(int i = 1; i < delim.size(); i++) {
            index = str.find(delim.at(i), prev);
            if(index == std::string::npos)
                index = str.size();
            if(index < next) {
                next = index;
                delim_index = i;
            }
        }
    }
    if(str.size()-prev > 0)
        rtn.push_back(str.substr(prev));
    return rtn;
}

std::string strip(std::string str) { 
    int start, stop;
    for(start = 0; start < str.size(); start++) {
        if(str.at(start) != ' ')
            break;
    }
    for(stop = str.size()-1; stop > 0; stop--) {
        if(str.at(stop) != ' ')
            break;
    }
    return str.substr(start,stop-start+1);
}

std::vector<std::string> split_strip(std::string str, std::vector<std::string> delim) {
    std::vector<std::string> splitStr = split_str(str, delim);
    for(int i = 0; i < splitStr.size(); i++) {
        splitStr[i] = strip(splitStr[i]);
    }
    return splitStr;
}

std::vector<int> split_int(std::string str, std::vector<std::string> delim) {
    std::vector<std::string> splitStr = split_str(str, delim);
    std::vector<int> splitInt = std::vector<int>(splitStr.size());
    for(int i = 0; i < splitStr.size(); i++) {
        try {
            splitInt[i] = stoi(splitStr[i]);
        } catch(const std::invalid_argument &e) {
            splitInt[i] = -1;
        }
    }
    return splitInt;
}

std::vector<long> split_long(std::string str, std::vector<std::string> delim) {
    std::vector<std::string> splitStr = split_str(str, delim);
    std::vector<long> splitLong = std::vector<long>(splitStr.size());
    for(long i = 0; i < splitStr.size(); i++) {
        try {
            splitLong[i] = stol(splitStr[i]);
        } catch(const std::invalid_argument &e) {
            splitLong[i] = -1;
        }
    }
    return splitLong;
}

