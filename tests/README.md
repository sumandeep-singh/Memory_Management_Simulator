# Testing Suite for Memory Allocator Simulator

This directory contains test cases and expected outputs for validating the memory allocation simulator functionality.

## Test Files

### Input Test Cases
- **test_basic.txt** - Fundamental allocation and deallocation test scenarios

### Expected Outputs  
- **expected_output_basic.txt** - Reference outputs for basic test validation

## Test Categories

### Basic Functionality Tests
- Memory pool initialization with various sizes
- Single block allocation and deallocation
- Adjacent block coalescing verification
- Invalid operation handling (negative sizes, invalid IDs)

### Algorithm Comparison Tests
- First Fit vs Best Fit vs Worst Fit performance
- Memory utilization efficiency analysis
- Fragmentation behavior under different strategies

### Edge Case Testing
- Maximum memory allocation attempts
- Rapid allocation/deallocation cycles  
- Memory exhaustion scenarios
- Block coalescing in complex fragmented states

## Running Tests

### Manual Testing
```bash
./memsim < tests/test_basic.txt > output.txt
diff tests/expected_output_basic.txt output.txt
```

### Automated Validation
Compare simulator output with expected results to verify:
- Correct allocation addresses
- Proper block ID assignment
- Accurate fragmentation calculations
- Expected success/failure behaviors

## Test Results Interpretation
- **Address Consistency**: Verify allocated addresses don't overlap
- **Statistics Accuracy**: Confirm memory utilization calculations
- **Coalescing Effectiveness**: Check adjacent free block merging
- **Error Handling**: Validate appropriate error messages for invalid operations
