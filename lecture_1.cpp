#include <iostream>
#include <chrono>
#include <cstdlib> // rand, srand
#include <ctime> // time
using namespace std;
using namespace chrono;

const int SIZE = 4000;

int MaxSubSum1(int A[], int n) {
    int MaxSum= 0;
    for (int i= 0; i< n; i++)
        for (int j = i; j < n; j++) {
            int ThisSum= 0;
            for (int k = i; k <= j; k++)
                ThisSum+= A[k];
            if (ThisSum> MaxSum)
                MaxSum= ThisSum;
        }
    return MaxSum;
}

int MaxSubSum2(int A[], int n) {
    int MaxSum= 0;
    for (int i= 0; i< n; i++) {
        int ThisSum= 0;
        for (int j = i; j < n; j++) {
            ThisSum+= A[j];
            if (ThisSum> MaxSum)
            MaxSum= ThisSum;
        }
    }
    return MaxSum;
}

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

int MaxSubSum3(int a[], int left, int right) {
    if (left == right)  // Base case
        return a[left] > 0 ? a[left] : 0;

    int center = (left + right) / 2;
    int maxLeftSum= MaxSubSum3(a, left, center);
    int maxRightSum= MaxSubSum3(a, center + 1, right);
    
    int maxLeftBorderSum= 0, leftBorderSum= 0;
    for (int i= center; i>= left; i--) {
        leftBorderSum+= a[i];
        if (leftBorderSum> maxLeftBorderSum)
            maxLeftBorderSum= leftBorderSum;
    }

    int maxRightBorderSum= 0, rightBorderSum= 0;
    for (int i= center + 1; i<= right; i++) {
        rightBorderSum+= a[i];
        if (rightBorderSum> maxRightBorderSum)
            maxRightBorderSum= rightBorderSum;
    }

    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum+ maxRightBorderSum);
}

int MaxSubSum4(int A[], int n) {
    int MaxSum= 0, ThisSum= 0;
    for (int j = 0; j < n; j++) {
        ThisSum+= A[j];
        if (ThisSum> MaxSum)
            MaxSum= ThisSum;
        else if (ThisSum< 0)
            ThisSum= 0;
    }
    return MaxSum;
}

int main() {
    int A[SIZE];

    srand(static_cast<unsigned int>(time(nullptr))); // 시드 설정
    // 배열에 100 ~ 100 사이 난수 넣기
    for (int i = 0; i < SIZE; i ++) {
        A[i] = (rand() % 201) - 100; // rand() % (max min + 1) + min
    }

    // 시간측정시작
    auto start = high_resolution_clock::now();
    int maxSum= MaxSubSum1(A, SIZE);
    // 시간측정종료
    auto end = high_resolution_clock::now();
    duration<double> exec_time= end -start;
    cout<< "Max Subsequence Sum 1: " << maxSum<< endl;
    cout<< "Execution time: " << exec_time.count() << " seconds" << endl;

    // 시간 측정 시작
    start = high_resolution_clock::now();    
    maxSum = MaxSubSum2(A,SIZE);    
    // 시간 측정 종료
    end = high_resolution_clock::now();
    exec_time = end - start;

    cout << "Max Subsequence Sum 2: " << maxSum << endl;
    cout << "Execution time: " << exec_time.count () << " seconds" << endl;


    // 시간측정시작
    start = high_resolution_clock::now();
    maxSum= MaxSubSum3(A, 0, SIZE -1);
    // 시간측정종료
    end = high_resolution_clock::now();
    exec_time= end -start;
    cout<< "Max Subsequence Sum 3: " << maxSum<< endl;
    cout<< "Execution time: " << exec_time.count() << " seconds" << endl;

    // 시간측정시작
    start = high_resolution_clock::now();
    maxSum= MaxSubSum4(A, SIZE);
    // 시간측정종료
    end = high_resolution_clock::now();
    exec_time= end -start;
    cout<< "Max Subsequence Sum 4: " << maxSum<< endl;
    cout<< "Execution time: " << exec_time.count() << " seconds" << endl;

    return 0;
}
