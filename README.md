projsemb
========

rtOS for ATmega



A fazer:
Implementar temporizadores (devem ser periódicos, mas também pode haver uma função sleep, que implementa uma temporização única)
Acabar scheduler
Dispatcher - Falta fazer clear à variável prioridade atual sempre que uma tarefa acaba

!!!IMPORTANTE!!!
As funções do kernel que acedem a estruturas partilhadas devem correr sem preepmção para evitar race conditions, falta arranjar forma de fazer isso
