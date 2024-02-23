#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;


std::vector<std::vector<int>> ReadMatrix(string name) {
    std::vector<std::vector<int>> matrix;
    ifstream myfile;
    myfile.open(name);
    if (myfile.is_open()) {
        cout << "Reading file '" << name << "'..." << endl;
        string line;
        while (getline(myfile, line))
        {
            std::vector<int> tmp;

            std::istringstream iss(line); // Создаем строковый поток для разбора текущей строки

            int num; 
            while (iss >> num) { // Считываем числа из строки
                tmp.push_back(num); 
            }
            matrix.push_back(tmp);
        }
        myfile.close();
        cout << "Succsesfull"<< endl;
    }
    else {
        cout << "We can't opened file '"<<name<<"' , enter any button to next " << endl; 
        getchar();
    }
    return matrix;
}


void PrintMatrix(std::vector<std::vector<int>> matrix,int tmp) {
    cout << "Matrix"<<tmp<<": " << endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}


std::vector<std::vector<int>> Multiplication(std::vector<std::vector<int>>MatrixOne, std::vector<std::vector<int>>MatrixTwo)
{
    std::vector<std::vector<int>> main_tmp;
    if (MatrixOne[0].size() !=MatrixTwo.size()) {
        cout << "Sizes of matrices are not compatible for multiplication" << endl;
        return main_tmp; // Returning an empty matrix as multiplication is not possible
    }

    for (int i = 0; i <MatrixOne.size(); i++) {
        std::vector<int> supporting_tmp;
        for (int j = 0; j <MatrixTwo[0].size(); j++) {
            int sum = 0;
            for (int k = 0; k <MatrixTwo.size(); k++) {
                sum +=MatrixOne[i][k] *MatrixTwo[k][j];
            }
            supporting_tmp.push_back(sum);
        }
        main_tmp.push_back(supporting_tmp);
    }
    return main_tmp;
}

bool Verification(std::vector<std::vector<int>> CppMatrix) {

    system("python python_check.py");
    std::vector<std::vector<int>> PythonMatrix = ReadMatrix("matrix_result_python.txt");
    for (int i = 0; i < CppMatrix.size(); i++) {
        for (int j = 0; j < CppMatrix[0].size(); j++) {
            if (PythonMatrix[i][j] != CppMatrix[i][j])
            {
                cout << "Matrix has different";
                return false;
            }
        }
    }
    cout << "Multiplication of matrix is True";
    return true;
}
void WriteMatrix(std::vector<std::vector<int>> matrix) {
    std::ofstream outFile("matrix3.txt");
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



void cycle() {

    std::vector<std::vector<int>> MatrixOne, MatrixTwo, MatrixCppFinal;
   MatrixOne = ReadMatrix("matrix1.txt");
   MatrixTwo = ReadMatrix("matrix2.txt");
    PrintMatrix(MatrixOne, 1);
    PrintMatrix(MatrixTwo, 2);
    auto start_time = std::chrono::high_resolution_clock::now();
    MatrixCppFinal = Multiplication(MatrixOne,MatrixTwo);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Time of work: " << duration.count() << " microseconds" << std::endl;
    std::cout << "Elements in  final matrix: " <<MatrixCppFinal.size() * MatrixCppFinal[0].size() << std::endl;
    PrintMatrix(MatrixCppFinal, 3);
    WriteMatrix(MatrixCppFinal);
    Verification(MatrixCppFinal);



}

int main() {

    return 0;
}

