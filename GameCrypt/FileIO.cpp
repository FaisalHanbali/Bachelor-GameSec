#include "pch.h"
#include "FileIO.h"
#include "Mutex.h"
#include "Encryption.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Compression.h"

namespace GameCrypt
{
	bool FileIO::SaveFile(std::vector<unsigned char> const& inData, std::wstring const& fileName)
	{
		Mutex mute;
		if (inData.empty())
		{
			return false;
		}
		std::ofstream file;
		file.open(fileName, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
		if (file.is_open())
		{
			file.write((const char*)inData.data(), (std::streamsize)inData.size());
			file.close();
			return true;
		}
		else
		{
			if (file.fail())
			{
				std::cerr << "Error writing to file: " << errno << std::endl;
			}
			file.close();
			return false;
		}
		return false;
	}
	bool FileIO::LoadFile(std::vector<unsigned char>& outData, std::wstring const& fileName)
	{
		// Note: If you want to utilize loading files in your filesystem with multiple files in a single pack, 
		// then you need to read header first (to know how much data coming up belongs to that file) then read and repeat.
		Mutex mute;
		std::ifstream file;
		file.open(fileName, std::ios_base::binary); // Important, we are reading binary data
		if (file.is_open())
		{
			auto size = std::filesystem::file_size(fileName);
			file.seekg(0, std::ios::beg); // Move the position back to the beginning of the file
			outData.resize(size);
			outData.reserve(size);
			file.read((char*)outData.data(), size); // read entire file size
			file.close();
			return true;
		}
		else
		{
			if (file.fail())
			{
				std::cerr << "Error reading to file: " << errno << std::endl;
			}
			file.close();
			return false;
		}
		return false;
	}
	bool FileIO::SaveToFileEncrypted(std::vector<unsigned char> const& inVec, std::wstring const& fileName)
	{
		if (inVec.empty() || fileName.empty())
		{
			return false;
		}
		Encryption_Header header;
		header.original_data_size = inVec.size();
		header.data_is_compressed = false; // Do not use compression. Maybe make a global for this or for specific file formats
		std::vector<unsigned char> EncryptedData;
		std::vector<unsigned char> Data = inVec;
		std::vector<unsigned char> outIV;

		{
			Mutex mute;
			header.compressed_data_size = header.original_data_size;
			Encryption encryption;
			EncryptedData = encryption.Encrypt(Data, outIV);
			if (EncryptedData.empty())
			{
				return false;
			}
			header.encrypted_data_size = EncryptedData.size();

			if (outIV.size() < sizeof(header.IV))
			{
				return false; // Error: IV too small in outIV -> Something went wrong
			}
			memcpy_s(header.IV, sizeof(header.IV), &outIV.at(0), sizeof(header.IV)); // Put IV into the header

			// Assemble final data: Header then data
			std::vector<unsigned char> finalData(sizeof(Encryption_Header));
			memcpy_s(finalData.data(), finalData.size(), &header, sizeof(header)); // Add header
			finalData.insert(finalData.end(), EncryptedData.begin(), EncryptedData.end()); // Add data
			finalData.swap(EncryptedData);
		} // end of mutex lifetime

		return SaveFile(EncryptedData, fileName);
	}
	bool FileIO::LoadEncryptedFile(std::vector<unsigned char>& outVec, std::wstring const& fileName)
	{
		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open())
		{
			return false;
		}
		size_t offset = 0;
		file.seekg(offset, std::ios::beg);
		std::vector<unsigned char> headerDataVec(sizeof(Encryption_Header));
		file.read(reinterpret_cast<char*>(headerDataVec.data()), sizeof(Encryption_Header));
		offset += sizeof(Encryption_Header);

		Encryption_Header header;
		memcpy_s(&header, sizeof(header), &headerDataVec.at(0), sizeof(header));

		file.seekg(offset, std::ios::beg);
		std::vector<unsigned char> encryptedData(header.encrypted_data_size);
		file.read(reinterpret_cast<char*>(encryptedData.data()), header.encrypted_data_size);

		Encryption encryption;
		outVec = encryption.Decrypt(encryptedData, std::initializer_list<unsigned char>(header.IV, header.IV + CryptoPP::AES::BLOCKSIZE));
		file.close();
		return !outVec.empty();
	}


} // namespace GameCrypt
