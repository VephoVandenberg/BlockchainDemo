#include <memory>
#include <random>

#include <SHA256.hpp>

#include "utils.hpp"

static std::unique_ptr<SHA256> s_sha = nullptr;

const std::string g_secretKeyword = "HYDRA DOMINATUS";

std::string Crypto::Utils::getHash(const std::string& data)
{
	if (s_sha == nullptr)
	{
		s_sha = std::make_unique<SHA256>();
	}

	s_sha->update(data);
	return s_sha->toString(s_sha->digest());
}

std::string Crypto::Utils::generatePrivateKey()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<size_t> distribution(0, SIZE_MAX);

	std::string privateKey;
	for (size_t i = 0; i < 8; i++)
	{
		privateKey += std::to_string(distribution(generator));
	}
	return getHash(privateKey);
}

std::string Crypto::Utils::generatePublicKey(const std::string& privateKey)
{
	return getHash(g_secretKeyword + privateKey);
}
