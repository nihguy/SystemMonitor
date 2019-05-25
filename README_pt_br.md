# Monitor de Sistema em C++

[English](README.md)

### Introdução

Esse projeto foi criado seguindo as [orientações](https://github.com/udacity/CppND-System-Monitor/) da [Nanograduação da Udacity em C++](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). O objetivo deste projeto é oferecer informações sobre todos os processos sendo executados em sua distribuição Linux. Isso é feito por meio da leitura de arquivos fornecidos pelo próprio sistema operacional, criando uma saída no terminal “semelhante” a do consagrado [Htop](https://hisham.hm/htop/).

### Como instalar

** Até o momento, este projeto foi testado apenas no Ubuntu 16.04.6 e no Fedora 29. **

1. Para rodar o projeto, é necessário intalar a biblioteca `ncurses` na sua distribuição linux.

** No Ubuntu **

```shell
apt-get install libncurses5-dev libncursesw5-dev
```

** No Fedora **

```shell
dnf install ncurses-devel
```

1. Para compilar o projeto, crie o diretório `build` e de dentro dele, execute os comandos `cmake` e o `make, como apresentado abaixo. 

```shell
mkdir build && cd $_
cmake .. && make
```

1. Se tudo correr como o esperado, o código compilado será criado dentro da pasta `bin` na raiz do projeto. Para executar o programa, basta rodar o executável `Project` que está dentro dessa pasta.

```shell
cd ../bin
./Project
```
