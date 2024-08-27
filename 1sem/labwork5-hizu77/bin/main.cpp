#include <sstream>
#include "../lib/Class.h"
#include "../lib/ThreeDArray.h"

int main() {
    ThreeDArray arr = ThreeDArray::make_array(1, 2, 3);
    std::stringstream output;
    arr[0][0][0] = 1;
    output << arr[0][0][0];
    std::cout << output.str();
    return 0;
}
