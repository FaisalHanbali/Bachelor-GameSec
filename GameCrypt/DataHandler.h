#pragma once
#include <vector>
#include <string>
// Unnecessary class
class DataHandler // Encrypts and Decrypts data
{
public:
	// Returns the data from parameter encrypted (with header)
	std::vector<unsigned char> EncryptData(std::vector<unsigned char> const& data);

	// Returns the decrypted data from parameter without header
	std::vector<unsigned char> DecryptData(std::vector<unsigned char> const& data);
};

