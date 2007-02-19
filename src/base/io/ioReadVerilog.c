/**CFile****************************************************************

  FileName    [ioReadVerilog.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Command processing package.]

  Synopsis    [Procedure to read network from file.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: ioReadVerilog.c,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/

#include "io.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

extern Abc_Lib_t * Ver_ParseFile( char * pFileName, Abc_Lib_t * pGateLib, int fCheck, int fUseMemMan );

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Reads hierarchical design from the Verilog file.]

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Ntk_t * Io_ReadVerilog( char * pFileName, int fCheck )
{
    Abc_Ntk_t * pNtk;
    Abc_Lib_t * pDesign;

    // parse the verilog file
    pDesign = Ver_ParseFile( pFileName, NULL, fCheck, 1 );
    if ( pDesign == NULL )
        return NULL;
/*
    // extract the master network
    pNtk = Vec_PtrEntryLast( pDesign->vModules );
    pNtk->pDesign = pDesign;
    pDesign->pManFunc = NULL;

    // verify the design for cyclic dependence
    assert( Vec_PtrSize(pDesign->vModules) > 0 );
    if ( Vec_PtrSize(pDesign->vModules) == 1 )
    {
//        printf( "Warning: The design is not hierarchical.\n" );
        Abc_LibFree( pDesign, pNtk );
        pNtk->pDesign = NULL;
        pNtk->pSpec = Extra_UtilStrsav( pFileName );
    }
    else
    {
        // bring the root model to the beginning
        for ( i = Vec_PtrSize(pDesign->vModules) - 2; i >= 0; i-- )
            Vec_PtrWriteEntry(pDesign->vModules, i+1, Vec_PtrEntry(pDesign->vModules, i) );
        Vec_PtrWriteEntry(pDesign->vModules, 0, pNtk );
        // check that there is no cyclic dependency
        Abc_NtkIsAcyclicHierarchy( pNtk );
    }
*/
    // extract the master network
    pNtk = Vec_PtrEntry( pDesign->vModules, 0 );
    pNtk->pDesign = pDesign;
    pDesign->pManFunc = NULL;

//Io_WriteVerilog( pNtk, "_temp.v" );

    // verify the design for cyclic dependence
    assert( Vec_PtrSize(pDesign->vModules) > 0 );
    if ( Vec_PtrSize(pDesign->vModules) == 1 )
    {
//        printf( "Warning: The design is not hierarchical.\n" );
        Abc_LibFree( pDesign, pNtk );
        pNtk->pDesign = NULL;
        pNtk->pSpec = Extra_UtilStrsav( pFileName );
    }
    else
    {
        // check that there is no cyclic dependency
        Abc_NtkIsAcyclicHierarchy( pNtk );
    }
    return pNtk;
}

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////



