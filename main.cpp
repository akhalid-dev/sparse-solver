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


    //Create a Reader Object
    Reader simple(path_a, Reader::sparse, Reader::CSC);
    auto [Lx, Li, Lp] = simple.read_from_file(path_a, Reader::sparse, Reader::CSC);

    //Creating four copies of B vector
    vector<double> b_1;
    vector<double> b_2;
    vector<double> b_3;
    vector<double> b_4;

    Reader::read_dense_matrix(path_b, b_1);
    Reader::read_dense_matrix(path_b, b_2);
    Reader::read_dense_matrix(path_b, b_3);
    Reader::read_dense_matrix(path_b, b_4);

    clock_t tStart = clock();

    //Solving using each implementation
    solve_sparse_naive(Lp.size(), Lx, Li, Lp, b_1);
    solve_sparse_optimized(Lp.size(), Lx, Li, Lp, b_2);
    solve_sparse_parallel(Lp.size(), Lx, Li, Lp, b_3); 
    solve_sparse_parallel_optimized(Lp.size(), Lx, Li, Lp, b_4);

    //Printing out test results
    cout << "Test # 1, passing: " << boolalpha << check(b_1, b_2) << endl; 
    cout << "Test # 2, passing: " << boolalpha << check(b_1, b_3) << endl; 
    cout << "Test # 3, passing: " << boolalpha << check(b_1, b_4) << endl; 

    
    printf("Total Time taken: %.7fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); 
    
    return 0;
}


/**
 * @brief This function implements the naive solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 */
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

/**
 * @brief This function implements the optimised solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 */
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

/**
 * @brief This function implements the parallelized solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 */
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

/**
 * @brief This function implements the optimised and parallelized solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 */
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

/**
 * @brief This function can be used to print compression formats i.e CSC.
 * 
 * @param Lx is array of corresponding nonzero values
 * @param Li is array of row indices
 * @param Lp points to column starts in indices and data
 */
void print_format(vector<double>& Lx, vector<int>& Li, vector<int>& Lp) {
    for (int i = 0; i < Lx.size(); i++) {
        cout << Lx[i] << " " << Li[i] << endl;
    }

    for (int i = 0; i < Lp.size(); i++) {
        cout << Lp[i] << endl;
    }
}

/**
 * @brief This function is used to test the results of two implmentations
 * 
 * @param A The x matrix using the first implementation
 * @param B The x matrix using the second implementation
 * @return true : The two vectors are equal.
 * @return false : The two vectors are not equal.
 */
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