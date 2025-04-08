#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10
#define LOSS_PROBABILITY 20

int send_frame(int frame_number){
    printf("Sending frame :%d\n",frame_number);
    sleep(1);
    int rand_value = rand()%100;
    if(rand_value < LOSS_PROBABILITY){
        printf("Frame %d lost during transmission\n",frame_number);
        return 0;
    }
    printf("Frame %d sent sucessfully\n",frame_number);
    return 1;
}
int receive_ack(int frame_number){
    printf("Recieving Ack for frame %d \n",frame_number);
    sleep(1);
    int rand_value= rand()%100;
    if(rand_value< LOSS_PROBABILITY){
        printf("Ack of frame %d lost during transmission\n",frame_number);
        return 0;
    }
    printf("Ack of frame %d received\n",frame_number);
    return 1;
}
void selective_repeat_arq(){
    int base =0;
    int ack_received[TOTAL_FRAMES]={0};
    int frame_sent[TOTAL_FRAMES]={0};
    while(base<TOTAL_FRAMES){
        for(int i=base;i<base+WINDOW_SIZE && i<TOTAL_FRAMES;i++){
            if(!frame_sent[i]){
                frame_sent[i]=send_frame(i);
            }
        }
        for(int i=base;i<base+WINDOW_SIZE && i<TOTAL_FRAMES;i++){
            if(frame_sent[i] && !ack_received[i]){
                ack_received[i]=receive_ack(i);
            }
        }
        while(base<TOTAL_FRAMES && ack_received[base]){
            printf("Slinding window forward frames %d, fully acknowledgede\n",base);
            base++;
        }
    }
    printf("All farmes sent and ack received\n");
}
int main(){
    srand(time(0));
    selective_repeat_arq();
    return 0;
}
