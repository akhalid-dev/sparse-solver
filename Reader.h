#ifndef READER_H
#define READER_H
#include <tuple>
#include <vector>

using namespace std;
/**
 * @brief This is a helper class used to read matrices from the file.
 * 
 */
class Reader {
    public:
        /** An enum Type. 
         *  The documentation block cannot be put after the enum! 
         */
        enum Type {
            sparse, /**< Type sparse */
            dense   /**< Type dense */
        };
        
        /** An enum Compress. 
         *  The documentation block cannot be put after the enum! 
         */
        enum Compress {
            CSC, /**< CSC Compression */
            CCS, /**< CCS Compression */
            CSR, /**< CSR Compression */
            CRS  /**< CRS Compression */
        };

        /**
         * @brief Construct a new Reader object
         * 
         * @param path is the directory for matrix
         * @param type is the type of object i.e sparse/dense
         * @param compression is the compression type of the matrix. i.e CSC
         */
        Reader(string path, Type type, Compress compression);

        /**
         * @brief Destroy the Reader object
         * 
         */
        ~Reader();

        /**
         * @brief Reads the matrix from the file and stores it based on type. (Used for sprase)
         * 
         * @param path is the directory for matrix
         * @param type is the type of object i.e sparse/dense
         * @param compression is the compression type of the matrix. i.e CSC
         * @return tuple<vector<double>, vector<int>, vector<int>>& 
         */
        tuple<vector<double>, vector<int>, vector<int>>& read_from_file(string path, Type type, Compress compression);
        
        /**
         * @brief Reads the matrix from the file and stores it based on type. (Used for dense)
         * 
         * @param file_path is the directory for matrix
         * @param matrix is the reference for 2D matrix
         */
        static void read_dense_matrix(string file_path, vector <double> &matrix);

        
    
    private:
        vector<double> data;
        vector<int> indices;
        vector<int> indptr;
        tuple<vector<double>, vector<int>, vector<int>> values;
        
};


#endif

/**
 * \mainpage
 * @brief This function is used to test the results of two implmentations
 * 
 * @param A The x matrix using the first implementation
 * @param B The x matrix using the second implementation
 * @return true : The two vectors are equal.
 * @return false : The two vectors are not equal.

 * 
 * @brief This function implements the naive solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 
 * @brief This function implements the optimised solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 * 
 * @brief This function implements the parallelized solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 * 
 *  * @brief This function implements the optimised and parallelized solver. 
 * 
 * @param n the matrix dimension
 * @param L_val is array of corresponding nonzero values
 * @param L_rows is array of row indices
 * @param L_col_p points to column starts in indices and data
 * @param x the x matrix
 * @return int : successful execution
 * 
 * @brief This function can be used to print compression formats i.e CSC.
 * 
 * @param Lx is array of corresponding nonzero values
 * @param Li is array of row indices
 * @param Lp points to column starts in indices and data
 * 
 * 
 * @brief This function is used to test the results of two implmentations
 * 
 * @param A The x matrix using the first implementation
 * @param B The x matrix using the second implementation
 * @return true : The two vectors are equal.
 * @return false : The two vectors are not equal.
 */