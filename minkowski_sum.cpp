#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// print 2D vector coordinate values
void print2DVector(vector<vector<int>> vec)
{
    // Sorting the vector for grading purpose
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) 
    {
        for (int j = 0; j < vec[0].size(); ++j) 
        {
            cout << vec[i][j] << "  ";
        }
        cout << endl;
    }
}

vector<vector<int>> delete_duplicates(vector<vector<int>> C)
{
    vector<vector<int>> C_new;
    
    sort(C.begin(), C.end());
    
    for (int i = 0; i < C.size() -1; i++)
    {
        if (C[i] != C[i+1])
            C_new.push_back(C[i]);
    }
    
    C_new.push_back(C[C.size() -1]);
    return C_new;
}

vector<vector<int>> minkowski_sum(vector<vector<int>> A, vector<vector<int>> B)
{
    vector<vector<int>> C;
    
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B.size(); j++)
        {
            vector<int> Ci = {A[i][0] + B[j][0], A[i][1] + B[j][1]};
            C.push_back(Ci);
        }
    }

    C = delete_duplicates(C);
    return C;
}

int main()
{
    // start with 2 triangles expressed as 2d vectors
    vector<vector<int>> A(3, vector<int>(2));
    A = {{0, 1}, {1, 0}, {0, -1}};
    vector<vector<int>> B(3, vector<int>(2));
    B = {{0, 0}, {1, 1}, {1, -1}};
    
    // compute minkowski sum of triangle A and B
    vector<vector<int>> C;
    C = minkowski_sum(A, B);

    print2DVector(C);

    return 0;
}
