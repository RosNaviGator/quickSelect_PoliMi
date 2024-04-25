#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


#define N 100
#define MAX 1000
#define seed chrono::system_clock::now().time_since_epoch().count()

using namespace std;
using vectInt = vector<int>;
using llu = long long unsigned int;


void newSwap(vectInt& vect, int i, int j)
{
    int temp = vect[i];
    vect[i] = vect[j];
    vect[j] = temp;
}

void printVec(vectInt& vect)
{
    for(llu i=0; i< vect.size(); i++)
    {
        cout << vect[i] <<" ";
    }
    cout << endl << "size is " << vect.size() <<endl;
    return;
}

int sort5(vectInt vect, vectInt& index, int i) 
{

    for( int j= i*5; j< 5*(i+1)-1; j++)
    {
        for(int z = i*5; z < 5*(i+1)-1; z++)
        {
            if (vect[z] > vect[z+1])
            {
                newSwap(vect, z, z+1);
                newSwap(index, z, z+1);
            }
        }
    }
    return (index[5*i+2]);

}

void moveElement(std::vector<int>& vec, int fromIndex, int toIndex) {
        // Temporarily store the element to be moved
    int valueToMove = vec[fromIndex];

    // Move elements to the right
    if (fromIndex < toIndex) {
        for (int i = fromIndex; i < toIndex; ++i) {
            vec[i] = vec[i + 1];
        }
    }
    // Move elements to the left
    else {
        for (int i = fromIndex; i > toIndex; --i) {
            vec[i] = vec[i - 1];
        }
    }

    // Place the element at the new position
    vec[toIndex] = valueToMove;
}



int newSort(vector<int> &vect, vector<int> &index, int i)
{
    i = 5 * i;  

    if (vect[index[i + 1]] < vect[index[i]])
    {
        swap(index[i], index[i + 1]);
    }
    if (vect[index[i + 3]] < vect[index[i + 2]])
    {
        swap(index[i + 2], index[i + 3]);
    }

    if (vect[index[i + 3]] < vect[index[i + 1]])
    {
        swap(index[i], index[i + 2]);
        swap(index[i + 1], index[i + 3]);
    }

    if (vect[index[i + 4]] < vect[index[i + 1]])
    {
        if (vect[index[i + 4]] < vect[index[i]])
        {
            moveElement(index, i + 4, i);
            newSwap(index, i + 4, i + 3);
        }
        else
        {
            moveElement(index, i + 4, i + 1);
            newSwap(index, i + 4, i + 3);
        }
    }
    else
    {
        if (vect[index[i + 4]] < vect[index[i + 3]])
        {
            moveElement(index, i + 4, i + 2);
            newSwap(index, i + 4, i + 3);
        }
        else
        {
            moveElement(index, i + 4, i + 3);
            newSwap(index, i + 4, i + 2);
        }
    }

    if (vect[index[i + 4]] < vect[index[i + 1]])
    {
        if (vect[index[i + 4]] < vect[index[i]])
        {
            moveElement(index, i + 4, i);
        }
        else
        {
            moveElement(index, i + 4, i + 1);
        }
    }
    else
    {
        if (vect[index[i + 4]] < vect[index[i + 2]])
        {
            moveElement(index, i + 4, i + 2);
        }
        else
        {
            moveElement(index, i + 4, i + 3);
        }
    }

    return index[i + 2];
}


int median(vectInt& vect, vectInt& index)
{
   if (index.size() < 5)
   {
       return index[index.size()/2];
   }
   int end = index.size();
   int blocks = index.size()/5;
   vectInt vect2;
   for(int i=0; i<blocks; i++)
   {
    vect2.push_back(newSort(vect, index, i));
   } 
   return median(vect, vect2);
    
}


int pivPartition(int position, vectInt& vect, int start, int end)
{   
    cout <<"pivot: " << vect[position] <<endl;
    newSwap(vect, position, end);
    int newPivot = vect[end];
    int i = start - 1;

    for (int j = start; j <= end - 1; ++j) 
    {
        if (vect[j] < newPivot)
        {
            i++;
            newSwap(vect, i, j);
        }
        else if (vect[j] == newPivot)
        {
            // Spostare solo l'elemento uguale al pivot al centro
            newSwap(vect, i + 1, j);
        }
    }
    newSwap(vect, i + 1, end);
    return i + 1;
}



int quickSelect(vectInt& vect, vectInt& index, int p, int q, int i)
{
    if (p >= q)
        return index[p];

    int pivot = median(vect, index);
    int r = pivPartition (pivot, vect, p, q);
    int k = r - p + 1;

    if (i == k)
        return index[r];
    else if (i < k)
        {   
            return quickSelect(vect, index, p, r - 1, i);
        } 
    else
        {
            return quickSelect(vect, index, r + 1, q, i - k);
        }      
}

int main()
{
    
    int m = 10;
    vectInt vect, index;
    for(int i=0; i<m; i++)
    {
        vect.push_back(i+1);
        index.push_back(i);
    }
    vect.at(1)=8;
    vect.at(2)=8;
    vect.at(3)=8;
    shuffle(vect.begin(), vect.end(), default_random_engine(seed));



    //cout << "med: " << vect.at(4) << endl;
    //int x = pivPartition(4, vect, 0, N-1);

    cout <<endl;
    printVec(vect);
    int x = pivPartition(1, vect, 0, m-1);
    cout << "x: " << x <<endl;
    printVec(vect);



    //int k = quickSelect(vect, index, 0, N-1, 80 );
    //cout <<"k: " <<k <<endl;

}