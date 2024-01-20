# Implementação de um versão do comando Linux `ls`


## Preparação

Estudo das seguintes funções:

| Função | Estudo |
|---    |---|
|write|ok |
|opendir| ok |
|readdir| ok |
|closedir| ok |
|stat| ok |
|lstat| ok |
|getpwuid| ok |
|getgrgid| ok |
|listxattr| ok |
|getxattr| ok |
|time| ok |
|ctime| ok |
|readlink| ok |
|malloc| ok |
|free| ok |
|perror| ok |
|strerror| ok |
|exit| ok |
|---|---|

## Opções a serem implementadas

- -a : Lista todos os arquivos do diretório (inclusive os arquivos ocultos);
- -l : Lista permissões, número de entidades (se for diretório, mostra a quantidade de subdiretórios existentes dentro dele; se for arquivo, mostra o número de referências que apontam para o arquivo), dono, grupo, tamanho do arquivo, data e hora da última atualização e o nome do arquivo;
- -r : Lista em ordem reversa;
- -t : Lista os arquivos por ordem decrescente das datas de atualização
- -R : Lista diretórios e subdiretórios recursivamente.



## Implementação

- [ ] Implementar versão simples
- [ ] Implementar opção `-a`
- [ ] Implementar opção `-R`
- [ ] Implementar opção `-l`
- [ ] Implementar opção `-r`
- [ ] Implementar opção `-t`

# Referências
- https://www.youtube.com/watch?v=j9yL30R6npk
- https://iq.opengenus.org/ls-command-in-c/
- https://betterprogramming.pub/how-does-ls-work-14fdc2b85308
- https://www.maizure.org/projects/decoded-gnu-coreutils/ls.html
- https://medium.com/@bdov_/https-medium-com-bdov-how-does-the-shell-command-ls-work-internally-11ea701fa1d2
- https://github.com/9fans/plan9port/blob/master/src/cmd/ls.c
- https://sites.uclouvain.be/SystInfo/usr/include/dirent.h



