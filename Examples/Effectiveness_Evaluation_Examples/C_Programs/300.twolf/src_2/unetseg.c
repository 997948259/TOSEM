#include "standard.h"
#include "groute.h"

unetseg()
{

SEGBOXPTR segptr ;
CHANGRDPTR ptr1 , ptr2 , bptr , fptr , sptr , eptr , ptr , gdptr ;
CHANGRDPTR tryptr[500] ;
DENSITYPTR denptr , headptr ;
NBOXPTR netptr ;
int pin1 , pin2 , x1 , x2 , x , i ;
int channel , chan , up_channel , segment , Flag , changes ;
int index , b , e , net , track , dtrack ;
int Ucount , Lcount ;
int j , t , tryFlag[500] , trynet , pinloc , self_reset ;


gtopChan = 1 ;
gbotChan = numChans ;
tracks = 0 ;
for( index = 1 ; index <= netchgs[0] ; index++ ) {
    net = netchgs[index] ;
    b = anet[net] ;
    e = anet[net + 1] - 1 ;
    for( segment = b ; segment <= e ; segment++ ) {
	if( aNetSeg[segment].current == 0 ) {
	    segptr = aNetSeg[segment].top ;
	} else {
	    segptr = aNetSeg[segment].bot ;
	}
	pin1 = segptr->pin1 ;
	pin2 = segptr->pin2 ;
	if( pin1 > maxterm && pin2 > maxterm ) {
	    continue ;
	}
	ptr1 = segptr->pin1ptr ;
	ptr2 = segptr->pin2ptr ;
	x1 = ptr1->netptr->newx ;
	x2 = ptr2->netptr->newx ;
	if( x1 == x2 ) {
	    continue ;
	}
	channel = segptr->channel ;
	if( channel > gtopChan ) {
	    gtopChan = channel ;
	}
	if( channel < gbotChan ) {
	    gbotChan = channel ;
	}
	net = aNetSeg[segment].net ;
	if( ptr1->nSegType > 0 ) {
	    Flag = 0 ;
	    bptr = ptr1 ;
	    while( bptr->prevgrd != GRDNULL 
			&& bptr->prevgrd->netptr->newx == x1 ) {
		if( net == tearray[bptr->prevgrd->netptr->terminal]->net
				   && bptr->prevgrd->nSegType < 0 ){
		    Flag = 1 ;
		    sptr = ptr1->nextgrd ;
		    while( sptr->netptr->newx == x1 ) {
			sptr = sptr->nextgrd ;
		    }
		    break ;
		} else {
		    bptr = bptr->prevgrd ;
		}
	    }
	    if( !Flag ) {
		sptr = ptr1->nextgrd ;
		while( sptr->netptr->newx == x1 ) {
		    if( net == tearray[sptr->netptr->terminal]->net 
					&& sptr->nSegType < 0 ) {
			Flag = 1 ;
		    }
		    sptr = sptr->nextgrd ;
		}
	    }
	    if( !Flag ) {
		sptr = bptr ;
	    }
	} else {
	    if( x1 != gxstart ) {
		sptr = ptr1->nextgrd ;
		while( sptr->netptr->newx == x1 ) {
		    sptr = sptr->nextgrd ;
		}
	    } else {
		sptr = ptr1 ;
	    }
	}

	if( ptr2->nSegType < 0 ) {
	    Flag = 0 ;
	    fptr = ptr2 ;
	    while( fptr->nextgrd != GRDNULL 
			&& fptr->nextgrd->netptr->newx == x2 ) {
		if( net == tearray[fptr->nextgrd->netptr->terminal]->net
				   && fptr->nextgrd->nSegType > 0 ){
		    Flag = 1 ;
		    eptr = ptr2->prevgrd ;
		    while( eptr->netptr->newx == x2 ) {
			eptr = eptr->prevgrd ;
		    }
		    break ;
		} else {
		    fptr = fptr->nextgrd ;
		}
	    }
	    if( !Flag ) {
		eptr = ptr2->prevgrd ;
		while( eptr->netptr->newx == x2 ) {
		    if( net == tearray[eptr->netptr->terminal]->net 
					&& eptr->nSegType > 0 ) {
			Flag = 1 ;
		    }
		    eptr = eptr->prevgrd ;
		}
	    }
	    if( !Flag ) {
		eptr = fptr ;
	    }
	} else {
	    if( x2 != gxstop ) {
		eptr = ptr2->prevgrd ;
		while( eptr->netptr->newx == x2 ) {
		    eptr = eptr->prevgrd ;
		}
	    } else {
		eptr = ptr2 ;
	    }
	}
	eptr = eptr->nextgrd ;
	if( pin1 <= maxterm ) {
	    ptr1->nSegType -= RIGHT ;
	}
	if( pin2 <= maxterm ) {
	    ptr2->nSegType -= LEFT  ;
	}

	for( ptr = sptr ; ptr != eptr ; ptr = ptr->nextgrd ) {
	    denptr = ptr->dptr ;
	    if( denptr->nnext != DENSENULL ) {
		denptr->nnext->nback = denptr->nback ;
	    }
	    denptr->nback->nnext = denptr->nnext ;
	    track = --(ptr->ntracks) ;

	    headptr = DboxHead[ channel ][ track ]->nnext ;
	    if( headptr != DENSENULL ) {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext  = headptr ;
		headptr->nback = denptr  ;
		denptr->nback  = DboxHead[ channel ][ track ] ;
	    } else {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = DENSENULL ;
		denptr->nback = DboxHead[ channel ][ track ];
	    }
	}
    }
}


/* time to build new linked list of nodes whose x-position
   have been changed */
Ucount = Lcount = 0 ;

if( ULgrdptr != GRDNULL ) {
    if( ULgrdptr->netptr->pinloc == 0 ) {
	gdptr = ULgrdptr->nnextgrd ;
	while( gdptr->netptr->pinloc == 0 ) {
	    gdptr = gdptr->nnextgrd ;
	}
	if( (int) gdptr->netptr->pinloc == -1 ) {
	    channel = gdptr->netptr->row ;
	} else {  /* pinloc == 1 */
	    channel = gdptr->netptr->row + 1 ;
	}
    } else {
	if( (int) ULgrdptr->netptr->pinloc == -1 ) {
	    channel = ULgrdptr->netptr->row ;
	} else {
	    channel = ULgrdptr->netptr->row + 1 ;
	}
    }
} else {
    if( LLgrdptr->netptr->pinloc == 0 ) {
	gdptr = LLgrdptr->nnextgrd ;
	while( gdptr->netptr->pinloc == 0 ) {
	    gdptr = gdptr->nnextgrd ;
	}
	if( (int) gdptr->netptr->pinloc == -1 ) {
	    channel = gdptr->netptr->row ;
	} else {  /* pinloc == 1 */
	    channel = gdptr->netptr->row + 1 ;
	}
    } else {
	if( (int) LLgrdptr->netptr->pinloc == -1 ) {
	    channel = LLgrdptr->netptr->row ;
	} else {
	    channel = LLgrdptr->netptr->row + 1 ;
	}
    }
    channel++ ;
}
up_channel = channel ;

if( ULgrdptr != GRDNULL ) {
    for( gdptr = ULgrdptr->nextgrd ; gdptr != URgrdptr ; 
				    gdptr = gdptr->nextgrd ) {
	Shuffle[ Ucount++ ] = gdptr ;
    }
    qsortgdx( (char *)Shuffle , Ucount , sizeof( CHANGRDPTR ) ) ;

    ULgrdptr->nnextgrd = Shuffle[ 0 ] ;
    Shuffle[ 0 ]->nprevgrd = ULgrdptr ;
    if( Ucount >= 2 ) {
	for( i = 0 ; i <= Ucount - 2 ; i++ ) {
	    Shuffle[ i ]->nnextgrd = Shuffle[ i+1 ] ;
	    Shuffle[ i+1 ]->nprevgrd = Shuffle[ i ] ;
	}
    }
    Shuffle[ Ucount-1 ]->nnextgrd = URgrdptr ;
    URgrdptr->nprevgrd = Shuffle[ Ucount-1 ] ;

    for( gdptr = ULgrdptr->nnextgrd ; gdptr != URgrdptr ; 
				    gdptr = gdptr->nnextgrd ) {
	x = gdptr->netptr->xpos ;
	dtrack = 0 ;
	if( x != gdptr->netptr->newx ) {
	    denptr = gdptr->dptr ;
	    if( denptr->nnext != DENSENULL ) {
		denptr->nnext->nback = denptr->nback ;
	    }
	    denptr->nback->nnext = denptr->nnext ;

	    tryptr[0] = gdptr->nprevgrd ;
	    if( tryptr[0]->netptr->xpos != x ) {
		tryFlag[ t=0 ] = 0 ;
		while( tryptr[t]->nprevgrd != GRDNULL &&
		       tryptr[t]->nprevgrd->netptr->xpos ==
				    tryptr[0]->netptr->xpos ) {
		    t++ ;
		    tryptr[ t ] = tryptr[ t-1 ]->nprevgrd ;
		    tryFlag[ t ] = 0 ;
		}
		for( i = 0 ; i <= t ; i++ ) {
		    if( tryFlag[i] == 0 ) {
			changes = 0 ;
			trynet = 
			    tearray[tryptr[i]->netptr->terminal]->net ;
			changes += tryptr[i]->nSegType ;
			for( j = i+1 ; j <= t ; j++ ) {
			    if( tearray[tryptr[j]->netptr->terminal]
						    ->net == trynet ) {
				tryFlag[j] = 1 ;
				changes += tryptr[j]->nSegType ;
			    }
			}
			if( changes < 0 ) {
			    dtrack += changes ;
			}
		    }
		}
		tryptr[0] = gdptr->nnextgrd ;
		if( tryptr[0]->netptr->xpos == x ) {
		    tryFlag[ t=0 ] = 0 ;
		    while( tryptr[t]->nnextgrd != GRDNULL &&
			   tryptr[t]->nnextgrd->netptr->xpos ==
					tryptr[0]->netptr->xpos ) {
			t++ ;
			tryptr[ t ] = tryptr[ t-1 ]->nnextgrd ;
			tryFlag[ t ] = 0 ;
		    }
		    for( i = 0 ; i <= t ; i++ ) {
			if( tryFlag[i] == 0 ) {
			    changes = 0 ;
			    trynet = 
			      tearray[tryptr[i]->netptr->terminal]->net;
			    changes += tryptr[i]->nSegType ;
			    for( j = i+1 ; j <= t ; j++ ) {
				if( tearray[tryptr[j]->netptr->terminal]
						    ->net == trynet ) {
				    tryFlag[j] = 1 ;
				    changes += tryptr[j]->nSegType ;
				}
			    }
			    if( changes > 0 ) {
				dtrack += changes ;
			    }
			}
		    }
		}
	    }
			
	    gdptr->ntracks = gdptr->nprevgrd->ntracks + dtrack ;
	    track = gdptr->ntracks ;

	    headptr = DboxHead[ channel ][ track ]->nnext ;
	    if( headptr != DENSENULL ) {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext  = headptr ;
		headptr->nback = denptr  ;
		denptr->nback  = DboxHead[ channel ][ track ] ;
	    } else {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = DENSENULL ;
		denptr->nback = DboxHead[ channel ][ track ];
	    }
	}
    }
}

if( LLgrdptr != GRDNULL ) {

    channel-- ;
    for( gdptr = LLgrdptr->nextgrd ; gdptr != LRgrdptr ; 
				    gdptr = gdptr->nextgrd ) {
	Shuffle[ Lcount++ ] = gdptr ;
    }
    qsortgdx( (char *)Shuffle , Lcount , sizeof( CHANGRDPTR ) ) ;

    LLgrdptr->nnextgrd = Shuffle[ 0 ] ;
    Shuffle[ 0 ]->nprevgrd = LLgrdptr ;
    if( Lcount >= 2 ) {
	for( i = 0 ; i <= Lcount - 2 ; i++ ) {
	    Shuffle[ i ]->nnextgrd = Shuffle[ i+1 ] ;
	    Shuffle[ i+1 ]->nprevgrd = Shuffle[ i ] ;
	}
    }
    Shuffle[ Lcount-1 ]->nnextgrd = LRgrdptr ;
    LRgrdptr->nprevgrd = Shuffle[ Lcount-1 ] ;

    for( gdptr = LLgrdptr->nnextgrd ; gdptr != LRgrdptr ; 
				    gdptr = gdptr->nnextgrd ) {
	x = gdptr->netptr->xpos ;
	dtrack = 0 ;
	if( x != gdptr->netptr->newx ) {
	    denptr = gdptr->dptr ;
	    if( denptr->nnext != DENSENULL ) {
		denptr->nnext->nback = denptr->nback ;
	    }
	    denptr->nback->nnext = denptr->nnext ;

	    tryptr[0] = gdptr->nprevgrd ;
	    if( tryptr[0]->netptr->xpos != x ) {
		tryFlag[ t=0 ] = 0 ;
		while( tryptr[t]->nprevgrd != GRDNULL &&
		       tryptr[t]->nprevgrd->netptr->xpos ==
				    tryptr[0]->netptr->xpos ) {
		    t++ ;
		    tryptr[ t ] = tryptr[ t-1 ]->nprevgrd ;
		    tryFlag[ t ] = 0 ;
		}
		for( i = 0 ; i <= t ; i++ ) {
		    if( tryFlag[i] == 0 ) {
			changes = 0 ;
			trynet = 
			    tearray[tryptr[i]->netptr->terminal]->net ;
			changes += tryptr[i]->nSegType ;
			for( j = i+1 ; j <= t ; j++ ) {
			    if( tearray[tryptr[j]->netptr->terminal]
						    ->net == trynet ) {
				tryFlag[j] = 1 ;
				changes += tryptr[j]->nSegType ;
			    }
			}
			if( changes < 0 ) {
			    dtrack += changes ;
			}
		    }
		}
		tryptr[0] = gdptr->nnextgrd ;
		if( tryptr[0]->netptr->xpos == x ) {
		    tryFlag[ t=0 ] = 0 ;
		    while( tryptr[t]->nnextgrd != GRDNULL &&
			   tryptr[t]->nnextgrd->netptr->xpos ==
					tryptr[0]->netptr->xpos ) {
			t++ ;
			tryptr[ t ] = tryptr[ t-1 ]->nnextgrd ;
			tryFlag[ t ] = 0 ;
		    }
		    for( i = 0 ; i <= t ; i++ ) {
			if( tryFlag[i] == 0 ) {
			    changes = 0 ;
			    trynet = 
			      tearray[tryptr[i]->netptr->terminal]->net;
			    changes += tryptr[i]->nSegType ;
			    for( j = i+1 ; j <= t ; j++ ) {
				if( tearray[tryptr[j]->netptr->terminal]
						    ->net == trynet ) {
				    tryFlag[j] = 1 ;
				    changes += tryptr[j]->nSegType ;
				}
			    }
			    if( changes > 0 ) {
				dtrack += changes ;
			    }
			}
		    }
		}
	    }
			
	    gdptr->ntracks = gdptr->nprevgrd->ntracks + dtrack ;
	    track = gdptr->ntracks ;

	    headptr = DboxHead[ channel ][ track ]->nnext ;
	    if( headptr != DENSENULL ) {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext  = headptr ;
		headptr->nback = denptr  ;
		denptr->nback  = DboxHead[ channel ][ track ] ;
	    } else {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = DENSENULL ;
		denptr->nback = DboxHead[ channel ][ track ];
	    }
	}
    }
}
if( uneven_cell_height ) {
    if( ULgrdptr != GRDNULL ) {
	channel = up_channel ;
	for( gdptr = ULgrdptr ; gdptr != URgrdptr ; 
				    gdptr = gdptr->nnextgrd ) {
	    netptr = gdptr->netptr ;
	    pinloc = netptr->pinloc ;
	    if( pinloc == 1 ) {
		self_reset = carray[ netptr->cell ]->tileptr->top ;
	    } else if( pinloc == -1 ) {
		self_reset = -carray[ netptr->cell ]->tileptr->bottom ;
	    } else {
		self_reset = 0 ;
	    }
	    gdptr->ntracks += ( self_reset + facing_cellheight( 
			netptr->terminal , netptr->row , pinloc , 
					NEW ) ) / track_spacing ;
	    denptr = gdptr->dptr ;
	    if( denptr->nnext != DENSENULL ) {
		denptr->nnext->nback = denptr->nback ;
	    }
	    denptr->nback->nnext = denptr->nnext ;
	    track = gdptr->ntracks ;

	    headptr = DboxHead[ channel ][ track ]->nnext ;
	    if( headptr != DENSENULL ) {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = headptr ;
		headptr->nback = denptr ;
		denptr->nback = DboxHead[ channel ][ track ] ;
	    } else {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = DENSENULL ;
		denptr->nback = DboxHead[ channel ][ track ] ;
	    }
	}
    }
    if( LLgrdptr != GRDNULL ) {
	channel = up_channel - 1 ;
	for( gdptr = LLgrdptr ; gdptr != LRgrdptr ; 
				    gdptr = gdptr->nnextgrd ) {
	    netptr = gdptr->netptr ;
	    pinloc = netptr->pinloc ;
	    if( pinloc == 1 ) {
		self_reset = carray[ netptr->cell ]->tileptr->top ;
	    } else if( pinloc == -1 ) {
		self_reset = -carray[ netptr->cell ]->tileptr->bottom ;
	    } else {
		self_reset = 0 ;
	    }
	    gdptr->ntracks += ( self_reset + facing_cellheight( 
			netptr->terminal , netptr->row , pinloc , 
					NEW ) ) / track_spacing ;
	    denptr = gdptr->dptr ;
	    if( denptr->nnext != DENSENULL ) {
		denptr->nnext->nback = denptr->nback ;
	    }
	    denptr->nback->nnext = denptr->nnext ;
	    track = gdptr->ntracks ;

	    headptr = DboxHead[ channel ][ track ]->nnext ;
	    if( headptr != DENSENULL ) {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = headptr ;
		headptr->nback = denptr ;
		denptr->nback = DboxHead[ channel ][ track ] ;
	    } else {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = DENSENULL ;
		denptr->nback = DboxHead[ channel ][ track ] ;
	    }
	}
    }
}

for( index = 1 ; index <= netchgs[0] ; index++ ) {
    net = netchgs[index] ;
    b = anet[net] ;
    e = anet[net + 1] - 1 ;
    for( segment = b ; segment <= e ; segment++ ) {
	if( aNetSeg[segment].ncurrent == 0 ) {
	    segptr = aNetSeg[segment].ntop ;
	} else {
	    segptr = aNetSeg[segment].nbot ;
	}
	pin1 = segptr->pin1 ;
	pin2 = segptr->pin2 ;
	if( pin1 > maxterm && pin2 > maxterm ) {
	    continue ;
	}
	ptr1 = segptr->pin1ptr ;
	ptr2 = segptr->pin2ptr ;
	x1 = ptr1->netptr->xpos ;
	x2 = ptr2->netptr->xpos ;
	if( x1 == x2 ) {
	    continue ;
	}
	channel = segptr->channel ;
	if( channel > gtopChan ) {
	    gtopChan = channel ;
	}
	if( channel < gbotChan ) {
	    gbotChan = channel ;
	}
	net = aNetSeg[segment].net ;
	if( ptr1->nSegType >= 0 ) {
	    Flag = 0 ;
	    bptr = ptr1 ;
	    while( bptr->nprevgrd != GRDNULL 
			&& bptr->nprevgrd->netptr->xpos == x1 ) {
		if( tearray[bptr->nprevgrd->netptr->terminal]->net
			== net && bptr->nprevgrd->nSegType < 0 ){
		    Flag = 1 ;
		    sptr = ptr1->nnextgrd ;
		    while( sptr->netptr->xpos == x1 ) {
			sptr = sptr->nnextgrd ;
		    }
		    break ;
		} else {
		    bptr = bptr->nprevgrd ;
		}
	    }
	    if( !Flag ) {
		sptr = ptr1->nnextgrd ;
		while( sptr->netptr->xpos == x1 ) {
		    if( net == tearray[sptr->netptr->terminal]->net 
					&& sptr->nSegType < 0 ) {
			Flag = 1 ;
		    }
		    sptr = sptr->nnextgrd ;
		}
	    }
	    if( !Flag ) {
		sptr = bptr ;
	    }
	} else {
	    sptr = ptr1->nnextgrd ;
	    while( sptr->netptr->xpos == x1 ) {
		sptr = sptr->nnextgrd ;
	    }
	}

	if( ptr2->nSegType <= 0 ) {
	    Flag = 0 ;
	    fptr = ptr2 ;
	    while( fptr->nnextgrd != GRDNULL 
			&& fptr->nnextgrd->netptr->xpos == x2 ) {
		if( tearray[fptr->nnextgrd->netptr->terminal]->net
			== net && fptr->nnextgrd->nSegType > 0 ){
		    Flag = 1 ;
		    eptr = ptr2->nprevgrd ;
		    while( eptr->netptr->xpos == x2 ) {
			eptr = eptr->nprevgrd ;
		    }
		    break ;
		} else {
		    fptr = fptr->nnextgrd ;
		}
	    }
	    if( !Flag ) {
		eptr = ptr2->nprevgrd ;
		while( eptr->netptr->xpos == x2 ) {
		    if( net == tearray[eptr->netptr->terminal]->net 
					&& eptr->nSegType > 0 ) {
			Flag = 1 ;
		    }
		    eptr = eptr->nprevgrd ;
		}
	    }
	    if( !Flag ) {
		eptr = fptr ;
	    }
	} else {
	    eptr = ptr2->nprevgrd ;
	    while( eptr->netptr->xpos == x2 ) {
		eptr = eptr->nprevgrd ;
	    }
	}
	eptr = eptr->nnextgrd ;
	if( pin1 <= maxterm ) {
	    ptr1->nSegType += RIGHT ;
	}
	if( pin2 <= maxterm ) {
	    ptr2->nSegType += LEFT  ;
	}

	for( ptr = sptr ; ptr != eptr ; ptr = ptr->nnextgrd ) {
	    denptr = ptr->dptr ;
	    if( denptr->nnext != DENSENULL ) {
		denptr->nnext->nback = denptr->nback ;
	    }
	    denptr->nback->nnext = denptr->nnext ;
	    track = ++(ptr->ntracks) ;

	    headptr = DboxHead[ channel ][ track ]->nnext ;
	    if( headptr != DENSENULL ) {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext  = headptr ;
		headptr->nback = denptr  ;
		denptr->nback  = DboxHead[ channel ][ track ] ;
	    } else {
		DboxHead[ channel ][ track ]->nnext = denptr ;
		denptr->nnext = DENSENULL ;
		denptr->nback = DboxHead[ channel ][ track ];
	    }
	}
    }
}

for( chan = 1 ; chan <= numChans ; chan++ ) {
    for( track = max_tdensity+30 ; track >= 0 ; track-- ) {
	if( DboxHead[ chan ][ track ]->nnext != DENSENULL ) {
	    break ;
	}
    }
    nmaxTrack[ chan ]  = track ;
    tracks += track ;
}
return;
}
