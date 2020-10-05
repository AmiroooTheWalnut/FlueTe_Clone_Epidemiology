/* main program for flute
 *
 * Dennis Chao
 * 12.2008
 */

//#define PARALLEL

#ifdef PARALLEL

#include <mpi.h>
#include "epimodel.h"
#include "epimodelparameters.h"

using namespace std;
int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  char *configname=NULL;
  if (argc==2)
    configname = argv[1];
  else {
    if (!rank)
      cerr << "Usage: " << argv[0] << " configfilename" << endl;
    MPI_Finalize();
    exit(-1);
  }
  EpiModelParameters parms(rank, size, configname);
  EpiModel model(rank, size, parms);
  model.run();
  MPI_Finalize();
  return 0;
}
#else // single processor mode
#include "epimodel.h"
#include "epimodelparameters.h"
#include <chrono> 

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
  char *configname=NULL;
  if (argc==2)
    configname = argv[1];
  else {
    cerr << "Usage: " << argv[0] << " configfilename" << endl;
    exit(-1);
  }
  EpiModelParameters parms(configname);
  EpiModel model(parms);
  model.run();
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  cout << "time::" << elapsed.count();
  return 0;
}
#endif
