#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "code.h"

//decompression is done with a WordTable
//size of WordTable is MAX_CODE aka UNIT16_MAX
//index for WordTable goes from EMPTY_CODE to MAX_CODE
//first element of WordTable is EMPTY_CODE (1)
//first element of WordTable the can store smt is START_CODE (2)
//typedef struct Word {
//    uint8_t *syms;
//    uint32_t len;
//} Word;

//typedef Word * WordTable;

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *word = (Word *) malloc(sizeof(Word));
    if (word == NULL) {
        return NULL;
    }

    uint8_t *temp = (uint8_t *) malloc(sizeof(uint8_t) * len);
    if (temp == NULL) {
        free(word);
        return NULL;
    }

    memcpy(temp, syms, sizeof(uint8_t) * len); //copies array passed in as *syms to temp
    word->syms = temp;
    word->len = len;
    return word;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    //append the Word w with sym
    //what about length? we change it, but how do we know the length of sym
    //listPointer->array = realloc(listPointer->array, 2*(list->size)*sizeof(void *));
    Word *new_word = (Word *) malloc(sizeof(Word));
    if (new_word == NULL)
        return NULL; // Error: failed to allocate memory

    new_word->len = w->len + 1;
    uint8_t *temp = (uint8_t *) malloc(sizeof(uint8_t) * new_word->len);
    if (temp == NULL) {
        free(new_word);
        return NULL;
    }
    if (w->syms != NULL) {
        memcpy(temp, w->syms, sizeof(uint8_t) * w->len);
    }
    temp[new_word->len - 1] = sym;
    new_word->syms = temp;
    free(w->syms);
    free(w);
    return new_word;
}

void word_delete(Word *w) {
    //delete a single word
    //delete sym, len
    free(w->syms);
    free(w);
}

WordTable *wt_create(void) {
    //intializes WordTable
    //0th element is set at index EMPTY_CODE. It is an empty word of length 0
    WordTable *wt = (Word **) malloc(MAX_CODE * sizeof(Word *));
    for (uint16_t i = 0; i < MAX_CODE; i++)
        wt[i] = NULL;
    uint8_t sym = { 32 }; //see if this works, previously sym = {32}
    Word *w = word_create(&sym, 0);
    wt[EMPTY_CODE] = w;
    return wt;
}

void wt_reset(WordTable *wt) {
    //resets a WordTable to contain only an empty word at index 0
    //all other words are set to NULL
    for (int i = 0; i < MAX_CODE; i++)
        wt[i] = NULL;
    uint8_t sym = { 32 };
    Word *w = word_create(&sym, 1);
    wt[EMPTY_CODE] = w;
}

void wt_delete(WordTable *wt) {
    //deletes whole WordTable
    for (int i = 0; i < MAX_CODE; i++) {
        if (wt[i] != NULL)
            word_delete(wt[i]);
    }
    free(wt);
}
