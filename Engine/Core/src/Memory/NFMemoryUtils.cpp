#include "NFEnginePCH.hpp"
#include "Memory/NFMemoryUtils.hpp"


using namespace nfe;

void nfe::MemZero(void* InAddress, NFSize Size)
{
	if (!InAddress)
	{
		return;
	}
	NFSize Position = 0;
	for (uint8* Address = static_cast<uint8*>(InAddress); Position < Size; ++Position)
	{
		*Address = 0;
		++Address;
	}
}
