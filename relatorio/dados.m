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
