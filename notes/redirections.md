## Brincando com redirecionamentos
`ls > outfile`
`< outfile wc`

## Outras dicas
Para sair do modo "inline" do `wc`, tecle `Ctrl+d`

Contar quantos arquivos tem no diretório:

`./pipex infile "ls" "wc -l" outfile`

Formas de testar:
../pipex "assets/deepthought.txt" "grep Now" "head -2" "outs/test-xx.txt"

## Comandos que nao existem

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < infile cat | opa -s > outfile
zsh: command not found: opa
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % echo $?
127

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < infile opa -s | wc -w > outfile
zsh: command not found: opa
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % echo $?
0

- Se o primeiro comando não existe, o segundo nem é executado.

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < infile grep Now | /usr/bin/cat > outfile
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % echo $?
0

almarcos@c2r11p1: ~/repos_cloned/tolmvad_pipex % < infile grep 42 | /usr/bin/cat > outfile
almarcos@c2r11p1: ~/repos_cloned/tolmvad_pipex % echo $?
0

O pipex precisa retornar o exit code do último comando.

## Arquivos que não existem

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < nao_existe wc -l | cat > outfile
zsh: no such file or directory: nao_existe
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % echo $?                           
0

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < execve.c wc -l | cat > nao_existe
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % echo $?                            
0

***Se o arquivo de input nao existir, apresente um erro. Se o arquivo de output nao existir, crie ele.***

Você precisa ter permisão de leitura para ver o conteudo do outfile e infile.

## Permisões nos arquivos infile e outfile

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % chmod 200 infile                   
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < infile grep Now | wc -w > outfile
zsh: permission denied: infile
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % echo $?
0

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % chmod 400 outfile                 
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < infile grep Now | wc -w > outfile
zsh: permission denied: outfile

Precisamos ter, no mínimo, permisão de leitura do infile e permisão de escrita no outfile, caso não tenhamos, apresente a mensagem de erro "permission denied".

Quando não temos as permisões mínimas para ambos os arquivos:

almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % < infile grep Now | wc -w > outfile
zsh: permission denied: infile
zsh: permission denied: outfile
almarcos@c2r11p1: ~/repos_cloned/my_pipex/tmp % echo $?
1
