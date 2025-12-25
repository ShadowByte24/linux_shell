#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000
#define MAXLIST 100

#define clear() printf("\033[H\033[J")

void init_shell(){
	clear();
	printf("\n**********************");
	printf("\n*****USE MY SHELL******");
	printf("\n**********************");
	char* username = getenv("USER");
	printf("\n USER is: %s",username);
	printf("\n");
	sleep(1);
}

int take_input(char* str){
	char* buf;

	buf=readline("\n>>");
	if (!buf) {
    printf("\n");
    return 1;
}
	if(strlen(buf)!=0){
		add_history(buf);
		strcpy(str,buf);
		return 0;
	} else{
		return 1;
	}
}

void printDir(){
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	printf("\nDir: %s",cwd);
}

void execArgs(char** parsed){
	pid_t pid=fork();
	if(pid==-1){
		printf("\nFailed forking child..");
		return;
	} else if(pid==0){
		if(execvp(parsed[0],parsed)<0){
			printf("\nCould not execute command...");
		}
		exit(0);
	}else{
		wait(NULL);
		return;
	}
}

void execArgsPiped(char** parsed,char** parsedPipe){
	//0 is read end, 1 is write end
	int pipefd[2];
	pid_t p1,p2;

	if(pipe(pipefd)<0){
		printf("\nPipe could not be initialized...");
		return;
	}

	p1=fork();
	if(p1<0){
		printf("\nCould not fork");
		return;
	}

	if(p1==0){
		//child 1 executing
		close(pipefd[0]);
		dup2(pipefd[1],STDOUT_FILENO);
		close(pipefd[1]);

		if(execvp(parsed[0],parsed)<0){
			printf("\nCould not execute command 1..");
			exit(0);
		}
	} else{
		//parent executing
		p2=fork();

		if(p2<0){
			printf("\nCould not fork");
			return;
		}

		if(p2==0){

			close(pipefd[1]);
			dup2(pipefd[0],STDIN_FILENO);
			close(pipefd[0]);

			if(execvp(parsedPipe[0],parsedPipe)<0){
				printf("\nCould not execute command 2...");
				exit(0);
			}
		}
		else{
			wait(NULL);
			wait(NULL);
		}
	}
}


void openHelp(){
	puts("\n***Welcome to my shell help***"
		"\nList of commands supported:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all other general commands used in UNIX shell"
		"\n>pipe handling"
		"\nimproper space handling");

	return;
}


int ownCmdHandler(char** parsed){
	int noOfOwnCmds=4,i,switchOwnArgs=0;
	char* ListofOwnCmds[noOfOwnCmds];
	char* username;

	ListofOwnCmds[0]="exit";
	ListofOwnCmds[1]="cd";
	ListofOwnCmds[2]="help";
	ListofOwnCmds[3]="hello";

	for(int i=0;i<noOfOwnCmds;i++){
		if(strcmp(parsed[0],ListofOwnCmds[i])==0){
			switchOwnArgs=i+1;
			break;
		}
	}

	switch(switchOwnArgs){
	case 1:
		printf("\nGoodBye");
		exit(0);
	case 2:
		 if (parsed[1] == NULL)
        chdir(getenv("HOME"));
    else
        chdir(parsed[1]);
    return 1;
	case 3:
		openHelp();
		return 1;
	case 4:
		username=getenv("USER");
		printf("\nHello %s.\nMind this is not a place to play around"
			"\nUse help to know more..\n",username);
		return 1;
	default:
		break;
	}

	return 0;
}

int parsePipe(char* str,char** strpiped){
	int i;
	for(i=0;i<2;i++){
		strpiped[i]=strsep(&str,"|");
		if(strpiped[i]==NULL) 
			break;
	}

	if(strpiped[1]==NULL)
		return 0; //if no pipe found
	else{
		return 1;
	}
}

//function for passing command words
void parseSpace(char* str, char** parsed){
	int i;

	for(int i=0;i<MAXLIST;i++){
		parsed[i]=strsep(&str," ");

		if(parsed[i]==NULL) break;
		if(strlen(parsed[i])==0) i--;
	}
}

int processString(char* str,char** parsed, char** parsedPipe){

	char* strpiped[2];
	int piped=0;

	piped=parsePipe(str,strpiped);

	if(piped){
		parseSpace(strpiped[0],parsed);
		parseSpace(strpiped[1],parsedPipe);
	} else{
		parseSpace(str,parsed);
	}

	if(ownCmdHandler(parsed))
		return 0;
	else return 1+piped;
}

int main(){

	char inputString[MAXCOM],*parsedArgs[MAXLIST];
	char* parsedArgsPiped[MAXLIST]={NULL};
	int execFlag=0;
	init_shell();

	while(1){
		printDir();

		if(take_input(inputString))
			continue;

		execFlag=processString(inputString,parsedArgs,parsedArgsPiped);
		//0 no command
		//1 simple command
		//2 including a pipe

		if(execFlag==1) execArgs(parsedArgs);
		if(execFlag==2) execArgsPiped(parsedArgs,parsedArgsPiped);
	}
	return 0;
}