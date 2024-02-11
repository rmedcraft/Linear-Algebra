#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<double>> mat){
    for(int r = 0; r < mat.size(); r++){
        for(int c = 0; c < mat.at(r).size(); c++){
            cout << mat.at(r).at(c) << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<double>> scale(vector<vector<double>> mat, int row, double scalar){
    cout << "Scale row " << (row + 1) <<  " by " << scalar << endl;
    if(row < mat.size()){
        for(int c = 0; c < mat.at(row).size(); c++){
            if(mat.at(row).at(c) != 0){ // prevents -0 from happening (what happened to two's compliment????)
                mat.at(row).at(c) *= scalar;
            }
            
        }
    }
    printMatrix(mat);
    return mat;
}

vector<vector<double>> swapRows(vector<vector<double>> mat, int row1, int row2){
    cout << "Swap row " << (row1 + 1) << " and " << " row " << (row2 + 1) << endl;
    if(row1 < mat.size() && row2 < mat.size()){
        vector<double> temp = mat.at(row1);
        mat.at(row1) = mat.at(row2);
        mat.at(row2) = temp;
    }
    printMatrix(mat);
    return mat;
}

vector<vector<double>> addRows(vector<vector<double>> mat, int rowFrom, int rowTo, double scalar){
    cout << "Adding " << scalar << " of row " << (rowFrom + 1) << " to row " << (rowTo + 1) << endl;
    if(rowFrom < mat.size() && rowTo < mat.size() && mat.at(rowTo).size() == mat.at(rowFrom).size()){
        for(int c = 0; c < mat.at(rowTo).size(); c++){
            if(mat.at(rowTo).at(c) != 0){
                mat.at(rowTo).at(c) += (scalar * mat.at(rowFrom).at(c));
            }
        }
    }
    printMatrix(mat);
    return mat;
}

vector<vector<double>> rowReduce(vector<vector<double>> mat, int pivotRow, int pivotCol){
    // if the pivot value is zero, then make it not zero.
    if(mat.at(pivotRow).at(pivotCol) == 0){
        for(int c = pivotCol; c < mat.at(pivotRow).size(); c++){
            for(int r = pivotRow + 1; r < mat.size(); r++){
                if(mat.at(r).at(c) != 0){
                    if(pivotRow != r){
                        mat = swapRows(mat, pivotRow, r);
                    }
                    if(pivotCol != c){
                        pivotCol = c;
                    }
                    goto foundPivot; // this is the first time I've ever had a valid use for goto !!!
                }
            }
        }
    }
    foundPivot: 

    // scale pivot to 1 
    mat = scale(mat, pivotRow, 1 / mat.at(pivotRow).at(pivotCol));

    // get everything below the pivot to 0
    for(int r = pivotRow + 1; r < mat.size(); r++){
        if(mat.at(r).at(pivotCol) != 0){
            mat = addRows(mat, pivotRow, r, -mat.at(r).at(pivotCol));
        }
    }

    // find next pivot
    if(pivotRow < mat.size() - 1 && pivotCol < mat.at(pivotRow).size() - 1){
        mat = rowReduce(mat, pivotRow + 1, pivotCol + 1);
    }

    // set everything above pivot to zero
    for(int r = pivotRow - 1; r >= 0; r--){
        if(mat.at(r).at(pivotCol) != 0){
            mat = addRows(mat, pivotRow, r, -mat.at(r).at(pivotCol));
        }
        
    }
    return mat;
}

int main(){
    // matrix that gets row reduced
    vector<vector<double>> mat {
        {0, 4, 2, 10, 9},
        {0, 1, 0, 6, 2},
        {0, -9, 8, 7, 6},
        {0, 1, 1, 1, 1}, 
        {0, 0, 0, 0, 0}
    };

    mat = rowReduce(mat, 0, 0);
    cout << "Final row reduced matrix: " << endl;
    printMatrix(mat);
    
}