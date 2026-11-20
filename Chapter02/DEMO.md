# Demonstração do exercício 5

Estado original preservado no commit `5e59b20d2e662914e580338729632f1eb204f95c`.

Na raiz do repositório:

```sh
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target Chapter02 -j 2
./cmake-build-debug/Chapter02/Chapter02
```

Espaço pausa o movimento e o tempo de vida. R reinicia a cena. Esc sai.
A partícula desaparece em 2 segundos de simulação; o timer invisível expira em 3.
O bloco segue em linha reta e pode sair da tela; pressione R para recomeçar.
Não há colisões neste exercício. Os atores mortos ficam alocados, mas não atualizam nem desenham.

Actor possui componentes por unique_ptr. Component acessa o dono por ponteiro não proprietário.
Update muda o estado; Draw apenas lê. Componentes de mesma prioridade preservam a ordem de inserção.

Para voltar apenas o capítulo ao ponto anterior (isso substitui os arquivos do capítulo):

```sh
git restore --source=5e59b20d2e662914e580338729632f1eb204f95c --staged --worktree -- Chapter02
```

Antes de restaurar, salve suas próprias alterações em um commit se quiser preservá-las.
A demonstração pode ser recuperada pelo commit com a mensagem `feat: demonstrate exercise 5 with SDL3 actors and components`.
