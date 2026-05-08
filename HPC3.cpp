// Parallel Reduction Operations using OpenMP
// Compile: g++ file.cpp -fopenmp

#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

int main() {

    int n;

    cout<<"Enter size of array: ";
    cin>>n;

    vector<int> a(n);

    cout<<"Enter elements:\n";

    for(int i=0;i<n;i++)
        cin>>a[i];

    int sum=0, min=a[0], max=a[0];

    double st=omp_get_wtime();

    // Parallel Sum
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++)
        sum += a[i];

    // Parallel Min
    #pragma omp parallel for reduction(min:min)
    for(int i=0;i<n;i++)
        if(a[i] < min)
            min = a[i];

    // Parallel Max
    #pragma omp parallel for reduction(max:max)
    for(int i=0;i<n;i++)
        if(a[i] > max)
            max = a[i];

    double avg = (double)sum / n;

    double et=omp_get_wtime();

    cout<<"\nSum = "<<sum;
    cout<<"\nMinimum = "<<min;
    cout<<"\nMaximum = "<<max;
    cout<<"\nAverage = "<<avg;

    cout<<"\nExecution Time = "<<et-st<<" sec\n";

    return 0;
}
/*Enter size of array: 5
Enter elements:
10 20 30 40 50
Sum = 150
Minimum = 10
Maximum = 50
Average = 30
Execution Time = 0.000012 sec*/