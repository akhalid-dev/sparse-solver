#ifndef MAIN_H
#define MAIN_H
#include <tuple>
#include <vector>

using namespace std;
/**
 * @brief This function is used to test the results of two implmentations
 * 
 * @param A The x matrix using the first implementation
 * @param B The x matrix using the second implementation
 * @return true : The two vectors are equal.
 * @return false : The two vectors are not equal.
 */
bool check(vector<double> A, vector<double> B);

/**
 * @brief This function can be used to print compression formats i.e CSC.
 * 
 * @param Lx is array of corresponding nonzero values
 * @param Li is array of row indices
 * @param Lp points to column starts in indices and data
 */
void print_format(vector<double>& Lx, vector<int>& Li, vector<int>& Lp);

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
int solve_sparse_parallel_optimized(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);

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
int solve_sparse_parallel(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);

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
int solve_sparse_optimized(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);

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
int solve_sparse_naive(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, vector <double> &x);

#endif