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
    enviar_mensaje("Estamos conectados \n",conexion);

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
