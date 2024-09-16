#pragma once
#include <vector>
#include <string>

namespace GameCrypt
{
	class FileIO
	{
	public:
		
		bool SaveFile(std::vector<unsigned char> const& inData, std::wstring const& fileName);
		bool LoadFile(std::vector<unsigned char>& outData, std::wstring const& fileName);

		bool SaveToFileEncrypted(std::vector<unsigned char> const& inData, std::wstring const& fileName);
		bool LoadEncryptedFile(std::vector<unsigned char>& outData, std::wstring const& fileName);
	};
}