#include <iostream>
#include <vector>
using namespace std;

// 병합하면서 inversion 개수를 세는 함수
long long mergeAndCount(vector<int>& A, int left, int mid, int right) {
    vector<int> L(A.begin() + left, A.begin() + mid + 1);
    vector<int> R(A.begin() + mid + 1, A.begin() + right + 1);

    int i = 0, j = 0;
    int nL = L.size(), nR = R.size();
    long long invCount = 0;

    int k = left;
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
            invCount += (nL - i);  // 핵심: L[i] 이후 모든 원소가 R[j]보다 큼
        }
    }

    // 남은 원소들 복사
    while (i < nL) A[k++] = L[i++];
    while (j < nR) A[k++] = R[j++];

    return invCount;
}

// 재귀적으로 분할정복
long long inversionSort(vector<int>& A, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += inversionSort(A, left, mid);      // 왼쪽 부분
        invCount += inversionSort(A, mid + 1, right); // 오른쪽 부분
        invCount += mergeAndCount(A, left, mid, right); // 병합 시 cross inversions 세기
    }
    return invCount;
}

int main() {
    vector<int> A = {8, 2, 91, 22, 57};

    cout << "Before sort: ";
    for (int x : A) cout << x << " ";
    cout << endl;

    long long inversions = inversionSort(A, 0, A.size() - 1);

    cout << "Sorted array: ";
    for (int x : A) cout << x << " ";
    cout << endl;

    cout << "Number of inversions: " << inversions << endl;

    return 0;
}
