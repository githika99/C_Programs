#include "word.h"
#include "io.h"
#include "code.h"
#include "endian.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define OPTIONS "i:o:vh"

//symbol is of type uint8_t *syms
//code is of type uint16_t code

int main(int argc, char **argv) {
    int opt = 0;
    int infile = open("stdin", O_RDONLY);
    //FILE * infile_fp = fopen("stdin", "r");
    int outfile = open("stdout", O_WRONLY | O_CREAT);
    //FILE * outfile_fp = fopen("stdout", "w");
    bool verbose = false;

    struct stat st;
    mode_t new_mode = st.st_mode | S_IRUSR | S_IWUSR;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            if ((infile = open(optarg, O_RDONLY, 0666)) == -1) {
                perror("open");
                return 1;
            }
            if (fstat(infile, &st) == -1) {
                perror("fstat");
                close(infile);
                return 1;
            }

            //set the new file permissions
            if (chmod(optarg, new_mode) == -1) {
                perror("chmod");
                close(infile);
                return 1;
            }
            //FILE * infile_fp = fopen(optarg, "r");
            break;
        case 'o':
            if ((outfile = open(optarg, O_WRONLY | O_CREAT, 0644)) == -1) {
                perror("open");
                exit(1);
            }
            if (chmod(optarg, new_mode) == -1) {
                perror("chmod");
                close(outfile);
                return 1;
            }
            //FILE * outfile_fp = fopen(optarg, "w");
            break;
        case 'v': verbose = true; break;
        case 'h':
            printf("SYNOPSIS\n\tDecompresses files with the LZ78 decompression algorithm.\n\tUsed "
                   "with files compressed with the corresponding encoder.\n\nUSAGE\n\t./decode "
                   "[-vh] [-i input] [-o output]\n\nOPTIONS\n\t-v          Display decompression "
                   "statistics\n\t-i input    Specify input to decompress (stdin by default)\n\t-o "
                   "output   Specify output of decompressed input (stdout by default)\n\t-h        "
                   "  Display program usage");
            return 0;
        }
    }

    struct FileHeader *fd_ptr, fd;
    fd_ptr = &fd;
    read_header(infile, fd_ptr);

    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;

    while (read_pair(infile, &curr_code, &curr_sym, sizeof(next_code))) {
        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        write_word(outfile, table[next_code]);
        next_code++;
        if (next_code == MAX_CODE) {
            wt_reset(table);
            next_code = START_CODE;
        }
        flush_words(outfile);
    }
    close(infile);
    close(outfile);

    //fseek(infile_fp, 0L, SEEK_END);
    //int infile_sz = ftell(infile_fp);
    //fseek(outfile_fp, 0L, SEEK_END);
    //int outfile_sz = ftell(outfile_fp);
    if (verbose) {
        //printf("Compressed file size: %d bytes\n", outfile_sz);
        //printf("Uncompressed file size: %d bytes\n", infile_sz);
        //printf("Compression ratio: %.2f%%", 100 * (1 - ( ((double)outfile_sz) / infile_sz)));
    }

    return 0;
}
