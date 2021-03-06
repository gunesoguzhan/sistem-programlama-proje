#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include "jrb.h"
#include "jval.h"

#define MAX 505
#define MAXLINE 505

typedef struct partInfo {
    char kelime[19];
    char huffmankodu[15];
} Part;

//check file standard and exit if its out of homework requirements
static int foo(int foo) {
    FILE *fp;
    int count = 0;
    char c;  // To store a character read from file
    fp = fopen(".kilit", "r");
    if (fp == NULL) {
        printf(".Kilit Dosyasi Mevcut Degil");
        return 0;
   }
    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            count = count + 1;
        }
    }
    // Close the file
    fclose(fp);
    if (count > MAXLINE) {
        return 0;
    } else {
        return count;
    }
}

void welcome(){printf("├             _            _\n├            | |          | |\n├            | | ___   ___| | __\n├            | |/ _ \\ / __| |/ /\n├            | | (_) | (__|   <\n├            |_|\\___/ \\___|_|\\_\\\n");}

void beginEncryption(){printf("├░██████╗██╗███████╗██████╗░███████╗██╗░░░░░███████╗███╗░░██╗██╗██╗░░░██╗░█████╗░██████╗░\n├██╔════╝██║██╔════╝██╔══██╗██╔════╝██║░░░░░██╔════╝████╗░██║██║╚██╗░██╔╝██╔══██╗██╔══██╗\n├╚█████╗░██║█████╗░░██████╔╝█████╗░░██║░░░░░█████╗░░██╔██╗██║██║░╚████╔╝░██║░░██║██████╔╝\n├░╚═══██╗██║██╔══╝░░██╔══██╗██╔══╝░░██║░░░░░██╔══╝░░██║╚████║██║░░╚██╔╝░░██║░░██║██╔══██╗\n├██████╔╝██║██║░░░░░██║░░██║███████╗███████╗███████╗██║░╚███║██║░░░██║░░░╚█████╔╝██║░░██║\n├╚═════╝░╚═╝╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝╚═╝░░╚══╝╚═╝░░░╚═╝░░░░╚════╝░╚═╝░░╚═╝\n");}
void beginDecryption(){printf("├░██████╗██╗███████╗██████╗░███████╗  ░█████╗░░█████╗░██╗██╗░░░░░██╗██╗░░░██╗░█████╗░██████╗░\n├██╔════╝██║██╔════╝██╔══██╗██╔════╝  ██╔══██╗██╔══██╗██║██║░░░░░██║╚██╗░██╔╝██╔══██╗██╔══██╗\n├╚█████╗░██║█████╗░░██████╔╝█████╗░░  ███████║██║░░╚═╝██║██║░░░░░██║░╚████╔╝░██║░░██║██████╔╝\n├░╚═══██╗██║██╔══╝░░██╔══██╗██╔══╝░░  ██╔══██║██║░░██╗██║██║░░░░░██║░░╚██╔╝░░██║░░██║██╔══██╗\n├██████╔╝██║██║░░░░░██║░░██║███████╗  ██║░░██║╚█████╔╝██║███████╗██║░░░██║░░░╚█████╔╝██║░░██║\n├╚═════╝░╚═╝╚═╝░░░░░╚═╝░░╚═╝╚══════╝  ╚═╝░░╚═╝░╚════╝░╚═╝╚══════╝╚═╝░░░╚═╝░░░░╚════╝░╚═╝░░╚═╝\n");}

int main(int argc, char **argv)
{
    if( argc > 4 ) {
       printf("├──Hatali Kullanim. Fazla Parametre Girildi──├\n├──────────────Doğru Kullanim────────────├ : \n├──>$kripto -d giriş_metin cikis_metin───├\n├                   ya  da               ├\n├──>$kripto -e giriş_metin cikis_metin───├\n");
    }
    else if( argc < 4 ) {
        printf("\n├──Hatali Kullanim. Eksik Parametre Girildi──├\n├──────────────Doğru Kullanim────────────├ : \n├──>$kripto -d giriş_metin cikis_metin───├\n├                   ya  da               ├\n├──>$kripto -e giriş_metin cikis_metin───├\n");
    }
    else if( argc == 4 ) {
        welcome();
        printf("├──────────Girdiğiniz parametreler :  \n├           ├──%s\n├           ├──%s\n├           ├──%s\n", argv[1],argv[2],argv[3]);
	     /*---------------------Begin Read .Kilit -----------------------*/
	IS is;
        int i;
        int res;
        int npart = 0;
        Part part[MAX];
        Part *p = &part[npart];
        int fop=foo(1);
        JRB t, tmp;
        t = make_jrb();
        is = new_inputstruct(".kilit");
        if (is == NULL) {
            exit(1);
        }
        /*compliant with JSON data interchange syntax*/
        while (get_line(is) >= 0) {
            Part *p = &part[npart];
            for (i = 0; i < is->NF; i++) {
                if (i == 0) {
                    res = sscanf(is->fields[i],
                        " \"%18[^\"]\": ", // RFC 8259 and ECMA-404 syntax
                        p->kelime);
                } else {
                    res = sscanf(is->fields[i],
                            " \"%14[^\"]\", ", // RFC 8259 and ECMA-404 syntax
                            p->huffmankodu);
                }
            }
            if (strcmp(argv[1], "-e") == 0) {
                jrb_insert_str(t, p->kelime, new_jval_v((void *) p));
            } else {
                jrb_insert_str(t, p->huffmankodu, new_jval_v((void *) p));
            }        
            npart++;
            if (npart == MAX) {
                break; //break if it overflows due to project restrictions
            }
        }
        jettison_inputstruct(is);
	     /*---------------------End Read .Kilit -----------------------*/   
             /*---------------------Begin Encryption -----------------------*/
        if(strcmp(argv[1], "-e") == 0){
            beginEncryption();
            IS isG;
            int iG;
            isG = new_inputstruct(argv[2]);
            if (isG == NULL) {
                exit(1);
            }
            FILE *zet;
            zet = fopen(argv[3], "w"); // "w" defines "writing mode"
            fprintf(zet,"");
            fclose(zet);
            while(get_line(isG) >= 0) {
                for (iG = 0; iG < isG->NF; iG++) {
                    //printf("%s\n",isG->fields[iG]);
                    tmp = jrb_find_str(t, isG->fields[iG]);
                    p = (Part *) tmp->val.v;
                    printf("%1s ",p->huffmankodu);
                    FILE *ppf;
                    ppf = fopen(argv[3], "a");
                    fprintf(ppf," ");
                    fprintf(ppf, p->huffmankodu);
                    fclose(ppf);
                }
            }
            jettison_inputstruct(isG);
        }
             /*---------------------End Encryption -----------------------*/
            /*---------------------Begin Decription -----------------------*/
         else if(strcmp(argv[1], "-d") == 0){
            beginDecryption();
            IS isc;
            int ic;
            isc = new_inputstruct(argv[2]);
            if (isc == NULL) {
                exit(1);
            }
            while(get_line(isc) >= 0) {
                for (ic = 0; ic < isc->NF; ic++) {
                    // printf("%d: %s\n", isc->line, isc->fields[ic]);
                    tmp = jrb_find_str(t, isc->fields[ic]);
                    p = (Part *) tmp->val.v;
                    printf("%-1s ", p->kelime);
                    if(ic==0){
                        FILE *fptr;
                        fptr = fopen(argv[3], "w");
                        fprintf(fptr, p->kelime);
                        fclose(fptr);
                    }else{
                        FILE *fptra;
                        fptra = fopen(argv[3], "a");
                        fprintf(fptra," ");
                        fprintf(fptra, p->kelime);
                        fclose(fptra);
                    }
                }
            }
            jettison_inputstruct(isc);
         }
            /*---------------------End Decription -----------------------*/
         else{printf("├───────────────────HATA -e ya da -d girilmeli───────────────────├\n");}
     }
    return 0;
}
