//DON'T MOVE//
#define MAXNUMBERS 1000000
#define MAXDIGITS 10
#define MAXCHARACTERS MAXNUMBERS * MAXDIGITS + MAXDIGITS
//////////////

#include <iostream>

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

char input[MAXCHARACTERS];
uint32_t numbers[MAXNUMBERS];
int main()
{
	uint32_t charCount = fread(input, sizeof(char), MAXCHARACTERS, stdin);

	char *it = input;
	uint32_t numberCount = toUnsignedIntegral<uint32_t, '\n'>(it);
	for (uint32_t i = 0; i < numberCount; ++i)
	{
		numbers[i] = toUnsignedIntegral<uint32_t, '\n'>(it);
	}

    return 0;
}