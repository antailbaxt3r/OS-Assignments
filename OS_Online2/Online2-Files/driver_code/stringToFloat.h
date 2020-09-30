#ifndef _FLOAT_HEADER_
#define _FLOAT_HEADER_

#define to_float(s, len) (syscall(441, s, len))
extern float getFloat(char * str, int len);
#endif
