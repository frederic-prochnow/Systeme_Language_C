#ifndef __CHAINES_H__
#define __CHAINES_H__

int   mon_strlen(const char *s);
int   mon_strcmp(const char * s1, const char * s2);
int   mon_strncmp(const char * s1, const char * s2, int n);
char *mon_strcat(char *s1, const char *s2);

const char *mon_strchr(const char *s, int c);
const char *mon_strstr(const char *haystack, const char *needle);



#endif
