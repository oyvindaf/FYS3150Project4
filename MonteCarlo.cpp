#include <iostream>
#include <fstream>
#include <ctime>
//#include <armadillo>
//#include <cstdlib>
#include <iomanip>
#include "lib.cpp"
#include <sstream>
#include <string>

using namespace std;
ofstream ofile;
// function for periodic boundary condition
inline int periodic(int pos, int size, int add) {
	return (pos + size + add) % (size);
}

// n x n matrix which represents the 2 dimensional lattice
int** initialize_lattice(int n)
{
  int lattice_value;
  int random_number;

  int** lattice2D = 0;
  lattice2D = new int*[n];

  for(int i = 0; i < n; i++)
  {
    lattice2D[i] = new int[n];
    for(int j = 0; j < n; j++)
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

int** ordered_initialize_lattice(int n)
{
  int lattice_value;
  int random_number;

  int** lattice2D = 0;
  lattice2D = new int*[n];

  for(int i = 0; i < n; i++)
  {
    lattice2D[i] = new int[n];
    for(int j = 0; j < n; j++)
    {
			lattice2D[i][j] = 1;
      }
  }
  return lattice2D;
}


int random_position(int n)
{
  int random_pos;
  random_pos = rand()%n;
  return random_pos;
}

void initialize(int size, double& M, double& E, int** myLattice) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			M += (int)myLattice[i][j];
		}
	}
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			E -= (double)myLattice[y][x] * (myLattice[periodic(y, size, -1)][x] + myLattice[y][periodic(x, size, -1)]);
		}
	}
}

void Metropolis(int size, long& idum, int **myLattice, double& E, double& M, double *w, int& accepted) {
	//looping over all spins
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			//finding random position
			int ix = random_position(size);
			int iy = random_position(size);
			int DeltaE = 2 * myLattice[iy][ix] *
			(myLattice[iy][periodic(ix, size, -1)] + myLattice[periodic(iy, size, -1)][ix] +
			myLattice[iy][periodic(ix, size, 1)] + myLattice[periodic(iy, size, 1)][ix]);
			if (ran1(&idum) <= w[DeltaE + 8]) {
				myLattice[iy][ix] *= -1;
				M += (double) 2 * myLattice[iy][ix];
				E += (double) DeltaE;
				accepted += 1;
			}
		}
	}
}

void Output(int size, int cycles, double temp, double* average) {
	double norm = 1 / ((double)(cycles));
	double E_avg = average[0] * norm;
	double E2_avg = average[1] * norm;
	double M_avg = average[2] * norm;
	double M2_avg = average[3] * norm;
	double Mabs_avg = average[4] * norm;

	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setprecision(8) << "T = " << temp;
	ofile << setw(8) << setprecision(8) << "|E| = " << E_avg/size/size;
	ofile << setw(8) << setprecision(8) << "|M| = " << M_avg/size/size;
}

void Loop_Output(int size, int cycles, double temp, double* average, int time_step, int accepted) {
	double norm = 1 / ((double)(cycles));
	double E_avg = average[0] * norm;
	double E2_avg = average[1] * norm;
	double M_avg = average[2] * norm;
	double M2_avg = average[3] * norm;
	double Mabs_avg = average[4] * norm;

	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setprecision(8) << time_step;
	ofile << setw(8) << setprecision(8) << " " << E_avg/size/size;
	ofile << setw(8) << setprecision(8) << " " << M_avg/size/size;
	ofile << setw(8) << setprecision(8) << " " << accepted << endl;
}


void read_input(int& n, int& montecarlo, double& temp, int& iterations, double& fin_temp) {
	cout << "number of lattices: ";
	cin >> n;
	cout << "number of montecarlo cycles: ";
	cin >> montecarlo;
	cout << "initial temperature: ";
	cin >> temp;
	cout << "final temperature: ";
	cin >> fin_temp;
	cout << "temperature iterations: "
	cin >> iterations;
}


int main(int argc, char* argv[]){
  srand(time(NULL)); // set random seed by using current time
  char* outfilename;
  int **myLattice, n, montecarlo, accepted;
  long idum;
  double w[17], average[5], E, M, init_temp, final_temp, temp_step;

  if (argc <= 1) {
	  cout << "Bad Usage: " << argv[0] << " read also output file on same line" << endl;
	  exit(1);
  }
  else {
	  outfilename = argv[1];
  }

  ofile.open(outfilename);

  read_input(n, montecarlo, init_temp);

  myLattice = initialize_lattice(n);

  E = 0; M = 0; accepted = 0;
  idum = -1;
  // setting up array for possible energy changes
  for (int de = -8; de <= 8; de++) w[de+8] = 0;
  for (int de = -8; de <= 8; de += 4) w[de+8] = exp(-de / init_temp);
  // initializing array for expectation values
  for (int i = 0; i < 5; i++) average[i] = 0;

  //  initializing magnetization and energy;
  initialize(n, M, E, myLattice);

  // starting the montecarlo cycle
  for (int cycle = 1; cycle <= montecarlo; cycle++) {
	  Metropolis(n, idum, myLattice, E, M, w, accepted);
	  average[0] += E; average[1] += E*E;
	  average[2] += M; average[3] += M*M; average[4] += fabs(M);
		Loop_Output(n, montecarlo, init_temp, average, cycle, accepted);
  }
  //Generating output data
	int time_step=10;

  ofile.close();

  return 0;
}
