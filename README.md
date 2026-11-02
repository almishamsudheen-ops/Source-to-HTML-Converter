# Source-to-HTML Converter

A command-line application developed in C that converts C source code into an HTML file. The generated HTML file displays the source code in a browser while preserving its original formatting and indentation.

The project uses file handling, string processing, and parser-based logic to read C source files and generate HTML output.

**Repository:** [GitHub](https://github.com/almishamsudheen-ops)

## Features

- Converts C source code into an HTML file.
- Accepts source and output filenames through command-line arguments.
- Generates browser-readable HTML output.
- Preserves original source code formatting and indentation.
- Supports optional line numbering.
- Uses parser logic to process C source code.
- Handles file opening and writing errors.
- Validates input and output file extensions (`.c` and `.html`).

## Technologies Used

- C Programming
- File Handling
- String Processing
- Pointers
- Command-Line Arguments
- Parser Design
- HTML Generation
- Makefile
- GCC Compiler

## Project Structure

```text
Source-to-HTML-Converter/
│
├── main.c
├── main.h
├── parser.c
├── parser.h
├── write_html.c
├── source.c
├── Makefile
└── README.md
```

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/almishamsudheen-ops/Source-to-HTML-Converter.git

cd Source-to-HTML-Converter
```

### Compilation

Using GCC:

```bash
gcc *.c -o source2html
```

Or using Makefile:

```bash
make
```

### Usage

Run the program by providing the source C file and output HTML file:

```bash
./source2html main.c output.html
```

Alternatively, if using the default GCC output:

```bash
gcc *.c
./a.out main.c output.html
```

### View the Output

Open the generated HTML file in your browser:

```bash
explorer.exe output.html
```

## Example

### Input (main.c)

```c
#include <stdio.h>

int main()
{
    int num = 10;

    printf("Hello World");

    return 0;
}
```

### Output

The program generates an HTML file containing the source code while maintaining its original structure and formatting.

## Error Handling

- Insufficient command-line arguments.
- Invalid source file extension.
- Invalid HTML output file extension.
- Failure to open the source file.
- Failure to create or open the HTML output file.
- Errors while writing to the output file.

## Key Learnings

- Improved understanding of C file handling.
- Practiced working with command-line arguments.
- Gained experience in pointers and string processing.
- Learned how to generate HTML dynamically using C.
- Understood parser logic and source code processing.
- Practiced modular programming using multiple C files and header files.

## Future Improvements

- Improve syntax highlighting for different C language elements.
- Add support for additional programming languages.
- Improve HTML formatting and styling using CSS.
- Add more error-handling mechanisms.
- Improve parser efficiency and code readability.

## Author

**Almi Shamsudheen**

- GitHub: [@almishamsudheen-ops](https://github.com/almishamsudheen-ops)
- LinkedIn: [Almi Shamsudheen](https://www.linkedin.com/in/almi-shamsudheen-67b4592b2)

Developed as part of C programming practice, focusing on file handling, parser logic, pointers, and HTML generation.

## License

MIT License
