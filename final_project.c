#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define u_sinir 30			////horizontal border of plane
#define sehrin_siniri 19	//explosion point of the bomb. 

int b_high = 0;//bombanýn yüksekligi icin
int u_konum=0;		//ucagin yataydaki konumu
int high = 1;		//this variable used for controlling bomb to fall down.
int b_yatay = 0;	//horizontal distance of the bomb
int count_true =0;		//number of true input of word
int count_wrong = 0;	//number of false input of word
int control_game;		//to control menu
int skor_loc = 40; 			//defines location of skor table
char kelime[20];		//word near the bomb
int speed_of_game = 500;	//used in Sleep function to define speed of game
int speed_flag =0;			//in every 5 true typed word, speed flag will increase 1 time.
int word_4=0 ,word_5=0 ,word_6=0 ,word_7=0 ,word_8=0 ,word_9=0 ,word_10=0;
//those variables are indicating the beginning index of the words which have 4 letters,5 letters etc..


int findWordNum(){
	FILE *f;
	f = fopen("codewords.txt","r");
	char kelimeHolder[20] ={0};
	int j = 0;
	for(j; ; j++){
		fscanf(f, "%s", kelime);
		if(strcmp(kelime, kelimeHolder) == 0){
			break;
		}
		sprintf(kelimeHolder, kelime);
	}
	fclose(f);
	return j;
}

int find_word_length(int wordNum){
	int letter_increment_flag =3;
	
	FILE *word_list;
	word_list = fopen("codewords.txt","r");
	int r;
	for(r = 1; r < wordNum; r++){
		fscanf(word_list, "%s", kelime);
		int y;
		for(y=0; kelime[y] != NULL; y++);		//ý am finding the length of word
		
		if(letter_increment_flag == y-1){	//if length of words increases y becomes.. 
											//1 higher than letter_increment_flag
			switch(y){						
			
			case 4 :word_4 = r;		break;	//beginning index of words with 4 letter
			case 5 :word_5 = r;		break;	//beginning index of words with 5 letter
			case 6 :word_6 = r;		break;	//beginning index of words with 6 letter
			case 7 :word_7 = r;		break;	//					.
			case 8 :word_8 = r;		break;	//					.
			case 9 :word_9 = r;		break;	//					.
			case 10 :word_10 = r;	break;	//					.
			default: NULL; break;
			}
			
		}
		letter_increment_flag = y;
		
	}
	fclose(word_list);
}
						/////////GET WORD FUNCTÝON/////////


int get_word(int s_flag, int wordNum){
		
	FILE *word_list;
	word_list = fopen("codewords.txt","r");
	int p;
	if(s_flag < 5){
		p = rand()%word_4;		//producing an integer from zero till beginning of words with 4 letter
		
	}else if(s_flag < 10){		//producing an integer from zero till beginning of words with 5 letter
		p = rand()%(word_5- word_4)+ word_4 ;
		
	}else if(s_flag < 15){		//producing an integer from zero till beginning of words with 6 letter
		p = rand()%(word_6- word_5) + word_5 ;					//	.
																//	.
	}else if(s_flag < 20){										//	.
		p = rand()%(word_7- word_6) + word_6;
		
	}else if(s_flag < 25){
		p = rand()%(word_8- word_7) + word_7 ;
	
	}else if(s_flag < 30){
		p = rand()%(word_9- word_8) + word_8 ;
	}
	else if(s_flag < 35){
		p = rand()%(word_10- word_9) + word_9;
	}else{
		p = rand()%(wordNum-word_10) + word_10;
	}
		 
	int r;
	for(r=0;r < p;r++){		//finding the word according to the index of word in the "codewords.txt" file
		fscanf(word_list, "%s", kelime);
	}
	fclose(word_list);
	
}

						////////////END OF GET WORD//////////////

typedef struct oyun_data{		//data in this struct will bi saved to a txt file
	
	int b_x;	
	int b_y;
	int u_x;
	int seh_sin;	
	int high_;		
	int num_true;
	int num_wrong;
	int skor_location;
	int _speed_of_game;
	int _speed_flag;
	char word[20];

} game_status;
game_status game1;


int to_send_file(void){
	game1.b_x = b_yatay;		
	game1.b_y = b_high;
	game1.u_x = u_konum;
	game1.high_ = high;
	game1.num_true = count_true;
	game1.num_wrong = count_wrong;
	game1.skor_location = skor_loc;
	game1._speed_of_game = speed_of_game;
	game1._speed_flag = speed_flag;
	sprintf(game1.word, "%s", kelime);
	

}

int load_game(void){
	FILE *load_file;
	char load_name[20];		//name of the game will be loaded
	printf("\nWhat is the name of the game you want to load?\n");
	scanf("%s",&load_name);
	sprintf(load_name, "%s.txt", load_name);
	while(1){
		if(load_file = fopen(load_name, "r"))	//there is such a game has alredy been saved
		{
			
			load_file = fopen(load_name, "r");
			fscanf(load_file, "%d", &b_yatay);		//data in the saved file are loaded to the variables of the game.
			fscanf(load_file, "%d",&b_high);
			fscanf(load_file, "%d",&high);
			fscanf(load_file, "%d",&count_true);
			fscanf(load_file, "%d",&count_wrong);
			fscanf(load_file, "%d",&skor_loc);
			fscanf(load_file, "%d",&u_konum);
			fscanf(load_file, "%d",&speed_of_game);
			fscanf(load_file, "%d",&speed_flag);
			fscanf(load_file, "%s",kelime);
		
			fclose(load_file);
			break;
			
			
		}else{				
			
			fclose(load_file);		
			printf("\nThere is no such a game named %s. Type another name\n", load_name);
			scanf("%s",load_name);
			sprintf(load_name, "%s.txt", load_name);
			
		}
	}
}


int save_game(void){
	
	to_send_file();		//variables in the game are assigned to the struct 
	
	char save_name[20];				//name of the game which will be saved
	
	printf("\nWhat is the name of the game you want to save?\n");
	
	scanf("%s",save_name);
	sprintf(save_name, "%s.txt", save_name);
	FILE *file;
	while(1){
		if(file = fopen(save_name, "r"))		//there is a game which has that name. 
		{
			fclose(file);
			printf("The game named as \"%s\" is already exist. Type another name\n", save_name);
			scanf("%s",save_name);
			sprintf(save_name, "%s.txt", save_name);		//
			
		}else{
			break;
		}
			
	}
			
			
	file = fopen(save_name,"w+");
	
	fprintf(file, "%d\n", game1.b_x);
	fprintf(file, "%d\n", game1.b_y);
	fprintf(file, "%d\n", game1.high_);
	fprintf(file, "%d\n", game1.num_true);
	fprintf(file, "%d\n", game1.num_wrong);
	fprintf(file, "%d\n", game1.skor_location);
	fprintf(file, "%d\n", game1.u_x);
	fprintf(file, "%d\n", game1._speed_of_game);
	fprintf(file, "%d\n", game1._speed_flag);	
	fprintf(file, "%s\n", game1.word);
	
	
	fclose(file);
}


int main( void )
{	
	srand(time(NULL));
	int flag=0;	//flag for game menu
	int k,j,s,u,l,z;		//those will be used for the other "for" loops
	int filelen;		//number of words in the file
	filelen = findWordNum();
	
	find_word_length(filelen);
	
	char c;		//this will be used for kbhit
	while(1)		//main loop for game
	{
		
		////////////////////----------GAME MENU----------////////////////////
		
		
		printf("\n\n\n\n\n\n\t\t\t\t\t When did you last time rescue a city?\n");
		printf("\n\t\t\t\t\t If you haven't yet, then adventure time!!!");
		printf("\n\nChoose one of this choices\n");
		printf("1- New Game\n");
		printf("2- Load a Saved Game\n");
		printf("3- Save Current Game\n");
		printf("4- Return to Game \n");
		printf("5- Exit \n");
		scanf("%d",&control_game);
		
		if(control_game == 1){
			b_high = 0;	
			u_konum=0;		
			high = 1;
			b_yatay = 0;	
			count_true =0;			//ALL THE VARÝABLES ÝS ASSÝGNED THEIR VALUES IN THE BEGÝNNÝNG
			count_wrong = 0;	
			speed_flag= 0;
			skor_loc = 40;
			flag =1;
			get_word(speed_flag,filelen);
			
			system("cls");
			
		}else if(control_game == 2){
			
			flag =1;
			load_game();
			system("cls");
		
			
			
		}else if(control_game == 3){
			if(flag == 0){
				system("cls");
				printf("\nGame did not started yet!!");
				sleep(1);
				system("cls");
				continue;
			}
			save_game();
			system("cls");
			continue;
			
		}else if(control_game == 4){
			if(flag == 0){
				system("cls");
				printf("\n\n\n\n\t\t\t\tGame did not started yet");
				sleep(1);
				system("cls");
				continue;
			}			
			system("cls");
		}else if(control_game == 5){
			break;
		}else{
			continue;
		}
		
		///////////////////---------GAME DYNAMICS---------///////////////////

		for(u_konum; u_konum<u_sinir; u_konum++)
		{
			if(c == 27)
				break;
			while(kbhit()){
				c = getch();
				if(c== kelime[0]){
					count_true++;
					kelime[0]= 0;		// when first element of kelime is zero, this means 
										// all characters of the kelime is written correctly
					int k=0;
					for(k; kelime[k+1] !=0; k++){
						kelime[k] = kelime[k+1];
						kelime[k+1]=0;
						
					}
				}else if(c == 27){
					break;
				}else{
					count_wrong++;
				}
			}
			
			
			if(kelime[0] == 0)
			{
				b_high =0;
				high = 1;
				speed_flag++;
				
			
				b_yatay = u_konum;	//plane is leaving bomb, so horizontal distance of bomb is 
									// equal to horizontal distance of plane 
				get_word(speed_flag, filelen);	
				if(speed_flag%5 == 0){		//speed increment for every 5 word 
					speed_of_game -= 30;
				}
				if(speed_of_game<=100){
					speed_of_game =100;	//after that speed, the speed of game will be constant
				}
				
			}else if(c == 27){
				c = 0;
				break;
			}
			
			
			/////PRINTING THE PLANE		
														
			for(k=0; k < u_konum; k++){		//distance of plane to the beginning of the line is increasing 
				printf("  ");				//after every printing the plane 
			}
			printf("(|__.-. |\n");
		
			for(s=0; s < u_konum; s++){		
				printf("  ");
			}
			printf("== ===_]+\n");
			
			for(j=0; j < u_konum; j++){		
				printf("  ");
			}
			printf("        |");
			
			////END OF PRINTING THE PLANE
			
			for(u =0;skor_loc-u>0;u++){
				printf("  ");
			}
			
			if(u_konum == u_sinir-1){
				skor_loc = 40;
			}
			if(u_konum == u_sinir-1){		
				u_konum =0;
			}	
			
			skor_loc--;
			printf("Skor = %d",count_true-count_wrong);
			printf("\n");
			
			for(b_high=0; b_high<high; b_high++){		//vertical distance of bomb
				
				printf("\n");
			}
				for(z=0;z<b_yatay;z++){					//horizontal distance of bomb
					printf("  ");
				}
				printf("<|>\n");
				for(z=0;z<b_yatay;z++){					//horizontal distance of bomb
					printf("  ");
				}
				printf(" |%s\n",kelime);
				for(z=0;z<b_yatay;z++){					//horizontal distance of bomb
					printf("  ");
				}
				printf(" *");
			
			high++;	
			
			for(l=20;l-high>1;l--){
				printf("\n");
			}
			printf(" _____        _____    _________________ ________    _________\n");
			printf("|o o o|_______|    |__|               | | # # # |____|o o o o|\n");
			printf("|o o o|* * *|: ::|. . |               |o| # # # |. . |o o o o|\n");
			printf("|o o o|* * *|::  |. . | []  []  []  []|o| # # # |. . |o o o o|\n");
			printf("|o o o|**** |:  :| . .| []  []  []    |o| # # # |. . |o o o o|\n");
			printf("|_[]__|__[]_|_||_|__< |____________;;_|_|___[]__|_.|_|__[]___|");
			
			if(b_high == sehrin_siniri){		//Eger Bomba sehrin sýnýrýna geldiyse donguden cikacak
				b_high =0;
				high = 1;
				flag =0;
				system("cls");
				printf("\n\n\n\n\t\t\tGAME OVER!!!\n");
				
				sleep(1);
				system("cls");
				break;
			}
			
			
			
			
			
			Sleep(speed_of_game);
			system("cls");
			
		}		//end of for loop outside
		
	}			//end of while loop
		
}				//end of main function
	
	
	
	

