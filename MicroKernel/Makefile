###########################################################################################
##                             Sistemas Embarcados 2013/2014                             ##
##                                    Micro-kernel RTS                                   ##
##                                                                                       ##
## Eduardo Nuno Moreira Soares de Almeida	201000641                                    ##
## Rui Pedro Zenhas Graca					201004124                                    ##
## Tiago dos Santos Maia Costa				200601289                                    ##
###########################################################################################
##                                 Makefile do micro-kernel                              ##
###########################################################################################


#microKernel.o: microKernel.c Scheduler_Fixo.o
#	gcc microKernel.c Scheduler_Fixo.o -o microKernel


SOURCES = MicroKernel.c Scheduler_Fixo.c ListaTarefas.c


all: $(SOURCES)
#	gcc -Wall -c Scheduler_Fixo.c ListaTarefas.c
	gcc -Wall -c MicroKernel.c
	
	
	
#	rm Scheduler_Fixo.o

clean:
	rm -rf *.o
