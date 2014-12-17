#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{


    // create empty vector for strings

    vector<string> sentence;

    // reserve memory for five elements to avoid reallocation
    sentence.reserve(5);
    // append some elements
    sentence.push_back("Hello,");
    //

    sentence.insert(sentence.end(),{"how","are","you","?"});

    // print elements separated with spaces
    copy (sentence.begin(), sentence.end(),
          ostream_iterator<string>(cout," "));


    cout << endl << "!!!finally Hello World!!!" << endl; // prints !!!Hello World!!!
    return 0;
}

