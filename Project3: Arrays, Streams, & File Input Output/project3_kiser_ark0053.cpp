/*
 * Author: Aidan Kiser
 * UserID: ark0053
 * Filename: project3_kiser_ark0053.cpp
 * Compile: g++ project3_kiser_ark0053.cpp -o Project3.out
 * Run: ./Project3.out
 * Version: 11 October 2023
 * Resources: Ppt notes & online resources for syntax, & sample code from PDF.
 */

#include <fstream>
#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

int readfile(int input_array[], ifstream& instream) {
    int index = 0;

    instream >> input_array[index];
    while (!instream.eof()) {
        index++;
        instream >> input_array[index];
    }
    
    return index;
}

void merge(int array[], int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 

    int* L = new int[n1];
    int* R = new int[n2];

  
    for (i = 0; i < n1; i++) {
        L[i] = array[l + i]; 
    }

    for (j = 0; j < n2; j++) {
        R[j] = array[m + 1 + j];
    }
  
    i = 0;
    j = 0; 
    k = l;

    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            array[k] = L[i]; 
            i++; 
        } 
        else { 
            array[k] = R[j]; 
            j++; 
        } 
        k++; 
    }
  
    while (i < n1) { 
        array[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) { 
        array[k] = R[j]; 
        j++; 
        k++; 
    }

    delete[] L;
    delete[] R;
} 
  
void mergesort(int array[], int l, int r) 
{ 
    if (l < r) { 
        int m = l + (r - l) / 2; 
   
        mergesort(array, l, m); 
        mergesort(array, m + 1, r); 
  
        merge(array, l, m, r); 
    } 
}

int combineandsort(int array_1[], int array_1_size, int array_2[], int array_2_size, int output_array[]) {
    int output_array_size = array_1_size + array_2_size;

    for (int i = 0; i < array_1_size; i++) {
        output_array[i] = array_1[i];
    }
    for (int i = 0; i < array_2_size; i++) {
        output_array[i+array_1_size] = array_2[i];
    }
    mergesort(output_array, 0, output_array_size-1);

    return output_array_size;
}

void writefile(int output_array[], int output_array_size) {
    ofstream outstream;
    string output_filename;
    cout << "Enter the output file name: ";
    cin >> output_filename;

    outstream.open((char*)output_filename.c_str());
    for (int i = 0; i < output_array_size; i++) {
        outstream << output_array[i] << "\n";
    }
    outstream.close();

    cout << "*** Please check the new file - " << output_filename << " ***\n";
}

int main() {
    int array_1[MAX_SIZE];
    int array_1_size;
    int array_2[MAX_SIZE];
    int array_2_size;

    cout << endl << "*** Welcome to Aidan's sorting program ***\n";

    ifstream instream;
    string filename_1;
    bool valid_file_1 = false;
    while (!valid_file_1) {
        cout << "Enter the first input file name: ";
        cin >> filename_1;
        instream.open((char*)filename_1.c_str());
        valid_file_1 = instream.good();
        if (!valid_file_1) {
            cout << "Error: Invalid filename, please try again\n";
            cout << endl;
        }
    }
    
    array_1_size = readfile(array_1, instream);
    instream.close();

    cout << "The list of " << array_1_size << " numbers in file " << filename_1 << " is:\n";
    for (int i = 0; i < array_1_size; i++) {
        cout << array_1[i] << "\n";
    }
    cout << endl;

    string filename_2;
    bool valid_file_2 = false;
    while (!valid_file_2) {
        cout << "Enter the second input file name: ";
        cin >> filename_2;
        instream.open((char*)filename_2.c_str());
        valid_file_2 = instream.good();
        if (!valid_file_2) {
            cout << "Error: Invalid filename, please try again\n";
            cout << endl;
        }
    }
    
    array_2_size = readfile(array_2, instream);
    instream.close();

    cout << "The list of " << array_2_size << " numbers in file " << filename_2 << " is:\n";
    for (int i = 0; i < array_2_size; i++) {
        cout << array_2[i] << "\n";
    }
    cout << endl;

    int output_array[MAX_SIZE];
    int output_array_size = combineandsort(array_1, array_1_size, array_2, array_2_size, output_array);

    cout << "The sorted list of " << output_array_size << " numbers is:";
    for (int i = 0; i < output_array_size; i++) {
        cout << " " << output_array[i];
    }
    cout << endl;

    writefile(output_array, output_array_size);

    cout << "*** Goodbye. ***" << endl;
    return 0;
}