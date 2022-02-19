#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
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
struct answer{
    char name[20];
    double sum;
    int count;
};

void* calculator(void* argument){
    struct answer* local= (struct answer*) argument;
    FILE *file;
    double temp=0.0;
    //printf("!!!Handle file %s\n",local->name);
    file = fopen((local->name), "r");
    local->sum=0.0;
    local->count=0;
    while(!feof(file)){
        //printf("--Scaning\n");
        fscanf(file,"%lf ",&temp);
        local->sum+=temp;
        local->count++;
    }
    //printf("finished handle file %s with sum=%lf and count=%d.\n",local->name,local->sum,local->count);
    fclose(file);
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    int k=0,i=0;
    int rc;
    int countsum=0;
    int num_argc=argc-1;
    double sum;
    pthread_t  thread_id[num_argc];
    struct answer whole[num_argc];
    for(i=0;i<argc-1;i++){
        strcpy(whole[i].name,argv[i+1]);
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        rc = pthread_create(&thread_id[i], NULL, calculator, &whole[i]);
        if(rc)			/* could not create thread */
        {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
        }
    }
    //printf("Something");
    for(i=0;i<argc-1;i++){
        //printf("Something");
        pthread_join(thread_id[i],NULL);
    }
    for(i=0;i<argc-1;i++){
        printf("%s SUM=%lf NUM=%d AVG=%lf\n",whole[i].name,whole[i].sum,whole[i].count,whole[i].sum/whole[i].count);
        sum+=(whole[i].sum);
        countsum+=(whole[i].count);
    }
    printf("AVERAGE=%lf\n",sum/countsum);
    return 0;
}


