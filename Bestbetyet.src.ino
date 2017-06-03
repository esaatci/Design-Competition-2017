#include <stdio.h>
#include <stdlib.h>

#define  SIZE   19      /* number of cities */

int      START;         /* index of start city, set interactively */
#define  GOAL   17      /* index of goal city, Vienna */

#define  OPEN    1

#define  TRUE    1
#define  FALSE   0

typedef  struct city {
         char           name[ 15 ];
         int            ind;            /* position in array cities */
         int            g_val;          /* optimal path to city */
         int            h_est;          /* estimate to goal */
         int            f_est;          /* g_value + h_estimate */
         int            opened;           /* open list */
         int            closed;         /* closed list */
         struct city    *adjcs[ SIZE ]; /* adjacent cities */
         struct city    *backptr;       /* optimal path pointer */
} CITY;

CITY  cities[ SIZE ];

int   distances[ SIZE ][ SIZE ];   /* distances between two cities */
int   open_count = 0;              /* number of items on open list */

void  get_input( void ),
      set_adjacency_lists( void ),
      astar( void );
void  failure( void ), success( const CITY *ptr ),
      expand( int index );
int   get_best_prospect( void );
void  update_values( CITY *ptr ),
      update_path( CITY *ptr, int index );
void  get_start_city( void );
void  print_cities( const CITY *ptr );

int main()
{
        get_input();
        set_adjacency_lists();

        cities[ START ].backptr = NULL; /* path starts here */
        cities[ START ].g_val = 0;

        cities[ START ].opened = TRUE;    /* put START on open list */
        ++open_count;

        astar();  /* search */

        return EXIT_SUCCESS;
}

void astar( void )
{
        int best;

        if ( open_count == 0 )            /* any more options? */
             failure();                   /* if not, fail */
        else {
             best = get_best_prospect();      /* get most promising city */
             if ( best == GOAL )              /* goal city? */
                  success( &cities[ GOAL ] ); /* if so, succeed */
             else {                           /* otherwise: */
                  cities[ best ].opened = FALSE;    /* remove from open */
                  --open_count;
                  cities[ best ].closed = TRUE;   /* put on closed */
                  expand( best );                 /* expand it */
                  astar();                        /* keep searching */
             }
        }
}

int get_best_prospect( void )
{
        int  i = 0, best;

        /* Find 1st city in open list. */
        while ( cities[ i++ ].opened == FALSE )
                        ;
        /* Assume it's the best. */
        best = --i;

        /* Look for something better. */
        for ( i = best + 1; i < SIZE; ++i )
            if ( cities[ i ].opened == TRUE  &&
                 cities[ i ].f_est  <  cities[ best ].f_est )
               best = i;

        return best;
}

void expand( int index )
{
        int i = 0;

        while ( cities[ index ].adjcs[ i ] != NULL ) {

             /* If adjacent city is not on OPEN or CLOSED, then      */
             /* (1) set its backpointer to current city, (2) compute */
             /* its g_val and f_est, and (3) put it on OPEN.         */
             if ( cities[ index ].adjcs[ i ] -> opened == FALSE  &&
                  cities[ index ].adjcs[ i ] -> closed == FALSE ) {
                cities[ index ].adjcs[ i ] -> backptr = &cities[ index ];
                update_values( cities[ index ].adjcs[ i ] );
                cities[ index ].adjcs[ i ] -> opened = TRUE;
                ++open_count;
             }
             /* Otherwise, see if its backpointer needs changing. */
             else
                update_path( cities[ index ].adjcs[ i ], index );
             ++i;
        }
}

void  update_values( CITY *ptr )
{
        int ind1, ind2;

        ind1 = ptr -> backptr -> ind;   /* current city */
        ind2 = ptr -> ind;              /* predecessor */
        ptr -> g_val = ptr -> backptr -> g_val  +  distances[ ind1 ][ ind2 ];
        ptr -> f_est = ptr -> g_val  +  ptr -> h_est;
}

void  update_path( CITY *ptr, int index )
{
        CITY  *best;

        /* Assume current path is best. */
        best = ptr -> backptr;

        /* Compare with new path. */
        if ( best != NULL && cities[ index ].g_val  <  best -> g_val ) {
           /* If new path is better than the old one,
              then reset backpointer and update g_val and f_est. */
           ptr -> backptr = &cities[ index ];
           update_values( ptr );

           /* Is city on CLOSED? */
           if ( ptr -> closed == TRUE ) {
              /* If so, put back on OPEN. */
              ptr -> closed = FALSE;
              ptr -> opened = TRUE;
              ++open_count;
           }
        }
}

void get_input( void )
{
        FILE  *fptr;
        int   i, j;

        /* Read cities' names into structure variables. */
        fptr = fopen( "names.dat", "r" );
        for ( i = 0; i < SIZE; ++i ) {
             fscanf( fptr, "%s%d", cities[ i ].name, &cities[ i ].h_est );
             cities[ i ].ind = i;
             cities[ i ].opened = FALSE;
             cities[ i ].closed = FALSE;
        }
        fclose( fptr );

        /* Read distances between cities into matrix. */
        fptr = fopen( "distance.dat", "r" );
        for ( i = 0; i < SIZE; ++i )
             for ( j = 0; j < SIZE; ++j )
                  fscanf( fptr, "%d", &distances[ i ][ j ] );
        fclose( fptr );

        /* Prompt user for START city, and read its index into START. */
        get_start_city();
}

void get_start_city( void )
{
        printf( "\n\n\t\tPlease select a start city." );
        printf( "\n\t\tEnter a number associated with one of the cities.\n" );

        printf( "\n\t\tAmsterdam  ---  1\tLisbon  --- 10" );
        printf( "\n\t\tBelgrade   ---  2\tMadrid  --- 11" );
        printf( "\n\t\tBerlin     ---  3\tMunich  --- 12" );
        printf( "\n\t\tBern       ---  4\tNaples  --- 13" );
        printf( "\n\t\tBrussels   ---  5\tParis   --- 14" );
        printf( "\n\t\tBudapest   ---  6\tPrague  --- 15" );
        printf( "\n\t\tCopenhagen ---  7\tRome    --- 16" );
        printf( "\n\t\tGenoa      ---  8\tTrieste --- 17" );
        printf( "\n\t\tHamburg    ---  9\tWarsaw  --- 18" );
        printf( "\n\n\t\t" );
        scanf( "%d", &START );

        /* Adjust index for any city except Warsaw, whose index is 18. */
        if ( START < 18 )
           --START;
}

void failure( void )
{
        printf( "\n\n\n\tYou can't get there from here.\n\n " );
}

void success( const CITY *ptr )
{
        int i;

        printf( "\n\n\n" );
        printf( "\n\n\tOPTIMAL PATH LENGTH: %d\n", ptr -> g_val );
        printf( "\n\n\tOPTIMAL PATH:\n" );
        print_cities( ptr );

        printf( "\n\n\tEXPANDED VERTICES:\n" );
        for ( i = 0; i < SIZE; ++i )
            if ( cities[ i ].closed == TRUE )
               printf( "\n\t%s", cities[ i ].name );
        printf( "\n\n\n" );
}

void print_cities( const CITY *ptr )
{
        if ( ptr -> ind == START )            /* halt backtrack */
           printf( "\n\t%s", ptr -> name );
        else {
           print_cities( ptr -> backptr );    /* backtrack */
           printf( "\n\t%s", ptr -> name );
        }
}

void set_adjacency_lists( void )
{
        /***         Amsterdam to ...     ***/
        cities[ 0 ].adjcs[ 0 ] = &cities[ 3 ];    /* Bern */
        cities[ 0 ].adjcs[ 1 ] = &cities[ 4 ];    /* Brussels */
        cities[ 0 ].adjcs[ 2 ] = &cities[ 8 ];    /* Hamburg */
        cities[ 0 ].adjcs[ 3 ] = &cities[ 11 ];   /* Munich */

        /***         Belgrade to ...      ***/
        cities[ 1 ].adjcs[ 0 ] = &cities[ 5 ];    /* Budapest */
        cities[ 1 ].adjcs[ 1 ] = &cities[ 16 ];   /* Trieste */
        cities[ 1 ].adjcs[ 2 ] = &cities[ 17 ];   /* Vienna */

        /***         Berlin to ...        ***/
        cities[ 2 ].adjcs[ 0 ] = &cities[ 3 ];    /* Bern */
        cities[ 2 ].adjcs[ 1 ] = &cities[ 8 ];    /* Hamburg */
        cities[ 2 ].adjcs[ 2 ] = &cities[ 14 ];   /* Prague */
        cities[ 2 ].adjcs[ 3 ] = &cities[ 18 ];   /* Warsaw */

        /***         Bern to ...          ***/
        cities[ 3 ].adjcs[ 0 ] = &cities[ 0 ];    /* Amsterdam */
        cities[ 3 ].adjcs[ 1 ] = &cities[ 2 ];    /* Belgrade */
        cities[ 3 ].adjcs[ 2 ] = &cities[ 4 ];    /* Brussels */
        cities[ 3 ].adjcs[ 3 ] = &cities[ 7 ];    /* Genoa */
        cities[ 3 ].adjcs[ 4 ] = &cities[ 10 ];   /* Madrid */
        cities[ 3 ].adjcs[ 5 ] = &cities[ 11 ];   /* Munich */
        cities[ 3 ].adjcs[ 6 ] = &cities[ 16 ];   /* Trieste */

        /***         Brussels to ...      ***/
        cities[ 4 ].adjcs[ 0 ] = &cities[ 0 ];    /* Amsterdam */
        cities[ 4 ].adjcs[ 1 ] = &cities[ 3 ];    /* Bern */
        cities[ 4 ].adjcs[ 2 ] = &cities[ 7 ];    /* Genoa */
        cities[ 4 ].adjcs[ 3 ] = &cities[ 13 ];   /* Paris */

        /***         Budapest to ...      ***/
        cities[ 5 ].adjcs[ 0 ] = &cities[ 1 ];    /* Belgrade */
        cities[ 5 ].adjcs[ 1 ] = &cities[ 16 ];   /* Trieste */
        cities[ 5 ].adjcs[ 2 ] = &cities[ 17 ];   /* Vienna */
        cities[ 5 ].adjcs[ 3 ] = &cities[ 18 ];   /* Warsaw */

        /***         Copenhagen to ...    ***/
        cities[ 6 ].adjcs[ 0 ] = &cities[ 8 ];    /* Hamburg */

        /***         Genoa to ...         ***/
        cities[ 7 ].adjcs[ 0 ] = &cities[ 4 ];    /* Brussels */
        cities[ 7 ].adjcs[ 1 ] = &cities[ 10 ];   /* Madrid */
        cities[ 7 ].adjcs[ 2 ] = &cities[ 13 ];   /* Paris */
        cities[ 7 ].adjcs[ 3 ] = &cities[ 15 ];   /* Rome */
        cities[ 7 ].adjcs[ 4 ] = &cities[ 16 ];   /* Trieste */

        /***         Hamburg to ...       ***/
        cities[ 8 ].adjcs[ 0 ] = &cities[ 0 ];    /* Amsterdam */
        cities[ 8 ].adjcs[ 1 ] = &cities[ 2 ];    /* Berlin */
        cities[ 8 ].adjcs[ 2 ] = &cities[ 6 ];    /* Copenhagen */

        /***         Lisbon to ...         ***/
        cities[ 9 ].adjcs[ 0 ] = &cities[ 10 ];   /* Madrid */

        /***          Madrid to ...        ***/
        cities[ 10 ].adjcs[ 0 ] = &cities[ 3 ];   /* Bern */
        cities[ 10 ].adjcs[ 1 ] = &cities[ 7 ];   /* Genoa */
        cities[ 10 ].adjcs[ 2 ] = &cities[ 9 ];   /* Lisbon */
        cities[ 10 ].adjcs[ 3 ] = &cities[ 13 ];  /* Paris */

        /***          Munich to ...        ***/
        cities[ 11 ].adjcs[ 0 ] = &cities[ 0 ];   /* Amsterdam */
        cities[ 11 ].adjcs[ 1 ] = &cities[ 14 ];  /* Prague */
        cities[ 11 ].adjcs[ 2 ] = &cities[ 15 ];  /* Rome */
        cities[ 11 ].adjcs[ 3 ] = &cities[ 17 ];  /* Vienna */

        /***          Naples to ...         ***/
        cities[ 12 ].adjcs[ 0 ] = &cities[ 15 ];  /* Rome */

        /***          Paris to ...         ***/
        cities[ 13 ].adjcs[ 0 ] = &cities[ 4 ];   /* Brussels */
        cities[ 13 ].adjcs[ 1 ] = &cities[ 7 ];   /* Genoa */
        cities[ 13 ].adjcs[ 2 ] = &cities[ 10 ];  /* Madrid */

        /***          Prague to ...        ***/
        cities[ 14 ].adjcs[ 0 ] = &cities[ 2 ];   /* Berlin */
        cities[ 14 ].adjcs[ 1 ] = &cities[ 11 ];  /* Munich */
        cities[ 14 ].adjcs[ 2 ] = &cities[ 17 ];  /* Vienna */
        cities[ 14 ].adjcs[ 3 ] = &cities[ 18 ];  /* Warsaw */

        /***          Rome to ...          ***/
        cities[ 15 ].adjcs[ 0 ] = &cities[ 7 ];   /* Genoa */
        cities[ 15 ].adjcs[ 1 ] = &cities[ 11 ];  /* Munich */
        cities[ 15 ].adjcs[ 2 ] = &cities[ 12 ];  /* Naples */
        cities[ 15 ].adjcs[ 3 ] = &cities[ 16 ];  /* Trieste */

        /***          Trieste to ...       ***/
        cities[ 16 ].adjcs[ 0 ] = &cities[ 1 ];   /* Belgrade */
        cities[ 16 ].adjcs[ 1 ] = &cities[ 3 ];   /* Bern */
        cities[ 16 ].adjcs[ 2 ] = &cities[ 5 ];   /* Budapest */
        cities[ 16 ].adjcs[ 3 ] = &cities[ 7 ];   /* Genoa */
        cities[ 16 ].adjcs[ 4 ] = &cities[ 15 ];  /* Rome */
        cities[ 16 ].adjcs[ 5 ] = &cities[ 17 ];  /* Vienna */

        /***          Warsaw to ...        ***/
        cities[ 18 ].adjcs[ 0 ] = &cities[ 2 ];   /* Berlin */
        cities[ 18 ].adjcs[ 1 ] = &cities[ 5 ];   /* Budapest */
        cities[ 18 ].adjcs[ 2 ] = &cities[ 14 ];  /* Prague */
        cities[ 18 ].adjcs[ 3 ] = &cities[ 17 ];  /* Vienna */
}

