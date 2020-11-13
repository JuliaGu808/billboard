#include <stdio.h>
#include <stdlib.h>
#include "safeinput.h"
#include <stdbool.h>
#include <time.h>
#include "serial.h"
#include <Windows.h>

void visaReklam(SERIALPORT port)
{
	printf("Restarting ad-lineup.\n");
	SerialWritePort(port, "a:", strlen("a:"));
	/*char buf[512];
	SerialReadPort(port, buf, 512);*/
}

void brandlarm(SERIALPORT port)
{
	printf("Activating fire emergency protocol.\n");
	SerialWritePort(port, "b:", strlen("b:"));
	/*char buf[512];
	SerialReadPort(port, buf, 512);*/
}

void Huvudmeny(SERIALPORT port)
{
	int exit = 0;
	while (exit == 0)
	{
		printf("***Main menu***\n");
		printf("1. Visa reklam\n2. Aktivera brandlarm\n");
		int selection;
		if (GetInputInt("Selection:>", &selection) == false)
			continue;
		switch (selection)
		{
		case 1:
			visaReklam(port);
			break;
		case 2:
			brandlarm(port);
			break;
		}
	}
}

int main()
{
	SERIALPORT port = SerialInit("\\\\.\\COM5");
	if (!SerialIsConnected(port))
	{
		return;
	}

	Huvudmeny(port);

	return 0;
}