# Trabajo Práctico 0: Programación C++

## Instalacion

Los siguientes requerimientos son necesarios

#### Descarga del codigo fuente

#### Via ssh keys
```
git clone git@github.com:ruso86/tp1-algo2.git
```
> Requiere cuenta en [GitHub](https://github.com/)

#### Via https
```
git clone https://github.com/ruso86/tp1-algo2
```
> Requiere cuenta en [GitHub](https://github.com/)

#### Zip file
- [Descargar ZIP file](https://github.com/ruso86/tp1-algo2/archive/master.zip)


## Compilacion

```bash
g++ ./main.cpp -o ./bin/tp1
```

## Uso

```bash
$ ./bin/tp1 -h
> tp1 [-m method=DFT] [-i file=ISTREAM] [-o file=OSTREAM]
$
$ ./bin/tp1 -i ./test/ones.input.txt -o ./test/ones.output.txt
> # Procesa desde archivo  entrada e imprime a archivo salida
>
$ ./bin/tp1 -i ./test/ones.input.txt
> # Procesa archivo e imprime a ostream
>
$ ./bin/tp1 -o ./test/ones.output.txt
> # Procesa iostream e imprime en archivo salida
> # luego de encontrar [ctrl + D] (EOF)
>
$ ./bin/tp1 -m IDFT
> # Marca modo como IDFT
```

## Links
### VSCode
 - [VS Code: C++ Development With Visual Studio Code](https://www.youtube.com/watch?v=X7CXjKGi_ro)
