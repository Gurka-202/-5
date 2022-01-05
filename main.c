#include <stdio.h>
#include <stdlib.h>

int main()
{

    float a,b,x,put_bin,step, delta;
    int ch, N;
    float **tabl=NULL, **tablBin = NULL;
    FILE *dat,*pim2,*fileBin;
    dat=fopen("dat.txt","r");
    pim2=fopen("pim2.txt","w");
    fileBin=fopen("fileBin.bin","w+b");

    while(ch = getc(dat)!= '\n');
    putchar(ch);
    fscanf(dat," %f %f %d %f",&a,&b,&N,&step);
    delta=(b-a)/(N-1);
    if (N==0)
        {
                    printf("O_o Mission complete. Have a nice day!");
            getch();
            exit(0);

        }
    tabl=(int**)calloc(N,sizeof(int));
    tablBin=(int**)calloc(N,sizeof(int));
    for (int i=0;i<N;i++)
        {
        tabl[i]=(int*)calloc(1,sizeof(int));
        tablBin[i]=(int*)calloc(1,sizeof(int));
        }
    printf("Function: sqrt(x)+2\n Start: %.1f\n End: %.1f\n Number: %d\n Delta: %.1f\n\n", a, b, N, delta);
    for (int i = 0; i<N; i++) {
        a+=delta;
        x=a;
            tabl[i][0]=i+1;
            tabl[i][1]=x-delta;
            tabl[i][2]=sqrt(tabl[i][1])+2;
    }



    fprintf(pim2,"    N  \tx   f(x)\n");
    for (int i=0;i<N;i++)
        {
        fprintf(pim2,"  %5.0f",tabl[i][0]);
        for (int j=1;j<3;j++)
            {
            fprintf(pim2,"  %5.1f",tabl[i][j]);
            }
        fprintf(pim2,"\n");
        }
    fwrite(&N,sizeof(int),1,fileBin);
    for (int i=0;i<N;i++)
        {
        for (int j=1;j<3;j++)
            {
            fwrite(&tabl[i][j],sizeof(float),1,fileBin);
            }
        }
        fclose(fileBin);
        fileBin=fopen("fileBin.bin","r+b");
    printf(" ---------------------\n | N |   x   |  f(x) |\n ---------------------\n");
    fread(&N,sizeof(int),1,fileBin);
    printf("\n%d\n\n",N);
    for (int i=0;i<N;i++)
    {
        int k=i+1;
        printf("%d",k);
        for (int j=1;j<3;j++)
        {
            fread(&put_bin,sizeof(float),1,fileBin);
            printf("   |%5.1f|",put_bin);
        }
        printf("\n");
    }
    printf("------------------------");
    fclose(dat);
    fclose(fileBin);
    fclose(pim2);
    return 0;
}
