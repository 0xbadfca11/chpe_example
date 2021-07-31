#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include <filesystem>

void f()
#ifdef _M_HYBRID
{
	puts(
		"EXE:  (CHPE"
#if defined(_M_HYBRID_X86_ARM64)
		"/ARM64)"
#elif defined(_M_HYBRID_X86)
		"/x86)"
#endif
	);
	__asm ret
}
#endif
;
int main()
{
	puts(
		"EXE: "
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

#ifdef _M_HYBRID
	f();
#endif

	std::filesystem::current_path("..");

	const std::filesystem::path dirs[] = {
		"./",
		"./x64",
		"./ARM64",
		"./ARM64EC",
		"./CHPE"
	};

	for (auto&& dir : dirs)
	{
		auto dll_path = dir /
#ifdef _DEBUG
			"Debug"
#else
			"Release"
#endif
			"/chpe_dll.dll";
		if (auto dll = LoadLibraryW(dll_path.c_str()))
		{
			auto f1 = reinterpret_cast<void(*)()>(GetProcAddress(dll, "f1"));
			auto f2 = reinterpret_cast<void(*)()>(GetProcAddress(dll, "f2"));
			if (f1)
			{
				_putws(dll_path.c_str());
				f1();
			}
			if (f2)
			{
				f2();
			}
		}
	}
}