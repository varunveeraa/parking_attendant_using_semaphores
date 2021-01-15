#include<stdio.h> #include<stdlib.h> #include <conio.h> #include <time.h> #include <semaphore.h> #define CAR 1#define SCOOTER 2 void delay(int n); struct vehicle{int num ; int row ; int col ; int type ;} ;int k=1; void V(); void P();#define MAX 10int top =-1;int waitqueue[MAX]; int parkdetails[4][10] ; int count_of_veh ;int count_of_car ; int count_of_sc ; void display(); void display_wq();void changecol ( struct vehicle * ) ; struct vehicle * add ( int, int, int, int ) ;

void del(struct vehicle * );
void getfreerowcol(int, int * );
void getrcbyinfo(int, int, int * );
void show();
void changecol(struct vehicle * v) {
  v -> col = v -> col - 1;
}
struct vehicle * add(int t, int num, int row, int col) {
  struct vehicle * v;
  v = (struct vehicle * ) malloc(sizeof(struct vehicle));
  v -> type = t;
  v -> row = row;
  v -> col = col;
  if (k == 0) {
    {
      printf("\n Wait Queue is full!!");
    }
  } else {
    top = top + 1;
    waitqueue[top] = num;
  }
  if (t == CAR && k == 1) {
    P();
    count_of_car++;
    delay(1);
    parkdetails[row][col] = num;
    count_of_veh++;
    V();
  } else if (t == SCOOTER && k == 1) {
    P();
    count_of_sc++;
    parkdetails[row][col] = num;
    V();
    count_of_veh++;
  }
}
void getfreerowcol(int type, int * arr) {
  int r, c, fromrow = 0, torow = 2;
  if (type == SCOOTER) {
    fromrow += 2;
    torow += 2;
  }
  for (r = fromrow; r < torow; r++) {
    for (c = 0; c < 9; c++) {
      if (parkdetails[r][c] == 0) {
        arr[0] = r;
        arr[1] = c;
        return;
      }
    }
  }
  if (r == 2 || r == 4) {
    arr[0] = -1;
    arr[1] = -1;
  }
} /* get the row-col position forthe vehiclewith specified number */
void getrcbyinfo(int type, int num, int * arr) {
  int r, c, fromrow = 0, torow = 2;
  if (type == SCOOTER) {
    fromrow += 2;
    torow += 2;
  }
  for (r = fromrow; r < torow; r++) {
    for (c = 0; c < 10; c++) {
      if (parkdetails[r][c] == num) {
        arr[0] = r;
        arr[1] = c;
        return;
      }
    }
  }
  if (r == 2 || r == 4) {
    arr[0] = -1;
    arr[1] = -1;
  }
}
void display() {
  int r, c;
  printf("Cars ->\n");
  for (r = 0; r < 4; r++) {
    if (r == 2) printf("Scooters ->\n");
    for (c = 0; c < 9; c++) printf("%d\t", parkdetails[r][c]);
    printf("\n");
  }
}
void display_wq() {
  int i;
  if (top == -1) {
    printf("\nWait Queue is empty!!");
  } else {
    printf("\nWait Queue is...\n");
    for (i = 0; i <= top; i++) printf("%d\t", waitqueue[i]);
  }
}
void main() {
  int choice, type, number, z = 0, row = 0, col = 0;
  int i, tarr[2];
  int finish = 1;
  struct vehicle * v;
  struct vehicle * car[2][10];
  struct vehicle * scooter[2][10];
  while (finish) {
    printf("\n Car Parking\n");
    printf("1. A vehicle has arrived!!\n");
    printf("2. How many vehicles are parked?\n");
    printf("3. How many cars are parked?\n");
    printf("4. How many scooters are parked?\n");
    printf("5. Whats the order the vehicles are parked in?\n");
    printf("6. A vehicle is leaving!!\n");
    printf("7. See the wait queue\n");
    printf("8. Bye bye!!\n");
    scanf("%d", & choice);
    switch (choice) {
    case 1:
      printf("\nYou may add your vehicle here: \n");
      type = 0;
      while (type != CAR && type != SCOOTER) {
        printf("Is your vehicle a scooter or a car (1 for Car / 2 for Scooter ): \n");
        scanf("%d", & type);
        if (type != CAR && type != SCOOTER) printf("\nOops looks like an invalid type.\n");
      }
      printf("We would want your vehicle number: ");
      scanf("%d", & number);
      if (type == CAR || type == SCOOTER) {
        getfreerowcol(type, tarr);
        if (tarr[0] != -1 && tarr[1] != -1) {
          row = tarr[0];
          col = tarr[1];
          if (type == CAR) car[row][col] = add(type, number, row, col);
          else scooter[row - 2][col] = add(type, number, row, col);
        } else {
          if (type == CAR) {
            printf("\nOops seems like there is no parking slot!! However you have been put in the waiting queue\n");
            if (top == MAX - 1) {
              printf("\n Wait Queue is full!!");
            } else {
              top = top + 1;
              waitqueue[top] = number;
            }
          } else {
            printf("\nOops seems like there is no parking slot for your scooter\n");
            if (top == MAX - 1) {
              printf("\n Wait Queue is full!!");
            } else {
              top = top + 1;
              waitqueue[top] = number;
            }
          }
        }
      } else {
        printf("Oops seems like an invalid type\n");
        break;
      }
      printf("\nU may press any key to continue");
      getch();
      break;
    case 2:
      printf("The total number of vehicles parked are: %d\n", count_of_veh);
      printf("\nU may press any key to continue");
      getch();
      break;
    case 3:
      printf("The total number of cars parked are: %d\n", count_of_car);
      printf("\nU may press any key to continue");
      getch();
      break;
    case 4:
      printf("The total number of scooters parked are: %d\n", count_of_sc);
      printf("\nU may press any key to continue");
      getch();
      break;
    case 5:
      printf("This is what the final display looks like\n");
      display();
      printf("\nU may press any key to continue");
      getch();
      break;
    case 6:
      printf("Departure\n");
      type = 0;
      18
      while (type != CAR && type != SCOOTER) {
        printf("Is your vehicle a scooter or a car (1 for Car / 2 for Scooter ): \n");
        scanf("%d", & type);
        if (type != CAR && type != SCOOTER) printf("\nOops looks like an invalid type.\n");
      }
      printf("We would want your vehicle number: ");
      scanf("%d", & number);
      if (type == CAR || type == SCOOTER) {
        getrcbyinfo(type, number, tarr);
        if (tarr[0] != -1 && tarr[1] != -1) {
          col = tarr[1];
          if (type == CAR) {
            row = tarr[0];
            free(car[row][col]);
            if (top != -1) {
              parkdetails[row][col] = waitqueue[0];
              for (i = 0; i < top; i++) {
                waitqueue[i] = waitqueue[i + 1];
              }
              top--;
            }
            elseparkdetails[row][col] = 0;
          } else {
            row = tarr[0] - 2;
            if (!(row < 0)) {
              free(scooter[row][col]);
              if (top != -1) {
                parkdetails[row][col] = waitqueue[0];
                for (i = 0; i < top; i++) {
                  waitqueue[i] = waitqueue[i + 1];
                }
                top--;
              }
              elseparkdetails[row][col] = 0;
            }
          }
        } else {
          if (type == CAR) printf("\nOops looks like an invalid car number\n");
          else printf("\nOops looks like an invalid scooter number\n");
        }
      }
      printf("\nU may press any key to continue");
      getch();
      break;
    case 7:
      printf("This is what the final display looks like \n");
      display_wq();
      printf("\nU may press any key to continue");
      getch();
      break;
    case 8:
      for (row = 0; row < 2; row++) {
        for (col = 0; col < 10; col++) {
          if (car[row][col] -> num != 0) free(car[row][col]);
          if (scooter[row][col] -> num != 0) free(scooter[row + 2][col]);
        }
      }
      finish = 0;
      break;
    }
  }
}
void delay(int n) {
  int ms = 1000 * n;
  clock_t start_time = clock();
}
void P() {
  printf("Vehicle is Parking.\n");
  if (k == 0) {
    printf("Please wait for a while as another vehicle is in the process");
  } else {
    k = k - 1;
  }
}
void V() {
  k = k + 1;
}