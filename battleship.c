//*******************************************
//*************Battleship - Exam 2***********
//**Written by - Steve, Jeremy, and Daniela**
//**********Due Sunday October 8th***********
//*******************************************

#include "template.h"

void displayMenu();
void displayGrid(char battleField[SIZE][SIZE]);
char getChoice();
void placeAircraftCarrier(char battleField[SIZE][SIZE]);
void placeBattleship(char battleField[SIZE][SIZE]);
void placeCruiser(char battleField[SIZE][SIZE]);
void placeDestroyer(char battleField[SIZE][SIZE]);
void placeSubmarine(char battleField[SIZE][SIZE]);
void reset(char battleField[SIZE][SIZE]);
void saveFile(char battleField[SIZE][SIZE], int missiles);
void loadFile(char battleField[SIZE][SIZE], int missiles);
void loadHighScores(int missiles, char initials[3]);
void saveHighScores(int missiles, char initials[3]);
void shootMissiles(int *missiles, char userGrid[SIZE][SIZE], char battleField[SIZE][SIZE]);

int main() {
	char battleField[SIZE][SIZE] = { // stores ship placements
		{ '\0',  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' },
		{ '0',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '1',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '2',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '3',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '4',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '5',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '6',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '7',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '8',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
		{ '9',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	};
	char userGrid[SIZE][SIZE] = { // stores hits and misses
	{ '\0',  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' },
	{ '0',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '1',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '2',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '3',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '4',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '5',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '6',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '7',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '8',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	{ '9',  'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
	};
	char choice;
	char initials[3];
	int missiles = 0;

	do {
		displayMenu();
		choice = getChoice();
		switch (choice) {
		case 'S':
			CLS;
			reset(battleField);
			printf("Placing ships...");
			placeCruiser(battleField);
			placeAircraftCarrier(battleField);
			placeBattleship(battleField);
			placeSubmarine(battleField);
			placeDestroyer(battleField);
			displayGrid(battleField);
			shootMissiles(&missiles, userGrid, battleField);
			saveHighScores(missiles, initials);
			break;
		case 'H':
			loadHighScores(missiles, initials);
			break;
		case 'Q':
			printf("Thanks for playing!\n\n");
			PAUSE;
			break;
		default:
			printf("ERROR - INVALID ENTRY.\n");
			PAUSE;
			break;
		}// end switch
	} while (choice != 'Q');
}//End Main *************************************************************************************************

void displayMenu() {
	CLS;
	printf("*****BATTLESHIP*****\n\n");
	printf("[S]tart Game.\n");
	printf("[H]igh scores.\n");
	printf("[Q]uit.\n\n");
	printf("Enter selection: ");
}// end displayMenu

void displayGrid(char battleField[SIZE][SIZE]) {
	int i = 0;
	int j = 0;

	for (i = 0; i < 11; i++) {
		printf("\n");
		for (j = 0; j < 11; j++) {
			printf(" %c ", battleField[i][j]);
		}
	}   printf("\n");
}//End displayGrid

char getChoice() {
	char result;
	scanf("%c", &result); FLUSH;
	result = toupper(result);
	return result;
}// end getChoice

void placeAircraftCarrier(char battleField[SIZE][SIZE]) {
	int x, y, z, i, temp;
	char collision;

	srand((unsigned)time(NULL));

	// test if ship placement is possible
	do {
		collision = 'N';
		x = (rand() % 9) + 1;
		y = (rand() % 9) + 1;
		z = (rand() % 4) + 1;
		if (z == 1) {
			temp = x;
			for (i = 0; i < 5; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
			}
		}// end if case 1

		else if (z == 2) {
			temp = x;
			for (i = 0; i < 5; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
			}
		}// end if case 2

		else if (z == 3) {
			temp = y;
			for (i = 0; i < 5; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
			}
		}// end if case 3

		else if (z == 4) {
			temp = y;
			for (i = 0; i < 5; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
			}
		}// end if case 4
	} while (collision != 'N');
	// place the ships

	switch (z) {
	case 1:// down
		for (i = 0; i < 5; i++) {
			battleField[x][y] = 'A';
			x++;
		}
		break;
	case 2:// up
		for (i = 0; i < 5; i++) {
			battleField[x][y] = 'A';
			x--;
		}
		break;
	case 3:// right
		for (i = 0; i < 5; i++) {
			battleField[x][y] = 'A';
			y++;
		}
		break;
	case 4:// left	
		for (i = 0; i < 5; i++) {
			battleField[x][y] = 'A';
			y--;
		}
		break;
	default:
		break;
	}// end switch
}// end placeAircraftCarrier

void placeCruiser(char battleField[SIZE][SIZE]) {
	int x, y, z, i, temp;
	char collision;

	srand((unsigned)time(NULL));

	// test if ship placement is possible
	do {
		collision = 'N';
		x = (rand() % 9) + 1;
		y = (rand() % 9) + 1;
		z = (rand() % 4) + 1;
		if (z == 1) {
			temp = x;
			for (i = 0; i < 2; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 1

		else if (z == 2) {
			temp = x;
			for (i = 0; i < 2; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 2

		else if (z == 3) {
			temp = y;
			for (i = 0; i < 2; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 3

		else if (z == 4) {
			temp = y;
			for (i = 0; i < 2; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 4
	} while (collision != 'N');
	// place the ships

	switch (z) {
	case 1:// down
		if (collision == 'N') {
			for (i = 0; i < 2; i++) {
				battleField[x][y] = 'C';
				x++;
			}
		}
		break;
	case 2:// up
		if (collision == 'N') {
			for (i = 0; i < 2; i++) {
				battleField[x][y] = 'C';
				x--;
			}
		}
		break;
	case 3:// right
		if (collision == 'N') {
			for (i = 0; i < 2; i++) {
				battleField[x][y] = 'C';
				y++;
			}
		}
		break;
	case 4:// left
		if (collision == 'N') {
			for (i = 0; i < 2; i++) {
				battleField[x][y] = 'C';
				y--;
			}
		}
		break;
	default:
		break;

	}// end switch
}// end placeCruiser

void placeBattleship(char battleField[SIZE][SIZE]) {
	int x, y, z, i, temp;
	char collision;

	srand((unsigned)time(NULL));

	// test if ship placement is possible
	do {
		collision = 'N';
		x = (rand() % 9) + 1;
		y = (rand() % 9) + 1;
		z = (rand() % 4) + 1;
		if (z == 1) {
			temp = x;
			for (i = 0; i < 4; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 1

		else if (z == 2) {
			temp = x;
			for (i = 0; i < 4; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 2

		else if (z == 3) {
			temp = y;
			for (i = 0; i < 4; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 3

		else if (z == 4) {
			temp = y;
			for (i = 0; i < 4; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 4
	} while (collision != 'N');
	// place the ships

	switch (z) {
	case 1:// down
		if (collision == 'N') {
			for (i = 0; i < 4; i++) {
				battleField[x][y] = 'B';
				x++;
			}
		}
		break;
	case 2:// up
		if (collision == 'N') {
			for (i = 0; i < 4; i++) {
				battleField[x][y] = 'B';
				x--;
			}
		}
		break;
	case 3:// right
		if (collision == 'N') {
			for (i = 0; i < 4; i++) {
				battleField[x][y] = 'B';
				y++;
			}
		}
		break;
	case 4:// left
		if (collision == 'N') {
			for (i = 0; i < 4; i++) {
				battleField[x][y] = 'B';
				y--;
			}
		}
		break;
	default:
		break;

	}// end switch
}// end placeBattleship

void placeSubmarine(char battleField[SIZE][SIZE]) {
	int x, y, z, i, temp;
	char collision;

	srand((unsigned)time(NULL));

	// test if ship placement is possible
	do {
		collision = 'N';
		x = (rand() % 9) + 1;
		y = (rand() % 9) + 1;
		z = (rand() % 4) + 1;
		if (z == 1) {
			temp = x;
			for (i = 0; i < 3; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 1

		else if (z == 2) {
			temp = x;
			for (i = 0; i < 3; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 2

		else if (z == 3) {
			temp = y;
			for (i = 0; i < 3; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 3

		else if (z == 4) {
			temp = y;
			for (i = 0; i < 3; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 4
	} while (collision != 'N');
	// place the ships

	switch (z) {
	case 1:// down
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'S';
				x++;
			}
		}
		break;
	case 2:// up
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'S';
				x--;
			}
		}
		break;
	case 3:// right
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'S';
				y++;
			}
		}
		break;
	case 4:// left
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'S';
				y--;
			}
		}
		break;
	default:
		break;

	}// end switch
}// end placeSubmarine

void placeDestroyer(char battleField[SIZE][SIZE]) {
	int x, y, z, i, temp;
	char collision;


	// test if ship placement is possible
	do {
		collision = 'N';
		srand((unsigned)time(NULL));
		x = (rand() % 9) + 1;
		y = (rand() % 9) + 1;
		z = (rand() % 4) + 1;
		if (z == 1) {
			temp = x;
			for (i = 0; i < 3; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 1

		else if (z == 2) {
			temp = x;
			for (i = 0; i < 3; i++) {
				if (battleField[temp][y] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 2

		else if (z == 3) {
			temp = y;
			for (i = 0; i < 3; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp++;
				collision = 'N';
			}
		}// end if case 3

		else if (z == 4) {
			temp = y;
			for (i = 0; i < 3; i++) {
				if (battleField[x][temp] != 'W') {
					collision = 'Y';
					break;
				}
				temp--;
				collision = 'N';
			}
		}// end if case 4
	} while (collision != 'N');
	// place the ships

	switch (z) {
	case 1:// down
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'D';
				x++;
			}
		}
		break;
	case 2:// up
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'D';
				x--;
			}
		}
		break;
	case 3:// right
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'D';
				y++;
			}
		}
		break;
	case 4:// left
		if (collision == 'N') {
			for (i = 0; i < 3; i++) {
				battleField[x][y] = 'D';
				y--;
			}
		}
		break;
	default:
		break;

	}// end switch

}// end placeDestroyer

void reset(char battleField[SIZE][SIZE]) {
	int i, j;

	for (i = 1; i < 11; i++) {
		for (j = 1; j < 11; j++)
			battleField[i][j] = 'W';
	}
}// end reset

void saveHighScores(int missiles, char initials[3]) {
	printf("Enter initials: ");
	scanf("%s", initials); FLUSH;
	initials = toupper(initials);
	FILE* ptr;
	ptr = fopen("highscores.bin", "ab");

	if (ptr == NULL) {
		printf("ERROR... COULD NOT OPEN FILE\n");
		PAUSE;
		exit(-1);
	}
	fwrite(&missiles, sizeof(missiles), 10, ptr);
	fwrite(&initials, sizeof(initials), 3, ptr);
	fclose(ptr);

}

void loadHighScores(int missiles, char initials[3]) {
	FILE* ptr;
	ptr = fopen("highscores.bin", "rb");
	fread(&missiles, sizeof(missiles), 10, ptr);
	fread(&initials, sizeof(initials), 3, ptr);
	printf("%s: %i missiles fired.\n", initials, missiles);
	fclose(ptr);
	PAUSE;
}

void shootMissiles(int *missiles, char userGrid[SIZE][SIZE], char battleField[SIZE][SIZE]) {
	char colCoordinate;
	char invalid;
	int x, y;
	int hits = 0, cruiserHits = 0, destroyerHits = 0, subHits = 0, 
		aircraftCarrierHits = 0, battleShipHits = 0;

	do {
		
		do {
			invalid = 'Y';
			CLS;
			printf("*****BATTLESHIP*****\n");
			displayGrid(userGrid);
			printf("\nEnter first coordinate(A-J): ");
			scanf("%c", &colCoordinate); FLUSH;
			colCoordinate = toupper(colCoordinate);
			printf("Enter second coordinate(0-9): ");
			scanf("%i", &y); FLUSH;

			y = y++; // makes y value correspond with array subscript

			if (y > 9 || y < 0) {
				printf("INVALID CHOICE\n");
				invalid = 'Y';
				break;
			}

			// convert A-J to their corresponding array values
			switch (colCoordinate) {
			case 'A':
				x = 1;
				invalid = 'N';
				break;
			case 'B':
				x = 2;
				invalid = 'N';
				break;
			case 'C':
				x = 3;
				invalid = 'N';
				break;
			case 'D':
				x = 4;
				invalid = 'N';
				break;
			case 'E':
				x = 5;
				invalid = 'N';
				break;
			case 'F':
				x = 6;
				invalid = 'N';
				break;
			case 'G':
				x = 7;
				invalid = 'N';
				break;
			case 'H':
				x = 8;
				invalid = 'N';
				break;
			case 'I':
				x = 9;
				invalid = 'N';
				break;
			case 'J':
				x = 10;
				invalid = 'N';
				break;
			default:
				printf("INVALID CHOICE\n");
				break;
			}

			// tests if coordinates have been used previously
			if (userGrid[y][x] == 'A' || userGrid[y][x] == 'B' || userGrid[y][x] == 'C' || userGrid[y][x] == 'D' 
				|| userGrid[y][x] == 'S' ||userGrid[y][x] == 'M') {
				printf("Error... You already used those coordinates.\n");
				invalid = 'Y';
				PAUSE;
			}

		} while (invalid != 'N');

		// check if hit or miss by specific ship
		if (battleField[y][x] != 'W' && battleField[y][x] == 'A') {
			aircraftCarrierHits++;
			hits++;
			(*missiles)++;
			userGrid[y][x] = 'A';
			printf("Hit!\n");
			if (aircraftCarrierHits == 5)
				printf("Aircraft Carrier sunk!\n");
			printf("Missiles used: %i\n", *missiles);
			PAUSE;
		}
		else if (battleField[y][x] != 'W' && battleField[y][x] == 'B') {
			battleShipHits++;
			hits++;
			(*missiles)++;
			userGrid[y][x] = 'B';
			printf("Hit!\n");
			if (battleShipHits == 4)
				printf("Battleship sunk!\n");
			printf("Missiles used: %i\n", *missiles);
			PAUSE;
		}
		else if (battleField[y][x] != 'W' && battleField[y][x] == 'C') {
			cruiserHits++;
			hits++;
			(*missiles)++;
			userGrid[y][x] = 'C';
			printf("Hit!\n");
			if (cruiserHits == 2)
				printf("Cruiser sunk!\n");
			printf("Missiles used: %i\n", *missiles);
			PAUSE;
		}
		else if (battleField[y][x] != 'W' && battleField[y][x] == 'D') {
			destroyerHits++;
			hits++;
			(*missiles)++;
			userGrid[y][x] = 'D';
			printf("Hit!\n");
			if (destroyerHits == 3)
				printf("Destroyer sunk!\n");
			printf("Missiles used: %i\n", *missiles);
			PAUSE;
		}
		else if (battleField[y][x] != 'W' && battleField[y][x] == 'S') {
			subHits++;
			hits++;
			(*missiles)++;
			userGrid[y][x] = 'S';
			printf("Hit!\n");
			if (subHits == 3)
				printf("Submarine sunk!\n");
			printf("Missiles used: %i\n", *missiles);
			PAUSE;
		}
		else { // miss
			(*missiles)++;
			userGrid[y][x] = 'M';
			printf("Miss!\n");
			printf("Missiles used: %i\n", *missiles);
			PAUSE;
		}
		if (hits == 17) {
			printf("You win!\n");
			PAUSE;
		}
	} while (hits != 17);

}// end shootMissiles
