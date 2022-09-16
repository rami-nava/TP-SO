#include "kernel.h"

int main(void) {
	logger = log_create("log.log", "Kernel", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Kernel listo para recibir a Consola");
	int cliente_fd = esperar_cliente(server_fd);

	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			enviar_mensaje("Confirmaciond de recepcion de instrucciones",cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			log_info(logger, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}

	conexion = crear_conexion(IP,PUERTO);
	enviar_mensaje("Estamos devuelta \n",cliente_fd);

}

void iterator(char* value) {
	log_info(logger,"%s", value);
}




