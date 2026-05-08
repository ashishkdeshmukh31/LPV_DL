// Simple HPC Application for AI/ML Domain
// Linear Regression in C++
// Compile: g++ file.cpp -fopenmp
// Run: ./a.out

#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

int main(){

    vector<int> x = {1,2,3,4,5};
    vector<int> y = {2,4,6,8,10};

    int n = x.size();

    double sumx=0,sumy=0,sumxy=0,sumx2=0;

    double st = omp_get_wtime();

    // Parallel Reduction
    #pragma omp parallel for reduction(+:sumx,sumy,sumxy,sumx2)
    for(int i=0;i<n;i++){

        sumx += x[i];
        sumy += y[i];
        sumxy += x[i]*y[i];
        sumx2 += x[i]*x[i];
    }

    // Linear Regression Formula
    double m = (n*sumxy - sumx*sumy) / (n*sumx2 - sumx*sumx);
    double c = (sumy - m*sumx) / n;

    int value = 6;

    double prediction = m*value + c;

    double et = omp_get_wtime();

    cout<<"Prediction for 6 = "<<prediction;

    cout<<"\nExecution Time = "<<et-st<<" sec\n";

    return 0;
}
/*
Prediction for 6 = 12
Execution Time = 0.000012 sec
*/