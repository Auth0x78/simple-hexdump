#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdint>

#define ERROR_EXIT(MSG, EXIT_CODE) { std::cerr << MSG << std::endl; exit(EXIT_CODE); }

int main(int argc, char* argv[])
{
	// Define BYTES_PER_ROW
	uint8_t BYTES_PER_ROW = 16;

	// Check if enough arguments were given.
	if (argc < 2)
		ERROR_EXIT("Error: No filepath given.", -1);
	if (argc == 3) {
		// Update BYTES_PER_ROW based on the optional second argument, with boundaries.
		int temp = atoi(argv[2]);
		BYTES_PER_ROW = temp < 32 ? (temp > 0 ? temp : 16) : 32;
	}

	// Open file in binary read mode
	std::ifstream file;
	file = std::ifstream(argv[1], std::ios_base::binary | std::ios_base::in);

	// Check if file failed to open.
	if (file.fail())
		ERROR_EXIT("Error: Failed to open file.", -1);

	// Calculate the file size
	file.seekg(0, std::ios::end);
	uint64_t fsize = file.tellg();

	// Reset file pointer to start of file
	file.seekg(0, std::ios::beg);

	// Allocate buffer to read BYTES_PER_ROW bytes at a time
	char* buffer = (char*)calloc(BYTES_PER_ROW, sizeof(char));
	if (buffer == nullptr)
		ERROR_EXIT("Failed to allocate buffer.", -1);

	std::cout << "Hexdump of file: " << argv[1] << std::endl << "Size of file: " << fsize / 1024 << "KB" << std::endl;

	// Read the first BYTES_PER_ROW bytes of the file
	file.read(buffer, BYTES_PER_ROW);
	if (file.gcount() == 0)
		ERROR_EXIT("Error: File is empty", -1);

	// Initial Header print
	printf("%10s", "");
	for (int i = 0; i < BYTES_PER_ROW; i++)
		printf("%02X ", i);
	printf(" Decoded Text");
	printf("\n");

	uint64_t address = 0x0;
	while (!file.fail())
	{
		// Print offset
		printf("%08llX  ", address);
		// Print hex values
		for (int i = 0; i < std::min((size_t)BYTES_PER_ROW, (size_t)file.gcount()); i++)
			printf("%02X ", buffer[i] & 0xff);

		// Print the decoded text values
		printf(" ");
		for (int i = 0; i < std::min((size_t)BYTES_PER_ROW, (size_t)file.gcount()); i++) {
			if (buffer[i] < 127 && buffer[i] > 32)
				printf("%c ", buffer[i]);
			else
				printf(". ");
		}

		// Print new line at the end of the row
		printf("\n");

		// Update address and read the next BYTES_PER_ROW bytes
		address += BYTES_PER_ROW;
		file.read(buffer, BYTES_PER_ROW);
	}

	//Free the buffer
	free(buffer);

	//Close the file
	file.close();

	return EXIT_SUCCESS;
}
