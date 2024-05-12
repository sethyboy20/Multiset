## Comparing Multisets
A program to compares and contrast two multisets of numbers.

## Usage
Run ```make``` to build the program.

Run ```main <filename here>``` on the TXT file of sequences to start the program.

The TXT file should be formatted with each set of numbers on a separate line, numbers separated by commas, enclosed in brackets such as in the example file  ```multisets.txt```.

Example input:

```console
{1,2,5,6,7,8}
{2,5,6,7,8,9}
```

Example output:
```console
Multisets:
	A={1,2,5,6,7,8}
	B={2,5,6,7,8,9}

Solutions:
	A∪B={1,2,5,6,7,8,9}
	A∩B={2,5,6,7,8}
	A-B={1}
	B-A={9}
	A+B={1,2,2,5,5,6,6,7,7,8,8,9}
```
