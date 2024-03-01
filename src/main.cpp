#include "stdio.h"

#include "list.h"

using namespace std;

int main() {
    auto list = List<int>();
    
    for (int i = 0; i < 10; ++i) {
        list.append(i);
    }

    list.print();

    list.removeAt(9);

    list.print();

    auto list2 = list;
    
    // list2.print();

    return 0;
}