#pragma once
#ifndef StringableObject_h__
#define StringableObject_h__
#include "NFEnginePCH.hpp"

namespace nfe
{
	class NIFRAME_DLL_EXPORT IStringableObject
	{
	public:

		virtual String ToString() const = 0;

	private:

	};
}

#endif // StringableObject_h__