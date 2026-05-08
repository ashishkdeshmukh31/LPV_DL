// CUDA Program for Addition of Two Vectors
// Compile: nvcc HPC4a.cu
// Run: ./a.out
//OR
// nvcc HPC4a.cu -o output
// ./output
#include<iostream>
using namespace std;

// CUDA Kernel
__global__ void add(int *a,int *b,int *c,int n){

    int i = threadIdx.x;

    if(i<n)
        c[i] = a[i] + b[i];
}

int main(){

    int n;

    cout<<"Enter size: ";
    cin>>n;

    int a[n], b[n], c[n];

    cout<<"Enter first vector:\n";
    for(int i=0;i<n;i++)
        cin>>a[i];

    cout<<"Enter second vector:\n";
    for(int i=0;i<n;i++)
        cin>>b[i];

    int *d_a,*d_b,*d_c;

    // Allocate GPU memory
    cudaMalloc(&d_a,n*sizeof(int));
    cudaMalloc(&d_b,n*sizeof(int));
    cudaMalloc(&d_c,n*sizeof(int));

    // Copy data CPU to GPU
    cudaMemcpy(d_a,a,n*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,n*sizeof(int),cudaMemcpyHostToDevice);

    // Launch Kernel
    add<<<1,n>>>(d_a,d_b,d_c,n);

    // Copy result GPU to CPU
    cudaMemcpy(c,d_c,n*sizeof(int),cudaMemcpyDeviceToHost);

    cout<<"\nResult Vector:\n";

    for(int i=0;i<n;i++)
        cout<<c[i]<<" ";

    // Free GPU memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
/*Enter size: 5
Enter first vector:
1 2 3 4 5
Enter second vector:
10 20 30 40 50
Result Vector:
11 22 33 44 55*/