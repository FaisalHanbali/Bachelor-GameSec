#include "pch.h"
#include "Encryption.h"
#include <rijndael.h>
#include <modes.h>
#include <cryptlib.h>
#include <aes.h>
#include <filters.h>
#include <osrng.h>
#include <iostream>

namespace GameCrypt
{
	std::vector<unsigned char> Encryption::Encrypt(std::vector<unsigned char> const& inVec, std::vector<unsigned char>& outIV)
	{
		using namespace CryptoPP;
		std::vector<unsigned char> ret; // Ciphertext will be here

		// Encryption key. We will not generate it because 
		std::initializer_list<unsigned char> key =
		{
			0xA3, 0xB2, 0x3C, 0x92, 0xFF, 0xD0, 0x03, 0x22,
			0x54, 0xAB, 0xDD, 0x32, 0xC9, 0xEA, 0xF2, 0x60
		};

		// Generate IV
		AutoSeededRandomPool prng;
		SecByteBlock iv(AES::BLOCKSIZE);
		prng.GenerateBlock(iv, iv.size());
		{
			std::vector<unsigned char> vector_iv(iv.begin(), iv.end());
			outIV.clear();
			outIV.reserve(vector_iv.size());
			outIV.swap(vector_iv); // we now have outIV assigned
		}// end lifetime of vector_iv

		CFB_Mode<AES>::Encryption e;
		e.SetKeyWithIV(key.begin(), AES::DEFAULT_KEYLENGTH, iv.begin(), AES::BLOCKSIZE); // 16 bytes == 128 bits
		AES::Encryption aesEncryption(key.begin(), AES::DEFAULT_KEYLENGTH);

		CFB_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv.begin());
		VectorSource encryptor(inVec, true, new StreamTransformationFilter(cbcEncryption, new VectorSink(ret)));

		StreamTransformationFilter filter(e);
		filter.Put((const byte*)inVec.data(), inVec.size());
		filter.MessageEnd();

		ret.resize(filter.MaxRetrievable());
		filter.Get(ret.data(), ret.size());
		return ret;
	}

	std::vector<unsigned char> Encryption::Decrypt(std::vector<unsigned char> const& inVec, std::initializer_list<unsigned char> const& inIV)
	{
		using namespace CryptoPP;

		std::vector<unsigned char> ret; // Decrypted text will be here
		std::initializer_list<unsigned char> key =
		{
			0xA3, 0xB2, 0x3C, 0x92, 0xFF, 0xD0, 0x03, 0x22,
			0x54, 0xAB, 0xDD, 0x32, 0xC9, 0xEA, 0xF2, 0x60
		};

		CFB_Mode<AES>::Encryption e;
		e.SetKeyWithIV(key.begin(), AES::DEFAULT_KEYLENGTH, inIV.begin(), AES::BLOCKSIZE); // 16 bytes == 128 bits
		AES::Decryption aesDecryption(key.begin(), AES::DEFAULT_KEYLENGTH);

		CFB_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, inIV.begin());
		VectorSource encryptor(inVec, true, new StreamTransformationFilter(cbcDecryption, new VectorSink(ret)));

		StreamTransformationFilter filter(e);
		filter.Put((const byte*)inVec.data(), inVec.size());
		filter.MessageEnd();

		ret.resize(filter.MaxRetrievable());
		filter.Get(ret.data(), ret.size()); // Obtain data into ret
		return ret;
	}
}