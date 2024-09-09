#pragma once
#include <vector>
#include <string>

namespace GameCrypt
{
	class FileIO
	{
	public:
		bool SaveToFile(CharV const& inVec, std::wstring const& fileName);
		bool ReadFile(CharV& outVec, std::wstring const& fileName);
	};
}