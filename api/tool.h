#ifndef TOOL_H_
#define TOOL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

char toHexChar(uint8_t val);

const char *toHexString(char *des, const char *src, size_t len);

const char *toHexBinary(char *des, const char *src, size_t len);

const char *parseVarint64(const char *p, uint64_t *v);

const char *parseLengthDelimited(const char *p, char *v, size_t *vn);

char *serialint64(char *p, uint64_t v);

char *serialLengthDelimited(char *p, const char *v, size_t vn);


#ifdef __cplusplus
}
#endif

#endif