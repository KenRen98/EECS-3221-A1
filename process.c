#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* 
Family Name: Ren
Given Name: Dexuan
Student Number: 215751332
CS Login: kenren98
YorkU email address: ken.ren98@gmail.com
*/
#define MAXARGU_SIZE 40

int main(int argc, char **argv)
{
    int k=0,i=0;
    int status;
    char x[MAXARGU_SIZE];
    //this is for easy way
    //char x[MAXARGU_SIZE*argc];
    char a[MAXARGU_SIZE];
    int fd[2];
    pipe(fd);
    //printf("number = %d\n",argc);
    if (argc<2)
    {
        return 0;
    }
    
    for(i=1;i<argc;i++){
        if(fork()==0){
            //printf("Child pid=%d\n",getpid());
            close(fd[0]);
            double s,temp=0.0;
            int count=0;
            FILE *file;
            file = fopen(argv[i], "r");
            //printf("!!!Handle file %s\n",argv[i]);
            while(!feof(file)){
                //printf("--Scaning\n");
                fscanf(file,"%lf ",&temp);
                s+=temp;
                count++;
                //printf("++Counting:%d\n",count);
            }
            //printf("Child PID=%d of Parent PID=%d, finished handle file %s with sum=%lf and count=%d.\n",getpid(),getppid(),argv[i],s,count);
            sprintf(a,"%lf %d %s",s,count,argv[i]);
            //printf("%s + %s",a,argv[i]);
            fclose(file);
            write(fd[1], a, (sizeof(a)));
            close(fd[1]);
            exit(0);
        }
        //else{
            //printf("Total: %d\n",argc);
        //}
    } 
        close(fd[1]);
        int countsum=0,tempcount=0;
        double tempsum=0.0,sum=0.0;
        char name[40];

        //the easy way:
        /*
        for (i = 1; i < argc ; i++){
            wait(NULL);
        }
        int scaning=0;
        char* ptc=x;
        read(fd[0],x,sizeof(x));
        for (i = 1; i < argc ; i++){
            //printf("\nParent PID=%d, and now Waiting.\n", getpid());
            //wait(&status);
            //printf("Child Exit Code = %d\n\n",status);
            scaning+=MAXARGU_SIZE;
            sscanf(ptc,"%lf %d %s\0",&tempsum,&tempcount,name);
            ptc=&x[scaning];
            printf("%s SUM=%lf NUM=%d AVG=%lf\n",name,tempsum,tempcount,tempsum/tempcount);
            sum+=tempsum;
            countsum+=tempcount;
        }
        */

        //the hard way:
        for (i = 1; i < argc ; i++){
            wait(NULL);
            read(fd[0],x,sizeof(x));
            sscanf(x,"%lf %d %s\0",&tempsum,&tempcount,name);
            printf("%s SUM=%lf NUM=%d AVG=%lf\n",name,tempsum,tempcount,tempsum/tempcount);
            sum+=tempsum;
            countsum+=tempcount;
            //printf("%lf and %d\n",sum,countsum);
        }

        printf("AVERAGE=%lf\n",sum/countsum);
    return 0;
}