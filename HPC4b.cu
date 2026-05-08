// CUDA Program for Matrix Multiplication
// Compile: nvcc file.cu
// Run: ./a.out
#include<iostream>
using namespace std;

// CUDA Kernel
__global__ void multiply(int *a,int *b,int *c,int n){

    int row = threadIdx.x;
    int col = threadIdx.y;

    int sum = 0;

    for(int k=0;k<n;k++)
        sum += a[row*n+k] * b[k*n+col];

    c[row*n+col] = sum;
}

int main(){

    int n;

    cout<<"Enter order of matrix: ";
    cin>>n;

    int size = n*n*sizeof(int);

    int a[n][n], b[n][n], c[n][n];

    cout<<"Enter first matrix:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];

    cout<<"Enter second matrix:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>b[i][j];

    int *d_a,*d_b,*d_c;

    // Allocate GPU memory
    cudaMalloc(&d_a,size);
    cudaMalloc(&d_b,size);
    cudaMalloc(&d_c,size);

    // Copy CPU to GPU
    cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

    // Launch Kernel
    dim3 threads(n,n);

    multiply<<<1,threads>>>(d_a,d_b,d_c,n);

    // Copy GPU to CPU
    cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);

    cout<<"\nMatrix Multiplication using CUDA:\n";

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<c[i][j]<<" ";
        cout<<endl;
    }

    // Free GPU memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
/*Enter order of matrix: 2

Enter first matrix:
1 2
3 4

Enter second matrix:
5 6
7 8
Matrix Multiplication using CUDA:
19 22
43 50*/