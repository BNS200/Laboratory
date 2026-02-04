#include <iostream>
#include "array.h"


using std::endl;
using std::cout;


int main() {
    // Array<int> arr(9, 0);
    // cout << arr << endl;
    // Array<int> arr1(std::move(arr));
    // cout << arr1 << endl;
    // arr1.insert(0, 9);
    // cout << arr1 << endl;
    Array<int> arr4 = Array<int>::getRandomArray(20);
    cout << arr4 << endl;
    arr4.bubbleSort();
    cout << arr4 << endl;
    Array<int>::iterator it = arr4.begin();
    for (auto& elem : arr4){
        cout << elem << " ";
    }




    // arr1.insertSeveral(1, 5, 8);
    // cout << arr1 << endl;
    

    return 0;
}
