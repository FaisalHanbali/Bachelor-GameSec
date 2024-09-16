#include <iostream>
#include <FileIO.h>
#include <ThemidaSDK.h>
int main()
{
	VM_START
	GameCrypt::FileIO fileIO;
	std::vector<unsigned char> actualData;
	fileIO.LoadEncryptedFile(actualData, L"EncryptedData.bin");
	VM_END
}