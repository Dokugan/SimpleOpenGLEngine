#pragma once
#include <vector>

namespace engine
{
	class Config
	{
	public:
	 	int windowHeight, windowWidth;
		std::vector<int> AxisXPositive, AxisXNegative, AxisYPositive, AxisYNegative;

		Config();
		Config(const std::string& path);

		void ParseConfig(const std::string& path);

		~Config();
	};
}
