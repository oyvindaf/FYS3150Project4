#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "lib.cpp"
#include <sstream>
#include <string>
#include <random>

using namespace std;
ofstream ofile;
void initialize(int size, double& M, double& E, int** myLattice);
void Loop_Output(int size, int cycles, double temp, double* average, int time_step, double accepted);
void Output_done(int size, int cycles, double temp, double* average);

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
			lattice2D[i][j] = -1;
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

void Metropolis(int size, int montecarlo, int **myLattice, double *w, double T, int loop) {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);
	uniform_int_distribution<int> RandomPosition(0, size-1);
	//looping over all spins

 double accepted = 0;
 double E = 0;
 double M = 0;
 double absM = 0;
 double average[5];
 for (int i = 0; i < 5; i++) average[i] = 0;
 initialize(size, M, E, myLattice);
 for(int cycles = 1; cycles <= montecarlo; cycles++){
	if (cycles == 0){
		cout << "E: " << E << endl;
		cout << "<E>: " << average[0] << endl;
		cout << "abs M: " << sqrt(M*M) << endl;
		cout << "Cycle: " << cycles <<endl;
	}
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			//finding random position
			int ix =(int) RandomPosition(gen);
			int iy = (int)RandomPosition(gen);
			int DeltaE = 2 * myLattice[iy][ix] *
			(myLattice[iy][periodic(ix, size, -1)] + myLattice[periodic(iy, size, -1)][ix] +
			myLattice[iy][periodic(ix, size, 1)] + myLattice[periodic(iy, size, 1)][ix]);
			double R = RandomNumberGenerator(gen);

			if (R <= w[DeltaE + 8]) {
				myLattice[iy][ix] *= -1;
				M += (double) 2 * myLattice[iy][ix];
				E += (double) DeltaE;
				accepted += 1;
			}


		}
	}
	absM = sqrt(M * M);
	average[0] += E;
	average[1] += E * E;
	average[2] += M;
	average[3] += M * M; //M2;
	average[4] += fabs(M);
	if (loop == 1) {
		Loop_Output(size, montecarlo, T, average, cycles, accepted / size / size / (double)(cycles));
	}
 }
 if (loop == 0) {
	Output_done(size, montecarlo, T, average);
 }
}

void Output_done(int size, int cycles, double temp, double* average) {
	double norm = 1 / ((double) cycles);
	double E_avg = average[0] * norm;
	double E2_avg = average[1] * norm;
	double M_avg = average[2] * norm;
	double M2_avg = average[3] * norm;
	double Mabs_avg = average[4] * norm;

	double E_var = (E2_avg - E_avg * E_avg)/size/size;
	double M_var = (M2_avg - Mabs_avg * Mabs_avg)/size/size;

	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setprecision(8) << temp;
	ofile << setw(8) << setprecision(8) << " " << E_avg/size/size;
	ofile << setw(8) << setprecision(8) << " " << E_var/(temp*temp);
	//ofile << setw(8) << setprecision(8) << " " << M_avg;
	ofile << setw(8) << setprecision(8) << " " << Mabs_avg/size/size;
	ofile << setw(8) << setprecision(8) << " " << M_var/temp << endl;
}

void Loop_Output(int size, int cycles, double temp, double* average, int time_step, double accepted) {
	double norm = 1 / ((double)(time_step*size*size));
	double E_avg = average[0] * norm;
	double E2_avg = average[1] * norm;
	double M_avg = average[2] * norm;
	double M2_avg = average[3] * norm;
	double Mabs_avg = average[4] * norm;

	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setprecision(8) << time_step;
	ofile << setw(8) << setprecision(8) << " " << E_avg;
	ofile << setw(8) << setprecision(8) << " " << Mabs_avg;
	ofile << setw(8) << setprecision(8) << " " << accepted << endl;
}

void Loop_Metropolis(double init_temp, double final_temp, double dT, int size, int montecarlo, int **myLattice, double *w, int loop){
	for (double temp = init_temp; temp <= final_temp; temp+=dT){
		for (int de = -8; de <= 8; de++) w[de + 8] = 0;
		for (int de = -8; de <= 8; de += 4) w[de + 8] = exp(-de / temp);

		Metropolis(size, montecarlo, myLattice, w, temp, loop);
	}
}

void read_input(int& n, int& montecarlo, double& temp1, double& temp2, double& dT, int& initial_state, int& loop) {
	cout << "number of lattices: ";
	cin >> n;
	cout << "number of montecarlo cycles: ";
	cin >> montecarlo;
	cout << "initial temperature: ";
	cin >> temp1;
	cout << "final temperature: ";
	cin >> temp2;
	cout << "temperature step size: ";
	cin >> dT;
	cout << "ordered or disordered, 1 is ordered 0 is disordered: ";
	cin >> initial_state;
	cout << "looped output or final output, 1 is looped, 0 is final: ";
	cin >> loop;
}


int main(int argc, char* argv[]){
  srand(time(NULL)); // set random seed by using current time
  char* outfilename;
  int **myLattice, n, montecarlo, accepted, loop;
  long idum;
  double w[17], average[5], E, M, init_temp, final_temp, temp_step;
  int initial_state;
  int ordered;
  int disordered;

  if (argc <= 1) {
	  cout << "Bad Usage: " << argv[0] << " read also output file on same line" << endl;
	  exit(1);
  }
  else {
	  outfilename = argv[1];
  }

  ofile.open(outfilename);

  read_input(n, montecarlo, init_temp, final_temp, temp_step, initial_state, loop);

	// if (initial_state = 1){
	// 	myLattice = ordered_initialize_lattice(n);
	// } else{
	// 	myLattice = initialize_lattice(n);
	// }
	myLattice = ordered_initialize_lattice(n);


  E = 0;
  M = 0;
  accepted = 0;
  idum = -1;
  // setting up array for possible energy changes
  for (int de = -8; de <= 8; de++) w[de+8] = 0;
  for (int de = -8; de <= 8; de += 4) w[de+8] = exp(-de / init_temp);

  if (loop == 1) {
	  Metropolis(n, montecarlo, myLattice, w, init_temp, loop);
  }
  else {
	  Loop_Metropolis(init_temp, final_temp, temp_step, n, montecarlo, myLattice, w, loop);
  }

  ofile.close();

  return 0;
}
