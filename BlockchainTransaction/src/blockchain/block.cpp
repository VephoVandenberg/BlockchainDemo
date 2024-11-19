#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "block.hpp"

using namespace Crypto;

Transaction::Transaction(const std::string& sender_, const std::string& receiver_, const double amount_)
	: sender(sender_)
	, receiver(receiver_)
	, amount(amount_)
	, timestamp(std::time(nullptr))
{}

void Transaction::printTransaction() const
{
	std::cout << "Sender: " << sender << "\n"
		<< "Receiver: " << receiver << "\n"
		<< "Amount: " << amount << "TON\n"
		<< "Timestamp: " << std::ctime(&timestamp) << "\n";
}

void Block::addTransaction(const Transaction& transaction)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (!m_transactions.empty() &&
		transaction.timestamp < m_transactions.back().timestamp)
	{
		std::cout << "ERROR::Transaction from " << transaction.sender << " is invalid." << '\n';
		return;
	}
	m_transactions.push_back(transaction);
}

void Block::printAllTrasnactions() const
{
	std::lock_guard<std::mutex> lock(m_mutex);
	std::cout << "Creation time: " << std::ctime(&m_timestamp) << '\n';
	for (const auto& transaction : m_transactions)
	{
		transaction.printTransaction();
		std::cout << "--------------------" << "\n";
	}
}

double Block::getTotalSum() const 
{
	double total = 0;
	std::lock_guard<std::mutex> lock(m_mutex);
	for (const auto& transaction : m_transactions)
	{
		total += transaction.amount;
	}

	return total;
}