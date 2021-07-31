#include <cstdio>
#include <intrin.h>

void f1()
{
	puts(
		"DLL: "
#if defined(_M_IX86)
		"x86"
#ifdef _M_HYBRID
		" (CHPE"
#elif defined(_M_HYBRID_X86_ARM64)
		"/ARM64)"
#elif defined(_M_HYBRID_X86)
		"/x86)"
#endif
#elif defined(_M_X64)
		"x64"
#ifdef _M_ARM64EC
		" (ARM64EC)"
#endif
#elif defined(_M_ARM64)
		"ARM64"
#elif defined(_M_ARM64EC)
		"ARM64EC"
#elif defined(_M_ARM)
		"ARM"
#endif
	);
}
void f2()
{
#ifdef _M_HYBRID
	puts(
		"EXE:  (CHPE"
#if defined(_M_HYBRID_X86_ARM64)
		"/ARM64)"
#elif defined(_M_HYBRID_X86)
		"/x86)"
#endif
	);
	__asm ret
#endif
}