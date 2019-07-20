#include "tool.h"

char toHexChar(uint8_t val)
{
	if (val >= 10)
		return 'A' + val - 10;

	return '0' + val;
}

const char* toHexString(char* des, const char *src, size_t len)
{
	char* xdes = des;

	for (size_t i = 0; i < len; ++i)
	{
		unsigned char c = *src++;
		*des++ = toHexChar(c >> 4);
		*des++ = toHexChar(c & 0xF);
	}
	*des = '\0';

	return xdes;
}

const char* toHexBinary(char* des, const char* src, size_t len)
{
	char* xdes = des;

	for (size_t i = 0; i < len; ++i)
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

const char* parseVarint64(const char* p, uint64_t* v)
{
	uint64_t result = 0;
	for (uint32_t shift = 0; shift < 70; shift += 7)
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

	return NULL;
}

const char* parseLengthDelimited(const char* p, char* v, size_t* vn)
{
	uint64_t len = 0;
	p = parseVarint64(p, &len);

	for (size_t i = 0; i < len; ++i)
	{
		*v = *p;
		p++, v++;
	}
	*vn = (size_t)len;

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

char* serialLengthDelimited(char* p, const char* v, size_t vn)
{
	p = serialint64(p, vn);

	for (size_t i = 0; i < vn; ++i)
	{
		*p = *v;
		p++, v++;
	}
	return p;
}