#include "pch.h"
#include "BruteForceGenerator.h"


BruteForceGenerator::BruteForceGenerator(int password_size) { 
	lenght = password_size;
	internal_pointers = new std::bitset<7>[password_size];
}

BruteForceGenerator::~BruteForceGenerator() {
	delete[] internal_pointers;
}

void BruteForceGenerator::increment_pointer(int index) {
	
	for (size_t i = 0; i < 7; ++i) {
		if (internal_pointers[index][i] == 0) {
			for (int j = 0; j <= i; ++j) {
				internal_pointers[index][j].flip();
			}
			break;
		}
	} //set character to starting character and increment upper char pointer
	if (internal_pointers[index].to_ulong() >= char_count) {
		internal_pointers[index].reset();
		increment_pointer(index - 1);
	}
}

void BruteForceGenerator::set_password_candidate(char *candidate) {
	//char* candidate_temp = new char[lenght+1];
	for (int i = 0; i < lenght; ++i) {
		candidate[i] = letters[(uint8_t)internal_pointers[i].to_ulong()];
	}
	candidate[lenght] = '\0';
	increment_pointer(lenght - 1);
}

void BruteForceGenerator::set_start_value(int value, int pointer_index) {
	int temp_value = 64;
	for (int i = pointer_size - 1; i >= 0; ) {
		if (value >= temp_value) {
			internal_pointers[pointer_index].set(i);
			value -= temp_value;
		} else {
			internal_pointers[pointer_index].reset(i);
		}
		temp_value = (int)pow(2, --i);
	}
}
//prepaired for use in MT version
void BruteForceGenerator::set_end_value(int value, int pointer_index) {
}

//void BruteForceGenerator::generate_candidates(char *candidates, int password_length, int size) {
//	char *input_string = new char[password_length + 1];
//
//	
//
//
//
//}

