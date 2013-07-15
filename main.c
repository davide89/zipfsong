#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define FAILURE 1
#define SUCCESS 0

#define FMAX 2000000000000



typedef struct song_s{
    long double freq;
    char *name;
    long double z;
    long double q;
    long double w;
}song_t;


int loadFileAndCompute(long int,long int,FILE*);
void quicksort (song_t *A, long int p, long int r );
long int partitionB(song_t *A,long int p,long int r );


int main(int argc,char *argv[]){
    long double n,m;

    FILE *fp;

    //fp=fopen(argv[1],"r");
    fp=stdin;

    //read parameters
    fscanf(fp,"%Lg %Lg",&n,&m);
    if(n<1 || n>50000|| m<1 || m>n ){
        return(FAILURE);
    }

    loadFileAndCompute(n,m,fp);


return(SUCCESS);
}




int loadFileAndCompute(long int n,long  int m,FILE *fp){
    song_t *tmp;
    long int i;
    long double f;
    char name[32];
    long double fReference;

    //ALLOCATIONS
    tmp=(song_t*)malloc(n*sizeof(song_t));
    if(!tmp){
        exit(FAILURE);
    }


    //READING AND COMPUTE
    for(i=0;i<n;i++){
        fscanf(fp,"%Lg %s",&f,name);

        if(f<0 || f>FMAX){
            exit(FAILURE);
        }


        tmp[i].freq=f;
        tmp[i].name=(char*)malloc((strlen(name)+1)*sizeof(char));
        if(!tmp[i].name){
             exit(FAILURE);
        }

        if(strlen(name)>30 || strlen(name)<1){
            exit(FAILURE);
        }
        strcpy(tmp[i].name,name);

        //check on name
        int k=strlen(tmp[i].name);
        int j;

        for(j=0;j<k;j++){
            if(tmp[i].name[j]<'a' || tmp[i].name[j]>'z'){
                if(tmp[i].name[j]<'0' || tmp[i].name[j]>'9'){
                    if(tmp[i].name[j]!='_'){
                        exit(FAILURE);
                    }
                }
            }
        }


        if(i==0){

            if(tmp[0].freq==0){
                //tmp[0].freq=1;
                exit(FAILURE);
            }
            tmp[0].z=1;
            tmp[0].q=1;
            tmp[0].w=0;
            fReference=tmp[0].freq;
        }
        else{
            tmp[i].z=(long double)(fReference/(i+1));
            tmp[i].q=(long double)(tmp[i].freq/tmp[i].z);
            tmp[i].w=i;
        }
    }


    quicksort(tmp,0,n-1);



    //PRINT
    for(i=0;i<m-1;i++){
        printf("%s\n",tmp[i].name);
    }
    printf("%s",tmp[m-1].name);


    //FREE MEMORY
    for(i=0;i<n;i++){
        free(tmp[i].name);
    }
    free(tmp);

return(SUCCESS);
}




void quicksort (song_t *A, long int p, long int r )
{
    long int q;

    if (p < r)
    {
        q = partitionB(A, p, r);
        quicksort(A, p, q);
        quicksort(A, q+1, r);
    }
return;
}


long int partitionB(song_t *A,long int p,long int r )
{
    long int i, j;
    song_t temp,x;
    x = A[p];
    i=p-1;
    j=r+1;
    while (i < j)
    {

        while(A[--j].q < x.q || (A[j].q == x.q && A[j].w > x.w ));
        while(A[++i].q > x.q || (A[i].q == x.q && A[i].w < x.w ));

        if (i < j)
        {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
return(j);
}
