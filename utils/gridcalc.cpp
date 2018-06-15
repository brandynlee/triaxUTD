#include <iostream>
#include <fstream>
#include <triaxNFW.h>

using namespace std;

Scalar minX = -5.0;
Scalar maxX = 5.0;
Scalar minY = -5.0;
Scalar maxY = 5.0;
int grid_res_x = 100;
int grid_res_y = 100;
Scalar zs = 1.0;
Scalar Ds = 1671.15679834;
Scalar zl = 0.25;
Scalar Dl = 806.1;
Scalar rhoC = 173130690600.0;

Vector2Array1D grid_points(nullptr);
ScalarArray1D sigmaCs(nullptr);
ScalarArray1D kappas(nullptr);
ScalarArray1D gamma1s(nullptr);
ScalarArray1D gamma2s(nullptr);

void generate_grid(Scalar sigmaC)
{
	int idx = 0;
	for(int y=0;y<grid_res_y;y++) {
		Scalar ycoord = y*(maxY-minY)/(grid_res_y-1) + minY;
		for(int x=0;x<grid_res_x;x++) {
			Scalar xcoord = x*(maxX-minX)/(grid_res_x-1) + minX;
			grid_points->v[idx].x = xcoord;
			grid_points->v[idx].y = ycoord;
			sigmaCs->v[idx] = sigmaC;
			idx++;
		}
	}
}

int main(int argc,char *argv[])
{
	if(argc<2) {
		cerr << "Usage: " << argv[0] << " [output file]" << endl;
		return -1;
	}
	// Allocate all the arrays
	grid_points.reset(new Vector2Array1Dobj(grid_res_y*grid_res_x));
	sigmaCs.reset(new ScalarArray1Dobj(grid_res_y*grid_res_x));
	kappas.reset(new ScalarArray1Dobj(grid_res_y*grid_res_x));
	gamma1s.reset(new ScalarArray1Dobj(grid_res_y*grid_res_x));
	gamma2s.reset(new ScalarArray1Dobj(grid_res_y*grid_res_x));

	triaxNFW nfw;
	nfw.setParameters(4, 2, NAN, 0.6, 0.9, 1.0, M_PI/4.0, zl, Dl, rhoC);
	generate_grid(nfw.calcSigmaC(zs, Ds));
	cout << "Calculating convergence and shear on " << (grid_res_y*grid_res_x) << " grid points..." << endl;
	nfw.calcConvergenceShear(grid_points, sigmaCs, kappas, gamma1s, gamma2s);
	cout << "Calculations completed." << endl;

	ofstream outfile(argv[1], ios::out|ios::trunc);
	if(outfile.fail()) {
		cerr << "Could not open file \"" << argv[1] << "\" for writing!" << endl;
		return -2;
	}

	cout << "Writing results to output file \"" << argv[1] << "\"..." << endl;
	for(int idx=0;idx<grid_res_y*grid_res_x;idx++) {
		outfile << grid_points->v[idx].x << " "
			<< grid_points->v[idx].y << " "
			<< kappas->v[idx] << " "
			<< gamma1s->v[idx] << " "
			<< gamma2s->v[idx] << endl;
	}

	outfile.close();

	cout << "Done." << endl;

	return 0;
}

