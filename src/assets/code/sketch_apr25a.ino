#include "HT1632.h"
#include <Wire.h>
#include "RTClib.h"

#define DATA 2
#define WR   3
#define CS   4

HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS); //Define the LED matrix
RTC_DS1307 RTC; //Define the Real Time Clock

//define global variables
byte running_program;
byte menu_item;
byte main_menu_program_state;
byte temp_program_state;
byte time_program_state;
byte tetris_program_state;
byte photo_program_state;
byte animation_program_state;
byte snake_program_state;
int parsed_digits[4];
boolean joy_reset;
boolean joy_reset_x;
boolean joy_reset_y;
boolean sel_reset;
boolean write_to_matrix;
byte prev_home_value;
byte dimmer_enabled;
byte first_digit_id;
byte second_digit_id;

int y_value = 0;
int x_value = 0;

//define pin constants
const byte temperaturePin = 0;
const int y_pin = A3;
const int x_pin = A2;
const byte sel_pin = 7;
const byte home_pin = 8;
const byte light_pin = 1;
const byte data_one = 9; 
const byte data_two = 10; 
const byte clock = 11;
const byte latch = 12;

int speakerPin = 5;


PROGMEM prog_uint16_t chars_five[21][5] = { //All the images used with 5-bit height
 {7,5,5,5,7}, //zero 3-bit
 {1,3,1,1,1}, //1
 {7,1,7,4,7}, //2
 {7,1,7,1,7}, //3
 {5,5,7,1,1}, //4
 {7,4,7,1,7}, //5
 {7,4,7,5,7}, //6
 {7,1,1,1,1}, //7
 {7,5,7,5,7}, //8
 {7,5,7,1,7}, //9
 {0,0,0,0,0}, //null 3-bit
 {60695,18869,19799,18708,19732}, //temp 16-bit
 {44683,43738,60075,43658,44683}, //home 16-bit
 {14987,4826,4779,4746,4747}, //time 14-bit
 {6,5,6,4,4}, //3-bit p
 {2,5,7,5,5}, //3-bit a
 {12603,10898,11155,10898,12947}, //date 14-bit
 {62091,34266,47019,38282,62859}, //GAME
 {4790,10917,10934,10917,4405}, //OVER
 {1,2,20,8,0}, //Check Mark
 {17,10,4,10,17} //X
};

PROGMEM prog_uint16_t chars_six[9][6] = { //All the images used with 6-bit height
  {59152,23255,21172,23255,21169,6311}, //Tetris
  {12451,10942,13747,10174,9703,1308}, //pause
  {12,18,33,33,18,12}, //clock
  {30,49,41,37,37,30}, //time
  {8,8,8,28,20,28}, //temp
  {16,24,8,2,51,63}, //tetris
  {0,30,18,16,18,16}, //snake
  {0,18,12,12,18,0}, //dim
  {25031,23421,27477,20309,19415,2576} //photo
};

//Frames for the funky animation program
PROGMEM prog_uint16_t frames[35][16]=
{
  {65535, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 65535},
  {16386, 65535, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 65535, 16386},
  {8196, 8196, 65535, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 65535, 8196, 8196}, 
  {4104, 4104, 4104, 65535, 4104, 4104, 4104, 4104, 4104, 4104, 4104, 4104, 65535, 4104, 4104, 4104}, 
  {2064, 2064, 2064, 2064, 65535, 2064, 2064, 2064, 2064, 2064, 2064, 65535, 2064, 2064, 2064, 2064}, 
  {1056, 1056, 1056, 1056, 1056, 65535, 1056, 1056, 1056, 1056, 65535, 1056, 1056, 1056, 1056, 1056},
  {576, 576, 576,  576, 576, 576, 65535, 576, 576, 65535, 576, 576, 576, 576, 576, 576},
  {384, 384, 384, 384, 384, 384, 384, 65535, 65535, 384, 384, 384, 384, 384, 384, 384},
  {576, 576, 576,  576, 576, 576, 65535, 576, 576, 65535, 576, 576, 576, 576, 576, 576},
  {1056, 1056, 1056, 1056, 1056, 65535, 1056, 1056, 1056, 1056, 65535, 1056, 1056, 1056, 1056, 1056},
  {2064, 2064, 2064, 2064, 65535, 2064, 2064, 2064, 2064, 2064, 2064, 65535, 2064, 2064, 2064, 2064}, 
  {4104, 4104, 4104, 65535, 4104, 4104, 4104, 4104, 4104, 4104, 4104, 4104, 65535, 4104, 4104, 4104}, 
  {8196, 8196, 65535, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 65535, 8196, 8196}, 
  {16386, 65535, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 16386, 65535, 16386},
  {65535, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 32769, 65535},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0},  
  { 0, 0, 0, 0, 0, 0, 0, 384, 384, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 384, 576, 576, 384, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 384, 576, 1056, 1056, 576, 384, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 384, 576, 1056, 2064, 2064, 1056, 576, 384, 0, 0, 0, 0},
  {0, 0, 0, 384, 576, 1056, 2064, 4104, 4104, 2064, 1056, 576, 384, 0, 0, 0},
  {0, 0, 384, 576, 1056, 2064, 4104, 8196, 8196, 4104, 2064, 1056, 576, 384, 0, 0},
  {0, 384, 576, 1056, 2064, 4104, 8196, 16386, 16386, 8196, 4104, 2064, 1056, 576, 384, 0},
  {384, 576, 1056, 2064, 4104, 8196, 16386, 32769, 32769, 16386, 8196, 4104, 2064, 1056, 576, 384},  
  {384, 960, 1632, 3120, 6168, 12300, 24582, 49155, 49155, 24582, 12300, 6168, 3120, 1632, 960, 384},
  {384, 960, 2016, 3696, 7224, 14364, 28686, 57351, 57351, 28686, 14364, 7224, 3696, 2016, 960, 384},
  {384, 960, 2016, 4080, 7800, 15420, 30750, 61455, 61455, 30750, 15420, 7800, 4080, 2016, 960, 384},
  {384, 960, 2016, 4080, 8184, 15996, 31806, 63519, 63519, 31806, 15996, 8184, 4080, 2016, 960, 384},
  {384, 960, 2016, 4080, 8184, 16380, 32382, 64575, 64575, 32382, 16380, 8184, 4080, 2016, 960, 384},
  {384, 960, 2016, 4080, 8184, 16380, 32766, 65151, 65151, 32766, 16380, 8184, 4080, 2016, 960, 384},
  {384, 960, 2016, 4080, 8184, 16380, 32766, 65535, 65535, 32766, 16380, 8184, 4080, 2016, 960, 384},
  {65151, 64575, 63519, 61455, 57351, 49155, 32769, 0, 0, 32769, 49155, 57351, 61455, 63519, 64575, 65151}, 
  {384, 960, 2016, 4080, 8184, 16380, 32766, 65535, 65535, 32766, 16380, 8184, 4080, 2016, 960, 384},
  {65151, 64575, 63519, 61455, 57351, 49155, 32769, 0, 0, 32769, 49155, 57351, 61455, 63519, 64575, 65151},
  {384, 960, 2016, 4080, 8184, 16380, 32766, 65535, 65535, 32766, 16380, 8184, 4080, 2016, 960, 384}
};

//constants defining characters for the 7-segment displays
const byte display_one[11] =
{
  235, //0
  136, //1
  199, //2
  206, //3
  172, //4
  110, //5
  111, //6
  200, //7
  239, //8
  238, //9
  0 //null
};

const byte display_two[18] =
{
  119, //0
  6, //1
  242, //2
  230, //3
  135, //4
  229, //5
  245, //6
  70, //7
  247, //8
  231, //9
  0, //null
  180, //square
  6, //I
  49, //L
  38, //L inverted
  146,  //N inverted
  133, //N
  145 //T
  
};

//Tetris pieces, 7 pieces, 4 rotation orientations, 5 rows
//Design was inspired from this site: http://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/
PROGMEM prog_uint16_t pieces[7][4][5] = 
{
  {
    {0,0,6,6,0}, //square
    {0,0,6,6,0},
    {0,0,6,6,0},
    {0,0,6,6,0}
  },
  {
    {0,0,15,0,0}, //I
    {0,4,4,4,4},
    {0,0,30,0,0},
    {4,4,4,4,0}
  },
  {
    {0,4,4,6,0}, //L
    {0,0,14,8,0},
    {0,12,4,4,0},
    {0,2,14,0,0}
  },
  {
    {0,4,4,12,0}, //L mirrored
    {0,8,14,0,0},
    {0,6,4,4,0},
    {0,0,14,2,0}
  },
  {
    {0,2,6,4,0}, //N
    {0,0,12,6,0},
    {0,4,12,8,0},
    {0,12,6,0,0}
  },
  {
    {0,4,6,2,0}, //N Mirrored
    {0,0,6,12,0},
    {0,8,12,4,0},
    {0,6,12,0,0}
  },
  {
    {0,4,6,4,0}, //T
    {0,0,14,4,0},
    {0,4,12,4,0},
    {0,4,14,0,0}
  }
  
};

//The tetris board
unsigned int board[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//Tetris variables
const signed char initial_position[2]={6,-4};
byte current_piece;
byte current_rotation;
byte next_piece;
signed char current_piece_location[2];
byte score;

//Music Variables
char names[] = { 'C',  'K',  'D',  'M',  'E',  'F',  'N',  'G',  'P',  'A',  'V',  'S',  'B', 'c',  'k', 'd',  'm', 'e', 'u', 'f',  'n', 'g',  'h', 'p', 'a', 'v',  's', 'b'};

int tones[] = { 1911, 1804, 1703, 1607, 1517, 1432, 1352, 1276, 1204, 1136, 1100, 1073, 1012, 955,  902, 851,  803, 758, 737, 716,  676, 638,  618, 602, 568, 552,  536, 506};

byte tetrisLength = 100;
char tetris[] = "AEFGAGFEDDFAGFEFGAFDD GSdcSAFAGFEEFGAFDD AEFGAGFEDDFAGFEFGAFDD GSdcSAFAGFEEFGAFDD AFGEFDKE AFGEFAdk "; // a space represents a rest
byte tetrisbeats[] = { 4, 2, 2, 2, 1, 1, 2, 2, 4, 2, 2, 4, 2, 2, 6, 2, 4, 4, 4, 4, 8,   2,   4, 2, 4, 2, 2, 6, 2, 4, 2, 2, 4, 2, 2, 4, 4, 4, 4, 4,   4,   4, 2, 2, 2, 1, 1, 2, 2, 4, 2, 2, 4, 2, 2, 6, 2, 4, 4, 4, 4, 8,   2,   4, 2, 4, 2, 2, 6, 2, 4, 2, 2, 4, 2, 2, 4, 4, 4, 4, 4,   4,   8, 8, 8, 8, 8, 8, 8, 4,   4,   8, 8, 8, 8, 4, 4, 8, 8,   8, 4, 2, 2, 2, 1, 1, 2, 2, 4, 2, 2, 4, 2, 2, 6, 2, 4, 4, 4, 4, 8,   2,   4, 2, 4, 2, 2, 6, 2, 4, 2, 2, 4, 2, 2, 4, 4, 4, 4, 4,   4,   4, 2, 2, 2, 1, 1, 2, 2, 4, 2, 2, 4, 2, 2, 6, 2, 4, 4, 4, 4, 8,   2,   4, 2, 4, 2, 2, 6, 2, 4, 2, 2, 4, 2, 2, 4, 4, 4, 4, 4,   4 };
byte tetrisTempo = 85;

byte Chocobo_length = 98;
char Chocobo_notes[] = "dBGEdBGBGBAGGAGFGFGGBdefdBGEdBGBGBAGGAGFGFGGBdefecANAcedgdBcANDNAcBBcBABecANAcedgdBAABAGAGAABcde n";
byte Chocobo_beats[] = { 4, 2, 2, 2, 2, 2, 2, 4, 4, 6, 2, 2, 1, 1, 2, 2, 6, 2, 2, 1, 1, 2, 2, 8, 4, 2, 2, 2, 2, 2, 2, 4, 4, 6, 2, 2, 1, 1, 2, 2, 6, 2, 2, 1, 1, 2, 2, 8, 4, 2, 2, 2, 2, 2, 2, 4, 4, 6, 2, 4, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 8, 4, 2, 2, 2, 2, 2, 2, 4, 4, 6, 2, 2, 1, 1, 2, 2, 6, 2, 2, 1, 1, 2, 2, 2, 2, 4 };
byte Chocobo_tempo = 100;
  
//Snake variables  
byte snake_score, snake_length, firstpress, snake_direction, snake_eat;
byte snake_board[24][16];
byte snake_fruit[2];

void setup() {
  
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS); 
  Wire.begin();
  RTC.begin();
  
  pinMode(sel_pin, INPUT);
  pinMode(home_pin, INPUT); 
  pinMode(speakerPin, OUTPUT);
  
  pinMode(data_one, OUTPUT);
  pinMode(data_two, OUTPUT);
  pinMode(clock, OUTPUT);  
  pinMode(latch, OUTPUT); 
  
  digitalWrite(speakerPin, LOW); //Turn off the piezo just in case
  
  //Initialize all the variables
  main_menu_program_state = 0;
  temp_program_state = 0;
  time_program_state = 0;
  tetris_program_state = 0;
  animation_program_state = 0;
  snake_program_state = 0;
  score = 0;
  photo_program_state = 0;
  joy_reset = 1;
  joy_reset_x = 1;
  joy_reset_y = 1;
  sel_reset = 1;
  write_to_matrix = 0;
  running_program = 6;
  dimmer_enabled = 1;
  
  first_digit_id = 10; //Turn LED segments off
  second_digit_id = 10;
  write_to_display();
  
  home_value(); //reset home button
  
  //Randomize the randomizer based on the time
  DateTime now = RTC.now();
  randomSeed(now.unixtime());
  
  next_piece = random(7); //Set the next tetris piece already
  
  delay(100); //Delay for safety
  matrix.clearScreen(); //Clear the screen
  
}

void loop() {
  
  //Switch to the currently running program
  switch(running_program)
  {
    case(0):funky_program();break;
    case(1):time_program();break;
    case(2):temperature_program();break;
    case(3):tetris_program();break;
    case(4):snake_program();break;
    case(5):photo_program();break;
    case(6):main_menu_program();break;
    default:main_menu_program();
  }

  //check to see if the select button has been reset
  if(!sel_reset)
  {
    sel_reset = select_value();
  }
  
  //run the dimmer to adjust screen brightness if it is enabled
  if(dimmer_enabled)
  {
    background_dimmer();
  }
  
  delay(10);
}


void main_menu_program()
{
  //menu items icon positions
  byte item_pos[6][2] = {
    {0,8},{0,0},{8,8},{8,0},{16,8},{16,0}
  };
  
  if(main_menu_program_state == 0)
  {
    //initialize the menu
    
    //Turn LED segments off
    first_digit_id = 10; 
    second_digit_id = 10;
    write_to_display();
  
    matrix.clearScreen(); //clear screen
    menu_item = 0; //select the first item
    //Write the icons
    write_char_six(2,9,1,6);
    write_char_six(3,1,1,6);
    write_char_six(4,9,9,6);
    write_char_six(5,1,9,6);
    write_char_six(6,9,17,6);
    write_char_six(7,1,17,6);
    
    matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,1); //draw the cursor
    
    write_to_matrix = 1;
  
    main_menu_program_state = 1;
  }
  else if (main_menu_program_state == 1)
  {
    read_joy_values();
    
    //move the cursur around if the joystick is moved and the direction is legal
    if(joy_reset_x && x_value > 600 && menu_item != 4 && menu_item != 5)
    {
      joy_reset_x = 0;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,0);
      menu_item += 2;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,1);
      write_to_matrix = 1;
    }
    else if(joy_reset_x && x_value < 500 && menu_item != 0 && menu_item != 1)
    {
      joy_reset_x = 0;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,0);
      menu_item -= 2;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,1);
      write_to_matrix = 1;
    }
    
    if(joy_reset_y && y_value > 600 && menu_item != 1 && menu_item != 3 && menu_item != 5)
    {
      joy_reset_y = 0;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,0);
      menu_item += 1;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,1);
      write_to_matrix = 1;
    }
    else if(joy_reset_y && y_value < 500 && menu_item != 0 && menu_item != 2 && menu_item != 4)
    {
      joy_reset_y = 0;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,0);
      menu_item -= 1;
      matrix.drawRect(item_pos[menu_item][0],item_pos[menu_item][1],8,8,1);
      write_to_matrix = 1;
    }
    
     //check for joystuck reset
    if(!joy_reset_x && x_value > 500 && x_value < 600)
    {
      joy_reset_x = 1;
    }
    
    if(!joy_reset_y && y_value > 500 && y_value < 600)
    {
      joy_reset_y = 1;
    }
    
    //run the selected program
    if (!select_value())
    {      
     running_program = menu_item;
     main_menu_program_state = 0;
     sel_reset = 0;
    }
  }

  
  
  //Write to matix
  if (write_to_matrix){
    matrix.writeScreen();
    write_to_matrix = 0;
  }
}

//----------END MENU PROGRAM------------------
//----------BEGIN ANIMATION PROGRAM-----------
void funky_program()
{
  if(!animation_program_state)
  {
    //initialize animation program
    animation_program_state = 1;
    matrix.clearScreen();
  }
  static byte i;
  
  if(i==35){i=0;} //go back to 0
  
  write_char_sixteen(i,0,0,16); //write the current frame
  i+=1;
  matrix.writeScreen();
  delay(90);
  
  //go back to main menu if home button is pressed
  if (!home_value())
  {
    animation_program_state = 0;
    running_program = 6;
  }
}
//----------END ANIMATION PROGRAM-----------
//----------BEGIN TEMPERATURE PROGRAM---------
void temperature_program()
{
  if (temp_program_state == 0)
  {
    //initialize program
    matrix.clearScreen();
    write_char_five(11,0,2,16); //Write "TEMP"
    temp_program_state = 1;
    matrix.writeScreen();
  }
  else if(temp_program_state == 1)
  {
    static int tick_count=0;
    tick_count += 1;
    //Only check the temperature every 100 ticks
    if (tick_count > 100)
    {
      tick_count = 0;
      
      float temperature;
      //converting to celcius
      temperature = analogRead(temperaturePin) * .004882814;
      temperature = (temperature - .5) * 100;
       
      //parsing the digits, based on this code:
      //http://arduino.cc/forum/index.php?topic=108753.0
      
      int digOne = 0, digTwo = 0, digThree = 0;
     	
      //digOne
      temperature/=10;
      digOne = temperature;
       
      //digTwo
      temperature = (temperature-digOne)*10;
      digTwo = temperature;
       
      //digThree
      temperature = (temperature-digTwo)*10;
      digThree = temperature;
      
      //writing the digits
      write_char_five(digOne, 12,8,3);
      write_char_five(digTwo, 8,8,3);
      write_char_five(digThree, 2,8,3);
      
      matrix.drawPixel(12,6,1); //Write a decimal point
      matrix.writeScreen();
      
    }
    
    //Check home button, and return to menu program
    if (!home_value())
      {
        running_program = 6;
        temp_program_state = 0;
      }
  }
}

//------------END TEMPERATURE PROGRAM------
//------------BEGIN TIME PROGRAM-----------
void time_program()
{
  //remember previous values
    static int tick_count;
    static int prev_hour;
    static int prev_minute;
    static int prev_second;
    static int prev_year;
    static int prev_month;
    static int prev_day;
    
  if (time_program_state == 0)
  {
   //initialize time display
   tick_count=50;
   prev_hour = -1;
   prev_minute = -1;
   prev_second = -1;
   
   matrix.clearScreen();
   write_char_five(13,1,1,14); //Time
   matrix.drawPixel(9,8,1);
   matrix.drawPixel(11,8,1);
   
   
   time_program_state = 1;
   write_to_matrix = 1;
  }
  else if(time_program_state == 1)
  {
    //Show time
    
    tick_count += 1; //only check for new time every 50 ticks
    if (tick_count > 50)
    {
      tick_count = 0;
      
      //read and store current time
      DateTime now = RTC.now();
      int cur_hour = now.hour();
      int cur_minute = now.minute();
      int cur_second = now.second();
      
      
      int ones = 0, tens = 0, v = 0; 
      
      //only update hours if there has been a change
      if(!(cur_hour == prev_hour))
      {
        //parse hours
        v=cur_hour;
                
        if(v>12) {v-=12;} //convert to 12-hour time
        
        parse_digits(v,2);
        
        //make tens hour digit either 1 or blank
        if(parsed_digits[1]==1){        
          write_char_five(1,14,8,2); //1
        } else {
          //clear tens hours location
          matrix.drawRect(8, 14, 5, 2, 0);
          matrix.fillRect(8, 14, 5, 2, 0);
        }
        
        //am or pm
        if(cur_hour > 11 && cur_hour < 24)
        {
        write_char_five(14,2,17,3); //p
        } else {
        write_char_five(15,2,17,3); //a
        }
                   
        write_char_five(parsed_digits[0],10,8,3);
        
      
        write_to_matrix = 1;  
      }
      
      if(!(cur_minute == prev_minute))
      {
        //parse minutes
        parse_digits(cur_minute,2);
        
        write_char_five(parsed_digits[1], 4,8,3);
        write_char_five(parsed_digits[0],0,8,3);
      
        write_to_matrix = 1;  
      }
      
      if(!(cur_second == prev_second))
      {
        //parse seconds
        parse_digits(cur_second,2);
        
        write_char_five(parsed_digits[1], 12, 17,3);
        write_char_five(parsed_digits[0],8,17,3);
      
        write_to_matrix = 1;
      }
      
      prev_second = cur_second;
      prev_minute = cur_minute;
      prev_hour = cur_hour;
      
    }
  }
  else if (time_program_state == 2)
  {
    
    //initialize date display
    matrix.clearScreen();
    tick_count=100;
    prev_year=0;
    prev_month=0;
    prev_day=0;
    
    write_char_five(16,1,1,14);
    
    time_program_state = 3;
    write_to_matrix = 1;
  }
  else if (time_program_state == 3)
  {
    tick_count += 1;
    //check to see if the date has changed every 100 ticks
    if (tick_count > 100)
    {
      tick_count = 0;
      
      DateTime now = RTC.now();
      int cur_year = now.year();
      int cur_month = now.month();
      int cur_day = now.day();
      
      int v = 0;
      
      if(cur_year != prev_year)
      {
        parse_digits(cur_year,4);
        
        write_char_five(parsed_digits[0],0,8,3);
        write_char_five(parsed_digits[1],4,8,3);
        write_char_five(parsed_digits[2],8,8,3);
        write_char_five(parsed_digits[3],12,8,3);
        
        write_to_matrix = 1;
      }
      if(cur_month != prev_month)
      {
        parse_digits(cur_month,2);
        
        write_char_five(parsed_digits[0],8,16,3);
        write_char_five(parsed_digits[1],12,16,3);
      }
      if(cur_day != prev_day)
      {
        parse_digits(cur_day,2);
        
        write_char_five(parsed_digits[0],0,16,3);
        write_char_five(parsed_digits[1],4,16,3);
      }
      
      prev_year = cur_year;
      prev_month = cur_month;
      prev_day = cur_day;
      
    }
    
  }
  
  if (write_to_matrix){
    matrix.writeScreen();
    write_to_matrix = 0;
  }
  
  //Toggle between diaplaying time and date
  if(!select_value() && sel_reset)
  {
    sel_reset = 0;
    if(time_program_state == 3)
    {
      time_program_state =0;
    }
    else if(time_program_state == 1)
    {
      time_program_state = 2;
    }
  }
  
  //Go back to main menu is home button is pressed
  if (!home_value())
      {
        running_program = 6;
        time_program_state = 0;
      }
}
//----------END TIME PROGRAM----------
//----------BEGIN TETRIS PROGRAM--------

void tetris_program()
{
  if(!tetris_program_state)
  {
    //initialize the tetris program
    tetris_program_state = 1;
    score = 0;
    for(int i=0;i<24;i++)
    {
      board[i] = 0; //clear the board
    }
    
    matrix.clearScreen();
    write_char_six(0,0,8,16); //Write "TETRIS:"
    matrix.writeScreen();  
    playTetris(); //play the music, it will wait till the select button is pressed
    matrix.clearScreen();
    init_piece(); //start the next piece
    
    matrix.writeScreen();  
  }
  
  static byte ticks;
  static byte score_ticks;
  static byte joy_ticks_right, joy_ticks_left;
  
  if(check_game_over())
  {
    //write the final score to the display
    parse_digits(score,2);    
    first_digit_id = parsed_digits[0];
    if(parsed_digits[1] = 0)
    {
       second_digit_id = 10;
    }
    else
    {
      second_digit_id = parsed_digits[1];
    }
    write_to_display();
    
    
    matrix.clearScreen();
    write_char_five(17,0,0,16); //write "GAME"
    write_char_five(18,1,8,14); //write "OVER"
    matrix.writeScreen();
    playTetris(); //play tetris music, is will wait till the select button is pressed
    matrix.clearScreen();
    score = 0;
    
    for(int i=0;i<24;i++)
    {
      board[i] = 0; //clear the board
    }
    init_piece(); //start a piece
    return;
  }
  
  ticks += 1;
  int max_ticks = 25;
  
  read_joy_values();
  if(x_value > 600)
  {
    ticks = max_ticks; //speed up ticks if the joystick is pointing down
  }
  
  
  if(ticks < max_ticks)
  { //if the piece is not naturally moving down, allow the user to control it
   
    if(!select_value() && sel_reset)
    { //user wants to rotate piece
      
      write_current_piece(0); //erase the piece
      sel_reset=0;
      byte prev_rotation = current_rotation;
      rotate_block();
      
      if(check_rotate())
      {//if the rotate is illegal, bring to orientation of the piece to its previous orientation
        current_rotation = prev_rotation;
      }
      
        write_current_piece(1); //write the piece back
        matrix.writeScreen();
        delay(50);
        return;  
      
    }
    signed char delta = 0;
  
  
    
    //if the user wants to move horizontally and the move is legal, move the piece
    if (y_value > 600 && !(check_side_collision(-1)) && joy_ticks_right == 0)
    {
      delta = -1;
      joy_ticks_right = 8;
      joy_ticks_left = 0;
    }
    else if (y_value < 300 && !(check_side_collision(1)) && joy_ticks_left == 0)
    {
      delta = 1;
      joy_ticks_left = 8;
      joy_ticks_right = 0;
    }
   
    if(delta != 0)
    {
      write_current_piece(0); //erase piece
      current_piece_location[0] += delta; //move the piece along the x-axis
      write_current_piece(1); //write the piece
      matrix.writeScreen();
    }
  
  }
  else if(ticks == max_ticks) //every max_ticks move the piece down one
  {
    //check to see if the piece is ontop of another piece or it is at the bottom
    if(check_block_collide() || check_end_currentpiece())
    {
      add_piece();
      init_piece();
      return;
    }
    
    ticks = 0;
    write_current_piece(0); //erase piece
    remove_row(); //check to see if a row is complete and remove it
    current_piece_location[1] += 1; //move the piece
    write_current_piece(1); //write the piece
    matrix.writeScreen();
  }
  
  //go to pause screen
  if (!home_value())
  {
    matrix.fillRect(0,0,16,16,0); //blank out an area
    write_char_six(1,1,0,14); //Write "PAISE"
    matrix.writeScreen(); 
    playTetris(); //play music and wait till select button
    matrix.fillRect(0,0,16,16,0); //clear the area again
    resume_screen(); //resume the matrix displaying the pieces
    matrix.writeScreen();
  }
      
  //calculate the ticks at which the joystick will move
  if(joy_ticks_right != 0)
  {
    joy_ticks_right -= 1;
  }
  if(joy_ticks_left != 0)
  {
    joy_ticks_left -= 1;
  }
  
  if(!sel_reset) //reset the select button
  {
    sel_reset = select_value();
  }
  
  
  //display the score and the next piece on the segmented display
  //if the score if over 9, alternate between showing the score and the next piece
  if(score_ticks == 50)
  {
    parse_digits(score,2);    
    first_digit_id = parsed_digits[0];
    if(parsed_digits[1] > 0)
    {
      second_digit_id = parsed_digits[1];
    }
    write_to_display();
  }
  else if(score_ticks == 60)
  {
    score_ticks = 0;

    second_digit_id = next_piece + 11;
    write_to_display();
  }
  
  score_ticks += 1;
}

void init_piece()
{
  //initialize a piece
  current_piece = next_piece;
  next_piece = random(7);
  current_rotation = 0;
  current_piece_location[0]=initial_position[0];
  current_piece_location[1]=initial_position[1];
  
}

void write_current_piece(int color)
{
  write_piece(current_piece,current_rotation,current_piece_location[0],current_piece_location[1],color);
}

void write_piece(byte id,byte rot, signed char x, signed char y, unsigned int color)
{
  for(byte i=0;i<5;i++)
  {
    for(byte j=0;j<5;j++)
    {
      if(y+i>=0 && x+j>=0) //Writing to locations bigger than 16x24 is ok, but locations less than 0; it doesn't like
      {
        if(pgm_read_word(&(pieces[id][rot][i])) & (0b00000001 << j))
        {
          matrix.drawPixel(y+i,x+j,color);
        }
      }
    }
  }
}

byte check_end_currentpiece()
{
  //check if piece is at the bottom
    for(byte i=0;i<5;i++)
    {
      if(pgm_read_word(&(pieces[current_piece][current_rotation][i])) && (current_piece_location[1] + i == 23))
      {
        return 1;
      }
    }
    return 0;
}

void add_piece() {
  //add the current piece to the board
  unsigned int x,y;
  unsigned int piece_row;
  for(byte i=0;i<5;i++)
  {
    y=current_piece_location[1];
    x=current_piece_location[0];
    
    if(i+current_piece_location[1]<24)
    {
      piece_row = pgm_read_word(&(pieces[current_piece][current_rotation][i]));
      
      if(current_piece_location[0] >= 0)
      {
        piece_row = piece_row << current_piece_location[0]; 
      }
      else
      {
        piece_row = piece_row >> abs(current_piece_location[0]); 
      }
      
      board[i+current_piece_location[1]] = board[i+current_piece_location[1]] | piece_row; 
    }
  }
}

byte check_side_collision(signed int movement_direction)
{
  unsigned int piece_row;  
  for(byte i=0;i<5;i++)
  {
    piece_row = pgm_read_word(&(pieces[current_piece][current_rotation][i]));
    
    //Need to double check sign cause current_piece_location is signed and piece_row is unsigned
    if(current_piece_location[0] >= 0)
    {
      piece_row = piece_row << current_piece_location[0]; 
    }
    else
    {
      piece_row = piece_row >> abs(current_piece_location[0]); 
    }  
    
    //1 is the rightmost column, and 32768 is the leftmost, so check to see if a piece is there
    if(piece_row & 1u && movement_direction <= 0 )
    {
      return 1; //right bound
    }
    else if(piece_row & 32768u && movement_direction >= 0)
    {
      return 1; //left bound
    }
    
    //move the piece in the theoretical position
    if(movement_direction > 0)
    {
      piece_row = piece_row << 1u;
    }
    else if (movement_direction < 0)
    {
      piece_row = piece_row >> 1u;
    }
    
    //Verify that moving side to side will not interfere with a block there
    //check to see if the piece intersects with a piece on the board
    if(board[i+current_piece_location[1]] & piece_row)
    {
      return 1;
    }  
  }
  return 0;
}

byte check_block_collide()
{
  unsigned int piece_row;
 
  //Check to see if the block is on top of another block 
  for(byte i=0;i<5;i++)
    {
      if(current_piece_location[1] + i >= 0)
      {
        piece_row = pgm_read_word(&(pieces[current_piece][current_rotation][i]));
        
        if(current_piece_location[0] >= 0)
        {
          piece_row = piece_row << current_piece_location[0]; 
        }
        else
        {
          piece_row = piece_row >> abs(current_piece_location[0]); 
        }
        
        //if the piece's row intersects with the board's row, return 1
        if(board[i+current_piece_location[1]+1] & piece_row)
        {
          return 1;
        }  
      }
      
    }
    return 0; //if nothing intersects return 0
}

void rotate_block()
{ //rotate the block
  current_rotation += 1;
  
  if (current_rotation == 4) {current_rotation = 0;}
  
}

byte check_rotate()
{
  unsigned int piece_row;
  
  //check to see if rotate is legal
  for(byte i=0;i<5;i++)
    {
      //check intersecting blocks
      if(current_piece_location[1] >= 0)
      {
        piece_row = pgm_read_word(&(pieces[current_piece][current_rotation][i]));
        
        if(current_piece_location[0] >= 0)
        {
          piece_row = piece_row << current_piece_location[0]; 
        }
        else
        {
          piece_row = piece_row >> abs(current_piece_location[0]); 
        }
        
        if(board[i+current_piece_location[1]] & piece_row)
        {
          return 1;
        } 
       }
       
       //check side bounds
       if(current_piece_location[0] < 0 && pgm_read_word(&(pieces[current_piece][current_rotation][i])) & (1 << (abs(current_piece_location[0]) - 1)))
       {
         return 2;
       }
       else if (current_piece_location[0] > 11 && pgm_read_word(&(pieces[current_piece][current_rotation][i])) & (16 >> abs(12 - current_piece_location[0])))
       {
         return 3;
       }
       
       //check bottom bounds
        
        if(current_piece_location[1] + i > 23 && pgm_read_word(&(pieces[current_piece][current_rotation][i])))
        {
          return 4;
        }
      
      
    }
    //1 isn't always returned for debugging purposes
    return 0;
}

byte check_game_over()
{
  //if the first row is > 0 then game over
  return board[0];
  
}



void remove_row()
{
  
  byte row = 0;
  
  for(int i=0;i<24;i++)
  {
    if(board[i] == 65535) //find a complete row
    {
      row = i; 
    }
  }
  
  if(row)
  {
    score += 1;
    
    for(int i=row;i>0;i--)
    {
      board[i] = board[i - 1]; //move rows down
      
      for(int j=0;j<16;j++) //rewrite the board to the display
      {
          if(board[i] & (1u << j))
          {
            matrix.drawPixel(i,j,1);
          }
          else
          {
            matrix.drawPixel(i,j,0);
          }
        }
      }
    }
    
  }
  
void resume_screen()
{
  for(byte i=0; i<16; i++)
  {
    for(int j=0; j<16; j++)
    {
      //redraw the board
      matrix.drawPixel(i,j,toeightbit(board[i] & (1u << j)));
    }   
  } 
}
//---------END TETRIS PROGRAM----------
//---------BEING TETRIS MUSIC PROGRAM---------
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

// Instantiating all the notes to their tone
void playNote(char note, int duration) {
 
  // Read all the possible notes
  for (int i = 0; i < 28; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
 
void playTetris()
{
  while(1)
  {
    for (int i = 0; i < tetrisLength; i++) {
      if (tetris[i] == ' ') {
        delay(tetrisbeats[i] * tetrisTempo); // Rest
      } else {
        playNote(tetris[i], tetrisbeats[i] * tetrisTempo);
      }
      delay(tetrisTempo / 2); //Pauses
      
      if (!home_value())
      {
        running_program = 6;
        tetris_program_state = 0;
        return;
      }
      
      if(!select_value()) //Stop Tetris music program
      {
        return;
      }
    }
  }
  
}

void playChocobo()
{

  
  while(1)
  {
    for (int i = 0; i < Chocobo_length; i++) {
      if (Chocobo_notes[i] == ' ') {
        delay(Chocobo_beats[i] * Chocobo_tempo); // Rest
      } else {
        playNote(Chocobo_notes[i], Chocobo_beats[i] * Chocobo_tempo);
      }
      delay(Chocobo_tempo / 2); //Pauses
      
      if (!home_value())
      {
        running_program = 6;
        snake_program_state = 0;
        return;
      }
      
      if(!select_value()) //Stop Chocobo music program
      {
        return;
      }
    }
  }
}

//---------END TETRIS MUSIC PROGRAM--------
//---------BEGIN PHOTO SENSOR PROGRAM------

void photo_program()
{
   if(!photo_program_state)
  {
    //initialize the photo secnsor program
    photo_program_state = 1;
    matrix.clearScreen();
    write_char_six(8,0,0,15); //wite "PHOTO"
    write_char_five(19,9,9,5); //write the checkmark
    write_char_five(20,1,9,5); //write the X symbol
    matrix.writeScreen();  
  } 
  
  read_joy_values();
  
  if (y_value < 500) //change the settings based on if the user scrolls
  {
    dimmer_enabled = 1;
  }
  else if(y_value > 600)
  {
    dimmer_enabled = 0;
  }
  
  if(dimmer_enabled) //write the cursor location with a rectangle
  {
    matrix.drawRect(8,8,8,8,1);
    matrix.drawRect(8,0,8,8,0); //erase the other position
  }
  else
  {
    matrix.drawRect(8,8,8,8,0);
    matrix.drawRect(8,0,8,8,1);
    matrix.setBrightness(15);
  }
  
  int lightLevel = analogRead(light_pin);

  parse_digits(lightLevel,4);
  //write the value of the photo resistor
  write_char_five(parsed_digits[0],0,16,3);
  write_char_five(parsed_digits[1],4,16,3);
  write_char_five(parsed_digits[2],8,16,3);
  write_char_five(parsed_digits[3],12,16,3);
  
  matrix.writeScreen();
  
  delay(100); //don't need the program to run too fast
  if (!home_value()) //return to main menu
  {
    running_program = 6;
    photo_program_state = 0;
    return;
  }
}

void background_dimmer() //adjust the brightness of the LED matrix based on ambient light
{
  int lightLevel = analogRead(light_pin);
  int brightLevel = map(lightLevel,200,950,15,0);
  
  brightLevel = constrain(brightLevel,0,15);
  matrix.setBrightness(brightLevel);
}


//---------END PHOTO SENSOR PROGRAM---------
//---------BEGIN SEGMENTED DISPLAY PROGRAM------
void write_to_display()
{ 
  //write to the shift registers controlling the Segmented displays
  //Both registers share the same clock and latch
  digitalWrite(latch, LOW);
  for(byte i = 0; i < 8; i++)
  {
    digitalWrite(clock, LOW);
    
    //The segmented display is common anode so LOW turns the LED on
    if (display_one[first_digit_id] & (1 << i) )
    {
      digitalWrite(data_one, LOW);
    }
    else
    {
      digitalWrite(data_one, HIGH);
    }
    
    if (display_two[second_digit_id] & (1 << i) )
    {
      digitalWrite(data_two, LOW);
    }
    else
    {
      digitalWrite(data_two, HIGH);
    }
    digitalWrite(clock, HIGH);
  }
  digitalWrite(latch, HIGH);
}


//---------END SEGMENTED DISPLAY PROGRAM------
//---------BEGIN SNAKE PROGRAM----
void snake_init()
{
  //initialize snake program
  matrix.clearScreen();
  snake_score=0;
  snake_direction = 3;
  firstpress = 1;
  // generate snake
  snake_length = 5;
  for (int i = 0; i < 24; i++)
  { 
    for (int j = 0; j < 16; j++)
    {
      snake_board[i][j] = 0;
    }
  }
  for (int i = 1; i < 6; i++)
  { 
    snake_board[4 + i][12] = i;
    matrix.drawPixel(4 + i, 12, 1);
  }
  
    //clear the segmented display
    first_digit_id = 10;
    second_digit_id = 10;
    write_to_display();
      
      
  random_apple();
  
  matrix.writeScreen();
}

void snake_program()
{
  // local variables
  byte head[2];
  byte tail[2];
  byte next_head[2];
  static byte ticks;
  ticks +=1;
 
  if(!snake_program_state)
  {
    snake_init();
    snake_program_state = 1;
  }
  
  if (firstpress == 1)
  {
    playChocobo(); //this function will loop until a button is pressed
    firstpress = 0;
  }
  
  // read joystick to change direction
  read_joy_values();
  if (y_value > 600 && snake_direction != 1)
  {
    snake_direction = 0;
  }
  if (y_value < 500 && snake_direction != 0)
  {
    snake_direction = 1;
  }
  if (x_value < 500 && snake_direction != 3)
  {
    snake_direction = 2;
  }
  if (x_value > 600 && snake_direction != 2)
  {
    snake_direction = 3;
  }
  
  //only update snake every 20 ticks
  if(ticks > 20)
  {
    ticks = 0;
  
    // determine snake head and tail positions
    for (int i = 0; i < 24; i++)
    {
      for (int j = 0; j < 16; j++)
      {
        int parsed_snake_length;
        
        if(!snake_eat)
        {
          parsed_snake_length = snake_length;
        }
        else
        {
          parsed_snake_length = snake_length -1;
        }
        if (snake_board[i][j] == parsed_snake_length)
        {
          head[0] = i;
          head[1] = j;
        }
        if (snake_board[i][j] == 1)
        {
          tail[0] = i;
          tail[1] = j;
        }
        
        if (snake_board[i][j] > 0 && !snake_eat)
        { snake_board[i][j] -= 1; }
        
      }
    }
    
    // erase tail
    if (!snake_eat)
    {
      matrix.drawPixel(tail[0], tail[1], 0);
    }
    snake_eat = 0;
    
    // move in snake_direction
    switch(snake_direction)
    {
      // go right
      case(0): head[1] -= 1;
               break;
      // go left
      case(1): head[1] += 1;
               break;
      // go up
      case(2): head[0] -= 1;
               break;
      // go down
      case(3): head[0] += 1;
               break;
    }
    if (head[1] < 0 || head[1] > 15 || head[0] < 0 || head[0] > 23 || snake_board[head[0]][head[1]] > 0)
    {
      snake_program_state = 0;
      // game over so restart the program
    }
    
    if (snake_fruit[0] == head[0] && snake_fruit[1] == head[1])
    {
      // increase snake size, remove fruit
      snake_eat = 1;
      snake_score += 1;
      
      parse_digits(snake_score,2);    //update segmented display
      first_digit_id = parsed_digits[0];
      second_digit_id = parsed_digits[1];
      write_to_display();
      
      snake_length += 1;
      random_apple(); //spawn a new fruit
      
      
    }
    
    matrix.drawPixel(head[0], head[1], 1);
    if(!snake_eat) //update the location of the snake's head in the board array
    {
      snake_board[head[0]][head[1]] = snake_length;
    }
    else
    {
      snake_board[head[0]][head[1]] = snake_length-1;
    }
    
    
    matrix.writeScreen(); 
  }
  
  if (!home_value()) //return to main menu
  {
    running_program = 6;
    snake_program_state = 0;
    return;
  }

}

void random_apple()
{
  rand:
  byte column = random(24);
  byte row = random(16);
  //make sure the fruit doesn't spawn ontop of the snake
  if (snake_board[column][row] > 0) 
  {
    goto rand;
  }
  matrix.drawPixel(column, row, 1);

  snake_fruit[0] = column;
  snake_fruit[1] = row;
}
//-------------END SNAKE PROGRAM--------------
void write_char_five(int id,int x,int y,int w)
{ //for writing characters that have 5 rows
  for(byte i=0; i<5; i++)
  {
    for(int j=0; j<w; j++)
    {
      matrix.drawPixel(y+i,x+j,toeightbit(pgm_read_word(&(chars_five[id][i])) & (1u << j)));
      //the library requests uint8_t so need the toeightbit function to convert
      //the bitshift determines the value of the location in question (j)
      //note need to force 1 to be unsigned (1u) cause we are working with uint16_t
      //note the use of pgm_read_word because the array is stored in PROG_MEM, & creates an address based on a pointer
    }   
  } 
}

void write_char_six(int id,int x,int y,int w)
{  //writing characters with 6 rows
  for(byte i=0; i<6; i++)
  {
    for(int j=0; j<w; j++)
    {
      matrix.drawPixel(y+i,x+j,toeightbit(pgm_read_word(&(chars_six[id][i])) & (1u << j)));

    }   
  } 
}

void write_char_sixteen(int id,int x,int y,int w)
{ //writing characters with 16 rows
  for(byte i=0; i<16; i++)
  {
    for(int j=0; j<w; j++)
    {
      matrix.drawPixel(y+i,x+j,toeightbit(pgm_read_word(&(frames[id][i])) & (1u << j)));
    }   
  } 
}

boolean toeightbit(unsigned int x)
{
  //my way of turning a uint16_t into 8-bit
  if(x)return 1; else return 0;
}

void read_joy_values()
{ //read joystick values
  y_value = analogRead(y_pin);
  x_value = analogRead(x_pin);
}

boolean select_value()
{
  return digitalRead(sel_pin); //read select button
}

int home_value()
{
  //read home button
  //home button is ON-OFF, not a momentary switch, so need to create a toggle function
  if(prev_home_value != digitalRead(home_pin))
  {
    prev_home_value = digitalRead(home_pin);
    return 0;
  }
  else
  {
    return 1;
  }
  
}

void parse_digits(int x, int d)
{
  d = constrain(d,0,4); //d is evaluation distance, the array has a size of 4 so don't want to exceed that
  int output=0;
  for(int i=0; i<d; i++)
  {
    //Modified from http://arduino.cc/forum/index.php/topic,49291.0.html
    parsed_digits[i]=x%10;
    x=x/10;
  }
}
