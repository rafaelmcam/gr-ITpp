IT++ no GNU Radio (Resultados)
=============================

Branch principal de blocos testes/experimentos/resultados. 



## Curva de BER para BPSK - Hamming

![Overview](/examples/Scripts%20Python/BerCurve_Hamming.png)




Transferência de Imagem SIMULADA - Sem Tratamento de Recepção Extra.      |  
:-------------------------:|
![](examples/Scripts&#32;Python/Scripts/BPSK&#32;-&#32;Sem&#32;Correlate/script_images.png) |  


Transferência de Imagem SIMULADA - Usando Mini Preambles + Header + Correlate.      |  
:-------------------------:|
![](examples/Scripts&#32;Python/Scripts/BPSK&#32;-&#32;Com&#32;Correlate/script_images_red_dot.png) |  


Transferência de Imagem SIMULADA - Usando Mini Preambles + Header + Correlate.      |  
:-------------------------:|
![](examples/Scripts&#32;Python/Scripts/BPSK&#32;-&#32;Com&#32;Correlate/script_images.png) |  





IT++ no GNU Radio (Instruções)
=============================



# Resolver warning do Xinithreads (talvez apenas ubuntu 18):

O gnuradio procura por um arquivo "libX11.so" que aparentemente não é padrão no ubuntu 18 (só vem com a versão "libX11.so.6"), instalar esse arquivo com:

sudo apt install libx11-dev


# Instalar documentação do gnuradio offline:
sudo apt install gnuradio-doc

e procurar pela pasta gnuradio-doc (meu pc é usr/share/doc/gnuradio-doc), subpasta html e abrir o arquivo index.html

No meu pc é o mesmo que copiar o link abaixo e abrir em um navegador: file:///usr/share/doc/gnuradio-doc/html/index.html

# Requisito biblioteca ITpp

sudo apt install libitpp-dev

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

# 3 formas de testar a instalação do módulo 
-> Dentro da pasta build executar:

make test (Ver se todos os testes são completados, "100% tests passed")

-> (Teste mais importante!!!) Em qualquer pasta, abrir um terminal:

python2

import ITpp

help(ITpp)

Espera-se que quando der o help(ITpp), a seção "Package Contents" possua: ITpp_swig, _ITpp_swig e dentro da seção "Functions" possua referências aos blocos instalados até então (exemplo: "Hamming_Encoder_sptr_swigregister(...)"). Se não tiver essas referências provavelmente vai dar o erro:
'module' object has no attribute "bloco". E o problema deve ser com o "swig" ou "pkg-config".

-> Dentro da pasta "examples" executar algum dos arquivos *.grc 