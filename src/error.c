#include "cub3d.h"

int	errmessage(int a, char *s)
{
	if (a == 1)
		printmess(2, "Error\nWrong number of objects");
	if (a == 2)
	{
		printmess(2, "There are two existing paths for ");
		printmess(2, s);
	}
	// if (a == 3)
	// 	printmess(2, "Error\nMap is not surrounded by walls");
	if (a == 4)
		printmess(2, "Error\nMissing path for one of the 4 directions of color for Floor/Ceiling");
	if (a == 5)
		printmess(2, "Error\nMap is not a .cub extension");
	if (a == 6)
	{
		printmess(2, "Error\nFile ");
		printmess(2, s);
		printmess(2, " does not exist..!");
	}
	if (a == 7)
	{
		printmess(2, "Error\nUnknown object detected in map file -> ");
		printmess(2, s);
	}
	if (a == 8)
		printmess(2, "Error\nMissing arguments");
	if (a == 9)
		printmess(2, "Error\nToo many arguments");
	if (a == 10)
		printmess(2, "Error\nNo map found..!");
	if (a == 11)
	{
		printmess(2, "Error\nColor value incorrect..!");
		free(s);
	}
	if (a == 12)
		printmess(2, "Error\nTwo starting direction found..!");
	exit(0) ;
}
