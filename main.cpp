#include"TicTacToe.h"

int main() 
{
	string num, gameChoice, choice = "y";
	TicTacToe game;
	
	while (choice == "y" || choice == "Y")
	{
		cout << "\tWelcome to Tic  Tac  Toe\n"
			<< "  \tCreate by Ali Haidar\n\n"
			<< "1. Load a Saved Game\n"
			<< "2. Delete a Saved Game\n"
			<< "3. New Game\n\n";

		cout << "Enter your Choice:   ";
		game.setFile();

		getline(cin, gameChoice);

		while (gameChoice != "1" && gameChoice != "2" &&gameChoice != "3") 
		{
			cout << "Invalid input. Enter again:  ";
			getline(cin, gameChoice);

		}

		if (gameChoice == "1") 
		{
			game.inputGameState();
			goto gamePlay;
		}
		else if (gameChoice == "2") 
		{
			game.deleteGameState();
			exit(0);
		}
		else if (gameChoice == "3") 
		{

			cout << "\nSelect playing grid\n"
				<< "1) 3 X 3\n"
				<< "2) 4 X 4\n"
				<< "3) 5 X 5\n\n";

			cout << "Enter your Choice:   ";
			getline(cin, num);
			while (num != "1" && num != "2" && num != "3")
			{
				cout << "Invalid input.\nPlease enter again:   ";
				getline(cin, num);
			}

			if (num == "1")
			{
				game.setSize(3);
			}
			else if (num == "2")
			{
				game.setSize(4);
			}
			else if (num == "3")
			{
				game.setSize(5);
			}

			game.setBoard();
			cout << "\t\tType Save and press enter to save your game at anytime.\n";
			Sleep(1000);
		
		gamePlay:
			while (!game.checkWinState()) 
			{
				if (!game.checkWinState() && game.getTurnCounter() == game.getSize() * game.getSize()) 
				{
					cout << endl;
					game.setBoard();
					cout << "Oops! it's a draw.\n";
					exit(0);
				}
				game.play();
			}

			game.printBoard();
			cout << "Game Over!\nPlayer " << game.getPlayer() - 1 << " is the Winner.\n\n";
			cout << "\Do you Wanna Play Again? Press Y for Yes and N for N\n";
			getline(cin, choice);
		}
	}
}









