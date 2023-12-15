#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include "io.h"
#include "code.h"
#include "endian.h"

//extern uint64_t total_syms; // To count the symbols processed.
//extern uint64_t total_bits; // To count the bits processed.
//#define BLOCK 4096 // 4KB blocks.
static uint8_t *buffer = NULL;
static uint8_t *read_buffer = NULL;
//you need to initialize a pointer (to a space in memory) to use it as a buffer
//static uint8_t* buffer = malloc(BLOCK);
static int buf_pos = 0; //computer reads it as bytes
static int read_buf_pos = 0; //changing it to bytes
uint64_t total_syms; // To count the symbols processed.
uint64_t total_bits; // To count the bits processed.

//typedef struct FileHeader {
//    uint32_t magic;
//    uint16_t protection;
//} FileHeader;

//doing your own buffer management
int read_bytes(int infile, uint8_t *buf, int to_read) {
    lseek(infile, buf_pos, SEEK_SET); //byte offset
    int bytes_read = 0;
    int result = 0;
    //printf("bytes to read is %d\n", to_read);
    while (bytes_read < to_read) {
        result += read(infile, buf, to_read);
        if (result == 0 || result == -1)
            break; //reached EOF
        bytes_read += result;
        //printf("bytes_read is %d\n", bytes_read);
    }
    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    printf("Entered write bytes\n");
    lseek(outfile, 0, SEEK_SET);
    int bytes_wrote = 0;
    int result = 0;
    while (bytes_wrote < to_write) {
        printf("enetered loop\n");
        result = write(outfile, buf, (to_write - bytes_wrote));
        printf("just wrote %d bytes", result);
        if (result == 0)
            break; //reached EOF
        if (result == -1) {
            perror("write");
            return 1;
        }
        bytes_wrote += result;
    }
    return bytes_wrote;
}

void read_header(int infile, FileHeader *header) {
    lseek(infile, 0, SEEK_SET);
    uint8_t *header_buffer = malloc(sizeof(FileHeader));
    read_bytes(infile, header_buffer, sizeof(FileHeader));

    //check byte order
    //if byte order is big endian, swap it to little endian

    memcpy(header, header_buffer, sizeof(FileHeader));
    bool endian = big_endian(); //returns true if big endian returns false if not big endian
    if (endian) {
        //printf("\nordering is big endian");
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    if (header->magic != MAGIC)
        printf("Bad magic number.");
    assert(header->magic == MAGIC);
}

void write_header(int outfile, FileHeader *header) {
    //check design doc
    printf("entered write_header\n");
    bool endian = big_endian(); //returns true if big endian returns false if not big endian
    if (endian) {
        //printf("\nordering is big endian");
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }

    uint8_t *header_buffer = malloc(sizeof(FileHeader));
    memcpy(header_buffer, header, sizeof(FileHeader));

    write_bytes(outfile, header_buffer, sizeof(FileHeader));
    //check byte order
    //if byte order is big endian, swap it to little endian
}

int read_block(int infile, int to_read) {
    //printf("\nread_block was entered\n");
    read_buf_pos = 0;
    return read_bytes(infile, read_buffer,
        to_read); //read a BLOCK of data (or less if there is less), data from infile
}

bool read_sym(int infile, uint8_t *sym) {
    //every call to this is with one symbol
    //check if there are no more symbols to read
    //make a read only buffer since write_pair and flush_pair use the buffer to read
    //call read_block

    //reads last character of file (LF) or ASCII 10. could catch for that if you want
    printf("total syms is %lu\n", total_syms);
    if (total_syms == 0) {
        total_bits = 0;
        total_syms = 0;
        read_buffer = malloc(BLOCK);
        read_buf_pos = 0;
        buffer = malloc(BLOCK);
        memset(buffer, 0, BLOCK); //CHANGE BACK TO 0 BEFORE SUMBITtinG
        buf_pos = 0;
        read_block(infile, 1);
    }

    int bytes_read = read_bytes(infile, sym, 1);
    printf("symbol read is %d\n", *sym);
    printf("true or false: %d\n", bytes_read);
    if (bytes_read == 1) { //succesful read, there was a sym to read
        read_buf_pos++;
        total_syms++;
        return true;
    }

    else //unsuccesful read, no more syms left
        return false;
}

void write_bits(uint8_t n, int buf_pos) {
    for (int i = 0; i < 8; i++)
        buffer[buf_pos + i] = ((n >> i) & 1) ? 1 : 0;
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    total_bits += bitlen;
    //write code to buffer, least significant byte first

    //write code to buffer
    write_bits((code >> 8) & 0xFF, buf_pos);
    buf_pos += 8;
    write_bits(code & 0xFF, buf_pos);
    buf_pos += 8;

    if (((buf_pos + 7) / 8) >= BLOCK) {
        write_bytes(outfile, buffer, BLOCK);
        buf_pos = 0;
        memset(buffer, 0, BLOCK); //0s out the memory
    }

    //write symbol to buffer
    write_bits(sym, buf_pos);
    buf_pos += 8;
    total_bits += 8;
    total_syms++;

    if (((buf_pos + 7) / 8) >= BLOCK) {
        write_bytes(outfile, buffer, BLOCK);
        buf_pos = 0;
        memset(buffer, 0, BLOCK); //0s out the memory
    }
}
//make buffer of BLK size
//fill it one byte at a time
//written out to outfile when buffer is full
//then write to buffer again until all data has been written

//code is 2 bytes
//sym is 1 byte

//for fileheader, you're writing out

void flush_pairs(int outfile) {
    printf("\n\nI am in flush pairs. Buf pos is %d\n", buf_pos);
    if (buf_pos > 0 && ((buf_pos + 7) / 8) <= BLOCK) {
        lseek(outfile, 0, SEEK_SET);
        printf("I am about to call write bytes to write %d bytes\n", ((buf_pos + 7) / 8));
        write_bytes(outfile, buffer,
            ((buf_pos + 7) / 8)); //write block to outfile, even though it isn't full
        buf_pos = 0;
        //flush pairs is the last function ran by encode.c
        //we set the buffer to -1, so that in the first call of the
        //first function of decode.c (read_pair), we know it is the first call
        //and we can initialize the buffer!
    }
    free(buffer); //free all my bits!!!!!-
    if (read_buffer != NULL)
        free(read_buffer);
}

//read pair from input file and place code and sym in pointers
//bitlen is the # of bits in the code
// Returns true if there are pairs left to read in the buffer, else false.
//There are pairs left to read if the read code is not STOP_CODE.
//reads one pair from infile, stores in buffer, keeps track of where you are in buffer

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    int bytelen = (bitlen + 7) / 8;
    if (total_syms == 0) {
        read_buffer = malloc(BLOCK);
        read_buf_pos = 0;
        buffer = malloc(BLOCK);
        buf_pos = 0;
        memset(buffer, 0, BLOCK);
        read_block(infile, BLOCK);
    }

    //read code
    for (int i = 0; i < bytelen; i++) {
        code[i] = (uint16_t) read_buffer[read_buf_pos];
        read_buf_pos++;
    }

    total_bits += bitlen;
    if (*code == STOP_CODE)
        return false;

    if (read_buf_pos == BLOCK)
        read_block(infile, BLOCK);

    //read sym
    *sym = read_buffer[read_buf_pos];
    read_buf_pos++;
    total_bits += 8;
    total_syms++;

    if (read_buf_pos == BLOCK)
        read_block(infile, BLOCK);

    return true;
}

void write_word(int outfile, Word *w) {
    // Write symbol to buffer.
    for (uint32_t i = 0; i < w->len; i++) {
        buffer[buf_pos] = w->syms[i];
        //buffer[buf_pos/8] = value stored at (w->syms[i])
        buf_pos++; //sym is 8 bits
        total_bits += 8;
        total_syms++;
        if (buf_pos == BLOCK) {
            write_bytes(outfile, buffer, BLOCK);
            buf_pos = 0;
            memset(buffer, 0, BLOCK); //0s out the memory
        }
    }
}

void flush_words(int outfile) {
    flush_pairs(outfile);
}

/*
int main (){
    int file2 = open("file2.txt", O_RDWR | O_CREAT, 0666);  
    int file_r = open("result.txt", O_RDWR, 0666); 
    //test functionality of encode.c
    if (file_r == -1) {
        perror("open error");
        return 1;
    }
    uint8_t * sym = malloc(1);
    read_sym(file2, sym);

    uint16_t code = 2;
    uint8_t curr_sym = 97;
    for (int i = 0; i < 400; i++) {
        write_pair(file_r, code, curr_sym, sizeof(code));
        code ++;
        curr_sym++;
    }

    //flush_pairs(file_r);

    close(file2);
    close(file_r);
    return 0;
}
*/
