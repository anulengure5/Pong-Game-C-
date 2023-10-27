

#include<iostream>
#include<raylib.h>
using namespace std;

int player_score=0;
int cpu_score=0;

class BALL  //Ball movement animation encapsulation
{
    public:
    float x, y;
    int speed_x,speed_y;
    int radius;//15px

    void Draw()
    {
         DrawCircle(x,y,radius,WHITE); 
         
    }


    void Update()
    {
        x+=speed_x;
        y+=speed_y;

        if((y+radius)>= GetScreenHeight()|| y-radius<=0) //speed change is 7px perframe so >= not== or ball amy exceed out 
        {
            speed_y*=-1;
        }
        
        // if((x+radius)>=GetScreenWidth() || x-radius<=0)
        // {
        //     speed_x*=-1;
        //     ResetBall();
        // }
//cpu ewin
            if(x+radius >=GetScreenWidth())
        {
          cpu_score++;
          ResetBall();  
        }


        if(x-radius <=0)
        {
          player_score++;
          ResetBall();  
        }
    }


    void ResetBall()
    {
        x=GetScreenWidth()/2;
        y=GetScreenHeight()/2;


        int speed_choices[2]={-1,1};

        speed_x*=speed_choices[GetRandomValue(0,1)];
        speed_y*=speed_choices[GetRandomValue(0,1)];


    }


};




class PADDLE
{ 
   protected:
   void LimitMovement()
   {
    if(y<=0)
    {
        y=0;
    }
    if(y+height>=GetScreenHeight())
    {
        y=GetScreenHeight()-height;
    }
   }



    public:

    float x,y;
    float width,height;
    int speed;

    void Draw()
    {
         
     DrawRectangle(x,y,width,height,WHITE);
    }


    void Update()
    {
        if(IsKeyDown(KEY_UP))   //built in click function
        y-=speed;  //on pressing cuts the height and moves up

        if(IsKeyDown(KEY_DOWN))
        y+=speed;

        LimitMovement();
    }

    //    if(y<=0)
    //    y=0;

    //    if(-height>= GetScreenHeight())
    //    y=GetScreenHeight()-height;



};

class AI_PADDLE : public PADDLE
{

public:
 
 void Update(int ball_y)
   {
      if(y+height/2 >ball_y)
      y-=speed;

      if(y+height/2<=ball_y)
      y+=speed;

   

   LimitMovement();
}



};

BALL ball;  // global instance;

PADDLE Player;

AI_PADDLE cpu;

int main()
{
    cout<<"GAME START"<<endl;
    const int screen_width=1200;  //on screen the top left corner marks as (0,0) along x is positive same as y 
    const int screen_height=900;   //screen center 640,400

    InitWindow(screen_width,screen_height,"PING-PONG");
    SetTargetFPS(60);//screen fps game;


    ball.radius=20;
    ball.x=screen_width/2;
    ball.y=screen_height/2;
    ball.speed_x=7;
    ball.speed_y=7;

    Player.width=25;
    Player.height=120;
    Player.x=screen_width-Player.width-10;//right paddle
    Player.y=screen_height/2-Player.height/2; 
    Player.speed=7;



    
    cpu.width=25;   
    cpu.height=120;
    cpu.x=10;//left paddle
    cpu.y=screen_height/2-cpu.height/2; 
    cpu.speed=6;



while(WindowShouldClose()==false)
 { 
    BeginDrawing();

    //update ball animation

    ball.Update(); //clrscreen updation
    Player.Update();
    cpu.Update(ball.y);


    //collision paddle touch
    if(CheckCollisionCircleRec({ball.x,ball.y},ball.radius,{Player.x,Player.y,Player.width,Player.height}))
    {
        ball.speed_x*=-1;

    }

        if(CheckCollisionCircleRec({ball.x,ball.y},ball.radius,{cpu.x,cpu.y,cpu.width,cpu.height}))
    {
        ball.speed_x*=-1;

    }
    
    

    ClearBackground(BLACK); //cleans the previous instance of ball for moving effect
    

    DrawRectangle(screen_width/2,0,screen_width/2,screen_height,BLACK);
    DrawCircle(screen_width/2,screen_height/2,150,WHITE);
   

     //Basic shapes creating , with Raylib built in func
   
     //game objects

     
     //court seperator line drawline(start x,starty,end x,end y,color)
    DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);


   
  
  


     ball.Draw();
     cpu.Draw();
     Player.Draw();


     DrawText(TextFormat("%i",cpu_score),screen_width/4-20,20,80,WHITE);
     DrawText(TextFormat("%i",player_score),3*screen_width/4-20,20,80,WHITE);



    //drawing circle;  (x coor,y coor, radius px, color)
   // DrawCircle(screen_width/2,screen_height/2,15,WHITE);

    //paddles draw rectangle(x coor, ycoor, breadth,height,color)
    //RECTANGLE is built from top left corner as (0,0) so on the x,y coor the top corner of rectangle is kept so modify to keep center at x,y
   
//    DrawRectangle(10,screen_height/2-(120/2),25,120,WHITE);-aipaddle
//    DrawRectangle(screen_width-(25+10),screen_height/2-(120/2),25,120,WHITE); -userpaddle
   






    EndDrawing();
    
 }
    CloseWindow();
 
 
 //events 



     
return 0;
}