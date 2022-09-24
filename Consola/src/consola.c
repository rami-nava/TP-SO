#include "consola.h"


int main(int argc, char** argv){
	if (argc < 2){
		return EXIT_FAILURE;
	}
	//Archivo config
    config = config_create(argv[1]);
    char* ip_kernel = config_get_string_value(config, "IP_KERNEL");
    char* puerto_kernel = config_get_string_value(config, "PUERTO_KERNEL");

    //Tuve que cambiar el ip y el puerto que teniamos porque no dejaba conectar al servidor

    //Archivo log
    logger = log_create("/home/utnso/TP-SO/Consola/cfg/consola.log", "consola", true, LOG_LEVEL_INFO);
    log_info(logger, "IP KERNEL: %s", ip_kernel);
    log_info(logger, "PUERTO KERNEL: %s", puerto_kernel);


    //Conexion
    conexion = crear_conexion(ip_kernel, puerto_kernel);
    paquete = crear_paquete();

    	char caracter;
    	char instruccion [Max];

        FILE *fp;
        fp = fopen ( argv[2], "r" );
    	if (fp == NULL)
        {
            printf("Error, no se pudo leer el archivo con las instrucciones \n");
            return EXIT_FAILURE;
        }
        else
        {
        	while((caracter = fgetc(fp)) != EOF){
            	int i = 0;
            	while(caracter != '\n')
            	{
            		instruccion[i] = caracter;
            		i++;
            		caracter = fgetc(fp);
            	}

            agregar_a_paquete(paquete,instruccion,strlen(instruccion)+1);
            }
        }
        fclose(fp);


    enviar_paquete(paquete,conexion);


    int cod_op = recibir_operacion(conexion);

	t_list* lista;
    switch (cod_op){
    case MENSAJE:
    	recibir_mensaje(conexion); //aca recibiria la instruccion del kernel
    	break;
    case PAQUETE:
    	lista = recibir_paquete(conexion);
    	log_info(logger, "Me llegaron los siguientes valores:\n");
    	list_iterate(lista, (void*) iterator);
    	break;
    default:
    	log_warning(logger,"Operacion desconocida. No quieras meter la pata");
    	break;
    		}


    terminar_programa(logger,config,conexion);

}

void terminar_programa(t_log* logger, t_config* config,int conexion)
{
	if(logger != NULL)
		log_destroy(logger);
	if(config != NULL)
		config_destroy(config);
	liberar_conexion(conexion);
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}
