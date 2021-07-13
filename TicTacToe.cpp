#include "TicTacToe.h"



TicTacToe::TicTacToe()
{
	this->mark = 0;
	this->size = 0;
	this->player = 1;
	this->tCounter = 0;
}

void TicTacToe::setSize(int size)
{
	if (size > 0)
	{
		this->size = size;
	}
	else
	{
		size = 3;
	}
}

// getter for size
int TicTacToe::getSize() const
{
	return this->size;
}


TicTacToe::~TicTacToe()
{
	for (int i = 0; i < this->getSize(); i++)
	{
		delete[]board[i];
	}
	delete board;
}

void TicTacToe::setBoard()
{
	board = new int*[size];
	for (int i = 0; i < size; i++)
	{
		board[i] = new int[size];
	}

	for (int i = 0, count = 1; i < size; i++)
	{
		for (int j = 0; j < size; j++, count++)
		{
			board[i][j] = count;
		}
	}
}

void TicTacToe::printBoard()
{
	for (int i = 0; i < size; i++) 
	{	
		for (int j = 0; j < size; j++) 
		{
			// will print X for player 1
			if (board[i][j] == 100) 
			{
				cout << "X" << '\t';
			}
			// will print O for player 2
			else if (board[i][j] == 200)
			{
				cout << "O" << '\t';
			}
			else
			{
				cout << board[i][j] << '\t';
			}
		}
		cout << endl;
	}
}

void TicTacToe::setFile()
{
	file.open("save.txt", ios::in | ios::out | ios::app);
}

void TicTacToe::closeFile()
{
	file.close();
}

// this function will ask the user to select from the given diff saved states of the game and will load the selected
// state into the game to be played again 
void TicTacToe::inputGameState()
{
	system("cls");
	// checking whether there is any save state available to delete or the file is empty :P
	file.seekg(0, ios::end);
	
	if (file.tellg() == 0) 
	{
		cout << "There is no saved state of game found to load.\n";
		exit(0);
	}
	else
	{
		file.seekg(0, ios::beg);
	}

	system("cls");
	
	string temp, choice;
	int counter = 1, playerTurn, tempSize, value;
	vector <string> dates;
	vector <int> sizes, player;

	file >> tempSize;
	sizes.push_back(tempSize);

	file >> playerTurn;
	player.push_back(playerTurn);

	file >> tCounter;

	getline(file, temp);
	dates.push_back(temp);
	cout << counter++ << " " << temp << endl;
	
	while (!file.eof())
	{
		getline(file, temp);
		if (temp == "End")
		{
			file >> tempSize;
			file >> playerTurn;
			file >> tCounter;
			player.push_back(playerTurn);
			sizes.push_back(tempSize);
			getline(file, temp);
			dates.push_back(temp);
			cout << counter++ << " " << temp << endl;
		}
	}
	cout << "Enter you choice: ";
	getline(cin, choice);

	stringstream gameChoice(choice);
	gameChoice >> tempSize;

	while (tempSize > counter || tempSize == 0)
	{
		cout << "Invalid option. Enter again: ";
		getline(cin, choice);

		stringstream gameChoice(choice);
		gameChoice >> tempSize;
	}

	if (tempSize == counter - 1) {
		exit(0);
	}

	file.close();
	file.open("save.txt");
	counter = 0;

	size = sizes[tempSize - 1];
	this->player = player[tempSize - 1];
	setBoard();
	dates.clear();
	sizes.clear();
	temp = "";
	file.clear();
	
	while (!file.eof())
	{
		getline(file, temp);

		if (counter == tempSize - 1)
		{
			for (int i = 0; i < this->size; i++) 
			{
				for (int j = 0; j < this->size; j++) 
				{
					file >> value;
					board[i][j] = value;
				}
			}
		}
		else 
		{
			getline(file, temp);
			getline(file, temp);
		}
		counter++;
	}

	this->printBoard();

}

// this function will save the current situation of the game into the file
void TicTacToe::saveState()
{
	time_t now = time(0);
	char date[26];
	ctime_s(date, sizeof(date), &now);

	file.clear();
	file << this->getSize() << " ";
	file << this->player << " ";
	file << this->getTurnCounter() << " ";
	file << date;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < this->getSize(); j++) 
		{
			file << board[i][j] << " ";
		}
	}

	file << endl << "End" << endl;

}


// will manage the record of how many turns have been made 
int TicTacToe::getTurnCounter() const
{
	return this->tCounter;
}

// this function will delete the selected saved game state from the file specified by the user
void TicTacToe::deleteGameState()
{
	system("cls");

	// checking whether there is any save state available to delete or the file is empty :P
	file.seekg(0, ios::end);
	
	if (file.tellg() == 0)
	{
		cout << "There is no saved state of game found.\n";
		exit(0);
	}
	else
	{
		file.seekg(0, ios::beg);
	}

	string temp, choice;
	int counter = 1, tempSize, value = 0;
	vector <string> dates;
	vector <int> sizes;

	ofstream newFile("newfile.txt");



	file >> tempSize;
	sizes.push_back(tempSize);

	file >> player;
	file >> tCounter;

	getline(file, temp);
	dates.push_back(temp);
	cout << counter++ << " " << temp << endl;
	
	while (!file.eof())
	{
		getline(file, temp);
		if (temp == "End") 
		{
			file >> tempSize;
			sizes.push_back(tempSize);

			file >> player;

			file >> tCounter;

			getline(file, temp);
			dates.push_back(temp);
			cout << counter++ << " " << temp << endl;
		}
	}
	cout << "Enter you choice: ";
	getline(cin, choice);

	stringstream gameChoice(choice);
	gameChoice >> tempSize;

	while (tempSize > counter || tempSize == 0) 
	{
		cout << "Invalid input. Enter again: ";
		getline(cin, choice);

		stringstream gameChoice(choice);
		gameChoice >> tempSize;
	}

	if (tempSize == counter - 1) 
	{
		exit(0);
	}

	file.close();
	file.open("save.txt");
	counter = 0;

	char c;
	size = sizes[tempSize - 1];
	dates.clear();
	sizes.clear();
	temp = "";
	file.clear();
	
	while (!file.eof()) 
	{
		getline(file, temp);

		if (counter == tempSize - 1) 
		{
			file.ignore(200, 'd');
			c = file.get();
			counter++;
			continue;
		}
		else
		{
			newFile << temp;
			if (!file.eof())
			{
				newFile << endl;
			}
		}
		if (temp == "End")
		{
			counter++;
		}

	}
	file.close();
	newFile.close();

	remove("save.txt");
	rename("newFile.txt", "save.txt");
	cout << endl << "Game has Successfully Deleted!";

}



// Will ask player for cell number to mark
void TicTacToe::play()
{
	system("cls");
	printBoard();

	cout << "Player " << this->player << " enter the cell-number where you want to mark.\n\n";
	getline(cin, markPause);
	
	if (markPause == "save" || markPause == "Save") 
	{
		this->saveState();
		cout << "Your game has been saved.\n";
		exit(0);
	}

	else
	{
		stringstream num(markPause);
		num >> mark;
		
		while (mark > size*size || mark < 0 || mark == 0)
		{
			cout << "Invalid entry. Pls Enter agian.\n";
			getline(cin, markPause);
			stringstream num(markPause);
			num >> mark;
		}
	}

	markCell(mark);

	if (player == 1)
	{
		player = 2;
	}
	else
	{
		player = 1;
	}
	this->tCounter++;
}


// Will mark cell for each player
void TicTacToe::markCell(int m)
{
	// validating entry number
	while (m < 0 || m > (this->size * this->size) - 1) 
	{
		cout << "No such cell exits. Please enter again.\n";
		cin >> m;
	}

	bool flag = 0;
	// marking the cell 
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) 
		{
			// will mark 100 if it is player 1
			if (board[i][j] == m && player == 1 && (board[i][j] != 100 || board[i][j] != 200)) 
			{
				board[i][j] = 100;
				flag = 1;
				break;
			}

			// will mark 200 if it is player 2
			else if (board[i][j] == m && player == 2 && (board[i][j] != 100 || board[i][j] != 200)) 
			{
				board[i][j] = 200;
				flag = 1;
				break;
			}
		}
	}
	// preventing overwrite
	if (!flag) 
	{
		cout << "Given cell is filled. Please enter again.";
		getline(cin, markPause);

		if (markPause == "save" || markPause == "Save")
		{
			this->saveState();
			cout << "Your game has been saved.\n";
			exit(0);
		}
		else
		{
			stringstream num(markPause);
			num >> m;
		}
		markCell(m);
	}
}

// checking the win state
bool TicTacToe::checkWinState()
{
	int counter;
	// checking whether the player has a same row
	for (int i = 0; i < size; i++)
	{
		counter = 0;
		for (int j = 0; j < size; j++) 
		{
			if (i == size - 1)
			{
				continue;
			}
			if (board[i][j] == board[i][j + 1])
			{
				counter++;
			}
		}

		if (counter == size - 1)
		{
			return true;
		}
	}

	// checking whether the player has a same col
	for (int i = 0; i < size; i++) 
	{
		counter = 0;
		for (int j = 0; j < size; j++) 
		{
			if (j == size - 1)
			{
				continue;
			}
			if (board[j][i] == board[j + 1][i])
			{
				counter++;
			}
		}

		if (counter == size - 1)
		{
			return true;
		}
	}


	// checking whether the player has a same priDiagonal
	counter = 0;
	for (int i = 0, j = this->size - 1; i < size; i++, j--)
	{
		if (i == this->size - 1)
		{
			continue;
		}
		if (board[i][j] == board[i + 1][j - 1])
		{
			counter++;
		}
	}

	if (counter == this->size - 1) 
	{
		return true;
	}

	// checking whether the player has a same secDiagonal
	counter = 0;
	for (int i = 0, j = 0; i < size; i++, j++) 
	{
		if (i == this->size - 1)
		{
			continue;
		}
		
		if (board[i][j] == board[i + 1][j + 1])
		{
			counter++;
		}
	}

	if (counter == this->size - 1) 
	{
		return true;
	}

	return false;
}

// getter for playerNo
int TicTacToe::getPlayer() const
{
	return this->player;
}










