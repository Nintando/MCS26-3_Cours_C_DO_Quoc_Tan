#include "ip2si.h"

char *ip_strdup(char *src) {
    char *dest;
    size_t len;

    if (!src)
        return (NULL);

    len = ip_strlen(src);
    dest = (char *)malloc(sizeof(char) * (len + 1));

    if (!dest)
        return (NULL);

    for (size_t i = 0; i <= len; i++) {
        dest[i] = src[i];
    }
    return (dest);
}
