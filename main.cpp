#include <iostream>
#include <time.h>
#include <fstream>

#include <tuple>
#include <vector>
#include <cstdlib>

#include <omp.h>
#include "Reader.h"

using namespace std;

bool check(vector<double> A, vector<double> B);
void print_format(vector<double>& Lx, vector<int>& Li, vector<int>& Lp);
int solve_sparse_parallel_optimized(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);
int solve_sparse_parallel(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);
int solve_sparse_optimized(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);
int solve_sparse_naive(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);

int main()
{
    // string path_a = "./matrices/TSOPF_RS_b678_c2/TSOPF_RS_b678_c2.mtx";
    // string path_b = "./matrices/b_for_TSOPF_RS_b678_c2_b.mtx";
    // string path_a = "./matrices/torso1/torso1.mtx";
    // string path_b = "./matrices/b_for_torso1.mtx";
    string path_a = "./matrices/small_A.mtx";
    string path_b = "./matrices/small_B.mtx";

    Reader simple(path_a, Reader::sparse, Reader::CSC);
    auto [Lx, Li, Lp] = simple.read_from_file(path_a, Reader::sparse, Reader::CSC);

    vector<double> matrix_a;
    vector<double> matrix_b;
    vector<double> matrix_c;
    vector<double> matrix_d;

    Reader::read_dense_matrix(path_b, matrix_a);
    Reader::read_dense_matrix(path_b, matrix_b);
    Reader::read_dense_matrix(path_b, matrix_c);
    Reader::read_dense_matrix(path_b, matrix_d);

    for(int i = 0; i < matrix_a.size(); i++) {
        assert (!isnan(matrix_a[i]));
        assert (!isnan(matrix_b[i]));
        assert (!isnan(matrix_c[i]));
        assert (!isnan(matrix_d[i]));
    }
    clock_t tStart = clock();

    solve_sparse_naive(Lp.size(), Lx, Li, Lp, matrix_a);
    solve_sparse_optimized(Lp.size(), Lx, Li, Lp, matrix_b);
    solve_sparse_parallel(Lp.size(), Lx, Li, Lp, matrix_c); 
    solve_sparse_parallel_optimized(Lp.size(), Lx, Li, Lp, matrix_d);

    cout << "Test # 1, passing:" << boolalpha << check(matrix_a, matrix_b) << endl; 
    cout << "Test # 2, passing:" << boolalpha << check(matrix_a, matrix_c) << endl; 
    cout << "Test # 3, passing:" << boolalpha << check(matrix_a, matrix_d) << endl; 

    for (int i = 0; i < Lp.size(); i++) {
        assert (!(isnan(matrix_a[i])));
        assert (!(isnan(matrix_b[i])));
        assert (!(isnan(matrix_c[i])));
        assert (!(isnan(matrix_d[i])));
    }

    printf("Total Time taken: %.7fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); 
    
    return 0;
}



int solve_sparse_naive(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, 
    vector <double> &x){
    cout << "Running naive implementation..." << endl;
    
    if (!L_rows.size() || !L_col_p.size() || !x.size())
        return 0;

    for (int j = 0 ; j < n ; j++){
        
        x[j] /= L_val[L_col_p[j]];
        
        for (int p = L_col_p[j]+1 ; p < L_col_p[j+1] ; p++)
            x[L_rows[p]] -= L_val[p] * x[j];
    }
    return 1;
}

int solve_sparse_optimized(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, 
    vector <double> &x){
    cout << "Running an optimized implementation..." << endl;
    if (!L_rows.size() || !L_col_p.size() || !x.size())
        return 0;

    for (int j = 0 ; j < n ; j++){
        if (x[j] == 0) {
            continue;
        }
        
        x[j] /= L_val[L_col_p[j]];
        
        for (int p = L_col_p[j]+1 ; p < L_col_p[j+1] ; p++)
            x[L_rows[p]] -= L_val[p] * x[j];
    }

    return 1;
}

int solve_sparse_parallel(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, 
    vector <double> &x){

    
    cout << "Running the parallelized implementation..." << endl;
    if (!L_rows.size() || !L_col_p.size() || !x.size())
        return 0;
    #pragma omp parallel
    for (int j = 0 ; j < n ; j++){
        x[j] /= L_val[L_col_p[j]];

        #pragma omp parallel
        for (int p = L_col_p[j]+1 ; p < L_col_p[j+1] ; p++)
            x[L_rows[p]] -= L_val[p] * x[j];
    }

    return 1;
}

int solve_sparse_parallel_optimized(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, 
    vector <double> &x){
    cout << "Running the parallelized optimized implementation..." << endl;
    if (!L_rows.size() || !L_col_p.size() || !x.size())
        return 0;
    #pragma omp parallel
    for (int j = 0 ; j < n ; j++){
        if (x[j] == 0) {
            continue;
        }
        x[j] /= L_val[L_col_p[j]];
        
        #pragma omp parallel
        for (int p = L_col_p[j]+1 ; p < L_col_p[j+1] ; p++)
            x[L_rows[p]] -= L_val[p] * x[j];
    }

    return 1;
}

void print_format(vector<double>& Lx, vector<int>& Li, vector<int>& Lp) {
    for (int i = 0; i < Lx.size(); i++) {
        cout << Lx[i] << " " << Li[i] << endl;
    }

    for (int i = 0; i < Lp.size(); i++) {
        cout << Lp[i] << endl;
    }
}

bool check(vector<double> A, vector<double> B) {
    if (A.size() != B.size()) {
        return false;
    }
    
    for(int i = 0; i < A.size(); i++) {
        if (abs(A[i] - B[i]) >= 0.01) {
            return false;
        }
    }

    return true;
}