#ifndef MAIN_H
#define MAIN_H
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
        tuple<vector<double>, vector<int>, vector<int>> values
        
};


#endif