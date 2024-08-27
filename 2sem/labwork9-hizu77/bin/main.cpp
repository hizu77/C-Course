#include "lib/Adapters.h"
#include "lib/TransformAdapter.h"
#include "lib/FilterAdapter.h"
#include "lib/TakeAdapter.h"
#include "lib/ReverseAdapter.h"
#include "lib/KeysValuesAdapter.h"
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <unordered_map>
#include <iostream>
using namespace std;

using namespace adapters;

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;
    std::vector<int> OK = {25, 9, 1};
    auto view = v | filter([](int i){return i % 2 == 1;}) | transform([](int i){return i * i;})
                | reverse();

    std::cout << *view.begin() << " " << *++view.begin() << " " << *++++view.begin();
}