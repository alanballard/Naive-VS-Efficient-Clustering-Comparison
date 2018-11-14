// File: main_convert.cpp
// -- conversion of a graph from ascii to binary, sample main file
//-----------------------------------------------------------------------------
// Community detection 
// Based on the article "Fast unfolding of community hierarchies in large networks"
// Copyright (C) 2008 V. Blondel, J.-L. Guillaume, R. Lambiotte, E. Lefebvre
//
// And based on the article "A Generalized and Adaptive Method for Community Detection"
// Copyright (C) 2014 R. Campigotto, P. Conde Céspedes, J.-L. Guillaume
//
// This file is part of Louvain algorithm.
// 
// Louvain algorithm is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Louvain algorithm is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with Louvain algorithm.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------
// Author   : E. Lefebvre, adapted by J.-L. Guillaume and R. Campigotto
// Email    : jean-loup.guillaume@lip6.fr
// Location : Paris, France
// Time	    : July 2014
//-----------------------------------------------------------------------------
// see README.txt for more details


#include "graph_2b.h"

using namespace std;

/*
char *infile = NULL;
char *outfile = NULL;
char *outfile_w = NULL;
char *rel = NULL;
int type = UNWEIGHTED;
bool do_renumber = false;
*/
/*
void
usage(char *prog_name, const char *more) {
  cerr << more;
  cerr << "usage: " << prog_name << " -i input_file -o outfile [-r outfile_relation] [-w outfile_weight] [-h]" << endl << endl;
  cerr << "read the graph and convert it to binary format" << endl;
  cerr << "-r file\tnodes are renumbered from 0 to nb_nodes-1 (the labelings connection is stored in a separate file)" << endl;
  cerr << "-w file\tread the graph as a weighted one and writes the weights in a separate file" << endl;
  cerr << "-h\tshow this usage message" << endl;
  exit(0);
}

void
parse_args(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      switch(argv[i][1]) {
      case 'i':
	if (i==argc-1)
	  usage(argv[0], "Infile missing\n");
	infile = argv[i+1];
	i++;
	break;
      case 'o':
	if (i==argc-1)
	  usage(argv[0], "Outfile missing\n");
        outfile = argv[i+1];
	i++;
	break;
      case 'w':
	type = WEIGHTED;
        outfile_w = argv[i+1];
	i++;
	break;
      case 'r':
	if (i==argc-1)
	  usage(argv[0], "Labelings connection outfile missing\n");
        rel = argv[i+1];
	i++;
	do_renumber=true;
	break;
      default:
	usage(argv[0], "Unknown option\n");
      }
    } else {
      usage(argv[0], "More than one filename\n");
    }
  }
  if (infile==NULL || outfile==NULL)
    usage(argv[0], "In or outfile missing\n");
}
*/

//int main(int argc, char **argv) {
int louvain_convert_2b(vector<vector<pair<int, int/*long double*/> > > source_links, int link_count, char *filename) {
  //parse_args(argc, argv);

	//char infile[256];
	//cout << "Enter file name, including suffix (ex. myfile.txt): ";
	//cin.getline(infile, 256);

	char outfile[256];
	//cout << "Enter OUTPUT file name, including suffix (ex. myfile.txt): ";
	//cin.getline(outfile, 256);

	ostringstream atkstring2;
	// If old file exists from a previous run, delete it.
	remove("louvain_binary.txt");
	atkstring2 << "louvain_binary" << ".txt";
	
	string s = atkstring2.str();	
	//char cstr[s.size() + 1];
	strcpy_s(outfile, s.c_str());	

	//char *infile = NULL;
	//char *infile = "network1000.txt";
	//char *outfile = "out yo yo.txt";
	char *outfile_w = NULL;
	char *rel = NULL;
	int type = UNWEIGHTED;
	bool do_renumber = false;

  Graph_b g_b(source_links, link_count, filename, type);

  g_b.clean_b(type);

  if (do_renumber)
	  g_b.renumber_b(type, rel);

  g_b.display_binary_b(outfile, outfile_w, type);

  return 0;
}
