#include "pch.h"
#include "Compression.h"
#include <filters.h>
#include <zlib.h>

namespace GameCrypt
{
	std::vector<unsigned char> Compressor::Compress(std::vector<unsigned char> const& data)
	{
		using namespace CryptoPP;
		std::vector<unsigned char> ret;
		VectorSource(data, true,
			new ZlibCompressor(
				new VectorSink(ret)
			)
		);
		return ret;
	}

	std::vector<unsigned char> Compressor::Decompress(std::vector<unsigned char> const& data)
	{
		using namespace CryptoPP;
		std::vector<unsigned char> ret;
		VectorSource(data, true,
			new ZlibDecompressor(
				new VectorSink(ret)
			)
		);
		return ret;
	}

}
