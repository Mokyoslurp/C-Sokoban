/**
 * @file test-solver.c
 *
 * @brief Test executable to verify the solver is working.
 *
 * @author M.Giordani
 *
 */

#define WITH_LIST false
#define WITH_GUI false

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "loader.h"
#include "sokoban.h"
#include "solver.h"

int main()
{
	printf("Solver tests launched ...\n");

	// soko_dumber
	print_solve("./data/soko_dumber.in", WITH_LIST, WITH_GUI);
	// soko_dumb
	print_solve("./data/soko_dumb.in", WITH_LIST, WITH_GUI);
	// soko_dumb_imp
	print_solve("./data/soko_dumb_imp.in", WITH_LIST, WITH_GUI);
	// soko81
	print_solve("./data/soko81.in", WITH_LIST, WITH_GUI);
	// soko99
	print_solve("./data/soko99.in", WITH_LIST, WITH_GUI);
	// soko1
	print_solve("./data/soko1.in", WITH_LIST, WITH_GUI);

	printf("Solver test succeeded !\n\n");

	// Computation results comparison (using OPT=1):

	// file			program		win			length		n°exp. node		time (list)		time (bst)

	// soko_dumber	Garion		y			2				5			0.000005		0.000005
	//				Giordani	y			2				5			0.000015		0.000007

	// soko_dumb	Garion		y			7				111			0.000086		0.000062
	//				Giordani	y			7				73			0.000126		0.000149

	// soko_dumb_impGarion		n							1805		0.014606		0.001895
	//				Giordani	n							1484		0.030639		0.003975

	// soko81		Garion		y			31				31906		4.647807		0.043387
	//				Giordani	y			31				8969		1.405643		0.027129

	// soko99		Garion		y			36				147508		218.615019		0.291131
	//				Giordani	y			36				25027		11.001479		0.098840

	// soko1		Garion		y			184				193895		318.875331		0.632850
	//				Giordani	y			184				55460		83.315191		0.235483

	return 0;
}
