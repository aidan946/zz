# zz (C++ Version)
A bad toy LS implementation written in C++

## Building

### Building with Ninja

The project includes a standalone `build.ninja` file for building with Ninja:

```bash
# Build the project
ninja

# Build debug version
ninja debug

# Run tests
ninja test

# Clean build artifacts
ninja clean

# Install to system (requires sudo)
ninja install

# Run the program
ninja run
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
- `--no-icons` - Disable filetype icons
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

- C++23 compatible compiler (g++ or clang++)
- Standard library with `<filesystem>` support
- Ninja build system

## Development

To run tests:
```bash
ninja test
```

To clean build artifacts:
```bash
ninja clean
```

To build debug version:
```bash
ninja debug
```


