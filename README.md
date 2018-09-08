IT++ no GNU Radio (Em construção)
=============================

![Overview](/README_overview.png)


# Resolver warning do Xinithreads (talvez apenas ubuntu 18):

O gnuradio procura por um arquivo "libX11.so" que aparentemente não é padrão no ubuntu 18 (só vem com a versão "libX11.so.6"), instalar esse arquivo com:

sudo apt install libx11-dev


# Instalar documentação do gnuradio offline:
sudo apt install gnuradio-doc

e procurar pela pasta gnuradio-doc (meu pc é usr/share/doc/gnuradio-doc), subpasta html e abrir o arquivo index.html

No meu pc é o mesmo que copiar o link abaixo e abrir em um navegador: file:///usr/share/doc/gnuradio-doc/html/index.html


# Observações para instalação do módulo gr-ITpp

provavelmente os cmake list padrões não requerem o swig/pkg-config pois eles não precisam linkar a biblioteca c++ externa com python normalmente, mas pro ITpp isso é necessário.

sudo apt install cmake

sudo apt install pkg-config

sudo apt install swig

(documentação apenas - não obrigatório?) sudo apt install doxygen

sudo apt install git

git clone https://github.com/rafaelmcam/gr-ITpp.git

Dentro da pasta gr-ITpp, fazer o procedimento padrão:


mkdir build

cd build

cmake ../

sudo make (algum erro aparece aqui?)

sudo make install

sudo ldconfig

se aparecer o erro que não pode gerar a documentação deletar a pasta build, depois sudo apt remove doxygen, e repetir o procedimento acima.