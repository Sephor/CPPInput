//DON'T MOVE//
#define MAXNUMBERS 100000
#define MAXDIGITS 10
#define MAXCHARACTERS MAXNUMBERS * MAXDIGITS + MAXDIGITS
//////////////

#include <iostream>
#include <fstream>
#include <chrono>

template<typename T, char Delimiter>
inline T toUnsignedIntegral(char*& position) 
{
	T result = 0;
	while (*position != Delimiter)
	{
		result *= 10;
		result += *position - 48;
		++position;
	}
	++position;
	return result;
}

template<typename T, char Delimiter, size_t Buffersize>
inline T nextNumber(char*& position, char*& inputBuffer) 
{
	T result = 0;
	while (*position != Delimiter)
	{
		if (position == &inputBuffer[Buffersize])
		{
			position = inputBuffer;
			fread(inputBuffer, sizeof(char), Buffersize, stdin);
		}
		result *= 10;
		result += *position - 48;
		++position;
	}
	++position;
	return result;
}


//Code for Testing
char input[MAXCHARACTERS];
uint32_t numbers[MAXNUMBERS];

void write(uint32_t* numbers, uint32_t count, char* filename)
{
	std::ofstream output(filename);
	output << count << '\n';
	for (uint32_t i = 0; i < count; ++i)
	{
		output << numbers[i] << '\n';
	}
	output.close();
}

uint32_t readUsingToUnsignedIntegral()
{
	fread(input, sizeof(char), MAXCHARACTERS, stdin);
	char *it = input;
	uint32_t numberCount = toUnsignedIntegral<uint32_t, '\n'>(it);
	for (uint32_t i = 0; i < numberCount; ++i)
	{
		numbers[i] = toUnsignedIntegral<uint32_t, '\n'>(it);
	}
	return numberCount;
}

int main()
{
	auto begin = std::chrono::high_resolution_clock::now();
	auto count = readUsingToUnsignedIntegral();
	auto end = std::chrono::high_resolution_clock::now();
	auto deltaTimeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << "toUnsignedIntegral:" << deltaTimeInMs << '\n';
	write(numbers, count, "out_toUnsignedIntegral");

    return 0;
}