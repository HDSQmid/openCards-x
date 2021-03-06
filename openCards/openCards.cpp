// openCards
//this program is basically cards: computer against humanity.
//it boasts a whopping two games so far, but has quite a few personas to play against. I plan on expanding it



#include "stdafx.h"

#include "deck.h"
#include "User.h"
#include "player.h"
#include "games.h"
#include "data.h"
#include "store.h"
#include "gameIO.h"

#define VERSION_NUM "Alpha 11"
#define VERSION_BUILD_DATE "11th March 2018"

//function for printing statistics
void viewStats() {

	std::cout << "\n ***STATISTICS*** \n\n" << std::endl;
	std::cout << "Wins: " << usr.getWinCt() << std::endl;
	std::cout << "Losses: " << usr.getLossCt() << std::endl;
	std::cout << "Winning Streak: " << usr.getWinStrk() << std::endl;
	std::cout << "Best Winning Streak: " << usr.getBestWinStrk() << std::endl;
	std::cout << "Money in bank: " << usr.getBank() << std::endl;
	std::cout << "\n";

}

//welcome for first run
void welcome() {

	std::cout << "Welcome to openCards " << VERSION_NUM << std::endl;

	std::cout << "What do you want us to call you?" << std::endl;

	std::string name;
	std::getline(std::cin, name);
	usr.setName(name);

	addBreak(2);

	std::cout << "Before you can play, you need to have some people to play against. Let's buy Mr Gupps! \nOh, and take 500 Cashies so that you can actually afford it!" << std::endl;
	usr.addMoney(500);
	addBreak();
	while (!shop.ownsBuy("Mr Gupps")) {

		std::cout << "Just buy it." << std::endl;

	}

	addBreak(2);

	std::cout << "You can't play games without owning the games. Let's buy Blackjack!" << std::endl;
	std::cout << "And because you ~~wasted~~ spent all your money on Mr Gupps, you can't afford it, so take another 500 Cashies" << std::endl;
	usr.addMoney(500);
	addBreak();
	while (!shop.ownsBuy("Blackjack")) {

		std::cout << "Just buy it." << std::endl;

	}
	addBreak(2);
	std::cout << "You're all ready to go!!! \nWelcome, and have fun\n" << std::endl;
	std::cout << "And take another 250 Cashies because I feel nice today" << std::endl;
	usr.addMoney(250);

	addBreak(2);

	data.save();
}

//debug function
void varSizes() {

	std::cout << "Size of card: " << sizeof(card) << std::endl;
	std::cout << "Size of deck: " << sizeof(deck) << std::endl;
	std::cout << "Size of user: " << sizeof(user) << std::endl;
	std::cout << "Size of player: " << sizeof(player) << std::endl;
	std::cout << "Size of gameConfig: " << sizeof(gameConfig) << std::endl;
	std::cout << "Size of dataIO: " << sizeof(dataIO) << std::endl;
	std::cout << "Size of cheats: " << sizeof(cheats) << std::endl;

	std::cout << "Rand() Max: " << RAND_MAX << std::endl;

}

//function to print game info
void printGameInfo() {

	std::cout << "Version " << VERSION_NUM << std::endl;
	std::cout << "Built on " << VERSION_BUILD_DATE << std::endl;
	std::cout << "Open Source Software" << std::endl;

}

//main menu of game
void menu() {
	int validChoice;
	char choice;

	do {

		//display menu
		std::cout << "\nMain menu:" << std::endl;
		std::cout << "Press 1 to start a game\n";
		std::cout << "Press 2 to view statistics\n";
		std::cout << "Press 3 to open the shop\n";
		std::cout << "Press 4 to view game info\n";
		std::cout << "Press 0 to exit\n";

		std::string temp = getInput();
		std::stringstream str(temp);
		str >> choice;

		do {



			switch (choice) {

			case '1':
				startGame();
				validChoice = 1;
				break;

			case '2':
				viewStats();
				validChoice = 1;
				break;

			case '3':
				shop.enter();
				validChoice = 1;
				break;

			case '4':
				printGameInfo();
				validChoice = 1;
				break;

			case '0':
				data.save();
				data.log("Application closed");
				exit(0);
				validChoice = 1;
				break;

			case 'd':
				varSizes();
				validChoice = 1;
				break;

			default:
				std::cout << "invalid choice. Try again" << std::endl;
				validChoice = 0;
				std::cin >> choice;

			}
			//go to start if choice is invalid
			if (!validChoice) continue;



		} while (1 == 0);
	} while (1 == 0);

	return;
}

//starts application. will eventually load data from files
void startApplication(int nNumberofArgs, char*pszArgs[]) {


	srand((unsigned int)time(NULL));

	if (nNumberofArgs == 1) {
		std::cout << "Starting Application..." << std::endl;
		data.load();
	}

	else {

		debuggingMode = 1;

	}


	return;
}

int main(int nNumberofArgs, char*pszArgs[])
{
	data.clearLog();
	data.log("Application launched");

	startApplication(nNumberofArgs, pszArgs);
	try {
		while (1 == 1) {

			menu();
		}

		std::cout << "lel how tf did you get here" << std::endl;
	}

	catch (std::exception e) {
		std::string str = e.what();
		std::string str2 = "Application crashed. Error: " + str;
		data.log(str2);

		addBreak(5);
		std::cout << "An unhandled exception occurred." << std::endl;
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << "Game will save and quit" << std::endl;
		try {
			data.save();
			std::cout << "Game saved successfully" << std::endl;
		}
		catch (...) {

			std::cout << "Game failed to save" << std::endl;

		}


		system("PAUSE");

	}

	catch (...) {

		data.log("Application crashed. Unknown Error.");

		addBreak(5);
		std::cout << "An unhandled exception occurred." << std::endl;
		std::cout << "Game will save and quit" << std::endl;
		try {
			data.save();
			std::cout << "Game saved successfully" << std::endl;
		}
		catch (...) {

			std::cout << "Game failed to save" << std::endl;

		}

		
		system("PAUSE");

	}

	

    return 0;
}

