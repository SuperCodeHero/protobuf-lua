#include "tool.h"

char toHexChar(uint8_t val)
{
	if (val >= 10)
		return 'A' + val - 10;

	return '0' + val;
}

uint8_t HexCharToSrc(char c)
{
    if('A' <= c && c <= 'F')
        return 10 + c - 'A';

    return c - '0';
}

const char* toHexString(char* des, const char *src, uint32_t len)
{
	char* xdes = des;

	for (uint32_t i = 0; i < len; ++i)
	{
		unsigned char c = *src++;
		*des++ = toHexChar(c >> 4);
		*des++ = toHexChar(c & 0xF);
	}
	*des = '\0';

	return xdes;
}

const char* toHexBinary(char* des, const char* src, uint32_t len)
{
	char* xdes = des;

	for (uint32_t i = 0; i < len; ++i)
	{
		unsigned char c = *src++;
		for (int shift = 0; shift < 8; ++shift)
		{
			int tc = (c >> shift) & 1;
			*des++ = tc + '0';
		}
	}

	return xdes;
}

const char* parseVarint64(const char* p, const char *end, uint64_t* v)
{
	uint64_t result = 0;
	for (uint32_t shift = 0; shift < 70 && p < end; shift += 7)
	{
		uint64_t byte = *((const unsigned char*)p);
		p++;

		result |= (byte & 127) << shift;
		if ((byte & 128) == 0)
		{
			*v = result;
			return p;
		}
	}

	return p;
}

const char* parseLengthDelimited(const char* p, const char *end, char* v, uint32_t* vn)
{
	uint64_t len = 0;
	p = parseVarint64(p, end, &len);

	for (uint32_t i = 0; i < len && p < end; ++i)
	{
		*v = *p;
		p++, v++;
	}
	*vn = (uint32_t)len;

	return p;
}

char* serialint64(char* p, uint64_t v)
{
	while (v > 127)
	{
		*p = (v & 127) | 128;
		v >>= 7;
		p++;
	}

	*p = (uint8_t)v;
	p++;
	return p;
}

char* serialLengthDelimited(char* p, const char* v, uint32_t vn)
{
	p = serialint64(p, vn);

	for (uint32_t i = 0; i < vn; ++i)
	{
		*p = *v;
		p++, v++;
	}
	return p;
}