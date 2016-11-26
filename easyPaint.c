/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define LINE_MODE 1
#define REC_MODE 2

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    int screenWidth = 1000;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    Vector2 lineStartPrev = {-1,-1};
    Vector2 lineStart[256];
    Vector2 lineEndingPrev = {-1,-1};
    Vector2 lineEnding[256];
    bool linePreview = false;
    
    Vector2 recPosition[256];
    Vector2 recPositionPrev;
    Vector2 recSize[256];
    Vector2 recSizePrev;
    bool recPreview = false;
    
    int lineCounter = 0;
    int recCounter = 0;
    
    int mode = LINE_MODE;
    Vector2 mousePosition;
    //interface
    
        //buttons
        int longbarPosY = 0;
        Rectangle butQuad = {2,longbarPosY + 3,24,24};
        Rectangle butLines = {2,longbarPosY + 24 + 6,24,24};
         
         
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();
        
        //Detect buttons
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(CheckCollisionPointRec(mousePosition,butQuad)) mode = REC_MODE;
            if(CheckCollisionPointRec(mousePosition,butLines)) mode = LINE_MODE;            
        }

        
        //Lines mode
        //------------------------------------------------------
        if (mousePosition.x > 50 && mode == LINE_MODE)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                lineStart[lineCounter] = mousePosition;
                lineStartPrev = mousePosition;
                linePreview = true;
            }
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                lineEnding[lineCounter] = mousePosition;
                lineEndingPrev = mousePosition;
            }
            else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                linePreview = false;
                lineEnding[lineCounter] = mousePosition;
                lineCounter++;
            }
            
            if (IsKeyDown(KEY_LEFT_CONTROL) || (IsKeyDown(KEY_RIGHT_CONTROL)))
            {
                if(IsKeyPressed(KEY_Z) && lineCounter >= 0) lineCounter--;
            }   
        }
        //Squares Module
        //-----------------------------------------------
        if (mousePosition.x > 50 && mode == REC_MODE)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                recPosition[recCounter] = mousePosition;
                recPositionPrev = mousePosition;
            }
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                recSize[recCounter].x = mousePosition.x - recPosition[recCounter].x;
                recSizePrev.x = mousePosition.x - recPositionPrev.x;
                recSize[recCounter].y = mousePosition.y - recPosition[recCounter].y;
                recSizePrev.y = mousePosition.y - recPositionPrev.y;
                recPreview = true;
            }
            else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                recSize[recCounter].x = mousePosition.x - recPosition[recCounter].x;
                recSize[recCounter].y = mousePosition.y - recPosition[recCounter].y;
                recCounter++;
                recPreview = false;
            }
            
            if (IsKeyDown(KEY_LEFT_CONTROL) || (IsKeyDown(KEY_RIGHT_CONTROL)))
            {
                if(IsKeyPressed(KEY_Z) && recCounter >= 0) recCounter--;
            }            
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            //interface
            DrawRectangle(0,0,30,screenHeight,GRAY);
            
                //Quad button
                if(mode == REC_MODE)DrawRectangleRec(butQuad,RAYWHITE);
                else DrawRectangleRec(butQuad,DARKGRAY);
                DrawRectangle(6,butQuad.y +5,15,12,MAROON);
                DrawRectangleLines(6,butQuad.y +5,15,12,BLACK);
                
                //Lines button
                if (mode == LINE_MODE)DrawRectangleRec(butLines,RAYWHITE);
                else DrawRectangleRec(butLines,DARKGRAY);
                
            //Line Drawing Logic
            //--------------------
            if(linePreview)DrawLineV(lineStartPrev,lineEndingPrev, BLACK); //preview line
            for (int i = 0; i < lineCounter; i++) //real lines drawing
            {
                DrawLineV(lineStart[i],lineEnding[i], BLACK);
            }
            //Rectangle Drawing Logic
            //--------------------
            if(recPreview)DrawRectangleV(recPositionPrev,recSizePrev,MAROON); //preview rec
            for (int i = 0; i < recCounter; i++) //real lines drawing
            {
                DrawRectangleV(recPosition[i],recSize[i], MAROON);
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}