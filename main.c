#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

#define ROWS 7
#define COLS 53


typedef struct
{
    Vector2 pos;
    Vector2 speed;
    float radius;

} Ball;


typedef struct
{
    Rectangle rect;
    bool alive;
    int level;

} Brick;



int main()
{
    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Summaiya's Contribution Brick Breaker"
    );


    SetTargetFPS(60);



    // Load GitHub contribution data

    int contribution[365];

    for(int i=0;i<365;i++)
        contribution[i]=0;


    FILE *file = fopen(
        "contributions.txt",
        "r"
    );


    if(file)
    {
        for(int i=0;i<365;i++)
        {
            fscanf(
                file,
                "%d",
                &contribution[i]
            );
        }

        fclose(file);
        printf("Loaded contributions:\n");

for(int i=0;i<365;i++)
{
    if(contribution[i] > 0)
        printf("%d ", contribution[i]);
}

printf("\n");
    }



    Brick bricks[ROWS][COLS];


    int index = 0;


    for(int r=0;r<ROWS;r++)
    {
        for(int c=0;c<COLS;c++)
        {

            bricks[r][c].rect =
(Rectangle)
{
    20+c*16,
    150+r*45,
    14,
30
};


            bricks[r][c].level =
            contribution[index];


            bricks[r][c].alive =
            contribution[index] > 0;


            index++;

        }
    }




    Ball ball =
    {
        {450,400},
        {5,-5},
        10
    };



    Rectangle paddle =
    {
        390,
        540,
        120,
        15
    };



    int score = 0;



    while(!WindowShouldClose())
    {

        // paddle

        if(IsKeyDown(KEY_LEFT))
            paddle.x -= 7;


        if(IsKeyDown(KEY_RIGHT))
            paddle.x += 7;


        if(paddle.x < 0)
            paddle.x = 0;


        if(paddle.x+paddle.width > SCREEN_WIDTH)
            paddle.x =
            SCREEN_WIDTH-paddle.width;




        // ball

        ball.pos.x += ball.speed.x;
        ball.pos.y += ball.speed.y;



        if(ball.pos.x < 0 ||
           ball.pos.x > SCREEN_WIDTH)
        {
            ball.speed.x *= -1;
        }


        if(ball.pos.y < 0)
            ball.speed.y *= -1;



        if(CheckCollisionCircleRec(
            ball.pos,
            ball.radius,
            paddle))
        {
            ball.speed.y *= -1;
        }




        // bricks

        for(int r=0;r<ROWS;r++)
        {
            for(int c=0;c<COLS;c++)
            {

                if(bricks[r][c].alive)
                {

                    if(CheckCollisionCircleRec(
                        ball.pos,
                        ball.radius,
                        bricks[r][c].rect))
                    {

                        bricks[r][c].alive=false;

                        ball.speed.y *= -1;

                        score++;

                    }

                }

            }
        }




        if(ball.pos.y > SCREEN_HEIGHT)
        {
            ball.pos =
            (Vector2){450,400};

            score=0;
        }




        BeginDrawing();


        ClearBackground(
            (Color){10,5,20,255}
        );



        DrawText(
            "SUMMAIYA'S CONTRIBUTION ARCADE",
            40,
            30,
            28,
            WHITE
        );



        DrawText(
            TextFormat(
            "COMMITS DESTROYED: %d",
            score),
            40,
            70,
            20,
            PINK
        );




        // draw contribution bricks

        for(int r=0;r<ROWS;r++)
        {
            for(int c=0;c<COLS;c++)
            {

                if(bricks[r][c].alive)
                {

                    Color green;


                    switch(bricks[r][c].level)
                    {

                    case 1:
                        green =
                        (Color){70,180,90,255};
                        break;


                    case 2:
                        green =
                        (Color){40,200,80,255};
                        break;


                    case 3:
                        green =
                        (Color){20,230,90,255};
                        break;


                    case 4:
                        green =
                        (Color){0,255,100,255};
                        break;


                    default:
                        green =
                        (Color){30,120,60,255};

                    }



                    DrawRectangleRounded(
                        bricks[r][c].rect,
                        0.25,
                        8,
                        green
                    );

                }

            }
        }




        DrawRectangleRounded(
            paddle,
            0.5,
            10,
            (Color){255,80,200,255}
        );



        DrawCircle(
            ball.pos.x,
            ball.pos.y,
            ball.radius,
            WHITE
        );



        EndDrawing();

    }



    CloseWindow();


    return 0;
}