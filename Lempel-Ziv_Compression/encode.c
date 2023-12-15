#include "trie.h"
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

//add verbose print option
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
            break;
        case 'v': verbose = true; break;
        case 'h':
            printf("SYNOPSIS\n\tCompresses files using the LZ78 compression "
                   "algorithm.\n\tCompressed files are decompressed with the corresponding "
                   "decoder.\n\nUSAGE\n\t./encode [-vh] [-i input] [-o output]\n\nOPTIONS\n\t-v    "
                   "      Display compression statistics\n\t-i input    Specify input to compress "
                   "(stdin by default)\n\t-o output   Specify output of compressed input (stdout "
                   "by default)\n\t-h          Display program help and usage");
            return 0;
        }
    }

    struct FileHeader *fd_ptr, fd;
    fd_ptr = &fd;
    fd_ptr->magic = 0xBAADBAAC;
    fd_ptr->protection = st.st_mode;
    write_header(outfile, fd_ptr);

    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    TrieNode *next_node = NULL;
    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = START_CODE;
    while (read_sym(infile, &curr_sym)) {
        next_node = trie_step(curr_node, curr_sym);
        if (next_node != NULL) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, sizeof(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code++;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }
    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, sizeof(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }
    write_pair(outfile, STOP_CODE, 0, sizeof(next_code));
    flush_pairs(outfile);

    close(infile);
    close(outfile);

    //fseek(infile_fp, 0L, SEEK_END);
    //int infile_sz = ftell(infile_fp);
    //fseek(outfile_fp, 0L, SEEK_END);
    //int outfile_sz = ftell(outfile_fp);
    if (verbose) {
        //printf("Compressed file size: %d bytes\n", infile_sz);
        //printf("Uncompressed file size: %d bytes\n", outfile_sz);
        //printf("Compression ratio: %.2f%%", 100 * (1 - ( ((double)infile_sz) / outfile_sz)));
    }
    return 0;
}
