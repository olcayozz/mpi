#include <stdio.h>
#include <math.h>
#include <stdlib.h>




typedef struct hypercube_details {
    int max_islands;        // Will contain  how many islands (power of 2)
    unsigned int max_degree;    // Will contain the maximum degree of connectivity
    unsigned int max_dimensions;    // Will contain max number of bits for address space
    unsigned int ** map;        // mapping, 2d array : map[ an island ][ to max_degree ] 
} hypercube_struct_t;




int makeHypercube( hypercube_struct_t * hc_ptr, int islands );
void freeHypercube( hypercube_struct_t * hc_ptr );



int main(void) {

    int source, connection;

    // Create the hypercube variable    
    hypercube_struct_t hypercube;

    // Call the make function.
    if( makeHypercube( &hypercube, 64) == 0 ) {
        printf("Something went wrong :(\n");
    } else {
        

        // example usage:

        // For each node/island.
        for( source = 0; source < hypercube.max_islands; source++ ) {
            printf("Island %d connects to islands: ",source);           
            for( connection = 0; connection < hypercube.max_degree; connection++ ) {
                printf("%d,", hypercube.map[source][connection]);                
            }
            printf("\n");
        }


        // and eventually free up the memory
        freeHypercube( &hypercube );

    }



}





int makeHypercube( hypercube_struct_t * hc_ptr, int islands ) {

    unsigned int target,source,dimension, degree;
    double d_temp;
    
    unsigned int * mask;
    
    hc_ptr->max_islands = islands;


    printf("%d Islands\n", hc_ptr->max_islands);

    // The degree is how many other nodes one node connects too
    hc_ptr->max_degree = log(hc_ptr->max_islands)/log(2);
    printf("Max degree should be %d\n", hc_ptr->max_degree);
    
    // Work out what power of base 2 this number is.
    d_temp = log(hc_ptr->max_islands)/log(2);
    hc_ptr->max_dimensions = (unsigned int)d_temp;
    if( d_temp - (double)hc_ptr->max_dimensions > 0.001 ) {
        printf("Error: Number of islands is not a power of 2, abort\n");
        return 0;
    }

    printf("Max Dimensions %d\n", hc_ptr->max_dimensions);

    // We create a number of bit masks equal to the maximum bits
    // required to map the addresses in binary.
    mask = malloc( hc_ptr->max_dimensions * sizeof( unsigned int ));
    
    mask[0] = 1;
    for( dimension = 1; dimension < hc_ptr->max_dimensions; dimension++ ) {
        mask[dimension] = (int)pow(2,dimension);
    }

    // We create a look up table map for each island, with the
    // max number of degree entries.
    hc_ptr->map = malloc( hc_ptr->max_islands * sizeof( unsigned int *));
    for( source = 0; source < islands; source++ ) {
        hc_ptr->map[source] = malloc( hc_ptr->max_degree * sizeof( unsigned int ));
    }        


    // We iterate through all the combinations and check for just a one 
    // bit change between addresses, saving to our map table.
    // We check that we dont create more address mappings than we malloc'd
    // by tracking the degree variable.  This shouldn't happen, but just to
    // be safe :)
    for( source = 0; source < hc_ptr->max_islands; source++ ) {
            
        degree = 0;
        
        for( target = 0; target < hc_ptr->max_islands; target++ ) {

            for( dimension = 0; dimension < hc_ptr->max_dimensions; dimension++ ) {

                if( (source ^ target) == mask[dimension] ) {
                    
                    if( degree > hc_ptr->max_degree ) {
                    
                        freeHypercube( hc_ptr );        
                        printf("\n Error, found an address match beyond the max degrees, abort\n");
                        return NULL;
                    
                    } else {

                        hc_ptr->map[source][degree] = target;
                        degree++;
                    }
                }
            }
        }     }
        
    free( mask );
    
}

void freeHypercube( hypercube_struct_t * hc_ptr ) {
    int i;

    for( i = 0; i < hc_ptr->max_islands; i++ ) {
        free( hc_ptr->map[i] );
        hc_ptr->map[i] = NULL;
    }    
    free( hc_ptr->map );
    hc_ptr->map = NULL;

    return;
}
