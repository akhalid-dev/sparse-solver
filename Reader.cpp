#include "Reader.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @brief 
 * 
 * @param path The path to the matrix file.
 * @param type The type of the format: d for dense, s for sparse.
 * @param compression The type of the format to store i.e: csc, csr etc.
 * @return tuple<vector<double>*, vector<int>*, vector<int>*> 
 */
tuple<vector<double>, vector<int>, vector<int>>& Reader::read_from_file(string path, Type type, Compress compression=CSC) {

    //Open the path
    ifstream file(path);

    if (file.fail()){
        throw std::runtime_error(std::string("Failed to open: ") + path);
    }

    // Declare variables:
    int M, N, L;

    // Ignore Comments:
    while (file.peek() == '%') file.ignore(2048, '\n');
    
    file >> M >> N >> L;
    
    data.resize(L);
    indices.resize(L);
    indptr.reserve(N);

    if (type == sparse) {
        int prev_col = -1;
        for (int i = 0; i < L; i++)
            {
                int row, col;
                double value;
                file >> row >> col >> value; 
                indices[i] = row - 1;
                data[i] = value;
                if (col != prev_col)
                    indptr.push_back(i);
                prev_col = col;
            }
        file.close();
    }

            
    values = make_tuple(data, indices, indptr);
    return values; 
}

void Reader::read_dense_matrix(string file_path, vector<double> &matrix){
    ifstream file(file_path);
    int num_row, num_col, num_lines;

    // Ignore comments headers
    while (file.peek() == '%') file.ignore(2048, '\n');
    if (file.fail())
        cout << "Failed to open" << endl;

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


/**
 * @brief Construct a new Reader:: Reader object
 * 
 * @param path The path to the matrix file.
 * @param type The type of the format to store i.e: csc, csr etc.
 */
Reader::Reader(string path, Type type, Compress compression) {
    //read_from_file(path, type, compression);
}


/**
 * @brief Destroy the Reader:: Reader object
 * 
 */
Reader::~Reader()
{
    data.clear();
    indices.clear();
    indptr.clear();
}

    





