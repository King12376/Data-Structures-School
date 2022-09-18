#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory
{
public:
  static T **allocArray(int m, int n)
  {
    T **p;
    p = new T*[m];//save to heap a new array of pointers

    T *array = new T [m * n];//created consecutive memory of size m*n (1-D array)

    for (int i = 0; i < m; i++)
    {
        (p)[i] = &array[i * n];//for each (i)th element of p, I point it to the adress of the beginning of a segment of size n, to symbolize different rows within the actual 1-D array
    }

    // for(int i=0; i<m; i++){
    //     (p)[i] = new T[n];
    // }

    return p;
  }
};

int main()
{
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++){
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";
    //cout<<endl;
  }
}
