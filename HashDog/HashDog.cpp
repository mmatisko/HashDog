// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BruteForceGenerator.h"
#include "Md5Hash.h"
#include "Utility.h"
#include "Attacker.h"

using namespace std;
using namespace std::chrono;

const short PASSWORD_LENGTH = 4;
const Attacker::attacked_hash HASH = Attacker::attacked_hash::md5;
const Attacker::attack_mode ATTACK = Attacker::attack_mode::brute_force;


int main() {
	int main_index = 0; //
	srand(time(NULL));
	
	Attacker *black_hat = new Attacker(4);

	char* searched_string = new char[PASSWORD_LENGTH + 1];
	unsigned char* searched_digest = new unsigned char[HASH + 1];
	Utility::generateRandomPassword(searched_string, PASSWORD_LENGTH);
	//memcpy(searched_string, "Op1ca!", HASH + 1);
	cout << "Searching for password: " << searched_string << endl;
	Md5Hash *md5_hash = new Md5Hash();
	md5_hash->hash_message(searched_string, searched_digest);

	//ATTACK with stopwatch! 
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	black_hat->perform_attack(PASSWORD_LENGTH, ATTACK, HASH, searched_digest);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	black_hat->print_proof();

	long duration = duration_cast<milliseconds>(t2 - t1).count();
	Utility::printHumanTime(duration);
}