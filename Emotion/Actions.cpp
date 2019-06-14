#include "Actions.h"

#define GetCurrentDir _getcwd

std::string Actions::GetCurrentWorkingDir(void)
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

int Actions::num_cifre(int numero)
{
	long cifre = 1, calcola = 0;
	bool finito = false;
	calcola = numero;
	while (!finito)
	{
		calcola /= 10;
		if (calcola != 0) cifre++;
		else finito = true;
	}
	return cifre;
}
