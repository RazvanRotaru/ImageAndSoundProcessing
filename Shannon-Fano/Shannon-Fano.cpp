#include "utils/DataContainer.h"
#include "shannon_fano_h/ShannonFanoSolver.h"

using namespace std;

int main(int argc, char* argv[])
{
	DataContainer* d = new DataContainer(argv[1]);
	ShannonFanoSolver* sfs = new ShannonFanoSolver(!argv[2] ? "" : argv[2]);
	d->accept(sfs);
	
	delete d;
	delete sfs;
	
	return 0;
}