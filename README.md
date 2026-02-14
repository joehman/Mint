# Mint

Mint is short for my interpreter and is an interpreter written in the C programming language.

## Installation

Clone the repository then run CMake and build the files CMake generates.
Windows support may be limited.

## Usage

Files can be passed by inputting them as an argument. 

```
Mint [file]
```

## Language

Variables are declared like this:

```
variablename = 123
```

Functions are declared like this:

```
func functionname(args)
  whatever
end
```

If statements are declared like this:

```
if a > b
  print(1)
end
```

### Objects

Currently, only the mtNumber object exists. It represents any number, decimal or integer.

### Modules

This language has a module system.

To import a module, type

```
import modulename
```

Curently, only the io module exists, which exposes the print function that allows you to print an object.
