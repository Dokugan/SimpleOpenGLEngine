#pragma once
#include <vector>
#include <string>

namespace engine
{
		std::vector<int> GetSetting(const std::string& name, const std::string& path = "../Engine/res/default.cfg");
}
