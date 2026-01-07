#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

/**
 * Dynamic Memory Allocation Simulator
 * 
 * Features implemented:
 * - First Fit allocation algorithm
 * - Best Fit allocation algorithm  
 * - Worst Fit allocation algorithm
 * - Dynamic memory allocation with block splitting
 * - Automatic coalescing of free blocks
 * - Memory utilization and fragmentation analysis
 */

// Enumeration for different allocation strategies
enum class AllocationStrategy { 
    FIRST_FIT, 
    BEST_FIT, 
    WORST_FIT 
};

// Structure representing a memory block
struct MemoryBlock {
    size_t startAddress;    // Starting memory address
    size_t blockSize;       // Size of the memory block
    bool isFree;           // Flag indicating if block is available
    int blockId;           // Unique identifier for allocated blocks (-1 for free)
    
    MemoryBlock(size_t start, size_t size, bool free, int id = -1) 
        : startAddress(start), blockSize(size), isFree(free), blockId(id) {}
};

// ============= GLOBAL VARIABLES =============
vector<MemoryBlock> memoryPool;
size_t totalMemorySize = 0;
int nextBlockId = 1;
AllocationStrategy currentStrategy = AllocationStrategy::FIRST_FIT;

// Statistics tracking
struct AllocationStats {
    int totalRequests = 0;
    int successfulAllocations = 0;
    int failedAllocations = 0;
} stats;

// ============= MEMORY INITIALIZATION =============
void initializeMemory(size_t memorySize) {
    totalMemorySize = memorySize;
    memoryPool.clear();
    
    // Create initial free block spanning entire memory
    memoryPool.emplace_back(0, memorySize, true, -1);
    nextBlockId = 1;

    // Reset allocation statistics
    stats.totalRequests = 0;
    stats.successfulAllocations = 0;
    stats.failedAllocations = 0;

    cout << "Memory pool initialized successfully with " << memorySize 
         << " bytes\n";
}

// ============= MEMORY ALLOCATION ALGORITHMS =============
int allocateMemory(size_t requestedSize) {
    stats.totalRequests++;

    if (requestedSize <= 0) {
        cout << "Error: Invalid allocation size requested\n";
        stats.failedAllocations++;
        return -1;
    }

    int selectedBlockIndex = -1;

    // Apply selected allocation strategy
    switch (currentStrategy) {
        case AllocationStrategy::FIRST_FIT: {
            for (size_t i = 0; i < memoryPool.size(); i++) {
                if (memoryPool[i].isFree && memoryPool[i].blockSize >= requestedSize) {
                    selectedBlockIndex = i;
                    break;
                }
            }
            break;
        }
        
        case AllocationStrategy::BEST_FIT: {
            size_t bestFitSize = SIZE_MAX;
            for (size_t i = 0; i < memoryPool.size(); i++) {
                if (memoryPool[i].isFree && 
                    memoryPool[i].blockSize >= requestedSize && 
                    memoryPool[i].blockSize < bestFitSize) {
                    bestFitSize = memoryPool[i].blockSize;
                    selectedBlockIndex = i;
                }
            }
            break;
        }
        
        case AllocationStrategy::WORST_FIT: {
            size_t worstFitSize = 0;
            for (size_t i = 0; i < memoryPool.size(); i++) {
                if (memoryPool[i].isFree && 
                    memoryPool[i].blockSize >= requestedSize && 
                    memoryPool[i].blockSize > worstFitSize) {
                    worstFitSize = memoryPool[i].blockSize;
                    selectedBlockIndex = i;
                }
            }
            break;
        }
    }

    if (selectedBlockIndex == -1) {
        cout << "Allocation failed: Insufficient memory available\n";
        stats.failedAllocations++;
        return -1;
    }

    // Perform allocation on selected block
    size_t allocatedAddress = memoryPool[selectedBlockIndex].startAddress;
    size_t remainingSize = memoryPool[selectedBlockIndex].blockSize - requestedSize;

    // Update block information
    memoryPool[selectedBlockIndex].blockSize = requestedSize;
    memoryPool[selectedBlockIndex].isFree = false;
    memoryPool[selectedBlockIndex].blockId = nextBlockId++;

    // Create new free block if there's remaining space
    if (remainingSize > 0) {
        memoryPool.insert(
            memoryPool.begin() + selectedBlockIndex + 1,
            MemoryBlock(allocatedAddress + requestedSize, remainingSize, true, -1)
        );
    }

    stats.successfulAllocations++;

    cout << "Memory allocated successfully: Block ID=" << memoryPool[selectedBlockIndex].blockId
         << ", Address=0x" << hex << allocatedAddress << dec << "\n";

    return memoryPool[selectedBlockIndex].blockId;
}

// ============= MEMORY DEALLOCATION =============
void deallocateMemory(int blockId) {
    for (size_t i = 0; i < memoryPool.size(); i++) {
        if (!memoryPool[i].isFree && memoryPool[i].blockId == blockId) {
            // Mark block as free
            memoryPool[i].isFree = true;
            memoryPool[i].blockId = -1;

            // Coalesce with next adjacent free block
            if (i + 1 < memoryPool.size() && memoryPool[i + 1].isFree) {
                memoryPool[i].blockSize += memoryPool[i + 1].blockSize;
                memoryPool.erase(memoryPool.begin() + i + 1);
            }

            // Coalesce with previous adjacent free block
            if (i > 0 && memoryPool[i - 1].isFree) {
                memoryPool[i - 1].blockSize += memoryPool[i].blockSize;
                memoryPool.erase(memoryPool.begin() + i);
            }

            cout << "Memory block " << blockId << " freed and coalesced successfully\n";
            return;
        }
    }
    cout << "Error: Invalid block ID specified\n";
}

// ============= MEMORY VISUALIZATION =============
void displayMemoryLayout() {
    cout << "\n=== Current Memory Layout ===\n";
    for (const auto& block : memoryPool) {
        cout << "[0x" << hex << block.startAddress
             << " - 0x" << (block.startAddress + block.blockSize - 1) << dec << "] ";
        if (block.isFree) {
            cout << "FREE BLOCK (Size: " << block.blockSize << ")\n";
        } else {
            cout << "ALLOCATED (ID: " << block.blockId 
                 << ", Size: " << block.blockSize << ")\n";
        }
    }
    cout << "==============================\n\n";
}

// ============= STATISTICS AND ANALYSIS =============
void generateMemoryStatistics() {
    size_t totalUsedMemory = 0, totalFreeMemory = 0, largestFreeBlock = 0;

    for (const auto& block : memoryPool) {
        if (block.isFree) {
            totalFreeMemory += block.blockSize;
            largestFreeBlock = max(largestFreeBlock, block.blockSize);
        } else {
            totalUsedMemory += block.blockSize;
        }
    }

    // Calculate fragmentation metrics
    double externalFragmentation = (totalFreeMemory == 0) ? 0.0 :
        100.0 * (totalFreeMemory - largestFreeBlock) / totalFreeMemory;

    double memoryUtilization = (totalMemorySize == 0) ? 0.0 :
        100.0 * totalUsedMemory / totalMemorySize;

    // Display comprehensive statistics
    cout << "\n========== Memory Analytics ==========\n";
    cout << "Total Memory Pool: " << totalMemorySize << " bytes\n";
    cout << "Memory in Use: " << totalUsedMemory << " bytes\n";
    cout << "Available Memory: " << totalFreeMemory << " bytes\n";
    cout << "Memory Utilization: " << fixed << setprecision(2) 
         << memoryUtilization << "%\n";
    cout << "Internal Fragmentation: 0 bytes (exact fit allocation)\n";
    cout << "External Fragmentation: " << fixed << setprecision(2) 
         << externalFragmentation << "%\n";
    cout << "\n--- Allocation History ---\n";
    cout << "Total Requests: " << stats.totalRequests << "\n";
    cout << "Successful Allocations: " << stats.successfulAllocations << "\n";
    cout << "Failed Allocations: " << stats.failedAllocations << "\n";
    
    if (stats.totalRequests > 0) {
        double successRate = 100.0 * stats.successfulAllocations / stats.totalRequests;
        cout << "Success Rate: " << fixed << setprecision(2) << successRate << "%\n";
    }
    cout << "=====================================\n\n";
}

// ============= COMMAND LINE INTERFACE =============
int main() {
    string userCommand;
    cout << "Dynamic Memory Allocator Simulator v1.0\n";
    cout << "Type 'help' for available commands\n\n";

    while (true) {
        cout << "memsim> ";
        cin >> userCommand;

        if (userCommand == "help") {
            cout << "\nAvailable Commands:\n";
            cout << "  init <size>     - Initialize memory pool\n";
            cout << "  set <strategy>  - Set allocation strategy (first_fit/best_fit/worst_fit)\n";
            cout << "  malloc <size>   - Allocate memory block\n";
            cout << "  free <id>       - Deallocate memory block\n";
            cout << "  dump            - Display memory layout\n";
            cout << "  stats           - Show memory statistics\n";
            cout << "  exit            - Quit simulator\n\n";
        }
        else if (userCommand == "init") {
            size_t memorySize;
            cin >> memorySize;
            initializeMemory(memorySize);
        }
        else if (userCommand == "set") {
            string strategyName;
            cin >> strategyName;
            if (strategyName == "first_fit") {
                currentStrategy = AllocationStrategy::FIRST_FIT;
                cout << "Allocation strategy set to First Fit\n";
            }
            else if (strategyName == "best_fit") {
                currentStrategy = AllocationStrategy::BEST_FIT;
                cout << "Allocation strategy set to Best Fit\n";
            }
            else if (strategyName == "worst_fit") {
                currentStrategy = AllocationStrategy::WORST_FIT;
                cout << "Allocation strategy set to Worst Fit\n";
            }
            else {
                cout << "Error: Unknown allocation strategy\n";
            }
        }
        else if (userCommand == "malloc") {
            size_t size;
            cin >> size;
            allocateMemory(size);
        }
        else if (userCommand == "free") {
            int blockId;
            cin >> blockId;
            deallocateMemory(blockId);
        }
        else if (userCommand == "dump") {
            displayMemoryLayout();
        }
        else if (userCommand == "stats") {
            generateMemoryStatistics();
        }
        else if (userCommand == "exit") {
            cout << "Simulator terminated.\n";
            break;
        }
        else {
            cout << "Error: Unknown command. Type 'help' for available commands.\n";
        }
    }

    return 0;
}
