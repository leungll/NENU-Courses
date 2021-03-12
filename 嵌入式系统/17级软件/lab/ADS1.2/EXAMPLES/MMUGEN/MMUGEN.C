/*----------------------------------------------------------------------------

        MMU table generator
        
        [PJM] 1st August 2000
        
        Copyright Peter Maloy, CodeSprite August 2000    www.codesprite.com

----------------------------------------------------------------------------*/

//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//---------------------------------------------------------------------------


enum  validwords {
        BASE_ADDRESS,
        LEVEL           ,
        VIRTUAL         ,
        TO                      ,
        PHYSICAL        ,
        PAGES           ,
        SECTION         ,
        NO_ACCESS       ,
        SVC_READWRITE,
        NO_USR_WRITE,
        FULL_ACCESS     ,
        FAULT           ,
        CACHEABLE       ,
        AND                     ,
        BUFFERABLE      ,
        NOT                     ,
        LARGEPAGES      ,
        SMALLPAGES      ,
        POSTPROCESS ,
        UNRECOGNISED
};

typedef struct
{
        unsigned long v_base;   /* first address in virtual section                     */
        unsigned long v_end;            /* last address in virtual section                      */
        unsigned long p_base;   /* corresponding physical base address          */
        unsigned long entrytype; /* 'P' for pages, 'S' for section                      */
        unsigned long access;   /* access types defined in the enum above       */
        unsigned long cb;               /* cacheable & bufferable status                        */
}mmudata;

typedef struct
{
        long index;
        char *word;
}tparsedata;

struct {
    FILE *rulefile ;
    FILE *outfile ;
    mmudata rule ;
    unsigned long base_address ;
    unsigned long table_entry ;
    long state ;
    long pagescount ;
} global ;


tparsedata parsedata[] = {
        {BASE_ADDRESS   ,"BASE_ADDRESS" },
        {LEVEL                  ,"LEVEL"                },
        {VIRTUAL                ,"VIRTUAL"              },
        {TO                             ,"TO"                   },
        {PHYSICAL               ,"PHYSICAL"             },
        {PAGES                  ,"PAGES"                },
        {SECTION                ,"SECTION"              },
        {NO_ACCESS              ,"NO_ACCESS"    },
        {SVC_READWRITE  ,"SVC_READWRITE"},
        {NO_USR_WRITE   ,"NO_USR_WRITE" },
        {FULL_ACCESS    ,"FULL_ACCESS"  },
        {FAULT                  ,"FAULT"                },
        {CACHEABLE              ,"CACHEABLE"    },
        {AND                    ,"AND"                  },
        {BUFFERABLE             ,"BUFFERABLE"   },
        {NOT                    ,"NOT"                  },
        {LARGEPAGES             ,"LARGEPAGES"   },
        {SMALLPAGES             ,"SMALLPAGES"   },
        {POSTPROCESS    ,"POSTPROCESS"  },
        {UNRECOGNISED   ,"UNRECOGNISED" }
};


//--function prototypes------------------------------------------------------
int  ValidateArgs (int argc, char **argv);
int  ParseRule (void);
int  WriteTableEntries (void);
int  WriteLevel1(void);
int  WriteLevel2(void);
int      GetWord (char *buffer);
int      GetWordIndex (char *buffer);
long atox( char *buffer);
int      stricomp( char *original, char *match );

//--MAIN---------------------------------------------------------------------


int main(int argc, char **argv)
{
        if( ValidateArgs(argc, argv)) return -1;

    global.state=0;

        while( ParseRule() )
        {
                if(WriteTableEntries()==-1)
                {
                        fclose( global.outfile );
                        fclose( global.rulefile );
                        exit(-1);
                }
        }

        printf("MMU table generation complete\n");
        
        fclose( global.outfile );
        fclose( global.rulefile );
        return 0 ;
}



//--VALIDATEARGS-------------------------------------------------------------

int ValidateArgs(int argc, char **argv)
{
        printf("\nMMUgen\n");
    printf("======\n");

        if(argc!=3)
    {
        printf("Usage: MMUgen Rulefile Outputfile\n");
        return -1;
    }

    if(NULL==(global.rulefile=fopen(argv[1],"r")))
    {
        printf("Couldn't open Rule file\n");
        return -1;
    }

    if(NULL==(global.outfile=fopen(argv[2],"wb")))
    {
                fclose(global.rulefile);
        printf("Couldn't open Output file\n");
        return -1;
    }
        fseek(global.outfile, 0L, SEEK_SET);

        
    return 0;
}


//--PARSERULE----------------------------------------------------------------

int ParseRule (void)
{
        char buffer[20];
        static int       notted = 0;
    long i;

        while(GetWord(buffer))
        {
                switch( GetWordIndex(buffer) )
                {
                        case BASE_ADDRESS:
                        GetWord(buffer);
                                        global.base_address = atox(buffer);
                                        break;

                        case LEVEL               :
                        GetWord(buffer);
                                        global.state = atoi(buffer);
                                        /* check table_entry is a sensible value */
                                        if(global.table_entry != 0 && global.table_entry != 0x1000)
                                        {
                                                printf("Table data error - at end of Level 1, the table was %08lx bytes long (should be 0x4000)\n",global.table_entry<<2);
                                        }
                                        break;

                        case VIRTUAL     :
                        GetWord(buffer);
                                        global.rule.v_base =  atox(buffer);
                                        break;

                        case TO                  :
                        GetWord(buffer);
                                        global.rule.v_end =  atox(buffer);
                                        break;

                        case PHYSICAL    :
                        GetWord(buffer) ;
                                        global.rule.p_base =  atox(buffer);
                                        break;

                        case PAGES               :
                                        global.rule.entrytype = 'P';
                                        global.rule.access = 0 ;
                                        global.rule.cb = 0 ;
                                        //completed rule, so implement it
                                        return 1 ;

                        case SECTION     :
                                        global.rule.entrytype = 'S';
                                        break ;

                        case NO_ACCESS   :
                                        global.rule.access = 0 ;
                                        break ;

                        case SVC_READWRITE:
                                        global.rule.access = 1 ;
                                        break ;

                        case NO_USR_WRITE:
                                        global.rule.access = 2 ;
                                        break ;

                        case FULL_ACCESS :
                                        global.rule.access = 3 ;
                                        break ;

                        case FAULT               :
                                        global.rule.entrytype = 'F';
                                        global.rule.access = 0 ;
                                        global.rule.cb = 0 ;
                                        //completed rule, so implement it
                                        return 1 ;

                        case CACHEABLE   :
                                        if(notted)
                                        {
                                                global.rule.cb &= 1;
                                                notted = 0;
                                        }
                                        else
                                        {
                                                global.rule.cb |= 2 ;
                                        }
                                        break ;

                        case AND                 :
                                        /* ignore */ break;

                        case BUFFERABLE  :
                                        if(notted)
                                        {
                                                global.rule.cb &= 2;
                                                notted=0;
                                        }
                                        else
                                        {
                                                global.rule.cb |= 1 ;
                                        }
                                        //completed rule, so implement it
                                        return 1 ;

                        case NOT                 :
                                        notted=1;
                                        break;

                        case LARGEPAGES  :
                                        global.rule.entrytype = 'L';
                                        break ;

                        case SMALLPAGES  :
                                        global.rule.entrytype = 'S';
                                        break ;

            case POSTPROCESS :
                                        GetWord(buffer); //skip ENTRY
                    GetWord(buffer); //get address
                    fseek( global.outfile, atox(buffer) ,SEEK_SET );
                                        GetWord(buffer); //skip EQUALS
                                        GetWord(buffer); //get value
                    i = atox(buffer);
                    fwrite( &i, 4, 1, global.outfile );
                    break ;

                        case UNRECOGNISED:
                                        printf("Unrecognised word '%s'\n",buffer);
                }
        }

        // must have hit end of rule file without finding the end of a rule
        return 0;

}


//--WRITETABLEENTRIES--------------------------------------------------------

int WriteTableEntries (void)
{
        switch( global.state )
        {
                case 1: return WriteLevel1();
                case 2: return WriteLevel2();
                default: printf("MMU page table level not set\n");
                                 return -1;
        }
}

//--WRITELEVEL1--------------------------------------------------------------

int WriteLevel1(void)
{
        unsigned long fields ;
        unsigned long physical ;
    unsigned long writevalue ;
        unsigned long i ;

        /* Check the table-entry number matches the virtual base address for this section */
        if( global.table_entry != (global.rule.v_base>>20) )
        {
                printf("MMU Table synchronisation error!\n  table_entry = %08lx, v_base = %08lx\n",
                                global.table_entry, global.rule.v_base);
                return -1 ;
        }

        if (global.rule.entrytype == 'S' || global.rule.entrytype == 'F')
        {
                if(global.rule.entrytype == 'S')
                {
                        fields = 0x12 | (global.rule.access<<10) | (global.rule.cb<<2) ;
                }
                else
                {
                        fields = 0; //generate fault on access
                }
                physical = global.rule.p_base ;

                /* generate all the SECTION entries for this descriptor */
                for (i = global.rule.v_base; i<global.rule.v_end; )
                {
            writevalue = physical|fields ;
                        fwrite( &writevalue, 4, 1, global.outfile );
                        global.table_entry++ ;
                        physical += 0x100000 ;

                        /* check for memory wrap-round */
                        i+=0x100000 ;
                        if (i==0x00000000) break;
                }

        }
        else
        {
                /* Single PAGE entry */
        writevalue = 0x11 + global.base_address + 0x4000 + 0x400*global.pagescount++ ;
                fwrite( &writevalue, 4, 1, global.outfile );

                global.table_entry++ ;
        }

        return 0 ;

}


//--WRITELEVEL2--------------------------------------------------------------

int WriteLevel2(void)
{
        unsigned long fields ;
        unsigned long physical ;
    unsigned long writevalue ;
        unsigned long i ;
        
        /* work out repeated data fields - note: this line would change if per-page access levels were to be supported*/
        fields = (global.rule.access << 10)|(global.rule.access << 8)|(global.rule.access << 6)|(global.rule.access << 4)|(global.rule.cb <<2);

        if (global.rule.entrytype == 'L')
        {
                fields |= 1 ;
        }
        else
        {
                fields |= 2 ;
        }

        /* create entries for this descriptor */
        i = global.rule.v_base ;
        physical = global.rule.p_base ;

        while(i<global.rule.v_end)
        {
                if( global.rule.entrytype == 'L' )
                {
                        int j ;
            writevalue = physical|fields ;

                        for( j=16; j; j-- )
                        {
                                fwrite( &writevalue, 4, 1, global.outfile );
                        }
                        physical += 0x10000;
                        i += 0x10000;
                }
                else
                {
            writevalue = physical|fields ;
                        fwrite( &writevalue, 4, 1, global.outfile );
                        physical += 0x1000;
                        i += 0x1000;
                }

        }

    return 0 ;

}


//--GETWORD------------------------------------------------------------------
// fetch next word, stepping over whitespace and comments
// return 0 if end-of-file

int      GetWord (char *buffer)
{
        int c=fgetc(global.rulefile);

        while(c=='\t' || c==' ' || c=='/' || c==0xd || c==0xa)
        {
                if( c=='/') //start of comment
                {
                        do
                        {
                                c=fgetc(global.rulefile);
                        } while( c!= '/' ) ;

                        // get next character beyond comment
                        c=fgetc(global.rulefile);
                }

                while( c=='\t' || c==' ' || c==0xd || c==0xa ) c=fgetc(global.rulefile);
        }

    // Check for end of file
        if( c==EOF ) return 0;

        // Ok, should be at the start of a word
        while ( c!='\t' && c!=' ' && c!=0xd && c!=0xa && c!=EOF)
        {
                *buffer++ = (char)c ;
                c=fgetc(global.rulefile);
        }

        //terminate word
        *buffer = '\0';
        
        return 1;
}

//--GETWORDINDEX-------------------------------------------------------------

int      GetWordIndex (char *buffer)
{
    int index=0 ;
    
        while ( parsedata[index].index != UNRECOGNISED
                && stricomp(parsedata[index].word,buffer) )
        {
                index++ ;
        }
        
        return index ;
}

//--ATOX---------------------------------------------------------------------

long atox( char *buffer)
{
        long v=0;
        
        while(*buffer)
        {
                v*=16;
                if(*buffer>='0' && *buffer<='9') v+= *buffer - '0';
                if(*buffer>='a' && *buffer<='f') v+= *buffer - 'a'+10;
                if(*buffer>='A' && *buffer<='F') v+= *buffer - 'A'+10;
                buffer++;
        }
        return v ;
}

//--STRICOMP-----------------------------------------------------------------
/*
        The program originally used stricmp, but this does
        not appear to be included in the ARM C library.
        
        This is not a true stricmp (or strcmpi), since only
        the "match" string is converted to upper case,
        allowing "original" to be in read-only memory.
*/
int      stricomp( char *original, char *match )
{
        char *ptr = match ;

        while(*ptr)
        {
                *ptr=toupper(*ptr) ;
                ptr++ ;
        }
        
        return strcmp(original,match) ;
}
