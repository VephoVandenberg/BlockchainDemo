#pragma once

#include <forward_list>
#include <memory>
#include <mutex>

#include "block.hpp"

namespace Crypto
{
	struct Transaction;

	class Blockchain
	{
	public:
		Blockchain() = default;
		~Blockchain() = default;

		void addTransaction(const Transaction& transaction);
		void printBlockchain() const;

		double getBalance(const std::string& client) const;

		void calcTotalTransactions() const;

	private:
		std::forward_list<std::unique_ptr<Block>> m_chain;
		std::unique_ptr<Block> m_transactionPool = nullptr;

		// mutable std::mutex m_mutex;
	};
}

