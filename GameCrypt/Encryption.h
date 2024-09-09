#pragma once
namespace GameCrypt
{
	class Encryption
	{
	public:
		CharV Encrypt(CharV& inVec);
		CharV Decrypt(CharV& inVec);
	};
}
