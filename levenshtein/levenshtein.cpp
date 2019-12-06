#include "string.h"
#include "stdlib.h"
#include "math.h"
#include <ctype.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

__declspec(dllexport) int __stdcall levenshtein(char *s1, char *s2) {
    size_t s1len, s2len, maxLen;
    unsigned int x, y, lastdiag, olddiag;
	unsigned int *column;
	int ldistance;

	s1len = strlen(s1);
    s2len = strlen(s2);
	column = (unsigned int*)malloc(sizeof(unsigned int)*(s1len+1));
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
	ldistance = column[s1len];
	free(column);

	maxLen = s1len > s2len ? s1len : s2len;
    ldistance = (int)ceil(((1 - ((float)ldistance / (float)maxLen)) * 100));

    return(ldistance);
}

/*
__declspec(dllexport) int __stdcall levenshtein(char *fstStr, char *secStr) {

    // 获取字符长度
    size_t fstLen = strlen(fstStr);
    size_t secLen = strlen(secStr);
    char fstChar, secChar;
    char *secBegin;
    int i, j, x, y, left, top, leftTop, maxLen;

    // 初始化二维表
    fstLen++;
    secLen++;
    unsigned int **charTable = new int[fstLen][secLen];

    charTable[0][0] = 0;

    for (i = 0; i < fstLen; i++) {
        charTable[i][0] = i;
    }

    for (i = 0; i < secLen; i++) {
        charTable[0][i] = i;
    }

    fstLen--;
    secLen--;

    secBegin = secStr;
    for (i = 1; i <= fstLen; i++) {

        x = i - 1;
        fstChar = *fstStr;
        fstStr++;

        secStr = secBegin;
        for (j = 1; j <= secLen; j++) {
            y = j - 1;
            secChar = *secStr;
            secStr++;

            left = charTable[x][j] + 1;
            top = charTable[i][y] + 1;
            leftTop = fstChar == secChar ? charTable[x][y] : charTable[x][y] + 1;

            charTable[i][j] = left < top ? (left < leftTop ? left : leftTop) : (top < leftTop ? top : leftTop);
        }
    }

    maxLen = fstLen > secLen ? fstLen : secLen;

    maxLen = (int)((1 - ((float)charTable[fstLen][secLen] / (float)maxLen)) * 100);

    return maxLen;
}
*/

#ifdef __cplusplus
}
#endif
