#include "sl.h"


char *load_text_file(const char *filename, int32 &num_bytes_read)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        num_bytes_read = 0;
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    int32 len = ftell(fp);
    if (len < 1)
    {
        num_bytes_read = 0;
        fclose(fp);
        return NULL;
    }
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(len + 1);
    memset(buffer, 0, len + 1);
    num_bytes_read = (int32)fread(buffer, 1, len, fp);
    fclose(fp);
    return buffer;
}

int32 string_split_c(const char *txt, char delim, char ***tokens)
{
    int32 *tklen, *t, count = 1;
    char **arr, *p = (char *)txt;

    while (*p != '\0')
    {
        if (*p++ == delim)
        {
            count += 1;
        }
    }
    t = tklen = (int32_t *)calloc(count, sizeof(int32_t));
    for (p = (char *)txt; *p != '\0'; p++)
    {
        *p == delim ? *t++ : (*t)++;
    }
    *tokens = arr = (char **)malloc(count * sizeof(char *));
    t = tklen;
    p = *arr++ = (char *)calloc(*(t++) + 1, sizeof(char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            *p++ = delim;
            p = *arr++ = (char *)calloc(*(t++) + 1, sizeof(char *));
            txt++;
        }
        else
        {
            *p++ = *txt++;
        }
    }
    free(tklen);
    return count;
}