# Memory Allocator Simulator - Demo Results

This directory contains demonstration outputs showcasing the behavior of different memory allocation algorithms implemented in the simulator.

## Demo Contents

### Visual Outputs
- **dump.png** - Screenshot showing memory layout visualization with allocated and free blocks
- **stats.png** - Memory statistics analysis displaying fragmentation levels and utilization metrics

### Key Features Demonstrated
1. **Memory Layout Visualization**: Real-time display of memory blocks with address ranges
2. **Allocation Strategy Comparison**: Performance differences between First Fit, Best Fit, and Worst Fit
3. **Fragmentation Analysis**: External fragmentation calculations and memory efficiency metrics
4. **Block Coalescing**: Automatic merging of adjacent free blocks during deallocation

### Testing Scenarios
The demo showcases various allocation patterns including:
- Sequential allocations of different sizes
- Mixed allocation and deallocation cycles
- Fragmentation buildup and recovery through coalescing
- Memory utilization under different allocation strategies

### Performance Insights
- **Best Fit**: Minimizes wasted space but can increase fragmentation
- **First Fit**: Fast allocation with moderate fragmentation
- **Worst Fit**: Reduces small unusable fragments but may waste large blocks

## Running Your Own Demo
Execute the simulator and try these command sequences:
```
init 1000
set best_fit
malloc 100
malloc 200
malloc 150
dump
stats
```
