#include <iostream>
#include <ctime>
//#include <armadillo>
#include <cstdlib>
using namespace std;


// n x n matrix which represents the 2 dimensional lattice
int** initialize_lattice(int n)
{
  int lattice_value;
  int random_number;

  int** lattice2D = 0;
  lattice2D = new int*[n];

  for(int i = 0; i <= n; i++)
  {
    lattice2D[i] = new int[n];
    for(int j = 0; j <= n; j++)
    {
      random_number = (rand()%10);
      if ( random_number < 5){
        lattice_value = -1;
      } else {
        lattice_value = 1;
      }
      lattice2D[i][j] = lattice_value;
      }
  }
  return lattice2D;
}

int random_position(int n)
{
  int random_pos;
// picks out random x and y position in the lattice
  random_pos = rand()%n;
  return random_pos;
}

bool corner(n,m,size)
{
  bool variable;
  if ((m = 0 && n = 0) || (m = size && n = 0 ) || (m = 0 && n = size ) || (m = size && n = size){
    variable = true;
  } else{
    variable = false;
  }
  return variable;
}

//boolean edge(n,m,size)
//{
//  bool variable;

//}


int main(){
  srand(time(NULL)); // set random seed by using current time
  int z;
  int n = 4;
  int** myLattice;

  myLattice = initialize_lattice(n);
  printf("Array contents: \n ");

  for(int h = 0; h < n; h++){
    for(int k = 0; k < n; k++){
      printf("%i,",myLattice[h][k]);
    }
    printf("\n");
  }
  int x,y;
  x = random_position(n);
  y = random_position(n);
  printf("random positions: \n ");
  printf("x-position: %i,",x);
  printf("\n y-position: %i",y);



  return 0;
}
