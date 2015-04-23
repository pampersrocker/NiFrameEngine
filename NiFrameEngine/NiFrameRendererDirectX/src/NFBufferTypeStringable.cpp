#include "NFRendererPCH.hpp"
#include "NFBufferTypeStringable.hpp"

#define StringifyEnum( name ) # name


namespace nfe
{
	map< D3DFORMAT, String>::type* BufferTypeStringable::D3DFormatToStringMap = PopulateMap();

	BufferTypeStringable::BufferTypeStringable(const _D3DFORMAT& format) :
		m_Format( format )
	{
	}


	BufferTypeStringable::~BufferTypeStringable(void)
	{
	}

	String BufferTypeStringable::ToString() const
	{
		return (*D3DFormatToStringMap)[ m_Format ];
	} 

	map< D3DFORMAT, String >::type* BufferTypeStringable::PopulateMap()
	{
		map< D3DFORMAT, String >::type* bufferMap = new map< D3DFORMAT, String >::type();

		(*bufferMap)[ D3DFMT_R8G8B8 ] = StringifyEnum( D3DFMT_R8G8B8 );          
		(*bufferMap)[ D3DFMT_A8R8G8B8 ] = StringifyEnum( D3DFMT_A8R8G8B8 );
		(*bufferMap)[ D3DFMT_X8R8G8B8 ] = StringifyEnum( D3DFMT_X8R8G8B8 );
		(*bufferMap)[ D3DFMT_R5G6B5 ] = StringifyEnum( D3DFMT_R5G6B5 );
		(*bufferMap)[ D3DFMT_X1R5G5B5 ] = StringifyEnum( D3DFMT_X1R5G5B5 );
		(*bufferMap)[ D3DFMT_A1R5G5B5 ] = StringifyEnum( D3DFMT_A1R5G5B5 );
		(*bufferMap)[ D3DFMT_A4R4G4B4 ] = StringifyEnum( D3DFMT_A4R4G4B4 );
		(*bufferMap)[ D3DFMT_R3G3B2 ] = StringifyEnum( D3DFMT_R3G3B2 );
		(*bufferMap)[ D3DFMT_A8 ] = StringifyEnum( D3DFMT_A8 );
		(*bufferMap)[ D3DFMT_A8R3G3B2 ] = StringifyEnum( D3DFMT_A8R3G3B2 );
		(*bufferMap)[ D3DFMT_X4R4G4B4 ] = StringifyEnum( D3DFMT_X4R4G4B4 );
		(*bufferMap)[ D3DFMT_A2B10G10R10 ] = StringifyEnum( D3DFMT_A2B10G10R10 );
		(*bufferMap)[ D3DFMT_A8B8G8R8 ] = StringifyEnum( D3DFMT_A8B8G8R8 );
		(*bufferMap)[ D3DFMT_X8B8G8R8 ] = StringifyEnum( D3DFMT_X8B8G8R8 );
		(*bufferMap)[ D3DFMT_G16R16 ] = StringifyEnum( D3DFMT_G16R16 );
		(*bufferMap)[ D3DFMT_A2R10G10B10 ] = StringifyEnum( D3DFMT_A2R10G10B10 );
		(*bufferMap)[ D3DFMT_A16B16G16R16 ] = StringifyEnum( D3DFMT_A16B16G16R16 );
		(*bufferMap)[ D3DFMT_A8P8 ] = StringifyEnum( D3DFMT_A8P8 );
		(*bufferMap)[ D3DFMT_P8 ] = StringifyEnum( D3DFMT_P8 );
		(*bufferMap)[ D3DFMT_L8 ] = StringifyEnum( D3DFMT_L8 );
		(*bufferMap)[ D3DFMT_A8L8 ] = StringifyEnum( D3DFMT_A8L8 );
		(*bufferMap)[ D3DFMT_A4L4 ] = StringifyEnum( D3DFMT_A4L4 );
		(*bufferMap)[ D3DFMT_V8U8 ] = StringifyEnum( D3DFMT_V8U8 );
		(*bufferMap)[ D3DFMT_L6V5U5 ] = StringifyEnum( D3DFMT_L6V5U5 );
		(*bufferMap)[ D3DFMT_X8L8V8U8 ] = StringifyEnum( D3DFMT_X8L8V8U8 );
		(*bufferMap)[ D3DFMT_Q8W8V8U8 ] = StringifyEnum( D3DFMT_Q8W8V8U8 );
		(*bufferMap)[ D3DFMT_V16U16 ] = StringifyEnum( D3DFMT_V16U16 );
		(*bufferMap)[ D3DFMT_A2W10V10U10 ] = StringifyEnum( D3DFMT_A2W10V10U10 );
		(*bufferMap)[ D3DFMT_UYVY ] = StringifyEnum( D3DFMT_UYVY );
		(*bufferMap)[ D3DFMT_R8G8_B8G8 ] = StringifyEnum( D3DFMT_R8G8_B8G8 );
		(*bufferMap)[ D3DFMT_YUY2 ] = StringifyEnum( D3DFMT_YUY2 );
		(*bufferMap)[ D3DFMT_G8R8_G8B8 ] = StringifyEnum( D3DFMT_G8R8_G8B8 );
		(*bufferMap)[ D3DFMT_DXT1 ] = StringifyEnum( D3DFMT_DXT1 );
		(*bufferMap)[ D3DFMT_DXT2 ] = StringifyEnum( D3DFMT_DXT2 );
		(*bufferMap)[ D3DFMT_DXT3 ] = StringifyEnum( D3DFMT_DXT3 );
		(*bufferMap)[ D3DFMT_DXT4 ] = StringifyEnum( D3DFMT_DXT4 );
		(*bufferMap)[ D3DFMT_DXT5 ] = StringifyEnum( D3DFMT_DXT5 );
		(*bufferMap)[ D3DFMT_D16_LOCKABLE ] = StringifyEnum( D3DFMT_D16_LOCKABLE );
		(*bufferMap)[ D3DFMT_D32 ] = StringifyEnum( D3DFMT_D32 );
		(*bufferMap)[ D3DFMT_D15S1 ] = StringifyEnum( D3DFMT_D15S1 );
		(*bufferMap)[ D3DFMT_D24S8 ] = StringifyEnum( D3DFMT_D24S8 );
		(*bufferMap)[ D3DFMT_D24X8 ] = StringifyEnum( D3DFMT_D24X8 );
		(*bufferMap)[ D3DFMT_D24X4S4 ] = StringifyEnum( D3DFMT_D24X4S4 );
		(*bufferMap)[ D3DFMT_D16 ] = StringifyEnum( D3DFMT_D16 );
		(*bufferMap)[ D3DFMT_D32F_LOCKABLE ] = StringifyEnum( D3DFMT_D32F_LOCKABLE );
		(*bufferMap)[ D3DFMT_D24FS8 ] = StringifyEnum( D3DFMT_D24FS8 );

		/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

		/* Z-Stencil formats valid for CPU access */
		(*bufferMap)[ D3DFMT_D32_LOCKABLE ] = StringifyEnum( D3DFMT_D32_LOCKABLE );
		(*bufferMap)[ D3DFMT_S8_LOCKABLE ] = StringifyEnum( D3DFMT_S8_LOCKABLE );

#endif // !D3D_DISABLE_9EX
		/* -- D3D9Ex only */


		(*bufferMap)[ D3DFMT_L16 ] = StringifyEnum( D3DFMT_L16 );

		(*bufferMap)[ D3DFMT_VERTEXDATA ] = StringifyEnum( D3DFMT_VERTEXDATA );
		(*bufferMap)[ D3DFMT_INDEX16 ] = StringifyEnum( D3DFMT_INDEX16 );
		(*bufferMap)[ D3DFMT_INDEX32 ] = StringifyEnum( D3DFMT_INDEX32 );

		(*bufferMap)[ D3DFMT_Q16W16V16U16 ] = StringifyEnum( D3DFMT_Q16W16V16U16 );

		(*bufferMap)[ D3DFMT_MULTI2_ARGB8 ] = StringifyEnum( D3DFMT_MULTI2_ARGB8 );

		// Floating point surface formats

		// s10e5 formats (16-bits per channel)
		(*bufferMap)[ D3DFMT_R16F ] = StringifyEnum( D3DFMT_R16F );
		(*bufferMap)[ D3DFMT_G16R16F ] = StringifyEnum( D3DFMT_G16R16F );
		(*bufferMap)[ D3DFMT_A16B16G16R16F ] = StringifyEnum( D3DFMT_A16B16G16R16F );

		// IEEE s23e8 formats (32-bits per channel)
		(*bufferMap)[ D3DFMT_R32F ] = StringifyEnum( D3DFMT_R32F );
		(*bufferMap)[ D3DFMT_G32R32F ] = StringifyEnum( D3DFMT_G32R32F );
		(*bufferMap)[ D3DFMT_A32B32G32R32F ] = StringifyEnum( D3DFMT_A32B32G32R32F );

		(*bufferMap)[ D3DFMT_CxV8U8 ] = StringifyEnum( D3DFMT_CxV8U8 );

		/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)
		// Monochrome 1 bit per pixel format
		(*bufferMap)[ D3DFMT_A1 ] = StringifyEnum( D3DFMT_A1 );
		// 2.8 biased fixed point
		(*bufferMap)[ D3DFMT_A2B10G10R10_XR_BIAS ] = StringifyEnum( D3DFMT_A2B10G10R10_XR_BIAS );
		// Binary format indicating that the data has no inherent type
		(*bufferMap)[ D3DFMT_BINARYBUFFER ] = StringifyEnum( D3DFMT_BINARYBUFFER );
#endif // !D3D_DISABLE_9EX
		/* -- D3D9Ex only */
		(*bufferMap)[ D3DFMT_FORCE_DWORD ] = StringifyEnum( D3DFMT_FORCE_DWORD );

		return bufferMap;

	}

}
