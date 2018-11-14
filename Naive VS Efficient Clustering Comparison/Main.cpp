#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>	
#include <time.h>		//for calculating run-time
#include <vector>
#include <cctype>		//for yes/no question


using namespace std;

//FUNCTION PROTOTYPES
vector< vector<pair<int, int>> > read_el(char *filename); //Read in edge list and convert to adjacency list
void print_el(vector< vector<pair<int, int>> > links); //Print adjacency and/or edge list

//Each method will be fed the same starting network and other paramters
//Naive likelihood 
int lik_naive(
	char *filename,
	vector< vector<pair<int, int>> > links,
	int nb_links,
	int N,
	int min_k,
	int max_k,
	int k_int,
	double InitTemp,
	double CR,
	double TL,
	int Max_Success,
	double LimitIT,
	double epsilon,
	int TL_counter,
	int Success_counter,
	double IT
	);
//Iterative/efficient likelihood
int lik_efficient(
	char *filename,
	vector< vector<pair<int, int>> > links,
	int nb_links,
	int N,
	int min_k,
	int max_k,
	int k_int,
	double InitTemp,
	double CR,
	double TL,
	int Max_Success,
	double LimitIT,
	double epsilon,
	int TL_counter,
	int Success_counter,
	double IT
	);
 //Modularity
 int modularity(
	char *filename,
	vector< vector<pair<int, int>> > links,
	int nb_links,
	int N,
	int min_k,
	int max_k,
	int k_int,
	double InitTemp,
	double CR,
	double TL,
	int Max_Success,
	double LimitIT,
	double epsilon,
	int TL_counter,
	int Success_counter,
	double IT
);

int louvain_convert_2b(vector<vector<pair<int, int/*long double*/> > > source_links, int nb_links, char *filename);
int louvain_clustering(char *filename);

int main()
{

	//Get file name
	char filename[256];
	cout << "Enter file name, including suffix (ex. myfile.txt): ";
	cin.getline(filename, 256);

	//Make sure file exists. otherwise, get file name again.
	int file_exists = 0;
	ifstream ifile(filename);
	file_exists = (bool)ifile;
	while (file_exists == 0)
	{
		cout << "Enter file name, including suffix (ex. myfile.txt): ";
		cin.getline(filename, 256);
		ifstream ifile(filename);
		file_exists = (bool)ifile;
	}


	cout << "Reading in edge list..." << endl;
	//Input network edge list and convert to adjacency list that includes weight information
	time_t read_start = time(0);//Time until solution
	vector< vector<pair<int, int>> > links;
	links = read_el(filename);

	//Check to see that every vertex in the network has at least 1 edge to another vertex. No singletons allowed.
	int missing = 0;
	for (int i = 0; i < links.size(); i++)
	{
		if (links[i].size() == 0){ missing = 1; }
		//links[i].size()
	}
	if (missing == 1){ 
		cout << "WARNING WARNING WARNING" << endl;
		cout << "*** ADJACENCY LIST IS NOT FULLY POPULATED ***" << endl;
		cout << "THE PROGRAM WILL NOT WORK CORRECTLY" << endl;
		cin.get();
	}

	//Get the number of distinct vertices in the network
	int N = links.size();

	cout << "Vertex count: " << links.size() << endl;
	time_t read_end = time(0);
	double read_time = difftime(read_end, read_start);
	cout << read_time / 60 << " minutes required to read edge list" << endl;

	//Get the number of DISTINCT edges in the network
	int nb_links = 0;
	for (int i = 0; i < links.size(); i++){
		for (int j = 0; j < links[i].size(); j++)	{
			nb_links = nb_links + 1;
		}
	}
	//This counts the link between i and j, and between j and i. In the undirected network case using an adjacency list, this double counts edges, so:
	nb_links = nb_links / 2;

	//Print network as edge list and adjacency list. Can be commented out when running the real program.
	//print_el(links); //print network as adjacency list, including weights. Can also print out as edge list, but currently commented out

	//Get the number of clusters in which to cluster the network
	int min_k;
	int max_k;
	int k_int;
	cout << "Enter the lower bound for number of clusters: "; 	cin >> min_k;
	cout << "Enter the upper bound for number of clusters: ";	cin >> max_k;
	cout << "Enter the number of clusters increment interval: ";	cin >> k_int;
	//say, cluster from  k=10 to k=100 by increments of 10 (10,20,30...,90,100)
			
	//Simulated Annealing Algorithm Parameters
	double InitTemp = 1;//.0025;//1
	double CR = .9925;// 0.9925;//.99
	int TL = 150;// 15000;	//300		//Maximum number of reclustering attempts at a given temperature
	int Max_Success = TL;//100	//Maximum number of successes allowed at a given temperature
							//Note: Setting both these values=1 is the equivalent of not using them at all in the SA algorithm.
	double LimitIT = 1.0e-8;
	double epsilon = 1.0e-6;
	int TL_counter = 0;
	int Success_counter = 0;

	double IT = InitTemp; //IT changes during Simulated Annealing process. InitTemp is used to initialize (or re-initialize) IT at the start of the process when multiple k values are analyzed
	
//	int seed = 0;	
	srand(time(0));
	//		random_device rd;
	//		mt19937 e2(rd());
	//		uniform_real_distribution<double> dist_uni(0.0, 1.0);
/*
	cout << "#############################################################" << endl;
	modularity(
		filename,
		links,
		nb_links,
		N,
		min_k,
		max_k,
		k_int,
		InitTemp,
		CR,
		TL,
		Max_Success,
		LimitIT,
		epsilon,
		TL_counter,
		Success_counter,
		IT
	);


cout << "#############################################################" << endl;
	lik_naive(
		filename,
		links,
		nb_links,
		N,
		min_k,
		max_k,
		k_int,
		InitTemp,
		CR,
		TL,
		Max_Success,
		LimitIT,
		epsilon,
		TL_counter,
		Success_counter,
		IT
	);
	
cout << "#############################################################" << endl;
	lik_efficient(
		filename,
		links,
		nb_links,
		N,
		min_k,
		max_k,
		k_int,
		InitTemp,
		CR,
		TL,
		Max_Success,
		LimitIT,
		epsilon,
		TL_counter,
		Success_counter,
		IT
		);
	
	cout << "#############################################################" << endl;
*/

louvain_convert_2b(links, nb_links, filename);
char binary_file[256] = "louvain_binary.txt";
louvain_clustering(binary_file);

	cout << "Program ended. Hit enter to exit.";
	cin.get(); cin.get();

}//END main()





/*
Example R code to create a graph in igraph,
get the edge list (that is not symmetric)
renumber the vertices (because they start at 1, but we need them to start at 0)
make symmetric
output to text file.


g <- make_graph("Zachary")
t1<-as.data.frame(as_edgelist(g))
t1<-t1-1 #resize so that vertex numbers start at zero
t2<-t1[,c(2,1)] #reverse column order
colnames(t2) <- c("V1","V2") #rename columns
t3<-rbind(t1, t2) #vertically stack columns
el<-t3[with(t3, order(V1, V2)), ] #order for clarity
write.table(el,"C:/Users/talktoalan/Documents/Visual Studio 2013/Projects/Efficient Undirected Network Clustering/Debug/karate_club.txt",sep="\t",col.names=FALSE,row.names=FALSE)


//http://www.alglib.net/specialfunctions/distributions/chisquare.php
//Download C++ .zip file, unpack and point to "src" folder here.
//#include <C:\Users\talktoalan\Documents\Visual Studio 2013\Projects\Efficient Undirected Network Clustering\Efficient Undirected Network Clustering\src\specialfunctions.h>

//Add all CPP files in SRC to project, and compile

//cout << fixed;
//setprecision(50);
//double G = 4838341969836854217585.0 - 1.0; //S(n,k)-1=S(34,5)-1
//double alpha = .95;
//long double v = pow(1-.05,1/G);
//cout << v << endl;
//invchisquaredistribution(const double v, const double y)
//cout << alglib::invchisquaredistribution(v, alpha) << endl;
//cout << alglib::invchisquaredistribution(2*v, alpha) << endl;
//cout << alglib::invchisquaredistribution(v, 1 - alpha) << endl;
//cout << alglib::invchisquaredistribution(2*v, 1-alpha) << endl;
//cin.get(); cin.get();
//C(34,5) at alpha=.05=117.5 n=34, k=5


//Test for acceptance
////from old method
////double dE = Ca - Cb;
////if (Cb - Ca > 1.0e-6){accept}
////where
////Ca=-teststat(proposed)= -(-2 * (LO - loglikelihood)) for proposed solution
////Cb=-teststat(current) = -(-2 * (LO - loglikelihood)) for current solution
//
////Then, in new method, accept if
////dE
////=Cb - Ca (where Cb=-prosed test stat and Ca=-current test stat
////=[-(-2 * (LO - loglikelihood_prop))] - [-(-2 * (LO - loglikelihood_curr))]
////=[2 * (LO - loglikelihood_prop)] - [2 * (LO - loglikelihood_curr)]
////=2*LO - 2*loglikelihood_prop - 2*LO + 2*loglikelihood_curr
////=2*(loglikelihood_curr - loglikelihood_prop)
////=-2*(loglikelihood_prop - loglikelihood_curr)
////=-2*[log(proposed/current)]
////=-2*[delta l from current paper] > 1.0e-6
//
////and get same decision from
////-[delta l from current paper] > 1.0e-6
////=-(loglikelihood_prop - loglikelihood_curr) > 1.0e-6
////=-(loglikelihood_curr - loglikelihood_prop) > 1.0e-6
////or [log(current/proposed)]< 1.0e-6
*/