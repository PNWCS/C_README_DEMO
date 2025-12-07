# IP Count

Counts how many unique IPv4 addresses appear in an input text file.
Each line of the input file should contain one IP address.

## Build
Prerequisites

A POSIX-compatible environment (Linux/macOS/WSL).

gcc or clang

make (GNU Make)

Build
make


This compiles all source files and produces the executable:

./bin/myapp

Clean
make clean


Remove all compiled object files and build artifacts.

Rebuild from scratch
make clean && make

## Run
./ipcount [-v] <input_file>

### Options
- `-v`  Verbose mode: print each newly seen IP address as it is counted.
- `-h`  Show a short help message and exit.

## Example

Count unique IPs in a log file:

```bash
$ ./ipcount access.log
Unique IP addresses: 42
```

Verbose mode (prints each new IP as it is discovered):

```bash
$ ./ipcount -v access.log
[new] 192.168.0.10
[new] 10.0.0.5
...
Unique IP addresses: 42
```
