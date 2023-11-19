#include <stdlib.h>
#include "pa2m.h"
#include "src/hash.h"

bool contar_elementos(const char *clave, void *valor, void *extra)
{
	if (extra != NULL) {
		int *contador = extra;
		(*contador)++;
	}
	return true;
}

bool contar_elementos_parcialmente(const char *clave, void *valor, void *extra)
{
	int *contador = extra;
	(*contador)++;

	if (*contador == 3) {
		return false;
	}

	return true;
}

void se_puede_crear_hash_con_capacidad_mayor_y_menor_a_tres()
{
	hash_t *hash_1 = hash_crear(5);
	hash_t *hash_2 = hash_crear(2);

	pa2m_afirmar(hash_1 != NULL,
		     "Se creó el hash con capacidad inicial mayor a 3");
	pa2m_afirmar(hash_2 != NULL,
		     "Se creó el hash con capacidad inicial menor a 3");

	hash_destruir(hash_1);
	hash_destruir(hash_2);
}

void se_puede_insertar()
{
	hash_t *hash = NULL;
	pa2m_afirmar(hash_insertar(hash, "A", (void *)1, NULL) == NULL,
		     "No se puede insertar en un hash nulo");

	hash = hash_crear(5);
	pa2m_afirmar(hash_insertar(hash, NULL, (void *)1, NULL) == NULL,
		     "No se puede insertar con clave nula en un hash válido");

	pa2m_afirmar(
		hash_insertar(hash, "A", NULL, NULL) == hash,
		"Se insertó elemento nulo con clave válida en hash válido");

	int valor = 42;
	pa2m_afirmar(hash_insertar(hash, "B", &valor, NULL) == hash,
		     "Se insertó elemento con clave válida en hash válido");

	pa2m_afirmar(hash_insertar(hash, "C", (void *)1, NULL) == hash,
		     "Se insertó elemento 1");
	pa2m_afirmar(hash_insertar(hash, "D", (void *)2, NULL) == hash,
		     "Se insertó elemento 2");
	pa2m_afirmar(hash_insertar(hash, "E", (void *)3, NULL) == hash,
		     "Se insertó elemento 3");
	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "La cantidad de claves presentes en el hash es correcta");

	hash_destruir(hash);
}

void se_puede_insertar_varios_elementos_y_rehash()
{
	hash_t *hash = hash_crear(3);

	pa2m_afirmar(hash_insertar(hash, "A", (void *)1, NULL) == hash,
		     "Se insertó elemento 1");
	pa2m_afirmar(hash_insertar(hash, "B", (void *)2, NULL) == hash,
		     "Se insertó elemento 2");
	pa2m_afirmar(hash_insertar(hash, "C", (void *)3, NULL) == hash,
		     "Se insertó elemento 3");
	pa2m_afirmar(hash_insertar(hash, "D", (void *)4, NULL) == hash,
		     "Se insertó elemento 4 y se hizo rehash");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad de claves presentes en el hash es correcta");

	hash_destruir(hash);
}

void se_puede_actualizar_elemento()
{
	hash_t *hash = hash_crear(3);

	int valor1 = 42;
	pa2m_afirmar(hash_insertar(hash, "A", &valor1, NULL) == hash,
		     "Se insertó elemento con clave 'A'");

	int valor2 = 99;
	void *anterior = NULL;
	pa2m_afirmar(hash_insertar(hash, "A", &valor2, &anterior) == hash &&
			     anterior == &valor1,
		     "Se actualizó elemento con clave 'A'");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de claves presentes en el hash es correcta");
	hash_destruir(hash);
}

void se_puede_quitar_elemento()
{
	hash_t *hash = NULL;
	pa2m_afirmar(hash_quitar(hash, "A") == NULL,
		     "No se puede quitar de un hash nulo");

	hash = hash_crear(3);
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL,
		     "No se puede quitar con clave nula en un hash válido");

	pa2m_afirmar(hash_quitar(hash, "A") == NULL,
		     "No se puede quitar un elemento que no existe en el hash");

	int valor = 42;
	pa2m_afirmar(hash_insertar(hash, "A", &valor, NULL) == hash,
		     "Se insertó elemento con clave 'A'");

	void *elemento = hash_quitar(hash, "A");
	pa2m_afirmar(
		elemento != NULL && elemento == &valor,
		"Se quitó elemento con clave 'A' que sí existía en el hash");
	pa2m_afirmar(
		hash_quitar(hash, "A") == NULL,
		"No se puede quitar de nuevo un elemento que ya fue quitado");

	hash_destruir(hash);
}

void se_puede_obtener_elementos_del_hash()
{
	hash_t *hash = NULL;
	pa2m_afirmar(hash_obtener(hash, "clave") == NULL,
		     "No se puede obtener elementos de un hash nulo");

	hash = hash_crear(3);
	pa2m_afirmar(hash_obtener(hash, NULL) == NULL,
		     "No se puede obtener con clave nula en un hash válido");

	pa2m_afirmar(
		hash_obtener(hash, "A") == NULL,
		"No se puede obtener una clave que no se encuentra en el hash");

	int valor = 42;
	pa2m_afirmar(hash_insertar(hash, "A", &valor, NULL) == hash,
		     "Se insertó elemento con clave 'A'");

	void *elemento = hash_obtener(hash, "A");
	pa2m_afirmar(
		elemento != NULL && elemento == &valor,
		"Se obtuvo elemento con clave 'A' que sí se encuentra en el hash");

	pa2m_afirmar(
		hash_quitar(hash, "A") != NULL,
		"Se quitó el elemento con clave 'A' que sí se encuentraba en el hash");

	pa2m_afirmar(hash_obtener(hash, "A") == NULL,
		     "Ya no se encuentra la clave 'A' en el hash");

	hash_destruir(hash);
}

void el_hash_contiene_la_cantidad_correcta()
{
	hash_t *hash = NULL;
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Un hash nulo no contiene claves");

	hash = hash_crear(3);

	int valor = 42;
	pa2m_afirmar(hash_insertar(hash, "A", &valor, NULL) == hash,
		     "Se insertó elemento con clave 'A'");
	pa2m_afirmar(
		hash_cantidad(hash) == 1,
		"La cantidad de claves presentes en un hash no nulo es correcta");

	hash_destruir(hash);
}

void prueba_iterar_hash()
{
	hash_t *hash = NULL;
	int contador = 0;

	pa2m_afirmar(hash_con_cada_clave(hash, contar_elementos, &contador) ==
			     0,
		     "No se puede iterar un hash nulo");

	const char claves[] = { 'A', 0, 'B', 0, 'C', 0, 'D', 0, 'E', 0, 'F', 0 };
	char valores[6] = { 1, 2, 3, 4, 5, 6 };
	hash = hash_crear(6);

	pa2m_afirmar(hash_con_cada_clave(hash, NULL, &contador) == 0,
		     "No se puede iterar con una función nula");

	for (size_t i = 0; i < 6; i++) {
		hash_insertar(hash, &claves[2 * i], &valores[i], NULL);
	}

	pa2m_afirmar(hash_con_cada_clave(hash, contar_elementos, NULL) == 6,
		     "Se puede iterar con un auxiiar nulo y en su totalidad");
	pa2m_afirmar(hash_con_cada_clave(hash, contar_elementos_parcialmente,
					 &contador) == 3,
		     "Se puede iterar parcialmente el hash");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Prueba de Creación ========================");
	se_puede_crear_hash_con_capacidad_mayor_y_menor_a_tres();

	pa2m_nuevo_grupo(
		"\n======================== Prueba de Inserción ========================");
	se_puede_insertar();
	se_puede_insertar_varios_elementos_y_rehash();
	se_puede_actualizar_elemento();

	pa2m_nuevo_grupo(
		"\n======================== Prueba de Eliminación ========================");
	se_puede_quitar_elemento();

	pa2m_nuevo_grupo(
		"\n======================== Prueba de Obtención ========================");
	se_puede_obtener_elementos_del_hash();

	pa2m_nuevo_grupo(
		"\n======================== Prueba de Cantidad ========================");
	el_hash_contiene_la_cantidad_correcta();

	pa2m_nuevo_grupo(
		"\n======================== Prueba de iterador interno ========================");
	prueba_iterar_hash();

	return pa2m_mostrar_reporte();
}
