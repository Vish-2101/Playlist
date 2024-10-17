#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
 
// Initializing the playlist

typedef struct pl{
    char title[100];
    char artist[100];
    float duration;
    struct pl *link;
    struct pl *prev;
} Playlist;

Playlist* start = NULL;
Playlist* current = NULL;

// Function to add the song to the playlist

void add_song(char* title, char* artist, float duration){

    // Not adding Duplicate songs

    Playlist* temp = start;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0 ){
            if(strcmp(temp->artist, artist) == 0) {
                printf("This song by %s already exists in the playlist.\n", artist);
                return;  
            }
        }
        temp = temp->link;
    }

    Playlist* song = (Playlist*)malloc(sizeof(Playlist));

    // Taking details of the song

    strcpy(song->title, title);
    strcpy(song->artist, artist);
    song->duration = duration;
    
    song->link = start;   

    if (start != NULL) {
        start->prev = song; 
    }

    song->prev = NULL; 
    start = song;       

    printf("Song '%s' by '%s' added to the playlist.\n", title, artist);
}

// Function to play the songs

void play_song(){
    if(start == NULL){
        printf("Playlist is Empty\n");
        return;
    }

    char name[100];
    printf("Enter the Title of the Song to Play:");
    scanf(" %[^\n]", name);
    Playlist* temp = start;
    while(temp != NULL){
        if(strcmp(temp->title, name) == 0){
            current = temp;
            printf("Now playing: %s by %s, Duration: %.2f minutes\n", current->title, current->artist, current->duration);
            return;
        }
        temp = temp->link;
    }
    printf("Song with title '%s' not found.\n", name);
}


// Function to autoplay the playlist

void auto_play_song(){
    if(start == NULL){
        printf("Playlist is Empty\n");
        return;
    }
    Playlist* temp = start;
    while(temp != NULL){
        printf("Playing: %s by %s, Duration: %.2f minutes\n", temp->title, temp->artist, temp->duration);
        Sleep(temp->duration * 60 * 1000);
        temp = temp->link;
    }
    printf("End of Playlist\n");
}

// Function to skip to next song

void play_next(){
    if(current != NULL && current->link != NULL){
        current = current->link;
        printf("Playing: %s by %s, Duration: %.2f minutes\n", current->title, current->artist, current->duration);
    }
    else{
        printf("End of playlist\n");
    }
        
}

// Function to go to previous song

void play_prev(){
    if(current != NULL && current->prev != NULL){
        current = current->prev;
        printf("Playing: %s by %s, Duration: %.2f minutes\n", current->title, current->artist, current->duration);
    }
    else{
        printf("Start of playlist\n");
    }
}

// Function to delete a song by name

void delete_song(){
    if(start == NULL){
        printf("Playlist is Empty");
        return;
    }

    char name[100];
    printf("Enter the Title of the Song to Delete:");
    scanf(" %[^\n]", name);
    Playlist* temp = start;
    while(temp != NULL){
        if(strcmp(temp->title, name) == 0){
            if(temp == start){
                start = start->link;
                if(start != NULL){
                    start->prev = NULL;
                }
            }
            else if(temp->link == NULL){
                temp->prev->link = NULL;
            }
            else{
                temp->prev->link = temp->link;
                temp->link->prev = temp->prev;
            }
            
            printf("Song with Title '%s' has been Deleted.\n", name);

            free(temp);
            if(current == temp){
                current = start;
            }
            return;
        }
        temp = temp->link;
    }
     printf("Song with Title '%s' not found in the Playlist.\n", name);
}

// Function to display the playlist

void display(){
    Playlist* temp = start;
    if(temp == NULL){
        printf("Playlist is empty\n");
        return;
    }
    printf("Playlist:\n");
    while (temp != NULL){
        printf("Title: %s, Artist: %s, Duration: %.2f minutes\n", temp->title, temp->artist, temp->duration);
        temp = temp->link;
    }
}

// Function to Autoplay in a Random order

void shuffle(){
    if(start == NULL){
        printf("Playlist is Empty\n");
        return;
    }

    // Counting the number of Songs

    int count = 0;
    Playlist* temp = start;
    while(temp != NULL){
        count++;
        temp = temp->link;
    }

    // Tracking the songs 

    int songs_played = 0;
    int song_arr[count];
    for (int i = 0; i < count; i++){
        song_arr[i] = 0;
    }

    // Random num Gen

    srand(time(0));

    // PLaying songs in a random order

    while(songs_played < count){
        int random = rand() % count;
        if(!song_arr[random]){
            song_arr[random] = 1;
            songs_played++;
            temp = start;
            for(int i = 0; i < random; i++){
                temp = temp->link;
            }
            printf("Playing: %s by %s, Duration: %.2f minutes\n", temp->title, temp->artist, temp->duration);
            Sleep((DWORD)(temp->duration*60*1000));
        }
    }
     printf("End of Playlist\n");
}

// Main Program

int main(){
    int choice;
    float duration;
    char title[30], artist[30];

    while (1) {
        printf("\nPlaylist Menu\n");
        printf("1. Add Song\n");
        printf("2. Play Song\n");
        printf("3. Play Next Song\n");
        printf("4. Play Previous Song\n");
        printf("5. Delete a Song\n");
        printf("6. Auto Play\n");
        printf("7. Shuffle Play\n");
        printf("8. Display\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf(" %[^\n]", title);
                printf("Enter artist name: ");
                scanf(" %[^\n]", artist);
                printf("Enter song duration (in minutes): ");
                scanf("%f", &duration);
                add_song(title, artist, duration);
                break;
            case 2:
                play_song();
                break;
            case 3:
                play_next();
                break;
            case 4:
                play_prev();
                break;
            case 5:
                delete_song();
                break;
            case 6:
                auto_play_song();
                break;
            case 7:
                shuffle();
                break;
            case 8:
                display();
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}