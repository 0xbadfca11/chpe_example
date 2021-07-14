# chpe_example

## Predefined macros

### By compiler

| | X86 | X64 | CHPE<br>(x86) | CHPE<br>(ARM64) | ARM64 | ARM64EC |
| --- | --- | --- | --- | --- | --- | --- |
| \_M_IX86 | defined | | defined | defined |
| \_M_X64<br>\_M_AMD64 | | defined | | | | defined |
| \_M_HYBRID | | | defined | defined | | |
| \_M_HYBRID_X86 | | | defined | | |
| \_M_HYBRID_X86_ARM64 | | | | defined | | |
| \_M_ARM64 | | | | | defined | |
| \_M_ARM64EC | | | | | | defined |
| \_WIN64 | | defined | | | defined | defined |

### By msbuild

| | X86 | X64 | CHPE<br>(x86) | CHPE<br>(ARM64) | ARM64 | ARM64EC
| --- | --- | --- | --- | --- | --- | --- |
| \_CHPE_<br>\_CHPE_X86_ARM64_<br>i386<br>\_X86_ | | | defined | defined | | |
| ARM64EC<br>\_ARM64EC_<br>AMD64<br>\_AMD64_ | | | | | | defined |

