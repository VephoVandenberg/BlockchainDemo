#include <iostream>

#include "src/blockchain/blockchain.hpp"
#include "src/wallet/wallet.hpp"

#include <SHA256.hpp>

/*TRY SCAVANGERS SHOW*/

int main(int argc, char** argv)
{
	std::shared_ptr<Crypto::Blockchain> blockchain = std::make_shared<Crypto::Blockchain>();

	Crypto::Wallet satoshi(blockchain);
	// Genesis block
	{
		blockchain->addTransaction(Crypto::Transaction("", satoshi.getPublicKey(), 100));
		blockchain->addTransaction(Crypto::Transaction("", satoshi.getPublicKey(), 100));
		blockchain->addTransaction(Crypto::Transaction("", satoshi.getPublicKey(), 100));
		blockchain->addTransaction(Crypto::Transaction("", satoshi.getPublicKey(), 100));
	}
	
	std::cout << satoshi.getBalance() << '\n';

	blockchain->printBlockchain();

	Crypto::Wallet w1(blockchain);
	Crypto::Wallet w2(blockchain);
	Crypto::Wallet w3(blockchain);

	satoshi.sendTransaction(w2.getPublicKey(), 10);
	satoshi.sendTransaction(w3.getPublicKey(), 20);
	satoshi.sendTransaction(w1.getPublicKey(), 10);
	satoshi.sendTransaction(w1.getPublicKey(), 100);

	blockchain->printBlockchain();

	std::cout << satoshi.getBalance() << '\n';


	return 0;
}
