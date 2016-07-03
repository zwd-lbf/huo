#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../base_util.h"
#include <stdbool.h>
#include "string.h"


bool string_is_sane(struct String *s) {
    assert (s != NULL);
    assert(s->length == 0 || s->body != NULL);
    assert(s->length == 0 || s->body[s->length] == 0);
    return true;
}

struct String string_from_char(char c) {
    struct String s = {
        .length = 1,
        .body = ARR_MALLOC(2, char)
    };
    s.body[0] = c;
    s.body[1] = 0;
    assert(string_is_sane(&s));
    return s;
}

struct String string_from_chars(const char *str) {
    struct String s;
    if (str == NULL) {
        s.length = 0;
        s.body = NULL;
    } else {
        int l = strlen(str);
        s.length = l;
        s.body = ARR_MALLOC(l + 1, char);
        strcpy(s.body, str);
        s.body[s.length] = 0;
    }
    assert(string_is_sane(&s));
    return s;
}

void string_concat_to(struct String *to, struct String *from) {
    assert(string_is_sane(from));
    assert(string_is_sane(to));
    int len = to->length;
    to->length += from->length;
    RESIZE(to->body, to->length + 1);
    for(int l = 0; l < from->length; l++){
        to->body[l+len] = from->body[l];
    }
    to->body[to->length] = 0;
    assert(string_is_sane(from));
    assert(string_is_sane(to));
}

int string_contains(char ch, struct String* string){
    assert(string_is_sane(string));
    if(!string->length){ return 0; }
    for(int i = 0; i < string->length; i++){
        if(ch == string->body[i]){
            assert(string_is_sane(string));
            return 1;
        }
    }
    assert(string_is_sane(string));
    return 0;
}

struct String string_copy_stack(struct String *from) {
    assert(string_is_sane(from));
    struct String s = {
        .length = 0,
        .body = NULL
    };
    string_copy_to(&s, from);
    assert(string_is_sane(&s));
    return s;
}

struct String *copy_string_heap(struct String *from) {
    assert(string_is_sane(from));
    struct String *s = malloc(sizeof(struct String));
    s->length = 0;
    string_copy_to(s, from);
    assert(string_is_sane(s));
    return s;
}

void string_copy_to(struct String *to, struct String *from) {
    assert(string_is_sane(from));
    assert(string_is_sane(to));
    if (from->length == 0) {
        RESIZE(to->body, 0);
        to->length = 0;
    } else {
        if (to->length != from->length) {
            RESIZE(to->body, from->length + 1); // 0 byte at end
            strcpy(to->body, from->body);
            to->length = from->length;
        }
    }
    assert(string_is_sane(from));
    assert(string_is_sane(to));
}

bool string_matches(struct String *base, struct String *compare){
    assert(string_is_sane(base));
    assert(string_is_sane(compare));
    if(base->length != compare->length){
        return false;
    }
    int counter = 0;
    while(counter < base->length){
        if(base->body[counter] != compare->body[counter]){
            return false;
        }
        counter++;
    }
    return true;
}

char *string_to_chars(struct String *s) {
    assert(string_is_sane(s));
    if (s->length == 0) {
        return "";
    }
    return s->body;
}
long string_length(struct String *s) {
    assert(string_is_sane(s));
    return s->length;
}
char string_index(struct String *s, long i) {
    assert(string_is_sane(s));
    if (i < 0) {
        ERROR("Negative index");
    }
    if (i >= s->length) {
        ERROR("Index out of range: %li >= %i", i, s->length);
    }
    return s->body[i];
}

unsigned long string_hash_code(struct String *s) {
    // djb2
    unsigned long hash = 5381;
    if (s->length == 0)
        return hash;

    char *pos = s->body;

    while (*pos != 0)
        hash = hash * 33 + *(pos++);

    return hash;
}
unsigned long string_hash_code_vv(void *s) {
    return string_hash_code((struct String *) s);
}

bool string_matches_vv(void *base, void *compare) {
    return string_matches((struct String *) base, (struct String *) compare);
}