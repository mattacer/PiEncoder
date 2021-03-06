﻿# PiEncoder
## Quick Summary
This program encodes a file by referencing the file's hexidecimal value to hexidecimal digits of pi. It also decodes encoded files by dereferencing the previously found digit locations pi stored in the encoded file.
## How it works
A file is segmenting into 8 byte blocks, which are each represented by a string of 16 hexidecimal values based on their bytes. The BBP algorithm is then used to calculate 16 digits of pi ranging from the 0th to 4.29 billionth digit of pi. When a match is found between the two sets of strings, the corresponding digit of pi is written to the encoded file in the form of a 4 byte unsigned integer.
## Purpose
In an ideal case, all blocks will have a corresponding digit of pi that can be represented by an unsigned integer. This will result in an encoded file that is half the size of the original file, plus the size of the header (28 bytes). Theoretically the encoded file can also be encoded several more times until an final minimum encoded file file size of 32 bytes is reached.
**Note: Encoded files are not encrypted or cryptographically secured. This program should not be used for sensitive data.**
## Limitations and Drawbacks
- Although both of the cases mentioned above are theoretically possible, it is important to note that it is also possible that a file will not be able to be encoded due to a digit of pi representing a block being greater than the maximum value of an unsigned integer. Once the digit of pi has gone beyond this value, the size of the block is no longer being reduced. Furthermore, as the digit of pi gets sufficiently large so does the data type used to represent the digit. This can result in the final encoded file size actually being larger than the original file which goes against the purpose of this program. The program currently limits the digit of pi to a maximum equal to the maximum value of an unsigned integer for this reason.
- The time complexity of this spigot algorithm is at best *O*(n*log*n) according to [David H. Bailey et al.](http://www.davidhbailey.com/dhbpapers/digits.pdf). This results in large running times unless the file happens to match at primarily lower digits of pi. For an encodabled file, you are essentially trading storage space for processing prower.
## "This looks an awful lot like pifs/πfs..."
Yes, thats because this project was based off of it. In fact, both use the code proved by David H. Baily, [piqpr8](http://www.experimentalmath.info/bbp-codes/). The idea was interesting, but finding collisions in digits of pi for entire files, let alone an entire operating system, poses the first problem listed in the **Limitations and Drawbacks** section above where the data type used to store the digit of pi becomes significantly large. The aim of this project was to avoid that problem by reducing the match sensitivity by segmenting the files while still retaining some file size reduction.
## Acknowledgements
- [**philipl**](https://github.com/philipl/pifs) for the idea.
- [**David H. Bailey**](http://www.experimentalmath.info/) for the algorithm and code.
## License
This software is released under the [MIT License](/LICENSE.md).
