#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void ejecutarConsulta(MYSQL *conn, const char *consulta) {
    if (mysql_query(conn, consulta)) {
        fprintf(stderr, "Error en la consulta: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(conn);
    if (resultado == NULL) {
        fprintf(stderr, "Error obteniendo resultado: %s\n", mysql_error(conn));
        return;
    }
int num_columnas = mysql_num_fields(resultado);
    MYSQL_ROW fila;

    while ((fila = mysql_fetch_row(resultado))) {
        for (int i = 0; i < num_columnas; i++) {
            printf("%s\t", fila[i] ? fila[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(resultado);
}
int main() {
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "Error al inicializar MySQL: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // Conéctate al servidor MySQL
    if (!mysql_real_connect(conn, "localhost", "root", "mysql", "JuegoPokemon", 0, NULL, 0)) {
        fprintf(stderr, "Error de conexión: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }
printf("Conexión exitosa a la base de datos\n");

    // Ejecutar una consulta
    ejecutarConsulta(conn, "SELECT * FROM Pokedex");

    mysql_close(conn);
    return EXIT_SUCCESS;
}
