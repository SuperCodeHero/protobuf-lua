#ifndef TOOL_H_
#define TOOL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

char toHexChar(uint8_t val);
uint8_t HexCharToSrc(char c);

const char *toHexString(char *des, const char *src, uint32_t len);

const char *toHexBinary(char *des, const char *src, uint32_t len);

const char *parseVarint64(const char *p, const char *end, uint64_t *v);

const char *parseLengthDelimited(const char *p, const char *end, char *v, uint32_t *vn);

char *serialint64(char *p, uint64_t v);

char *serialLengthDelimited(char *p, const char *v, uint32_t vn);


#ifdef __cplusplus
}
#endif

#endif