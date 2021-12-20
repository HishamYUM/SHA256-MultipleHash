# Multiple Times Hash with Multiple Hashing Functions
This code is writen in C and using OpenSSL and EVP functions. 
You use this code in order to hash files multiple times.
For example, let's say you have to files: file1.bin and file2.bin, using this code you are able to concatenate thes files and hash the entire content multiple times:
In other words, you take the entire content of file1.bin and file2.bin and hash it with any supported hashing algorithm by openssl, then you hash the hash value obtained earlier, then you hash it again and so on, depending on the number of times you provided as argument


## Compile command 
gcc multihash -o multihash -lcrypto

## Run the code 
./multihash sha256 3 file1.bin file2.bin
with sha256 is the hashing function, you can change it to any function like md5
3 is the number of times you would to hash the files contaents
then you provide the files name


You maybe encounter a problem is that the file add a new line in the end of file, so check the file's content
