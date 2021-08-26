# chpe_example

## How to make CHPE
1. Modify the .sln/.vcxproj file yourself by text editor to allow ``$(Platform) == CHPE``.  
2. [Download EWDK](https://docs.microsoft.com/windows-hardware/drivers/download-the-wdk#enterprise-wdk-ewdk).  
3. Open Visual Studio through ``SetupVSEnv`` in EWDK environment.  
4. Open modified .sln or .vcxproj from SetupVSEnv-ed VS. (Don't open from explorer)  
5. Make additional project settings.  
   - \[MUST\] Remove ``odbccp32.lib`` from ``Linker`` -> ``Input`` -> ``Additional Dependencies``. It's not exist.
   - \[MUST\] Set the ``General`` -> ``Windows SDK Version`` to ``$(Version_Number)``. The EWDK environment use discrete Windows SDK.
     - [Can use the Condition element to share project in both EWDK and non-EWDK environments](chpe_exe/chpe_exe.vcxproj#L51).  
   - \[MAY\] Change ``General`` -> ``Platform Toolset``.
   - \[I Recommend\] Change ``General`` -> ``Output Directory`` and ``Intermediate Directory``. By default it mixes with x86.
   - \[For DEBUG\] Disable ``C/C++`` -> ``Optimization`` -> ``Optimization``. The default value is on.
   - \[For DEBUG\] Change ``C/C++`` -> ``General`` -> ``Debug Information Format`` to other than ``Program Database for Edit And Continue``. ``Control Flow Guard`` cannot be turned off.
   - \[For DEBUG\] Disable ``C/C++`` -> ``General`` -> ``Support Just My Code Debugging``. If do not turn it off, will get an internal compiler error.
   - \[For DLL\] Disable ``Advanced`` -> ``Whole Program Optimization`` or Add ``/NOIMPLIB`` to ``Linker`` -> ``Command Line`` ->  ``Additional Options``. If do not, will get ``LINK : fatal error LNK1376: /DLL and /WOWA64 are incompatible when producing an import library. Generate the import library separately.``

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

## a
CHPE is compiled twice. As x86, and as ARM64. X86 is used for parts that could not be compiled as ARM64 on a function-by-function (such as containg inline assembler or intrinsic function).
