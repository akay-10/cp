# Competitive Programming Template

A C++ template for competitive programming with debugging utilities.

## Files

- `code.cc` - Main solution file
- `run.sh` - Build and run script
- `dbg.h` - Debugging macro header
- `input.txt` - Input file (for local testing)
- `compile_commands.json` - Clangd configuration

## Usage

```bash
./run.sh local    # Run with dbg.h enabled for debugging
./run.sh judge    # Run without dbg.h for final submission
```

## Features

- Debugging with `dbg()` macro when compiled in LOCAL mode
- Common type aliases: `ll`, `pii`, `vi`, etc.
- Input: Overloaded >> operator for most common containers

## dbg() Usage

```cpp
int x = 5;
vi v = {1, 2, 3};
dbg(x, v);  // Prints: [file.cc:line] x = 5, v = {1, 2, 3}
```

## Compile Commands

The `compile_commands.json` is configured with `-DLOCAL` for clangd. Run in judge mode before submitting.

## Stress test

- Use https://luchobazz.github.io/quicktest/
```bash
qt cmp -t code.cpp -c brute.cpp -g gen.cpp --test-cases=10 --diff
```
