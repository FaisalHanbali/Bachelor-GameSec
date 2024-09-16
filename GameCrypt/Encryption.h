#pragma once
#include <aes.h>
namespace GameCrypt
{
	class Encryption
	{
	public:
		std::vector<unsigned char> Encrypt(std::vector<unsigned char> const& inVec, std::vector<unsigned char>& outIV);
		std::vector<unsigned char> Decrypt(std::vector<unsigned char> const& inVec, std::initializer_list<unsigned char> const& inIV);
	};

#pragma pack(1) // This ensures we dont have padding between the members in memory->If we want this to work cross platform without issues
	struct Encryption_Header
	{
	public:
		Encryption_Header()
		{
			clear();
		}
		void clear()
		{
			original_data_size = 0;
			data_is_compressed = false;
			compressed_data_size = 0;
			encrypted_data_size = 0;
			memset(IV, 0, sizeof(IV));
		}
		size_t original_data_size;
		bool data_is_compressed;
		size_t compressed_data_size; // Compress then encrypt
		size_t encrypted_data_size;
		unsigned char IV[CryptoPP::AES::BLOCKSIZE];
		// Use memcpy_s to assign data from an unsigned char vector
	};
#pragma pack()
}
