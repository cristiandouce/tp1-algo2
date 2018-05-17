set testPath=C:\Users\daj\ProyectosVSC\tp1-algo2\tp1-algo2\test
set  binPath=C:\Users\daj\ProyectosVSC\tp1-algo2\tp1-algo2\bin

del %testPath%\*_fft.txt
del %testPath%\*_ifft.txt
pause

rem Tests nuestros

%binPath%\tp1.exe -i %testPath%\TestCantidad.txt -o %testPath%\TestCantidad_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TestCantidad_fft.txt -o %testPath%\TestCantidad_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato1.txt -o %testPath%\TestFormato1_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato1_fft.txt -o %testPath%\TestFormato1_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato2.txt -o %testPath%\TestFormato2_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato2_fft.txt -o %testPath%\TestFormato2_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato3.txt -o %testPath%\TestFormato3_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato3_fft.txt -o %testPath%\TestFormato3_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato4.txt -o %testPath%\TestFormato4_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TestFormato4_fft.txt -o %testPath%\TestFormato4_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea1.txt -o %testPath%\TestLineaErronea1_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea1_fft.txt -o %testPath%\TestLineaErronea1_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea2.txt -o %testPath%\TestLineaErronea2_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TestLineaErronea2_fft.txt -o %testPath%\TestLineaErronea2_ifft.txt -m IFFT
pause

rem Tests catedra
%binPath%\tp1.exe -i %testPath%\TPulso.txt -o %testPath%\TPulso_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TPulso_fft.txt -o %testPath%\TPulso_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\Frecuencia1.txt -o %testPath%\Frecuencia1_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\Frecuencia1_fft.txt -o %testPath%\Frecuencia1_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\TFrecuencia3B.txt -o %testPath%\TFrecuencia3B_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\TFrecuencia3B_fft.txt -o %testPath%\TFrecuencia3B_ifft.txt -m IFFT
pause

%binPath%\tp1.exe -i %testPath%\Tbwavfs11025.txt -o %testPath%\Tbwavfs11025_fft.txt -m FFT
pause

%binPath%\tp1.exe -i %testPath%\Tbwavfs11025_fft.txt -o %testPath%\Tbwavfs11025_ifft.txt -m IFFT
pause
