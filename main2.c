/**
 MIT License
 
 Copyright (c) 2018 Matias Barrientos.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, const char * argv[]) {
    
    list *lista = list_create_empty ();
    
    int *data = NULL;
    
    int i;
    
    for (i = 0; i < 10; i++) {
        data = (int *) malloc (sizeof (int));
        *data = i;
        list_push_back (lista, data);
    }
    
    data = list_first (lista);
    
    data = (int *) malloc (sizeof (int));
    *data = 11;
    
    list_push_current (lista, data);
    
    data = list_first (lista);
    
    while (data != NULL) {
        printf ("%d\n", *data);
        data = list_next (lista);
    }
    
    printf ("\n");
    
    // Si esta agrega la funcion release esto no es necesario
    free (list_pop_back (lista));
    free (list_pop_front (lista));
    
    data = list_last (lista);
    
    while (data != NULL) {
        printf ("%d\n", *data);
        free (data);
        data = list_prev (lista);
    }
    
    list_release (&lista);
    
    return 0;
}
