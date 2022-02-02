#include "raylib.h"

#define SCREEN_SIDE 600
#define CELL_SIDE 8

Color texts = {60,60,60,255};
Color background = {20,20,20,255};
Color cells = {255,255,255,255};

const int LEN = SCREEN_SIDE / CELL_SIDE;

int grid[LEN][LEN] = {{0}};
int grid2[LEN][LEN] = {{0}};

bool run = true;
bool show_info = true;
short toggle_color = 1;



double mapVal(double value,double istart,double istop,double ostart,double ostop)
{
    return ostart+(ostop-ostart)*((value-istart)/(istop-istart));
}

void implementRules()
{
    for(int row=1;row<=LEN-2;row++)
        {
            for(int column=1;column<=LEN-2;column++)
                {
                    int alive = 0;

                    for(int i=-1;i<=1;i++)
                        for(int j = -1 ; j <= 1; j++)
                            alive += grid[row+i][column+j];
                    alive -= grid[row][column];

                    if((grid[row][column]==1) && (alive<2))
                        grid2[row][column] = 0;
                    else if((grid[row][column]==1) && (alive>3))
                        grid2[row][column] = 0;
                    else if((grid[row][column]==0) && (alive==3))
                        grid2[row][column] = 1;
                    else
                        grid2[row][column] = grid[row][column];
                }
        }
}


void clearGrids()
{
    for (int i = 0;i<LEN ;i++ )
        for (int j=0;j<LEN ;j++ )
            grid[i][j] = grid2[i][j];
    
    for (int i = 0;i<LEN ;i++ )
        for (int j=0;j<LEN ;j++ )
            grid2[i][j] = 0;
}


void drawGrid()
{
    for(int row=0; row<LEN; row++)
        for(int column=0; column<LEN; column++)
            {
                if (toggle_color==1)
                    cells = (Color){mapVal(row,0,LEN,0,255),mapVal(column,0,LEN,0,255),255,255};

                else if (toggle_color==2)
                    cells = (Color){mapVal(row,0,LEN,0,255),255,mapVal(column,0,LEN,0,255),255};
                
                else if (toggle_color==3)
                    cells = (Color){255,mapVal(row,0,LEN,0,255),mapVal(column,0,LEN,0,255),255};
                
                if (grid[row][column]==1)
                    DrawRectangle(row*CELL_SIDE, column*CELL_SIDE, CELL_SIDE, CELL_SIDE, cells); 
            }
}


void showInfo(Color tc)
{
    DrawText(TextFormat("FPS: %03i", GetFPS()), 3, 8, 14, tc);
    DrawText(TextFormat("Cells: %04i", LEN*LEN), 3, 24,14, tc);

    if (run)
        DrawText("Paused: No", 3, 40, 14, tc);
    else
        DrawText("Paused: Yes", 3, 40, 14, tc);
    DrawText(TextFormat("Color Theme: %01i",toggle_color), 3, 56, 14, tc);

}

void randomDistribution()
{
    for (int i = 0;i<LEN ;i++ )
        for (int j=0;j<LEN ;j++ )
            grid[i][j] = GetRandomValue(0, 1);
}

void mouseActions()
{
    if (IsKeyPressed(KEY_SPACE))
        run = !run;
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        grid[(int)(GetMouseX()/CELL_SIDE)][(int)(GetMouseY()/CELL_SIDE)] = 1;


    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        grid[(int)(GetMouseX()/CELL_SIDE)][(int)(GetMouseY()/CELL_SIDE)] = 0;

    if (IsKeyPressed(KEY_ENTER))
        clearGrids();

    if (IsKeyDown(KEY_F))
    {
        if (IsKeyPressed(KEY_D))
            SetTargetFPS(GetFPS()/2);
        else if (IsKeyPressed(KEY_I))
            SetTargetFPS(GetFPS()*2);
    }

    if (IsKeyPressed(KEY_C))
    {                
        if (toggle_color>3)
            toggle_color = 0;
        toggle_color++;
    }

    if (IsKeyPressed(KEY_R))
        randomDistribution();
    if (IsKeyPressed(KEY_I))
        show_info = !show_info;
}



int main(void)
{
    
    InitWindow(SCREEN_SIDE, SCREEN_SIDE, "Game Of Life"); 
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(background);
        drawGrid();
        if (show_info)
            showInfo(texts);
        
        EndDrawing();
        
        if (run)
        {   
            implementRules();
            clearGrids();
        }   
        mouseActions();
    }
    CloseWindow();    
}