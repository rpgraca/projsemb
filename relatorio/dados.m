% Medições de tempos de execução
% Atualização dos temporizadores

% Uma tarefa por temporizador
NumTemps1 =	 [0		1		2		3		4		5		10	];
Tempo1 =	 [1.24	16.2	30.8	46.2	61.2	76		151	]; % Tempo em us


% Tarefas partilham temporizador global 
NumTemps2 =	 [0		1		2		3		4		5		10	];
Tempo2 =	 [1.24	16.2	20.8	25.2	29.6	34		56.8]; % Tempo em us



% Sched_dispatch()
% Uma tarefa de prioridade 0 com NumPrioridades1 niveis de prioridade sem tarefas
NumPrioridades1 =	[1		2		3		4		5		10	];
Tempo3 =			[4.4	7.12	9.6		12.5	15.2	28.6];

% Uma tarefa de prioridade 0 com NumPrioridades2 niveis de prioridade com 1 tarefa cada (sem mudança de contexto)
NumPrioridades2 =	[1		2		3		4		5		10	];
Tempo4 =			[4.4	16.6	28.8	40.8	53.6	114	];

% Uma tarefa de prioridade 0 com NumPrioridades3 niveis de prioridade com 1 tarefa cada (com mudança de contexto)
NumPrioridades3 =	[1		2		3		4		5		10	];
Tempo5 =			[24.4	34.4	47		60		71		130	];

% Terminação de tarefa
% Terminar uma tarefa de um nivel de prioridade com NumTarefas1 tarefas nesse nivel de prioridade
NumTarefas1 =		[1		2		3		4		5		10	];
Tempo5 =			[53.8	56.3	60.1	63.7	67.2	90	];

% Sinalização de um sinal
% Tempo da função Sinais_sinaliza() com NumTarefas2 tarefas à espera nesse sinal
NumTarefas2 =		[1		2		3		4		5		10	];
Tempo6 =			[5.9	9.2		12.6	15.9	19.2	35.8];

% Outras medições
% Adicionar Tarefa - 57.5
% Espera Timer - 5.2 
% Sleep - 40
% Fim Sleep - 38
% Espera Sinal - 5.2
% Semaforo lock - 7.1
% Semaforo unlock - 2.5 

% Calculos
x = 0:0.01:10;
Temp_1pT = polyfit(NumTemps1, Tempo1, 1);
Temp_TG = polyfit(NumTemps2(2:length(Tempo2)), Tempo2(2:length(Tempo2)),1);
figure(1);
hold on
scatter(NumTemps2,Tempo2,'r');
scatter(NumTemps1,Tempo1);
plot(x,Temp_1pT(1)*x + Temp_1pT(2));
plot(x,Temp_TG(1)*x + Temp_TG(2),'r');
grid
ylabel('Tempo (us)');
xlabel('Numero de tarefas');


