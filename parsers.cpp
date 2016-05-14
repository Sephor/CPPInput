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

uint32_t numbers[MAXNUMBERS];
int main()
{
	std::ios::sync_with_stdio(false);

	uint32_t numberCount;
	std::cin >> numberCount;
	for (uint32_t i = 0; i < numberCount; ++i)
	{
		std::cin >> numbers[i];
	}

    return 0;
}