#include <bits/stdc++.h>
#include <omp.h>
#include <time.h>

using namespace std;
void serialPrefixSum(const std::vector<int>& input, vector<int>& output) {
    int n = input.size();
    if (n == 0) {
        return; 
    }

    output[0] = input[0];  

    for (int i = 1; i < n; i++) {
        output[i] = output[i - 1] + input[i];
    }
}

int main() {
    clock_t start, end;
    int n;
    cout<<"Enter the size of array: ";
    cin>>n;
    vector<int> arr(n);
    vector<int> prefix_sum(n);
    for(int i=0; i<n; i++){
        arr[i] = i+1;
        prefix_sum[i] = i+1;
    }
    start = clock();
    serialPrefixSum(arr, prefix_sum);

    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("\n Time taken for execution in seconds: %f \n", duration);
    
    // cout<<"Prefix Sum Array:";
    // Print the prefix sum
    // for(int i = 0; i < n; i++) {
    //     std::cout << prefix_sum[i] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}
