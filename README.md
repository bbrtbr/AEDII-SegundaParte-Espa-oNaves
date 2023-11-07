A fuga à Via Láctea está em andamento devido a sua contribuição na implementação do sistema de filas de prioridades.
Porém, uma arma poderosa foi desenvolvida pelo sistema opressor da galáxia distante que utiliza a energia da matéria
escura para destruir planetas inteiros. Isso fez com que a mais naves chegassem à região da passagem entre as galáxias
buscando proteção.
Ao longo da passagem das naves em fuga, observou-se um fenômeno estranho. A passagem aumentava de tamanho
até 100 vezes de tempos em tempos. Os pesquisadores de ambas as galáxeas ainda não entendem o porquê da ocorrência
de tal fenômeno, mas os alunos de AEDII do curso de Ciência da Computação da UFCA conseguiram achar um padrão
de frequência com a análise das ocorrências anteriores. Eles observaram que as naves possuem compartimentos grandes,
suponha todas com quatro deles, que servem para transportar os recursos essenciais à vida de cada população, que são base
para a produção de outros. A ordem dos compartimentos parece importar nos experimentos, onde eles são postos em fila
do começo até o fim de cada nave. Os estudantes entenderam que sempre que ocorre a passagem de naves distintas com os
mesmos recursos nos compartimentos, mas de modo que todas as possibilidades de permutações das posições dos recursos
ocorra, então a passagem se expande, possibilitando a passagem de mais naves. Por exemplo, supondo que C1, C2 e C3 são
os compartimentos da nave N e R1, R2 e R3 os recursos presentes em tais compartimentos de N, a abertura se expandirá
quando naves distintas de N passarem pela abertura transportando os mesmos recursos R1, R2 e R3, mas cada uma nas
demais possibilidades de alocação nos compartimentos C1, C2 e C3. Assim, a abertura se expandirá quando houverem
as alocações: (R1, R2, R3),(R1, R3, R2),(R2, R1, R3),(R2, R3, R1),(R3, R2, R1) e (R3, R1, R2) nos compartimentos C1, C2
e C3.
Infelizmente, a abertura se dá em um período curto de tempo, impedindo que seja usada na totalidade, já que não se
sabe quando irá se expandir novamente devido ao grande número de naves na fila. Dessa forma, vários recursos distintos
chegam nas naves, mas apenas quando todas as permutações de três quaisquer deles ocorre, há a expansão. Para resolver
o problema e antever quando a abertura ficará maior e aproveitar ao máximo a oportunidade, os estudantes da UFCA
se comprometeram a desenvolver uma solução para identificar o momento em que a abertura se expandirá novamente,
dado o momento da última expansão. Eles sabem que a fila de naves pode ser muito grande, mas deseja-se identificar a
ocorrência do fenômeno o mais rápido possível e informar aos organizadores da fila para acelerarem a passagem de mais
naves.
Implemente um algoritmo que resolva o problema em questão da forma mais eficiente possível. Suponha que exista
uma lista de 100 recursos diferentes conhecidos na galáxia e que cada nave transporta três deles. Após a escolha da nave
a efetuar a travessia, é feita a análise dos seus compartimentos para saber quais recursos ela transporta e em que ordem
eles aparecem. Esses dados devem ser levados em conta para avaliar se tal ordem já apareceu ou não desde a última
expansão.
