#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define FACTOR_CARGA_MAXIMO 0.7

typedef struct nodo{
    char* clave;
    void* valor;
    struct  nodo* siguiente;    
}nodo_t;


struct hash{
    nodo_t** vector;
    size_t capacidad;
    size_t cantidad;
};

hash_t *hash_crear(size_t capacidad)
{   
    hash_t* diccionario = calloc(1, sizeof(hash_t));
    if(diccionario == NULL)
        return NULL;
    diccionario->capacidad = capacidad;

    diccionario->vector = calloc(1, sizeof(nodo_t)*capacidad);
    if(diccionario->vector == NULL){
        free(diccionario);
        return NULL;
    }

    return diccionario;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
              void **anterior)
{
    if (!hash || !clave)
        return NULL;

    return NULL;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
    if (!hash)
        return NULL;

    return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
    if (!hash)
        return NULL;

    return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
    if (!hash)
        return NULL;

    return false;
}

size_t hash_cantidad(hash_t *hash)
{
    if (!hash)
        return 0;
    return 0;
}

void hash_destruir(hash_t *hash)
{
    hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *)) {
    if (!hash) {
        return;
    }

    for (size_t i = 0; i < hash->capacidad; i++) {
        nodo_t *actual = hash->vector[i];
        while (actual != NULL) {
            nodo_t *aux = actual;
            actual = actual->siguiente;

            if (destructor != NULL) {
                destructor(aux->valor);
            }
            free(aux->clave);
            free(aux);
        }
    }

    free(hash->vector);
    free(hash);
}

/* SI LO HICIERA REC
void liberar_nodos(nodo_t *nodo, void (*destructor)(void *)) {
    if (nodo == NULL) {
        return;
    }

    liberar_nodos(nodo->siguiente, destructor);

    if (destructor != NULL) {
        destructor(nodo->valor);
    }
    free(nodo->clave);
    free(nodo);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *)) {
    if (hash == NULL) {
        return;
    }

    for (size_t i = 0; i < hash->capacidad; i++) {
        liberar_nodos(hash->vector[i], destructor);
    }

    free(hash->vector);
    free(hash);
}

*/

size_t hash_con_cada_clave(hash_t *hash,
               bool (*f)(const char *clave, void *valor, void *aux),
               void *aux)
{
    size_t n = 0;
    if (!hash || !f)
        return n;

    return n;
}
