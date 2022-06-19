# Jogo de Damas

Para testes, o código fonte foi compilado com o compilador g++ 9.2.0, utilizando o seguinte comando no console git bash para o Windows

```console
g++ src/*.cpp -o game.exe
```

Executando game.exe, há um menu inicial no qual o usuário pode escolher um dos três modos

- **Um jogador:** o usuário joga contra um algoritmo que captura a peça inimiga se puder ou executa um movimento aleatório, se não;

- **Dois jogadores:** dois usuários competem um contra o outro;

- **Nenhum jogador:** nesse modo, o algoritmo supracitado compete contra ele mesmo, e o usuário pode acompanhar as jogadas que são feitas na tela a cada segundo.

Ademais, caso o usuário escolha o modo **um jogador**, ele poderá escolher com qual cor quer jogar

- **Azul:** faz o papel das peças _pretas_ em damas, ou seja, joga primeiro;
- **Vermelho:** faz o papel das peças _brancas_, sempre jogando depois das pretas.

Após essas escolhas, será impresso o tabuleiro com a configuração inicial das peças. Se o jogador for humano, ele deverá, na sua vez, declarar seu movimento especificando as casas de origem e de destino no tabuleiro, nessa ordem. As casas deverão ser escritas na notação algébrica do xadrez e deverão ser serparadas por pelo menos um caractere ' ' (espaço). Um exemplo de jogada válida é "c3 d4", para as peças pretas configuração inicial. Se for fornecida uma jogada que infrinja as regras do jogo, o usuário será notificado, e seu input será requisitado até ele fornecer uma entrada válida.

**IMPORTANTE:** o programa como está **não** é portável, pois ele utiliza bibliotecas do Windows para modificar o console, limpando-o e inserindo cores, e para parar a execução do programa por períodos determinados de tempo. Portanto, tentar compilá-lo em outro SO resultará em erro.
