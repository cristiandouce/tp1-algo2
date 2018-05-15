set testPath=C:\Users\daj\ProyectosVSC\tp1-algo2\tp1-algo2\test
set  binPath=C:\Users\daj\ProyectosVSC\tp1-algo2\tp1-algo2\bin

del %testPath%\*_dft.txt
del %testPath%\*_idft.txt

pause

rem Tests nuestros

%binPath%\tp1.exe -i "%testPath%\TestCantidad.txt" -o "%testPath%\TestCantidad_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TestCantidad_dft.txt -o %testPath%\TestCantidad_idft.txt -m IDFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato1.txt -o %testPath%\TestFormato1_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TestFormato1_dft.txt -o %testPath%\TestFormato1_idft.txt -m IDFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato2.txt -o %testPath%\TestFormato2_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TestFormato2_dft.txt -o %testPath%\TestFormato2_idft.txt -m IDFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato3.txt -o %testPath%\TestFormato3_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TestFormato3_dft.txt -o %testPath%\TestFormato3_idft.txt -m IDFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato4.txt -o %testPath%\TestFormato4_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TestFormato4_dft.txt -o %testPath%\TestFormato4_idft.txt -m IDFT
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea1.txt -o %testPath%\TestLineaErronea1_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea1_dft.txt -o %testPath%\TestLineaErronea1_idft.txt -m IDFT
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea2.txt -o %testPath%\TestLineaErronea2_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea2_dft.txt -o %testPath%\TestLineaErronea2_idft.txt -m IDFT
pause

rem Tests catedra
%binPath%\tp1.exe -i %testPath%\TPulso.txt -o %testPath%\TPulso_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TPulso_dft.txt -o %testPath%\TPulso_idft.txt -m IDFT
pause


%binPath%\tp1.exe -i %testPath%\Frecuencia1.txt -o %testPath%\Frecuencia1_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\Frecuencia1_dft.txt -o %testPath%\Frecuencia1_idft.txt -m IDFT
pause

%binPath%\tp1.exe -i %testPath%\TFrecuencia3B.txt -o %testPath%\TFrecuencia3B_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\TFrecuencia3B_dft.txt -o %testPath%\TFrecuencia3B_idft.txt -m IDFT
pause


%binPath%\tp1.exe -i %testPath%\Tbwavfs11025.txt -o %testPath%\Tbwavfs11025_dft.txt
pause

%binPath%\tp1.exe -i %testPath%\Tbwavfs11025_dft.txt -o %testPath%\Tbwavfs11025_idft.txt -m IDFT
pause