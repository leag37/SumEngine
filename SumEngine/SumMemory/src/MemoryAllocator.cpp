#include "MemoryAllocator.h"

namespace SumMemory
{
	MemoryAllocator* MemoryAllocator::instance = 0;

	MemoryAllocator::MemoryAllocator()
	{ }

	//************************************************************************************************
	// Initialization
	//************************************************************************************************
	void MemoryAllocator::init()
	{
		_designatedVictim = Chunk();

		// Array order is as follow:
		// 17, 9, 25, 5, 13, 21, 29, 3, 7, 11, 15, 19, 23, 27, 31, 
		// 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 1
		
		// Initialize fix length array
		_fixedSize[0] = Chunk(0, 8);//136);
		_fixedSize[1] = Chunk(0, 16);//72);
		_fixedSize[2] = Chunk(0, 24);//200);
		_fixedSize[3] = Chunk(0, 32);//40);
		_fixedSize[4] = Chunk(0, 40);//104);
		_fixedSize[5] = Chunk(0, 48);//168);
		_fixedSize[6] = Chunk(0, 56);//232);
		_fixedSize[7] = Chunk(0, 64);//24);
		_fixedSize[8] = Chunk(0, 72);//56);
		_fixedSize[9] = Chunk(0, 80);//88);
		_fixedSize[10] = Chunk(0, 88);//120);
		_fixedSize[11] = Chunk(0, 96);//152);
		_fixedSize[12] = Chunk(0, 104);//184);
		_fixedSize[13] = Chunk(0, 112);//216);
		_fixedSize[14] = Chunk(0, 120);//248);
		_fixedSize[15] = Chunk(0, 128);//16);
		_fixedSize[16] = Chunk(0, 136);//32);
		_fixedSize[17] = Chunk(0, 144);//48);
		_fixedSize[18] = Chunk(0, 152);//64);
		_fixedSize[19] = Chunk(0, 160);//80);
		_fixedSize[20] = Chunk(0, 168);//96);
		_fixedSize[21] = Chunk(0, 176);//112);
		_fixedSize[22] = Chunk(0, 184);//128);
		_fixedSize[23] = Chunk(0, 192);//144);
		_fixedSize[24] = Chunk(0, 200);//160);
		_fixedSize[25] = Chunk(0, 208);//176);
		_fixedSize[26] = Chunk(0, 216);//192);
		_fixedSize[27] = Chunk(0, 224);//208);
		_fixedSize[28] = Chunk(0, 232);//224);
		_fixedSize[29] = Chunk(0, 240);
		_fixedSize[30] = Chunk(0, 248);//256);
		_fixedSize[31] = Chunk(0, 256);//8);

		// Variable length chunks
		_variableSize[0] = Chunk(0, 98304);
		_variableSize[1] = Chunk(0, 6144);
		_variableSize[2] = Chunk(0, 1572864);
		_variableSize[3] = Chunk(0, 1536);
		_variableSize[4] = Chunk(0, 24576);
		_variableSize[5] = Chunk(0, 393216);
		_variableSize[6] = Chunk(0, 6291456);
		_variableSize[7] = Chunk(0, 768);
		_variableSize[8] = Chunk(0, 3072);
		_variableSize[9] = Chunk(0, 12288);
		_variableSize[10] = Chunk(0, 49152);
		_variableSize[11] = Chunk(0, 196608);
		_variableSize[12] = Chunk(0, 786432);
		_variableSize[13] = Chunk(0, 3145728);
		_variableSize[14] = Chunk(0, 10485760);
		_variableSize[15] = Chunk(0, 512);
		_variableSize[16] = Chunk(0, 1024);
		_variableSize[17] = Chunk(0, 2048);
		_variableSize[18] = Chunk(0, 4096);
		_variableSize[19] = Chunk(0, 8192);
		_variableSize[20] = Chunk(0, 16384);
		_variableSize[21] = Chunk(0, 32768);
		_variableSize[22] = Chunk(0, 65536);
		_variableSize[23] = Chunk(0, 131072);
		_variableSize[24] = Chunk(0, 262144);
		_variableSize[25] = Chunk(0, 524288);
		_variableSize[26] = Chunk(0, 1048576);
		_variableSize[27] = Chunk(0, 2097152);
		_variableSize[28] = Chunk(0, 4194304);
		_variableSize[29] = Chunk(0, 8388608);
		_variableSize[30] = Chunk(0, 12582912);
		_variableSize[31] = Chunk(0, 384);
	}

	//************************************************************************************************
	// Allocate memory of a given size
	// The basic scheme for allocating memory is as follows:
	// 1) Check for free chunk in exact-fit bin
	// 2) If not, look into the next largest bin
	// 3) If that bin has no chunk,	check designated victim (dv) chunk
	// 4) If the dv chunk is not sufficiently large
	//		- search for the smallest available small-size chunk
	//		- split off a chunk of needed size
	//		- make the rest the dv chunk
	// 5) If no suitable small-size chunks are found
	//		- split off a piece from a large-size chunk
	//		- make the remainder the dv chunk
	// 6) All else fails, allocate new from memory
	//************************************************************************************************
	void* MemoryAllocator::allocate(size_t size)
	{
		// 1
		//-------------------------

		// Get fixed size bin to check first
		SUINT bin = size >> 3;
		Chunk chk = _fixedSize[bin];
		
		if(chk.ptr)
		{
			return chk.pop();
		}

		// 2
		//-------------------------
		
		// Only check next bin if next bin is available
		if(bin < 31)
		{
			chk = _fixedSize[bin + 1];

			if(chk.ptr)
			{
				return chk.pop();
			}
		}

		// 3
		//-------------------------
		
		if(_designatedVictim.ptr)
		{
			void* ptr = _designatedVictim.ptr;
			if(*reinterpret_cast<SUINT*>(_designatedVictim.ptr) >= size)
			{
				// Carve out piece from DV
				void* ptr = static_cast<void*>(reinterpret_cast<SCHAR*>(_designatedVictim.pop()) - 4);

				// Push back on if DV is not perfect fit
				if(*(reinterpret_cast<SUINT*>(ptr)) == size)
				{
					_designatedVictim.push(reinterpret_cast<SCHAR*>(ptr) + size + 4);
					*(reinterpret_cast<SUINT*>(_designatedVictim.ptr)) = *reinterpret_cast<SUINT*>(ptr) - size;
				}
				return static_cast<void*>(reinterpret_cast<SCHAR*>(ptr) + 4);
			}
		}

		// 4
		//-------------------------

		if(size < 256)
		{
			for(bin = bin + 2; bin < 32; ++bin)
			{
				if(_fixedSize[bin].ptr)
				{
					void* ptr = static_cast<void*>(reinterpret_cast<SCHAR*>(_designatedVictim.pop()) - 4);
					_designatedVictim.push(reinterpret_cast<SCHAR*>(ptr) + size + 4);
					*(reinterpret_cast<SUINT*>(_designatedVictim.ptr)) = *reinterpret_cast<SUINT*>(ptr) - size;
					return static_cast<void*>(reinterpret_cast<SCHAR*>(ptr) + 4);
				}
			}
		}

		// 5
		//-------------------------
		bin = 0;
		Chunk pChk = Chunk(0, (SUINT) - 1);
		SUINT base = 1;
		while(bin < 32)
		{
			chk = _variableSize[bin];
			if(size <= chk.chunkSize && size > pChk.chunkSize)
			{
				// Is there a valid chunk in the bin?
				if(chk.ptr)
				{
					// Carve out piece from DV
					void* ptr = static_cast<void*>(reinterpret_cast<SCHAR*>(chk.pop()) - 4);

					// Push back on if DV is not perfect fit
					if(*(reinterpret_cast<SUINT*>(ptr)) == size)
					{
						_designatedVictim.push(reinterpret_cast<SCHAR*>(ptr) + size + 4);
						*(reinterpret_cast<SUINT*>(_designatedVictim.ptr)) = *reinterpret_cast<SUINT*>(ptr) - size;
					}
					return static_cast<void*>(reinterpret_cast<SCHAR*>(ptr) + 4);
				}

				bin = 32;
			}
			else if(size < chk.chunkSize)
			{
				base = base << 1;
				bin += base - 1;
			}
			else
			{
				base = base << 1;
				bin += base;
			}

			pChk = chk;
		}

		// 6
		//-------------------------
		SUINT* sPtr = reinterpret_cast<SUINT*>(malloc(size + sizeof(SUINT)));
		*sPtr = size;
		return reinterpret_cast<void*>(reinterpret_cast<SCHAR*>(sPtr) + sizeof(SUINT));
	}

	//************************************************************************************************
	// Free a given chunk of memory
	//************************************************************************************************
	void MemoryAllocator::free(void* ptr)
	{
		// Get actual pointer location
		ptr = reinterpret_cast<SCHAR*>(ptr) - sizeof(SUINT);

		// Get size of chunk
		SUINT size = *reinterpret_cast<SUINT*>(ptr);

		// Find appropriate bin
		if(size > 256)
		{
			SUINT bin = 0;
			SUINT base = 0;
			Chunk chk;
			Chunk pChk = Chunk(0, (SUINT) - 1);
			while(bin < 32)
			{
				chk = _variableSize[bin];
				if(size <= chk.chunkSize && size > pChk.chunkSize)
				{
					chk.push(ptr);
					return;
				}
				else if(size < chk.chunkSize)
				{
					bin += ++base - 1;
				}
				else
				{
					bin += ++base;
				}

				pChk = chk;
			}

			// Push into auxiliary chunk
			_designatedVictim.push(ptr);
		}
		else 
		{
			SUINT bin = size >> 3;
			_fixedSize[bin].push(ptr);
		}
	}
}