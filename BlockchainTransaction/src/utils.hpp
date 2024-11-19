#pragma once

#include <string>

namespace Crypto
{
	namespace Utils
	{
		std::string getHash(const std::string& hash);

		std::string generatePrivateKey();
		std::string generatePublicKey(const std::string& privateKey);
	}
}