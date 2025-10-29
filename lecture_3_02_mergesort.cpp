#include <iostream>
#include <climits> // INT_MAX
using namespace std;

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int* L = new int[n1 + 1];
    int* R = new int[n2 + 1];

    for (int i = 0; i < n1; ++i) 
        L[i] = A[p + i];
    for (int j = 0; j < n2; ++j) 
        R[j] = A[q + 1 + j];

    L[n1] = INT_MAX; // Sentinel
    R[n2] = INT_MAX;

    int i = 0, j = 0;

    for (int k = p; k <= r; ++k) {
        if (L[i] <= R[j]) 
            A[k] = L[i++];
        else               
            A[k] = R[j++];
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int A[], int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;  //  q 선언 및 초기화
        mergeSort(A, p, q);       // 왼쪽 절반 정렬
        mergeSort(A, q + 1, r);   // 오른쪽 절반 정렬
        merge(A, p, q, r);        // 두 부분을 병합
    }
}

int main() {
    int A[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(A) / sizeof(A[0]);

    mergeSort(A, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) 
        cout << A[i] << ' ';
    
    return 0;
}



// #include <iostream>
// #include <climits> // For INT_MAX
// using namespace std;

// void merge(int A[], int p, int q, int r) {
//     int n1 = q - p + 1;
//     int n2 = r - q;

//     int* L = new int[n1 + 1];
//     int* R = new int[n2 + 1];

//     for (int i = 0; i < n1; i++)
//         L[i] = A[p + i];
//     for (int j = 0; j < n2; j++)
//         R[j] = A[q + 1 + j];
//     L[n1] = INT_MAX; // Sentinel value
//     R[n2] = INT_MAX;
    
//     int i = 0, j = 0;
    
//     for (int k = p; k <= r; k++) {
//         if (L[i] <= R[j]) A[k] = L[i++];
//         else A[k] = R[j++];
//     }

//     delete[] L;
//     delete[] R;
// }

// void mergeSort(int A[], int p, int r) {
//     if (p < r) {
//         q = (p + r) / 2 ;
//         mergeSort(A, p, q);     // 왼쪽 절반 정렬
//         mergeSort(A, q+1, r);    // 오른쪽 절반 정렬
//         merge(A, p, q, r) ;      // 두 부분을 병합
//     }
// }
// int main() {
//     int A[] = {38, 27, 43, 3, 9, 82, 10};
//     int n = sizeof(A) / sizeof(A[0]);
//     mergeSort(A, 0, n - 1);

//     cout << "Sorted array: ";
//     for (int i = 0; i < n; i++) {
//         cout << A[i] << " ";
//     }
//     return 0;
// }