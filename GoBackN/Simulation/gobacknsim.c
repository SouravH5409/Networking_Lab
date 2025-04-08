#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4

int simulate_acknowledgement(){
	return rand()%10<7;
}
int main(){
	int base =1;
	int next_seq_num=1;
	while(base<=TOTAL_PACKETS){
		printf("/n------------SENDING WINDOW ------------\n");
		while(next_seq_num<base+WINDOW_SIZE && next_seq_num <= TOTAL_PACKETS){
			printf("Sender : sending packet %d\n",next_seq_num);
			next_seq_num++;
		}
		sleep(1);
		printf("\n -----------WAITING FOR ACKNOWLEDGEMENT------------\n");
		for(int i=base;i<next_seq_num;i++){
			if(simulate_acknowledgement()){
				printf("Acknowledgement for packet %d recieved \n",i);
				
			}else{
				printf("Acknowledgement for packet %d lost\n",i);
				printf("Retransmitting from packet %d\n",i);
				next_seq_num = i;
				break;
			}
		}
		base = next_seq_num;
		sleep(1);
		
	}
	
return 0;
}
