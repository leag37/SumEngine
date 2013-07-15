#include "SumMemoryAllocator.h"

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
		_fixedSize[0] = Chunk(0, 8);
		_fixedSize[1] = Chunk(0, 16);
		_fixedSize[2] = Chunk(0, 24);
		_fixedSize[3] = Chunk(0, 32);
		_fixedSize[4] = Chunk(0, 40);
		_fixedSize[5] = Chunk(0, 48);
		_fixedSize[6] = Chunk(0, 56);
		_fixedSize[7] = Chunk(0, 64);
		_fixedSize[8] = Chunk(0, 72);
		_fixedSize[9] = Chunk(0, 80);
		_fixedSize[10] = Chunk(0, 88);
		_fixedSize[11] = Chunk(0, 96);
		_fixedSize[12] = Chunk(0, 104);
		_fixedSize[13] = Chunk(0, 112);
		_fixedSize[14] = Chunk(0, 120);
		_fixedSize[15] = Chunk(0, 128);
		_fixedSize[16] = Chunk(0, 136);
		_fixedSize[17] = Chunk(0, 144);
		_fixedSize[18] = Chunk(0, 152);
		_fixedSize[19] = Chunk(0, 160);
		_fixedSize[20] = Chunk(0, 168);
		_fixedSize[21] = Chunk(0, 176);
		_fixedSize[22] = Chunk(0, 184);
		_fixedSize[23] = Chunk(0, 192);
		_fixedSize[24] = Chunk(0, 200);
		_fixedSize[25] = Chunk(0, 208);
		_fixedSize[26] = Chunk(0, 216);
		_fixedSize[27] = Chunk(0, 224);
		_fixedSize[28] = Chunk(0, 232);
		_fixedSize[29] = Chunk(0, 240);
		_fixedSize[30] = Chunk(0, 248);
		_fixedSize[31] = Chunk(0, 256);

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


		// Initialize critical section
		_criticalSection = CriticalSection();
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
		// Safety check
		if(size == 0)
		{
			return 0;
		}

		// Enter the critical section
		_criticalSection.enter();

		// Check against minimum size
		size = size < 8 ? 8 : size;

		// ONLY PERFORM 1 and 2 if size <= 256
		SUINT bin = 0;
		Chunk* chk = 0;
		if(size <= 256)
		{
			// 1
			// Check for free chunk in exact-fit bin
			//-------------------------

			// Get fixed size bin to check first
			bin = (size >> 3) - 1;
			chk = &_fixedSize[bin];
		
			if(chk->ptr)
			{
				return validatePointer(chk->pop(), size);
			}

			// 2
			// If not, look into the next largest bin
			//-------------------------
		
			// Only check next bin if next bin is available
			if(bin < 31)
			{
				chk = &_fixedSize[bin + 1];

				if(chk->ptr)
				{
					return validatePointer(chk->pop(), size);
				}
			}
		}

		// 3
		// If that bin has no chunk, check designated victim (dv) chunk
		//-------------------------
		
		if(_designatedVictim.ptr)
		{
			// Get the pointer value at memory offset
			SUINT ptrSize = *reinterpret_cast<SUINT*>(_designatedVictim.ptr);
			if(ptrSize >= size)
			{
				// Get the return pointer from the DV
				void* rPtr = _designatedVictim.pop();

				// If the pointer size is not exact, push back remnant onto DV
				if(ptrSize != size)
				{
					// Get pointer at new location for designated victim
					void* nPtr =  static_cast<void*>(static_cast<SCHAR*>(rPtr) + size + MEM_OFFSET);
					
					// Set pointer size and push onto DV
					validateChunk(nPtr, *reinterpret_cast<SUINT*>(rPtr) - size - MEM_OFFSET);
					_designatedVictim.push(nPtr);
				}

				return validatePointer(rPtr, size);
			}
		}

		// 4
		// If the dv chunk is not sufficiently large
		// - search for the smallest available small-size chunk
		// - split off a chunk of needed size
		// - make the rest the dv chunk
		//-------------------------

		if(size <= 256)
		{
			for(bin = bin + 2; bin < 32; ++bin)
			{
				if(_fixedSize[bin].ptr)
				{
					// Get pointer to return
					void* rPtr = _fixedSize[bin].pop();
					
					// Get pointer at new location for designated victim
					void* nPtr =  static_cast<void*>(static_cast<SCHAR*>(rPtr) + size + MEM_OFFSET);
					
					// Set pointer size and push onto DV
					validateChunk(nPtr, *reinterpret_cast<SUINT*>(rPtr) - size - MEM_OFFSET);
					_designatedVictim.push(nPtr);

					// Return value
					return validatePointer(rPtr, size);
				}
			}
		}

		// 5
		// If no suitable small-size chunks are found
		// - split off a piece from a large-size chunk
		// - make the remainder the dv chunk
		//-------------------------
		bin = 0;
		SUINT base = 1;
		while(bin < 32)
		{
			// Get next variable-size chunk
			chk = &_variableSize[bin];

			// We fit within this chunk and it exists
			SUINT fitBinSize = chk->chunkSize;
			SUINT smallBinSize = fitBinSize >> 1;
			if(chk->ptr && size <= fitBinSize && size > smallBinSize)
			{
				// Get pointer to return
				void* rPtr = chk->pop();
					
				// Get pointer at new location for designated victim
				void* nPtr =  static_cast<void*>(static_cast<SCHAR*>(rPtr) + size + MEM_OFFSET);
					
				// Set pointer size and push onto DV
				validateChunk(nPtr, *reinterpret_cast<SUINT*>(rPtr) - size - MEM_OFFSET);
				_designatedVictim.push(nPtr);

				// Return value
				return validatePointer(rPtr, size);
			}
			else if(size < chk->chunkSize)
			{
				bin += base;
				base = base << 1;
			}
			else
			{
				base = base << 1;
				bin += base;
			}
		}

		// 6
		// All else fails, allocate new from memory
		//-------------------------
		void* ptr = static_cast<void*>(reinterpret_cast<SCHAR*>(malloc(size + MEM_OFFSET)) + MEM_OFFSET);

		return validatePointer(ptr, size);
	}

	//************************************************************************************************
	// Free a given chunk of memory
	//************************************************************************************************
	void MemoryAllocator::free(void* ptr)
	{
		// Safety check
		if(ptr == 0)
		{
			return;
		}

		// Enter the critical section
		_criticalSection.enter();

		// Get data pointer location
		void* nPtr = static_cast<void*>(reinterpret_cast<SCHAR*>(ptr) - MEM_OFFSET);

		// Get size of memory to be freed
		SUINT size = *reinterpret_cast<SUINT*>(nPtr);

		// Set this piece of data to zero to ensure pushing happens safely
		*reinterpret_cast<SUINT*>(nPtr) = 0;

		// Set the size of the pointer
		*reinterpret_cast<SUINT*>(ptr) = size;

		// Find appropriate bin
		if(size > 256)
		{
			SUINT bin = 0;
			SUINT base = 1;
			while(bin < 32)
			{
				Chunk* chk = &_variableSize[bin];

				// The memory chunk fits is smaller than the next largest bin
				SUINT fitBinSize = chk->chunkSize;
				SUINT bigBinSize = fitBinSize << 1;
				if(size >= fitBinSize && size < bigBinSize)
				{
					chk->push(ptr);
					_criticalSection.leave();
					return;
				}
				else if(size < fitBinSize)
				{
					bin += base;
					base = base << 1;
				}
				else
				{
					base = base << 1;
					bin += base;
				}
			}

			// Push into auxiliary chunk if no other choice
			_designatedVictim.push(ptr);
		}
		else 
		{
			SUINT bin = (size >> 3) - 1;
			_fixedSize[bin].push(ptr);
		}

		// Leave the critical section
		_criticalSection.leave();
	}
}