/*
https://en.wikipedia.org/wiki/Median_of_medians
*/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int pivot(int arr[], int left, int right);
int partition(int arr[], int left, int right, int pivotIndex);

// return the index of the m (count from 0) th biggest element, though the order of the original list may have changed
int select(int arr[], int left, int right, int m) {
    if (m < left || m > right) return -1;
    if (left == right) return left;
    int pivotIndex = pivot(arr, left, right);
    pivotIndex = partition(arr, left, right, pivotIndex);

    if (m == pivotIndex) {
        return pivotIndex;
    }
    else if ( m > pivotIndex) {
        left =  pivotIndex +1;
    }
    else {
        right = pivotIndex -1;
    }

    return select(arr, left, right, m);
}

// swap element at index i and j
static void swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// return the index of the median of a group of at most five elements
static int median5(int arr[], int left, int right) {
    // insertion sort
    int i = left;
    while (i <= right) {
        int j = i;
        while (j > left && arr[j] < arr[j-1]) {
            swap (arr, j, j-1);
        }
        i++;
    }
    // will return lower median if number of elements is even
    return (left + right)/2 ;
}

int pivot(int arr[], int left, int right) {
    // for 5 or less elements just get median
    if (right - left < 5) return median5(arr, left, right);
    
    //  otherwise move the medians of five-element subgroups to the first n/5 positions
    for (int i = left; i <= right; i += 5) {
        int subRight = i + 4;
        if (i + 4 > right) subRight = right;

        int mid =  median5(arr, i, subRight);
        swap(arr, mid, left + (i-left)/5);
    }

    // compute the median of the n/5 medians-of-five
    return select(arr, left, left + (right-left)/5, left + (right-left)/10);
}


// group a list (ranging from indices left to right) into two parts, those less than a certain element, and those greater than or equal to the element. 
int partition(int arr[], int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    // Move pivot to end
    swap(arr, pivotIndex, right);

    int storeIndex = left;
    for (int i=left; i<right; i++) {
        if (arr[i] < pivotValue) {
            swap (arr, i, storeIndex);
            storeIndex++;
        }
    }
    // Move pivot to its final place
    swap(arr, storeIndex, right);
    return storeIndex;
}


// test
int main() {
    int a[10000];
    int begin = 0, end = 0, m = -1;
    string s;
    
    while ((cout<<"Please type in the elements of the array, enter to end, q to quit:"<<endl) && getline(cin, s) && s.find('q')== string::npos) {
        stringstream ostr(s);
        // cout<<"get elements:"<<s<<":"<<endl;
        while (ostr>>a[end]) {
            // cout<<a[end]<<":";
            end++;
        }
        // cout<<endl;
        // cout<< end - begin<<endl;
        if (end - begin == 0) {
            cout<<"Invalid inputs!"<<endl;
            continue;
        }

        cout<<"Please type in the order of the element you want:"<<endl;
        cin>>m;
        // to eat up the remaining '\n' in the istream
        cin.get();
        if ( m <=0 || m > end -begin) {
            cout<<"Invalid number!"<<endl;
            continue;
        }
        int mth = select(a, begin, end-1, m-1 + begin);
        cout<< "The " << m <<"th element is "<<a[mth] <<endl;
        begin = end;
    }
    return 0;
}
