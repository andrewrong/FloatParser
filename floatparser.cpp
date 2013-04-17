#include <iostream>
#include <cmath>
float FloatParser(float value,int mantissaNum,int expNum)
{
    float* fPtr = &value;
    int* iPtr = reinterpret_cast<int*>(fPtr);
    
    int floatToInt = *iPtr;
    int exp = 0;

    {
	for(int i = mantissaNum; i < (mantissaNum + expNum); i++)
	{
	    int tmp = (floatToInt >> i) & (0x00000001);

	    if(tmp)
	    {
		exp += std::pow(2,i - mantissaNum);
	    }
	}
    }

    int signal = 1;

    {
	int tmp = (floatToInt >> 31) & (0x00000001);

	if(tmp)
	{
	    signal = -1;
	}
    }

    float decimal = 0;

    for(int i = 0; i < mantissaNum; i++)
    {
	int tmp = (floatToInt >> i) & (0x00000001);
	
	if(tmp)
	    decimal += std::pow(2,(-mantissaNum + i + (exp - 127)));
    }

    return (std::pow(2,exp - 127) + decimal) * signal;
}

int main()
{
    float tmp = 1.2348;

    std::cout << FloatParser(tmp,23,8) << std::endl;;

    return 0;
}
