// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: Joonsu Oh
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//
bool isThereDuplicate(Node *NODE, char *promptName);
Node *appropriateNode(Node *NODE, char *promptName);
void insertNewNode(Node *insertAfterThisNode, char *promptName, char *promptArtist, char *promptGenre);
void findSong(Node *NODE, char *promptSearch);
void findAndDeleteSong(Node *NODE, char *promptDeletion);
void printMusicLibrary(Node *head);
void quitLibrary(Node *head);
bool isPrecedence(char* songToBeInserted, char* songToBeCompared);
// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH=1024;

int main(void){
    // Declare the head of the linked list.
    //   ADD YOUR STATEMENT(S) HERE
	Node *head = malloc(sizeof(Node));
	head->nextNode = NULL;
	
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" ) ;
    
		
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;
			
		
        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE

            // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
            char promptName[ MAX_LENGTH + 1 ];
			inputStringFromUser("Song name", promptName, MAX_LENGTH);
           
			char promptArtist[ MAX_LENGTH + 1 ];
			inputStringFromUser("Artist", promptArtist, MAX_LENGTH);

            char promptGenre[ MAX_LENGTH + 1 ];
			inputStringFromUser("Genre", promptGenre, MAX_LENGTH);
			
			if( isThereDuplicate(head, promptName)){
				songNameDuplicate(promptName);
			}else{
				insertNewNode(appropriateNode(head, promptName), promptName, promptArtist, promptGenre);
			}
        }
        else if( response == 'D' ) {
            // Delete a song from the list.
            char promptDeletion[ MAX_LENGTH + 1 ];
			inputStringFromUser("\nEnter the name of the song to be deleted", promptDeletion, MAX_LENGTH);
			findAndDeleteSong(head, promptDeletion);
        }
        else if( response == 'S' ) {
            // Search for a song by its name.
            char promptSearch[ MAX_LENGTH + 1 ];
			inputStringFromUser("\nEnter the name of the song to search for", promptSearch, MAX_LENGTH);
			findSong(head, promptSearch);
        }
        else if( response == 'P' ) {
            // Print the music library.
			printMusicLibrary(head);
        }
        else if( response == 'Q' ) {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
  
    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE
	quitLibrary(head);
    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
	printMusicLibrary(head);
	free(head);
    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

// Add your functions below this line.
bool isThereDuplicate(Node *NODE, char *promptName){
	if(NODE != NULL){
	Node *curr = NODE->nextNode;
		while(curr != NULL){
			if(strcmp(promptName, curr->songName) == 0 ){
				return true;
			}
			curr = curr->nextNode;
		}
	}
	return false;
}

Node *appropriateNode(Node *NODE, char *promptName){
	if(NODE != NULL){
		Node *prev = NODE;
		Node *curr = NODE->nextNode;
		while(curr != NULL){
			if( isPrecedence(promptName, curr->songName) ){ //New entered song precedes
				return  prev; //the new song has to be added after the prev
			}
			prev = prev->nextNode;
			curr = curr->nextNode;
		}
		return prev;
	}
}

bool isPrecedence(char* songToBeInserted, char* songToBeCompared){
	int i=0, j=0;
	while( (songToBeInserted[i] != '\0') && (songToBeCompared[j] != '\0') ) { //Loop ends if either string reaches the end
		while(songToBeInserted[i] == 32) i++;
		while(songToBeCompared[j] == 32) j++;
		
		if( tolower(songToBeInserted[i]) < tolower(songToBeCompared[j]) ){
			return true;
		}
		else if( tolower(songToBeInserted[i]) > tolower(songToBeCompared[j]) ){
			return false;
		}
		//else if( tolower(songToBeInserted[i]) == tolower(songToBeCompared[j]) ){
		//loop continues
		i++,j++;
		//}
	}
	
	if(songToBeInserted[i] == '\0'){ //New Song precedes
		return true;
	}else{ //New Song does not precede
		return false;
	}
}




void insertNewNode(Node *insertAfterThisNode, char *promptName, char *promptArtist, char *promptGenre){
		
	if(insertAfterThisNode != NULL){
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->nextNode = insertAfterThisNode->nextNode;
		insertAfterThisNode->nextNode = newNode;
		newNode->songName = malloc(strlen(promptName)+1);
		newNode->artist = malloc(strlen(promptArtist)+1);
		newNode->genre = malloc(strlen(promptGenre)+1);
		
		strcpy( newNode->songName, promptName);
		strcpy( newNode->artist, promptArtist);
		strcpy( newNode->genre, promptGenre);
		
	}
	return;
}

void findSong(Node *NODE, char *promptSearch){
	if(NODE != NULL){
		Node *curr = NODE->nextNode;
			while(curr != NULL){
				if(strcmp(promptSearch, curr->songName) == 0 ){
					songNameFound(promptSearch);
					printf("\n%s", curr->songName);
					printf("\n%s", curr->artist);
					printf("\n%s\n", curr->genre);
					return;
				}
				curr = curr->nextNode;
			}
		}
	songNameNotFound(promptSearch);
	return;
}


void printMusicLibrary(Node *head){
	Node *curr = head->nextNode;
	if( curr == NULL ){
		printMusicLibraryEmpty();
		return;
	}
	else{
		printMusicLibraryTitle();
		while( curr != NULL ){
			printf("\n%s", curr->songName);
			printf("\n%s", curr->artist);
			printf("\n%s\n", curr->genre);
			
			curr = curr->nextNode;
		}
		return;
	}
}

void quitLibrary(Node *head){
	if(head != NULL){
		while( (head->nextNode) != NULL){
			Node *curr = head->nextNode;
			head->nextNode = curr->nextNode;
			
			songNameDeleted(curr->songName);
			
			free(curr->songName);
			free(curr->artist);	
			free(curr->genre);
			free(curr);				
		}
	}
	return;
}

void findAndDeleteSong(Node *head, char *songToBeDeleted){ //to be used in following way: findAndDelteSong(head, promptDeletion)
	if(head != NULL){
		Node *prev = head;
		Node *curr = head->nextNode;
			while(curr != NULL){
				if(strcmp(songToBeDeleted, curr->songName) == 0 ){
					prev->nextNode = curr->nextNode;
					free(curr->songName);
					free(curr->artist);	
					free(curr->genre);
					free(curr);
					songNameDeleted(songToBeDeleted);
					return;
				}
				curr = curr->nextNode;
				prev = prev->nextNode;
			}
		}
	songNameNotFound(songToBeDeleted);
	return;
}
