#include <iostream>
#include <vector>
using namespace std;

// 원소값과 인덱스를 함께 저장하기 위한 구조체
struct Pair {
    int val;  // 값
    int idx;  // 원래 인덱스
};

// 병합하면서 오른쪽에 있는 더 작은 원소 수를 계산
void merge(vector<Pair>& A, vector<int>& counts, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Pair> L(n1);
    vector<Pair> R(n2);

    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int j = 0; j < n2; j++) R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;
    int rightCount = 0;  // 오른쪽에서 이미 지나간(더 작은) 원소 수

    while (i < n1 && j < n2) {
        if (L[i].val <= R[j].val) {
            counts[L[i].idx] += rightCount; // 오른쪽에서 이미 지난 더 작은 원소 수 누적
            A[k++] = L[i++];
        } else {
            rightCount++; // 오른쪽에서 더 작은 값 등장
            A[k++] = R[j++];
        }
    }

    // 왼쪽 배열에 남은 원소 처리
    while (i < n1) {
        counts[L[i].idx] += rightCount;
        A[k++] = L[i++];
    }

    // 오른쪽 배열 남은 원소 복사
    while (j < n2) {
        A[k++] = R[j++];
    }
}

// 분할정복 기반 Merge Sort
void mergeSort(vector<Pair>& A, vector<int>& counts, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(A, counts, left, mid);
    mergeSort(A, counts, mid + 1, right);
    merge(A, counts, left, mid, right);
}

// Wrapper 함수: 실제 실행
vector<int> countSmaller(vector<int>& nums) {
    int n = nums.size();
    vector<Pair> A(n);
    vector<int> counts(n, 0);

    for (int i = 0; i < n; i++) {
        A[i].val = nums[i];
        A[i].idx = i;
    }

    mergeSort(A, counts, 0, n - 1);
    return counts;
}

int main() {
    vector<int> nums = {5, 2, 6, 1};
    vector<int> result = countSmaller(nums);

    cout << "Input : ";
    for (int x : nums) cout << x << " ";
    cout << "\n";

    cout << "Count of smaller elements to right:\n";
    for (int x : result) cout << x << " ";
    cout << "\n";

    return 0;
}
