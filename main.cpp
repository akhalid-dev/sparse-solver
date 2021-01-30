#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int read_sparse_matrix(string file_path, vector <double> &values, vector <int> &rows, vector <int>  &col_ptrs);
void read_dense_matrix(string file_path, vector <double> &matrix);
int solve_sparse_low_tri(const vector <double> &L_values, const vector <int> &L_rows, const vector <int>  &L_col_ptrs, 
                         vector <double> &b_values, vector <int> &b_rows, vector <int>  &b_col_ptrs);

int solve_sparse_naive(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, 
                         vector <double> &x);

int main(int argc, const char * argv[]) {
    
    vector <double> L_val;
    vector <int> L_rows;
    vector <int> L_col_p;

    // vector <double> b_values;
    // vector <int> b_rows;
    // vector <int> b_col_ptrs;

    string L_path = "./TSOPF_RS_b678_c2.mtx";
    string b_path = "./TSOPF_RS_b678_c2_b.mtx";

    int n = read_sparse_matrix(L_path, L_val, L_rows, L_col_p);
    //read_sparse_matrix(b_path, b_values, b_rows, b_col_ptrs);

    vector <double> b;
    read_dense_matrix(b_path, b);

    solve_sparse_naive(n, L_val, L_rows, L_col_p, b);

    return 0;
}

int solve_sparse_naive(int n, const vector <double> &L_val, const vector <int> &L_rows, const vector <int>  &L_col_p, 
                         vector <double> &x){

    if (!L_rows.size() || !L_col_p.size() || !x.size())
        return 0;

    for (int j = 0 ; j < n ; j++){
        x[j] /= L_val[L_col_p[j]];
        for (int p = L_col_p[j]+1 ; p < L_col_p[j+1] ; p++)
            x[L_rows[p]] -= L_val[p] * x[j];
    }

    return 1;
}


int read_sparse_matrix(string file_path, vector <double> &values, vector <int> &rows, vector <int> &col_ptrs){
    // Open the file:
    ifstream file(file_path);
    
    if (file.fail()){
        cout << "Failed to open" << endl;
        return -1;
    }

    // Declare variables:
    int M = 0, N = 0, L = 0;

    // Ignore headers and comments:
    while (file.peek() == '%') file.ignore(2048, '\n');

    // Read defining parameters:
    
    file >> M >> N >> L;
    cout << M << " " << N << " " << L << endl;

    values.resize(L);
    rows.resize(L);
    col_ptrs.reserve(N);

    int prev_row = -1;
    // Read the data
    for (int i = 0; i < L; i++)
    {
        int row, col_ptr, col;
        double value;
        file >> row >> col >> value; 
        rows[i] = row;
        values[i] = value;
        if (row != prev_row)
            col_ptrs.push_back(i);
        prev_row = row;
    }
    file.close();
    return N;
}

void read_dense_matrix(string file_path, vector <double> &matrix){
    ifstream file(file_path);
    int num_row, num_col, num_lines;

    // Ignore comments headers
    while (file.peek() == '%') file.ignore(2048, '\n');
    if (file.fail())
        cout << "Faled to open" << endl;

    // Read number of rows and columns
    file >> num_row>> num_col >> num_lines;

    // Create 2D array and fill with zeros 
    matrix = vector<double>(num_row*num_col, 0.0);

    // fill the matrix with data
    for (int l = 0; l < num_lines; l++)
    {
        double data;
        int row, col;
        file >> row >> col >> data;
        matrix[(row -1) + (col -1) * num_row] = data;
    }

    file.close();
}