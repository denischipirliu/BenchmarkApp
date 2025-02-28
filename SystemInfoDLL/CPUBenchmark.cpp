#include "pch.h"
#include "CPUBenchmark.h"
#include "openssl/evp.h"
#include "openssl/rand.h"
#include "openssl/blowfish.h"
#include <iostream>
#include <chrono>
#include <cstring>
#include <thread>
#include <vector>
#include <windows.h>
#include "blowfish.h"

const int FILE_SIZE_AES = 50 * 1024 * 1024; // 50 MB
const int FILE_SIZE_BLOWFISH = 1 * 1024 * 1024; // 1 MB
const int AES_REFERENCE_TIME = 100; // 100 milliseconds
const int BLOWFISH_REFERENCE_TIME = 200; // 200 milliseconds

// Function to perform AES encryption using EVP API
void aesEncrypt(const unsigned char* plaintext, int plaintext_len, unsigned char* key,
	unsigned char* iv, unsigned char* ciphertext)
{
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL) {
		// Handle error (memory allocation failed)
		std::cerr << "Error initializing EVP context" << std::endl;
		return;
	}

	// Initialize the encryption operation using 256-bit AES in CFB mode
	if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, key, iv)) {
		// Handle error (initialization failed)
		std::cerr << "Error initializing encryption" << std::endl;
		EVP_CIPHER_CTX_free(ctx);
		return;
	}

	int len;
	if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
		// Handle error (encryption failed)
		std::cerr << "Error during encryption" << std::endl;
		EVP_CIPHER_CTX_free(ctx);
		return;
	}

	int ciphertext_len = len;

	if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
		// Handle error (finalizing encryption failed)
		std::cerr << "Error finalizing encryption" << std::endl;
		EVP_CIPHER_CTX_free(ctx);
		return;
	}
	ciphertext_len += len;

	EVP_CIPHER_CTX_free(ctx); // Clean up
}

// Function to perform AES decryption using EVP API
void aesDecrypt(const unsigned char* ciphertext, int ciphertext_len, unsigned char* key,
	unsigned char* iv, unsigned char* plaintext)
{
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL) {
		// Handle error (memory allocation failed)
		std::cerr << "Error initializing EVP context" << std::endl;
		return;
	}

	// Initialize the decryption operation using 256-bit AES in CFB mode
	if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, key, iv)) {
		// Handle error (initialization failed)
		std::cerr << "Error initializing decryption" << std::endl;
		EVP_CIPHER_CTX_free(ctx);
		return;
	}

	int len;
	if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
		// Handle error (decryption failed)
		std::cerr << "Error during decryption" << std::endl;
		EVP_CIPHER_CTX_free(ctx);
		return;
	}

	int plaintext_len = len;

	if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
		// Handle error (finalizing decryption failed)
		std::cerr << "Error finalizing decryption" << std::endl;
		EVP_CIPHER_CTX_free(ctx);
		return;
	}
	plaintext_len += len;

	EVP_CIPHER_CTX_free(ctx); // Clean up
}

// Function to generate random data for encryption
void generateRandomData(unsigned char* data, int len)
{
	RAND_bytes(data, len);
}

// Function to benchmark the encryption and decryption speed of AES
int aesBenchmark()
{
	unsigned char key[32]; // 256-bit key
	unsigned char iv[16]; // 128-bit IV
	unsigned char* plaintext = new unsigned char[FILE_SIZE_AES]; // 50 MB plaintext
	unsigned char* ciphertext = new unsigned char[FILE_SIZE_AES]; // 50 MB ciphertext

	generateRandomData(key, 32);
	generateRandomData(iv, 16);
	generateRandomData(plaintext, FILE_SIZE_AES);

	auto start = std::chrono::high_resolution_clock::now();
	aesEncrypt(plaintext, FILE_SIZE_AES, key, iv, ciphertext);
	aesDecrypt(ciphertext, FILE_SIZE_AES, key, iv, plaintext);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = end - start;
	delete[] plaintext;
	delete[] ciphertext;
	return static_cast<int>(elapsed.count() * 1000); // Return time in milliseconds
}



// Function to benchmark the encryption and decryption speed of Blowfish
int blowfishBenchmark()
{
	blf_ctx ctx;
	unsigned char key[56]; // 448-bit key
	unsigned char* plaintext = new unsigned char[FILE_SIZE_BLOWFISH]; // 1 MB plaintext
	unsigned char* ciphertext = new unsigned char[FILE_SIZE_BLOWFISH]; // 1 MB ciphertext
	
	generateRandomData(key, 56);
	generateRandomData(plaintext, FILE_SIZE_BLOWFISH);

	blf_key(&ctx,(char*) key, 56);

	auto start = std::chrono::high_resolution_clock::now();
	Blowfish_ECB_encrypt(&ctx, plaintext, ciphertext, FILE_SIZE_BLOWFISH);
	Blowfish_ECB_decrypt(&ctx, ciphertext, plaintext, FILE_SIZE_BLOWFISH);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = end - start;
	delete[] plaintext;
	delete[] ciphertext;
	return static_cast<int>(elapsed.count() * 1000); // Return time in milliseconds
}

void setThreadAffinity(int coreId) {
	// Set the affinity mask so the thread runs on the specified core
	DWORD_PTR affinityMask = 1 << coreId;
	SetThreadAffinityMask(GetCurrentThread(), affinityMask);
}

int scoreCalculator(int aesTime, int blowfishTime) 
{
	int aesScore = (AES_REFERENCE_TIME * 100) / aesTime;
	int blowfishScore = (BLOWFISH_REFERENCE_TIME * 100) / blowfishTime;
	return (aesScore + blowfishScore) / 2;

}

int runBenchmark()
{
	int numIterations = 100;
	int aesBenchmarkTime = 0, blowfishBenchmarkTime = 0;
	for (int i = 0; i < numIterations; ++i) {
		aesBenchmarkTime += aesBenchmark();
		blowfishBenchmarkTime += blowfishBenchmark();
	}
	int avgAESTime = aesBenchmarkTime / numIterations;
	int avgBlowfishTime = blowfishBenchmarkTime / numIterations;
	int score = scoreCalculator(avgAESTime, avgBlowfishTime);
	return score;

}

// Function to get the single core benchmark data for encryption and decryption
extern "C" int getSingleCoreCPUBenchmark()
{
	setThreadAffinity(0);
	return runBenchmark();
}

//Function to get the multi-core benchmark data for encryption and decryption
extern "C" int getMultiCoreCPUBenchmark()
{
	std::vector<std::thread> threads;
	int numCores = std::thread::hardware_concurrency();
	std::vector<int> threadScores(numCores);
	int totalScore = 0;

	for (int i = 0; i < numCores; ++i) {
		threads.emplace_back([i, &threadScores]() {
			setThreadAffinity(i);
			threadScores[i] = runBenchmark();
			}
		);
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	
	for (int score : threadScores) {
		totalScore += score;
	}

	return totalScore;
}
