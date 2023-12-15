<h1>Description</h1>
There are errors in the encoding and decoding. This assignment consits of a compression (encode) algorithm and decompression (decode) algorithm that do LZ78 data compression. 

<h1>Building</h1>
$ make
and 
$ make all
make both the encode and decode executables.

<h2>Encode</h2>
$ make encode

<h3>Options for Encode</h3>
SYNOPSIS
   Compresses files using the LZ78 compression algorithm.
   Compressed files are decompressed with the corresponding decoder.

USAGE
   ./encode [-vh] [-i input] [-o output]

OPTIONS
   -v          Display compression statistics
   -i input    Specify input to compress (stdin by default)
   -o output   Specify output of compressed input (stdout by default)
   -h          Display program help and usage

<h2>Decode</h2>
$ make decode

<h3>Options for Decode</h3>
SYNOPSIS
   Decompresses files with the LZ78 decompression algorithm.
   Used with files compressed with the corresponding encoder.

USAGE
   ./decode [-vh] [-i input] [-o output]

OPTIONS
   -v          Display decompression statistics
   -i input    Specify input to decompress (stdin by default)
   -o output   Specify output of decompressed input (stdout by default)
   -h          Display program usage

<h1>Cleaning</h1>
$ make clean

<h1>Bugs</h1>

