//
//  memory_statistics.h
//  Codex
//
//  Created by Jens Kwasniok on 22.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__memory_statistics__
#define __Codex__memory_statistics__

#include "config.h"

#if CDX_ENABLE_MEMORY_STATISTICS
#include <new>
#include <iostream>
#include <map>

//! Use macros only!<p>
//! Use 'NEW' instead of 'new' to track a memory block. The static instance of this class is created
//! automaticcally when NEW is called the first time. All entries are check when the programm exits,
//! any missing deletion of a tracked memory block will be printed to the standard outstream.
//! Use PRINT_MEMORY_STATISTICS() at any time to print the statistics for that moment.
//! @see NEW, PRINT_MEMORY_STATISTICS()
class Memory_Statistics {
public:

private:
	struct Allocation_Info {
		size_t size;
		const char* filename;
		int line;
	};

	long tracked_allocations;
	long tracked_bytes_allocated;
	long total_tracked_allocations;
	long total_tracked_bytes_allocated;
	std::map<unsigned long, unsigned long> tracked_allocation_distribution;
	std::map<void*, Allocation_Info> infos;
	bool enabled;

public:
	//! This method is not thread-save.
	//! @return reference to global memory statistics
	static Memory_Statistics& get();

	Memory_Statistics();
	~Memory_Statistics();

	bool is_enabled() {return enabled;}
	void tracked_allocation(void* ptr, const Allocation_Info& m);
	void deallocation(void* ptr);
	void print_statistics();
};

//! Allocates a block of memory and stores the given informatio associated with this address.
//! The address is tracked until it is freed.
void* operator new (std::size_t size, const char* filename, int line);

//! Deletes (all kinds of) memory blocks. If it was allocated with new(std::size_t, const char*, int)
//! the deallocation is registered as well.
void operator delete (void* ptr) noexcept;

#define NEW new(__FILE__, __LINE__)
#define PRINT_MEMORY_STATISTICS() Memory_Statistics::get().print_statistics()

#else
#define NEW new
#define PRINT_MEMORY_STATISTICS()
#endif // if(CDX_ENABLE_MEMORY_STATISTICS)

#endif /* defined(__Codex__memory_statistics__) */
