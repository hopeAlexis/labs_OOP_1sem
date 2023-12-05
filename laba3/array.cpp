#include <vector>
#include <iostream>

//using template and typename T for different variable types
template<class T>
class Arr3D
{
private:
    std::vector<T> cube;    //vector to represent a cube(3D array)
    int d1, d2, d3;
public:
    Arr3D(int d1, int d2, int d3) : d1(d1), d2(d2), d3(d3), cube(d1 * d2 * d3) {}

    //in this vector we first put all k (3rd dimension)
    //then all j on top of 3rd dim (therefore j * d3 + k)
    //ditto i * d3 * d2
    //example: cube 10*10*10 --> element (0;1;3) is in cube[3 + 10]

    T& operator()(int i, int j, int k)
    {
        return cube[k + j * d3 + i * d3 * d2];
    }

    std::vector<T> getCube() const
    {
        return cube;
    }

    //const function 'cause it's a getter
    std::vector<T> getValues1(int i) const;
    std::vector<T> getValues2(int j) const;
    std::vector<T> getValues3(int k) const;
    std::vector<T> getValues12(int i, int j) const;
    std::vector<T> getValues13(int i, int k) const;
    std::vector<T> getValues23(int j, int k) const;

    //receive an address of an array to copy (const 'cause we don't change the array)
    void setValues1(int i, const std::vector<std::vector<T>>& arr);
    void setValues2(int j, const std::vector<std::vector<T>>& arr);
    void setValues3(int k, const std::vector<std::vector<T>>& arr);
    void setValues12(int i, int j, const std::vector<std::vector<T>>& arr);
    void setValues13(int i, int k, const std::vector<std::vector<T>>& arr);
    void setValues23(int j, int k, const std::vector<std::vector<T>>& arr);
};


template<class T>
std::ostream& operator<< (std::ostream &out, Arr3D<T>& arr)
{
    for (int i = 0; i < arr.getCube().size(); i++)
    {
        out << arr.getCube()[i] << " ";
    }
    return out;
}

template<typename T>
std::vector<T> Arr3D<T>::getValues1(int i)  const
{
    std::vector<T> portion(d2 * d3);    //we cut a portion of a cube until i
    for (int j = 0; j < d2; j++)
    {
        for (int k = 0; k < d3; k++)
        {
            portion[j * d3 + k] = cube[k + j * d3 + i * d3 * d2];
        }
    }
    return portion;
}

template<typename T>
std::vector<T> Arr3D<T>::getValues2(int j) const
{
    std::vector<T> portion(d1 * d3);
    for (int i = 0; i < d1; i++)
    {
        for (int k = 0; k < d3; k++)
        {
            portion[i * d3 + k] = cube[k + j * d3 + i * d3 * d2];
        }
    }
    return portion;
}

template<typename T>
std::vector<T> Arr3D<T>::getValues3(int k) const
{
    std::vector<T> portion(d1 * d2);
    for (int i = 0; i < d1; i++)
    {
        for (int j = 0; j < d2; j++)
        {
            portion[i * d2 + j] = cube[k + j * d3 + i * d3 * d2];
        }
    }
    return portion;
}

template<typename T>
std::vector<T> Arr3D<T>::getValues12(int i, int j) const
{
    std::vector<T> portion(d3);
    for (int k = 0; k < d3; k++)
    {
        portion[k] = cube[k + j * d3 + i * d3 * d2];
    }
    return portion;
}

template<typename T>
std::vector<T> Arr3D<T>::getValues13(int i, int k) const
{
    std::vector<T> portion(d2);
    for (int j = 0; j < d2; j++)
    {
        portion[j] = cube[k + j * d3 + i * d3 * d2];
    }
    return portion;
}

template<typename T>
std::vector<T> Arr3D<T>::getValues23(int j, int k) const
{
    std::vector<T> portion(d1);
    for (int i = 0; i < d1; i++)
    {
        portion[i] = cube[k + j * d3 + i * d3 * d2];
    }
    return portion;
}

template<typename T>
void Arr3D<T>::setValues1(int i, const std::vector<std::vector<T>>& arr)
{
    for (int j = 0; j < d2; j++)
    {
        for (int k = 0; k < d3; k++)
        {
            cube[k + j * d3 + i * d3 * d2] = arr[j][k];
        }
    }
}

template<typename T>
void Arr3D<T>::setValues2(int j, const std::vector<std::vector<T>>& arr)
{
    for (int i = 0; i < d1; i++)
    {
        for (int k = 0; k < d3; k++)
        {
            cube[k + j * d3 + i * d3 * d2] = arr[i][k];
        }
    }
}

template<typename T>
void Arr3D<T>::setValues3(int k, const std::vector<std::vector<T>>& arr)
{
    for (int i = 0; i < d1; i++)
    {
        for (int j = 0; j < d2; j++)
        {
            cube[k + j * d3 + i * d3 * d2] = arr[i][j];
        }
    }
}

template<typename T>
void Arr3D<T>::setValues12(int i, int j, const std::vector<std::vector<T>>& arr)
{
    for (int k = 0; k < d3; k++)
    {
        cube[k + j * d3 + i * d3 * d2] = arr[k];
    }
}

template<typename T>
void Arr3D<T>::setValues13(int i, int k, const std::vector<std::vector<T>>& arr)
{
    for (int j = 0; j < d2; j++)
    {
        cube[k + j * d3 + i * d3 * d2] = arr[j];
    }
}

template<typename T>
void Arr3D<T>::setValues23(int j, int k, const std::vector<std::vector<T>>& arr)
{
    for (int i = 0; i < d1; i++)
    {
        cube[k + j * d3 + i * d3 * d2] = arr[i];
    }
}

template<typename T>
Arr3D<T> fillOne(int d1, int d2, int d3)
{
    Arr3D<T> arr(d1, d2, d3);
    T one = static_cast<T>(1);      //using static cast to convert 1 into type T

    for (int i = 0; i < d1; i++)
    {
        for (int j = 0; j < d2; j++)
        {
            for (int k = 0; k < d3; k++)
            {
                arr(i, j, k) = one;
            }
        }
    }
    return arr;
}

template<typename T>
Arr3D<T> fillZero(int d1, int d2, int d3)
{
    Arr3D<T> arr(d1, d2, d3);
    T zero = static_cast<T>(0);     //using static cast to convert 1 into type T

    for (int i = 0; i < d1; i++)
    {
        for (int j = 0; j < d2; j++)
        {
            for (int k = 0; k < d3; k++)
            {
                arr(i, j, k) = zero;
            }
        }
    }
    return arr;
}

template<typename T>
Arr3D<T> fillAny(int d1, int d2, int d3, T value)
{
    Arr3D<T> arr(d1, d2, d3);

    for (int i = 0; i < d1; i++)
    {
        for (int j = 0; j < d2; j++)
        {
            for (int k = 0; k < d3; k++)
            {
                arr(i, j, k) = value;
            }
        }
    }
    return arr;
}

int main()
{
    Arr3D<int> arr(3,3,3);
    std::cout << arr << "\n\n";

    arr = fillAny(3, 3, 3, 7);
    std::cout << arr << "\n\n";
    std::vector<std::vector<int>> values = { {0, 1, 2}, {5, 5, 5}, {6, 8, 9} };     //vector of vectors
    arr.setValues1(2, values);
    std::cout << arr << "\n\n";
}

