#include <iostream>
#include <ctime>

#include "../utils.hpp"

#include "../blockchain/block.hpp"
#include "../blockchain/blockchain.hpp"
#include "../wallet/wallet.hpp"

using namespace Crypto;

constexpr double g_minBalance = 1.0;

Wallet::Wallet(const std::shared_ptr<Blockchain>& blockchain)
	: m_blockchain(blockchain)
	, m_privateKey(Utils::generatePrivateKey())
	, m_publicKey(Utils::generatePublicKey(m_privateKey))
{}

void Wallet::updateBalance()
{
	double total = m_blockchain->getBalance(m_publicKey);
	
	if (total < 0.0f)
	{
		std::cout << "ERROR::Your balance is somehow negative. Fund your account" << '\n';
		return;
	}

	m_balance = total;
}

double Wallet::getBalance()
{
	updateBalance();
	return m_balance;
}

void Wallet::sendTransaction(const std::string& receiver, const double amount)
{
	m_balance = m_blockchain->getBalance(m_publicKey);
	if (m_balance - amount <= g_minBalance)
	{
		std::cout << "ERROR::Fund your balance, to make a transaction." << '\n';
		return;
	}

	m_balance -= amount;
	m_blockchain->addTransaction(Transaction(m_publicKey, receiver, amount));
}

std::string Wallet::signTransaction(const Transaction& transaction)
{
	std::string header = std::to_string(transaction.amount) + transaction.sender + transaction.receiver;
	return Utils::getHash(m_privateKey + header);
}
