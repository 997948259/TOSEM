/*</
define p:largest_block<5;
alw(p)
/>*/
/*</
define p:largest_block>0;
som(p)
/>*/
/*</
define p:module_1=1;
define q:module_4=1;
alw(p->som(q))
/>*/
</
define p1:module_1=1;
define p2:module_2=1;
define p3:module_3=1;
define p4:module_4=1;
alw(p1->som((p2;p3;p4)#))
/>
frame(EOF,dbglvl,spec_fd,seedi,zfile,bi_buf,bi_valid,window_size,block_start,ins_h,prev_length,strstart,match_start,eofile,lookahead,max_chain_length,max_lazy_match,compr_level,good_match,nice_match,configuration_table,optarg,optind,nextchar,opterr,optopt,first_nonopt,last_nonopt,license_msg,inbuf,outbuf,d_buf,window,prev,ascii,to_stdout,decompress,force,no_name,no_time,recursive,list$,verbose,quiet,do_lzw,test,foreground,progname,maxbits,method,level,exit_code,save_orig_name,last_member,part_nb,time_stamp,ifile_size,env,args,z_suffix,z_len,bytes_in,bytes_out,total_in,total_out,ifname,ofname,remove_ofname,istat,ifd,ofd,insize,inptr,outcnt,intopts,border,cplens,cplext,cpdist,cpdext,bb,bk,mask_bits,lbits,dbits,hufts,msg_done,extra_lbits,extra_dbits,extra_blbits,dyn_ltree,dyn_dtree,static_ltree,static_dtree,bl_tree,l_desc,d_desc,bl_desc,bl_count,bl_order,heap,heap_len,heap_max,depth,length_code,dist_code,base_length,base_dist,flag_buf,last_lit,last_dist,last_flags,flags,flag_bit,opt_len,static_len,compressed_len,input_len,file_type,file_method,pt_len,blocksize,pt_table,bitbuf,subbitbuf,bitcount,j,done,block_mode,orig_len,max_len,literal,lit_base,leaves,parents,peek_bits,valid,decrypt,key,pkzip,ext_header,crc,header_bytes,end_of_array,start_of_array,first_array_element,last_array_element,largest_block,module_1,module_2,module_3,module_4) and (
int module_1<==1 and skip;
int module_2<==0 and skip;
int module_3<==0 and skip;
int module_4<==0 and skip;
 int largest_block<==0 and skip;
 int dbglvl<==4 and skip;
 int EOF<==-1 and skip;
 char* start_of_array and skip;
 char* end_of_array and skip;
 char first_array_element and skip;
 char last_array_element and skip;
 
 struct spec_fd_t {
 int limit and 
 int len$ and 
 int pos and 
 char *buf 
 };
 struct stat {
        int     st_dev and
        int     st_ino and
        int st_mode and
        int      st_nlink and
        int      st_uid and
        int      st_gid and
        int     st_rdev and
        int     st_size and
        int st_atime and
        int st_mtime and
        int st_ctime 
        };
 spec_fd_t  spec_fd[3] and skip;
 int seedi and skip;
 
 function f()
 {
   skip
 };
 
 function ran ( float RValue )
 {
     frame(ran_lo,ran_hi,ran_test,return$) and ( 
     int return$<==0 and skip;
     int ran_lo and skip;
     int ran_hi and skip;
     int ran_test and skip;
     ran_hi:=seedi/ 127773;
     ran_lo:=seedi % 127773;
     ran_test:=16807*ran_lo-2836*ran_hi;
     if(ran_test>0) then 
     {
         seedi:=ran_test
         
     }
     else
     {
         seedi:=ran_test+2147483647
     };
     return$<==1 and RValue:=((float)seedi/ 2147483647);
     skip
     )
     }; 
  function spec_init ( int RValue )
 {
     frame(exit,spec_init_i,spec_init_j,spec_init_limit,return) and ( 
     int return<==0 and skip;
	 int exit and skip;
     int spec_init_i,spec_init_j and skip;
     if(3<dbglvl) then 
     {
         output ("spec_init\n") and skip
     }
     else 
     {
          skip 
     };
     spec_init_i:=0;
     
     while(spec_init_i<3)
     {
         int spec_init_limit<==spec_fd[spec_init_i].limit and skip;
         memset(&spec_fd[spec_init_i],0,sizeof((* spec_fd)),RValue) and skip;
         spec_fd[spec_init_i].limit:=spec_init_limit;
         spec_fd[spec_init_i].buf:=(unsigned char *)malloc(spec_init_limit+(100*1024));
         if(spec_fd[spec_init_i].buf=NULL) then 
         {
             output ("spec_init: Error mallocing memory!\n") and skip;
             exit<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         spec_init_j:=0;
         
         while(spec_init_j<spec_init_limit)
         {
             spec_fd[spec_init_i].buf[spec_init_j]:=0;
             spec_init_j:=spec_init_j+1024
             
         };
         spec_init_i:=spec_init_i+1
         
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_random_load ( int fd,int RValue )
 {
     frame(spec_random_load_i,spec_random_load_j,spec_random_load_random_text,spec_random_load_temp$_1,return) and ( 
     int return<==0 and skip;
     int spec_random_load_i,spec_random_load_j and skip;
     char spec_random_load_random_text[32,(128*1024)] and skip;
     if(4<dbglvl) then 
     {
         output ("Creating Chunks\n") and skip
     }
     else 
     {
          skip 
     };
     spec_random_load_i:=0;
     
     while(spec_random_load_i<32)
     {
         if(5<dbglvl) then 
         {
             output ("Creating Chunk ",spec_random_load_i,"\n") and skip
         }
         else 
         {
              skip 
         };
         spec_random_load_j:=0;
         
         while(spec_random_load_j<(128*1024))
         {
             spec_random_load_random_text[spec_random_load_i,spec_random_load_j]:=(int)(ran(RValue)*256);
             spec_random_load_j:=spec_random_load_j+1
             
         };
         spec_random_load_i:=spec_random_load_i+1
         
     };
     if(4<dbglvl) then 
     {
         output ("Filling input file\n") and skip
     }
     else 
     {
          skip 
     };
     spec_random_load_i:=0;
     
     while(spec_random_load_i<spec_fd[fd].limit)
     {
         float spec_random_load_temp$_1 and skip;
         spec_random_load_temp$_1:=ran(RValue);
         memcpy(spec_fd[fd].buf+spec_random_load_i,spec_random_load_random_text[(int)(spec_random_load_temp$_1*32)],(128*1024),RValue) and skip;
         spec_random_load_i:=spec_random_load_i+(128*1024)
         
     };
     spec_fd[fd].len$:=1024*1024;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_load ( int num,char *filename,int size,int RValue )
 {
     frame(exit,spec_load_fd,spec_load_rc,spec_load_i,spec_load_3_temp$_1,spec_load_4_tmp,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
	 int exit and skip;
     int spec_load_fd,spec_load_rc,spec_load_i and skip;
	
///	 printf(" %s \n",filename) and skip;
     spec_load_fd:=_open(filename,32768,0,RValue);   //修改过
     output(spec_load_fd) and skip; 
     if(spec_load_fd<0) then 
     {
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     spec_fd[num].len$<==0 and spec_fd[num].pos<==spec_fd[num].len$ and skip;
     break$<==0 and skip;
     spec_load_i:=0;
  ///   output("\nyubin333\n") and skip;
	  //不能读取read库
     while( break$=0 AND  spec_load_i<16)
     {
         spec_load_rc:=_read(spec_load_fd,spec_fd[num].buf+spec_load_i,(128*1024),RValue);
		 output("yubin3333:") and skip; 
		 output(spec_load_rc) and skip; 
		 output("\nyubinpppp\n") and skip;
         if(spec_load_rc=0) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             if(spec_load_rc<0) then 
             {
                 int spec_load_3_temp$_1 and skip;
                 exit<==0 and skip 
                 
             }
             else 
             {
                  skip 
             };
             spec_fd[num].len$:=spec_fd[num].len$+spec_load_rc;
             spec_load_i:=spec_load_i+spec_load_rc
			  //output("spec_load_rc:",spec_load_rc) and skip;
			   //output("spec_load_i:",spec_load_i) and skip
         }
         else
         {
             skip
         }
         
     };
	 
	// spec_fd[num].len$:=spec_fd[num].len$+1;
	// output("yubin444\n") and skip;
     break$<==0 and skip;
     _close(spec_load_fd,RValue) and skip;
     while(spec_fd[num].len$<size)
     {
         int spec_load_4_tmp<==size-spec_fd[num].len$ and skip;
         if(spec_load_4_tmp>spec_fd[num].len$) then 
         {
             spec_load_4_tmp:=spec_fd[num].len$
         }
         else 
         {
              skip 
         };
         if(3<dbglvl) then 
         {
             output ("Duplicating ",spec_load_4_tmp," bytes\n") and skip
         }
         else 
         {
              skip 
         };
         memcpy(spec_fd[num].buf+spec_fd[num].len$,spec_fd[num].buf,spec_load_4_tmp,RValue) and skip;
         spec_fd[num].len$:=spec_fd[num].len$+spec_load_4_tmp
     };
	 output("yubin555\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_read ( int fd,unsigned char *buf,int size,int RValue )
 {
     frame(exit,spec_read_rc,return) and ( 
     int return<==0 and skip;
     int spec_read_rc<==0 and skip;
	 int exit and skip;
     if(4<dbglvl) then 
     {
         output ("spec_read: ",fd,", ",buf,"x, ",size," = ") and skip
     }
     else 
     {
          skip 
     };
     if(fd>3) then 
     {
         fprintf(stderr,"spec_read: fd=%d, > 3!\n",fd,RValue) and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     if(spec_fd[fd].pos>=spec_fd[fd].len$) then 
     {
         if(4<dbglvl) then 
         {
             output ("EOF\n") and skip
         }
         else 
         {
              skip 
         };
         return<==1 and RValue:=EOF;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(spec_fd[fd].pos+size>=spec_fd[fd].len$) then 
         {
             spec_read_rc:=spec_fd[fd].len$-spec_fd[fd].pos
             
         }
         else
         {
             spec_read_rc:=size
         };
         memcpy(buf,&(spec_fd[fd].buf[spec_fd[fd].pos]),spec_read_rc,RValue) and skip;
         spec_fd[fd].pos:=spec_fd[fd].pos+spec_read_rc;
         if(4<dbglvl) then 
         {
             output (spec_read_rc,"\n","\n") and skip
         }
         else 
         {
              skip 
         };
         return<==1 and RValue:=spec_read_rc;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function spec_getc ( int fd,int RValue )
 {
     frame(exit,spec_getc_rc,return) and ( 
     int return<==0 and skip;
     int spec_getc_rc<==0 and skip;
	 int exit and skip;
     if(4<dbglvl) then 
     {
         output ("spec_getc: ",fd," = ") and skip
     }
     else 
     {
          skip 
     };
     if(fd>3) then 
     {
         fprintf(stderr,"spec_read: fd=%d, > 3!\n",fd,RValue) and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     if(spec_fd[fd].pos>=spec_fd[fd].len$) then 
     {
         if(4<dbglvl) then 
         {
             output ("EOF\n") and skip
         }
         else 
         {
              skip 
         };
         return<==1 and RValue:=EOF;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         spec_getc_rc:=spec_fd[fd].buf[spec_fd[fd].pos];
         spec_fd[fd].pos:=spec_fd[fd].pos+1;
         if(4<dbglvl) then 
         {
             output (spec_getc_rc,"\n","\n") and skip
         }
         else 
         {
              skip 
         };
         return<==1 and RValue:=spec_getc_rc;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function spec_ungetc ( unsigned char ch,int fd,int RValue )
 {
     frame(exit,spec_ungetc_rc,return) and ( 
     int return<==0 and skip;
     int spec_ungetc_rc<==0 and skip;
	 int exit and skip;
     if(4<dbglvl) then 
     {
         output ("spec_ungetc: ",fd," = ") and skip
     }
     else 
     {
          skip 
     };
     if(fd>3) then 
     {
         fprintf(stderr,"spec_read: fd=%d, > 3!\n",fd,RValue) and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     if(spec_fd[fd].pos<=0) then 
     {
         fprintf(stderr,"spec_ungetc: pos %d <= 0\n",spec_fd[fd].pos,RValue) and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     if(spec_fd[fd].buf[(spec_fd[fd].pos-1)]!=ch) then 
     {
         spec_fd[fd].pos:=spec_fd[fd].pos-1;
         fprintf(stderr,"spec_ungetc: can't unget something that wasn't what was in the buffer!\n",RValue) and skip;
         exit<==0 and skip 
         
     }
     else 
     {
         spec_fd[fd].pos:=spec_fd[fd].pos-1
         
     };
     if(4<dbglvl) then 
     {
         output (spec_ungetc_rc,"\n","\n") and skip
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=ch;
     skip
     )
     }; 
  function spec_rewind ( int fd,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     spec_fd[fd].pos:=0;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_reset ( int fd,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     memset(spec_fd[fd].buf,0,spec_fd[fd].len$,RValue) and skip;
     spec_fd[fd].len$<==0 and spec_fd[fd].pos<==spec_fd[fd].len$ and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_write ( int fd,unsigned char *buf,int size,int RValue )
 {
     frame(exit,return) and ( 
     int return<==0 and skip;
	 int exit and skip;
     if(4<dbglvl) then 
     {
         output ("spec_write: ",fd,", ",buf,"x, ",size," = ") and skip
     }
     else 
     {
          skip 
     };
     if(fd>3) then 
     {
         fprintf(stderr,"spec_write: fd=%d, > 3!\n",fd,RValue) and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     memcpy(&(spec_fd[fd].buf[spec_fd[fd].pos]),buf,size,RValue) and skip;
     spec_fd[fd].len$:=spec_fd[fd].len$+size;
     spec_fd[fd].pos:=spec_fd[fd].pos+size;
     if(4<dbglvl) then 
     {
         output (size,"\n","\n") and skip
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=size;
     skip
     )
     }; 
  function spec_putc ( unsigned char ch,int fd,int RValue )
 {
     frame(exit,return) and ( 
     int return<==0 and skip;
	 int exit and skip;
     if(4<dbglvl) then 
     {
         output ("spec_putc: ",ch,", ",fd," = ") and skip
     }
     else 
     {
          skip 
     };
     if(fd>3) then 
     {
         fprintf(stderr,"spec_write: fd=%d, > 3!\n",fd,RValue) and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     spec_fd[fd].buf[spec_fd[fd].pos]:=ch;
     spec_fd[fd].pos:=spec_fd[fd].pos+1;
     spec_fd[fd].len$:=spec_fd[fd].len$+1;
     return<==1 and RValue:=ch;
     skip
     )
     }; 
function read_dictionary(){
module_4<==1 and skip;
first_array_element<==start_of_array[0] and skip;
last_array_element<==end_of_array[0] and skip
};
function initialize_memory(){
	 module_3<==1 and skip;
	 unsigned int i,j and skip;
	 i<==0 and j<==1 and skip;
	 while( i < 5)
	 {
	    largest_block <== i and skip;
     	i <== j and skip;
	    j <== (2*j+1) and skip
	 };
	 output("largest_block:\n") and skip;
	 output(largest_block) and skip;
	 output("\n") and skip;
	 start_of_array <== (char *) malloc(sizeof(char)*largest_block) and skip;
	 if (start_of_array = NULL)	 then {
		output("Not enough memory for base pool.\n")
	  };
	  end_of_array <== (char *) malloc(sizeof(char)*largest_block) and skip;
	 if (end_of_array = NULL) then {
		output("Not enough memory for base pool.\n")
	  };
	  read_dictionary()
};
  function main ( int argc,char **argv,int RValue )
 {
     frame(exit,main_i,main_j,main_fd,main_level,main_input_size,main_compressed_size,main_input_name,main_validate_array,return) and ( 
	 module_2<==1 and skip;
     int return<==0 and skip;
     int main_i,main_j,main_fd,main_level and skip;
     int main_input_size<==64,main_compressed_size and skip;
     char *main_input_name<=="D:\\Input\\1.txt" and skip;
     unsigned char *main_validate_array and skip;
	 int exit and skip;
     seedi:=10;
	 while(seedi<15000000)
	 {
	 seedi:=seedi+1
	 };
	 seedi:=10;
     if(argc>1) then 
     {
         main_input_name:=argv[1]
     }
     else 
     {
          skip 
     };
     if(argc>2) then 
     {
         main_input_size:=atoi(argv[2],RValue)
     }
     else 
     {
          skip 
     };
     if(argc>3) then 
     {
         main_compressed_size:=atoi(argv[3],RValue)
     }
     else
     {
         main_compressed_size:=main_input_size
     };
     spec_fd[0].limit:=main_input_size*(1024);
     spec_fd[1].limit:=main_compressed_size*(1024);
     spec_fd[2].limit:=main_input_size*(1024);
	 initialize_memory();
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_initbufs (  )
 {
     no_name:=0;
     no_time:=0;
     time_stamp:=0;
     save_orig_name:=0;
     ifile_size:=-1;
     to_stdout:=1
     
 };
 function spec_compress ( int in,int out,int lev,int RValue )
 {
     level:=lev;
     part_nb:=0;
     clear_bufs(RValue);
	 //output("houxia333\n") and skip;
     ifd:=in;
     ofd:=out;
     zip(ifd,ofd,RValue)
	 //output("houxia444\n") and skip
     
 };
 function spec_uncompress ( int in,int out,int lev, int RValue )
 {
     level:=lev;
     part_nb:=0;
     clear_bufs(RValue);
     ifd:=in;
     ofd:=out;
     method:=get_method(1,RValue);
     unzip(ifd,ofd,RValue)
     
 };
 function debug_time ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=0;
     skip
     )
}; 
 int zfile and skip;
 int bi_buf<==0 and skip;
 int bi_valid<==0 and skip;
 function bi_init ( int zipfile )
 {
     zfile:=zipfile;
     bi_buf:=0;
     bi_valid:=0;
     if(zfile!=-1) then 
     {
		 skip
         
     }
     else 
     {
          skip 
     }

     
 };
 function send_bits ( int value,int length )
 {
     if(bi_valid>(int)16-length) then 
     {
         bi_buf:=bi_buf| (value<<bi_valid);
         if(outcnt<16384-2) then 
         {
             outbuf[outcnt]:=(unsigned char)(bi_buf & 255);
             outcnt:=outcnt+1;
             outbuf[outcnt]:=(unsigned char)((unsigned int)bi_buf>>8);
             outcnt:=outcnt+1
             
         }
         else
         {
             outbuf[outcnt]:=(unsigned char)((unsigned char)(bi_buf & 255));
             outcnt:=outcnt+1;
             if(outcnt=16384) then 
             {
                 flush_outbuf(RValue)
             }
             else 
             {
                  skip 
             };
             outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)bi_buf>>8));
             outcnt:=outcnt+1;
             if(outcnt=16384) then 
             {
                 flush_outbuf(RValue)
             }
             else 
             {
                  skip 
             }
         };
         bi_buf:=(unsigned int)value>>(16-bi_valid);
         bi_valid:=bi_valid+length-16
     }
     else
     {
         bi_buf:=bi_buf| (value<<bi_valid);
         bi_valid:=bi_valid+length
     }
     
 };
 function bi_reverse ( int code,int len$,int RValue )
 {
     frame(bi_reverse_res,count$,return) and ( 
     int return<==0 and skip;
     int bi_reverse_res<==0 and skip;
     int count$<==0 and skip;
     while (count$=0 OR (len$-1)>0)
     {
         count$:=count$+1;
         len$:=len$-1;
         bi_reverse_res:=bi_reverse_res| (code & 1);
         code:=code>>1;
		 bi_reverse_res:=bi_reverse_res<<1
     };
         return<==1 and skip;
		 RValue:=bi_reverse_res>>1;
         skip
         )
   }; 
  function bi_windup (  )
 {
     if(bi_valid>8) then 
     {
         if(outcnt<16384-2) then 
         {
             outbuf[outcnt]:=(unsigned char)(bi_buf & 255);
             outcnt:=outcnt+1;
             outbuf[outcnt]:=(unsigned char)((unsigned int)bi_buf>>8);
             outcnt:=outcnt+1
         }
         else
         {
             outbuf[outcnt]:=(unsigned char)((unsigned char)(bi_buf & 255));
             outcnt:=outcnt+1;
             if(outcnt=16384) then 
             {
                 flush_outbuf(RValue)
             }
             else 
             {
                  skip 
             };
             outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)bi_buf>>8));
             outcnt:=outcnt+1;
             if(outcnt=16384) then 
             {
                 flush_outbuf(RValue)
             }
             else 
             {
                  skip 
             }
         }
         
     }
     else
     {
         if(bi_valid>0) then 
         {
             outbuf[outcnt]:=(unsigned char)bi_buf;
             outcnt:=outcnt+1;
             if(outcnt=16384) then 
             {
                 flush_outbuf(RValue)
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
     bi_buf:=0;
     bi_valid:=0
     
 };
 int window_size<==65536 and skip;
 int block_start and skip;
 int ins_h and skip;
 int prev_length and skip;
 int strstart and skip;
 int match_start and skip;
 int eofile and skip;
 int lookahead and skip;
 int max_chain_length and skip;
 int max_lazy_match and skip;
 int compr_level and skip;
 int good_match and skip;
 struct config {
 int good_length and 
 int max_lazy and 
 int nice_length and 
 int max_chain 
 };
 int nice_match and skip;
 config configuration_table[10]<=={{0,0,0,0},{4,4,8,4},{4,5,16,8},{4,6,32,32},{4,4,16,16},{8,16,32,32},{8,16,128,128},{8,32,128,256},{32,128,258,1024},{32,258,258,4096}} and skip;
 function lm_init ( int pack_level,int *flags )
 {
     frame(lm_init_j,return,tmp) and ( 
     int return<==0 and skip;
     int lm_init_j and skip;
	 int tmp and skip;
     if(pack_level<1 OR pack_level>9) then 
     {
         error("bad pack level",RValue)
     }
     else 
     {
          skip 
     };
     compr_level:=pack_level;
     memset((char *)(prev+32768),0,(int)(1<<15)*sizeof((* (prev+32768))),RValue) and skip;
     max_lazy_match:=configuration_table[pack_level].max_lazy;
     good_match:=configuration_table[pack_level].good_length;
     nice_match:=configuration_table[pack_level].nice_length;
     max_chain_length:=configuration_table[pack_level].max_chain;
     if(pack_level=1) then 
     {
         * flags:=* flags| (4)
         
     }
     else
     {
         if(pack_level=9) then 
         {
             * flags:=* flags| (2)
             
         }
         else 
         {
              skip 
         }
     };
     strstart:=0;
     block_start:=0;
     lookahead:=file_read((char *)window,( if(4<=2) then (int)32768 else 2*32768),RValue);
     if(lookahead=0 OR lookahead=(int)EOF) then 
     {
         eofile:=1;
		 lookahead:=0; return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         eofile:=0;
         while(lookahead<262 AND !eofile)
         {
             fill_window(RValue)
         };
         ins_h:=0;
         lm_init_j:=0;
         
         while(lm_init_j<3-1)
         {
		     tmp:=(ins_h<<5) ^ (window[lm_init_j]);
             ins_h:= tmp & ((int)(1<<15)-1);
             lm_init_j:=lm_init_j+1
             
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function intest_match ( int cur_match,int RValue )
 { frame(intest_match_chain_length,intest_match_scan,intest_match_match,intest_match_len$,intest_match_best_len,intest_match_limit,intest_match_strend,intest_match_scan_end1,intest_match_scan_end,count$,return,break$,continue$) and ( 
     int continue$<==0 and skip;
     int break$<==0 and skip;
     int return<==0 and skip;
     int intest_match_chain_length<==max_chain_length and skip;
     unsigned char *intest_match_scan<==window+strstart and skip;
     unsigned char *intest_match_match and skip;
     int intest_match_len$ and skip;
     int intest_match_best_len<==prev_length and skip;
     int intest_match_limit and skip;
	 intest_match_limit<==( if(strstart>(unsigned int)(32768-262)) then strstart-(int)(32768-262) else 0) and skip;
     unsigned char *intest_match_strend<==window+strstart+258 and skip;
     unsigned char intest_match_scan_end1<==intest_match_scan[intest_match_best_len-1] and skip;
     unsigned char intest_match_scan_end<==intest_match_scan[intest_match_best_len] and skip;
     if(prev_length>=good_match) then 
     {
         intest_match_chain_length:=intest_match_chain_length>> (2 )
         
     }
     else 
     {
          skip 
     };
     count$<==0 and skip;
     break$<==0 and skip;
     while( break$=0 AND   ( count$=0 OR cur_match>intest_match_limit AND (intest_match_chain_length)!=0))
     {
	 //output("intest_match_chain_length:",intest_match_chain_length) and skip;
	 //output("\n") and skip;
         count$:=count$+1;
         intest_match_chain_length:=intest_match_chain_length-1;
         continue$<==0 and skip;
         intest_match_match:=window+cur_match;
         if(intest_match_match[intest_match_best_len]!=intest_match_scan_end OR intest_match_match[intest_match_best_len-1]!=intest_match_scan_end1 OR * intest_match_match!=* intest_match_scan OR * (intest_match_match+1)!=intest_match_scan[1]) then 
         {
             intest_match_match:=intest_match_match+1;
             continue$<==1 and skip
          }
         else 
         {
             intest_match_match:=intest_match_match+1
             
         };
         if(continue$=0)   then 
         {
             intest_match_scan:=intest_match_scan+2;
			 intest_match_match:=intest_match_match+1;
			 int count$<==0 and skip;
             while( ( count$=0 OR * (intest_match_scan+1)=* (intest_match_match+1) AND * (intest_match_scan+1)=* (intest_match_match+1) AND * (intest_match_scan+1)=* (intest_match_match+1) AND * (intest_match_scan+1)=* (intest_match_match+1) AND * (intest_match_scan+1)=* (intest_match_match+1) AND * (intest_match_scan+1)=* (intest_match_match+1) AND * (intest_match_scan+1)=* (intest_match_match+1) AND * (intest_match_scan+1)=* (intest_match_match+1) AND intest_match_scan<intest_match_strend))
             {
                 count$:=count$+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1;
                 intest_match_scan:=intest_match_scan+1;
                 intest_match_match:=intest_match_match+1
             };
             intest_match_len$:=258-(int)(intest_match_strend-intest_match_scan);
             intest_match_scan:=intest_match_strend-258;
             if(intest_match_len$>intest_match_best_len) then 
             {
			 //output("执行了match_start:=cur_match!!!\n") and skip;
                 match_start:=cur_match;
                 intest_match_best_len:=intest_match_len$;
                 if(intest_match_len$>=nice_match) then 
                 {
                     break$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     intest_match_scan_end1:=intest_match_scan[intest_match_best_len-1];
                     intest_match_scan_end:=intest_match_scan[intest_match_best_len]
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
         };
		 cur_match:=prev[cur_match & (32768-1)]
     };
     break$<==0 and skip;
     continue$<==0 and skip;
     return<==1 and RValue:=intest_match_best_len;
     skip
     )
     }; 
  function fill_window ()
 {
     frame(fill_window_n,fill_window_m,fill_window_more,fill_window_tmp) and ( 
     int fill_window_n,fill_window_m and skip;
     int fill_window_more and skip;
	 int* fill_window_tmp and skip;
	 fill_window_more<==(unsigned int)(window_size-(unsigned int)lookahead-(unsigned int)strstart) and skip;
     if(fill_window_more=(int)EOF) then 
     {
         fill_window_more:=fill_window_more-1
         
     }
     else
     {
         if(strstart>=32768+(32768-262)) then 
         {
             memcpy((char *)window,(char *)window+32768,(int)32768,RValue) and skip;
             match_start:=match_start-32768;
             strstart:=strstart-32768;
             block_start:=block_start-(int)32768;
             fill_window_n:=0;
             
             while(fill_window_n<(int)(1<<15))
             {
				fill_window_tmp:=prev+32768;
                 fill_window_m:=fill_window_tmp[fill_window_n];
                 fill_window_tmp[fill_window_n]:=(unsigned int)(( if(fill_window_m>=32768) then fill_window_m-32768 else 0));
                 fill_window_n:=fill_window_n+1
                 
             };
             fill_window_n:=0;
             
             while(fill_window_n<32768)
             {
                 fill_window_m:=prev[fill_window_n];
                 prev[fill_window_n]:=(unsigned int)( if(fill_window_m>=32768) then fill_window_m-32768 else 0);
                 fill_window_n:=fill_window_n+1
                 
             };
             fill_window_more:=fill_window_more+32768
             
         }
         else 
         {
              skip 
         }
     };
     if(!eofile) then 
     {
         fill_window_n:=file_read((char *)window+strstart+lookahead,fill_window_more,RValue);
         if(fill_window_n=0 OR fill_window_n=(int)EOF) then 
         {
             eofile:=1
         }
         else
         {
             lookahead:=lookahead+fill_window_n
         }
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function deflate_fast ( int RValue )
 {
     frame(deflate_fast_hash_head,deflate_fast_flush,deflate_fast_match_length,count$,return,deflate_fast_tmp,tmp) and ( 
     int return<==0 and skip;
     int deflate_fast_hash_head and skip;
     int deflate_fast_flush and skip;
     int deflate_fast_match_length<==0 and skip;
	 int *deflate_fast_tmp and skip;
	 int tmp and skip;
     prev_length:=3-1;
     while(lookahead!=0)
     {
		 tmp:=(ins_h<<5) ^ (window[strstart+3-1]);
         ins_h:=tmp & ((int)(1<<15)-1);
		 deflate_fast_tmp:=prev+32768;
		 deflate_fast_hash_head<==deflate_fast_tmp[ins_h] and prev[strstart & (32768-1)]<==deflate_fast_hash_head and skip;
		 deflate_fast_tmp[ins_h]:=strstart;
         if(deflate_fast_hash_head!=0 AND strstart-deflate_fast_hash_head<=(32768-262)) then 
         {
             deflate_fast_match_length:=intest_match(deflate_fast_hash_head,RValue);
             if(deflate_fast_match_length>lookahead) then 
             {
                 deflate_fast_match_length:=lookahead
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
         if(deflate_fast_match_length>=3) then 
         {
             deflate_fast_flush:=ct_tally(strstart-match_start,deflate_fast_match_length-3,RValue);
             lookahead:=lookahead-deflate_fast_match_length;
             if(deflate_fast_match_length<=max_lazy_match) then 
             {
                 deflate_fast_match_length:=deflate_fast_match_length-1;
                 int count$<==0 and skip;
                 while( ( count$=0 OR (deflate_fast_match_length-1)!=0))
                 {
                     count$:=count$+1;
                     deflate_fast_match_length:=deflate_fast_match_length-1;
                     strstart:=strstart+1;
					 tmp:=(ins_h<<5) ^ (window[strstart+3-1]);
                    ins_h:= tmp & ((int)(1<<15)-1);
					deflate_fast_tmp:=prev+32768;
					deflate_fast_hash_head<==deflate_fast_tmp[ins_h] and prev[strstart & (32768-1)]<==deflate_fast_hash_head and skip;
					deflate_fast_tmp[ins_h]:=strstart
                 };
                 strstart:=strstart+1
             }
             else
             {
                 strstart:=strstart+deflate_fast_match_length;
                 deflate_fast_match_length:=0;
                 ins_h:=window[strstart];
				  tmp:=(ins_h<<5) ^ (window[strstart+3-1]);
                 ins_h:=tmp & ((int)(1<<15)-1)
             }
             
         }
         else
         {
             deflate_fast_flush:=ct_tally(0,window[strstart],RValue);
             lookahead:=lookahead-1;
             strstart:=strstart+1
         };
             while(lookahead<262 AND !eofile)
             {
                 fill_window()
             }
         };
         return<==1 and RValue:=flush_block(( if(block_start>=0) then (char *)&window[(int)block_start] else (char *)NULL),(int)strstart-block_start,1,RValue);
         skip
         )
         }; 
  function deflate ( int RValue )
 {
     frame(tmp,deflate_hash_head,deflate_prev_match,deflate_flush,deflate_match_available,deflate_match_length,count$,return,deflate_tmp) and ( 
     int return<==0 and skip;
     int deflate_hash_head and skip;
     int deflate_prev_match and skip;
     int deflate_flush and skip;
     int deflate_match_available<==0 and skip;
     int deflate_match_length<==3-1 and skip;
	 int* deflate_tmp and skip;
	 int tmp and skip;
	 //output("houxia888888\n") and skip;
     /*if(compr_level<=3) then 
     {
         return<==1 and RValue:=deflate_fast(RValue);
         skip
     }
     else 
     {
          skip 
     };*/
	 
     if(return=0)   then 
     {
         while(lookahead!=0)
         {
		  //output("lookahead1:",lookahead) and skip;
			deflate_tmp:=prev+32768;
			tmp:=(ins_h<<5) ^ (window[strstart+3-1]);
             ins_h:= tmp & ((int)(1<<15)-1);
			 deflate_hash_head<==deflate_tmp[ins_h] and prev[strstart & (32768-1)]<==deflate_hash_head and skip;
			 deflate_tmp[ins_h]:=strstart;
             prev_length:=deflate_match_length;
			 deflate_prev_match:=match_start;
			 deflate_match_length:=3-1;
			 /*output("prev_length:",prev_length) and skip;
			 output("max_lazy_match:",max_lazy_match) and skip;
			 output("strstart:",strstart) and skip;
			 output("deflate_hash_head:",deflate_hash_head) and skip;
			 output("deflate_match_available:",deflate_match_available) and skip;
			 output("deflate_match_length:",deflate_match_length) and skip;
			 output("deflate_prev_match:",deflate_prev_match) and skip;
			 */
             if(deflate_hash_head!=0 AND prev_length<max_lazy_match AND strstart-deflate_hash_head<=(32768-262)) then 
             {
			 //output("houxia0\n") and skip;
                 deflate_match_length:=intest_match(deflate_hash_head,RValue);
                 if(deflate_match_length>lookahead) then 
                 {
                     deflate_match_length:=lookahead
                 }
                 else 
                 {
                      skip 
                 };
                 if(deflate_match_length=3 AND strstart-match_start>4096) then 
                 {
                     deflate_match_length:=deflate_match_length-1
                     
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
			 
             if(prev_length>=3 AND deflate_match_length<=prev_length) then 
             {
			 //output("houxia00\n") and skip;
			 //output("strstart-1-deflate_prev_match:",strstart-1-deflate_prev_match) and skip;
			 //output("prev_length-3:",prev_length-3) and skip;
                 deflate_flush:=ct_tally(strstart-1-deflate_prev_match,prev_length-3,RValue);
				 //output("houxia00_1\n") and skip;
                 lookahead:=lookahead-(prev_length-1);
                 prev_length:=prev_length-2;
                 int count$<==0 and skip;
				     count$:=count$+1;
                     strstart:=strstart+1;
					 tmp:=(ins_h<<5) ^ (window[strstart+3-1]);
                     ins_h:=tmp & ((int)(1<<15)-1);
					 deflate_tmp:=prev+32768;
					 deflate_hash_head<==deflate_tmp[ins_h] and prev[strstart & (32768-1)]<==deflate_hash_head and skip;
					 deflate_tmp[ins_h]:=strstart;
				 prev_length:=prev_length-1;

				 //output("houxia00_2\n") and skip;
                 while( count$=0 OR prev_length!=0)
                 {
                     count$:=count$+1;
                     prev_length:=prev_length-1;
                     strstart:=strstart+1;
					 tmp:=(ins_h<<5) ^ (window[strstart+3-1]);
                     ins_h:=tmp & ((int)(1<<15)-1);
					 deflate_tmp:=prev+32768;
					 deflate_hash_head<==deflate_tmp[ins_h] and prev[strstart & (32768-1)]<==deflate_hash_head and skip;
					 deflate_tmp[ins_h]:=strstart
                 };
				 //output("houxia00_3\n") and skip;
                 deflate_match_available:=0;
                 deflate_match_length:=3-1;
                 strstart:=strstart+1;
                 if(deflate_flush) then 
                 {
                     flush_block(( if(block_start>=0) then (char *)&window[(int)block_start] else (char *)NULL),(int)strstart-block_start,0,RValue);
					 block_start:=strstart
					 }
                     else 
                     {
                          skip 
                     }
					 ////output("houxia00_4\n") and skip
                     
                 }
                 else
                 {
				 
                     if(deflate_match_available) then 
                     {
					 //output("houxia000\n") and skip;
                         if(extern ct_tally(0,window[strstart-1],RValue)) then 
                         {
                             flush_block(( if(block_start>=0) then (char *)&window[(int)block_start] else (char *)NULL),(int)strstart-block_start,0,RValue);
							 block_start:=strstart
                         }
                         else 
                         {
                              skip 
                         };
                         strstart:=strstart+1;
                         lookahead:=lookahead-1
                     }
                     else
                     {
                         deflate_match_available:=1;
                         strstart:=strstart+1;
                         lookahead:=lookahead-1
                     }
                 }
				 //output("lookahead:",lookahead) and skip
                 /*while(lookahead<262 AND !eofile)
                 {
                     //fill_window()
					 skip
                 }*/
				 
             };
			 //output("houxia0000\n") and skip;
             if(deflate_match_available) then 
             {
                 ct_tally(0,window[strstart-1],RValue)
             }
             else 
             {
                  skip 
             };
			 //output("houxia00000\n") and skip;
			 
             return<==1 and RValue:=flush_block(( if(block_start>=0) then (char *)&window[(int)block_start] else (char *)NULL),(int)strstart-block_start,1,RValue);
             //output("houxia000001\n") and skip;
			 skip
         }
         else
         {
             skip
         }
		 //output("houxia8888888\n") and skip
       )
}; 
struct option {
char *name and 
int has_arg and 
int *flag and 
int val 
};
     char *optarg<==0 and skip;
     int optind<==0 and skip;
     char *nextchar and skip;
     int opterr<==1 and skip;
     int optopt<=='\0' and skip;
 function my_strlen ( char *str,int RValue )
 {
     frame(my_strlen_n,return) and ( 
     int return<==0 and skip;
     int my_strlen_n<==0 and skip;
     while(* str)
     {
         str:=str+1;
         my_strlen_n:=my_strlen_n+1
     };
     return<==1 and RValue:=my_strlen_n;
     skip
     )
     }; 
  function my_index ( char *str,int chr,char* RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     while( return=0 AND  * str)
     {
         if(* str=chr) then 
         {
             return<==1 and RValue:=(char *)str;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             str:=str+1
         }
         else
         {
             skip
         }
     };
     if(return=0)   then 
     {
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
      int first_nonopt and skip;
     int last_nonopt and skip;
 function exchange ( char **argv )
 {
     frame(exchange_temp,exchange_first,exchange_last) and ( 
     char *exchange_temp,**exchange_first,**exchange_last and skip;
     exchange_first:=&argv[first_nonopt];
     exchange_last:=&argv[optind-1];
     while(exchange_first<exchange_last)
     {
         exchange_temp:=* exchange_first;
         * exchange_first:=* exchange_last;
         * exchange_last:=exchange_temp;
         exchange_first:=exchange_first+1;
         exchange_last:=exchange_last-1
     };
     exchange_first:=&argv[first_nonopt];
     first_nonopt:=first_nonopt+(optind-last_nonopt);
     exchange_last:=&argv[first_nonopt-1];
     while(exchange_first<exchange_last)
     {
         exchange_temp:=* exchange_first;
         * exchange_first:=* exchange_last;
         * exchange_last:=exchange_temp;
         exchange_first:=exchange_first+1;
         exchange_last:=exchange_last-1
     };
     exchange_first:=&argv[first_nonopt];
     last_nonopt:=optind;
     exchange_last:=&argv[last_nonopt-1];
     while(exchange_first<exchange_last)
     {
         exchange_temp:=* exchange_first;
         * exchange_first:=* exchange_last;
         * exchange_last:=exchange_temp;
         exchange_first:=exchange_first+1;
         exchange_last:=exchange_last-1
     }
     )
     }; 
 
 //char *license_msg[]<=={"   Copyright (C) 1992-1993 Jean-loup Gailly","   This program is free software; you can redistribute it and/or modify","   it under the terms of the GNU General Public License as published by","   the Free Software Foundation; either version 2, or (at your option)","   any later version.","","   This program is distributed in the hope that it will be useful,","   but WITHOUT ANY WARRANTY; without even the implied warranty of","   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the","   GNU General Public License for more details.","","   You should have received a copy of the GNU General Public License","   aint with this program; if not, write to the Free Software","   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.",0} and skip;
 unsigned char inbuf[32768+64] and skip;
 unsigned char outbuf[16384+2048] and skip;
 int d_buf[32768] and skip;
 unsigned char window[232768] and skip;
 int prev[1<<16] and skip;
 int ascii<==0 and skip;
 int to_stdout<==0 and skip;
 int decompress<==0 and skip;
 int force<==0 and skip;
 int no_name<==-1 and skip;
 int no_time<==-1 and skip;
 int recursive<==0 and skip;
 int list$<==0 and skip;
 int verbose<==0 and skip;
 int quiet<==0 and skip;
 int do_lzw<==0 and skip;
 int test<==0 and skip;
 int foreground and skip;
 char *progname and skip;
 int maxbits<==16 and skip;
 int method<==8 and skip;
 int level<==6 and skip;
 int exit_code<==0 and skip;
 int save_orig_name and skip;
 int last_member and skip;
 int part_nb and skip;
 int time_stamp and skip;
 int ifile_size and skip;
 char *env and skip;
 char **args<==NULL and skip;
 char z_suffix[30+1] and skip;
 int z_len and skip;
 int bytes_in and skip;
 int bytes_out and skip;
 int total_in<==0 and skip;
 int total_out<==0 and skip;
 char ifname[1024] and skip;
 char ofname[1024] and skip;
 int remove_ofname<==0 and skip;
 struct stat istat and skip;
 int ifd and skip;
 int ofd and skip;
 int insize and skip;
 int inptr and skip;
 int outcnt and skip;
 option intopts[96]<=={{"ascii",0,0,'a'},{"to-stdout",0,0,'c'},{"stdout",0,0,'c'},{"decompress",0,0,'d'},{"uncompress",0,0,'d'},{"force",0,0,'f'},{"help",0,0,'h'},{"list",0,0,'l'},{"license",0,0,'L'},{"no-name",0,0,'n'},{"name",0,0,'N'},{"quiet",0,0,'q'},{"silent",0,0,'q'},{"recursive",0,0,'r'},{"suffix",1,0,'S'},{"test",0,0,'t'},{"no-time",0,0,'T'},{"verbose",0,0,'v'},{"version",0,0,'V'},{"fast",0,0,'1'},{"best",0,0,'9'},{"lzw",0,0,'Z'},{"bits",1,0,'b'},{0,0,0,0}} and skip;
 function usage (  )
 {
     fprintf(stderr,"usage: %s [-%scdfhlLnN%stvV19] [-S suffix] [file ...]\n",progname,"a","",RValue) and skip   
 };
 function help (  )
 {
     frame(help_help_msg,help_p) and ( 
	 printf("help \n") and skip
    /* char *help_help_msg[]<=={" -c --stdout      write on standard output, keep original files unchanged"," -d --decompress  decompress"," -f --force       force overwrite of output file and compress links"," -h --help        give this help"," -l --list        list compressed file contents"," -L --license     display software license"," -n --no-name     do not save or restore the original name and time stamp"," -N --name        save or restore the original name and time stamp"," -q --quiet       suppress all warnings"," -S .suf  --suffix .suf     use suffix .suf on compressed files"," -t --test        test compressed file integrity"," -v --verbose     verbose mode"," -V --version     display version number"," -1 --fast        compress faster"," -9 --best        compress better"," file...          files to (de)compress. If none given, use standard input.",0} and skip;
     char **help_p<==help_help_msg and skip;
     fprintf(stderr,"%s %s (%s)\n",progname,"1.2.4","18 Aug 93",RValue) and skip;
     usage();
     while(* help_p)
     {
         fprintf(stderr,"%s\n",* help_p,RValue) and skip;
         help_p:=help_p+1
     }*/
     )
     }; 
  function license (  )
 {
     frame(license_p) and ( 
	 printf("error license\n") and skip
     //char **license_p<==license_msg and skip;
    // fprintf(stderr,"%s %s (%s)\n",progname,"1.2.4","18 Aug 93",RValue) and skip;
    // while(* license_p)
     //{
         //fprintf(stderr,"%s\n",* license_p,RValue) and skip;
         //license_p:=license_p+1
    // }
     )
     }; 
  function version (  )
 {
     fprintf(stderr,"%s %s (%s)\n",progname,"1.2.4","18 Aug 93",RValue) and skip;
     fprintf(stderr,"Compilation options:\n%s %s ","NO_DIR","NO_UTIME",RValue) and skip;
     fprintf(stderr,"NO_CHOWN ",RValue) and skip;
     fprintf(stderr,"\n",RValue) and skip
     
 };

 
 
  function get_suffix ( char *name,char* RValue )
 {
     frame(get_suffix_nlen,get_suffix_slen,get_suffix_suffix,get_suffix_known_suffixes,get_suffix_suf,get_suffix_4_s,count$,return) and ( 
     int return<==0 and skip;
     int get_suffix_nlen,get_suffix_slen and skip;
     char get_suffix_suffix[30+3] and skip;
     char *get_suffix_known_suffixes[]<=={z_suffix,".gz",".z",".taz",".tgz","-gz","-z","_z",NULL} and skip;
     char **get_suffix_suf<==get_suffix_known_suffixes and skip;
     if((extern strcmp(z_suffix,"z")=0)) then 
     {
         get_suffix_suf:=get_suffix_suf+1
     }
     else 
     {
          skip 
     };
     get_suffix_nlen:=strlen(name) ;
     if(get_suffix_nlen<=30+2) then 
     {
         strcpy(get_suffix_suffix,name) and skip
         
     }
     else
     {
         strcpy(get_suffix_suffix,name+get_suffix_nlen-30-2) and skip
     };
     _strlwr(get_suffix_suffix,RValue) and skip;
     get_suffix_slen:=strlen(get_suffix_suffix);
     int count$<==0 and skip;
     while( return=0 AND   ( count$=0 OR * (get_suffix_suf+1)!=NULL))
     {
         count$:=count$+1;
         get_suffix_suf:=get_suffix_suf+1;
         int get_suffix_4_s and skip;
         get_suffix_4_s:=strlen(* get_suffix_suf);
         if(get_suffix_slen>get_suffix_4_s AND get_suffix_suffix[get_suffix_slen-get_suffix_4_s-1]!='/' AND (strcmp((get_suffix_suffix+get_suffix_slen-get_suffix_4_s),(* get_suffix_suf))=0)) then 
         {
             return<==1 and RValue:=name+get_suffix_nlen-get_suffix_4_s;
             skip
             
         }
         else 
         {
              skip 
         }
     };
     if(return=0)   then 
     {
         return<==1 and RValue:=NULL;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function get_istat ( char *iname,stat *sbuf,int RValue )
 {
     frame(get_istat_ilen,get_istat_suffixes,get_istat_suf,get_istat_s,count$,return) and ( 
     int return<==0 and skip;
     int get_istat_ilen and skip;
     char *get_istat_suffixes[]<=={z_suffix,".gz",".z","-z",".Z",NULL} and skip;
     char **get_istat_suf<==get_istat_suffixes and skip;
     char *get_istat_s and skip;
     strcpy(ifname,iname) and skip;
     if(!decompress) then 
     {
         perror(ifname,RValue) and skip;
         exit_code:=1;
         return<==1 and RValue:=1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         get_istat_s:=get_suffix(ifname,RValue);
         if(get_istat_s!=NULL) then 
         {
             perror(ifname,RValue) and skip;
             exit_code:=1;
             return<==1 and RValue:=1;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             get_istat_ilen:=strlen(ifname);
             if((extern strcmp(z_suffix,".gz")=0)) then 
             {
                 get_istat_suf:=get_istat_suf+1
             }
             else 
             {
                  skip 
             };
             int count$<==0 and skip;
             while( ( count$=0 OR * (get_istat_suf+1)!=NULL))
             {
                 count$:=count$+1;
                 get_istat_suf:=get_istat_suf+1;
                 get_istat_s:=* get_istat_suf;
                 strcat(ifname,get_istat_s) and skip;
                 ifname[get_istat_ilen]:='\0'
             };
             strcat(ifname,z_suffix) and skip;
             perror(ifname,RValue) and skip;
             exit_code:=1;
             return<==1 and RValue:=1;
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
  function make_ofname ( int RValue )
 {
     frame(make_ofname_suff,return) and ( 
     int return<==0 and skip;
     char *make_ofname_suff and skip;
     strcpy(ofname,ifname) and skip;
     make_ofname_suff:=get_suffix(ofname,RValue);
     if(decompress) then 
     {
         if(make_ofname_suff=NULL) then 
         {
             if(!recursive AND (list$ OR test)) then 
             {
                 return<==1 and RValue:=0;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 if(verbose OR (!recursive AND !quiet)) then 
                 {
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 return<==1 and RValue:=2;
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
         };
         if(return=0)  then
         {
             if(return=0)   then 
             {
                 _strlwr(make_ofname_suff,RValue) and skip;
                 if((extern strcmp(make_ofname_suff,".tgz")=0) OR (extern strcmp(make_ofname_suff,".taz")=0)) then 
                 {
                     strcpy(make_ofname_suff,".tar") and skip
                 }
                 else
                 {
                     * make_ofname_suff:='\0'
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
         if(make_ofname_suff!=NULL) then 
         {
             if(verbose OR (!recursive AND !quiet)) then 
             {
                 fprintf(stderr,"%s: %s already has %s suffix -- unchanged\n",progname,ifname,make_ofname_suff,RValue) and skip
                 
             }
             else 
             {
                  skip 
             };
             if(exit_code=0) then 
             {
                 exit_code:=2
             }
             else 
             {
                  skip 
             };
             return<==1 and RValue:=2;
             skip
         }
         else
         {
             save_orig_name:=0;
             strcat(ofname,z_suffix) and skip
         }
     };
     if(return=0)  then
     {
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function get_method ( int in,int RValue )
 {
     frame(get_method_flags,get_method_magic,get_method_stamp,get_method_3_11_part,get_method_3_13_len$,get_method_3_16_17_c,count$,get_method_3_16_19_p,get_method_3_16_19_base,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     unsigned char get_method_flags and skip;
     char get_method_magic[2] and skip;
     int get_method_stamp and skip;
     if(force AND to_stdout) then 
     {
         get_method_magic[0]:=(char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(1,RValue)));
         get_method_magic[1]:=(char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(1,RValue)))
         
     }
     else
     {
         get_method_magic[0]:=(char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
         get_method_magic[1]:=(char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)))
     };
     method:=-1;
     part_nb:=part_nb+1;
     header_bytes:=0;
     last_member:=0;
     if(memcmp(get_method_magic,"\037\213",2,RValue)=0 OR memcmp(get_method_magic,"\037\236",2,RValue)=0) then 
     {
         method:=(int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
         if(method!=8) then 
         {
             fprintf(stderr,"%s: %s: unknown method %d -- get newer version of gzip\n",progname,ifname,method,RValue) and skip;
             exit_code:=1;
             return<==1 and RValue:=-1;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             get_method_flags:=(unsigned char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
             if((get_method_flags & 32)!=0) then 
             {
                 fprintf(stderr,"%s: %s is encrypted -- get newer version of gzip\n",progname,ifname,RValue) and skip;
                 exit_code:=1;
                 return<==1 and RValue:=-1;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 if((get_method_flags & 2)!=0) then 
                 {
                     fprintf(stderr,"%s: %s is a a multi-part gzip file -- get newer version of gzip\n",progname,ifname,RValue) and skip;
                     exit_code:=1;
                     if(force<=1) then 
                     {
                         return<==1 and RValue:=-1;
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
         };
         if(return=0)  then
         {
             if((get_method_flags & 192)!=0) then 
             {
                 fprintf(stderr,"%s: %s has flags 0x%x -- get newer version of gzip\n",progname,ifname,get_method_flags,RValue) and skip;
                 exit_code:=1;
                 if(force<=1) then 
                 {
                     return<==1 and RValue:=-1;
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
         };
         if(return=0)  then
         {
             get_method_stamp:=(unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
             get_method_stamp:=get_method_stamp| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<8);
             get_method_stamp:=get_method_stamp| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<16);
             get_method_stamp:=get_method_stamp| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<24);
             if(get_method_stamp!=0 AND !no_time) then 
             {
                 time_stamp:=get_method_stamp
             }
             else 
             {
                  skip 
             };
             
             if((get_method_flags & 2)!=0) then 
             {
                 int get_method_3_11_part<==(int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))) and skip;
                 get_method_3_11_part:=get_method_3_11_part| (((int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<8);
                 if(verbose) then 
                 {
                     fprintf(stderr,"%s: %s: part number %u\n",progname,ifname,get_method_3_11_part,RValue) and skip
                     
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
             
             if((get_method_flags & 8)!=0) then 
             {
                 if(no_name OR (to_stdout AND !list$) OR part_nb>1) then 
                 {
                     char get_method_3_16_17_c and skip;
                     int count$<==0 and skip;
                     while( count$=0 OR get_method_3_16_17_c!=0)
                     {
                         count$:=count$+1;
                         get_method_3_16_17_c:=(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)))
                     }
                 }
                 else
                 {
                     char *get_method_3_16_19_p and skip;
                     get_method_3_16_19_p:=gzipbasename(ofname,RValue);
                     char *get_method_3_16_19_base<==get_method_3_16_19_p and skip;
                     break$<==0 and skip;
                     while( break$=0 AND  true)
                     {
                         * get_method_3_16_19_p:=(char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
                         if(* get_method_3_16_19_p='\0') then 
                         {
                             get_method_3_16_19_p:=get_method_3_16_19_p+1;
                             break$<==1 and skip
                          }
                         else 
                         {
                             get_method_3_16_19_p:=get_method_3_16_19_p+1
                             
                         };
                         if(break$=0)   then
                         {
                             if(get_method_3_16_19_p>=ofname+1024) then 
                             {
                                 error("corrupted input -- file name too large",RValue)
                                 
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
                     if(!list$) then 
                     {
                         if(get_method_3_16_19_base) then 
                         {
                             list$:=0
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
                  skip 
             };
             if((get_method_flags & 16)!=0) then 
             {
                 while((( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)))!=0)
                 {
				    skip
                 }
                 
             }
             else 
             {
                  skip 
             };
             if(part_nb=1) then 
             {
                 header_bytes:=inptr+2*4
                 
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
         if(memcmp(get_method_magic,"\120\113\003\004",2,RValue)=0 AND inptr=2 AND memcmp((char *)inbuf,"\120\113\003\004",4,RValue)=0) then 
         {
             inptr:=0;
             if(return=0)   then 
             {
                 last_member:=1
             }
             else
             {
                 if(memcmp(get_method_magic,"\037\036",2,RValue)=0) then 
                 {
                     method:=2
                 }
                 else
                 {
                     if(memcmp(get_method_magic,"\037\235",2,RValue)=0) then 
                     {
                         method:=1;
                         last_member:=1
                     }
                     else
                     {
                         if(memcmp(get_method_magic,"\037\240",2,RValue)=0) then 
                         {
                             method:=3;
                             last_member:=1
                         }
                         else
                         {
                             if(force AND to_stdout AND !list$) then 
                             {
                                 method:=0;
                                 inptr:=0;
                                 last_member:=1
                                 
                             }
                             else 
                             {
                                  skip 
                             }
                         }
                     }
                 }
             }
         }
         else
         {
             skip
         }
     };
     if(return=0)  then
     {
         if(method>=0) then 
         {
             return<==1 and RValue:=method;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(part_nb=1) then 
             {
             //    fprintf(stderr,"\n%s: %s: not in gzip format\n",progname,ifname,RValue) and skip;
                 exit_code:=1;
                 return<==1 and RValue:=-1;
                 skip
             }
             else
             {
                 return<==1 and RValue:=-2;
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
  function same_file ( stat *stat1,stat *stat2,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:= (stat1->st_ino=stat2->st_ino AND stat1->st_dev=stat2->st_dev AND stat1->st_mode=stat2->st_mode AND stat1->st_uid=stat2->st_uid AND stat1->st_gid=stat2->st_gid AND stat1->st_size=stat2->st_size AND stat1->st_atime=stat2->st_atime AND stat1->st_mtime=stat2->st_mtime AND stat1->st_ctime=stat2->st_ctime);
     skip
     )
     }; 

  function copy_stat ( stat *ifstat )
 {
     
     remove_ofname:=0;
     if((extern _unlink(ifname,RValue))) then 
     {
         if(!quiet) then 
         {
             perror(ifname,RValue) and skip
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

  function abort_gzip (  )
 {
     if(remove_ofname) then 
     {
         _close(ofd,RValue) and skip;
         _unlink(ofname,RValue) and skip      
     }
     else 
     {
          skip 
     }   
 };
 union struct$0 {
 int n and 
 struct huft* t 
 };
 struct huft {
 unsigned char e and 
 unsigned char b and 
 struct$0  v 
 };
 int border[19]<=={16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15} and skip;
 int cplens[31]<=={3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258,0,0} and skip;
 int cplext[31]<=={0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,99,99} and skip;
 int cpdist[30]<=={1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577} and skip;
 int cpdext[30]<=={0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13} and skip;
 int bb and skip;
 int bk and skip;
 int mask_bits[17]<=={0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767,65535} and skip;
 int lbits<==9 and skip;
 int dbits<==6 and skip;
 int hufts and skip;
 function huft_build ( int *b,int n,int s,int *d,int *e,huft **t,int *m ,int RValue)
 {
     frame(huft_build_a,huft_build_c,huft_build_n,huft_build_s,huft_build_f,huft_build_g,huft_build_h,huft_build_i,huft_build_j,huft_build_k,huft_build_l,huft_build_p,huft_build_q,huft_build_r,huft_build_u,huft_build_v,huft_build_w,huft_build_x,huft_build_xp,huft_build_y,huft_build_z,count$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int huft_build_a and skip;
	 int huft_build_n and skip;
     int huft_build_c[16+1] and skip;
     int huft_build_f and skip;
     int huft_build_g and skip;
     int huft_build_h and skip;
     int huft_build_i and skip;
     int huft_build_j and skip;
     int huft_build_k and skip;
     int huft_build_l and skip;
	 int huft_build_s and skip;
     int *huft_build_p and skip;
     huft *huft_build_q and skip;
     huft huft_build_r and skip;
     huft *huft_build_u[16] and skip;
     int huft_build_v[288] and skip;
     int huft_build_w and skip;
     int huft_build_x[16+1] and skip;
     int *huft_build_xp and skip;
     int huft_build_y and skip;
     int huft_build_z and skip;
     memset((char *)huft_build_c,0,64,RValue) and skip;
     huft_build_p:=b;
     huft_build_i:=huft_build_n;
     int count$<==0 and skip;
     while(count$=0 OR (huft_build_i-1))
     {
         count$:=count$+1;
         huft_build_i:=huft_build_i-1;
         huft_build_c[* huft_build_p]:=huft_build_c[* huft_build_p]+1;
         huft_build_p:=huft_build_p+1
     };
     if(huft_build_c[0]=huft_build_n) then 
     {
         * t:=(huft *)NULL;
         * m:=0;
         return<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         huft_build_l:=* m;
         break$<==0 and skip;
         huft_build_j:=1;
         
         while( break$=0 AND  huft_build_j<=16)
         {
             if(huft_build_c[huft_build_j]) then 
             {
                 break$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 huft_build_j:=huft_build_j+1
             }
             else
             {
                 skip
             }
             
         };
         break$<==0 and skip;
         huft_build_k:=huft_build_j;
         if((int)huft_build_l<huft_build_j) then 
         {
             huft_build_l:=huft_build_j
         }
         else 
         {
              skip 
         };
         break$<==0 and skip;
         huft_build_i:=16;
         
         while( break$=0 AND  huft_build_i)
         {
             if(huft_build_c[huft_build_i]) then 
             {
                 break$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 huft_build_i:=huft_build_i-1
             }
             else
             {
                 skip
             }
             
         };
         break$<==0 and skip;
         huft_build_g:=huft_build_i;
         if((int)huft_build_l>huft_build_i) then 
         {
             huft_build_l:=huft_build_i
         }
         else 
         {
              skip 
         };
         * m:=huft_build_l;
         huft_build_y:=1<<huft_build_j;
         
         while( return=0 AND  huft_build_j<huft_build_i)
         {
		     huft_build_y<==huft_build_y-huft_build_c[huft_build_j] and skip;
             if(huft_build_y<0) then 
             {
                 return<==1 and RValue:=2;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 huft_build_j:=huft_build_j+1 and huft_build_y:=huft_build_y<< (1)
             }
             else
             {
                 skip
             }
             
         };
         if(return=0)   then 
         {
		     huft_build_y:=huft_build_y-huft_build_c[huft_build_i];
             if(huft_build_y<0) then 
             {
                 return<==1 and RValue:=2;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 huft_build_c[huft_build_i]:=huft_build_c[huft_build_i]+huft_build_y;
                 huft_build_j<==0 and huft_build_x[1]<==huft_build_j and skip;
                 huft_build_p:=huft_build_c+1;
                 huft_build_xp:=huft_build_x+2;
                 while((huft_build_i-1))
                 {
                     huft_build_i:=huft_build_i-1;
                     huft_build_j:=huft_build_j+* huft_build_p ;
                      * huft_build_xp:=huft_build_j;
                     huft_build_xp:=huft_build_xp+1;
                     huft_build_p:=huft_build_p+1
                 };
                 huft_build_p:=b;
                 huft_build_i:=0;
                 count$<==0 and skip;
                 while( ( count$=0 OR (huft_build_i+1)<huft_build_n))
                 {
                     count$:=count$+1;
                     huft_build_i:=huft_build_i+1;
                     huft_build_j:=* huft_build_p ;
                     if((huft_build_j)!=0) then 
                     {
                         huft_build_p:=huft_build_p+1;
                         huft_build_v[huft_build_x[huft_build_j]]:=huft_build_i;
                         huft_build_x[huft_build_j]:=huft_build_x[huft_build_j]+1
                     }
                     else 
                     {
                         huft_build_p:=huft_build_p+1
                         
                     }
                 };
                 huft_build_i<==0 and huft_build_x[0]<==huft_build_i and skip;
                 huft_build_p:=huft_build_v;
                 huft_build_h:=-1;
                 huft_build_w:=-huft_build_l;
                 huft_build_u[0]:=(huft *)NULL;
                 huft_build_q:=(huft *)NULL;
                 huft_build_z:=0;
                 while( return=0 AND  huft_build_k<=huft_build_g)
                 {
                     huft_build_a:=huft_build_c[huft_build_k];
                     while( return=0 AND  huft_build_a)
                     {
                         huft_build_a:=huft_build_a-1;
                         while( return=0 AND  huft_build_k>huft_build_w+huft_build_l)
                         {
                             huft_build_h:=huft_build_h+1;
                             huft_build_w:=huft_build_w+huft_build_l;
							 huft_build_z<==huft_build_g-huft_build_w and skip;
                             huft_build_z:=if(huft_build_z>(int)huft_build_l) then huft_build_l else huft_build_z;
                             huft_build_j:=huft_build_k-huft_build_w ;
                             huft_build_f:=1<<(huft_build_j) ;
                             if((huft_build_f)>huft_build_a+1) then 
                             {
                                 huft_build_f:=huft_build_f-huft_build_a+1;
                                 huft_build_xp:=huft_build_c+huft_build_k;
                                 break$<==0 and skip;
                                 while( break$=0 AND (huft_build_j+1)<huft_build_z)
                                 {
                                     huft_build_j:=huft_build_j+1;
									 huft_build_f<==huft_build_f<< (1) and skip; 
                                     if(huft_build_f<=* (huft_build_xp+1)) then 
                                     {
                                         huft_build_xp:=huft_build_xp+1;
                                         break$<==1 and skip
                                      }
                                     else 
                                     {
                                         huft_build_xp:=huft_build_xp+1
                                         
                                     };
                                     if(break$=0)   then
                                     {
                                         huft_build_f:=huft_build_f-* huft_build_xp
                                     }
                                     else
                                     {
                                         skip
                                     }
                                 };
                                 break$<==0 and skip
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             huft_build_z:=1<<huft_build_j;
                             huft_build_q:=(huft *)malloc((huft_build_z+1)*sizeof(huft));
                             if((huft_build_q)=(huft *)NULL) then 
                             {
                                 if(huft_build_h) then 
                                 {
                                     huft_free(huft_build_u[0],RValue)
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 return<==1 and RValue:=3;
                                 skip
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             if(return=0)   then 
                             {
                                 hufts:=hufts+huft_build_z+1;
                                 * t:=huft_build_q+1;
								 t<==&(huft_build_q->v.t) and skip;
                                 * (t):=(huft *)NULL;
                                 huft_build_u[huft_build_h]:=(huft_build_q+1);
                                 huft_build_q:=huft_build_q+1;
                                 if(huft_build_h) then 
                                 {
                                     huft_build_x[huft_build_h]:=huft_build_i;
                                     huft_build_r.b:=(unsigned char)huft_build_l;
                                     huft_build_r.e:=(unsigned char)(16+huft_build_j);
                                     huft_build_r.v.t:=huft_build_q;
                                     huft_build_j:=huft_build_i>>(huft_build_w-huft_build_l);
                                     huft_build_u[huft_build_h-1,huft_build_j]:=huft_build_r
                                     
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
                         if(return=0)   then 
                         {
                             huft_build_r.b:=(unsigned char)(huft_build_k-huft_build_w);
                             if(huft_build_p>=huft_build_v+huft_build_n) then 
                             {
                                 huft_build_r.e:=99
                             }
                             else
                             {
                                 if(* huft_build_p<huft_build_s) then 
                                 {
                                     huft_build_r.e:=(unsigned char)(( if(* huft_build_p<256) then 16 else 15));
                                     huft_build_r.v.n:=(unsigned int)(* huft_build_p);
                                     huft_build_p:=huft_build_p+1
                                 }
                                 else
                                 {
                                     huft_build_r.e:=(unsigned char)e[* huft_build_p-huft_build_s];
                                     huft_build_r.v.n:=d[* huft_build_p-huft_build_s];
                                     huft_build_p:=huft_build_p+1
                                 }
                             };
                             huft_build_f:=1<<(huft_build_k-huft_build_w);
                             huft_build_j:=huft_build_i>>huft_build_w;
                             
                             while(huft_build_j<huft_build_z)
                             {
                                 huft_build_q[huft_build_j]:=huft_build_r;
                                 huft_build_j:=huft_build_j+huft_build_f
                                 
                             };
                             huft_build_j:=1<<(huft_build_k-1);
                             
                             while(huft_build_i & huft_build_j)
                             {
                                 huft_build_i:=huft_build_i^ (huft_build_j);
                                 huft_build_j:=huft_build_j>> (1 )
                                 
                             };
                             huft_build_i:=huft_build_i^ (huft_build_j);
                             while((huft_build_i & ((1<<huft_build_w)-1))!=huft_build_x[huft_build_h])
                             {
                                 huft_build_h:=huft_build_h-1;
                                 huft_build_w:=huft_build_w-huft_build_l
                             }
                         }
                         else
                         {
                             skip
                         }
                     };
                     if(return=0)   then 
                     {
                         huft_build_k:=huft_build_k+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 if(return=0)   then 
                 {
                     return<==1 and RValue:= (huft_build_y!=0 AND huft_build_g!=1);
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
     )
     }; 
  function huft_free ( huft *t,int RValue )
 {
     frame(huft_free_p,huft_free_q,return) and ( 
     int return<==0 and skip;
     huft *huft_free_p,*huft_free_q and skip;
     huft_free_p:=t;
     while(huft_free_p!=(huft *)NULL)
     {
	     huft_free_p<==huft_free_p-1 and skip;
         huft_free_q:=huft_free_p->v.t;
         huft_free_p:=huft_free_p-1;
         free((char *)huft_free_p) and skip;
         huft_free_p:=huft_free_q
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function inflate_codes ( huft *tl,huft *td,int bl,int bd,int RValue )
 {
	frame(tmp,inflate_codes_e,inflate_codes_n,inflate_codes_temp,inflate_codes_d,inflate_codes_w,inflate_codes_t,inflate_codes_ml,inflate_codes_md,inflate_codes_b,inflate_codes_k,count$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int inflate_codes_e and skip;
     int inflate_codes_n,inflate_codes_d and skip;
     int inflate_codes_w and skip;
	 int inflate_codes_temp and skip;
     huft *inflate_codes_t and skip;
     int inflate_codes_ml,inflate_codes_md and skip;
     int inflate_codes_b and skip;
     int inflate_codes_k and skip;
	 int tmp and skip;
     inflate_codes_b:=bb;
     inflate_codes_k:=bk;
     inflate_codes_w:=outcnt;
     inflate_codes_ml:=mask_bits[bl];
     inflate_codes_md:=mask_bits[bd];
     break$<==0 and skip;
     while( return=0 AND   break$=0 AND  true)
     {
         while(inflate_codes_k<((unsigned int)bl))
         {
		     inflate_codes_temp:=((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_codes_k;
             if(inptr<insize) then {inptr:=inptr+1} else{skip};
			 inflate_codes_b:=inflate_codes_b| (inflate_codes_temp);
             inflate_codes_k:=inflate_codes_k+8
         };
		 tmp:=(unsigned int)inflate_codes_b & inflate_codes_ml;
         inflate_codes_t:=tl+ tmp;
         inflate_codes_e:=(inflate_codes_t)->e ;
         if(inflate_codes_e>16) then 
         {
             int count$<==0 and skip;
             while( return=0 AND count$=0 OR inflate_codes_e>16)
             {
                 count$:=count$+1;
                 if(inflate_codes_e=99) then 
                 {
                     return<==1 and RValue:=1;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     inflate_codes_b:=inflate_codes_b>>(inflate_codes_t->b);
                     inflate_codes_k:=inflate_codes_k-(inflate_codes_t->b);
                     inflate_codes_e:=inflate_codes_e-16;
                     while(inflate_codes_k<inflate_codes_e)
                     {
                         inflate_codes_b:=inflate_codes_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_codes_k);
                         if(inptr<insize) then {inptr:=inptr+1} else{skip};
						 inflate_codes_k:=inflate_codes_k+8
                     }
                 }
                 else
                 {
                     skip
                 };
			  inflate_codes_t:=inflate_codes_t->v.t+((unsigned int)inflate_codes_b & mask_bits[inflate_codes_e]);
			  inflate_codes_e:=(inflate_codes_t)->e
             }
         }
         else 
         {
              skip 
         };
         if(return=0)  then
         {
             inflate_codes_b:=inflate_codes_b>>(inflate_codes_t->b);
             inflate_codes_k:=inflate_codes_k-(inflate_codes_t->b);
             if(inflate_codes_e=16) then 
             {
                 window[inflate_codes_w]:=(unsigned char)inflate_codes_t->v.n;
                 inflate_codes_w:=inflate_codes_w+1;
                 if(inflate_codes_w=32768) then 
                 {
                     outcnt:=inflate_codes_w;
                     flush_window(RValue);
                     inflate_codes_w:=0
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
             else
             {
                 if(inflate_codes_e=15) then 
                 {
                     break$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     while(inflate_codes_k<inflate_codes_e)
                     {
                         inflate_codes_b:=inflate_codes_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_codes_k);
                         if(inptr<insize) then {inptr:=inptr+1} else{skip};
						 inflate_codes_k:=inflate_codes_k+8
                     };
                     inflate_codes_n:=inflate_codes_t->v.n+((unsigned int)inflate_codes_b & mask_bits[inflate_codes_e]);
                     inflate_codes_b:=inflate_codes_b>> (inflate_codes_e );
                     inflate_codes_k:=inflate_codes_k-inflate_codes_e;
                     while(inflate_codes_k<((unsigned int)bd))
                     {
                         inflate_codes_b:=inflate_codes_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_codes_k);
                         if(inptr<insize) then {inptr:=inptr+1} else{skip};
						 inflate_codes_k:=inflate_codes_k+8
                     };
                     inflate_codes_t:=td+((unsigned int)inflate_codes_b & inflate_codes_md) ;
                     inflate_codes_e:=(inflate_codes_t)->e ;
                     if((inflate_codes_e)>16) then 
                     {
                         count$<==0 and skip;
                         while( return=0 AND  count$=0 OR (inflate_codes_e)>16)
                         {
                             count$:=count$+1;
                             if(inflate_codes_e=99) then 
                             {
                                 return<==1 and RValue:=1;
                                 skip
                             }
                             else 
                             {
                                  skip 
                             };
                             if(return=0)   then 
                             {
                                 inflate_codes_b:=inflate_codes_b>>(inflate_codes_t->b);
                                 inflate_codes_k:=inflate_codes_k-(inflate_codes_t->b);
                                 inflate_codes_e:=inflate_codes_e-16;
                                 while(inflate_codes_k<inflate_codes_e)
                                 {
                                     inflate_codes_b:=inflate_codes_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_codes_k);
                                     if(inptr<insize) then {inptr:=inptr+1} else{skip};
									 inflate_codes_k:=inflate_codes_k+8
                                 }
                             }
                             else
                             {
                                 skip
                             };
							 inflate_codes_t:=inflate_codes_t->v.t+((unsigned int)inflate_codes_b & mask_bits[inflate_codes_e]);
			                 inflate_codes_e:=(inflate_codes_t)->e
                         }
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)  then
                     {
                         inflate_codes_b:=inflate_codes_b>>(inflate_codes_t->b);
                         inflate_codes_k:=inflate_codes_k-(inflate_codes_t->b);
                         while(inflate_codes_k<inflate_codes_e)
                         {
                             inflate_codes_b:=inflate_codes_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_codes_k);
                             if(inptr<insize) then {inptr:=inptr+1} else{skip};
							 inflate_codes_k:=inflate_codes_k+8
                         };
                         inflate_codes_d:=inflate_codes_w-inflate_codes_t->v.n-((unsigned int)inflate_codes_b & mask_bits[inflate_codes_e]);
                         inflate_codes_b:=inflate_codes_b>> (inflate_codes_e );
                         inflate_codes_k:=inflate_codes_k-inflate_codes_e;
                         count$<==0 and skip;
                         while( count$=0 OR inflate_codes_n)
                         {
                             count$:=count$+1;
							 inflate_codes_d:=inflate_codes_d& (32768-1);
							 inflate_codes_e:=32768-( if(inflate_codes_d>inflate_codes_w) then inflate_codes_d else inflate_codes_w);
							 inflate_codes_e:=( if(inflate_codes_e>inflate_codes_n) then inflate_codes_n else inflate_codes_e);
                             inflate_codes_n:=inflate_codes_n-inflate_codes_e;
                             if(inflate_codes_w-inflate_codes_d>=inflate_codes_e) then 
                             {
                                 memcpy(window+inflate_codes_w,window+inflate_codes_d,inflate_codes_e,RValue) and skip;
                                 inflate_codes_w:=inflate_codes_w+inflate_codes_e;
                                 inflate_codes_d:=inflate_codes_d+inflate_codes_e
                                 
                             }
                             else
                             {
                                 count$<==0 and skip;
                                 while( count$=0 OR (inflate_codes_e-1))
                                 {
                                     count$:=count$+1;
                                     inflate_codes_e:=inflate_codes_e-1;
                                     window[inflate_codes_w]:=window[inflate_codes_d];
                                     inflate_codes_w:=inflate_codes_w+1;
                                     inflate_codes_d:=inflate_codes_d+1
                                 }
                             };
                             if(inflate_codes_w=32768) then 
                             {
                                 outcnt:=inflate_codes_w;
                                 flush_window(RValue);
                                 inflate_codes_w:=0
                                 
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
             }		 
     };
     break$<==0 and skip;
     if(return=0)   then 
     {
         outcnt:=inflate_codes_w;
         bb:=inflate_codes_b;
         bk:=inflate_codes_k;
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function inflate_dynamic ( int RValue )
 {
     frame(inflate_dynamic_i,inflate_dynamic_j,inflate_dynamic_l,inflate_dynamic_m,inflate_dynamic_n,inflate_dynamic_tl,inflate_dynamic_td,inflate_dynamic_bl,inflate_dynamic_bd,inflate_dynamic_nb,inflate_dynamic_nl,inflate_dynamic_nd$,inflate_dynamic_ll,inflate_dynamic_b,inflate_dynamic_k,return) and ( 
     int return<==0 and skip;
     int inflate_dynamic_i and skip;
     int inflate_dynamic_j and skip;
     int inflate_dynamic_l and skip;
     int inflate_dynamic_m and skip;
     int inflate_dynamic_n and skip;
     huft *inflate_dynamic_tl and skip;
     huft *inflate_dynamic_td and skip;
     int inflate_dynamic_bl and skip;
     int inflate_dynamic_bd and skip;
     int inflate_dynamic_nb and skip;
     int inflate_dynamic_nl and skip;
     int inflate_dynamic_nd$ and skip;
     int inflate_dynamic_ll[286+30] and skip;
     int inflate_dynamic_b and skip;
     int inflate_dynamic_k and skip;
     inflate_dynamic_b:=bb;
     inflate_dynamic_k:=bk;
     while(inflate_dynamic_k<5)
     {
         inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
         if(inptr<insize) then {inptr:=inptr+1} else{skip};
		 inflate_dynamic_k:=inflate_dynamic_k+8
     };
     inflate_dynamic_nl:=257+((unsigned int)inflate_dynamic_b & 31);
     inflate_dynamic_b:=inflate_dynamic_b>> (5 );
     inflate_dynamic_k:=inflate_dynamic_k-5;
     while(inflate_dynamic_k<5)
     {
         inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
         if(inptr<insize) then {inptr:=inptr+1} else{skip};
		 inflate_dynamic_k:=inflate_dynamic_k+8
     };
     inflate_dynamic_nd$:=1+((unsigned int)inflate_dynamic_b & 31);
     inflate_dynamic_b:=inflate_dynamic_b>> (5 );
     inflate_dynamic_k:=inflate_dynamic_k-5;
     while(inflate_dynamic_k<4)
     {
         inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
         if(inptr<insize) then {inptr:=inptr+1} else{skip};
		 inflate_dynamic_k:=inflate_dynamic_k+8
     };
     inflate_dynamic_nb:=4+((unsigned int)inflate_dynamic_b & 15);
     inflate_dynamic_b:=inflate_dynamic_b>> (4 );
     inflate_dynamic_k:=inflate_dynamic_k-4;
     if(inflate_dynamic_nl>286 OR inflate_dynamic_nd$>30) then 
     {
         return<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         inflate_dynamic_j:=0;
         
         while(inflate_dynamic_j<inflate_dynamic_nb)
         {
             while(inflate_dynamic_k<3)
             {
                 inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
                 if(inptr<insize) then {inptr:=inptr+1} else{skip};
				 inflate_dynamic_k:=inflate_dynamic_k+8
             };
             inflate_dynamic_ll[border[inflate_dynamic_j]]:=(unsigned int)inflate_dynamic_b & 7;
             inflate_dynamic_b:=inflate_dynamic_b>> (3 );
             inflate_dynamic_k:=inflate_dynamic_k-3;
             inflate_dynamic_j:=inflate_dynamic_j+1
             
         };
         while(inflate_dynamic_j<19)
         {
             inflate_dynamic_ll[border[inflate_dynamic_j]]:=0;
             inflate_dynamic_j:=inflate_dynamic_j+1
             
         };
         inflate_dynamic_bl:=7;
         inflate_dynamic_i:=huft_build(inflate_dynamic_ll,19,19,NULL,NULL,&inflate_dynamic_tl,&inflate_dynamic_bl,RValue) ;
		 if(inflate_dynamic_i!=0) then 
         {
             if(inflate_dynamic_i=1) then 
             {
                 huft_free(inflate_dynamic_tl,RValue)
             }
             else 
             {
                  skip 
             };
             return<==1 and RValue:=inflate_dynamic_i;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             inflate_dynamic_n:=inflate_dynamic_nl+inflate_dynamic_nd$;
             inflate_dynamic_m:=mask_bits[inflate_dynamic_bl];
             inflate_dynamic_l<==0 and inflate_dynamic_i<==inflate_dynamic_l and skip;
             while( return=0 AND  (unsigned int)inflate_dynamic_i<inflate_dynamic_n)
             {
                 while(inflate_dynamic_k<((unsigned int)inflate_dynamic_bl))
                 {
                     inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
                     if(inptr<insize) then {inptr:=inptr+1} else{skip};
					 inflate_dynamic_k:=inflate_dynamic_k+8
                 };
				 inflate_dynamic_td:=inflate_dynamic_tl+((unsigned int)inflate_dynamic_b & inflate_dynamic_m);
                 inflate_dynamic_j:=(inflate_dynamic_td)->b;
                 inflate_dynamic_b:=inflate_dynamic_b>> (inflate_dynamic_j );
                 inflate_dynamic_k:=inflate_dynamic_k-inflate_dynamic_j;
                 inflate_dynamic_j:=inflate_dynamic_td->v.n;
                 if(inflate_dynamic_j<16) then 
                 {
                     inflate_dynamic_l<==inflate_dynamic_j and inflate_dynamic_ll[inflate_dynamic_i]<==inflate_dynamic_l and skip;
                     inflate_dynamic_i:=inflate_dynamic_i+1
                 }
                 else
                 {
                     if(inflate_dynamic_j=16) then 
                     {
                         while(inflate_dynamic_k<2)
                         {
                             inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
                             if(inptr<insize) then {inptr:=inptr+1} else{skip};
							 inflate_dynamic_k:=inflate_dynamic_k+8
                         };
                         inflate_dynamic_j:=3+((unsigned int)inflate_dynamic_b & 3);
                         inflate_dynamic_b:=inflate_dynamic_b>> (2 );
                         inflate_dynamic_k:=inflate_dynamic_k-2;
                         if((unsigned int)inflate_dynamic_i+inflate_dynamic_j>inflate_dynamic_n) then 
                         {
                             return<==1 and RValue:=1;
                             skip
                         }
                         else 
                         {
                              skip 
                         };
                         if(return=0)   then 
                         {
                             while(inflate_dynamic_j)
                             {
                                 inflate_dynamic_j:=inflate_dynamic_j-1;
                                 inflate_dynamic_ll[inflate_dynamic_i]:=inflate_dynamic_l;
                                 inflate_dynamic_i:=inflate_dynamic_i+1
                             }
                         }
                         else
                         {
                             if(inflate_dynamic_j=17) then 
                             {
                                 while(inflate_dynamic_k<3)
                                 {
                                     inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
                                     if(inptr<insize) then {inptr:=inptr+1} else{skip};                                    
									 inflate_dynamic_k:=inflate_dynamic_k+8
                                 };
                                 inflate_dynamic_j:=3+((unsigned int)inflate_dynamic_b & 7);
                                 inflate_dynamic_b:=inflate_dynamic_b>> (3 );
                                 inflate_dynamic_k:=inflate_dynamic_k-3;
                                 if((unsigned int)inflate_dynamic_i+inflate_dynamic_j>inflate_dynamic_n) then 
                                 {
                                     return<==1 and RValue:=1;
                                     skip
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(return=0)   then 
                                 {
                                     while(inflate_dynamic_j)
                                     {
                                         inflate_dynamic_j:=inflate_dynamic_j-1;
                                         inflate_dynamic_ll[inflate_dynamic_i]:=0;
                                         inflate_dynamic_i:=inflate_dynamic_i+1
                                     };
                                     inflate_dynamic_l:=0
                                 }
                                 else
                                 {
                                     while(inflate_dynamic_k<7)
                                     {
                                         inflate_dynamic_b:=inflate_dynamic_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_dynamic_k);
                                         if(inptr<insize) then {inptr:=inptr+1} else{skip};
										 inflate_dynamic_k:=inflate_dynamic_k+8
                                     };
                                     inflate_dynamic_j:=11+((unsigned int)inflate_dynamic_b & 127);
                                     inflate_dynamic_b:=inflate_dynamic_b>> (7 );
                                     inflate_dynamic_k:=inflate_dynamic_k-7;
                                     if((unsigned int)inflate_dynamic_i+inflate_dynamic_j>inflate_dynamic_n) then 
                                     {
                                         return<==1 and RValue:=1;
                                         skip
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     if(return=0)   then 
                                     {
                                         while(inflate_dynamic_j)
                                         {
                                             inflate_dynamic_j:=inflate_dynamic_j-1;
                                             inflate_dynamic_ll[inflate_dynamic_i]:=0;
                                             inflate_dynamic_i:=inflate_dynamic_i+1
                                         };
                                         inflate_dynamic_l:=0
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
                             }
                         }
                     }
                 }
             };
             if(return=0)   then 
             {
                 huft_free(inflate_dynamic_tl,RValue);
                 bb:=inflate_dynamic_b;
                 bk:=inflate_dynamic_k;
                 inflate_dynamic_bl:=lbits;
                 inflate_dynamic_i:=huft_build(inflate_dynamic_ll,inflate_dynamic_nl,257,cplens,cplext,&inflate_dynamic_tl,&inflate_dynamic_bl,RValue) ;
                 if((inflate_dynamic_i)!=0) then 
                 {
                     if(inflate_dynamic_i=1) then 
                     {
                         fprintf(stderr," incomplete literal tree\n",RValue) and skip;
                         huft_free(inflate_dynamic_tl,RValue)
                         
                     }
                     else 
                     {
                          skip 
                     };
                     return<==1 and RValue:=inflate_dynamic_i;
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     inflate_dynamic_bd:=dbits;
                     inflate_dynamic_i:=huft_build(inflate_dynamic_ll+inflate_dynamic_nl,inflate_dynamic_nd$,0,cpdist,cpdext,&inflate_dynamic_td,&inflate_dynamic_bd,RValue) ;
                     if((inflate_dynamic_i)!=0) then 
                     {
                         if(inflate_dynamic_i=1) then 
                         {
                             fprintf(stderr," incomplete distance tree\n",RValue) and skip;
                             huft_free(inflate_dynamic_td,RValue)
                             
                         }
                         else 
                         {
                              skip 
                         };
                         huft_free(inflate_dynamic_tl,RValue);
                         return<==1 and RValue:=inflate_dynamic_i;
                         skip
                         
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)   then 
                     {
                         if(extern inflate_codes(inflate_dynamic_tl,inflate_dynamic_td,inflate_dynamic_bl,inflate_dynamic_bd,RValue)) then 
                         {
                             return<==1 and RValue:=1;
                             skip
                         }
                         else 
                         {
                              skip 
                         };
                         if(return=0)   then 
                         {
                             huft_free(inflate_dynamic_tl,RValue);
                             huft_free(inflate_dynamic_td,RValue);
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
  function inflate_block ( int *e,int RValue )
 {
     frame(inflate_block_t,inflate_block_b,inflate_block_k,return) and ( 
     int return<==0 and skip;
     int inflate_block_t and skip;
     int inflate_block_b and skip;
     int inflate_block_k and skip;
     inflate_block_b:=bb;
     inflate_block_k:=bk;
     while(inflate_block_k<1)
     {
         inflate_block_b:=inflate_block_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_block_k);
         if(inptr<insize) then {inptr:=inptr+1} else{skip};
		 inflate_block_k:=inflate_block_k+8
     };
     * e:=(int)inflate_block_b & 1;
     inflate_block_b:=inflate_block_b>> (1 );
     inflate_block_k:=inflate_block_k-1;
     while(inflate_block_k<2)
     {
         inflate_block_b:=inflate_block_b| (((unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue))))<<inflate_block_k);
         if(inptr<insize) then {inptr:=inptr+1} else{skip};
		 inflate_block_k:=inflate_block_k+8
     };
     inflate_block_t:=(unsigned int)inflate_block_b & 3;
     inflate_block_b:=inflate_block_b>> (2 );
     inflate_block_k:=inflate_block_k-2;
     bb:=inflate_block_b;
     bk:=inflate_block_k;
     if(inflate_block_t=2) then 
     {
         return<==1 and RValue:=inflate_dynamic(RValue);
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         return<==1 and RValue:=2;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function inflate ( int RValue )
 {
     frame(inflate_e,inflate_r,inflate_h,count$,return) and ( 
     int return<==0 and skip;
     int inflate_e and skip;
     int inflate_r and skip;
     int inflate_h and skip;
     outcnt:=0;
     bk:=0;
     bb:=0;
     inflate_h:=0;
     int count$<==0 and skip;
     while( return=0 AND   ( count$=0 OR !inflate_e))
     {
         count$:=count$+1;
         hufts:=0;
         inflate_r:=inflate_block(&inflate_e,RValue) ;
         if((inflate_r)!=0) then 
         {
             return<==1 and RValue:=inflate_r;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(hufts>inflate_h) then 
             {
                 inflate_h:=hufts
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
     if(return=0)   then 
     {
         while(bk>=8)
         {
             bk:=bk-8;
             inptr:=inptr-1
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
      int msg_done<==0 and skip;
 function lzw ( int in,int out,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(msg_done) then 
     {
         return<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         msg_done:=1;
         fprintf(stderr,"output in compress .Z format not supported\n",RValue) and skip;
         if(in!=out) then 
         {
             exit_code:=1
             
         }
         else 
         {
              skip 
         };
         return<==1 and RValue:=1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
      int extra_lbits[29]<=={0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0} and skip;
     int extra_dbits[30]<=={0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13} and skip;
     int extra_blbits[19]<=={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7} and skip;
     union struct$1 {
     int freq and 
     int code 
 };
 union struct$2 {
 int dad and 
 int len$ 
 };
 struct ct_data {
 struct$1  fc and 
 struct$2  dl 
 };
 ct_data dyn_ltree[573] and skip;
 ct_data dyn_dtree[61] and skip;
 ct_data static_ltree[286+2] and skip;
 ct_data static_dtree[30] and skip;
 ct_data bl_tree[39] and skip;
 struct tree_desc {
 struct ct_data* dyn_tree and 
 struct ct_data* static_tree and 
 int *extra_bits and 
 int extra_base and 
 int elems and 
 int max_length and 
 int max_code 
 };
 tree_desc l_desc<=={dyn_ltree,static_ltree,extra_lbits,256+1,286,15,0} and skip;
 tree_desc d_desc<=={dyn_dtree,static_dtree,extra_dbits,0,30,15,0} and skip;
 tree_desc bl_desc<=={bl_tree,NULL,extra_blbits,0,19,7,0} and skip;
 int bl_count[15+1] and skip;
 unsigned char bl_order[19]<=={16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15} and skip;
 int heap[2286+1] and skip;
 int heap_len and skip;
 int heap_max and skip;
 unsigned char depth[2286+1] and skip;
 unsigned char length_code[258-3+1] and skip;
 unsigned char dist_code[512] and skip;
 int base_length[29] and skip;
 int base_dist[30] and skip;
 unsigned char flag_buf[(32768/ 8)] and skip;
 int last_lit and skip;
 int last_dist and skip;
 int last_flags and skip;
 unsigned char flags and skip;
 unsigned char flag_bit and skip;
 int opt_len and skip;
 int static_len and skip;
 int compressed_len and skip;
 int input_len and skip;
 int *file_type and skip;
 int *file_method and skip;
 function ct_init ( int *attr,int *methodp )
 {
     frame(ct_init_n,ct_init_bits,ct_init_length,ct_init_code,ct_init_dist,return) and ( 
     int return<==0 and skip;
     int ct_init_n and skip;
     int ct_init_bits and skip;
     int ct_init_length and skip;
     int ct_init_code and skip;
     int ct_init_dist and skip;
     file_type:=attr;
     file_method:=methodp;
     input_len<==0 and compressed_len<==input_len and skip;
     if(static_dtree[0].dl.len$!=0) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         ct_init_length:=0;
         ct_init_code:=0;
         
         while(ct_init_code<29-1)
         {
             base_length[ct_init_code]:=ct_init_length;
             ct_init_n:=0;
             
             while(ct_init_n<(1<<extra_lbits[ct_init_code]))
             {
                 length_code[ct_init_length]:=(unsigned char)ct_init_code;
                 ct_init_length:=ct_init_length+1;
                 ct_init_n:=ct_init_n+1
                 
             };
             ct_init_code:=ct_init_code+1
             
         };
         length_code[ct_init_length-1]:=(unsigned char)ct_init_code;
         ct_init_dist:=0;
         ct_init_code:=0;
         
         while(ct_init_code<16)
         {
             base_dist[ct_init_code]:=ct_init_dist;
             ct_init_n:=0;
             
             while(ct_init_n<(1<<extra_dbits[ct_init_code]))
             {
                 dist_code[ct_init_dist]:=(unsigned char)ct_init_code;
                 ct_init_dist:=ct_init_dist+1;
                 ct_init_n:=ct_init_n+1
                 
             };
             ct_init_code:=ct_init_code+1
             
         };
         ct_init_dist:=ct_init_dist>> (7 );
         while(ct_init_code<30)
         {
             base_dist[ct_init_code]:=ct_init_dist<<7;
             ct_init_n:=0;
             
             while(ct_init_n<(1<<(extra_dbits[ct_init_code]-7)))
             {
                 dist_code[256+ct_init_dist]:=(unsigned char)ct_init_code;
                 ct_init_dist:=ct_init_dist+1;
                 ct_init_n:=ct_init_n+1
                 
             };
             ct_init_code:=ct_init_code+1
             
         };
         ct_init_bits:=0;
         
         while(ct_init_bits<=15)
         {
             bl_count[ct_init_bits]:=0;
             ct_init_bits:=ct_init_bits+1
             
         };
         ct_init_n:=0;
         while(ct_init_n<=143)
         {
             static_ltree[ct_init_n].dl.len$:=8;
			 ct_init_n:=ct_init_n+1;
			 bl_count[8]:=bl_count[8]+1
		 };
         while(ct_init_n<=255)
         {
            static_ltree[ct_init_n].dl.len$:=9;
			ct_init_n:=ct_init_n+1;
			bl_count[9]:=bl_count[9]+1
	     };
         while(ct_init_n<=279)
         {
            static_ltree[ct_init_n].dl.len$:=7;
			ct_init_n:=ct_init_n+1;
			bl_count[7]:=bl_count[7]+1
		};
         while(ct_init_n<=287)
        {
            static_ltree[ct_init_n].dl.len$:=8;
			ct_init_n:=ct_init_n+1;
			bl_count[8]:=bl_count[8]+1
		};
                         gen_codes((ct_data *)static_ltree,286+1,RValue);
                         ct_init_n:=0;
                         
                         while(ct_init_n<30)
                         {
                             static_dtree[ct_init_n].dl.len$:=5;
                             static_dtree[ct_init_n].fc.code:=bi_reverse(ct_init_n,5,RValue);
                             ct_init_n:=ct_init_n+1
                             
                         };
                         init_block(RValue)
                     }
                     else
                     {
                         skip
                     }
                     )
                     }; 
  function init_block (  )
 {
     frame(init_block_n) and ( 
     int init_block_n and skip;
     init_block_n:=0;
     
     while(init_block_n<286)
     {
         dyn_ltree[init_block_n].fc.freq:=0;
         init_block_n:=init_block_n+1
         
     };
	 
     init_block_n:=0;
     
     while(init_block_n<30)
     {
         dyn_dtree[init_block_n].fc.freq:=0;
         init_block_n:=init_block_n+1
         
     };
     init_block_n:=0;
     
     while(init_block_n<19)
     {
         bl_tree[init_block_n].fc.freq:=0;
         init_block_n:=init_block_n+1
         
     };
     dyn_ltree[256].fc.freq:=1;
     static_len<==0 and opt_len<==static_len and skip;
     last_flags<==0 and last_dist<==last_flags and last_lit<==last_dist and skip;
     flags:=0;
     flag_bit:=1
	 
     )
     }; 
/*  function pqdownheap ( ct_data *tree,int k )
 {
     frame(pqdownheap_v,pqdownheap_j,break$) and ( 
     int break$<==0 and skip;
     int pqdownheap_v<==heap[k] and skip;
     int pqdownheap_j<==k<<1 and skip;
     break$<==0 and skip;
     while( break$=0 AND  pqdownheap_j<=heap_len)
     {
         if((tree[pqdownheap_v].fc.freq<tree[heap[pqdownheap_j]].fc.freq OR (tree[pqdownheap_v].fc.freq=tree[heap[pqdownheap_j]].fc.freq AND depth[pqdownheap_v]<=depth[heap[pqdownheap_j]]))) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             heap[k]:=heap[pqdownheap_j];
             k:=pqdownheap_j;
             pqdownheap_j:=pqdownheap_j<< (1 )
         }
         else
         {
             skip
         }
     };
     break$<==0 and skip;
     heap[k]:=pqdownheap_v
     )
     }; */
  function gen_bitlen ( tree_desc *desc )
 {
     frame(gen_bitlen_tree,gen_bitlen_extra,gen_bitlen_base,gen_bitlen_max_code,gen_bitlen_max_length,gen_bitlen_stree,gen_bitlen_h,gen_bitlen_n,gen_bitlen_m,gen_bitlen_bits,gen_bitlen_xbits,gen_bitlen_f,gen_bitlen_overflow,count$,return,continue$) and ( 
     int continue$<==0 and skip;
     int return<==0 and skip;
     ct_data *gen_bitlen_tree<==desc->dyn_tree and skip;
     int *gen_bitlen_extra<==desc->extra_bits and skip;
     int gen_bitlen_base<==desc->extra_base and skip;
     int gen_bitlen_max_code<==desc->max_code and skip;
     int gen_bitlen_max_length<==desc->max_length and skip;
     ct_data *gen_bitlen_stree<==desc->static_tree and skip;
     int gen_bitlen_h and skip;
     int gen_bitlen_n,gen_bitlen_m and skip;
     int gen_bitlen_bits and skip;
     int gen_bitlen_xbits and skip;
     int gen_bitlen_f and skip;
     int gen_bitlen_overflow<==0 and skip;
     gen_bitlen_bits:=0;
     
     while(gen_bitlen_bits<=15)
     {
         bl_count[gen_bitlen_bits]:=0;
         gen_bitlen_bits:=gen_bitlen_bits+1
         
     };
     gen_bitlen_tree[heap[heap_max]].dl.len$:=0;
     continue$<==0 and skip;
     gen_bitlen_h:=heap_max+1;
     
     while(gen_bitlen_h<573)
     {
          continue$<==0 and skip;
         gen_bitlen_n:=heap[gen_bitlen_h];
         gen_bitlen_bits:=gen_bitlen_tree[gen_bitlen_tree[gen_bitlen_n].dl.dad].dl.len$+1;
         if(gen_bitlen_bits>gen_bitlen_max_length) then 
         {
             gen_bitlen_bits:=gen_bitlen_max_length;
			 gen_bitlen_overflow:=gen_bitlen_overflow+1
			 }
             else 
             {
                  skip 
             };
             gen_bitlen_tree[gen_bitlen_n].dl.len$:=(unsigned int)gen_bitlen_bits;
             if(gen_bitlen_n>gen_bitlen_max_code) then 
             {
                 continue$<==1 and skip;
                  gen_bitlen_h:=gen_bitlen_h+1}
                 else 
                 {
                      skip 
                 };
                 if(continue$=0)   then 
                 {
                     bl_count[gen_bitlen_bits]:=bl_count[gen_bitlen_bits]+1;
                     gen_bitlen_xbits:=0;
                     if(gen_bitlen_n>=gen_bitlen_base) then 
                     {
                         gen_bitlen_xbits:=gen_bitlen_extra[gen_bitlen_n-gen_bitlen_base]
                     }
                     else 
                     {
                          skip 
                     };
                     gen_bitlen_f:=gen_bitlen_tree[gen_bitlen_n].fc.freq;
                     opt_len:=opt_len+(unsigned int)gen_bitlen_f*(gen_bitlen_bits+gen_bitlen_xbits);
                     if(gen_bitlen_stree) then 
                     {
                         static_len:=static_len+(unsigned int)gen_bitlen_f*(gen_bitlen_stree[gen_bitlen_n].dl.len$+gen_bitlen_xbits)
                     }
                     else 
                     {
                          skip 
                     };
                     gen_bitlen_h:=gen_bitlen_h+1
                 }
                 else
                 {
                     skip
                 }
                 
             };
             continue$<==0 and skip;
             if(gen_bitlen_overflow=0) then 
             {
                  return<==1 and skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 int count$<==0 and skip;
                 while( ( count$=0 OR gen_bitlen_overflow>0))
                 {
                     count$:=count$+1;
                     gen_bitlen_bits:=gen_bitlen_max_length-1;
                     while(bl_count[gen_bitlen_bits]=0)
                     {
                         gen_bitlen_bits:=gen_bitlen_bits-1
                     };
                     bl_count[gen_bitlen_bits]:=bl_count[gen_bitlen_bits]-1;
                     bl_count[gen_bitlen_bits+1]:=bl_count[gen_bitlen_bits+1]+2;
                     bl_count[gen_bitlen_max_length]:=bl_count[gen_bitlen_max_length]-1;
                     gen_bitlen_overflow:=gen_bitlen_overflow-2
                 };
                 gen_bitlen_bits:=gen_bitlen_max_length;
                 
                 while(gen_bitlen_bits!=0)
                 {
                     gen_bitlen_n:=bl_count[gen_bitlen_bits];
                     while(gen_bitlen_n!=0)
                     {
                         continue$<==0 and skip;
                         gen_bitlen_m:=heap[(gen_bitlen_h-1)];
                         gen_bitlen_h:=gen_bitlen_h-1;
                         if(gen_bitlen_m>gen_bitlen_max_code) then 
                         {
                             continue$<==1 and skip;
                              gen_bitlen_bits:=gen_bitlen_bits-1
                         }
                         else 
                         {
                              skip 
                         };
                         if(continue$=0)   then 
                         {
                             if(gen_bitlen_tree[gen_bitlen_m].dl.len$!=(unsigned int)gen_bitlen_bits) then 
                             {
                                 opt_len:=opt_len+((int)gen_bitlen_bits-(int)gen_bitlen_tree[gen_bitlen_m].dl.len$)*(int)gen_bitlen_tree[gen_bitlen_m].fc.freq;
                                 gen_bitlen_tree[gen_bitlen_m].dl.len$:=(unsigned int)gen_bitlen_bits
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             gen_bitlen_n:=gen_bitlen_n-1
                         }
                         else
                         {
                             skip
                         }
                     };
                     continue$<==0 and skip;
                     gen_bitlen_bits:=gen_bitlen_bits-1
                     
                 }
             }
             else
             {
                 skip
             }
             )
             }; 
  function gen_codes ( ct_data *tree,int max_code )
 {
     frame(gen_codes_next_code,gen_codes_code,gen_codes_bits,gen_codes_n,gen_codes_len$,continue$) and ( 
     int continue$<==0 and skip;
     int gen_codes_next_code[15+1] and skip;
     int gen_codes_code<==0 and skip;
     int gen_codes_bits and skip;
     int gen_codes_n and skip;
     gen_codes_bits:=1;
     
     while(gen_codes_bits<=15)
     {
         gen_codes_code<==(gen_codes_code+bl_count[gen_codes_bits-1])<<1 and gen_codes_next_code[gen_codes_bits]<==gen_codes_code and skip;
         gen_codes_bits:=gen_codes_bits+1
         
     };
     continue$<==0 and skip;
     gen_codes_n:=0;
     
     while(gen_codes_n<=max_code)
     {
          continue$<==0 and skip;
         int gen_codes_len$<==tree[gen_codes_n].dl.len$ and skip;
         if(gen_codes_len$=0) then 
         {
             continue$<==1 and skip;
              gen_codes_n:=gen_codes_n+1
         }
         else 
         {
              skip 
         };
         if(continue$=0)   then 
         {
             tree[gen_codes_n].fc.code:=bi_reverse(gen_codes_next_code[gen_codes_len$],gen_codes_len$,RValue);
             gen_codes_next_code[gen_codes_len$]:=gen_codes_next_code[gen_codes_len$]+1;
             gen_codes_n:=gen_codes_n+1
         }
         else
         {
             skip
         }
     };
     continue$<==0 and skip
     )
     }; 
  function build_tree ( tree_desc *desc )
 {
     frame(build_tree_tree,build_tree_stree,build_tree_elems,build_tree_n,build_tree_m,build_tree_max_code,build_tree_node,build_tree_3_new,count$) and ( 
     ct_data *build_tree_tree<==desc->dyn_tree and skip;
     ct_data *build_tree_stree<==desc->static_tree and skip;
     int build_tree_elems<==desc->elems and skip;
     int build_tree_n,build_tree_m and skip;
     int build_tree_max_code<==-1 and skip;
     int build_tree_node<==build_tree_elems and skip;
     heap_len:=0;
	 heap_max:=573;
	 build_tree_n:=0;
     
     while(build_tree_n<build_tree_elems)
     {
         if(build_tree_tree[build_tree_n].fc.freq!=0) then 
         {
             build_tree_max_code<==build_tree_n and heap[(heap_len+1)]<==build_tree_max_code and skip;
             heap_len:=heap_len+1;
             depth[build_tree_n]:=0
             
         }
         else
         {
             build_tree_tree[build_tree_n].dl.len$:=0
         };
         build_tree_n:=build_tree_n+1
         
     };
     while(heap_len<2)
     {
	     heap_len:=heap_len+1;
	     heap[heap_len]:=( if(build_tree_max_code<2) then (build_tree_max_code+1) else 0);
         if(build_tree_max_code<2) then{build_tree_max_code:=build_tree_max_code+1} else{skip};
		 int build_tree_3_new<==heap[heap_len] and skip;
         build_tree_tree[build_tree_3_new].fc.freq:=1;
         depth[build_tree_3_new]:=0;
         opt_len:=opt_len-1;
         if(build_tree_stree) then 
         {
             static_len:=static_len-build_tree_stree[build_tree_3_new].dl.len$
         }
         else 
         {
              skip 
         }
     };
     desc->max_code:=build_tree_max_code;
     build_tree_n:=heap_len/ 2;
     
     while(build_tree_n>=1)
     {
         //pqdownheap(build_tree_tree,build_tree_n);
         build_tree_n:=build_tree_n-1
         
     };
     int count$<==0 and skip;
     while( ( count$=0 OR heap_len>=2))
     {
         count$:=count$+1;
         build_tree_n:=heap[1];
         heap[1]:=heap[heap_len];
         heap_len:=heap_len-1;
         //pqdownheap(build_tree_tree,1);
         build_tree_m:=heap[1];
         heap[(heap_max-1)]:=build_tree_n;
         heap_max:=heap_max-1;
         heap[(heap_max-1)]:=build_tree_m;
         heap_max:=heap_max-1;
         build_tree_tree[build_tree_node].fc.freq:=build_tree_tree[build_tree_n].fc.freq+build_tree_tree[build_tree_m].fc.freq;
         depth[build_tree_node]:=(unsigned char)((( if(depth[build_tree_n]>=depth[build_tree_m]) then depth[build_tree_n] else depth[build_tree_m]))+1);
         build_tree_tree[build_tree_m].dl.dad<==(unsigned int)build_tree_node and build_tree_tree[build_tree_n].dl.dad<==build_tree_tree[build_tree_m].dl.dad and skip;
         heap[1]:=build_tree_node;
         build_tree_node:=build_tree_node+1
         //pqdownheap(build_tree_tree,1)
     };
     heap[(heap_max-1)]:=heap[1];
     heap_max:=heap_max-1;
     gen_bitlen((tree_desc *)desc);
     gen_codes((ct_data *)build_tree_tree,build_tree_max_code)
     )
     }; 
  function scan_tree ( ct_data *tree,int max_code )
 {
     frame(scan_tree_n,scan_tree_prevlen,scan_tree_curlen,scan_tree_nextlen,scan_tree_count,scan_tree_max_count,scan_tree_min_count,continue$) and ( 
     int continue$<==0 and skip;
     int scan_tree_n and skip;
     int scan_tree_prevlen<==-1 and skip;
     int scan_tree_curlen and skip;
     int scan_tree_nextlen<==tree[0].dl.len$ and skip;
     int scan_tree_count<==0 and skip;
     int scan_tree_max_count<==7 and skip;
     int scan_tree_min_count<==4 and skip;
     if(scan_tree_nextlen=0) then 
     {
         scan_tree_max_count:=138;
		 scan_tree_min_count:=3
		 }
         else 
         {
              skip 
         };
         tree[max_code+1].dl.len$:=(unsigned int)65535;
         continue$<==0 and skip;
         scan_tree_n:=0;
         
         while(scan_tree_n<=max_code)
         {
              continue$<==0 and skip;
             scan_tree_curlen:=scan_tree_nextlen;
             scan_tree_nextlen:=tree[scan_tree_n+1].dl.len$;
             if((scan_tree_count+1)<scan_tree_max_count AND scan_tree_curlen=scan_tree_nextlen) then 
             {
                 scan_tree_count:=scan_tree_count+1;
                 continue$<==1 and skip;
                  scan_tree_n:=scan_tree_n+1
                 
             }
             else
             {
                 scan_tree_count:=scan_tree_count+1;
                 if(scan_tree_count<scan_tree_min_count) then 
                 {
                     bl_tree[scan_tree_curlen].fc.freq:=bl_tree[scan_tree_curlen].fc.freq+scan_tree_count
                 }
                 else
                 {
                     if(scan_tree_curlen!=0) then 
                     {
                         if(scan_tree_curlen!=scan_tree_prevlen) then 
                         {
                             bl_tree[scan_tree_curlen].fc.freq:=bl_tree[scan_tree_curlen].fc.freq+1
                         }
                         else 
                         {
                              skip 
                         };
                         bl_tree[16].fc.freq:=bl_tree[16].fc.freq+1
                     }
                     else
                     {
                         if(scan_tree_count<=10) then 
                         {
                             bl_tree[17].fc.freq:=bl_tree[17].fc.freq+1
                         }
                         else
                         {
                             bl_tree[18].fc.freq:=bl_tree[18].fc.freq+1
                         }
                     }
                 }
             };
             if(continue$=0)  then 
             {
                 scan_tree_count:=0;
                 scan_tree_prevlen:=scan_tree_curlen;
                 if(scan_tree_nextlen=0) then 
                 {
                     scan_tree_max_count:=138;
					 scan_tree_min_count:=3
                 }
                 else
                 {
                     if(scan_tree_curlen=scan_tree_nextlen) then 
                     {
                         scan_tree_max_count:=6;
						 scan_tree_min_count:=3
					}
                      else
                      {
                             scan_tree_max_count:=7;
							 scan_tree_min_count:=4
					 }
                      };
                         scan_tree_n:=scan_tree_n+1
                }
                     else
                     {
                         skip
                     }
                 };
                 continue$<==0 and skip
                 )
                 }; 
  function send_tree ( ct_data *tree,int max_code )
 {
     frame(send_tree_n,send_tree_prevlen,send_tree_curlen,send_tree_nextlen,send_tree_count,send_tree_max_count,send_tree_min_count,count$,continue$) and ( 
     int continue$<==0 and skip;
     int send_tree_n and skip;
     int send_tree_prevlen<==-1 and skip;
     int send_tree_curlen and skip;
     int send_tree_nextlen<==tree[0].dl.len$ and skip;
     int send_tree_count<==0 and skip;
     int send_tree_max_count<==7 and skip;
     int send_tree_min_count<==4 and skip;
     if(send_tree_nextlen=0) then 
     {
         send_tree_max_count:=138;
		 send_tree_min_count:=3
	}
    else 
    {
        skip 
    };
         continue$<==0 and skip;
         send_tree_n:=0;
         /*output("send_tree_n:",send_tree_n) and skip;
		 output("\n") and skip;
		 output("max_code:",max_code) and skip;
		 output("\n") and skip;*/
         while(send_tree_n<=max_code)
         {
		
		
              continue$<==0 and skip;
             send_tree_curlen:=send_tree_nextlen;
             send_tree_nextlen:=tree[send_tree_n+1].dl.len$;

			 /* output("send_tree_n:",send_tree_n) and skip;
		 output("\n") and skip;
		 output("send_tree_count:",send_tree_count) and skip;
		 output("\n") and skip;
		 output("send_tree_curlen:",send_tree_curlen) and skip;
		 output("\n") and skip;
		 output("send_tree_nextlen:",send_tree_nextlen) and skip;
		 output("\n") and skip;*/
		 send_tree_count:=send_tree_count+1;
             if(send_tree_count<send_tree_max_count AND send_tree_curlen=send_tree_nextlen) then 
             {
                 
                 continue$<==1 and skip
				 //output("wangmeng222\n") and skip
                 
             }
             else
             {
                 if(send_tree_count<send_tree_min_count) then 
                 {
                     int count$<==0 and skip;
					 send_bits(bl_tree[send_tree_curlen].fc.code,bl_tree[send_tree_curlen].dl.len$);
                     send_tree_count:=send_tree_count-1;
					 //output("send_tree_count111:",send_tree_count) and skip;
					//output("\n") and skip;
					 while( send_tree_count!=0)
                     {
                         
                         send_tree_count:=send_tree_count-1;
						 //output("send_tree_count222:",send_tree_count) and skip;
						//output("\n") and skip;
                         send_bits(bl_tree[send_tree_curlen].fc.code,bl_tree[send_tree_curlen].dl.len$)
                     }
                 }
                 else
                 {
                     if(send_tree_curlen!=0) then 
                     {
                         if(send_tree_curlen!=send_tree_prevlen) then 
                         {
                             send_bits(bl_tree[send_tree_curlen].fc.code,bl_tree[send_tree_curlen].dl.len$);
                             send_tree_count:=send_tree_count-1
                             
                         }
                         else 
                         {
                              skip 
                         };
                         send_bits(bl_tree[16].fc.code,bl_tree[16].dl.len$);
                         send_bits(send_tree_count-3,2)
                     }
                     else
                     {
                         if(send_tree_count<=10) then 
                         {
                             send_bits(bl_tree[17].fc.code,bl_tree[17].dl.len$);
                             send_bits(send_tree_count-3,3)
                         }
                         else
                         {
                             send_bits(bl_tree[18].fc.code,bl_tree[18].dl.len$);
                             send_bits(send_tree_count-11,7)
                         }
                     }
                 }
             };
             if(continue$=0)  then 
             {
                 send_tree_count:=0;
                 send_tree_prevlen:=send_tree_curlen;
                 if(send_tree_nextlen=0) then 
                 {
                     send_tree_max_count:=138;
					 send_tree_min_count:=3
                 }
                 else
                 {
                     if(send_tree_curlen=send_tree_nextlen) then 
                     {
                         send_tree_max_count:=6;
						 send_tree_min_count:=3
						 }
                         else
                         {
                             send_tree_max_count:=7;
							 send_tree_min_count:=4
							 }
                         }
                         
                     }
                     else
                     {
                         skip
                     };
					 send_tree_n:=send_tree_n+1
                 };
                 continue$<==0 and skip
                  
                 )
                 }; 
  function build_bl_tree ( int RValue )
 {
     frame(build_bl_tree_max_blindex,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int build_bl_tree_max_blindex and skip;
     scan_tree((ct_data *)dyn_ltree,l_desc.max_code);
     scan_tree((ct_data *)dyn_dtree,d_desc.max_code);
     build_tree((tree_desc *)(&bl_desc));
     break$<==0 and skip;
     build_bl_tree_max_blindex:=19-1;
     
     while( break$=0 AND  build_bl_tree_max_blindex>=3)
     {
         if(bl_tree[bl_order[build_bl_tree_max_blindex]].dl.len$!=0) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             build_bl_tree_max_blindex:=build_bl_tree_max_blindex-1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     opt_len:=opt_len+3*(build_bl_tree_max_blindex+1)+5+5+4;
     return<==1 and RValue:=build_bl_tree_max_blindex;
     skip
     )
     }; 
  function send_all_trees ( int lcodes,int dcodes,int blcodes )
 {
     frame(send_all_trees_rank) and ( 
     int send_all_trees_rank and skip;
     send_bits(lcodes-257,5);
     send_bits(dcodes-1,5);
     send_bits(blcodes-4,4);
	 //output("888\n") and skip;
     send_all_trees_rank:=0;
	 //output("blcodes:",blcodes) and skip;
     
     while(send_all_trees_rank<blcodes)
     {
         send_bits(bl_tree[bl_order[send_all_trees_rank]].dl.len$,3);
         send_all_trees_rank:=send_all_trees_rank+1
         
     };
	 //output("999\n") and skip;
     send_tree((ct_data *)dyn_ltree,lcodes-1);
	 //output("101010\n") and skip;
     send_tree((ct_data *)dyn_dtree,dcodes-1)
	 //output("111111\n") and skip
	 
     )
     }; 
  function flush_block ( char *buf,int stored_len,int eof,int RValue )
 {
     frame(flush_block_opt_lenb,flush_block_static_lenb,flush_block_max_blindex,return) and ( 
     int return<==0 and skip;
     int flush_block_opt_lenb,flush_block_static_lenb and skip;
     int flush_block_max_blindex and skip;
     flag_buf[last_flags]:=flags;
     if(* file_type=(unsigned int)65535) then 
     {
         set_file_type(RValue)
     }
     else 
     {
          skip 
     };
     build_tree((tree_desc *)(&l_desc));
     build_tree((tree_desc *)(&d_desc));
	 //output("111\n") and skip;
     flush_block_max_blindex:=build_bl_tree(RValue);
     flush_block_opt_lenb:=(opt_len+3+7)>>3;
     flush_block_static_lenb:=(static_len+3+7)>>3;
     input_len:=input_len+stored_len;
	 
     if(flush_block_static_lenb<=flush_block_opt_lenb) then 
     {
         flush_block_opt_lenb:=flush_block_static_lenb
     }
     else 
     {
          skip 
     };
     if(stored_len<=flush_block_opt_lenb AND eof AND compressed_len=0 AND 0) then 
     {
	 
         if(buf=NULL) then 
         {
             error("block vanished",RValue)
         }
         else 
         {
              skip 
         };
         //copy_block(buf,(unsigned int)stored_len,0) and skip;
         compressed_len:=stored_len<<3;
         * file_method:=0
         
     }
     else
     {
	 
         if(stored_len+4<=flush_block_opt_lenb AND buf!=NULL) then 
         {
		  //output("222\n") and skip;
             send_bits((0<<1)+eof,3);
             compressed_len:=(compressed_len+3+7) & ~7;
             compressed_len:=compressed_len+(stored_len+4)<<3
             //copy_block(buf,(unsigned int)stored_len,1)
         }
         else
         {
		 
             if(flush_block_static_lenb=flush_block_opt_lenb) then 
             {
			 //output("333\n") and skip;
                 send_bits((1<<1)+eof,3);
                 compress_block((ct_data *)static_ltree,(ct_data *)static_dtree,RValue);
                 compressed_len:=compressed_len+3+static_len
             }
             else
             {
			 //output("444\n") and skip;
                 send_bits((2<<1)+eof,3);
				 //output("555\n") and skip;
                 send_all_trees(l_desc.max_code+1,d_desc.max_code+1,flush_block_max_blindex+1);
                 //output("666\n") and skip;
				 compress_block((ct_data *)dyn_ltree,(ct_data *)dyn_dtree,RValue);
                 //output("777\n") and skip;
				 compressed_len:=compressed_len+3+opt_len
             }
         }
     };
	  
     init_block();
     if(eof) then 
     {
         bi_windup();
         compressed_len:=compressed_len+7
         
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=compressed_len>>3;
     skip
     )
     }; 
  function ct_tally ( int dist,int lc,int RValue )
 {
     frame(ct_tally_tmp,ct_tally_4_out_length,ct_tally_4_in_length,ct_tally_4_dcode,return) and ( 
     
	 int return<==0 and skip;
     int ct_tally_tmp and skip;
	 int ct_tally_4_out_length and skip;
     int ct_tally_4_in_length and skip;
     int ct_tally_4_dcode and skip;
     inbuf[last_lit]:=(unsigned char)lc;
     last_lit:=last_lit+1;
	 
     if(dist=0) then 
     {
         dyn_ltree[lc].fc.freq:=dyn_ltree[lc].fc.freq+1
         
     }
     else
     {
         dist:=dist-1;
         dyn_ltree[length_code[lc]+256+1].fc.freq:=dyn_ltree[length_code[lc]+256+1].fc.freq+1;

         //ct_tally_tmp:=( if(dist<256) then dist_code[dist] else dist_code[256+(dist>>7)]);

		 dyn_dtree[0].fc.freq:=dyn_dtree[0].fc.freq+1;
		 d_buf[last_dist]:=(unsigned int)dist;
         last_dist:=last_dist+1;
         flags:=flags| (flag_bit)
     };
     flag_bit:=flag_bit<< (1 );
     if((last_lit & 7)=0) then 
     {
         flag_buf[last_flags]:=flags;
         last_flags:=last_flags+1;
         flags:=0;
		 flag_bit:=1
     }
     else 
     {
          skip 
     };
     if(level>2 AND ((last_lit & 4095)=0)) then 
     {
	     ct_tally_tmp<==last_lit*8 and skip;
         ct_tally_4_out_length<==ct_tally_tmp and skip;
		 ct_tally_4_in_length<==(strstart-block_start) and skip;
         ct_tally_4_dcode:=0;
         
         while(ct_tally_4_dcode<30)
         {
             ct_tally_4_out_length:=ct_tally_4_out_length+(unsigned int)dyn_dtree[ct_tally_4_dcode].fc.freq*(5+extra_dbits[ct_tally_4_dcode]);
             ct_tally_4_dcode:=ct_tally_4_dcode+1
             
         };
         ct_tally_4_out_length:=ct_tally_4_out_length>> (3 );
         if((last_dist<last_lit/2) AND (ct_tally_4_out_length < (ct_tally_4_in_length/2)) ) then 
         {
             return<==1 and RValue:=1;
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
     };
     if(return=0)  then
     {
         return<==1 and RValue:=((last_lit=32767) OR (last_dist=32768));
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function compress_block ( ct_data *ltree,ct_data *dtree )
 {
     frame(compress_block_dist,compress_block_lc,compress_block_lx,compress_block_dx,compress_block_fx,compress_block_flag,compress_block_code,compress_block_extra,count$) and ( 
     int compress_block_dist and skip;
     int compress_block_lc and skip;
     int compress_block_lx<==0 and skip;
     int compress_block_dx<==0 and skip;
     int compress_block_fx<==0 and skip;
     unsigned char compress_block_flag<==0 and skip;
     int compress_block_code and skip;
     int compress_block_extra and skip;
	 //output("wangmeng111\n") and skip;
     if(last_lit!=0) then 
     {
         int count$<==0 and skip;
         while( count$=0 OR compress_block_lx<last_lit)
         {
		     //output("wangmeng333\n") and skip;
             count$:=count$+1;
			 //output("compress_block_fx:",compress_block_fx) and skip;
			 //output("\n") and skip;
             if((compress_block_lx & 7)=0) then 
             {
                 compress_block_flag:=flag_buf[compress_block_fx];
                 compress_block_fx:=compress_block_fx+1
             }
             else 
             {
                  skip 
             };
			 //output("compress_block_lx:",compress_block_lx) and skip;
			 //output("\n") and skip;
             compress_block_lc:=inbuf[compress_block_lx];
             compress_block_lx:=compress_block_lx+1;
			 //output("compress_block_lc:",compress_block_lc) and skip;
			 //output("\n") and skip;
             if((compress_block_flag & 1)=0) then 
             {
                 send_bits(ltree[compress_block_lc].fc.code,ltree[compress_block_lc].dl.len$)
                 
             }
             else
             {
                 compress_block_code:=length_code[compress_block_lc];
                 send_bits(ltree[compress_block_code+256+1].fc.code,ltree[compress_block_code+256+1].dl.len$);
                 compress_block_extra:=extra_lbits[compress_block_code];
                 if(compress_block_extra!=0) then 
                 {
                     compress_block_lc:=compress_block_lc-base_length[compress_block_code];
                     send_bits(compress_block_lc,compress_block_extra)
                     
                 }
                 else 
                 {
                      skip 
                 };
				  //output("compress_block_dx:",compress_block_dx) and skip;
				 //output("\n") and skip;
				 //output("compress_block_dist:",compress_block_dist) and skip;
				 //output("\n") and skip;
                 compress_block_dist:=d_buf[compress_block_dx];
                 compress_block_dx:=compress_block_dx+1;

				 //output("256+(compress_block_dist>>7):",256+(compress_block_dist>>7) ) and skip;
				 //output("\n") and skip;


                 //compress_block_code:=(( if(compress_block_dist<256) then dist_code[compress_block_dist] else dist_code[256+(compress_block_dist>>7)]));
                 compress_block_code:=0;
				 //output("compress_block_code111:",compress_block_code) and skip;
				 //output("\n") and skip;

				 send_bits(dtree[compress_block_code].fc.code,dtree[compress_block_code].dl.len$);
                 
				 //output("compress_block_code:",compress_block_code) and skip;
				 //output("\n") and skip;

				 compress_block_extra:=extra_dbits[compress_block_code];
				 
				 

                 if(compress_block_extra!=0) then 
                 {
				
                     compress_block_dist:=compress_block_dist-base_dist[compress_block_code];
                     send_bits(compress_block_dist,compress_block_extra)
					  //output("compress_block_code111:",compress_block_code) and skip;
				 //output("\n") and skip
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             compress_block_flag:=compress_block_flag>> (1 )
         }
     }
     else 
     {
          skip 
     };
	 //output("wangmeng222\n") and skip;
     send_bits(ltree[256].fc.code,ltree[256].dl.len$)
     )
     }; 
  function set_file_type (  )
 {
     frame(set_file_type_n,set_file_type_ascii_freq,set_file_type_bin_freq) and ( 
     int set_file_type_n<==0 and skip;
     int set_file_type_ascii_freq<==0 and skip;
     int set_file_type_bin_freq<==0 and skip;
     while(set_file_type_n<7)
     {
         set_file_type_bin_freq:=set_file_type_bin_freq+dyn_ltree[set_file_type_n].fc.freq;
         set_file_type_n:=set_file_type_n+1
     };
     while(set_file_type_n<128)
     {
         set_file_type_ascii_freq:=set_file_type_ascii_freq+dyn_ltree[set_file_type_n].fc.freq;
         set_file_type_n:=set_file_type_n+1
     };
     while(set_file_type_n<256)
     {
         set_file_type_bin_freq:=set_file_type_bin_freq+dyn_ltree[set_file_type_n].fc.freq;
         set_file_type_n:=set_file_type_n+1
     };
     * file_type:=( if(set_file_type_bin_freq>(set_file_type_ascii_freq>>2)) then 0 else 1)
     )
}; 
 unsigned char pt_len[(16+3)] and skip;
 int blocksize and skip;
 int pt_table[256] and skip;
 int bitbuf and skip;
 int subbitbuf and skip;
 int bitcount and skip;
 function fillbuf (int n,int RValue)
 {
     bitbuf:=bitbuf<< (n );
     while(n>bitcount)
     {
	     n:=n-bitcount;
         bitbuf:=bitbuf| (subbitbuf<<(n));
         subbitbuf:=(int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(1,RValue)));
         if((int)subbitbuf=EOF) then 
         {
             subbitbuf:=0
         }
         else 
         {
              skip 
         };
         bitcount:=8
     };
	 bitcount:=bitcount-n;
     bitbuf:=bitbuf| (subbitbuf>>(bitcount))
     
 };
 function getbits ( int getbits_n,int RValue )
 {
     frame(getbits_x,return) and ( 
     int return<==0 and skip;
     int getbits_x and skip;
     getbits_x:=bitbuf>>(16-getbits_n);
     fillbuf(getbits_n);
     return<==1 and RValue:=getbits_x;
     skip
     )
     }; 
  function init_getbits (  )
 {
     bitbuf:=0;
     subbitbuf:=0;
     bitcount:=0;
     fillbuf(16)
     
 };
 function make_table ( int nchar,unsigned char bitlen[],int tablebits,int table[] )
 {
     frame(make_table_count,make_table_weight,make_table_start,make_table_p,make_table_i,make_table_k,make_table_len$,make_table_ch,make_table_jutbits,make_table_avail,make_table_nextcode,make_table_mask,continue$) and ( 
     int continue$<==0 and skip;
     int make_table_count[17],make_table_weight[17],make_table_start[18],*make_table_p and skip;
     int make_table_i,make_table_k,make_table_len$,make_table_ch,make_table_jutbits,make_table_avail,make_table_nextcode,make_table_mask and skip;
     make_table_i:=1;
     
     while(make_table_i<=16)
     {
         make_table_count[make_table_i]:=0;
         make_table_i:=make_table_i+1
         
     };
     make_table_i:=0;
     
     while(make_table_i<(int)nchar)
     {
         make_table_count[bitlen[make_table_i]]:=make_table_count[bitlen[make_table_i]]+1;
         make_table_i:=make_table_i+1
         
     };
     make_table_start[1]:=0;
     make_table_i:=1;
     
     while(make_table_i<=16)
     {
         make_table_start[make_table_i+1]:=make_table_start[make_table_i]+(make_table_count[make_table_i]<<(16-make_table_i));
         make_table_i:=make_table_i+1
         
     };
     if((make_table_start[17] & 65535)!=0) then 
     {
         error("Bad table\n",RValue)
     }
     else 
     {
          skip 
     };
     make_table_jutbits:=16-tablebits;
     make_table_i:=1;
     
     while(make_table_i<=(int)tablebits)
     {
         make_table_start[make_table_i]:=make_table_start[make_table_i]>> (make_table_jutbits );
         make_table_weight[make_table_i]:=(int)1<<(tablebits-make_table_i);
         make_table_i:=make_table_i+1
         
     };
     while(make_table_i<=16)
     {
         make_table_weight[make_table_i]:=(int)1<<(16-make_table_i);
         make_table_i:=make_table_i+1
     };
     make_table_i:=make_table_start[tablebits+1]>>make_table_jutbits;
     if(make_table_i!=0) then 
     {
         make_table_k:=1<<tablebits;
         while(make_table_i!=make_table_k)
         {
             table[make_table_i]:=0;
             make_table_i:=make_table_i+1
         }
         
     }
     else 
     {
          skip 
     };
     make_table_avail:=nchar;
     make_table_mask:=(int)1<<(15-tablebits);
     continue$<==0 and skip;
     make_table_ch:=0;
     
     while(make_table_ch<(int)nchar)
     {
          continue$<==0 and skip;
         make_table_len$:=bitlen[make_table_ch] ;
         if((make_table_len$)=0) then 
         {
             continue$<==1 and skip;
              make_table_ch:=make_table_ch+1
         }
         else 
         {
              skip 
         };
         if(continue$=0)   then 
         {
             make_table_nextcode:=make_table_start[make_table_len$]+make_table_weight[make_table_len$];
             if(make_table_len$<=(int)tablebits) then 
             {
                 make_table_i:=make_table_start[make_table_len$];
                 
                 while(make_table_i<make_table_nextcode)
                 {
                     table[make_table_i]:=make_table_ch;
                     make_table_i:=make_table_i+1
                     
                 }
                 
             }
             else
             {
                 make_table_k:=make_table_start[make_table_len$];
                 make_table_p:=&table[make_table_k>>make_table_jutbits];
                 make_table_i:=make_table_len$-tablebits;
                 while(make_table_i!=0)
                 {      
                     make_table_k:=make_table_k<< (1 );
                     make_table_i:=make_table_i-1
                 };
                 * make_table_p:=make_table_ch
             };
             make_table_start[make_table_len$]:=make_table_nextcode;
             make_table_ch:=make_table_ch+1
         }
         else
         {
             skip
         }
     };
     continue$<==0 and skip
     )
     }; 
  function read_pt_len ( int nn,int nbit,int i_special )
 {
     frame(read_pt_len_i,read_pt_len_c,read_pt_len_n,read_pt_len_mask) and ( 
     int read_pt_len_i,read_pt_len_c,read_pt_len_n and skip;
     int read_pt_len_mask and skip;
     read_pt_len_n:=getbits(nbit,RValue);
     if(read_pt_len_n=0) then 
     {
         read_pt_len_c:=getbits(nbit,RValue);
         read_pt_len_i:=0;
         
         while(read_pt_len_i<nn)
         {
             pt_len[read_pt_len_i]:=0;
             read_pt_len_i:=read_pt_len_i+1
             
         };
         read_pt_len_i:=0;
         
         while(read_pt_len_i<256)
         {
             pt_table[read_pt_len_i]:=read_pt_len_c;
             read_pt_len_i:=read_pt_len_i+1
             
         }
     }
     else
     {
         read_pt_len_i:=0;
         while(read_pt_len_i<read_pt_len_n)
         {
             read_pt_len_c:=bitbuf>>(16-3);
             if(read_pt_len_c=7) then 
             {
                 read_pt_len_mask:=(int)1<<(16-1-3);
                 while(read_pt_len_mask & bitbuf)
                 {
                     read_pt_len_mask:=read_pt_len_mask>> (1 );
                     read_pt_len_c:=read_pt_len_c+1
                 }
                 
             }
             else 
             {
                  skip 
             };
             fillbuf(( if((read_pt_len_c<7)) then 3 else read_pt_len_c-3));
             pt_len[read_pt_len_i]:=read_pt_len_c;
             read_pt_len_i:=read_pt_len_i+1;
             if(read_pt_len_i=i_special) then 
             {
                 read_pt_len_c:=getbits(2,RValue);
                 while((read_pt_len_c-1)>=0)
                 {
                     read_pt_len_c:=read_pt_len_c-1;
                     pt_len[read_pt_len_i]:=0;
                     read_pt_len_i:=read_pt_len_i+1
                 }
                 
             }
             else 
             {
                  skip 
             }
         };
         while(read_pt_len_i<nn)
         {
             pt_len[read_pt_len_i]:=0;
             read_pt_len_i:=read_pt_len_i+1
         };
         make_table(nn,pt_len,8,pt_table)
     }
     )
     }; 
  function read_c_len (  )
 {
     frame(read_c_len_i,read_c_len_c,read_c_len_n,read_c_len_mask,count$) and ( 
     int read_c_len_i,read_c_len_c,read_c_len_n and skip;
     int read_c_len_mask and skip;
     read_c_len_n:=getbits(9,RValue);
     if(read_c_len_n=0) then 
     {
         read_c_len_c:=getbits(9,RValue);
         read_c_len_i:=0;
         
         while(read_c_len_i<(255+256+2-3))
         {
             outbuf[read_c_len_i]:=0;
             read_c_len_i:=read_c_len_i+1
             
         };
         read_c_len_i:=0;
         
         while(read_c_len_i<4096)
         {
             d_buf[read_c_len_i]:=read_c_len_c;
             read_c_len_i:=read_c_len_i+1
             
         }
     }
     else
     {
         read_c_len_i:=0;
         while(read_c_len_i<read_c_len_n)
         {
             read_c_len_c:=pt_table[bitbuf>>(16-8)];
             if(read_c_len_c>=(16+3)) then 
             {
                 read_c_len_mask:=(int)1<<(16-1-8);
                 int count$<==0 and skip;
                 while( count$=0 OR read_c_len_c>=(16+3))
                 {
                     count$:=count$+1;                   
                     read_c_len_mask:=read_c_len_mask>> (1 )
                 }                 
             }
             else 
             {
                  skip 
             };
             fillbuf((int)pt_len[read_c_len_c]);
             if(read_c_len_c<=2) then 
             {
                 if(read_c_len_c=0) then 
                 {
                     read_c_len_c:=1
                 }
                 else
                 {
                     if(read_c_len_c=1) then 
                     {
                         read_c_len_c:=getbits(4,RValue)+3
                     }
                     else
                     {
                         read_c_len_c:=getbits(9,RValue)+20
                     }
                 };
                 while((read_c_len_c-1)>=0)
                 {
                     read_c_len_c:=read_c_len_c-1;
                     outbuf[read_c_len_i]:=0;
                     read_c_len_i:=read_c_len_i+1
                 }
             }
             else
             {
                 outbuf[read_c_len_i]:=read_c_len_c-2;
                 read_c_len_i:=read_c_len_i+1
             }
         };
         while(read_c_len_i<(255+256+2-3))
         {
             outbuf[read_c_len_i]:=0;
             read_c_len_i:=read_c_len_i+1
         };
         make_table((255+256+2-3),outbuf,12,d_buf)
     }
     )
     }; 
  function decode_c_1 ( int RValue )
 {
     frame(decode_c_j,decode_c_mask,count$,return) and ( 
     int return<==0 and skip;
     int decode_c_j,decode_c_mask and skip;
     if(blocksize=0) then 
     {
         blocksize:=getbits(16,RValue);
         if(blocksize=0) then 
         {
             return<==1 and RValue:=(255+256+2-3);
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             read_pt_len((16+3),5,3);
             read_c_len();
             read_pt_len((13+1),4,-1)
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
         blocksize:=blocksize-1;
         decode_c_j:=d_buf[bitbuf>>(16-12)];
         if(decode_c_j>=(255+256+2-3)) then 
         {
             decode_c_mask:=(int)1<<(16-1-12);
             int count$<==0 and skip;
             while( count$=0 OR decode_c_j>=(255+256+2-3))
             {
                 count$:=count$+1;          
                 decode_c_mask:=decode_c_mask>> (1 )
             }
             
         }
         else 
         {
              skip 
         };
         fillbuf((int)outbuf[decode_c_j]);
         return<==1 and RValue:=decode_c_j;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function decode_p ( int RValue )
 {
     frame(decode_p_j,decode_p_mask,count$,return) and ( 
     int return<==0 and skip;
     int decode_p_j,decode_p_mask and skip;
     decode_p_j:=pt_table[bitbuf>>(16-8)];
     if(decode_p_j>=(13+1)) then 
     {
         decode_p_mask:=(int)1<<(16-1-8);
         int count$<==0 and skip;
         while( count$=0 OR decode_p_j>=(13+1))
         {
             count$:=count$+1;           
             decode_p_mask:=decode_p_mask>> (1 )
         }
         
     }
     else 
     {
          skip 
     };
     fillbuf((int)pt_len[decode_p_j]);
     if(decode_p_j!=0) then 
     {
         decode_p_j:=((int)1<<(decode_p_j-1))+getbits((int)(decode_p_j-1),RValue)
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=decode_p_j;
     skip
     )
     }; 
  function huf_decode_start (  )
 {
     init_getbits();
     blocksize:=0
     
 };
 int j and skip;
 int done and skip;
 function decode_start (  )
 {
     huf_decode_start();
     j:=0;
     done:=0
     
 };
 function decode ( int count,unsigned char buffer[],int RValue )
 {
     frame(decode_i,decode_r,decode_c,return) and ( 
     int return<==0 and skip;
     int decode_i and skip;
     int decode_r,decode_c and skip;
     decode_r:=0;
     while( return=0 AND  (j-1)>=0)
     {
         j:=j-1;
         buffer[decode_r]:=buffer[decode_i];
         decode_i:=(decode_i+1) & (((int)1<<13)-1);
         if((decode_r+1)=count) then 
         {
             decode_r:=decode_r+1;
             return<==1 and RValue:=decode_r;
             skip
         }
         else 
         {
             decode_r:=decode_r+1
             
         }
     };
     if(return=0)   then 
     {
         while( return=0 AND   return=0 AND  true)
         {
             decode_c:=decode_c_1(RValue);
             if(decode_c=(255+256+2-3)) then 
             {
                 done:=1;
                 return<==1 and RValue:=decode_r;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 if(decode_c<=255) then 
                 {
                     buffer[decode_r]:=decode_c;
                     if((decode_r+1)=count) then 
                     {
                         decode_r:=decode_r+1;
                         return<==1 and RValue:=decode_r;
                         skip
                     }
                     else 
                     {
                         decode_r:=decode_r+1
                         
                     }
                 }
                 else
                 {
                     j:=decode_c-(255+1-3);
                     decode_i:=(decode_r-decode_p(RValue)-1) & (((int)1<<13)-1);
                     while( return=0 AND  (j-1)>=0)
                     {
                         j:=j-1;
                         buffer[decode_r]:=buffer[decode_i];
                         decode_i:=(decode_i+1) & (((int)1<<13)-1);
                         if((decode_r+1)=count) then 
                         {
                             decode_r:=decode_r+1;
                             return<==1 and RValue:=decode_r;
                             skip
                         }
                         else 
                         {
                             decode_r:=decode_r+1
                             
                         }
                     }
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
     }
     )
     }; 
  function unlzh ( int in,int out,int RValue )
 {
     frame(unlzh_n,return) and ( 
     int return<==0 and skip;
     int unlzh_n and skip;
     ifd:=in;
     ofd:=out;
     decode_start();
     while(!done)
     {
         unlzh_n:=decode((int)((int)1<<13),window,RValue);
         if(!test AND unlzh_n>0) then 
         {
             write_buf(out,(char *)window,unlzh_n,RValue)
             
         }
         else 
         {
              skip 
         }
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
      struct struct$3 {
     int dummy 
 };
 union bytes {
 int word and 
 struct$3  bytes$ 
 };
 int block_mode<==128 and skip;
 int orig_len and skip;
 int max_len and skip;
 unsigned char literal[256] and skip;
 int lit_base[25+1] and skip;
 int leaves[25+1] and skip;
 int parents[25+1] and skip;
 int peek_bits and skip;
 int valid and skip;
 function read_tree ( int RValue )
 {
     frame(read_tree_len$,read_tree_base,read_tree_n) and ( 
     int read_tree_len$ and skip;
     int read_tree_base and skip;
     int read_tree_n and skip;
     orig_len:=0;
     read_tree_n:=1;
     
     while(read_tree_n<=4)
     {
         orig_len:=(orig_len<<8) | (unsigned int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
         read_tree_n:=read_tree_n+1
         
     };
     max_len:=(int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
     if(max_len>25) then 
     {
         error("invalid compressed data -- Huffman code > 32 bits",RValue)
         
     }
     else 
     {
          skip 
     };
     read_tree_n:=0;
     read_tree_len$:=1;
     
     while(read_tree_len$<=max_len)
     {
         leaves[read_tree_len$]:=(int)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
         read_tree_n:=read_tree_n+leaves[read_tree_len$];
         read_tree_len$:=read_tree_len$+1
         
     };
     if(read_tree_n>256) then 
     {
         error("too many leaves in Huffman tree",RValue)
         
     }
     else 
     {
          skip 
     };
     leaves[max_len]:=leaves[max_len]+1;
     read_tree_base:=0;
     read_tree_len$:=1;
     
     while(read_tree_len$<=max_len)
     {
         lit_base[read_tree_len$]:=read_tree_base;
         read_tree_n:=leaves[read_tree_len$];
         
         while(read_tree_n>0)
         {
             literal[read_tree_base]:=(unsigned char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
             read_tree_base:=read_tree_base+1;
             read_tree_n:=read_tree_n-1
             
         };
         read_tree_len$:=read_tree_len$+1
         
     };
     leaves[max_len]:=leaves[max_len]+1
     )
     }; 
  function build_tree_1 (  )
 {
     frame(build_tree_nodes,build_tree_len$,build_tree_prefixp,build_tree_prefixes) and ( 
     int build_tree_nodes<==0 and skip;
     int build_tree_len$ and skip;
     unsigned char *build_tree_prefixp and skip;
     build_tree_len$:=max_len;
     
     while(build_tree_len$>=1)
     {
         build_tree_nodes:=build_tree_nodes>> (1 );
         parents[build_tree_len$]:=build_tree_nodes;
         lit_base[build_tree_len$]:=lit_base[build_tree_len$]-build_tree_nodes;
         build_tree_nodes:=build_tree_nodes+leaves[build_tree_len$];
         build_tree_len$:=build_tree_len$-1
         
     };
     peek_bits:=(( if(max_len<=12) then max_len else 12));
     build_tree_prefixp:=&outbuf[1<<peek_bits];
     build_tree_len$:=1;
     
     while(build_tree_len$<=peek_bits)
     {
         int build_tree_prefixes<==leaves[build_tree_len$]<<(peek_bits-build_tree_len$) and skip;
         while(build_tree_prefixes)
         {
             build_tree_prefixes:=build_tree_prefixes-1;
             * (build_tree_prefixp-1):=(unsigned char)build_tree_len$;
             build_tree_prefixp:=build_tree_prefixp-1
         };
         build_tree_len$:=build_tree_len$+1
         
     };
     while(build_tree_prefixp>outbuf)
     {
         * (build_tree_prefixp-1):=0;
         build_tree_prefixp:=build_tree_prefixp-1
     }
     )
     }; 
  function unpack ( int in,int out,int RValue )
 {
     frame(unpack_len$,unpack_eob,unpack_peek,unpack_peek_mask,unpack_3_mask,count$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int unpack_len$ and skip;
     int unpack_eob and skip;
     int unpack_peek and skip;
     int unpack_peek_mask and skip;
     ifd:=in;
     ofd:=out;
     read_tree();
     build_tree_1();
     valid:=0;
	 bitbuf:=0;
     unpack_peek_mask:=(1<<peek_bits)-1;
     unpack_eob:=leaves[max_len]-1;
     break$<==0 and skip;
     while( break$=0 AND  true)
     {
         while(valid<peek_bits)
         {
             bitbuf:=(bitbuf<<8) | ( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue));
			 if(inptr<insize) then {inptr:=inptr+1} else {skip};
			 valid:=valid+8
			 };
             unpack_peek:=(bitbuf>>(valid-peek_bits)) & unpack_peek_mask;
             unpack_len$:=outbuf[unpack_peek];
             if(unpack_len$>0) then 
             {
                 unpack_peek:=unpack_peek>> (peek_bits-unpack_len$ )
                 
             }
             else
             {
                 int unpack_3_mask<==unpack_peek_mask and skip;
                 unpack_len$:=peek_bits;
                 int count$<==0 and skip;
                 while( count$=0 OR unpack_peek<(unsigned int)parents[unpack_len$])
                 {
                     count$:=count$+1;
                     unpack_len$:=unpack_len$+1;
					 unpack_3_mask:=(unpack_3_mask<<1)+1;
					 while(valid<unpack_len$)
                     {
                         bitbuf:=(bitbuf<<8) | ( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue));
						 if(inptr<insize) then {inptr:=inptr+1} else {skip};
						 valid:=valid+8
						 };
                         unpack_peek:=(bitbuf>>(valid-unpack_len$)) & unpack_3_mask
                     }
                 };
                 if(unpack_peek=unpack_eob AND unpack_len$=max_len) then 
                 {
                     break$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     window[outcnt]:=(unsigned char)(literal[unpack_peek+lit_base[unpack_len$]]);
                     outcnt:=outcnt+1;
                     if(outcnt=32768) then 
                     {
                         flush_window(RValue)
                     }
                     else 
                     {
                          skip 
                     };
                     (valid:=valid-unpack_len$) and skip
                 }
                 else
                 {
                     skip
                 }
                 
             };
             break$<==0 and skip;
             flush_window(RValue);
         /*    if(orig_len!=(unsigned int)bytes_out) then 
             {
                 error("invalid compressed data--length error",RValue)
                 
             }
             else 
             {
                  skip 
             }; */
             return<==1 and RValue:=0;
             skip
             )
             }; 
              int decrypt and skip;
             char *key and skip;
             int pkzip<==0 and skip;
             int ext_header<==0 and skip;
 function unzip ( int in,int out,int RValue )
 {
     frame(unzip_orig_crc,unzip_orig_len,unzip_n,unzip_tmp1,unzip_tmp2,unzip_tmp3,unzip_tmp4,unzip_buf,unzip_2_res,unzip_6_7_9_c,return) and ( 
     int return<==0 and skip;
     int unzip_orig_crc<==0 and skip;
     int unzip_orig_len<==0 and skip;
     int unzip_n and skip;
	 int unzip_6_7_9_c and skip;
	 unsigned char unzip_tmp1 and skip;
	 unsigned char unzip_tmp2 and skip;
	 unsigned char unzip_tmp3 and skip;
	 unsigned char unzip_tmp4 and skip;
     unsigned char unzip_buf[16] and skip;
     ifd:=in;
     ofd:=out;
     if(method=8) then 
     {
         int unzip_2_res and skip;
         unzip_2_res:=inflate(RValue);
         if(unzip_2_res=3) then 
         {
             error("out of memory",RValue)
         }
         else
         {
             if(unzip_2_res!=0) then 
             {
                 error("invalid compressed data--format violated",RValue)
                 
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
     if(!pkzip) then 
     {
         unzip_n:=0;      
         while(unzip_n<8)
         {
             unzip_buf[unzip_n]:=(unsigned char)(( if(inptr<insize) then inbuf[inptr] else fill_inbuf(0,RValue)));
             if(inptr<insize) then{inptr:=inptr+1}else{skip};
			 unzip_n:=unzip_n+1
             
         };
		 unzip_tmp1<==unzip_buf[0] and skip;
		 unzip_tmp2<==unzip_buf[1] and skip;
		 unzip_tmp2<==unzip_tmp2<<8 and skip;
		 unzip_tmp3<==*(unzip_buf+2) and skip;
		 //unzip_tmp3<==unzip_tmp3[0] and skip;
		 unzip_tmp4<==*(unzip_buf+3) and skip;
		 //unzip_tmp4<==unzip_tmp4[1] and skip;
		 unzip_tmp4<==unzip_tmp4<<8 and skip;
	     unzip_orig_crc:=((unzip_tmp1 | unzip_tmp2) | ((unzip_tmp3 | unzip_tmp4)<<16));
		 unzip_tmp1<==*(unzip_buf+4) and skip;
		 //unzip_tmp1<==unzip_tmp1[0] and skip;
		 unzip_tmp2<==*(unzip_buf+5) and skip;
		 //unzip_tmp2<==unzip_tmp2[1] and skip;
		 unzip_tmp2<==unzip_tmp2<<8 and skip;
		 unzip_tmp3<==*(unzip_buf+6) and skip;
		 //unzip_tmp3<==unzip_tmp3[0] and skip;
		 unzip_tmp4<==*(unzip_buf+7) and skip;
		 //unzip_tmp4<==unzip_tmp4[1] and skip;
		 unzip_tmp4<==unzip_tmp4<<8 and skip;
         unzip_orig_len:=((unzip_tmp1 | unzip_tmp2) | ((unzip_tmp3 | unzip_tmp4)<<16)) 
     }
     else
     {
         skip 
     };
  /*   if(unzip_orig_len!=(unsigned int)bytes_out) then 
     {
         error("invalid compressed data--length error",RValue)
         
     }
     else 
     {
          skip 
     }; */
     pkzip<==0 and ext_header<==pkzip and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function copy ( int in,int out,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     while(insize!=0 AND (int)insize!=EOF)
     {
         write_buf(out,(char *)inbuf,insize,RValue);
         bytes_out:=bytes_out+insize;
         insize:=spec_read(in,(char *)inbuf,32768,RValue)
     };
     if((int)insize=EOF) then 
     {
         read_error(RValue)
         
     }
     else 
     {
          skip 
     };
     bytes_in:=bytes_out;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function clear_bufs (  )
 {
     outcnt:=0;
     inptr<==0 and insize<==inptr and skip;
     bytes_out<==0 and bytes_in<==bytes_out and skip
     
 };
 function fill_inbuf ( int eof_ok,int RValue )
 {
     frame(fill_inbuf_len$,count$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int fill_inbuf_len$ and skip;
     insize:=0;
     int count$<==0 and skip;
     break$<==0 and skip;
     while( break$=0 AND   ( count$=0 OR insize<32768))
     {
         count$:=count$+1;
         fill_inbuf_len$:=spec_read(ifd,(char *)inbuf+insize,32768-insize,RValue);
         if(fill_inbuf_len$=0 OR fill_inbuf_len$=EOF) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             insize:=insize+fill_inbuf_len$
         }
         else
         {
             skip
         }
     };
     break$<==0 and skip;
     if(insize=0) then 
     {
         if(eof_ok) then 
         {
             return<==1 and RValue:=EOF;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             read_error(RValue)
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
         bytes_in:=bytes_in+(unsigned int)insize;
         inptr:=1;
         return<==1 and RValue:=inbuf[0];
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function flush_outbuf (  )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(outcnt=0) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         write_buf(ofd,(char *)outbuf,outcnt,RValue);
         bytes_out:=bytes_out+(unsigned int)outcnt;
         outcnt:=0
     }
     else
     {
         skip
     }
     )
     }; 
  function flush_window (  )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(outcnt=0) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(!test) then 
         {
             write_buf(ofd,(char *)window,outcnt,RValue)
             
         }
         else 
         {
              skip 
         };
         bytes_out:=bytes_out+(unsigned int)outcnt;
         outcnt:=0
     }
     else
     {
         skip
     }
     )
     }; 
  function write_buf ( int fd,char *buf,int cnt )
 {
     frame(write_buf_n) and ( 
     int write_buf_n and skip;
     write_buf_n:=spec_write(fd,buf,cnt,RValue) ;
     while((write_buf_n)!=cnt)
     {
         if(write_buf_n=(int)(-1)) then 
         {
             write_error(RValue)
             
         }
         else 
         {
              skip 
         };
         cnt:=cnt-write_buf_n;
         buf:=(char *)((char *)buf+write_buf_n);
         write_buf_n:=spec_write(fd,buf,cnt,RValue) 
     }
     )
     }; 
  function strlwr ( char *s,char* RValue )
 {
     frame(strlwr_t,return) and ( 
     int return<==0 and skip;
     char *strlwr_t and skip;
     strlwr_t:=s;
     
     while(* strlwr_t)
     {
         * strlwr_t:=(( if(isupper(* strlwr_t,RValue)) then (* strlwr_t)-'A'+'a' else (* strlwr_t)));
         strlwr_t:=strlwr_t+1
         
     };
     return<==1 and RValue:=s;
     skip
     )
     }; 
  function gzipbasename ( char *fname,char* RValue )
 {
     frame(gzipbasename_p,return) and ( 
     int return<==0 and skip;
     char *gzipbasename_p and skip;
     gzipbasename_p:=strrchr(fname,'/',RValue) ;
     if((gzipbasename_p)!=NULL) then 
     {
         fname:=gzipbasename_p+1
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=fname;
     skip
     )
     }; 
  function make_simple_name ( char *name )
 {
     frame(make_simple_name_p,count$,return) and ( 
     int return<==0 and skip;
     char *make_simple_name_p and skip;
     make_simple_name_p:=strrchr(name,'.',RValue);
     if(make_simple_name_p=NULL) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(make_simple_name_p=name) then 
         {
             make_simple_name_p:=make_simple_name_p+1
         }
         else 
         {
              skip 
         };
         int count$<==0 and skip;
         while( count$=0 OR make_simple_name_p!=name)
         {
             count$:=count$+1;
             if(* (make_simple_name_p-1)='.') then 
             {
                 make_simple_name_p:=make_simple_name_p-1;
                 * make_simple_name_p:='_'
             }
             else 
             {
                 make_simple_name_p:=make_simple_name_p-1
                 
             }
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function add_envopt ( int *argcp,char ***argvp,char *env,char* RValue )
 {
     frame(add_envopt_p,add_envopt_oargv,add_envopt_nargv,add_envopt_oargc,add_envopt_nargc,add_envopt_temp$_1,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     char *add_envopt_p and skip;
     char **add_envopt_oargv and skip;
     char **add_envopt_nargv and skip;
     int add_envopt_oargc<==* argcp and skip;
     int add_envopt_nargc<==0 and skip;
     if(env=NULL) then 
     {
         return<==1 and RValue:=NULL;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         int add_envopt_temp$_1 and skip;
         add_envopt_temp$_1:=strlen(env);
         add_envopt_p:=(char *)xmalloc(add_envopt_temp$_1+1,RValue);
         env:=strcpy(add_envopt_p,env);
         break$<==0 and skip;
         add_envopt_p:=env;
         
         while( break$=0 AND  * add_envopt_p)
         {
             add_envopt_p:=add_envopt_p+strspn(add_envopt_p," \t",RValue);
             if(* add_envopt_p='\0') then 
             {
                 break$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 add_envopt_p:=add_envopt_p+strcspn(add_envopt_p," \t",RValue);
                 if(* add_envopt_p) then 
                 {
                     * add_envopt_p:='\0';
                     add_envopt_p:=add_envopt_p+1
                 }
                 else 
                 {
                      skip 
                 };
                 add_envopt_nargc:=add_envopt_nargc+1
             }
             else
             {
                 skip
             }
             
         };
         break$<==0 and skip;
         if(add_envopt_nargc=0) then 
         {
             free(env) and skip;
             return<==1 and RValue:=NULL;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             * argcp:=* argcp+add_envopt_nargc;
             add_envopt_nargv:=(char **)calloc(* argcp+1,4,RValue);
             if(add_envopt_nargv=NULL) then 
             {
                 error("out of memory",RValue)
             }
             else 
             {
                  skip 
             };
             add_envopt_oargv:=* argvp;
             * argvp:=add_envopt_nargv;
             if(add_envopt_oargc<0) then 
             {
                 add_envopt_oargc:=add_envopt_oargc-1;
                 error("argc<=0",RValue)
             }
             else 
             {
                 add_envopt_oargc:=add_envopt_oargc-1
                 
             };
             * (add_envopt_nargv):=* (add_envopt_oargv);
             add_envopt_nargv:=add_envopt_nargv+1;
             add_envopt_oargv:=add_envopt_oargv+1;
             add_envopt_p:=env;
             
             while(add_envopt_nargc>0)
             {
                 add_envopt_p:=add_envopt_p+strspn(add_envopt_p," \t",RValue);
                 * (add_envopt_nargv):=add_envopt_p;
                 add_envopt_nargv:=add_envopt_nargv+1;
                 while(* add_envopt_p)
                 {
                     add_envopt_p:=add_envopt_p+1
                 };
                 add_envopt_nargc:=add_envopt_nargc-1
                 
             };
             while(add_envopt_oargc)
             {
                 add_envopt_oargc:=add_envopt_oargc-1;
                 * (add_envopt_nargv):=* (add_envopt_oargv);
                 add_envopt_nargv:=add_envopt_nargv+1;
                 add_envopt_oargv:=add_envopt_oargv+1
             };
             * add_envopt_nargv:=NULL;
             return<==1 and RValue:=env;
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
  function error ( char *m )
 {
     fprintf(stderr,"\n%s: %s: %s\n",progname,ifname,m,RValue) and skip;
     abort_gzip() 
     
 };

 function read_error (  )
 {
     fprintf(stderr,"\n%s: ",progname,RValue) and skip;
     abort_gzip()
     
 };
 function write_error (  )
 {
     fprintf(stderr,"\n%s: ",progname,RValue) and skip;
     perror(ofname,RValue) and skip;
     abort_gzip()
     
 };
 function display_ratio ( int num,int den,FILE *file )
 {
     frame(display_ratio_ratio) and ( 
     int display_ratio_ratio and skip;
     if(den=0) then 
     {
         display_ratio_ratio:=0
         
     }
     else
     {
         if(den<2147483) then 
         {
             display_ratio_ratio:=1000*num/ den
         }
         else
         {
             display_ratio_ratio:=num/ (den/ 1000)
         }
     };
     if(display_ratio_ratio<0) then 
     {
         fputc('-',file,RValue) and skip;
         display_ratio_ratio:=-display_ratio_ratio
         
     }
     else
     {
         fputc(' ',file,RValue)
     };
     fprintf(file,"%2ld.%1ld%%",display_ratio_ratio/ 10,display_ratio_ratio % 10,RValue) and skip
     )
     }; 
  function xmalloc ( int size,char* RValue )
 {
     frame(xmalloc_cp,return) and ( 
     int return<==0 and skip;
     char *xmalloc_cp and skip;
     xmalloc_cp:=(char *)malloc(size);
     if(xmalloc_cp=NULL) then 
     {
         error("out of memory")
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=xmalloc_cp;
     skip
     )
     }; 
      int crc and skip;
     int header_bytes and skip;
 function zip ( int in,int out,int RValue )
 {
     frame(zip_flags,zip_tmp,zip_attr,zip_deflate_flags,zip_16_p,count$,return) and ( 
     int return<==0 and skip;
     unsigned char zip_flags<==0 and skip;
     int zip_attr<==0 and skip;
     int zip_deflate_flags<==0 and skip;
	 unsigned char zip_tmp[20] and skip;
     ifd:=in;
     ofd:=out;
     outcnt:=0;
     method:=8;
	 zip_tmp<=="\037\213" and skip;
     outbuf[outcnt]:=(unsigned char)(zip_tmp[0]);
     outcnt:=outcnt+1;
     if(outcnt=16384) then 
     {
         flush_outbuf()
     }
     else 
     {
          skip 
     };
     outbuf[outcnt]:=(unsigned char)(zip_tmp[1]);
     outcnt:=outcnt+1;
     if(outcnt=16384) then 
     {
         flush_outbuf()
     }
     else 
     {
          skip 
     };
     outbuf[outcnt]:=(unsigned char)8;
     outcnt:=outcnt+1;
     if(outcnt=16384) then 
     {
         flush_outbuf()
     }
     else 
     {
          skip 
     };
     if(save_orig_name) then 
     {
         zip_flags:=zip_flags| (8)
         
     }
     else 
     {
          skip 
     };
     outbuf[outcnt]:=(unsigned char)zip_flags;
     outcnt:=outcnt+1;
     if(outcnt=16384) then 
     {
         flush_outbuf()
     }
     else 
     {
          skip 
     };
	 //output("houxia555\n") and skip;
     if(outcnt<16384-2) then 
     {
         outbuf[outcnt]:=(unsigned char)((time_stamp & 65535) & 255);
         outcnt:=outcnt+1;
         outbuf[outcnt]:=(unsigned char)((unsigned int)(time_stamp & 65535)>>8);
         outcnt:=outcnt+1
         
     }
     else
     {
         outbuf[outcnt]:=(unsigned char)((unsigned char)((time_stamp & 65535) & 255));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         };
         outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)(time_stamp & 65535)>>8));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         }
     };
	 //output("houxia666\n") and skip;
     if(outcnt<16384-2) then 
     {
         outbuf[outcnt]:=(unsigned char)((((unsigned int)time_stamp)>>16) & 255);
         outcnt:=outcnt+1;
         outbuf[outcnt]:=(unsigned char)((unsigned int)(((unsigned int)time_stamp)>>16)>>8);
         outcnt:=outcnt+1
         
     }
     else
     {
         outbuf[outcnt]:=(unsigned char)((unsigned char)((((unsigned int)time_stamp)>>16) & 255));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         };
         outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)(((unsigned int)time_stamp)>>16)>>8));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         }
     };
	 //output("houxia666\n") and skip;
     bi_init(out);
     ct_init(&zip_attr,&method);
     lm_init(level,&zip_deflate_flags);
     outbuf[outcnt]:=(unsigned char)((unsigned char)zip_deflate_flags);
     outcnt:=outcnt+1;
	 //output("houxia777\n") and skip;
     if(outcnt=16384) then 
     {
         flush_outbuf()
     }
     else 
     {
          skip 
     };
     outbuf[outcnt]:=(unsigned char)3;
     outcnt:=outcnt+1;
     if(outcnt=16384) then 
     {
         flush_outbuf()
     }
     else 
     {
          skip 
     };
     if(save_orig_name) then 
     {
         char *zip_16_p and skip;
         zip_16_p:=gzipbasename(ifname,RValue);
         int count$<==0 and skip;
         while( count$=0 OR * zip_16_p)
         {
             count$:=count$+1;
             zip_16_p:=zip_16_p+1;
             outbuf[outcnt]:=(unsigned char)(* zip_16_p);
             outcnt:=outcnt+1;
             if(outcnt=16384) then 
             {
                 flush_outbuf()
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
	 //output("houxia888\n") and skip;
     header_bytes:=(int)outcnt;
	 //output("houxia8888\n") and skip;
     deflate(RValue);
	 //output("houxia88888\n") and skip;
     if(outcnt<16384-2) then 
     {
         outbuf[outcnt]:=(unsigned char)((crc & 65535) & 255);
         outcnt:=outcnt+1;
         outbuf[outcnt]:=(unsigned char)((unsigned int)(crc & 65535)>>8);
         outcnt:=outcnt+1
         
     }
     else
     {
         outbuf[outcnt]:=(unsigned char)((unsigned char)((crc & 65535) & 255));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         };
         outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)(crc & 65535)>>8));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         }
     };
	 //output("houxia999\n") and skip;
     if(outcnt<16384-2) then 
     {
         outbuf[outcnt]:=(unsigned char)((((unsigned int)crc)>>16) & 255);
         outcnt:=outcnt+1;
         outbuf[outcnt]:=(unsigned char)((unsigned int)(((unsigned int)crc)>>16)>>8);
         outcnt:=outcnt+1
         
     }
     else
     {
         outbuf[outcnt]:=(unsigned char)((unsigned char)((((unsigned int)crc)>>16) & 255));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         };
         outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)(((unsigned int)crc)>>16)>>8));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         }
     };
     if(outcnt<16384-2) then 
     {
         outbuf[outcnt]:=(unsigned char)((bytes_in & 65535) & 255);
         outcnt:=outcnt+1;
         outbuf[outcnt]:=(unsigned char)((unsigned int)(bytes_in & 65535)>>8);
         outcnt:=outcnt+1
         
     }
     else
     {
         outbuf[outcnt]:=(unsigned char)((unsigned char)((bytes_in & 65535) & 255));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         };
         outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)(bytes_in & 65535)>>8));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         }
     };
	 //output("houxia101010\n") and skip;
     if(outcnt<16384-2) then 
     {
         outbuf[outcnt]:=(unsigned char)((((unsigned int)bytes_in)>>16) & 255);
         outcnt:=outcnt+1;
         outbuf[outcnt]:=(unsigned char)((unsigned int)(((unsigned int)bytes_in)>>16)>>8);
         outcnt:=outcnt+1
         
     }
     else
     {
         outbuf[outcnt]:=(unsigned char)((unsigned char)((((unsigned int)bytes_in)>>16) & 255));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         };
         outbuf[outcnt]:=(unsigned char)((unsigned char)((unsigned int)(((unsigned int)bytes_in)>>16)>>8));
         outcnt:=outcnt+1;
         if(outcnt=16384) then 
         {
             flush_outbuf()
         }
         else 
         {
              skip 
         }
     };
     header_bytes:=header_bytes+2*4;
     flush_outbuf();
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function file_read ( char *buf,int size,int RValue )
 {
     frame(file_read_len$,return) and (
     int return<==0 and skip;
     int file_read_len$ and skip;
     file_read_len$:=spec_read(ifd,buf,size,RValue);
     if(file_read_len$=(int)(-1) OR file_read_len$=0) then 
     {
         return<==1 and RValue:=file_read_len$;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         bytes_in:=bytes_in+file_read_len$;
         return<==1 and RValue:=file_read_len$;
         skip
     }
     else
     {
         skip
     }
     )
 };
  frame(argv,argc,count$,str$) and ( 
 char *argv[1] and skip;
 main(1,argv,RValue)
 )
 )
