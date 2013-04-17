#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iterator>

using namespace std;
template<class F>
F FloatParser(F value,int mantissaNum,int expNum)
{
    F* fPtr = &value;
    
    if(sizeof(F) < sizeof(int))
    {
	std::cout << " 不受理小于32bits的浮点数" << std::endl;	
	exit(-1);	
    }

    const int intNum = sizeof(F) / sizeof(int);
    int** iPtr = new int*[intNum];
    iPtr[0] = reinterpret_cast<int*>(fPtr); 

    for(int i = 0; i < intNum; i++)
    {
	iPtr[i] = iPtr[0] + i;
    }
    
    char* bitMap = new char[sizeof(F) * 8];

    for(int i = 0; i < intNum; i++)
    {
	for(int j = 0; j < sizeof(int) * 8; j++)
	{
	    if(((*iPtr[i]) >> j) & (0x00000001))
	    {
		bitMap[i*sizeof(int)*8+j] = 1;
	    }
	    else
	    {
		bitMap[i*sizeof(int)*8+j] = 0;
	    }
	}
    }

    int exp = 0;
    for(int i = mantissaNum;i < (mantissaNum + expNum); i++)
    {
	if(bitMap[i])
	{
	    exp += (std::pow(2,i - mantissaNum));
	}
    }

    int signal = 1;
    const int expDifference = std::pow(2,(expNum - 1)) - 1;
    F decimal = 0;

    for(int i = 0; i < mantissaNum; i++)
    {
	if(bitMap[i])
	{
	    decimal += std::pow(2,(-mantissaNum + i + exp - expDifference));
	}
    }
    
    if(bitMap[63])
    {
	signal = -1;
    }

    delete[] iPtr;
    delete[] bitMap;

    return (std::pow(2,(exp - expDifference)) + decimal) * signal;
}

int main()
{
    double tmp = 1.2348;
    std::cout << FloatParser(tmp,52,11) << std::endl;;
    return 0;
}
