#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define TIMEOUT 3
#define TOTAL_PACKETS 5
int stimualte_acknowledgement(){
    return rand()%10< 7;
}
int main()
{
    srand(time(0));
    int packet=1;
    int ack_recieved;
    while(packet<=TOTAL_PACKETS){
        printf("\nSender : Sending packets :%d\n",packet);
        sleep(1);
        ack_recieved = stimualte_acknowledgement();
        if(ack_recieved){
            printf("\nReciever:Acknowledgement for packet %d recieved\n",packet);
            packet++;
        }
        else{
            printf("\nReciever:Acknowlegment for packet %d lost!Retransmitting\n",packet);
            sleep(TIMEOUT);
        }
       
    }
    printf("\nAll packets have been sent\n");
    return 0;
}