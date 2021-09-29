#include "Util.h"

vector<string> splitString(string str, string delim)
{
    vector<string> splitString = vector<string>();

    string substr;
    // we use size_t so we can compare with npos accurately
    size_t nextIndex = 0;
    while ((nextIndex = str.find(delim)) != string::npos && nextIndex != 0)
    {
        substr = str.substr(0, nextIndex);
        splitString.push_back(substr);
        str.erase(0, nextIndex + delim.length());
    }
    splitString.push_back(str);

    return splitString;
}
