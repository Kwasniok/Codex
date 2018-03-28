//
//  memory_statistics.cpp
//  Codex
//
//  Created by Jens Kwasniok on 22.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "memory_statistics.h"

#if CDX_ENABLE_MEMORY_STATISTICS
Memory_Statistics& Memory_Statistics::get()
{
	// Use of static local variable solves initialization and destruction problems.
	// global is destructed before its deletion (via finalize) and therefore does not
	// detect its own deletion which would case an error (see delete()).
	// global is initialized when get() is called the first time.
	//
	// get() IS NOT thread-save on its own.
	static Memory_Statistics global;
	return global;
}

Memory_Statistics::Memory_Statistics()
{
	enabled = true;
}

Memory_Statistics::~Memory_Statistics()
{
	{
		enabled = false;

		if (tracked_allocations != 0 || tracked_bytes_allocated != 0)
		{
			std::cout << "[MEM] FINAL:" << std::endl <<
			"      WARNING: Amount of tracked allocations should be zero at this moment." << std::endl <<
			"      list of all non-freed memory blocks:" << std::endl;
			for (auto& i : infos)
			{
				std::cout << "      address = " << i.first << std::endl <<
				"            alloc size = " << i.second.size << std::endl <<
				"            alloc filename = " << i.second.filename << std::endl <<
				"            alloc line = " << i.second.line << std::endl;
			}

			print_statistics();
		}
	}
}

void Memory_Statistics::tracked_allocation(void* ptr, const Allocation_Info& m)
{
#if CDX_MEM_STATS_PRINT_INFO
	std::cout << "[MEM] ALLOC (tracked): address = " << ptr << std::endl <<
	"      alloc size = " << m.size << " byte(s)" << std::endl <<
	"      alloc filename = \"" << (m.filename?m.filename:"") << "\"" << std::endl <<
	"      alloc line = " << m.line << std::endl;
#endif
	tracked_bytes_allocated += m.size;
	total_tracked_bytes_allocated += m.size;
	++tracked_allocations;
	++total_tracked_allocations;
	infos[ptr] = m;
	++ tracked_allocation_distribution[m.size];
}

void Memory_Statistics::deallocation(void* ptr)
{
	if (!ptr) return;

	auto it = infos.find(ptr);
	if (it != infos.end())
	{
		const Allocation_Info& m = it->second;

#if CDX_MEM_STATS_PRINT_INFO
		std::cout << "[MEM] FREE  (tracked): address = " << ptr << std::endl <<
		"      alloc size = " << m.size << " byte(s)" << std::endl <<
		"      alloc filename = \"" << (m.filename?m.filename:"") << "\"" << std::endl <<
		"      alloc line = " << m.line << std::endl;
#endif
		tracked_bytes_allocated -= m.size;
		--tracked_allocations;
		infos.erase(it);
	}
	else
	{
#if CDX_MEM_STATS_PRINT_UNTRACKED_INFO
		std::cout << "[MEM] FREE  (untracked): address = " << ptr << std::endl;
#endif
	}
}

void Memory_Statistics::print_statistics()
{
	std::cout << std::endl <<
	"[MEM] STATS (tracked (de)allocations only): " << std::endl <<
	(tracked_allocations!=0? "*--->":"     ") << // marker
	" allocations = " << tracked_allocations << std::endl <<
	(tracked_bytes_allocated!=0?"*--->":"     ") << // marker
	" bytes allocated = " << tracked_bytes_allocated << std::endl <<
	"      total allocations = " << total_tracked_allocations << std::endl <<
	"      total bytes allocated = " << total_tracked_bytes_allocated << std::endl <<
	std::endl <<
	"      distribution:";
	for (auto it : tracked_allocation_distribution)
	{
		std::cout << std::endl <<
		"      " << it.first << " byte(s) : " << it.second << " time(s)";
	}
	std::cout << std::endl << std::endl;
}

void* operator new(std::size_t size, const char* filename, int line)
{
	void* ptr = std::malloc(size);

	if (ptr != nullptr)
	{
		Memory_Statistics::get().tracked_allocation(ptr, {size, filename, line});
	}

	return ptr;
}

void operator delete(void* ptr) noexcept
{
	if (Memory_Statistics::get().is_enabled())
	{
		Memory_Statistics::get().deallocation(ptr);
	}
	std::free(ptr);
}
#endif // if(CDX_ENABLE_MEMORY_STATISTICS)
