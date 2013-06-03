#pragma once
#ifndef NiFrameReferenceCounted_h__
#define NiFrameReferenceCounted_h__

#include "NiFrameEnginePCH.hpp"

namespace NiFrame
{
	template< typename T >
	class ReferenceCounted
	{
	public:
		ReferenceCounted( void );
		ReferenceCounted( T* pointer );
		ReferenceCounted( const ReferenceCounted< T > & refCount );
		ReferenceCounted( ReferenceCounted< T >&& refCount );
		~ReferenceCounted();
		

		ReferenceCounted< T >& operator =( const ReferenceCounted< T >& refCount );
		ReferenceCounted< T >& operator =( ReferenceCounted< T >&& refCount );

		T* operator ->();

		T* operator *();

	private:
		
		void IncRef( void );

		void DecRef( void );

		T* m_CountedPointer;

		uint32* m_Count;

	};

	template< typename T >
	NiFrame::ReferenceCounted<T>::ReferenceCounted( void ):
		m_CountedPointer( nullptr ),
		m_Count( new uint32( 1 ) )
	{

	}

	template< typename T >
	NiFrame::ReferenceCounted<T>::ReferenceCounted( ReferenceCounted< T >&& refCount ) :
		m_CountedPointer( refCount.m_CountedPointer ),
		m_Count( refCount.m_Count )
	{
		refCount.m_CountedPointer = nullptr;
		m_Count = nullptr;
	}

	template< typename T >
	NiFrame::ReferenceCounted<T>::~ReferenceCounted()
	{
		DecRef();
	}

	template< typename T >
	NiFrame::ReferenceCounted<T>::ReferenceCounted( const ReferenceCounted< T >& refCount )
	{
		//DecRef();

		//this = &refCount;
		m_Count = refCount.m_Count;
		m_CountedPointer = refCount.m_CountedPointer;

		IncRef();

	}

	template< typename T >
	NiFrame::ReferenceCounted<T>::ReferenceCounted( T* pointer ) :
		m_CountedPointer( pointer ),
		m_Count( new uint32( 1 ) )
	{
	}

	template< typename T >
	T* NiFrame::ReferenceCounted<T>::operator*()
	{
		return m_CountedPointer;
	}

	template< typename T >
	T* NiFrame::ReferenceCounted<T>::operator->()
	{
		return m_CountedPointer;
	}

	template< typename T >
	ReferenceCounted< T >& NiFrame::ReferenceCounted<T>::operator=( ReferenceCounted< T >&& refCount )
	{
		if ( this != &refCount )
		{
			DecRef();
			m_CountedPointer = refCount.m_CountedPointer;
			m_Count = refCount.m_Count;

			refCount.m_CountedPointer = nullptr;
			refCount.m_Count = nullptr;
		}

		return *this;

	}

	template< typename T >
	ReferenceCounted< T >& NiFrame::ReferenceCounted<T>::operator=( const ReferenceCounted< T >& refCount )
	{
		if ( m_Count != refCount.m_Count )
		{
			m_CountedPointer = refCount.m_CountedPointer;
			
			m_Count = refCount.m_Count;
			
			IncRef();
		}

		return *this;
	}

	template< typename T >
	void NiFrame::ReferenceCounted<T>::DecRef( void )
	{
		if ( (* m_Count ) > 1 )
		{
			--(* m_Count);
		}
		else
		{
			SAFE_DELETE( m_CountedPointer )
			SAFE_DELETE( m_Count )
		}
	}

	template< typename T >
	void NiFrame::ReferenceCounted<T>::IncRef( void )
	{
		if ( ( *m_Count ) > 0 )
		{
			++( *m_Count );
		}
	}

}

#endif // NiFrameReferenceCounted_h__
