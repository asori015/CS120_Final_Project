// NOTE THIS CAN ONLY BE USED ON A MEGA! NOT ENOUGH RAM ON UNO!

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <avr/pgmspace.h> 

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

int song1[][4] = {{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4},{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4}};

//int song1[][4] = {{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4},{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4},{0,2,0,0},{0,0,3,0},
//                   {1,0,0,0},{0,0,0,4},{0,0,3,0},{0,0,3,0},{0,2,0,0},{0,2,0,0},{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4},
//                   {1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4},{0,2,0,0},{0,0,3,0},{1,0,0,0},{0,0,0,4},{0,0,3,0},{0,0,3,0},
//                   {0,2,0,0},{0,2,0,0}};

//                   {0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,1,0},{0,1,0,0},
//                   {0,0,0,1},{1,0,0,0},{0,1,0,0},{0,1,0,0},{0,0,1,0},{0,0,1,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},
//                   {0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,1,0,0},
//                   {0,0,1,0},{0,0,1,0}};

int song2[][4] = {{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4},{1,0,3,0},{0,2,0,4},{1,0,3,0},{0,2,0,4},{0,2,0,0},{0,0,3,0},
                   {1,0,0,4},{1,0,0,4},{0,2,3,0},{0,2,3,0},{1,2,0,0},{0,0,4,3},{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4},
                   {1,2,0,0},{0,2,3,0},{0,0,3,4},{1,0,0,4},{0,2,0,0},{0,0,3,0},{1,0,0,0},{0,0,0,4},{1,0,0,4},{0,2,3,0},
                   {1,0,0,4},{0,2,3,0}};

int song3[1][4];

int row1 = -7;
int row2 = row1 - 14;
int row3 = row2 - 14;
int row4 = row3 - 14;
int row5 = row4 - 14;
int row6 = row5 - 14;
int row7 = row6 - 14;
int row8 = row7 - 14;
int row9 = row8 - 14;
int row10 = row9 - 14;

int col1 = 0;
int col2 = 1;
int col3 = 2;
int col4 = 3;
int col5 = 4;
int col6 = 5;
int col7 = 6;
int col8 = 7;
int col9 = 8;
int col10 = 9;

void setup() {

  matrix.begin();
  matrix.fillScreen(matrix.Color333(1,0,0));
  Serial.begin(9600);
}

void drawArrow(int x, int y, int dir){
  //right
  if(dir == 1){
    matrix.drawPixel(1 + x, y, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y, matrix.Color333(0,0,7));

    matrix.drawPixel(0 + x, y + 1, matrix.Color333(1,0,0));
    matrix.drawPixel(1 + x, y + 1, matrix.Color333(0,0,7));
    matrix.drawPixel(2 + x, y + 1, matrix.Color333(0,0,7));
    matrix.drawPixel(3 + x, y + 1, matrix.Color333(0,0,7));

    matrix.drawPixel(-1 + x, y + 2, matrix.Color333(1,0,0));
    matrix.drawPixel(0 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(1 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(2 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(3 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(4 + x, y + 2, matrix.Color333(0,0,7));

    matrix.drawPixel(1 + x, y + 3, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y + 3, matrix.Color333(0,0,7));
    
    matrix.drawPixel(1 + x, y + 4, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y + 4, matrix.Color333(0,0,7));
  }
  //up
  else if(dir == 2){
    matrix.drawPixel(1 + x, y, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y, matrix.Color333(0,0,7));

    matrix.drawPixel(0 + x, y + 1, matrix.Color333(1,0,0));
    matrix.drawPixel(1 + x, y + 1, matrix.Color333(0,0,7));
 
    matrix.drawPixel(-1 + x, y + 2, matrix.Color333(1,0,0));
    matrix.drawPixel(0 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(1 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(2 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(3 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(4 + x, y + 2, matrix.Color333(0,0,7));

    matrix.drawPixel(0 + x, y + 3, matrix.Color333(1,0,0));
    matrix.drawPixel(1 + x, y + 3, matrix.Color333(0,0,7));

    matrix.drawPixel(1 + x, y + 4, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y + 4, matrix.Color333(0,0,7));
  }
  //down
  else if(dir == 3){
    matrix.drawPixel(1 + x, y, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y, matrix.Color333(0,0,7));

    matrix.drawPixel(2 + x, y + 1, matrix.Color333(1,0,0));
    matrix.drawPixel(3 + x, y + 1, matrix.Color333(0,0,7));
 
    matrix.drawPixel(-1 + x, y + 2, matrix.Color333(1,0,0));
    matrix.drawPixel(0 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(1 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(2 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(3 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(4 + x, y + 2, matrix.Color333(0,0,7));

    matrix.drawPixel(2 + x, y + 3, matrix.Color333(1,0,0));
    matrix.drawPixel(3 + x, y + 3, matrix.Color333(0,0,7));

    matrix.drawPixel(1 + x, y + 4, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y + 4, matrix.Color333(0,0,7));
  }
  //left
  else if(dir == 4){
    matrix.drawPixel(1 + x, y, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y, matrix.Color333(0,0,7));

    matrix.drawPixel(1 + x, y + 1, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y + 1, matrix.Color333(0,0,7));
 
    matrix.drawPixel(-1 + x, y + 2, matrix.Color333(1,0,0));
    matrix.drawPixel(0 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(1 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(2 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(3 + x, y + 2, matrix.Color333(0,0,7));
    matrix.drawPixel(4 + x, y + 2, matrix.Color333(0,0,7));

    matrix.drawPixel(0 + x, y + 3, matrix.Color333(1,0,0));
    matrix.drawPixel(1 + x, y + 3, matrix.Color333(0,0,7));
    matrix.drawPixel(2 + x, y + 3, matrix.Color333(0,0,7));
    matrix.drawPixel(3 + x, y + 3, matrix.Color333(0,0,7));

    matrix.drawPixel(1 + x, y + 4, matrix.Color333(1,0,0));
    matrix.drawPixel(2 + x, y + 4, matrix.Color333(0,0,7));
  }
  else{
    return;
  }
}

int i = 0;
bool yes = false;
bool song_1 = false;
bool song_2 = false;
bool song_3 = false;
int change = 0;
void loop() {
  //  send data only when you receive data:
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    if(incomingByte == 5){
      yes = true;
      row1 = -7;
      row2 = row1 - 14;
      row3 = row2 - 14;
      row4 = row3 - 14;
      row5 = row4 - 14;
      row6 = row5 - 14;
      row7 = row6 - 14;
      row8 = row7 - 14;
      row9 = row8 - 14;
      row10 = row9 - 14;
      col1 = 0;
      col2 = 1;
      col3 = 2;
      col4 = 3;
      col5 = 4;
      col6 = 5;
      col7 = 6;
      col8 = 7;
      col9 = 8;
      col10 = 9;
      song_1 = true;
      song_2 = false;
      song_3 = false;
      i = 0;
    }
    if(incomingByte == 6){
      yes = true;
      row1 = -7;
      row2 = row1 - 14;
      row3 = row2 - 14;
      row4 = row3 - 14;
      row5 = row4 - 14;
      row6 = row5 - 14;
      row7 = row6 - 14;
      row8 = row7 - 14;
      row9 = row8 - 14;
      row10 = row9 - 14;
      col1 = 0;
      col2 = 1;
      col3 = 2;
      col4 = 3;
      col5 = 4;
      col6 = 5;
      col7 = 6;
      col8 = 7;
      col9 = 8;
      col10 = 9;
      song_1 = false;
      song_2 = true;
      song_3 = false;
      i = 0;
    }
    if(incomingByte == 7){
      yes = true;
      row1 = -7;
      row2 = row1 - 14;
      row3 = row2 - 14;
      row4 = row3 - 14;
      row5 = row4 - 14;
      row6 = row5 - 14;
      row7 = row6 - 14;
      row8 = row7 - 14;
      row9 = row8 - 14;
      row10 = row9 - 14;
      col1 = 0;
      col2 = 1;
      col3 = 2;
      col4 = 3;
      col5 = 4;
      col6 = 5;
      col7 = 6;
      col8 = 7;
      col9 = 8;
      col10 = 9;
      song_1 = false;
      song_2 = false;
      song_3 = true;
      i = 0;
    }
    else if(incomingByte == 2){
      yes = false;
    }
    else if(incomingByte == 3){
      yes = true;
    }
    else if(incomingByte == 4){
      yes = false;
      matrix.fillScreen(matrix.Color333(1,0,0));
    }
  }

  if(yes && song_1){
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row1, 4, song1[col1][0]);
      drawArrow(row1, 11, song1[col1][1]);
      drawArrow(row1, 18, song1[col1][2]);
      drawArrow(row1, 25, song1[col1][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row2, 4, song1[col2][0]);
      drawArrow(row2, 11, song1[col2][1]);
      drawArrow(row2, 18, song1[col2][2]);
      drawArrow(row2, 25, song1[col2][3]);
    }
  
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row3, 4, song1[col3][0]);
      drawArrow(row3, 11, song1[col3][1]);
      drawArrow(row3, 18, song1[col3][2]);
      drawArrow(row3, 25, song1[col3][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row4, 4, song1[col4][0]);
      drawArrow(row4, 11, song1[col4][1]);
      drawArrow(row4, 18, song1[col4][2]);
      drawArrow(row4, 25, song1[col4][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row5, 4, song1[col5][0]);
      drawArrow(row5, 11, song1[col5][1]);
      drawArrow(row5, 18, song1[col5][2]);
      drawArrow(row5, 25, song1[col5][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row6, 4, song1[col6][0]);
      drawArrow(row6, 11, song1[col6][1]);
      drawArrow(row6, 18, song1[col6][2]);
      drawArrow(row6, 25, song1[col6][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row7, 4, song1[col7][0]);
      drawArrow(row7, 11, song1[col7][1]);
      drawArrow(row7, 18, song1[col7][2]);
      drawArrow(row7, 25, song1[col7][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row8, 4, song1[col8][0]);
      drawArrow(row8, 11, song1[col8][1]);
      drawArrow(row8, 18, song1[col8][2]);
      drawArrow(row8, 25, song1[col8][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row9, 4, song1[col9][0]);
      drawArrow(row9, 11, song1[col9][1]);
      drawArrow(row9, 18, song1[col9][2]);
      drawArrow(row9, 25, song1[col9][3]);
    }
    if(i < sizeof(song1)/sizeof(song1[0])){
      drawArrow(row10, 4, song1[col10][0]);
      drawArrow(row10, 11, song1[col10][1]);
      drawArrow(row10, 18, song1[col10][2]);
      drawArrow(row10, 25, song1[col10][3]);
    }
  
    if(row1 >= 65){
      row1 = row10 - 14;
      col1 += 10;
      i++;
    }
    if(row2 >= 65){
      row2 = row1 - 14;
      col2 += 10;
      i++;
    }
    if(row3 >= 65){
      row3 = row2 - 14;
      col3 += 10;
      i++;
    }
    if(row4 >= 65){
      row4 = row3 - 14;
      col4 += 10;
      i++;
    }
    if(row5 >= 65){
      row5 = row4 - 14;
      col5 += 10;
      i++;
    }
    if(row6 >= 65){
      row6 = row5 - 14;
      col6 += 10;
      i++;
    }
    if(row7 >= 65){
      row7 = row6 - 14;
      col7 += 10;
      i++;
    }
    if(row8 >= 65){
      row8 = row7 - 14;
      col8 += 10;
      i++;
    }
    if(row9 >= 65){
      row9 = row8 - 14;
      col9 += 10;
      i++;
    }
    if(row10 >= 65){
      row10 = row9 - 14;
      col10 += 10;
      i++;
    }
    
    row1++;
    row2++;
    row3++;
    row4++;
    row5++;
    row6++;
    row7++;
    row8++;
    row9++;
    row10++;
  }

  if(yes && song_2){
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row1, 4, song2[col1][0]);
      drawArrow(row1, 11, song2[col1][1]);
      drawArrow(row1, 18, song2[col1][2]);
      drawArrow(row1, 25, song2[col1][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row2, 4, song2[col2][0]);
      drawArrow(row2, 11, song2[col2][1]);
      drawArrow(row2, 18, song2[col2][2]);
      drawArrow(row2, 25, song2[col2][3]);
    }
  
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row3, 4, song2[col3][0]);
      drawArrow(row3, 11, song2[col3][1]);
      drawArrow(row3, 18, song2[col3][2]);
      drawArrow(row3, 25, song2[col3][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row4, 4, song2[col4][0]);
      drawArrow(row4, 11, song2[col4][1]);
      drawArrow(row4, 18, song2[col4][2]);
      drawArrow(row4, 25, song2[col4][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row5, 4, song2[col5][0]);
      drawArrow(row5, 11, song2[col5][1]);
      drawArrow(row5, 18, song2[col5][2]);
      drawArrow(row5, 25, song2[col5][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row6, 4, song2[col6][0]);
      drawArrow(row6, 11, song2[col6][1]);
      drawArrow(row6, 18, song2[col6][2]);
      drawArrow(row6, 25, song2[col6][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row7, 4, song2[col7][0]);
      drawArrow(row7, 11, song2[col7][1]);
      drawArrow(row7, 18, song2[col7][2]);
      drawArrow(row7, 25, song2[col7][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row8, 4, song2[col8][0]);
      drawArrow(row8, 11, song2[col8][1]);
      drawArrow(row8, 18, song2[col8][2]);
      drawArrow(row8, 25, song2[col8][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row9, 4, song2[col9][0]);
      drawArrow(row9, 11, song2[col9][1]);
      drawArrow(row9, 18, song2[col9][2]);
      drawArrow(row9, 25, song2[col9][3]);
    }
    if(i < sizeof(song2)/sizeof(song2[0])){
      drawArrow(row10, 4, song2[col10][0]);
      drawArrow(row10, 11, song2[col10][1]);
      drawArrow(row10, 18, song2[col10][2]);
      drawArrow(row10, 25, song2[col10][3]);
    }
  
    if(row1 >= 65){
      row1 = row10 - 14;
      col1 += 10;
      i++;
    }
    if(row2 >= 65){
      row2 = row1 - 14;
      col2 += 10;
      i++;
    }
    if(row3 >= 65){
      row3 = row2 - 14;
      col3 += 10;
      i++;
    }
    if(row4 >= 65){
      row4 = row3 - 14;
      col4 += 10;
      i++;
    }
    if(row5 >= 65){
      row5 = row4 - 14;
      col5 += 10;
      i++;
    }
    if(row6 >= 65){
      row6 = row5 - 14;
      col6 += 10;
      i++;
    }
    if(row7 >= 65){
      row7 = row6 - 14;
      col7 += 10;
      i++;
    }
    if(row8 >= 65){
      row8 = row7 - 14;
      col8 += 10;
      i++;
    }
    if(row9 >= 65){
      row9 = row8 - 14;
      col9 += 10;
      i++;
    }
    if(row10 >= 65){
      row10 = row9 - 14;
      col10 += 10;
      i++;
    }
    
    row1++;
    row2++;
    row3++;
    row4++;
    row5++;
    row6++;
    row7++;
    row8++;
    row9++;
    row10++;
  }

  if(yes && song_3){
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row1, 4, song3[col1][0]);
      drawArrow(row1, 11, song3[col1][1]);
      drawArrow(row1, 18, song3[col1][2]);
      drawArrow(row1, 25, song3[col1][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row2, 4, song3[col2][0]);
      drawArrow(row2, 11, song3[col2][1]);
      drawArrow(row2, 18, song3[col2][2]);
      drawArrow(row2, 25, song3[col2][3]);
    }
  
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row3, 4, song3[col3][0]);
      drawArrow(row3, 11, song3[col3][1]);
      drawArrow(row3, 18, song3[col3][2]);
      drawArrow(row3, 25, song3[col3][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row4, 4, song3[col4][0]);
      drawArrow(row4, 11, song3[col4][1]);
      drawArrow(row4, 18, song3[col4][2]);
      drawArrow(row4, 25, song3[col4][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row5, 4, song3[col5][0]);
      drawArrow(row5, 11, song3[col5][1]);
      drawArrow(row5, 18, song3[col5][2]);
      drawArrow(row5, 25, song3[col5][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row6, 4, song3[col6][0]);
      drawArrow(row6, 11, song3[col6][1]);
      drawArrow(row6, 18, song3[col6][2]);
      drawArrow(row6, 25, song3[col6][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row7, 4, song3[col7][0]);
      drawArrow(row7, 11, song3[col7][1]);
      drawArrow(row7, 18, song3[col7][2]);
      drawArrow(row7, 25, song3[col7][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row8, 4, song3[col8][0]);
      drawArrow(row8, 11, song3[col8][1]);
      drawArrow(row8, 18, song3[col8][2]);
      drawArrow(row8, 25, song3[col8][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row9, 4, song3[col9][0]);
      drawArrow(row9, 11, song3[col9][1]);
      drawArrow(row9, 18, song3[col9][2]);
      drawArrow(row9, 25, song3[col9][3]);
    }
    if(i < sizeof(song3)/sizeof(song3[0])){
      drawArrow(row10, 4, song3[col10][0]);
      drawArrow(row10, 11, song3[col10][1]);
      drawArrow(row10, 18, song3[col10][2]);
      drawArrow(row10, 25, song3[col10][3]);
    }
  
    if(row1 >= 65){
      row1 = row10 - 14;
      col1 += 10;
      i++;
    }
    if(row2 >= 65){
      row2 = row1 - 14;
      col2 += 10;
      i++;
    }
    if(row3 >= 65){
      row3 = row2 - 14;
      col3 += 10;
      i++;
    }
    if(row4 >= 65){
      row4 = row3 - 14;
      col4 += 10;
      i++;
    }
    if(row5 >= 65){
      row5 = row4 - 14;
      col5 += 10;
      i++;
    }
    if(row6 >= 65){
      row6 = row5 - 14;
      col6 += 10;
      i++;
    }
    if(row7 >= 65){
      row7 = row6 - 14;
      col7 += 10;
      i++;
    }
    if(row8 >= 65){
      row8 = row7 - 14;
      col8 += 10;
      i++;
    }
    if(row9 >= 65){
      row9 = row8 - 14;
      col9 += 10;
      i++;
    }
    if(row10 >= 65){
      row10 = row9 - 14;
      col10 += 10;
      i++;
    }
    
    row1++;
    row2++;
    row3++;
    row4++;
    row5++;
    row6++;
    row7++;
    row8++;
    row9++;
    row10++;
  }

  matrix.drawLine(0, 3, matrix.width()-1, 3, matrix.Color333(7, 7, 7));
  matrix.drawLine(0, 16, matrix.width()-1, 16, matrix.Color333(7, 7, 7));

  delay(50);
}
