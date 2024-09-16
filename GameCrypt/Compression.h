#pragma once
#include <iostream>
#include <vector>
namespace GameCrypt 
{
	class Compressor
	{
	public:
		std::vector<unsigned char> Compress(std::vector<unsigned char> const& data);
		std::vector<unsigned char> Decompress(std::vector<unsigned char> const& data);
	};
}