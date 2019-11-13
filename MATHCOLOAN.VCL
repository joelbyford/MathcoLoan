<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: MathcoLoan - Win32 (WCE x86) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"X86Dbg/MathcoLoan.res" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "DEBUG" /d "WIN32_PLATFORM_PSPC=310" /d "_X86_" /d "x86" /d "_i386_" /d "_AFXDLL" /r "C:\My Documents\Projects\MathcoLoan\MathcoLoan.rc"" 
Creating temporary file "C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP11.tmp" with contents
[
/nologo /W3 /Zi /Od /D "DEBUG" /D "_i386_" /D UNDER_CE=300 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC=310" /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "_WIN32_WCE_CEPC" /D "_AFXDLL" /FR"X86Dbg/" /Fp"X86Dbg/MathcoLoan.pch" /Yu"stdafx.h" /Fo"X86Dbg/" /Fd"X86Dbg/" /Gs8192 /GF /c 
"C:\My Documents\Projects\MathcoLoan\AmntDetailDlg.cpp"
"C:\My Documents\Projects\MathcoLoan\CeBtnST.cpp"
"C:\My Documents\Projects\MathcoLoan\ChartForm.cpp"
"C:\My Documents\Projects\MathcoLoan\LineGraph.cpp"
"C:\My Documents\Projects\MathcoLoan\LoanCalcs.cpp"
"C:\My Documents\Projects\MathcoLoan\MainFrm.cpp"
"C:\My Documents\Projects\MathcoLoan\MathcoLoan.cpp"
"C:\My Documents\Projects\MathcoLoan\MathcoLoanDoc.cpp"
"C:\My Documents\Projects\MathcoLoan\MathcoLoanView.cpp"
"C:\My Documents\Projects\MathcoLoan\PXLWriter.cpp"
"C:\My Documents\Projects\MathcoLoan\RegisterDlg.cpp"
"C:\My Documents\Projects\MathcoLoan\SchedForm.cpp"
]
Creating command line "cl.exe @C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP11.tmp" 
Creating temporary file "C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP12.tmp" with contents
[
/nologo /W3 /Zi /Od /D "DEBUG" /D "_i386_" /D UNDER_CE=300 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC=310" /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "_WIN32_WCE_CEPC" /D "_AFXDLL" /FR"X86Dbg/" /Fp"X86Dbg/MathcoLoan.pch" /Yc"stdafx.h" /Fo"X86Dbg/" /Fd"X86Dbg/" /Gs8192 /GF /c 
"C:\My Documents\Projects\MathcoLoan\StdAfx.cpp"
]
Creating command line "cl.exe @C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP12.tmp" 
Creating temporary file "C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP13.tmp" with contents
[
/nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"wWinMainCRTStartup" /incremental:yes /pdb:"X86Dbg/MathcoLoan.pdb" /debug /out:"X86Dbg/MathcoLoan.exe" /subsystem:windowsce,3.00 /MACHINE:IX86 
".\X86Dbg\AmntDetailDlg.obj"
".\X86Dbg\CeBtnST.obj"
".\X86Dbg\ChartForm.obj"
".\X86Dbg\LineGraph.obj"
".\X86Dbg\LoanCalcs.obj"
".\X86Dbg\MainFrm.obj"
".\X86Dbg\MathcoLoan.obj"
".\X86Dbg\MathcoLoanDoc.obj"
".\X86Dbg\MathcoLoanView.obj"
".\X86Dbg\PXLWriter.obj"
".\X86Dbg\RegisterDlg.obj"
".\X86Dbg\SchedForm.obj"
".\X86Dbg\StdAfx.obj"
".\X86Dbg\MathcoLoan.res"
]
Creating command line "link.exe @C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP13.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
StdAfx.cpp
Compiling...
AmntDetailDlg.cpp
CeBtnST.cpp
ChartForm.cpp
LineGraph.cpp
LoanCalcs.cpp
MainFrm.cpp
MathcoLoan.cpp
MathcoLoanDoc.cpp
MathcoLoanView.cpp
C:\My Documents\Projects\MathcoLoan\MathcoLoanView.cpp(620) : warning C4101: 'szTrash' : unreferenced local variable
C:\My Documents\Projects\MathcoLoan\MathcoLoanView.cpp(619) : warning C4101: 'szTmpString2' : unreferenced local variable
PXLWriter.cpp
RegisterDlg.cpp
SchedForm.cpp
Generating Code...
Linking...
Creating temporary file "C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP16.tmp" with contents
[
/nologo /o"X86Dbg/MathcoLoan.bsc" 
".\X86Dbg\StdAfx.sbr"
".\X86Dbg\AmntDetailDlg.sbr"
".\X86Dbg\CeBtnST.sbr"
".\X86Dbg\ChartForm.sbr"
".\X86Dbg\LineGraph.sbr"
".\X86Dbg\LoanCalcs.sbr"
".\X86Dbg\MainFrm.sbr"
".\X86Dbg\MathcoLoan.sbr"
".\X86Dbg\MathcoLoanDoc.sbr"
".\X86Dbg\MathcoLoanView.sbr"
".\X86Dbg\PXLWriter.sbr"
".\X86Dbg\RegisterDlg.sbr"
".\X86Dbg\SchedForm.sbr"]
Creating command line "bscmake.exe @C:\DOCUME~1\Joel\LOCALS~1\Temp\RSP16.tmp"
Creating browse info file...
<h3>Output Window</h3>



<h3>Results</h3>
MathcoLoan.exe - 0 error(s), 2 warning(s)
</pre>
</body>
</html>
