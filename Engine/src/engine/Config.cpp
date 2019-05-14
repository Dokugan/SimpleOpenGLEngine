#include "Config.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>

namespace engine {

	std::vector<int> GetSetting(const std::string& name, const std::string& path)
	{
		std::vector<int> results;

		std::ifstream stream(path);

		std::string line;
		int linenum = 1;
		while (std::getline(stream, line))
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
				std::istream_iterator<std::string>{} };

			if (!tokens.empty())
			{
				if (tokens.at(0) == name && tokens.at(1) == "=")
				{
					try
					{
						for (int i = 2; i < tokens.size(); i++)
						{
							results.push_back(std::stoi(tokens.at(i)));
						}
					}
					catch (...)
					{
						std::cout << "ERROR parsing config file at line" << linenum;
					}
				}
			}
			linenum++;
		}
		return results;
	}

// 	void Config::ParseConfig(const std::string & path)
// 	{
// 		std::ifstream stream(path);
//
// 		std::string line;
// 		int linenum = 1;
// 		while (std::getline(stream, line))
// 		{
// 			std::istringstream iss(line);
// 			std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
// 											std::istream_iterator<std::string>{} };
// 			if (!tokens.empty())
// 			{
// 				if (tokens.at(0) == "windowWidth" && tokens.at(1) == "="){
// 					try	{
// 						this->windowWidth = std::stoi(tokens.at(2));
// 					}
// 					catch (std::invalid_argument&){
// 						std::cout << "ERROR parsing config file at line" << linenum;
// 					}				
// 				}
// 				else if (tokens.at(0) == "windowHeight" && tokens.at(1) == "="){
// 					try{
// 						this->windowHeight = std::stoi(tokens.at(2));
// 					}
// 					catch (std::invalid_argument&){
// 						std::cout << "ERROR parsing config file at line" << linenum;
// 					}
// 				}
// 				else if (tokens.at(0) == "inputAxisPositiveY" && tokens.at(1) == "="){
// 					for (size_t i = 2; i < tokens.size(); i++){
// 						try {
// 							AxisYPositive.push_back(std::stoi(tokens.at(i)));
// 						}
// 						catch (std::invalid_argument&) {
// 							std::cout << "ERROR parsing config file at line" << linenum;
// 						}
// 					}
// 				}
// 				else if (tokens.at(0) == "inputAxisPositiveX" && tokens.at(1) == "="){
// 					for (size_t i = 2; i < tokens.size(); i++){
// 						try {
// 							AxisXPositive.push_back(std::stoi(tokens.at(i)));
// 						}
// 						catch (std::invalid_argument&) {
// 							std::cout << "ERROR parsing config file at line" << linenum;
// 						}						
// 					}
// 				}
// 				else if (tokens.at(0) == "inputAxisNegativeY" && tokens.at(1) == "="){
// 					for (size_t i = 2; i < tokens.size(); i++){
// 						try {
// 							AxisYNegative.push_back(std::stoi(tokens.at(i)));
// 						}
// 						catch (std::invalid_argument&) {
// 							std::cout << "ERROR parsing config file at line" << linenum;
// 						}						
// 					}
// 				}
// 				else if (tokens.at(0) == "inputAxisNegativeX" && tokens.at(1) == "="){
// 					for (size_t i = 2; i < tokens.size(); i++){
// 						try {
// 							AxisXNegative.push_back(std::stoi(tokens.at(i)));
// 						}
// 						catch (std::invalid_argument&) {
// 							std::cout << "ERROR parsing config file at line" << linenum;
// 						}						
// 					}
// 				}
// 			}
// 			linenum++;
// 		}
// 	}

}
