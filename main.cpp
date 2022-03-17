/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * GPX2: Generalized Partition Crossover 2
* Reference:  R. Tinos, D. Whitley, and G. Ochoa (2017). A new generalized partition crossover for 	*
*		the traveling salesman problem: tunneling between local optima. arXiv.org					*
 *  Contact: Renato Tinos <rtinos@ffclrp.usp.br>
 *
 * gpx2 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gpx2 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "defs.h"
#include <cstdlib>
#include <cmath>

/******************************************************************************\
*				  	random initialization of the parents						 *
\******************************************************************************/
void rand_init(int *p1, int *p2){
	int *v_in, gene;

	v_in=aloc_vectori(n_cities);

	for (gene=0;gene<n_cities;gene++) {
		v_in[gene]=gene;
	}

	srand (time(NULL));
	rand_perm(v_in, p1, n_cities);		// random permutation of v_in
	rand_perm(v_in, p2, n_cities);		// random permutation of v_in

	delete [] v_in;
}


/******************************************************************************\
*				  	Main													 *
\******************************************************************************/
int main(int argc , char *argv[])
{
	int *p1, *p2;
	double off_1_fitness, off_2_fitness;

	// Arguments
	if( argc < 2) {
		cout<<"Insufficient number of arguments!"<<endl;
		exit(1);
	}
	else{
		prob_name=argv[1];
	}

	// TSP
	read_problem(prob_name);


	cout << "\n ***** Example: recombination of 2 random individuals ****" << endl;

	p1=aloc_vectori(n_cities);
	p2=aloc_vectori(n_cities);
	rand_init(p1, p2);		// random initialization of the parents

	// Recombination by GPX2
	gpx(&p1, &p2, &off_1_fitness, &off_2_fitness);
	cout << "Offspring 1 cost, Offspring 2 cost" << endl;
	cout << (long long) off_1_fitness << ", " << (long long) off_2_fitness << endl;

	if (n_cities<=max_dm_size)
		desaloc_matrixi (W,n_cities);
	delete [] coord_x;
	delete [] coord_y;
	delete [] p1;
	delete [] p2;

	return 0;
}
