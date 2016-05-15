//DON'T MOVE//
#define MAXNUMBERS 1000000
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
inline T nextNumber(char*& position, char* inputBuffer) 
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

uint32_t numbers[MAXNUMBERS];

void write(uint32_t* numbers, uint32_t count, std::string& filename)
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
	char* input = static_cast<char*>(malloc(MAXCHARACTERS * sizeof(char)));
	fread(input, sizeof(char), MAXCHARACTERS, stdin);
	char *it = input;
	uint32_t numberCount = toUnsignedIntegral<uint32_t, '\n'>(it);
	for (uint32_t i = 0; i < numberCount; ++i)
	{
		numbers[i] = toUnsignedIntegral<uint32_t, '\n'>(it);
	}
	return numberCount;
}

uint32_t readUsingCin()
{
	uint32_t numberCount;
	std::cin >> numberCount;
	for (uint32_t i = 0; i < numberCount; ++i)
	{
		std::cin >> numbers[i];
	}
	return numberCount;
}

uint32_t readUsingNextNumber()
{
	char input[1000];
	char* it = &input[1000];
	uint32_t numberCount = nextNumber<uint32_t, '\n', 1000>(it, input);
	for (uint32_t i = 0; i < numberCount; ++i)
	{
		numbers[i] = nextNumber<uint32_t, '\n', 1000>(it, input);
	}
	return numberCount;
}

void runTest(uint32_t (*function)(void), char* name)
{
	auto begin = std::chrono::high_resolution_clock::now();
	auto count = function();
	auto end = std::chrono::high_resolution_clock::now();
	auto deltaTimeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	std::cout << name << ":" << deltaTimeInMs << '\n';
	write(numbers, count, std::string("out_") + name);
	fseek(stdin, 0L, SEEK_SET);
	clearerr(stdin);
}

int main()
{
	runTest(&readUsingToUnsignedIntegral, "toUnsignedIntegral");
	runTest(&readUsingCin, "cin");
	runTest(&readUsingNextNumber, "nextNumber");

    return 0;
}