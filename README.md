# Dynamic Memory Allocator Simulator

A comprehensive C++ implementation of various memory allocation algorithms used in operating systems. This simulator provides an interactive command-line interface to experiment with different allocation strategies and analyze memory utilization patterns.

## Core Functionality
- **Memory Pool Simulation**: Manages a contiguous block of virtual memory
- **Multiple Allocation Strategies**: 
  - First Fit: Allocates using the first available block
  - Best Fit: Finds the smallest suitable block to minimize waste  
  - Worst Fit: Uses the largest available block
- **Dynamic Memory Operations**: Allocation with automatic block splitting
- **Intelligent Deallocation**: Automatic coalescing of adjacent free blocks
- **Real-time Statistics**: Monitor fragmentation levels and allocation efficiency
- **Interactive CLI**: Easy-to-use command interface for testing scenarios

## Building the Project

### Linux/Unix Systems:
```bash
make
```

### Alternative compilation:
```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o memsim
```

## Usage
Launch the simulator:
```bash
./memsim
```

### Available Commands:
- `init <size>` - Initialize memory pool with specified size
- `set <strategy>` - Set allocation strategy (first_fit, best_fit, worst_fit)  
- `malloc <size>` - Allocate memory block of given size
- `free <id>` - Deallocate memory block by ID
- `dump` - Display current memory layout
- `stats` - Show detailed memory statistics
- `exit` - Quit the simulator

## Implementation Details
- **Zero Internal Fragmentation**: Precise block splitting eliminates wasted space within allocated blocks
- **Efficient Coalescing**: Merges adjacent free blocks to reduce external fragmentation
- **Comprehensive Metrics**: Tracks allocation success rates, fragmentation levels, and memory utilization

## Technical Notes
Advanced features like buddy allocation, cache simulation, and virtual memory management were outside the scope of this implementation, focusing instead on core allocation algorithm comparison.


