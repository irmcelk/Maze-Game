#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h> 
#include <time.h>

#define MAX_USERS 100
#define MAX_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_SCORES 5

typedef struct {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int  high_score;
       int  current_score;
} User;

typedef struct {
    int scores;
    char username[MAX_USERNAME_LENGTH];
} Score;

typedef struct {
    User users[MAX_USERS];
    int userCount;
} UserDatabase;

// Kullanýcý veritabaný oluþturma ve baþlatma
UserDatabase* createUserDatabase() {
    UserDatabase *db = (UserDatabase*)malloc(sizeof(UserDatabase));
    if (db != NULL) {
        db->userCount = 0;
    }
    return db;
}

int isUsernameTaken(const char *username,UserDatabase *db) {
	int i;
    for (i = 0; i < db->userCount; i++) {
        if (strcmp(db->users[i].username, username) == 0) {
            return 1; // Kullanýcý adý zaten alýnmýþ
        }
    }
    return 0; // Kullanýcý adý kullanýlabilir
}
// Kullanýcý eklemek
User createUser(UserDatabase *db) {
	User newUser;
    int i;
    printf("First Name:");
    scanf("%s",newUser.firstName);
    printf("Last Name:");
    scanf("%s",newUser.lastName);
    printf("User name:");
    scanf("%s",newUser.username);
    while (isUsernameTaken(newUser.username,db)) {
        printf("This nickname is used. Enter a new nickname: ");
        scanf("%s", newUser.username);
    }
    printf("Password:");
    scanf("%s",newUser.password);
   printf("Registration is successful");
    // Yeni kullanýcý ekleme
    if (db->userCount < MAX_USERS) {
        strcpy(db->users[db->userCount].firstName, newUser.firstName);
        strcpy(db->users[db->userCount].lastName, newUser.lastName);
        strcpy(db->users[db->userCount].username, newUser.username);
        strcpy(db->users[db->userCount].password, newUser.password);
        db->users[db->userCount].high_score = 0;
        db->userCount++;
        saveUserDatabaseToFile(db);
        return newUser; // Baþarýyla eklendi
    } 
}
//kullanýcý dosyasýný sýfýrlama program tekrar baþlatýlýnca sýfýrlanmýþ dosya geliyor
void resetPlayer(UserDatabase *db){
   FILE *data=fopen("users.dat","w");
     if (data == NULL) {
        printf("File opening error.\n");
        return;
    }

    fclose(data);
     db->userCount = 0;
    printf("File reseted.\n");
}
// Kullanýcý bilgilerini bir dosyaya yazma
void saveUserDatabaseToFile(UserDatabase *db) {
    FILE *file = fopen("users.dat", "wb");
    if (file != NULL) {
        fwrite(db, sizeof(UserDatabase), 1, file);
        fclose(file);
    } else {
        printf("File opening error\n");
    }
}

// Kullanýcý bilgilerini bir dosyadan okuma
UserDatabase* loadUserDatabaseFromFile() {
    UserDatabase *db = (UserDatabase*)malloc(sizeof(UserDatabase));
    FILE *file = fopen("users.dat", "rb");
    if (file != NULL) {
        fread(db, sizeof(UserDatabase), 1, file);
        fclose(file);
    } else {
        printf("File opening error\n");
    }
    return db;
}
//dosyadaki verileri güncelleme
void updateUserDatabaseFromFile(char *userName, int newScore) {
    UserDatabase *db = loadUserDatabaseFromFile();
    int found = 0;
    int i;
    printf("\nUsername: %s\n", userName);
    for (i = 0; i < db->userCount; ++i) {
        if (strcmp(db->users[i].username, userName) == 0) {
            db->users[i].current_score = newScore;
            if (newScore > db->users[i].high_score) {
                db->users[i].high_score = newScore;
                printf("Skor guncellendi\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Error: User not found.\n");
    }

    saveUserDatabaseToFile(db);

    free(db);
}
   
User loginUser(UserDatabase *db) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int i;
    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password:");
    scanf("%s", password);

    for (i = 0; i < db->userCount; i++) {
        if (strcmp(db->users[i].username, username) == 0 && strcmp(db->users[i].password, password) == 0) {
            printf("Login successful! Welcome, %s.\n", db->users[i].username);
            return db->users[i]; // Kullanýcýnýn indeksini döndür
        }
    }

    printf("Username or password is wrong.\n");
}


char** createMap(int ROWS,int COLS,int choice){
  char** map;
  int i,j;
  FILE *file ;
   char filename[100];
  map=(char**)malloc(ROWS*sizeof(char*));
  for(i=0;i<ROWS;i++)	{
  	map[i]=(char*)malloc(COLS*sizeof(char));
  }
  if(choice==1){
  	file = fopen("Harita1.txt", "r");
  }
  else if(choice==2){
  	file = fopen("Harita2.txt", "r");
  }
  else if(choice==3)
  	file = fopen("Harita3.txt", "r");
  else{
    printf("Lutfen harita dosyasini giriniz: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
  }
    if (file != NULL) {
       for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            fscanf(file, "%s", &map[i][j]);
			   
        }
    }
    printf("Matrix:\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%c\t", map[i][j]);
        }
        printf("\n");
    }
        fclose(file);
}
    
	else {
        printf("File opening error\n");
    }
  
return map;	
}
void printMap(char** map,int ROWS, int COLS) {
	int i,j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}
int findStart(char** map, int *startRow, int *startCol,int ROWS, int COLS) {
	int i,j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (map[i][j] == 'G') {
                *startRow = i;
                *startCol = j;
                return 1;
            }
        }
    }
    return 0; // Baþlangýç konumu bulunamadý
}
int movePlayer(char** map, int *playerRow, int *playerCol, char move,int ROWS, int COLS){
    int newRow = *playerRow;
    int newCol = *playerCol;
    switch (move) {
        case 'W':
        case 'w':
        case 72: // Yukarý ok tuþu ASCII deðeri
           newRow--;
            break;
        case 'A':
        case 'a':
        case 75: // Sol ok tuþu ASCII deðeri
            newCol--;
            break;
        case 'S':
        case 's':
        case 80: // Aþaðý ok tuþu ASCII deðeri
            newRow++;
            break;
            
        case 'D':
        case 'd':
        case 77: // Sað ok tuþu ASCII deðeri
            newCol++;
            break;
    }
    
    // Geçerli hareket kontrolü
    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1') {
        // Yeni konum geçerli, oyuncuyu hareket ettir
        map[*playerRow][*playerCol] = '0';
        *playerRow = newRow;
        *playerCol = newCol;
      //map[*playerRow][*playerCol] == 'C'||map[*playerRow][*playerCol] == 'K'||map[*playerRow][*playerCol] == 'P'||map[*playerRow][*playerCol] == 'p'||map[*playerRow][*playerCol] == 'E'||map[*playerRow][*playerCol] == 'e'
        if (strchr("CK", map[*playerRow][*playerCol]) != NULL) {
            return 2;
        }
        else if (strchr("PpEe", map[*playerRow][*playerCol]) != NULL) {
            return 3;
        }
        map[*playerRow][*playerCol] = 'X'; // Oyuncuyu yeni konumda göster
        return 1;
    } 
	    // Geçersiz hareket, oyuncu hareket etmez
        return 0;
    
}
	
int parca(char *parcalar,char a, char b){
   int length = strlen(parcalar);
   int i,j;
    for (i = 0; i < length - 1; ++i) {
        if ((parcalar[i] == a || parcalar[i] == b ) && (parcalar[i + 1] == a || parcalar[i + 1] == b)) {
            // Bir çift bulunduðunda, bu çifti sil ve diziyi sola kaydýr
            for (j = i; j < length - 2; ++j) {
                parcalar[j] = parcalar[j + 2];
            }
            parcalar[length - 2] = '\0';  // Yeni uzunluðu ayarla
            length -= 2;  // Yeni uzunluðu güncelle
            i = (i > 0) ? (i - 2) : -1;  // Eðer i sýfýrdan büyükse geriye git
        }
    }
    return length;
}

int startGame(char**map,int ROWS,int COLS,User u){
	char *parcalar=NULL;
	int i,j;
	int count=0,cp=0,cP=0,cE=0,ce=0;// hangi parçacýktan kaç tane olduðunu tutmak için
	int count2=0,count3=0;// kaç karþýt madde üretileceðini bulmak için
    int startRow, startCol;
    int result;//movepPlayer returnu
    int seconds=120;
    int newScore;
    
    if (!findStart(map, &startRow, &startCol,ROWS,COLS)) {
        printf("Baslangic konumu bulunamadi.\n");
        return;
    }

    int playerRow = startRow;
    int playerCol = startCol;
    map[playerRow][playerCol] = 'X';
    clock_t start_time = clock(); //baþlangý zamaný
    // Oyun döngüsü
    char move;
    do {
    system("cls"); // Ekraný temizle
    printMap(map,ROWS,COLS);
    printf("\r%02d\n",seconds);
    clock_t stop = clock(); // Geçen süreyi al
     while(clock()<stop){
	 }
	 seconds--;
    printf("W - Up, A - Left, S - Down, D - Right or You can use arrow signs,ESC is quit\n");
    printf("Choose a movement: ");
    move = getch();
    if (move==27) 
		{
			printf("Quit\n");
			return 0;
		}

    result = movePlayer(map, &playerRow, &playerCol, move,ROWS,COLS);
    if (result == 0) {
        printf("Gecersiz hareket! Tekrar deneyin.\n");
        sleep(1); // 1 saniye bekletme
    } 
   
	else if(result==2){
        if (map[playerRow][playerCol] == 'C') {
        	for(i=0;i<count;i++){
        	printf("%c\n",parcalar[i]);	
		}
            printf("Tebrikler! Cikisi buldunuz.\n");
        if(cp!=0 && cP!=0){
            if(cp<=cP){
              count=parca(parcalar,'p','P');	
			}
			else {
				count=parca(parcalar,'P','p');
			}
		}
		 if(ce!=0 && cE!=0){
			if(ce<=cE){
			 count=parca(parcalar,'e','E');	
			}
			else{
			 	count=parca(parcalar,'E','e');	
			}
		}
		 
		    for(i=0;i<count;i++){
        	printf("%c\n",parcalar[i]);	
        	if(parcalar[i]=='E')
        	  count2++;
        	else if(parcalar[i]=='p')
        	  count3++;
		  }
		  if(count2<=count3){
		  	printf("%d tane karsit madde uretildi\n",count2);
		  	 u.current_score=count2*ROWS*COLS;
		  	
		
		  }
		  else {
		  	printf("%d tane karsit madde uretildi\n",count3);
		  	 u.current_score=count3*ROWS*COLS;
		  }
		   printf("Skorunuz %d", u.current_score);
		  updateUserDatabaseFromFile(u.username, u.current_score);
           return 0; // Oyunu bitir
        }
   
        else if(map[playerRow][playerCol] == 'K'){
        	printf("Karadelik!!!!\n");
            return 0; // Oyunu bitir
		}
}
     else if(result==3){
     	sleep(1);
     	//dizi oluþacak dizini yeri arttýrýlacak sonra diziye bu elemaný kayýt edicez.
     	count++;
     	char *temp = (char*)realloc(parcalar, count * sizeof(char));
            if (temp == NULL) {
                // Hata kontrolü
                printf("Bellek genisletme hatasi\n");
                free(parcalar);
                exit(EXIT_FAILURE);
            }
            parcalar = temp;
		if (map[playerRow][playerCol] == 'P') {
            *(parcalar+count-1)='P';
            cP++;
        }
        else if (map[playerRow][playerCol] == 'p') {
            *(parcalar+count-1)='p';
            cp++;
        }
        else if (map[playerRow][playerCol] == 'E') {
            *(parcalar+count-1)='E'; 
            cE++;
        }
        else if (map[playerRow][playerCol] == 'e') {
            *(parcalar+count-1)='e';
            ce++;
        }
        map[playerRow][playerCol] = 'X';
        int i;
        for(i=0;i<count;i++){
        	printf("\n%c",parcalar[i]);	
		}
		sleep(2);

	 }
  } while (seconds>0);
   printf("Time is out. You cant reach exit.Try again!\n");
  //control();
    free(parcalar);
}
//otomatik modda giriþ rastgele olduðu için giriþin C ye göre olan konumunu buluyor
void findExit(char** map, int *startRow, int *startCol, int ROWS, int COLS, int *resultX, int *resultY) {
    int exitRow, exitCol;
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (map[i][j] == 'C') {
                exitRow = i;
                exitCol = j;
            }
        }
    }

    *resultX = exitRow - (*startRow);
    *resultY = exitCol - (*startCol);
}

int runAutomaticMode(char** map,int ROWS,int COLS,User player) {
    int startRow, startCol;
    int resultX, resultY;
    int i,j;
    char move;
    int flag=0;
    srand(time(NULL));
    for(i=0;i<ROWS;i++){
     		for(j=0;j<COLS;j++){
     			if(map[i][j]=='G'){
     				map[i][j]='0';
				 }
			 }
		 }
		 //mapteki giriþi rastgele olarak deðiþtiriyor
	while(flag==0){
     startRow = rand() % ROWS;
     startCol = rand() % COLS;
     if(map[startRow][startCol]=='0'){
     	map[startRow][startCol]=='G';
     	flag=1;
	 }
  }
    int playerRow = startRow;
    int playerCol = startCol;
    map[playerRow][playerCol] = 'X';
    int newRow = playerRow;
    int newCol = playerCol;
    int result=0;
    findExit(map, &startRow, &startCol, ROWS, COLS, &resultX, &resultY);
   for(i=0;i<30;i++) {
        while(resultX>0){
         system("cls"); // Ekraný temizle
         printMap(map,ROWS,COLS);
        	move='S';
        	printf("%c\n",move);
            newRow++;
          if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1'){
            result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
             resultX--;}
         else{
         	printf("%c olmadý\n",move);
         	newRow--;
         	newCol++;
         	move='D';
         		printf("%c\n",move);
            if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1' )
             {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS); 
			 resultY--;}
		    else {
		        printf("%c olmadý\n",move);
		        move='A';
		    	printf("%c\n",move);
			   newCol=newCol-2;
			if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1' )
             {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS); 
        
			 resultY++;}
			 else{
			 	printf("%c olmadý\n",move);
			 	move='W';
			 
			 	newCol++;
			 	newRow--;
			 	if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1' )
                {result=movePlayer(map, &playerRow, &playerCol, move,ROWS, COLS);
			 	resultX++;
				 }
			 	else{
			 		return 0;
				 }
			 }
			 
		 }
   	}
   	sleep(1);
   	if (result == 2) {
            if (map[playerRow][playerCol] == 'C') {
                printf("Otomatik mod: Cikisi buldum!\n");
                return 0;
            } else if (map[playerRow][playerCol] == 'K') {
                printf("Otomatik mod: Karadelikle karsilasildi. Oyun sona erdi.\n");
                return 0;
            }
        }
      else if(result==3){
      	printf("Madde\n");
	  }

}
        while(resultY>0){
            system("cls"); // Ekraný temizle
            printMap(map,ROWS, COLS);
            move='D';
            printf("%c\n",move);
            newCol++;
           if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1' )
            {
			 result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
			 resultY--;
			}
           else {
           	printf("%c olmadý\n",move);
         	newRow++;
         	newCol--;
         	move='S';
         	printf("%c\n",move);
         	if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1'){
            result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
             resultX--;
			 }
            else{
            printf("%c olmadý\n",move);
         	newRow=newRow-2;
         	move='W';
         	printf("%c\n",move);
         	if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1')
                {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
			 	resultX++;
		  } 
			else { 
		       printf("%c olmadý\n",move);
         	   newCol--;
         	   newRow++;
         	   move='A';
               printf("%c\n",move);
			     if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1')
                    {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
			           resultY++;
			       }
			    else
			   	 {
			 		return 0;
				 }
				 
			}
	 }
}
         	
     sleep(2);    	 
     if (result == 2) {
            if (map[playerRow][playerCol] == 'C') {
                printf("***Otomatik mod: Cikisi buldum!***\n");
                return 0;
            } 
			else if (map[playerRow][playerCol] == 'K') {
                printf("***Otomatik mod: Karadelikle karsilasildi. Oyun sona erdi.****\n");
                sleep(2);
                return 0;
            }
        }

   }
     while(resultX<0){
     	system("cls"); // Ekraný temizle
            printMap(map,ROWS, COLS);
            move='W';
            printf("%c\n",move);
            newRow--;
           if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1')
            {
			 result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS); 
			 resultX++;
			}
           else {
           	printf("%c olmadý\n",move);
         	newRow++;
         	newCol--;
         	move='A';
         	printf("%c\n",move);
         	if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1' ){
            result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
            resultY++;
			}
            else{
            printf("%c olmadý\n",move);
         	newCol=newCol+2;
         	move='D';
         	printf("%c\n",move);
         	if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1')
                {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
			 	resultY--;
		  } 
			else { 
		       printf("%c olmadý\n",move);
         	   newCol--;
         	   newRow++;
         	   move='S';
               printf("%c\n",move);
			     if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1')
                    {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
			          resultX--;
			 }
			    else
			   	 {	return 0;
				
				 }	 
			}	 
			
	}
}
     sleep(2);    	 
     if (result == 2) {
            if (map[playerRow][playerCol] == 'C') {
                printf("***Otomatik mod: Cikisi buldum!***\n");
                return 0;
            } 
			else if (map[playerRow][playerCol] == 'K') {
                printf("***Otomatik mod: Karadelikle karsilasildi. Oyun sona erdi.****\n");
                sleep(2);
                return 0;
            }
        }
     
   	
	 }
	 while(resultY<0){
            system("cls"); // Ekraný temizle
            printMap(map,ROWS, COLS);
            move='A';
            printf("%c\n",move);
            newCol--;
           if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1' )
            {
			 result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS); 
			 resultY++;
			}
           else {
           	printf("%c olmadý\n",move);
         	newRow--;
         	newCol++;
         	move='W';
         	printf("%c\n",move);
         	if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1'){
            result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
             resultX++;
			 }
            else{
            printf("%c olmadý\n",move);
         	newCol=newCol-2;
         	move='S';
         	printf("%c\n",move);
         	if (newRow >= 0 && newRow < ROWS && map[newRow][newCol] != '1')
                {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
			 	resultX++;
		  } 
			else { 
		       printf("%c olmadý\n",move);
		       newRow++;
         	   newCol++;
         	   move='D';
               printf("%c\n",move);
			     if (newCol >= 0 && newCol < COLS && map[newRow][newCol] != '1')
                    {result=movePlayer(map, &playerRow, &playerCol, move, ROWS, COLS);
			           resultY++;
			       }
			    else
			   	 {
			 		return 0;
				 }
				 
			}
	 }
}
         	
     sleep(2);    	 
     if (result == 2) {
            if (map[playerRow][playerCol] == 'C') {
                printf("***Otomatik mod: Cikisi buldum!***\n");
                return 0;
            } 
			else if (map[playerRow][playerCol] == 'K') {
                printf("***Otomatik mod: Karadelikle karsilasildi. Oyun sona erdi.****\n");
                sleep(2);
                return 0;
            }
        }

 }
    
       return 0;
}
}
int compareUsers(const void *a, const void *b) {
    return ((User *)b)->high_score - ((User *)a)->high_score;
}
void printUserDatabase(UserDatabase *db) {
	qsort(db->users, db->userCount, sizeof(User), compareUsers);
    int i;
    for (i = 0; i < 5; ++i) {
        printf("User %d:\n", i + 1);
        printf("  Username: %s\n", db->users[i].username);
        printf("  High Score: %d\n", db->users[i].high_score);
        printf("\n");
    }
}

void displayMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Create New Account\n");
    printf("2. Login\n");
    printf("3. Show Highest Scores\n");
    printf("4. Reset Players\n");
    printf("5. Show Game Rules\n");
    printf("6. Start Game\n");
    printf("7. Quit\n");
    printf("Choice: ");
}
void printGameRules(){
	printf("Welcome to the Antimatter Maze game!\n");
    printf("Navigate through the maze using the keys: W, A, S, D, and arrow keys.\n");
    printf("Explore paths filled with subatomic particles.\n");
    printf("Collect these particles as you move from the specified entry point to the exit.\n");
    printf("Utilize the collected subatomic particles to generate antimatter hydrogen.\n");
    printf("You have 120 seconds to conquer the maze and emerge victorious.\n");
    printf("Play in controlled mode or let the game take control in auto-play mode.\n");
    printf("Choose from ready-made maps or load your preferred custom map.\n");
    printf("Subatomic Particles Guide:\n");
    printf("   P+: Proton\n");
    printf("   e-: Electron\n");
    printf("   P-: Antiproton\n");
    printf("   e+: Positron\n");
    printf("To produce antimatter hydrogen at the maze exit, you should only have P- and e+ particles in your possession.");
    printf("Press the 'esc' key to exit the game manually.\n");
    printf("In auto-play mode, the game attempts to find the exit in 30 moves.\n");
    printf("Embark on a thrilling journey through the Antimatter Maze, collect particles, and race against time to create antimatter hydrogen. Are you ready for the challenge?");
}

int main() {
	int i,choice;
	int currentUserIndex = -1;
	char **map;
	int rows,cols;
	int startRow, startCol;
	int playerRow;
    int playerCol;
    UserDatabase *db = loadUserDatabaseFromFile();
    User player;
    
    if (db == NULL) {
        db = createUserDatabase();
    }
    
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                player=createUser(db);
                break;
            case 2:
                player = loginUser(db);
                currentUserIndex=1;
                break;
            case 3:
            	 printUserDatabase(db);
                break;
            case 4:
                resetPlayer(db);
                break;
            case 5:
               printGameRules();
                break;
            case 6:
                if (currentUserIndex=1) {
                    printf("Game is starting...\n");
                    printf("1-Player Controlled Game\n2-Automatic Game: ");
                    scanf("%d",&choice);
                    printf("Choose map\n1-5*5(Easy)\n2-6*10(Normal)\n3-12*15\n4-Load Your Own Map: ");
                    if(choice==1){
                     scanf("%d",&choice);
                       if(choice==1){
                       	map=createMap(5,5,1);
                       	startGame(map,5,5,player);
					   }
					   else if(choice==2){
					   	map=createMap(6,10,2);
                       	startGame(map,6,10,player);
					   }
					   else if(choice==3){
					   	map=createMap(12,10,3);
                       	startGame(map,12,10,player);
					   }
					   else if(choice==4){
					   	  printf("Rows?\n");
					   	  scanf("%d",&rows);
					   	  printf("Cols?\n");
					   	  scanf("%d",&cols);
					   	  map=createMap(rows,cols,choice);
					   	  startGame(map,rows,cols,player);
					   }
                      	else{
                      		printf("Invalid section.Try Again\n");
						  }
					}
                    else{ 
                    scanf("%d",&choice);
                       if(choice==1){
                       	map=createMap(5,5,1);
                        runAutomaticMode(map,5,5,player);
					   }
					   else if(choice==2){
					   	map=createMap(6,10,2);
                       	runAutomaticMode(map,6,10,player);
					   }
					   else if(choice==3){
					   	map=createMap(12,10,3);
                       	runAutomaticMode(map,12,10,player);
					   }
					   else if(choice==4){
					   	  printf("Rows?\n");
					   	  scanf("%d",&rows);
					   	  printf("Cols?\n");
					   	  scanf("%d",&cols);
					   	  printf("--");
					   	  map=createMap(rows,cols,choice);
					   	  runAutomaticMode(map,rows,cols,player);
					   }
                      	else{
                      		printf("Invalid section.Try Again\n");
						  }
                     	
					}
            
                } 
				else {
                    printf("You must log in first\n");
                }
                break;
            case 7:
                printf("Exiting the game...\n");
                break;
            default:
                printf("Invalid selection. Try again.\n");
        }
    } while (choice != 7);

    // Belleði temizle
    free(db);

    // Kullanýcý veritabanýný dosyadan yükleme
    UserDatabase *loadedDb = loadUserDatabaseFromFile();

    // Yüklendikten sonra kullanýcýlarý kontrol etme
    for (i = 0; i < loadedDb->userCount; i++) {
        printf("Username: %s\n", loadedDb->users[i].username);
    }

    // Belleði temizle
    free(loadedDb);
    for(i=0;i<20;i++){
    	free(map[i]);
	}
	free (map);

    return 0;
}
