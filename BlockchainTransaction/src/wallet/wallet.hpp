#pragma once

#include <unordered_map>
#include <memory>
#include <mutex>

/*
	Blockchain
	digitial signatures
	decentralize
	proof of work
	Ledger
	Crypto wallet
*/

namespace Crypto
{
	class Blockchain;
	class Transaction;

	class Wallet
	{
	public:
		Wallet(const std::shared_ptr<Blockchain>& blockchain);
		~Wallet() = default;

		void updateBalance();
		void sendTransaction(const std::string& receiver, const double amount);

		double getBalance();
		inline std::string getPublicKey() const { return m_publicKey; }

	private:
		double m_balance = 0.0;

		std::shared_ptr<Blockchain> m_blockchain = nullptr;
#if 1
		std::string m_privateKey;
		std::string m_publicKey;
		
		std::string signTransaction(const Transaction& transaction);
#endif
	};
} 