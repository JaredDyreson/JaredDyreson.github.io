#include <iostream>
using namespace std;

int find(int array[], int size, int val);

int main()
{
  // initialize array
  // test find function
  int arrValues[] = {10, 25, 87, 6};
  cout << find(arrValues, 4, 87) << endl;
  cout << find(arrValues, 4, 4);
  return 0;
}

int find(int array[], int size, int val)
{
  int position = -1; // position of value in the array
  // loop through array
  for(int i = 0; position==-1 && i < size; i++)
    if(array[i] == val)
      position = i;
  // check if val is in particular array element
  // return position
  return position;
}
