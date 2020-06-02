#include <sstream>
#include "sown.h"

using namespace std;

vector<string> split(string str, char delim) {
    
    vector<string> vec;
    
    stringstream ss;
    
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == delim)
        {
            if(ss.str() != "")
            {
                vec.push_back(ss.str());
            }
            ss.str("");
        }
        else
        {
            ss << str[i];
        }
    }
    
    if(ss.str() != "")
    {
        vec.push_back(ss.str());
    }
    
    return vec;
}

