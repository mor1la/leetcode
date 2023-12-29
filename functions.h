#pragma once
#include "library.h"

void ending(struct Text t);
void moreten(struct Text *t);
int cmp(const void* sent1,const void* sent2);
int greenword(struct Text t);
int check(int i,wchar_t*** words,wchar_t* token,struct Text t);
wchar_t*** arrofwords(struct Text t);
wchar_t*** arrofseps(struct Text t);
void freeText(struct Text t);
