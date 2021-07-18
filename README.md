# chpe_example

## How to make CHPE
1. [Download EWDK](https://docs.microsoft.com/windows-hardware/drivers/develop/using-the-enterprise-wdk). Launch it.  
2. - (a) Download [CHPE.targets](CHPE.targets). put project dir.  
     or
   - (b) Modify the .sln/.vcxproj file yourself to allow ``$(Platform) == CHPE``.  
     - \[MUST\] Remove 'odbccp32.lib' from ``Additional Dependencies``. Does not exist.
     - \[MUST\] Set the ``Windows SDK Version`` to ``$(Version_Number)``. The EWDK environment has a separate Windows SDK.
     - \[MAY\] Change ``Platform Toolset``.
     - \[I Recommend\] Change ``Output Directory`` and ``Intermediate Directory``. By default it mixes with x86. 
     - \[For DEBUG\] Disable ``Optimization``. The default value is on.
     - \[For DEBUG\] Change ``Debug Information Format`` to other than ``Program Database for Edit And Continue``. ``Control Flow Guard`` cannot be turned off.
     - \[For DEBUG\] Disable ``Support Just My Code Debugging``. If do not turn it off, will get an internal compiler error.
3. - (a) Run ``msbuild CHPE.targets /p:WindowsTargetPlatformVersion=%Version_Number% /p:Platform=CHPE /p:Configuration=Release /p:ProjectName=<your_project_name>``
   - (b-1) Run ``msbuild <your_project> /p:Platform=CHPE /p:Configuration=Release``.  
           or
   - (b-2) 1. Run ``SetupVSEnv``.
           2. Run ``start devenv``.
           3. Build in VS.

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

``Project Properties -> Advanced -> Build Project as ARM64X``

| | ARM64EC | ARM64X |
| --- | --- | --- |
| Machine | IMAGE_FILE_MACHINE_AMD64 | IMAGE_FILE_MACHINE_ARM64 |
| Loadable Process | x64 | x64<br>ARM64 |
