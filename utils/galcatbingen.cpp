#include <iostream>
#include <fstream>
#include <cmath>
#include "../src/mcmc.h" // for CatalogEntry

using namespace std;

int main(int argc, char* argv[])
{
	double zs, Ds;
	zs = NAN;
	Ds = NAN;
	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " [catalog file (text)] [output binary catalog file (bin)] [zs (optional)] [Ds (optional)]" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	if (infile.fail()) {
		cerr << "Could not open file " << argv[1] << endl;
		return -2;
	}

	ofstream outfile(argv[2], ofstream::trunc | ofstream::binary);
	if (outfile.fail()) {
		cerr << "Could not write file " << argv[2] << endl;
		return -3;
	}

	if (argc >= 3) {
		sscanf(argv[3], "%lf", &zs);
	}
	if (argc >= 4) {
		sscanf(argv[4], "%lf", &Ds);
	}

	string line;
	CatalogEntry entry;
	while (!infile.eof()) {
		getline(infile, line);
		sscanf(line.c_str(), "%lf %lf %lf %lf %lf %lf", &entry.x, &entry.y, &entry.eps1, &entry.eps2, &entry.zs, &entry.Ds);
		if(!isnan(zs)) entry.zs=zs;
		if(!isnan(Ds)) entry.Ds=Ds;
		outfile.write((const char*)&entry, sizeof(CatalogEntry));
	}

	infile.close();
	outfile.close();

	cout << "Binary catalog file written to " << argv[2] << endl;
	return 0;
}
