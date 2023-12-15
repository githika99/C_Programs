<h1>Description</h1>
For this assignment, a private and public key is created. Using these keys, a message is encrypted and then decrypted.

<h1>Building</h1>
$ make

<h2>Keygen</h2>
$ ./keygen

<h3>Options for Keygen</h3>
SYNOPSIS
   Generates an SS public/private key pair.

USAGE
   ./keygen [OPTIONS]

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -b bits         Minimum bits needed for public key n (default: 256).
   -i iterations   Miller-Rabin iterations for testing primes (default: 50).
   -n pbfile       Public key file (default: ss.pub).
   -d pvfile       Private key file (default: ss.priv).
   -s seed         Random seed for testing.

<h2>Encrypt</h2>
$ ./encrypt

<h3>Options for Encrypt</h3>
SYNOPSIS
   Encrypts data using SS encryption.
   Encrypted data is decrypted by the decrypt program.

USAGE
   ./encrypt [OPTIONS]

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to encrypt (default: stdin).
   -o outfile      Output file for encrypted data (default: stdout).
   -n pbfile       Public key file (default: ss.pub).

<h2>Decrypt</h2>
$ ./decrypt

<h3>Options for Decrypt</h3>
SYNOPSIS
   Decrypts data using SS decryption.
   Encrypted data is encrypted by the encrypt program.

USAGE
   ./decrypt [OPTIONS]

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to decrypt (default: stdin).
   -o outfile      Output file for decrypted data (default: stdout).
   -n pvfile       Private key file (default: ss.priv).

<h1>Cleaning</h1>
$ make clean

<h1>Bugs</h1>
