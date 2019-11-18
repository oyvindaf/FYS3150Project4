#include "mpi.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "lib.cpp"
#include <sstream>
#include <string>
#include <random>
#include <ctime>

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

void Metropolis(int size, int montecarlo, int **myLattice, double *w, double T, int loop, int loop_start, int loop_end, int my_rank) {
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
 double tot_average[5];
 for (int i = 0; i < 5; i++) average[i] = 0;
 for (int i = 0; i < 5; i++) tot_average[i] = 0;
 initialize(size, M, E, myLattice);

 for(int cycles = loop_start; cycles <= loop_end; cycles++){
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

 for (int i = 0; i < 5; i++) {
	 MPI_Reduce(&average[i], &tot_average[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
 }

 if ((loop == 0) && (my_rank == 0)) {
	Output_done(size, montecarlo, T, tot_average);
 }
}

void Output_done(int size, int cycles, double temp, double* average) {
	double norm = 1 / ((double)(cycles))/size/size;
	double E_avg = average[0] * norm;
	double E2_avg = average[1] * norm;
	double M_avg = average[2] * norm;
	double M2_avg = average[3] * norm;
	double Mabs_avg = average[4] * norm;

	double E_var = (E2_avg - E_avg * E_avg);
	double M_var = (M2_avg - Mabs_avg * Mabs_avg);

	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setprecision(8) << temp;
	ofile << setw(8) << setprecision(8) << " " << E_avg;
	ofile << setw(8) << setprecision(8) << " " << E_var/(temp*temp);
	//ofile << setw(8) << setprecision(8) << " " << M_avg;
	ofile << setw(8) << setprecision(8) << " " << Mabs_avg;
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

void Loop_Metropolis(double init_temp, double final_temp, double dT, int size, int montecarlo, int **myLattice, double *w, int loop, int loop_start, int loop_end, int my_rank){
	for (double temp = init_temp; temp <= final_temp; temp+=dT){
		for (int de = -8; de <= 8; de++) w[de + 8] = 0;
		for (int de = -8; de <= 8; de += 4) w[de + 8] = exp(-de / temp);

		Metropolis(size, montecarlo, myLattice, w, temp, loop, loop_start, loop_end, my_rank);
	}
}

int main(int argc, char* argv[]){

	clock_t start;
	double duration;


  srand(time(NULL)); // set random seed by using current time
  char* outfilename;
  int **myLattice, n, montecarlo, accepted, loop, my_rank, numprocs;
  long idum;
  double w[17], average[5], tot_average[5], E, M, init_temp, final_temp, temp_step;
  string initial_state;
  string ordered;
  string disordered;

  //read_input(n, montecarlo, init_temp, final_temp, temp_step, initial_state, loop);

	start = clock();

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0 && argc <= 1) {
	  cout << "Bad Usage: " << argv[0] << " read also output file on same line" << endl;
	  exit(1);
  }
  if (my_rank == 0 && argc > 1) {
	  outfilename = argv[1];
	  ofile.open(outfilename);
  }

	n = 100;
	montecarlo = 100000;
	init_temp = 2.1;
	final_temp = 2.4;
	temp_step = 0.005;
	initial_state = disordered;
	loop = 0;

  int intervals_proc = montecarlo / numprocs;
  int loop_start = my_rank * intervals_proc + 1;
  int loop_end = (my_rank + 1) * intervals_proc;
  if ((my_rank == numprocs - 1) && (loop_end < montecarlo)) loop_end = montecarlo;

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&init_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&final_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (initial_state == ordered){
		myLattice = ordered_initialize_lattice(n);
	} else{
		myLattice = initialize_lattice(n);
	}


  E = 0;
  M = 0;
  accepted = 0;
  idum = -1-my_rank;
  // setting up array for possible energy changes
  for (int de = -8; de <= 8; de++) w[de+8] = 0;
  for (int de = -8; de <= 8; de += 4) w[de+8] = exp(-de / init_temp);

  if (loop == 1) {
	  Metropolis(n, montecarlo, myLattice, w, init_temp, loop, loop_start, loop_end, my_rank);
  }
  else {
	  Loop_Metropolis(init_temp, final_temp, temp_step, n, montecarlo, myLattice, w, loop, loop_start, loop_end, my_rank);
  }

  ofile.close();

	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	cout << "runtime:" << duration << '\n';

  return 0;
}
