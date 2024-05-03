#include <iostream>
#include <cstdlib> // Include this to use srand and rand functions

void stream_cipher(std::string &text, unsigned int key);
int main();

void stream_cipher(std::string &text, unsigned int key)
{
	// Use the 'key' to seed the random number generator
	srand(key);

	// XOR each character in the string with the next random number
	for (size_t k = 0; k < text.length(); ++k) // Corrected the for loop syntax
	{
		text[k] ^= static_cast<char>(rand()); // Use static_cast for type conversion
	}
}

int main()
{
	std::string msg = "Meet me tonight."; // Corrected the string declaration

	std::cout << msg << std::endl;
	stream_cipher(msg, 5235395);
	std::cout << msg << std::endl;
	stream_cipher(msg, 5235395);
	std::cout << msg << std::endl;

	return 0;
}
