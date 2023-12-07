# Ft_ssl

This program provides an implementation of popular cryptographic hashing algorithms, including MD5, SHA256 and Whirlpool. It allows users to generate hash digests of strings, files, or standard input.

## Getting Started
These instructions will help you get a copy of the project up and running on your local machine for development and testing purposes.

### I. Prerequisites
- A C compiler (like gcc)
- Make (for building the program)

### II. Installing

1. Clone the repository:
````
git clone https://github.com/jmbertin/Ft_ssl_md5.git
````

2. Navigate to the project directory:
````
cd Ft_ssl_md5
````

3. Compile the program:
````
make
````

### III. Usage
After compiling, you can use the program to compute hash digests. Here are some usage examples:

**HASH** :
- ``md5``
- ``sha256``
- ``whirlpool``

**OPTIONS** :
- ``-p`` - echo STDIN to STDOUT and append the checksum to STDOUT
- ``-q`` - quiet mode
- ``-r`` - reverse the format of the output.
- ``-s`` - print the sum of the given string

**INPUT TYPE** :
- To compute the hash of a string:
````
./ft_ssl <HASH> -s "your string here"
````
- To compute the hash of a file:
````
./ft_ssl <HASH> filename.txt
````
- To compute the hash of standard input:
````
echo "your input here" | ./ft_ssl <HASH>
````
- You can add multiple input sources:
````
echo "your input here" | ./ft_ssl <HASH> -s "second input" 3rd_input.txt
````
*Without the ``-p`` flag, stdin will be ignored if there's at least one file or string.*

- To run into **interactive mode**, just launch the binary (*in interactive mode, the use of a file or a string is mandatory*):
````
./ft_ssl
````
**Enter ``exit`` to quit, or enter ``execute`` followed by the same arguments as above.**


### IV. Testing

You can use the testers inside the folder.

- Parsing tester
````
./test_error_parsing.sh
````

- Hash generation testing
````
./tests_hash.sh
````

----

## Hash Algorithms

### MD5

Documentation : [PDF RFC1321](./documentation/MD5-RFC1321.pdf)
The MD5 (Message-Digest Algorithm 5) is a widely used cryptographic hash function that produces a 128-bit (16-byte) hash value. It's commonly used to check the integrity of data. However, it is not suitable for security-sensitive applications, as it is vulnerable to collision attacks.

**How MD5 Works**
- **Step 1: Padding** - The message is extended so that its length is congruent to 448 modulo 512.
- **Step 2: Appending Length** - A 64-bit representation of the original message length is appended.
- **Step 3: Initialization of Buffers** - Four buffers (A, B, C, D) are initialized with specific values.
- **Step 4: Processing in 512-bit Blocks** - The main algorithm operates on each 512-bit block of the padded message.
- **Step 5: Producing the Digest** - The final digest is calculated by concatenating the buffers A, B, C, and D.

### SHA256
Documentation : [PDF RFC6234](./documentation/SHA256-RFC6234.pdf)
SHA256 is part of the SHA-2 (Secure Hash Algorithm 2) family. It produces a 256-bit hash and is used in various security applications and protocols, including TLS and SSL, PGP, SSH, and more.

**How SHA256 Works**
- **Step 1: Padding** - The message is padded so that its length is congruent to 448 modulo 512.
- **Step 2: Parsing** - The padded message is divided into 512-bit blocks.
- **Step 3: Setting Initial Hash Values** - Eight hash values are initialized to specific constants.
- **Step 4: Compression** - Each block is compressed in a series of operations involving bitwise operations, modular additions, and compression functions.
- **Step 5: Producing the Final Hash** - The compressed message blocks are combined to produce the final SHA256 hash.


### Whirlpool
Documentation : [ISO Website (ISO/EIC 10118-3:2018)](https://www.iso.org/fr/standard/67116.html)
Whirlpool is a cryptographic hash function that produces a 512-bit (64-byte) hash value. It's designed for security and is often used in various cryptographic applications. Whirlpool is part of the ISO/IEC 10118-3 standard and has undergone several revisions since its initial design.

**How Whirlpool Works**
- **Step 1: Padding** - The message is padded to ensure that its length is a multiple of 512 bits. The padding scheme is similar to that of MD5 and SHA-1, where a single '1' bit is appended, followed by a series of '0' bits, and finally, the length of the original message is added.
- **Step 2: Initializing the Hash State** - The hash state is initialized with a 512-bit value. In the original Whirlpool version, this value is all zeros, while in later versions like Whirlpool-T and Whirlpool-0, different initialization values are used.
- **Step 3: Processing in 512-bit Blocks** - The padded message is processed in 512-bit blocks. Each block undergoes a series of transformations that include bitwise operations, permutations, and substitutions based on the Whirlpool S-boxes (substitution boxes).
- **Step 4: The Miyaguchi-Preneel Compression Function** - This function is used to update the hash state with the processed message block. The function takes the current hash state, the processed message block, and the previous hash state as inputs, and produces a new hash state.
- **Step 5: Producing the Final Hash** - After all message blocks have been processed, the hash state represents the final hash value. This hash is the output of the Whirlpool algorithm.

----

## Contribution
If you encounter any bugs or wish to add features, please feel free to open an issue or submit a pull request.
