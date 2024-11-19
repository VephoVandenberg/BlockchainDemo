#include <iostream>
#include <chrono>

#include "block.hpp"
#include "blockchain.hpp"

using namespace Crypto;

constexpr size_t g_blockMaxSize = 4;

void Blockchain::addTransaction(const Transaction& transaction)
{
	if (m_transactionPool == nullptr)
	{
		m_transactionPool = std::make_unique<Block>();
		m_transactionPool->setTime(std::time(nullptr));
	}

 	m_transactionPool->addTransaction(transaction);
	
	if (m_transactionPool->getBlockSize() >= g_blockMaxSize)
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		m_chain.emplace_front(std::move(m_transactionPool));
	}
}

void Blockchain::printBlockchain() const
{
	for (const auto& block : m_chain)
	{
		std::cout << "===================" << '\n';
		block->printAllTrasnactions();
		std::cout << "===================" << '\n';
	}
}

double Blockchain::getBalance(const std::string& client) const
{
	double total = 0.0;
	for (const auto& block : m_chain)
	{
		for (const auto& transaction : block->getTransactions())
		{
			if (transaction.sender == client)
			{
				total -= transaction.amount;
			}
			else if (transaction.receiver == client)
			{
				total += transaction.amount;
			}
		}
	}

	return total;
}

void Blockchain::calcTotalTransactions() const
{
	double total = 0.0;
	size_t nTransactions = 0;
	for (const auto& block : m_chain)
	{
		nTransactions += block->getBlockSize();
		for (const auto& transaction : block->getTransactions())
		{
			total += transaction.amount;
		}
	}

	std::cout << "Total number of transactions: " << nTransactions << '\n'
		<< "And the total sum of currency: " << total << '\n';
}
