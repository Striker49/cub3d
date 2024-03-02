
#include "cub3d.h"

int	errmessage(int a)
{
	if (a == 1)
		printf("Error\nWrong number of objects");
	//if (a == 2)
		//printf("Error\nMap is not rectangular");
	if (a == 3)
		printf("Error\nMap is not surrounded by walls");
	// if (a == 4)
	// 	printf("Error\nNo path to exit");
	if (a == 5)
		printf("Error\nMap is not a .cub extension");
	if (a == 6)
		printf("Error\nMap is too big");
	if (a == 7)
		printf("Error\nUnknown objet detected in map file");
	if (a == 8)
		printf("Error\nMissing arguments");
	if (a == 9)
		printf("Error\nToo many arguments");
	exit(0);
}