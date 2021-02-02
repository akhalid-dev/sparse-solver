#ifndef READER_H
#define READER_H
#include <tuple>
#include <vector>

using namespace std;

class Reader {
    public:
        enum Type {sparse, dense};
        enum Compress {CSC, CCS, CSR, CRS};

        Reader(string path, Type type, Compress compression);
        ~Reader();
        tuple<vector<double>, vector<int>, vector<int>>& read_from_file(string path, Type type, Compress compression);
        
        static void read_dense_matrix(string file_path, vector <double> &matrix);

        
    
    private:
        vector<double> data;
        vector<int> indices;
        vector<int> indptr;
        tuple<vector<double>, vector<int>, vector<int>> values;


        //Dense
        
};


#endif