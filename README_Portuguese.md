[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Prime World Trailer](PW_trailer.png)](https://youtu.be/Fkd-zva4npI)
[Prime World](https://wikipedia.org/wiki/Prime_World) é um jogo de arena de batalha online multiplayer (MOBA) lançado em 2014. O jogo foi desenvolvido em um motor de jogo próprio pela empresa [Nival](http://nival.com/), escrito principalmente em C++.

O jogo consiste em duas partes: Castelo e Batalha. O jogador assume o papel de Lorde ou Lady. No Castelo, o jogador constrói edifícios, contrata Heróis e escolhe Talentos para eles. Na parte de Batalha, o jogador controla um Herói e, usando Talentos, luta contra outros jogadores em batalhas de equipe.

Em 2024, o código-fonte da parte de Batalha do jogo foi disponibilizado sob uma [licença especial](LICENSE.md), proibindo o uso comercial, mas totalmente aberto para a comunidade de jogos, estudo e fins de pesquisa.
Por favor, leia atentamente os termos do [acordo de licença](LICENSE.md) antes de utilizar.

## O que está neste repositório
- `pw` — código principal da parte de batalha
- `pw_publish` — cliente compilado da parte de batalha com códigos de trapaça e editor para o cliente
- `pw/branches/r1117/Bin/PF_Editor.exe` — editor de dados do jogo

## Preparação
É necessário baixar os dados deste repositório e mesclar a pasta `Bin` com os dados principais do jogo. Veja como fazer isso:

1. Copie a pasta `pw_publish/branch/Client/PvP/Bin` para `pw/branches/r1117`, substituindo os arquivos existentes.
2. Execute o cliente com códigos de trapaça `pw/branches/r1117/Bin/PW_Game.exe`.
3. Se tudo estiver correto, você verá a janela de carregamento, mas sem imagem e apenas com a tela preta.
4. Na pasta `Profiles -> game.cfg`, altere o valor de `local_game 0` para `local_game 1`.
5. Execute o cliente com códigos de trapaça. Agora você deverá ver o lobby, onde poderá selecionar o mapa, herói e iniciar a batalha.
6. No jogo, pressione a tecla Tilde (~) no teclado para abrir o console para digitar os códigos de trapaça.

Se ocorrerem erros, verifique os arquivos de log em `pw/branches/r1117/Bin/logs`.

## Dados do Jogo
Os dados podem ser editados pelo editor e estão localizados em `pw/branches/r1117/Data`

Ao editar os dados, você pode:
1. Alterar descrições de talentos e habilidades dos heróis.
2. Modificar talentos e habilidades dos heróis.
3. Alterar a lógica de tropas (creeps) e torres.
4. Adicionar novos heróis e habilidades.
5. Adicionar novos talentos.
6. Modificar e adicionar efeitos.
7. Modificar e adicionar modelos e animações.

Ao alterar os dados, não é necessário compilar um novo cliente a partir do código. Basta clicar em `File -> Save`, e todas as alterações aparecerão instantaneamente no cliente do jogo `PW_Game`. Como exemplo, você pode tentar alterar a descrição de algum talento ou habilidade de um herói.

## Editor de Dados do Jogo
O editor de dados do jogo está localizado em `pw/branches/r1117/Bin/PF_Editor.exe`

Na primeira vez que abrir o editor, é preciso configurar o caminho para `Data`:
1. `Tools -> File System Configuration`.
2. `Add -> WinFileSystem`.
3. Defina a pasta Data como o system root: `pw/branches/r1117/Data`.
4. Feche as janelas.
5. No editor: `Views -> Object Browser` e `Views -> Properties Editor`. Estes são os dois painéis principais para editar dados.

As abas do editor podem ser movidas e fixadas.

## Cliente do Jogo com Códigos de Trapaça
No repositório você pode encontrar o cliente do jogo já compilado com códigos de trapaça em `pw_publish/branch/Client/PvP/Bin/PW_Game.exe`

É necessário que as pastas `Localization`, `Profiles` e `Data` estejam próximas à pasta `Bin`. Portanto, durante a preparação, é preciso mover para a pasta `pw`. Se o código for alterado, será necessário recompilar o cliente.

## Como Iniciar PvP
1. Em `Profiles -> game.cfg`, altere `local_game 0`.
2. Adicione `login_adress <server address>`.
3. Execute o jogo com o parâmetro `-dev_login MyNickname`.

## Como Iniciar o Jogo com Bots
1. Renomeie o arquivo `Profiles -> private.cfg_example` para `private.cfg`.
2. Abra o arquivo com o Bloco de Notas.
3. Procure por `AT BEGINNING GAME`.
4. Adicione uma nova linha: `add_ai bots` — isto atribuirá um bot de IA para cada herói no jogo.

## Solução de Possíveis Erros
1. Renomeie o arquivo `Profiles -> private.cfg_example` para `private.cfg`.
2. Abra o arquivo com o Bloco de Notas.
3. Procure pela seção `performance section`.
4. Procure pela linha `setvar gfx_fullscreen = 0` — isto irá iniciar o jogo em modo janela, que pode ser mais estável.
5. Outras configurações de otimização também podem ser alteradas nesta seção.

## Agradecimentos
À comunidade **Prime World: Nova** pela contribuição na documentação e correção de erros.
