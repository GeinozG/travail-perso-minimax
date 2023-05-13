#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Game.h"

const int SQUARE_SIZE = 200;

int main(int argc, char* argv[])
{
	try
	{
        std::ifstream configFile;
        configFile.open("./config.txt");

        if (!configFile.is_open())
        {
            throw std::runtime_error("config file not found");
        }

        std::string line;
        int searchDepth = -1;
        int iStartingPlayer = -1;
        float windowScale = -1;
        while (configFile)
        {
            std::getline(configFile, line);

            // Remove whitespaces from the line
            line.erase(
                std::remove_if(line.begin(), line.end(), ::isspace),
                line.end()
            );

            std::string option = line.substr(0, line.find('='));
            std::string value = line.substr(line.find('=') + 1);

            if (option == "search_depth") searchDepth = std::stoi(value);
            else if (option == "starting_player") iStartingPlayer = std::stoi(value);
            else if (option == "window_scale") windowScale = std::stof(value);
            else if (option[0] == '#' || '\n') continue;
            else throw std::runtime_error("Unknown option: " + option);
        }
        configFile.close();

        SquareType startingPlayer;
        switch (iStartingPlayer)
        {
        case 1:
            startingPlayer = SquareType::Human;
            break;
        case 2:
            startingPlayer = SquareType::Computer;
            break;
        default:
            startingPlayer = SquareType::Human;
            break;
        }

	    Game game(SQUARE_SIZE, searchDepth, startingPlayer, windowScale);
	    game.loadAssets();

	    game.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
        return -1;
	}

    return 0;
}
