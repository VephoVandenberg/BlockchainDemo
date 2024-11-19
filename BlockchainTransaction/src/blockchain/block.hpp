#pragma once
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <mutex>

namespace Crypto
{
	struct Transaction
	{
		std::string sender;
		std::string receiver;
		double amount;
		time_t timestamp;

		Transaction(const std::string& sender, const std::string& receiver, const double amount);

		void printTransaction() const;
	};

	class Block
	{
	public:
		Block() = default;
		~Block() = default;

		void addTransaction(const Transaction& transaction);
		void printAllTrasnactions() const;

		inline void setTime(const time_t& timestamp) { m_timestamp = timestamp; }
		inline size_t getBlockSize() const { return m_transactions.size(); }
		inline const auto& getTransactions() const { return m_transactions; }
		
		double getTotalSum() const;

	private:
		std::vector<Transaction> m_transactions;

		time_t m_timestamp;

		mutable std::mutex m_mutex;
	};
}