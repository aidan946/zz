# zz
A bad toy LS

## Building

The project uses zig as its build system:

```bash
# Build the project
zig build

# Run the program
zig build run

# Run the program with debug symbols
zig build debug
```

## Usage

Basic usage:
```bash
zz
```

With options:
```bash
zz -r 3 --no-icons --no-gitignore
```

### Command Line Options

- `-r <depth>` - Enable recursive listing with specified depth
- `--no-highlights` - Disable syntax highlighting (not yet implemented)
- `--no-icons` - Disable filetype icons
- `--no-list` - Use inline format instead of list format
- `--no-gitignore` - Ignore .gitignore patterns

## Dependencies

- C++23 compatible compiler
- zig build system
