#ifndef CONSOLA_H_
#define CONSOLA_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>

//#include "utils.h"
#include "/home/utnso/TP-SO/Utils/src/utils.h"


#define MaxCant 100
#define Max 20

t_config* config;
t_log* logger;
t_paquete* paquete;
int conexion;

void terminar_programa(t_log*, t_config*,int);
void iterator(char* value);

#endif /* CONSOLA_H_ */
