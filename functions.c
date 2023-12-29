#include "functions.h"


void ending(struct Text t){
    for (int i = 0;i < t.n;i++) {
        for (int j = 0; j < t.array[i]->len-3; j++) {
            if ((t.array[i]->str[j] == L'т') && (t.array[i]->str[j+1] == L'ь') && (t.array[i]->str[j+2] == L'с') && (t.array[i]->str[j+3] == L'я')){
                wmemmove(&t.array[i]->str[j+1],&t.array[i]->str[j+2],(t.array[i]->len-j-1));
                t.array[i]->len = t.array[i]->len-1;
                j+=3;
            }
            if ((t.array[i]->str[j] == L'т') && (t.array[i]->str[j+1] == L'с') && (t.array[i]->str[j+2] == L'я')){
                wmemmove(&t.array[i]->str[j+2],&t.array[i]->str[j+1],(t.array[i]->len-j-1));
                t.array[i]->str[j+1]=L'ь';
                t.array[i]->len = t.array[i]->len+1;
            }
        }
    }
}
void moreten(struct Text *t){
    for (int i = 0;i<t->n;i++){
        if (t->array[i]->countwords>10){
            free(t->array[i]);
            memmove(&t->array[i], &t->array[i + 1], sizeof(struct Sentence *) * (t->n - i - 1));
            t->n-=1;
        }
    }
}
int cmp(const void* sent1,const void* sent2){
    struct Sentence *f = *(struct Sentence **) sent1;
    struct Sentence *s = *(struct Sentence **) sent2;
    int amount1 = f->countwords;
    int amount2 = s->countwords;
    if(amount1<amount2)
        return -1;
    if (amount1>amount2)
        return 1;
    return 0;
}

int greenword(struct Text t){
    wchar_t *temp = (wchar_t *) malloc((t.array[0]->len+1)* sizeof(wchar_t));
    wcscpy(temp,t.array[0]->str);
    wchar_t* pt;
    wchar_t* token = wcstok(temp, L" \t\n,.;:",&pt);
    token = wcstok(NULL, L" \t\n,.;:", &pt);
    if (token==NULL){
        return 0;
    }
    wchar_t*** words = arrofwords(t);
    wchar_t*** seps = arrofseps(t);
    for (int i = 0;i<t.n;i++){
        if (check(i,words,token,t)==1){
            for (int j = 0;j<t.array[i]->countwords;j++) {
                if (wcscmp(words[i][j], token) == 0){
                    wprintf(L"%s%ls",GREEN,words[i][j]);
                }else {
                    wprintf(L"%s%ls",NONE,words[i][j]);
                }
                wprintf(L"%s%ls",NONE,seps[i][j]);

            }
            wprintf(L"\n");
            }
        }
    return 1;
}
int check(int i,wchar_t*** words,wchar_t* token,struct Text t){
    for (int j = 0;j<t.array[i]->countwords;j++){
        if (wcscmp(words[i][j], token) == 0)
            return 1;
    }
    return 0;
}
void freeText(struct Text t) {
    for (int i = 0; i < t.n; i++) {
        free(t.array[i]->str);
        free(t.array[i]);
    }
}
wchar_t*** arrofwords(struct Text t){
    wchar_t*** words = malloc(sizeof(wchar_t *)*t.n);
    for (int i = 0;i < t.n;i++){
        words[i] = malloc(sizeof(wchar_t *)*t.array[i]->countwords);
        int countwords = 0;
        wchar_t* pt;
        wchar_t *temp = (wchar_t *) malloc((t.array[i]->len+1) * sizeof(wchar_t));
        wcscpy(temp,t.array[i]->str);
        wchar_t *pch = wcstok(temp,L" ,\t.\n;:",&pt);
        while (pch!=NULL){
            words[i][countwords] = pch;
            countwords++;
            pch = wcstok(NULL,L" ,\t.\n;:",&pt);
        }
    }
    return words;
}
wchar_t*** arrofseps(struct Text t){
    wchar_t*** seps = malloc(sizeof(wchar_t *)*t.n);
    wchar_t alphabet[] = L"1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNMёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
    for (int i = 0;i < t.n;i++){
        seps[i] = malloc(sizeof(wchar_t *)*t.array[i]->countwords);
        int countseps = 0;
        wchar_t* pt;
        wchar_t *temp = (wchar_t *) malloc((t.array[i]->len+1) * sizeof(wchar_t));
        wcscpy(temp,t.array[i]->str);
        wchar_t *pch = wcstok(temp,alphabet,&pt);
        while (pch!=NULL){
            seps[i][countseps] = pch;
            countseps++;
            pch = wcstok(NULL,alphabet,&pt);
        }
    }
    return seps;
}
