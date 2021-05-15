/*</
define p:read_min_RValue>=0;
alw(p)
/>*/
/*</
define p:read_min_RValue>0;
som(p)
/>*/
</
define p:module_1=1;
define q:module_4=1;
alw(p->som(q))
/>
/*</
define p1:module_1=1;
define p2:module_2=1;
define p3:module_3=1;
define p4:module_4=1;
som((p1;p2;p3)#)
/>*/
frame(syf,basket_size,basket1,perm,net,nr_group,group_pos,initialize,read_min_RValue,module_1,module_2,module_3,module_4) and (
int module_1<==1 and skip;
int module_2<==0 and skip;
int module_3<==0 and skip;
int module_4<==0 and skip;
int syf <==0 and skip;
int read_min_RValue<==0 and skip;
struct node {
int number and 
char *ident and 
struct node* pred,*child,*sibling,*sibling_prev and 
int depth and 
int orientation and 
struct arc* basic_arc and 
struct arc* firstout,*firstin and 
int potential and 
int flow and 
int mark and 
int time 
};
struct arc {
node *tail$,*head$ and 
struct arc* nextout,*nextin and 
int cost,org_cost and 
int flow and 
int ident 
};
struct network {
char inputfile[200] and 
char clustfile[200] and 
int n,n_trips and 
int max_m,m,m_org,m_impl and 
int primal_unbounded and 
int dual_unbounded and 
int perturbed and 
int feasible and 
int eps and 
int opt_tol and 
int feas_tol and 
int pert_val and 
int bigM and 
float optcost and 
int ignore_impl and 
node *nodes,*stop_nodes and 
arc *arcs,*stop_arcs and 
arc *dummy_arcs,*stop_dummy and 
int iterations and 
int bound_exchanges and 
int checksum 
};
struct basket {
arc *a and 
int cost and 
int abs_cost 
};
int basket_size and skip;
basket basket1[100+300+1] and skip;
basket *perm[100+300+1] and skip;
network net and skip;

 

 
  
  function resize_prob ( network *net,int RValue )
 {
     frame(resize_prob_arc1,resize_prob_node1,resize_prob_stop,resize_prob_root,resize_prob_off,return) and ( 
     int return<==0 and skip;
     arc *resize_prob_arc1 and skip;
     node *resize_prob_node1,*resize_prob_stop,*resize_prob_root and skip;
     int resize_prob_off and skip;
     net->max_m:=net->max_m+300000;
     resize_prob_arc1:=(arc *)realloc(net->arcs,net->max_m*sizeof(arc),RValue);
     if(!resize_prob_arc1) then 
     {
         output ("network ",net->inputfile,": not enough memory\n") and skip;
         fflush(stdout,RValue) and skip;
         return<==1 and RValue:=-1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         resize_prob_off:=(int)resize_prob_arc1-(int)net->arcs;
         net->arcs:=resize_prob_arc1;
         net->stop_arcs:=resize_prob_arc1+net->m;
         resize_prob_node1:=net->nodes  ; resize_prob_root:=resize_prob_node1;
         resize_prob_node1:=resize_prob_node1+1 ; resize_prob_stop:=(void *)net->stop_nodes;
         while(resize_prob_node1<resize_prob_stop)
         {
             if(resize_prob_node1->pred!=resize_prob_root) then 
             {
                 resize_prob_node1->basic_arc:=(arc *)((int)resize_prob_node1->basic_arc+resize_prob_off)
             }
             else 
             {
                  skip 
             };
             resize_prob_node1:=resize_prob_node1+1
             
         };
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function compute_red_cost ( int cost,node *tail$,int head_potential,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=(cost-tail$->potential+head_potential);
     skip
     )
     }; 
  function insert_new_arc ( arc *new,int newpos,node *tail$,node *head$,int cost,int red_cost )
 {
     frame(insert_new_arc_pos,return) and ( 
     int return<==0 and skip;
     int insert_new_arc_pos and skip;
     new[newpos].tail$:=tail$;
     new[newpos].head$:=head$;
     new[newpos].org_cost:=cost;
     new[newpos].cost:=cost;
     new[newpos].flow:=(int)red_cost;
     insert_new_arc_pos:=newpos+1;
     while((insert_new_arc_pos-1) AND red_cost>(int)new[insert_new_arc_pos/2-1].flow)
     {
         new[insert_new_arc_pos-1].tail$:=new[insert_new_arc_pos/ 2-1].tail$;
         new[insert_new_arc_pos-1].head$:=new[insert_new_arc_pos/ 2-1].head$;
         new[insert_new_arc_pos-1].cost:=new[insert_new_arc_pos/ 2-1].cost;
         new[insert_new_arc_pos-1].org_cost:=new[insert_new_arc_pos/ 2-1].cost;
         new[insert_new_arc_pos-1].flow:=new[insert_new_arc_pos/ 2-1].flow;
         insert_new_arc_pos:=insert_new_arc_pos/ 2;
         new[insert_new_arc_pos-1].tail$:=tail$;
         new[insert_new_arc_pos-1].head$:=head$;
         new[insert_new_arc_pos-1].cost:=cost;
         new[insert_new_arc_pos-1].org_cost:=cost;
         new[insert_new_arc_pos-1].flow:=(int)red_cost
     };
      return<==1 and skip
     )
     }; 
  function replace_weaker_arc ( arc *new,node *tail$,node *head$,int cost,int red_cost )
 {
     frame(replace_weaker_arc_pos,replace_weaker_arc_cmp,return) and ( 
     int return<==0 and skip;
     int replace_weaker_arc_pos and skip;
     int replace_weaker_arc_cmp and skip;
     new[0].tail$:=tail$;
     new[0].head$:=head$;
     new[0].org_cost:=cost;
     new[0].cost:=cost;
     new[0].flow:=(int)red_cost;
     replace_weaker_arc_pos:=1;
     replace_weaker_arc_cmp:=( if((new[1].flow>new[2].flow)) then 2 else 3);
     while(replace_weaker_arc_cmp<=300000 AND red_cost<new[replace_weaker_arc_cmp-1].flow)
     {
         new[replace_weaker_arc_pos-1].tail$:=new[replace_weaker_arc_cmp-1].tail$;
         new[replace_weaker_arc_pos-1].head$:=new[replace_weaker_arc_cmp-1].head$;
         new[replace_weaker_arc_pos-1].cost:=new[replace_weaker_arc_cmp-1].cost;
         new[replace_weaker_arc_pos-1].org_cost:=new[replace_weaker_arc_cmp-1].cost;
         new[replace_weaker_arc_pos-1].flow:=new[replace_weaker_arc_cmp-1].flow;
         new[replace_weaker_arc_cmp-1].tail$:=tail$;
         new[replace_weaker_arc_cmp-1].head$:=head$;
         new[replace_weaker_arc_cmp-1].cost:=cost;
         new[replace_weaker_arc_cmp-1].org_cost:=cost;
         new[replace_weaker_arc_cmp-1].flow:=(int)red_cost;
         replace_weaker_arc_pos:=replace_weaker_arc_cmp;
         replace_weaker_arc_cmp:=replace_weaker_arc_cmp*2;
         if(replace_weaker_arc_cmp+1<=300000) then 
         {
             if(new[replace_weaker_arc_cmp-1].flow<new[replace_weaker_arc_cmp].flow) then 
             {
                 replace_weaker_arc_cmp:=replace_weaker_arc_cmp+1
             }
             else 
             {
                  skip 
             }
         }
         else 
         {
              skip 
         }
     };
      return<==1 and skip
     )
     }; 
  function price_out_impl ( network *net,int RValue )
 {
     frame(price_out_impl_i,price_out_impl_trips,price_out_impl_new_arcs,price_out_impl_resized,price_out_impl_latest,price_out_impl_min_impl_duration,price_out_impl_bigM,price_out_impl_head_potential,price_out_impl_arc_cost,price_out_impl_red_cost,price_out_impl_bigM_minus_min_impl_duration,price_out_impl_arcout,price_out_impl_arcin,price_out_impl_arcnew,price_out_impl_stop,price_out_impl_first_of_sparse_list,price_out_impl_tail$,price_out_impl_head$,return,continue) and ( 
     int continue<==0 and skip;
     int return<==0 and skip;
     int price_out_impl_i and skip;
     int price_out_impl_trips and skip;
     int price_out_impl_new_arcs<==0 and skip;
     int price_out_impl_resized<==0 and skip;
     int price_out_impl_latest and skip;
     int price_out_impl_min_impl_duration<==15 and skip;
     int price_out_impl_bigM<==net->bigM and skip;
     int price_out_impl_head_potential and skip;
     int price_out_impl_arc_cost<==30 and skip;
     int price_out_impl_red_cost and skip;
     int price_out_impl_bigM_minus_min_impl_duration and skip;
     arc *price_out_impl_arcout,*price_out_impl_arcin,*price_out_impl_arcnew,*price_out_impl_stop and skip;
     arc *price_out_impl_first_of_sparse_list and skip;
     node *price_out_impl_tail$,*price_out_impl_head$ and skip;
     price_out_impl_bigM_minus_min_impl_duration:=(int)price_out_impl_bigM-price_out_impl_min_impl_duration;
     if((net->m+300000)>net->max_m AND (((net->n_trips*net->n_trips)/2+net->m)>net->max_m)) then 
     {
         price_out_impl_resized:=1;
         if(extern resize_prob(net,RValue)) then 
         {
             return<==1 and RValue:=-1;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             refresh_neighbour_lists(net,RValue)
         }
         else
         {
             skip
         }
         
     }
     else 
     {
          skip 
     };
     if(return=0)  then
     {
         price_out_impl_arcnew:=net->stop_arcs;
         price_out_impl_trips:=net->n_trips;
         price_out_impl_arcout:=net->arcs;
         price_out_impl_i:=0;
         
         while(price_out_impl_i<price_out_impl_trips AND price_out_impl_arcout[1].ident=-1)
         {
             price_out_impl_i:=price_out_impl_i+1 ; price_out_impl_arcout:=price_out_impl_arcout+3
             
         };
         price_out_impl_first_of_sparse_list:=(arc *)NULL;
         continue<==0 and skip;
         while(price_out_impl_i<price_out_impl_trips)
         {
              continue<==0 and skip;
             if(price_out_impl_arcout[1].ident!=-1) then 
             {
                 price_out_impl_arcout->head$->firstout->head$->mark:=(unsigned int)price_out_impl_first_of_sparse_list;
                 price_out_impl_first_of_sparse_list:=price_out_impl_arcout+1
                 
             }
             else 
             {
                  skip 
             };
             if(price_out_impl_arcout->ident=-1) then 
             {
                 continue<==1 and skip;
                  price_out_impl_i:=price_out_impl_i+1 ; price_out_impl_arcout:=price_out_impl_arcout+3
				}
                 else 
                 {
                      skip 
                 };
                 if(continue=0)   then 
                 {
                     price_out_impl_head$:=price_out_impl_arcout->head$;
                     price_out_impl_latest:=price_out_impl_head$->time-price_out_impl_arcout->org_cost+(int)price_out_impl_bigM_minus_min_impl_duration;
                     price_out_impl_head_potential:=price_out_impl_head$->potential;
                     price_out_impl_arcin:=(arc *)price_out_impl_first_of_sparse_list->tail$->mark;
                     while(price_out_impl_arcin)
                     {
                         continue<==0 and skip;
                         price_out_impl_tail$:=price_out_impl_arcin->tail$;
                         if(price_out_impl_tail$->time+price_out_impl_arcin->org_cost>price_out_impl_latest) then 
                         {
                             price_out_impl_arcin:=(arc *)price_out_impl_tail$->mark;
                             continue<==1 and skip
                         }
                         else 
                         {
                              skip 
                         };
                         if(continue=0)   then 
                         {
                             price_out_impl_red_cost:=compute_red_cost(price_out_impl_arc_cost,price_out_impl_tail$,price_out_impl_head_potential,RValue);
                             if(price_out_impl_red_cost<0) then 
                             {
                                 if(price_out_impl_new_arcs<300000) then 
                                 {
                                     insert_new_arc(price_out_impl_arcnew,price_out_impl_new_arcs,price_out_impl_tail$,price_out_impl_head$,price_out_impl_arc_cost,price_out_impl_red_cost);
                                     price_out_impl_new_arcs:=price_out_impl_new_arcs+1
                                 }
                                 else
                                 {
                                     if((int)price_out_impl_arcnew[0].flow>price_out_impl_red_cost) then 
                                     {
                                         replace_weaker_arc(price_out_impl_arcnew,price_out_impl_tail$,price_out_impl_head$,price_out_impl_arc_cost,price_out_impl_red_cost)
                                     }
                                     else 
                                     {
                                          skip 
                                     }
                                 }
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             price_out_impl_arcin:=(arc *)price_out_impl_tail$->mark
                         }
                         else
                         {
                             skip
                         }
                     };
                     continue<==0 and skip;
                     price_out_impl_i:=price_out_impl_i+1 ; price_out_impl_arcout:=price_out_impl_arcout+3
                 }
                 else
                 {
                     skip
                 }
                 
             };
             continue<==0 and skip;
             if(price_out_impl_new_arcs) then 
             {
                 price_out_impl_arcnew:=net->stop_arcs;
                 net->stop_arcs:=net->stop_arcs+price_out_impl_new_arcs;
                 price_out_impl_stop:=(void *)net->stop_arcs;
                 if(price_out_impl_resized) then 
                 {
                     while(price_out_impl_arcnew!=price_out_impl_stop)
                     {
                         price_out_impl_arcnew->flow:=(int)0;
                         price_out_impl_arcnew->ident:=1;
                         price_out_impl_arcnew:=price_out_impl_arcnew+1
                         
                     }
                     
                 }
                 else
                 {
                     while(price_out_impl_arcnew!=price_out_impl_stop)
                     {
                         price_out_impl_arcnew->flow:=(int)0;
                         price_out_impl_arcnew->ident:=1;
                         price_out_impl_arcnew->nextout:=price_out_impl_arcnew->tail$->firstout;
                         price_out_impl_arcnew->tail$->firstout:=price_out_impl_arcnew;
                         price_out_impl_arcnew->nextin:=price_out_impl_arcnew->head$->firstin;
                         price_out_impl_arcnew->head$->firstin:=price_out_impl_arcnew;
                         price_out_impl_arcnew:=price_out_impl_arcnew+1
                         
                     }
                 };
                 net->m:=net->m+price_out_impl_new_arcs;
                 net->m_impl:=net->m_impl+price_out_impl_new_arcs
                 
             }
             else 
             {
                  skip 
             };
             return<==1 and RValue:=price_out_impl_new_arcs;
             skip
         }
         else
         {
             skip
         }
         )
         }; 
  function suspend_impl ( network *net,int threshold,int all,int RValue )
 {
     frame(suspend_impl_susp,suspend_impl_red_cost,suspend_impl_new_arc,suspend_impl_arc1,suspend_impl_stop,return) and ( 
     int return<==0 and skip;
     int suspend_impl_susp and skip;
     int suspend_impl_red_cost and skip;
     arc *suspend_impl_new_arc,*suspend_impl_arc1 and skip;
     void *suspend_impl_stop and skip;
     if(all) then 
     {
         suspend_impl_susp:=net->m_impl
     }
     else
     {
         suspend_impl_stop:=(void *)net->stop_arcs;
         suspend_impl_new_arc:=&(net->arcs[net->m-net->m_impl]);
         suspend_impl_susp:=0 ; suspend_impl_arc1:=suspend_impl_new_arc;
         while(suspend_impl_arc1<(arc *)suspend_impl_stop)
         {
             if(suspend_impl_arc1->ident=1) then 
             {
                 suspend_impl_red_cost:=suspend_impl_arc1->cost-suspend_impl_arc1->tail$->potential+suspend_impl_arc1->head$->potential
             }
             else
             {
                 suspend_impl_red_cost:=(int)(-2);
                 if(suspend_impl_arc1->ident=0) then 
                 {
                     if(suspend_impl_arc1->tail$->basic_arc=suspend_impl_arc1) then 
                     {
                         suspend_impl_arc1->tail$->basic_arc:=suspend_impl_new_arc
                     }
                     else
                     {
                         suspend_impl_arc1->head$->basic_arc:=suspend_impl_new_arc
                     }
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             if(suspend_impl_red_cost>threshold) then 
             {
                 suspend_impl_susp:=suspend_impl_susp+1
             }
             else
             {
                 * suspend_impl_new_arc:=* suspend_impl_arc1;
                 suspend_impl_new_arc:=suspend_impl_new_arc+1
             };
             suspend_impl_arc1:=suspend_impl_arc1+1
             
         }
     };
     if(suspend_impl_susp) then 
     {
         net->m:=net->m-suspend_impl_susp;
         net->m_impl:=net->m_impl-suspend_impl_susp;
         net->stop_arcs:=net->stop_arcs-suspend_impl_susp;
         refresh_neighbour_lists(net,RValue)
         
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=suspend_impl_susp;
     skip
     )
     }; 

 function ABS ( int x,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(x>=0) then 
     {
         return<==1 and RValue:=x;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         return<==1 and RValue:=(-x);
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function MAX ( int a,int b,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(a>b) then 
     {
         return<==1 and RValue:=a;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         return<==1 and RValue:=b;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function FREE ( void *vec )
 {
     if(vec) then 
     {
         free(vec) and skip
     }
     else 
     {
          skip 
     }
     
 };
 function global_opt ( int RValue )
 {
     frame(fCost,global_opt_new_arcs,return) and ( 
     int return<==0 and skip;
	 float fCost and skip;
     int global_opt_new_arcs and skip;
     global_opt_new_arcs:=-1;
     while(global_opt_new_arcs)
     {
         output ("active arcs                : ",net.m,"\n") and skip;
         primal_net_simplex(&net,RValue);
         output ("simplex iterations         : ",net.iterations,"\n") and skip;
		 fCost <== (extern flow_cost(&net,RValue )) and skip;
         output ("flow value                 : ",fCost,"\n") and skip;
		// printf( "flow value                 : %0.0f\n", fCost) and skip;
         global_opt_new_arcs:=price_out_impl(&net,RValue);
         if(global_opt_new_arcs) then 
         {
             output ("new implicit arcs          : ",global_opt_new_arcs,"\n") and skip
         }
         else 
         {
              skip 
         };
         if(global_opt_new_arcs<0) then 
         {
             output ("not enough memory, exit(-1)\n") and skip;
             exit(-1,RValue) and skip
             
         }
         else 
         {
              skip 
         }
     };
     output ("checksum                   : ",net.checksum,"\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(return) and ( 
	 module_2<==1 and skip;
     int return<==0 and skip;
     output ("\nMCF SPEC version 1.6.I\n") and skip;
     output ("by  Andreas Loebel\n") and skip;
     output ("Copyright (c) 1998,1999   ZIB Berlin\n") and skip;
     output ("All Rights Reserved.\n") and skip;
     output ("\n") and skip;
     memset((void *)(&net),0,(unsigned int)sizeof(network),RValue) and skip;
     net.bigM:=(int)1.0e7;
     strcpy(net.inputfile,"E:/Input/1/inp.in\0") and skip;
	 read_min_RValue:=read_min(&net,RValue);
     if(read_min_RValue) then 
     {
         output ("read error, exit\n") and skip;
         getfree(&net,RValue);
         return<==1 and RValue:=-1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         output ("nodes                      : ",net.n_trips,"\n") and skip;
         primal_start_artificial(&net,RValue);
         global_opt(RValue);
         output ("optimal\n") and skip;
         if(extern write_circulations("mcf.out",&net,RValue)) then 
         {
             getfree(&net,RValue);
			 //output ("come here11111111111111111111111","\n") and skip;
             return<==1 and RValue:=-1;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             getfree(&net,RValue);
			 //output ("come here222222222222222222222222","\n") and skip;
             return<==1 and RValue:=0;
             skip
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function refresh_neighbour_lists ( network *net )
 {
     frame(refresh_neighbour_lists_node1,refresh_neighbour_lists_arc1,refresh_neighbour_lists_stop,return) and ( 
     int return<==0 and skip;
     node *refresh_neighbour_lists_node1 and skip;
     arc *refresh_neighbour_lists_arc1 and skip;
     void *refresh_neighbour_lists_stop and skip;
     refresh_neighbour_lists_node1:=net->nodes;
     refresh_neighbour_lists_stop:=(void *)net->stop_nodes;
     
     while(refresh_neighbour_lists_node1<(node *)refresh_neighbour_lists_stop)
     {
         refresh_neighbour_lists_node1->firstin:=(arc *)NULL;
         refresh_neighbour_lists_node1->firstout:=(arc *)NULL;
         refresh_neighbour_lists_node1:=refresh_neighbour_lists_node1+1
         
     };
     refresh_neighbour_lists_arc1:=net->arcs;
     refresh_neighbour_lists_stop:=(void *)net->stop_arcs;
     
     while(refresh_neighbour_lists_arc1<(arc *)refresh_neighbour_lists_stop)
     {
         refresh_neighbour_lists_arc1->nextout:=refresh_neighbour_lists_arc1->tail$->firstout;
         refresh_neighbour_lists_arc1->tail$->firstout:=refresh_neighbour_lists_arc1;
         refresh_neighbour_lists_arc1->nextin:=refresh_neighbour_lists_arc1->head$->firstin;
         refresh_neighbour_lists_arc1->head$->firstin:=refresh_neighbour_lists_arc1;
         refresh_neighbour_lists_arc1:=refresh_neighbour_lists_arc1+1
         
     };
      return<==1 and skip
     )
     }; 
  function refresh_potential ( network *net,int RValue )
 {
     frame(refresh_potential_stop,refresh_potential_node1,refresh_potential_tmp,refresh_potential_root,refresh_potential_checksum,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     node *refresh_potential_stop<==net->stop_nodes and skip;
     node *refresh_potential_node1,*refresh_potential_tmp and skip;
     node *refresh_potential_root<==net->nodes and skip;
     int refresh_potential_checksum<==0 and skip;
     refresh_potential_node1:=refresh_potential_root ;
	  refresh_potential_stop:=net->stop_nodes;
     while(refresh_potential_node1<(node *)refresh_potential_stop)
     {
         refresh_potential_node1->mark:=0;
         refresh_potential_node1:=refresh_potential_node1+1
         
     };
     refresh_potential_root->potential:=-100000000;
     refresh_potential_node1<==refresh_potential_root->child and skip; 
	 refresh_potential_tmp<==refresh_potential_node1 and skip;
     while(refresh_potential_node1!=refresh_potential_root)
     {
	
         while(refresh_potential_node1)
         {
             if(refresh_potential_node1->orientation=1) then 
             {
                 refresh_potential_node1->potential:=refresh_potential_node1->basic_arc->cost+refresh_potential_node1->pred->potential
             }
             else
             {
                 refresh_potential_node1->potential:=refresh_potential_node1->pred->potential-refresh_potential_node1->basic_arc->cost;
                 refresh_potential_checksum:=refresh_potential_checksum+1
             };
             refresh_potential_tmp:=refresh_potential_node1;
             refresh_potential_node1:=refresh_potential_node1->child
         };
         refresh_potential_node1:=refresh_potential_tmp;
         break$<==0 and skip;
         while( break$=0 AND refresh_potential_node1->pred)
         {
             refresh_potential_tmp:=refresh_potential_node1->sibling;
             if(refresh_potential_tmp) then 
             {
                 refresh_potential_node1:=refresh_potential_tmp;
                 break$<==1 and skip
              }
             else
             {
                 refresh_potential_node1:=refresh_potential_node1->pred
             }
         };

         break$<==0 and skip
     };
     return<==1 and RValue:=refresh_potential_checksum;
     skip
     )
     }; 
  function flow_cost ( network *net,float RValue )
 {
     frame(flow_cost_arc1,flow_cost_node1,flow_cost_stop,flow_cost_fleet,flow_cost_operational_cost,return) and ( 
     int return<==0 and skip;
     arc *flow_cost_arc1 and skip;
     node *flow_cost_node1 and skip;
     void *flow_cost_stop and skip;
     int flow_cost_fleet<==0 and skip;
     int flow_cost_operational_cost<==0 and skip;
     flow_cost_stop:=(void *)net->stop_arcs;
     flow_cost_arc1:=net->arcs;
     
     while(flow_cost_arc1!=(arc *)flow_cost_stop)
     {
         if(flow_cost_arc1->ident=2) then 
         {
             flow_cost_arc1->flow:=1
         }
         else
         {
             flow_cost_arc1->flow:=0
         };
         flow_cost_arc1:=flow_cost_arc1+1
         
     };
     flow_cost_stop:=(void *)net->stop_nodes;
     flow_cost_node1:=net->nodes ; flow_cost_node1:=flow_cost_node1+1;
     while(flow_cost_node1!=(node *)flow_cost_stop)
     {
         flow_cost_node1->basic_arc->flow:=flow_cost_node1->flow;
         flow_cost_node1:=flow_cost_node1+1
         
     };
     flow_cost_stop:=(void *)net->stop_arcs;
     flow_cost_arc1:=net->arcs;
     
     while(flow_cost_arc1!=(arc *)flow_cost_stop)
     {
         if(flow_cost_arc1->flow) then 
         {
             if(!(flow_cost_arc1->tail$->number<0 AND flow_cost_arc1->head$->number>0)) then 
             {
                 if(!flow_cost_arc1->tail$->number) then 
                 {
                     flow_cost_operational_cost:=flow_cost_operational_cost+(flow_cost_arc1->cost-net->bigM);
                     flow_cost_fleet:=flow_cost_fleet+1
                 }
                 else
                 {
                     flow_cost_operational_cost:=flow_cost_operational_cost+flow_cost_arc1->cost
                 }
                 
             }
             else 
             {
                  skip 
             }
             
         }
         else 
         {
              skip 
         };
         flow_cost_arc1:=flow_cost_arc1+1
         
     };
     return<==1 and RValue:=(float)flow_cost_fleet*(float)(net->bigM)+(float)flow_cost_operational_cost;
     skip
     )
     }; 
  function flow_org_cost ( network *net,float RValue )
 {
     frame(flow_org_cost_arc1,flow_org_cost_node1,flow_org_cost_stop,flow_org_cost_fleet,flow_org_cost_operational_cost,return) and ( 
     int return<==0 and skip;
     arc *flow_org_cost_arc1 and skip;
     node *flow_org_cost_node1 and skip;
     void *flow_org_cost_stop and skip;
     int flow_org_cost_fleet<==0 and skip;
     int flow_org_cost_operational_cost<==0 and skip;
     flow_org_cost_stop:=(void *)net->stop_arcs;
     flow_org_cost_arc1:=net->arcs;
     
     while(flow_org_cost_arc1!=(arc *)flow_org_cost_stop)
     {
         if(flow_org_cost_arc1->ident=2) then 
         {
             flow_org_cost_arc1->flow:=(int)1
         }
         else
         {
             flow_org_cost_arc1->flow:=(int)0
         };
         flow_org_cost_arc1:=flow_org_cost_arc1+1
         
     };
     flow_org_cost_stop:=(void *)net->stop_nodes;
     flow_org_cost_node1:=net->nodes ; flow_org_cost_node1:=flow_org_cost_node1+1;
     while(flow_org_cost_node1!=(node *)flow_org_cost_stop)
     {
         flow_org_cost_node1->basic_arc->flow:=flow_org_cost_node1->flow;
         flow_org_cost_node1:=flow_org_cost_node1+1
         
     };
     flow_org_cost_stop:=(void *)net->stop_arcs;
     flow_org_cost_arc1:=net->arcs;
     
     while(flow_org_cost_arc1!=(arc *)flow_org_cost_stop)
     {
         if(flow_org_cost_arc1->flow) then 
         {
             if(!(flow_org_cost_arc1->tail$->number<0 AND flow_org_cost_arc1->head$->number>0)) then 
             {
                 if(!flow_org_cost_arc1->tail$->number) then 
                 {
                     flow_org_cost_operational_cost:=flow_org_cost_operational_cost+(flow_org_cost_arc1->org_cost-net->bigM);
                     flow_org_cost_fleet:=flow_org_cost_fleet+1
                 }
                 else
                 {
                     flow_org_cost_operational_cost:=flow_org_cost_operational_cost+flow_org_cost_arc1->org_cost
                 }
                 
             }
             else 
             {
                  skip 
             }
             
         }
         else 
         {
              skip 
         };
         flow_org_cost_arc1:=flow_org_cost_arc1+1
         
     };
     return<==1 and RValue:=flow_org_cost_fleet*net->bigM+flow_org_cost_operational_cost;
     skip
     )
     }; 
  function primal_feasible ( network *net,int RValue )
 {
     frame(primal_feasible_stop,primal_feasible_node1,primal_feasible_dummy,primal_feasible_stop_dummy,primal_feasible_arc1,primal_feasible_flow,return) and ( 
     int return<==0 and skip;
     void *primal_feasible_stop and skip;
     node *primal_feasible_node1 and skip;
     arc *primal_feasible_dummy<==net->dummy_arcs and skip;
     arc *primal_feasible_stop_dummy<==net->stop_dummy and skip;
     arc *primal_feasible_arc1 and skip;
     int primal_feasible_flow and skip;
     primal_feasible_node1:=net->nodes;
     primal_feasible_stop:=(void *)net->stop_nodes;
     primal_feasible_node1:=primal_feasible_node1+1;
     
     while( return=0 AND  primal_feasible_node1<(node *)primal_feasible_stop)
     {
         primal_feasible_arc1:=primal_feasible_node1->basic_arc;
         primal_feasible_flow:=primal_feasible_node1->flow;
         if(primal_feasible_arc1>=primal_feasible_dummy AND primal_feasible_arc1<primal_feasible_stop_dummy) then 
         {
             if((extern ABS(primal_feasible_flow,RValue))>(int)net->feas_tol) then 
             {
                 output ("PRIMAL NETWORK SIMPLEX: ") and skip;
                 output ("artificial arc1 with nonzero flow, node1 ",primal_feasible_node1->number," (",primal_feasible_flow,")\n") and skip
                 
             }
             else 
             {
                  skip 
             }
             
         }
         else
         {
             if(primal_feasible_flow<(int)(-net->feas_tol) OR (primal_feasible_flow-(int)1)>(int)net->feas_tol) then 
             {
                 output ("PRIMAL NETWORK SIMPLEX: ") and skip;
                 output ("basis primal infeasible (",primal_feasible_flow,")\n") and skip;
                 net->feasible:=0;
                 return<==1 and RValue:=1;
                 skip
                 
             }
             else 
             {
                  skip 
             }
         };
         if(return=0)  then
         {
             primal_feasible_node1:=primal_feasible_node1+1
         }
         else
         {
             skip
         }
         
     };
     if(return=0)   then 
     {
         net->feasible:=1;
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function dual_feasible ( network *net,int RValue )
 {
     frame(dual_feasible_arc1,dual_feasible_stop,dual_feasible_red_cost,nm_1$,break$$,switch$,return) and ( 
     int return<==0 and skip;
     arc *dual_feasible_arc1 and skip;
     arc *dual_feasible_stop<==net->stop_arcs and skip;
     int dual_feasible_red_cost and skip;
     dual_feasible_arc1:=net->arcs;
     
     while( return=0 AND  dual_feasible_arc1<dual_feasible_stop)
     {
         dual_feasible_red_cost:=dual_feasible_arc1->cost-dual_feasible_arc1->tail$->potential+dual_feasible_arc1->head$->potential;
         int switch$ and skip;
         int break$$ and skip;
         break$$<==0 and skip;
          switch$<==0 and skip;
          int nm_1$ and skip;
         nm_1$ := dual_feasible_arc1->ident;
         if (nm_1$=0 OR (switch$=1 AND break$$=0 AND return=0) ) then 
         {
             switch$<==1 and skip
             
         }
         else
         {
             skip
         };
         if (nm_1$=1 OR (switch$=1 AND break$$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             if(dual_feasible_red_cost<(int)(-net->feas_tol)) then 
             {
                 fprintf(stderr,"DUAL NETWORK SIMPLEX: ",RValue) and skip;
                 fprintf(stderr,"basis dual infeasible\n",RValue) and skip;
                 return<==1 and RValue:=1;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 break$$<==1 and skip
              }
             else
             {
                 skip
             }
             
         }
         else
         {
             skip
         };
         if (nm_1$=2 OR (switch$=1 AND break$$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             if(dual_feasible_red_cost>(int)net->feas_tol) then 
             {
                 fprintf(stderr,"DUAL NETWORK SIMPLEX: ",RValue) and skip;
                 fprintf(stderr,"basis dual infeasible\n",RValue) and skip;
                 return<==1 and RValue:=1;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 break$$<==1 and skip
              }
             else
             {
                 skip
             }
             
         }
         else
         {
             skip
         };
         if (nm_1$=-1 OR (switch$=1 AND break$$=0 AND return=0) ) then 
         {
             switch$<==1 and skip
             
         }
         else
         {
             skip
         };
         if(break$$=0 AND return=0) then 
         {
             break$$<==1 and skip
              
         }
         else
         {
              skip
         };
         if(return=0)   then 
         {
             dual_feasible_arc1:=dual_feasible_arc1+1
         }
         else
         {
             skip
         }
         
     }/*;
     if(return=0)   then 
     {
         return<==1 and RValue:=0;
         skip;
         fprintf(stderr,"DUAL NETWORK SIMPLEX: ",RValue) and skip;
         fprintf(stderr,"basis dual infeasible\n",RValue) and skip;
         return<==1 and RValue:=1;
         skip
     }
     else
     {
         skip
     }*/
     )
     }; 
  function getfree ( network *net,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     FREE(net->nodes);
     FREE(net->arcs);
     FREE(net->dummy_arcs);
     net->stop_nodes<==0 and skip ; net->nodes<==net->stop_nodes and skip;
     net->stop_arcs<==0 and skip; net->arcs<==net->stop_arcs and skip;
     net->stop_dummy<==0 and skip; net->dummy_arcs<==net->stop_dummy and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function write_circulations ( char *outfile,network *net,int RValue )
 {
     frame(write_circulations_out,write_circulations_block,write_circulations_arc1,write_circulations_arc2,write_circulations_first_impl,return,break$) and ( 
	 module_4<==1 and skip;
     int break$<==0 and skip;
     int return<==0 and skip;
     FILE *write_circulations_out<==NULL and skip;
     arc *write_circulations_block and skip;
     arc *write_circulations_arc1 and skip;
     arc *write_circulations_arc2 and skip;
     arc *write_circulations_first_impl<==net->stop_arcs-net->m_impl and skip;
     write_circulations_out:=fopen(outfile,"w") ;
     if((write_circulations_out)=NULL) then 
     {
         return<==1 and RValue:=-1;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         refresh_neighbour_lists(net);
         write_circulations_block:=net->nodes[net->n].firstout;
         
         while( return=0 AND  write_circulations_block)
         {
             if(write_circulations_block->flow) then 
             {
                 fprintf(write_circulations_out,"()\n",RValue) and skip;
                 write_circulations_arc1:=write_circulations_block;
                 while( return=0 AND  write_circulations_arc1)
                 {
                     if(write_circulations_arc1>=write_circulations_first_impl) then 
                     {
                         fprintf(write_circulations_out,"***\n",RValue) and skip
                     }
                     else 
                     {
                          skip 
                     };
                     fprintf(write_circulations_out,"%d\n",-write_circulations_arc1->head$->number,RValue) and skip;
                     write_circulations_arc2:=write_circulations_arc1->head$[net->n_trips].firstout;
                     break$<==0 and skip;
                     while( break$=0 AND  write_circulations_arc2)
                     {
                         if(write_circulations_arc2->flow) then 
                         {
                             break$<==1 and skip
                          }
                         else 
                         {
                              skip 
                         };
                         if(break$=0)   then
                         {
                             write_circulations_arc2:=write_circulations_arc2->nextout
                         }
                         else
                         {
                             skip
                         }
                         
                     };
                     break$<==0 and skip;
                     if(!write_circulations_arc2) then 
                     {
                         fclose(write_circulations_out) and skip;
                         return<==1 and RValue:=-1;
                         skip
                         
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)   then 
                     {
                         if(write_circulations_arc2->head$->number) then 
                         {
                             write_circulations_arc1:=write_circulations_arc2
                         }
                         else
                         {
                             write_circulations_arc1:=NULL
                         }
                     }
                     else
                     {
                         skip
                     }
                 }
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)  then
             {
                 write_circulations_block:=write_circulations_block->nextout
             }
             else
             {
                 skip
             }
             
         };
         if(return=0)   then 
         {
             fclose(write_circulations_out) and skip;
             return<==1 and RValue:=0;
             skip
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function bea_compute_red_cost ( arc *arc1,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=arc1->cost-arc1->tail$->potential+arc1->head$->potential;
     skip
     )
     }; 
  function bea_is_dual_infeasible ( arc *arc1,int red_cost,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=((red_cost<0 AND arc1->ident=1) OR (red_cost>0 AND arc1->ident=2));
     skip
     )
     }; 
  function sort_basket ( int min,int max )
 {
     frame(sort_basket_l,sort_basket_r,sort_basket_cut,sort_basket_xchange,count$) and ( 
     int sort_basket_l,sort_basket_r and skip;
     int sort_basket_cut and skip;
     basket *sort_basket_xchange and skip;
     sort_basket_l:=min;
     sort_basket_r:=max;
     sort_basket_cut:=perm[(int)((sort_basket_l+sort_basket_r)/ 2)]->abs_cost;
     int count$<==0 and skip;
     while( ( count$=0 OR sort_basket_l<=sort_basket_r))
     {
         count$:=count$+1;
         while(perm[sort_basket_l]->abs_cost>sort_basket_cut)
         {
             sort_basket_l:=sort_basket_l+1
         };
         while(sort_basket_cut>perm[sort_basket_r]->abs_cost)
         {
             sort_basket_r:=sort_basket_r-1
         };
         if(sort_basket_l<sort_basket_r) then 
         {
             sort_basket_xchange:=perm[sort_basket_l];
             perm[sort_basket_l]:=perm[sort_basket_r];
             perm[sort_basket_r]:=sort_basket_xchange
             
         }
         else 
         {
              skip 
         };
         if(sort_basket_l<=sort_basket_r) then 
         {
             sort_basket_l:=sort_basket_l+1;
             sort_basket_r:=sort_basket_r-1
             
         }
         else 
         {
              skip 
         }
     };
     if(min<sort_basket_r) then 
     {
         sort_basket(min,sort_basket_r)
     }
     else 
     {
          skip 
     };
     if(sort_basket_l<max AND sort_basket_l<=100) then 
     {
         sort_basket(sort_basket_l,max)
     }
     else 
     {
          skip 
     }
     )
     }; 
      int nr_group and skip;
     int group_pos and skip;
     int initialize<==1 and skip;
 function primal_bea_mpp ( int m,arc *arcs,arc *stop_arcs,int *red_cost_of_bea,arc* RValue )
 {
     frame(primal_bea_mpp_i,primal_bea_mpp_next$,primal_bea_mpp_old_group_pos,primal_bea_mpp_arc1,primal_bea_mpp_red_cost,primal_bea_mpp_mygoto,return) and ( 
     int return<==0 and skip;
     int primal_bea_mpp_i,primal_bea_mpp_next$,primal_bea_mpp_old_group_pos and skip;
     arc *primal_bea_mpp_arc1 and skip;
     int primal_bea_mpp_red_cost and skip;
     int primal_bea_mpp_mygoto<==0 and skip;
     if(initialize) then 
     {
         primal_bea_mpp_i:=1;
         
         while(primal_bea_mpp_i<300+100+1)
         {
             perm[primal_bea_mpp_i]:=&(basket1[primal_bea_mpp_i]);
             primal_bea_mpp_i:=primal_bea_mpp_i+1
             
         };
         nr_group:=((m-1)/ 300)+1;
         group_pos:=0;
         basket_size:=0;
         initialize:=0
         
     }
     else
     {
         primal_bea_mpp_i:=2 and primal_bea_mpp_next$:=0;
         while(primal_bea_mpp_i<=100 AND primal_bea_mpp_i<=basket_size)
         {
             primal_bea_mpp_arc1:=perm[primal_bea_mpp_i]->a;
             primal_bea_mpp_red_cost:=bea_compute_red_cost(primal_bea_mpp_arc1,RValue);
             if(extern bea_is_dual_infeasible(primal_bea_mpp_arc1,primal_bea_mpp_red_cost,RValue)) then 
             {
                 primal_bea_mpp_next$:=primal_bea_mpp_next$+1;
                 perm[primal_bea_mpp_next$]->a:=primal_bea_mpp_arc1;
                 perm[primal_bea_mpp_next$]->cost:=primal_bea_mpp_red_cost;
                 perm[primal_bea_mpp_next$]->abs_cost:=ABS(primal_bea_mpp_red_cost,RValue)
                 
             }
             else 
             {
                  skip 
             };
             primal_bea_mpp_i:=primal_bea_mpp_i+1
             
         };
         basket_size:=primal_bea_mpp_next$
     };
     primal_bea_mpp_old_group_pos:=group_pos;
     while(primal_bea_mpp_mygoto=0)
     {
         primal_bea_mpp_mygoto:=1;
         primal_bea_mpp_arc1:=arcs+group_pos;
         while(primal_bea_mpp_arc1<stop_arcs)
         {
             if(primal_bea_mpp_arc1->ident>0) then 
             {
                 primal_bea_mpp_red_cost:=bea_compute_red_cost(primal_bea_mpp_arc1,RValue);
                 if(extern bea_is_dual_infeasible(primal_bea_mpp_arc1,primal_bea_mpp_red_cost,RValue)) then 
                 {
                     basket_size:=basket_size+1;
                     perm[basket_size]->a:=primal_bea_mpp_arc1;
                     perm[basket_size]->cost:=primal_bea_mpp_red_cost;
                     perm[basket_size]->abs_cost:=ABS(primal_bea_mpp_red_cost,RValue)
                     
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else 
             {
                  skip 
             };
             primal_bea_mpp_arc1:=primal_bea_mpp_arc1+nr_group
             
         };
         if((group_pos+1)=nr_group) then 
         {
             group_pos:=group_pos+1;
             group_pos:=0
         }
         else 
         {
             group_pos:=group_pos+1
             
         };
         if(basket_size<100 AND group_pos!=primal_bea_mpp_old_group_pos) then 
         {
             primal_bea_mpp_mygoto:=0
         }
         else 
         {
              skip 
         }
     };
     if(basket_size=0) then 
     {
         initialize:=1;
         * red_cost_of_bea:=0;
         return<==1 and RValue:=NULL;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         sort_basket(1,basket_size);
         * red_cost_of_bea:=perm[1]->cost;
         return<==1 and RValue:=(perm[1]->a);
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function primal_iminus ( int *delta,int *xchange,node *iplus,node *jplus,node **w,node * RValue )
 {
     frame(primal_iminus_iminus,return) and ( 
     int return<==0 and skip;
     node *primal_iminus_iminus<==NULL and skip;
     while(iplus!=jplus)
     {
         if(iplus->depth<jplus->depth) then 
         {
             if(iplus->orientation) then 
             {
                 if(* delta>iplus->flow) then 
                 {
                     primal_iminus_iminus:=iplus;
                     * delta:=iplus->flow;
                     * xchange:=0
                     
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else
             {
                 if(iplus->pred->pred) then 
                 {
                     if(* delta>((int)1-iplus->flow)) then 
                     {
                         primal_iminus_iminus:=iplus;
                         * delta:=((int)1-iplus->flow);
                         * xchange:=0
                         
                     }
                     else 
                     {
                          skip 
                     }
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             iplus:=iplus->pred
         }
         else
         {
             if(!jplus->orientation) then 
             {
                 if(* delta>=jplus->flow) then 
                 {
                     primal_iminus_iminus:=jplus;
                     * delta:=jplus->flow;
                     * xchange:=1
                     
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else
             {
                 if(jplus->pred->pred) then 
                 {
                     if(* delta>=((int)1-jplus->flow)) then 
                     {
                         primal_iminus_iminus:=jplus;
                         * delta:=((int)1-jplus->flow);
                         * xchange:=1
                         
                     }
                     else 
                     {
                          skip 
                     }
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             jplus:=jplus->pred
         }
     };
     * w:=iplus;
     return<==1 and RValue:=primal_iminus_iminus;
     skip
     )
     }; 
  function primal_update_flow ( node *iplus,node *jplus,node *w )
 {
     while(iplus!=w)
     {
         if(iplus->orientation) then 
         {
             iplus->flow:=(int)0
         }
         else
         {
             iplus->flow:=(int)1
         };
         iplus:=iplus->pred
         
     };
     while(jplus!=w)
     {
         if(jplus->orientation) then 
         {
             jplus->flow:=(int)1
         }
         else
         {
             jplus->flow:=(int)0
         };
         jplus:=jplus->pred
         
     }
     
 };
 function primal_net_simplex ( network *net,int RValue )
 {
     frame(primal_net_simplex_delta,primal_net_simplex_new_flow,primal_net_simplex_opt,primal_net_simplex_xchange,primal_net_simplex_new_orientation,primal_net_simplex_iplus,primal_net_simplex_jplus,primal_net_simplex_iminus,primal_net_simplex_jminus,primal_net_simplex_w,primal_net_simplex_bea,primal_net_simplex_bla,primal_net_simplex_arcs,primal_net_simplex_stop_arcs,primal_net_simplex_temp,primal_net_simplex_m,primal_net_simplex_new_set,primal_net_simplex_red_cost_of_bea,primal_net_simplex_iterations,primal_net_simplex_bound_exchanges,primal_net_simplex_checksum,return) and ( 
     int return<==0 and skip;
     int primal_net_simplex_delta and skip;
     int primal_net_simplex_new_flow and skip;
     int primal_net_simplex_opt<==0 and skip;
     int primal_net_simplex_xchange and skip;
     int primal_net_simplex_new_orientation and skip;
     node *primal_net_simplex_iplus and skip;
     node *primal_net_simplex_jplus and skip;
     node *primal_net_simplex_iminus and skip;
     node *primal_net_simplex_jminus and skip;
     node *primal_net_simplex_w and skip;
     arc *primal_net_simplex_bea and skip;
     arc *primal_net_simplex_bla and skip;
     arc *primal_net_simplex_arcs<==net->arcs and skip;
     arc *primal_net_simplex_stop_arcs<==net->stop_arcs and skip;
     node *primal_net_simplex_temp and skip;
     int primal_net_simplex_m<==net->m and skip;
     int primal_net_simplex_new_set and skip;
     int primal_net_simplex_red_cost_of_bea and skip;
     int *primal_net_simplex_iterations<==&(net->iterations) and skip;
     int *primal_net_simplex_bound_exchanges<==&(net->bound_exchanges) and skip;
     int *primal_net_simplex_checksum<==&(net->checksum) and skip;
	 
     while(!primal_net_simplex_opt)
     {
         primal_net_simplex_bea:=primal_bea_mpp(primal_net_simplex_m,primal_net_simplex_arcs,primal_net_simplex_stop_arcs,&primal_net_simplex_red_cost_of_bea,RValue) ;
         if((primal_net_simplex_bea)) then 
         {
             (* primal_net_simplex_iterations):=(* primal_net_simplex_iterations)+1;
             if(primal_net_simplex_red_cost_of_bea>0) then 
             {
                 primal_net_simplex_iplus:=primal_net_simplex_bea->head$;
                 primal_net_simplex_jplus:=primal_net_simplex_bea->tail$
                 
             }
             else
             {
                 primal_net_simplex_iplus:=primal_net_simplex_bea->tail$;
                 primal_net_simplex_jplus:=primal_net_simplex_bea->head$
             };
             primal_net_simplex_delta:=1;
             primal_net_simplex_iminus:=primal_iminus(&primal_net_simplex_delta,&primal_net_simplex_xchange,primal_net_simplex_iplus,primal_net_simplex_jplus,&primal_net_simplex_w,RValue);
             if(!primal_net_simplex_iminus) then 
             {
                 (* primal_net_simplex_bound_exchanges):=(* primal_net_simplex_bound_exchanges)+1;
                 if(primal_net_simplex_bea->ident=2) then 
                 {
                     primal_net_simplex_bea->ident:=1
                 }
                 else
                 {
                     primal_net_simplex_bea->ident:=2
                 };
                 if(primal_net_simplex_delta) then 
                 {
                     primal_update_flow(primal_net_simplex_iplus,primal_net_simplex_jplus,primal_net_simplex_w)
                 }
                 else 
                 {
                      skip 
                 }
             }
             else
             {
                 if(primal_net_simplex_xchange) then 
                 {
                     primal_net_simplex_temp:=primal_net_simplex_jplus;
                     primal_net_simplex_jplus:=primal_net_simplex_iplus;
                     primal_net_simplex_iplus:=primal_net_simplex_temp
                     
                 }
                 else 
                 {
                      skip 
                 };
                 primal_net_simplex_jminus:=primal_net_simplex_iminus->pred;
                 primal_net_simplex_bla:=primal_net_simplex_iminus->basic_arc;
                 if(primal_net_simplex_xchange!=primal_net_simplex_iminus->orientation) then 
                 {
                     primal_net_simplex_new_set:=1
                 }
                 else
                 {
                     primal_net_simplex_new_set:=2
                 };
                 if(primal_net_simplex_red_cost_of_bea>0) then 
                 {
                     primal_net_simplex_new_flow:=1-primal_net_simplex_delta
                 }
                 else
                 {
                     primal_net_simplex_new_flow:=primal_net_simplex_delta
                 };
                 if(primal_net_simplex_bea->tail$=primal_net_simplex_iplus) then 
                 {
                     primal_net_simplex_new_orientation:=1
                 }
                 else
                 {
                     primal_net_simplex_new_orientation:=0
                 };
                 update_tree(!primal_net_simplex_xchange,primal_net_simplex_new_orientation,primal_net_simplex_delta,primal_net_simplex_new_flow,primal_net_simplex_iplus,primal_net_simplex_jplus,primal_net_simplex_iminus,primal_net_simplex_jminus,primal_net_simplex_w,primal_net_simplex_bea,primal_net_simplex_red_cost_of_bea,(int)net->feas_tol,RValue);
                 primal_net_simplex_bea->ident:=0;
                 primal_net_simplex_bla->ident:=primal_net_simplex_new_set;
                 if(!((* primal_net_simplex_iterations-1) % 20)) then 
                 {
                     * primal_net_simplex_checksum:=* primal_net_simplex_checksum + (extern refresh_potential(net, RValue));
                     if((* primal_net_simplex_checksum)>2000000000) then 
                     {
                         output (* primal_net_simplex_checksum,"\n","\n") and skip;
                         fflush(stdout,RValue) and skip
                         
                     }
                     else 
                     {
                          skip 
                     }
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
         }
         else
         {
             primal_net_simplex_opt:=1
         }
     };
	 
     * primal_net_simplex_checksum:=* primal_net_simplex_checksum+(extern refresh_potential(net,RValue));
     primal_feasible(net,RValue);
     dual_feasible(net,RValue);
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function primal_start_artificial ( network *net,int RValue )
 {
     frame(primal_start_artificial_node1,primal_start_artificial_root,primal_start_artificial_arc1,primal_start_artificial_stop,return) and ( 
     int return<==0 and skip;
     node *primal_start_artificial_node1,*primal_start_artificial_root and skip;
     arc *primal_start_artificial_arc1 and skip;
     void *primal_start_artificial_stop and skip;
     primal_start_artificial_node1<==net->nodes and skip; primal_start_artificial_root<==primal_start_artificial_node1 and skip;
     primal_start_artificial_node1:=primal_start_artificial_node1+1;
     primal_start_artificial_root->basic_arc:=NULL;
     primal_start_artificial_root->pred:=NULL;
     primal_start_artificial_root->child:=primal_start_artificial_node1;
     primal_start_artificial_root->sibling:=NULL;
     primal_start_artificial_root->sibling_prev:=NULL;
     primal_start_artificial_root->depth:=(net->n)+1;
     primal_start_artificial_root->orientation:=0;
     primal_start_artificial_root->potential:=-100000000;
     primal_start_artificial_root->flow:=0;
     primal_start_artificial_stop:=(void *)net->stop_arcs;
     primal_start_artificial_arc1:=net->arcs;
     
     while(primal_start_artificial_arc1!=(arc *)primal_start_artificial_stop)
     {
         if(primal_start_artificial_arc1->ident!=-1) then 
         {
             primal_start_artificial_arc1->ident:=1
         }
         else 
         {
              skip 
         };
         primal_start_artificial_arc1:=primal_start_artificial_arc1+1
         
     };
     primal_start_artificial_arc1:=net->dummy_arcs;
     primal_start_artificial_stop:=(void *)net->stop_nodes;
     
     while(primal_start_artificial_node1!=(node *)primal_start_artificial_stop)
     {
         primal_start_artificial_node1->basic_arc:=primal_start_artificial_arc1;
         primal_start_artificial_node1->pred:=primal_start_artificial_root;
         primal_start_artificial_node1->child:=NULL;
         primal_start_artificial_node1->sibling:=primal_start_artificial_node1+1;
         primal_start_artificial_node1->sibling_prev:=primal_start_artificial_node1-1;
         primal_start_artificial_node1->depth:=1;
         primal_start_artificial_arc1->cost:=100000000;
         primal_start_artificial_arc1->ident:=0;
         primal_start_artificial_node1->orientation:=1;
         primal_start_artificial_node1->potential:=0;
         primal_start_artificial_arc1->tail$:=primal_start_artificial_node1;
         primal_start_artificial_arc1->head$:=primal_start_artificial_root;
         primal_start_artificial_node1->flow:=(int)0;
         primal_start_artificial_arc1:=primal_start_artificial_arc1+1 ; primal_start_artificial_node1:=primal_start_artificial_node1+1
         
     };
     primal_start_artificial_node1:=primal_start_artificial_node1-1;
     primal_start_artificial_root:=primal_start_artificial_root+1;
     primal_start_artificial_node1->sibling:=NULL;
     primal_start_artificial_root->sibling_prev:=NULL;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function read_min ( network *net,int RValue )
 {
     frame(read_min_in,read_min_instring,read_min_t,read_min_h,read_min_c,read_min_i,read_min_arc1,read_min_node1,return) and ( 
	 module_3<==1 and skip;
     int return<==0 and skip;
     FILE *read_min_in<==NULL and skip;
     char read_min_instring[201] and skip;
     int read_min_t,read_min_h,read_min_c and skip;
     int read_min_i and skip;
     arc *read_min_arc1 and skip;
     node *read_min_node1 and skip;
     read_min_in:=fopen(net->inputfile,"r") ;
     if((read_min_in)=NULL) then 
     {
         return<==1 and RValue:=-1;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         fgets(read_min_instring,200,read_min_in) and skip;
         if(sscanf(read_min_instring,"%d %d",&read_min_t,&read_min_h,RValue)!=2) then 
         {
             return<==1 and RValue:=-1;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             net->n_trips:=read_min_t;
             net->m_org:=read_min_h;
             net->n:=(read_min_t+read_min_t+1);
             net->m:=(read_min_t+read_min_t+read_min_t+read_min_h);
             net->max_m:=3014656;
             net->nodes<==(node *)(extern calloc(net->n+1,sizeof(node),RValue)) and skip;
             net->dummy_arcs<==(arc *)calloc(net->n,sizeof(arc),RValue) and skip;
             net->arcs<==(arc *)calloc(net->max_m,sizeof(arc),RValue) and skip;
             if(!(net->nodes AND net->arcs AND net->dummy_arcs)) then 
             {
                 output ("read_min(): not enough memory\n") and skip;
                 getfree(net,RValue);
				 //output ("come here3333333333333333333333333","\n") and skip;
                 return<==1 and RValue:=-1;
                 skip
                 
             }
             else 
             {
                  skip 
             };
			   if(return=0)   then 
             {
                 net->stop_nodes:=net->nodes+net->n+1;
                 net->stop_arcs:=net->arcs +net->m;
                 net->stop_dummy:=net->dummy_arcs + net->n;
                 read_min_node1:=net->nodes;
                 read_min_arc1:=net->arcs;
                 read_min_i:=1;
                 
                 while( return=0 AND  read_min_i<=net->n_trips)
                 {
                     fgets(read_min_instring,200,read_min_in) and skip;
                     if(sscanf(read_min_instring,"%d %d",&read_min_t,&read_min_h,RValue)!=2 OR read_min_t>read_min_h) then 
                     {
                         return<==1 and RValue:=-1;
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)   then 
                     {
                         read_min_node1[read_min_i].number:=-read_min_i;
                         read_min_node1[read_min_i].flow:=-1;
                         read_min_node1[read_min_i+net->n_trips].number:=read_min_i;
                         read_min_node1[read_min_i+net->n_trips].flow:=1;
                         read_min_node1[read_min_i].time:=read_min_t;
                         read_min_node1[read_min_i+net->n_trips].time:=read_min_h;
                         read_min_arc1->tail$:=&(read_min_node1[net->n]);
                         read_min_arc1->head$:=&(read_min_node1[read_min_i]);
                         read_min_arc1->cost<==(int)(net->bigM+15) and skip ; 
						 read_min_arc1->org_cost<==read_min_arc1->cost and skip;
                         read_min_arc1->nextout:=read_min_arc1->tail$->firstout;
                         read_min_arc1->tail$->firstout:=read_min_arc1;
                         read_min_arc1->nextin:=read_min_arc1->head$->firstin;
                         read_min_arc1->head$->firstin:=read_min_arc1;
                         read_min_arc1:=read_min_arc1+1;

                         read_min_arc1->tail$:=&(read_min_node1[read_min_i+net->n_trips]);
                         read_min_arc1->head$:=&(read_min_node1[net->n]);
                         read_min_arc1->cost<==15 and skip;
						 read_min_arc1->org_cost<==15 and skip;
                         read_min_arc1->nextout:=read_min_arc1->tail$->firstout;
                         read_min_arc1->tail$->firstout:=read_min_arc1;
                         read_min_arc1->nextin:=read_min_arc1->head$->firstin;
                         read_min_arc1->head$->firstin:=read_min_arc1;
                         read_min_arc1:=read_min_arc1+1;

                         read_min_arc1->tail$:=&(read_min_node1[read_min_i]);
                         read_min_arc1->head$:=&(read_min_node1[read_min_i+net->n_trips]);
                         read_min_arc1->cost<==(int)(2*(extern MAX(net->bigM,(int)1.0e7,RValue))) and skip;
						
						 read_min_arc1->org_cost<==read_min_arc1->cost and skip;
                         read_min_arc1->nextout:=read_min_arc1->tail$->firstout;
                         read_min_arc1->tail$->firstout:=read_min_arc1;
                         read_min_arc1->nextin:=read_min_arc1->head$->firstin;
                         read_min_arc1->head$->firstin:=read_min_arc1;
                         read_min_arc1:=read_min_arc1+1;
                         read_min_i:=read_min_i+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 if(return=0)   then 
                 {
                     if(read_min_i!=net->n_trips+1) then 
                     {
                         return<==1 and RValue:=-1;
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)   then 
                     {
                         read_min_i:=0;
                         
                         while( return=0 AND  read_min_i<net->m_org)
                         {
                             fgets(read_min_instring,200,read_min_in) and skip;
                             if(sscanf(read_min_instring,"%d %d %d",&read_min_t,&read_min_h,&read_min_c,RValue)!=3) then 
                             {
                                 return<==1 and RValue:=-1;
                                 skip
                             }
                             else 
                             {
                                  skip 
                             };
                             if(return=0)   then 
                             {
                                 read_min_arc1->tail$:=&(read_min_node1[read_min_t+net->n_trips]);
                                 read_min_arc1->head$:=&(read_min_node1[read_min_h]);
                                 read_min_arc1->org_cost:=(int)read_min_c;
                                 read_min_arc1->cost:=(int)read_min_c;
                                 read_min_arc1->nextout:=read_min_arc1->tail$->firstout;
                                 read_min_arc1->tail$->firstout:=read_min_arc1;
                                 read_min_arc1->nextin:=read_min_arc1->head$->firstin;
                                 read_min_arc1->head$->firstin:=read_min_arc1;
                                 read_min_i:=read_min_i+1 ; read_min_arc1:=read_min_arc1+1
                             }
                             else
                             {
                                 skip
                             }
                             
                         };
                         if(return=0)   then 
                         {
                             if(net->stop_arcs!=read_min_arc1) then 
                             {
                                 net->stop_arcs:=read_min_arc1;
                                 read_min_arc1:=net->arcs;
                                 net->m:=0;
                                 
                                 while(read_min_arc1<net->stop_arcs)
                                 {
                                     (net->m):=(net->m)+1;
                                     read_min_arc1:=read_min_arc1+1
                                     
                                 };
                                 net->m_org:=net->m
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             fclose(read_min_in) and skip;
                             net->clustfile[0]:=(char)0;
                             read_min_i:=1;
                             
                             while(read_min_i<=net->n_trips)
                             {
                                 net->arcs[3*read_min_i-1].cost:=(int)((-2)*(extern MAX(net->bigM,(int)1.0e7,RValue)));
                                 net->arcs[3*read_min_i-1].org_cost:=(int)((-2)*((extern MAX(net->bigM,(int)1.0e7,RValue))));
                                 read_min_i:=read_min_i+1
                                 
                             };
                             return<==1 and RValue:=0;
                             skip
                         }
                         else
                         {
                             skip
                         }
                     }
                     else
                     {
                         skip
                     }
                 }
                 else
                 {
                     skip
                 }
             }
             else
             {
                 skip
             }
            
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function update_tree ( int cycle_ori,int new_orientation,int delta,int new_flow,node *iplus,node *jplus,node *iminus,node *jminus,node *w,arc *bea,int sigma,int feas_tol )
 {
     frame(update_tree_basic_arc_temp,update_tree_new_basic_arc,update_tree_father,update_tree_temp,update_tree_new_pred,update_tree_orientation_temp,update_tree_depth_temp,update_tree_depth_iminus,update_tree_new_depth,update_tree_flow_temp,update_tree_mygoto,break$) and (
     int break$<==0 and skip;
     arc *update_tree_basic_arc_temp and skip;
     arc *update_tree_new_basic_arc and skip;
     node *update_tree_father and skip;
     node *update_tree_temp and skip;
     node *update_tree_new_pred and skip;
     int update_tree_orientation_temp and skip;
     int update_tree_depth_temp and skip;
     int update_tree_depth_iminus and skip;
     int update_tree_new_depth and skip;
     int update_tree_flow_temp and skip;
     int update_tree_mygoto<==0 and skip;

     if((bea->tail$=jplus AND sigma<0) OR (bea->tail$=iplus AND sigma>0)) then 
     {
         sigma:=ABS(sigma,RValue)
     }
     else
     {
         sigma:=-((extern ABS(sigma,RValue)))
     };
     update_tree_father:=iminus;
     update_tree_father->potential:=update_tree_father->potential+sigma;
     break$<==0 and skip;
     while( break$=0 AND  1)
     {
         update_tree_temp:=update_tree_father->child;
         break$<==0 and skip;
         while( break$=0 AND  1)
         {
             if(update_tree_temp!=NULL OR update_tree_mygoto=2) then 
             {
                 update_tree_mygoto:=0;
                 update_tree_temp->potential:=update_tree_temp->potential+sigma;
                 update_tree_father:=update_tree_temp;
                 break$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 break$<==0 and skip;
                 while( break$=0 AND  1)
                 {
                     if(update_tree_father=iminus) then 
                     {
                         update_tree_mygoto:=3;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         update_tree_temp:=update_tree_father->sibling;
                         if(update_tree_temp) then 
                         {
                             update_tree_mygoto:=2;
                             break$<==1 and skip
                              
                         }
                         else 
                         {
                              skip 
                         };
                         if(break$=0)   then
                         {
                             update_tree_father:=update_tree_father->pred
                         }
                         else
                         {
                             skip
                         }
                     }
                     else
                     {
                         skip
                     }
                 };

                 break$<==0 and skip;
                 if(update_tree_mygoto=3) then 
                 {
                     break$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 }
             }
             else
             {
                 skip
             }
         };
         break$<==0 and skip;
         if(update_tree_mygoto=3) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         }
     };
     break$<==0 and skip;
     update_tree_temp:=iplus;
     update_tree_father:=update_tree_temp->pred;
     update_tree_depth_iminus<==iminus->depth and skip;
	  update_tree_new_depth<==update_tree_depth_iminus and skip;
     update_tree_new_pred:=jplus;
     update_tree_new_basic_arc:=bea;
     while(update_tree_temp!=jminus)
     {
         if(update_tree_temp->sibling) then 
         {
             update_tree_temp->sibling->sibling_prev:=update_tree_temp->sibling_prev
         }
         else 
         {
              skip 
         };
         if(update_tree_temp->sibling_prev) then 
         {
             update_tree_temp->sibling_prev->sibling:=update_tree_temp->sibling
         }
         else
         {
             update_tree_father->child:=update_tree_temp->sibling
         };
         update_tree_temp->pred:=update_tree_new_pred;
         update_tree_temp->sibling:=update_tree_new_pred->child;
         if(update_tree_temp->sibling) then 
         {
             update_tree_temp->sibling->sibling_prev:=update_tree_temp
         }
         else 
         {
              skip 
         };
         update_tree_new_pred->child:=update_tree_temp;
         update_tree_temp->sibling_prev:=0;
         update_tree_orientation_temp:=!(update_tree_temp->orientation);
         if(update_tree_orientation_temp=cycle_ori) then 
         {
             update_tree_flow_temp:=update_tree_temp->flow+delta
         }
         else
         {
             update_tree_flow_temp:=update_tree_temp->flow-delta
         };
         update_tree_basic_arc_temp:=update_tree_temp->basic_arc;
         update_tree_depth_temp:=update_tree_temp->depth;
         update_tree_temp->orientation:=new_orientation;
         update_tree_temp->flow:=new_flow;
         update_tree_temp->basic_arc:=update_tree_new_basic_arc;
         update_tree_temp->depth:=update_tree_new_depth;
         update_tree_new_pred:=update_tree_temp;
         new_orientation:=update_tree_orientation_temp;
         new_flow:=update_tree_flow_temp;
         update_tree_new_basic_arc:=update_tree_basic_arc_temp;
         update_tree_new_depth:=update_tree_depth_iminus-update_tree_depth_temp;
         update_tree_temp:=update_tree_father;
         update_tree_father:=update_tree_temp->pred
     };

     if(delta>feas_tol) then 
     {
         update_tree_temp:=jminus;
         
         while(update_tree_temp!=w)
         {
             update_tree_temp->depth:=update_tree_temp->depth-update_tree_depth_iminus;
             if(update_tree_temp->orientation!=cycle_ori) then 
             {
                 update_tree_temp->flow:=update_tree_temp->flow+delta
             }
             else
             {
                 update_tree_temp->flow:=update_tree_temp->flow-delta
             };
             update_tree_temp:=update_tree_temp->pred
             
         };
         update_tree_temp:=jplus;
         
         while(update_tree_temp!=w)
         {
             update_tree_temp->depth:=update_tree_temp->depth+update_tree_depth_iminus;
             if(update_tree_temp->orientation=cycle_ori) then 
             {
                 update_tree_temp->flow:=update_tree_temp->flow+delta
             }
             else
             {
                 update_tree_temp->flow:=update_tree_temp->flow-delta
             };
             update_tree_temp:=update_tree_temp->pred
             
         }
     }
     else
     {
         update_tree_temp:=jminus;
         while(update_tree_temp!=w)
         {
             update_tree_temp->depth:=update_tree_temp->depth-update_tree_depth_iminus;
             update_tree_temp:=update_tree_temp->pred
             
         };
         update_tree_temp:=jplus;
         
         while(update_tree_temp!=w)
         {
             update_tree_temp->depth:=update_tree_temp->depth+update_tree_depth_iminus;
             update_tree_temp:=update_tree_temp->pred
             
         }
     }
     )
 };
  main(RValue)
 )
