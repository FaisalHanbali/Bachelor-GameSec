#include "pch.h"
#include "CppUnitTest.h"
#include "FileIO.h"
#include <Encryption.h>
#include <Compression.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace GameCryptTest
{
	std::vector<unsigned char> expectedData = {
				'L', 'o', 'r', 'e', 'm', ' ', 'i', 'p', 's', 'u', 'm', ' ', 'd', 'o', 'l', 'o', 'r', ' ', 's', 'i', 't', ' ',
				'a', 'm', 'e', 't', ',', ' ', 'c', 'o', 'n', 's', 'e', 'c', 't', 'e', 't', 'u', 'r', ' ', 'a', 'd', 'i', 'p', 'i', 's', 'c', 'i', 'n', 'g', ' ', 'e', 'l', 'i', 't', ',', ' ',
				's', 'e', 'd', ' ', 'd', 'o', ' ', 'e', 'i', 'u', 's', 'm', 'o', 'd', ' ', 't', 'e', 'm', 'p', 'o', 'r', ' ',
				'i', 'n', 'c', 'i', 'd', 'i', 'd', 'u', 'n', 't', ' ', 'u', 't', ' ', 'l', 'a', 'b', 'o', 'r', 'e', ' ', 'e', 't', ' ',
				'd', 'o', 'l', 'o', 'r', 'e', ' ', 'm', 'a', 'g', 'n', 'a', ' ', 'a', 'l', 'i', 'q', 'u', 'a', '.', ' ',
				'U', 't', ' ', 'e', 'n', 'i', 'm', ' ', 'a', 'd', ' ', 'm', 'i', 'n', 'i', 'm', ' ', 'v', 'e', 'n', 'i', 'a', 'm', ',', ' ',
				'q', 'u', 'i', 's', ' ', 'n', 'o', 's', 't', 'r', 'u', 'd', ' ', 'e', 'x', 'e', 'r', 'c', 'i', 't', 'a', 't', 'i', 'o', 'n', ' ',
				'u', 'l', 'l', 'a', 'm', 'c', 'o', ' ', 'l', 'a', 'b', 'o', 'r', 'i', 's', ' ', 'n', 'i', 's', 'i', ' ', 'u', 't', ' ', 'a', 'l', 'i', 'q', 'u', 'i', 'p', ' ', 'e', 'x', ' ', 'e', 'a', ' ',
				'c', 'o', 'm', 'm', 'o', 'd', 'o', ' ', 'c', 'o', 'n', 's', 'e', 'q', 'u', 'a', 't', '.', ' ', 'D', 'u', 'i', 's', ' ', 'a', 'u', 't', 'e', ' ',
				'i', 'r', 'u', 'r', 'e', ' ', 'd', 'o', 'l', 'o', 'r', ' ', 'i', 'n', ' ', 'r', 'e', 'p', 'r', 'e', 'h', 'e', 'n', 'd', 'e', 'r', 'i', 't', ' ',
				'i', 'n', ' ', 'v', 'o', 'l', 'u', 'p', 't', 'a', 't', 'e', ' ', 'v', 'e', 'l', 'i', 't', ' ', 'e', 's', 's', 'e', ' ', 'c', 'i', 'l', 'l', 'u', 'm', ' ',
				'd', 'o', 'l', 'o', 'r', 'e', ' ', 'e', 'u', ' ', 'f', 'u', 'g', 'i', 'a', 't', ' ', 'n', 'u', 'l', 'l', 'a', ' ', 'p', 'a', 'r', 'i', 'a', 't', 'u', 'r', '.', ' ',
				'E', 'x', 'c', 'e', 'p', 't', 'e', 'u', 'r', ' ', 's', 'i', 'n', 't', ' ', 'o', 'c', 'c', 'a', 'e', 'c', 'a', 't', ' ', 'c', 'u', 'p', 'i', 'd', 'a', 't', 'a', 't', ' ', 'n', 'o', 'n', ' ',
				'p', 'r', 'o', 'i', 'd', 'e', 'n', 't', ',', ' ', 's', 'u', 'n', 't', ' ', 'i', 'n', ' ', 'c', 'u', 'l', 'p', 'a', ' ', 'q', 'u', 'i', ' ', 'o', 'f', 'f', 'i', 'c', 'i', 'a', ' ',
				'd', 'e', 's', 'e', 'r', 'u', 'n', 't', ' ', 'm', 'o', 'l', 'l', 'i', 't', ' ', 'a', 'n', 'i', 'm', ' ', 'i', 'd', ' ', 'e', 's', 't', ' ', 'l', 'a', 'b', 'o', 'r', 'u', 'm', '.'
	};
	TEST_CLASS(GameCryptTest)
	{
	public:
		
		TEST_METHOD(SaveData)
		{
			GameCrypt::FileIO fileIO;
#ifdef WIN32
			Assert::IsTrue(fileIO.SaveFile(expectedData, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\Win32\\LoremIpsum.txt"));
#elif _WIN64													
			Assert::IsTrue(fileIO.SaveFile(expectedData, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\x64\\LoremIpsum.txt"));
#else
			Assert::Fail(L"Unsupported operating system");
#endif
		}
		TEST_METHOD(LoadData)
		{
			GameCrypt::FileIO fileIO;
			std::vector<unsigned char> data;
#ifdef WIN32
			Assert::IsTrue(fileIO.LoadFile(data, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\Win32\\LoremIpsum.txt"));
#elif _WIN64													
			Assert::IsTrue(fileIO.LoadFile(data, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\x64\\LoremIpsum.txt"));
#else
			Assert::Fail(L"Unsupported operating system");
#endif
		}
		TEST_METHOD(CompressData)
		{
			GameCrypt::Compressor compressor;
			std::vector<unsigned char> data = compressor.Compress(expectedData);
			Assert::AreNotEqual(data.size(), expectedData.size());
		}
		TEST_METHOD(DecompressData)
		{
			GameCrypt::Compressor compressor;
			std::vector<unsigned char> data = compressor.Compress(expectedData);
			Assert::AreNotEqual(data.size(), expectedData.size());
			std::vector<unsigned char> decompressed = compressor.Decompress(data);
			Assert::AreEqual(expectedData.size(), decompressed.size(), L"Data size does not match!");
			for (size_t i = 0; i < expectedData.size(); ++i)
				Assert::AreEqual(expectedData[i], decompressed[i]);
		}
		TEST_METHOD(EncryptAndSave)
		{
			GameCrypt::FileIO fileIO;
#ifdef WIN32
			Assert::IsTrue(fileIO.SaveToFileEncrypted(expectedData, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\Win32\\EncryptedData.bin"));
#elif _WIN64													
			Assert::IsTrue(fileIO.SaveToFileEncrypted(expectedData, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\x64\\EncryptedData.bin"));
#else
			Assert::Fail(L"Unsupported operating system");
#endif
		}

		TEST_METHOD(LoadAndDecrypt)
		{
			GameCrypt::FileIO fileIO;
			std::vector<unsigned char> actualData;
#ifdef WIN32
			Assert::IsTrue(fileIO.LoadEncryptedFile(actualData, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\Win32\\EncryptedData.bin"));
#elif _WIN64													
			Assert::IsTrue(fileIO.LoadEncryptedFile(actualData, L"F:\\Source\\Bachelor\\Game-sec\\EncryptedFiles\\x64\\EncryptedData.bin"));
#else
			Assert::Fail(L"Unsupported operating system");
#endif
			Assert::AreEqual(expectedData.size(), actualData.size(), L"Data size does not match!");
			for (size_t i = 0; i < expectedData.size(); ++i)
				Assert::AreEqual(expectedData[i], actualData[i]);
		}
	};
}
