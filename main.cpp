#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;


vector<vector<int>> ReadMatrix(string name) {
    vector<vector<int>> matrix;
    ifstream myfile;
    myfile.open(name);
    if (myfile.is_open()) {
        cout << "Reading file '" << name << "'..." << endl;
        string line;
        while (getline(myfile, line))
        {
            vector<int> tmp;

            istringstream iss(line); // Создаем строковый поток для разбора текущей строки

            int num;
            while (iss >> num) { // Считываем числа из строки
                tmp.push_back(num);
            }
            matrix.push_back(tmp);
        }
        myfile.close();
        cout << "Succsesfull" << endl;
    }
    else {
        cout << "We can't opened file '" << name << "' , enter any button to next " << endl;
        getchar();
    }
    return matrix;
}


void PrintMatrix(vector<vector<int>> matrix, int tmp) {
    cout << "Matrix" << tmp << ": " << endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}


vector<vector<int>> Multiplication(vector<vector<int>>MatrixOne, vector<vector<int>>MatrixTwo)
{
    vector<vector<int>> main_tmp;
    if (MatrixOne[0].size() != MatrixTwo.size()) {
        cout << "Sizes of matrices are not compatible for multiplication" << endl;
        return main_tmp; // Returning an empty matrix as multiplication is not possible
    }

    for (int i = 0; i < MatrixOne.size(); i++) {
        vector<int> supporting_tmp;
        for (int j = 0; j < MatrixTwo[0].size(); j++) {
            int sum = 0;
            for (int k = 0; k < MatrixTwo.size(); k++) {
                sum += MatrixOne[i][k] * MatrixTwo[k][j];
            }
            supporting_tmp.push_back(sum);
        }
        main_tmp.push_back(supporting_tmp);
    }
    return main_tmp;
}

bool Verification(vector<vector<int>> CppMatrix, string path1,string path2) {

    
    string command = "python python_check.py " + path1 + " " + path2;
    system(command.c_str());
    vector<vector<int>> PythonMatrix = ReadMatrix("data\\matrix_result_python.txt");
    

    for (int i = 0; i < CppMatrix.size(); i++) {
        for (int j = 0; j < CppMatrix[0].size(); j++) {
            if (PythonMatrix[i][j] != CppMatrix[i][j])
            {
                cout << "Matrix has different";
                return false;
            }
        }
    }
    cout << "Multiplication of matrix is True"<<endl;
    return true;
}
void WriteMatrix(vector<vector<int>> matrix) {
    ofstream outFile("data\\matrix3.txt");
    if (outFile.is_open()) {
        for (const auto& row : matrix) {
            for (int value : row) {
                outFile << value << " ";
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Matrix has been successfully written" << endl;
    }
    else {
        cout << "Unable to open file matrix3 for writing." << endl;
    }
}



void cycle(string path1,string path2) {
    cout << "___________________Work with files: " << path1<< " and "<<path2 <<"___________________" << endl;
    vector<vector<int>> MatrixOne, MatrixTwo, MatrixCppFinal;
    MatrixOne = ReadMatrix(path1);
    MatrixTwo = ReadMatrix(path2);
    PrintMatrix(MatrixOne, 1);
    PrintMatrix(MatrixTwo, 2);
    auto start_time = chrono::high_resolution_clock::now();
    MatrixCppFinal = Multiplication(MatrixOne, MatrixTwo);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Time of work: " << duration.count() << " microseconds" << endl;
    cout << "Elements in  final matrix: " << MatrixCppFinal.size() * MatrixCppFinal[0].size() << endl;
    PrintMatrix(MatrixCppFinal, 3);
    WriteMatrix(MatrixCppFinal);
    Verification(MatrixCppFinal, path1, path2);
}

int main() {
    cycle("data\\A1.txt","data\\B1.txt");
    cycle("data\\A2.txt", "data\\B2.txt");
    cycle("data\\A3.txt", "data\\B3.txt");
    return 0;
}

