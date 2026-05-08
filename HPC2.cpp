// Sequential and Parallel Bubble & Merge Sort using OpenMP
// Compile: g++ file.cpp -fopenmp
// Run: ./a.out

#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

// Bubble Sort
void bubble(vector<int> a,bool parallel){
    int n=a.size();
    double st=omp_get_wtime();

    for(int i=0;i<n-1;i++){

        #pragma omp parallel for if(parallel)
        for(int j=0;j<n-i-1;j++){

            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
        }
    }

    cout<<(parallel?"\nParallel Bubble Sort: ":"\nSequential Bubble Sort: ");

    for(int x:a) cout<<x<<" ";

    cout<<"\nTime: "<<omp_get_wtime()-st<<" sec\n";
}

// Merge Function
void merge(vector<int>& a,int l,int m,int r){

    vector<int> t;
    int i=l,j=m+1;

    while(i<=m && j<=r)
        t.push_back(a[i]<a[j]?a[i++]:a[j++]);

    while(i<=m) t.push_back(a[i++]);
    while(j<=r) t.push_back(a[j++]);

    for(int k=l;k<=r;k++)
        a[k]=t[k-l];
}

// Sequential Merge Sort
void seqMerge(vector<int>& a,int l,int r){

    if(l>=r) return;

    int m=(l+r)/2;

    seqMerge(a,l,m);
    seqMerge(a,m+1,r);

    merge(a,l,m,r);
}

// Parallel Merge Sort
void parMerge(vector<int>& a,int l,int r){

    if(l>=r) return;

    int m=(l+r)/2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parMerge(a,l,m);

        #pragma omp section
        parMerge(a,m+1,r);
    }

    merge(a,l,m,r);
}

int main(){

    int n;

    cout<<"Enter size: ";
    cin>>n;

    vector<int> a(n),b,c;

    cout<<"Enter elements:\n";

    for(int i=0;i<n;i++)
        cin>>a[i];

    b=c=a;

    // Bubble Sort
    bubble(a,false);
    bubble(a,true);

    // Sequential Merge Sort
    double st=omp_get_wtime();

    seqMerge(b,0,n-1);

    cout<<"\nSequential Merge Sort: ";

    for(int x:b) cout<<x<<" ";

    cout<<"\nTime: "<<omp_get_wtime()-st<<" sec\n";

    // Parallel Merge Sort
    st=omp_get_wtime();

    parMerge(c,0,n-1);

    cout<<"\nParallel Merge Sort: ";

    for(int x:c) cout<<x<<" ";

    cout<<"\nTime: "<<omp_get_wtime()-st<<" sec\n";

    return 0;
}
/*Enter size: 5
Enter elements:
5 2 4 1 3
Sequential Bubble Sort: 1 2 3 4 5
Time: 0.000021 sec

Parallel Bubble Sort: 1 2 3 4 5
Time: 0.000010 sec

Sequential Merge Sort: 1 2 3 4 5
Time: 0.000015 sec

Parallel Merge Sort: 1 2 3 4 5
Time: 0.000007 sec*/