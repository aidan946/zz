# zz (C++ Version)
A bad toy LS implementation written in C++

## Building

### Using Make (Simple)
```bash
make
```

For debug build:
```bash
make debug
```

### Using CMake (Advanced)
```bash
mkdir build
cd build
cmake ..
make
```

## Usage

Basic usage:
```bash
./zz
```

With options:
```bash
./zz -r 3 --no-icons --no-gitignore
```

### Command Line Options

- `-r <depth>` - Enable recursive listing with specified depth
- `--no-highlights` - Disable syntax highlighting (not yet implemented)
- `--no-icons` - Disable file type icons
- `--no-list` - Use inline format instead of list format
- `--no-gitignore` - Ignore .gitignore patterns

## Examples

List current directory with icons:
```bash
./zz
```

Recursively list 2 levels deep without icons:
```bash
./zz -r 2 --no-icons
```

List everything including gitignored files:
```bash
./zz --no-gitignore
```

## Dependencies

- C++23 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Standard library with `<filesystem>` support

## Installation

```bash
make install
```

Or with CMake:
```bash
cd build
make install
```

This will install the `zz` binary to `/usr/local/bin/`.

## Development

To run tests:
```bash
make test
```

To clean build artifacts:
```bash
make clean
```
