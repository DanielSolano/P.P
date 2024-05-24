#include "raylib.h"
#include <iostream>

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define SQUARE_SIZE 31

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct SnakeSegment
{
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Texture2D sprite;
} SnakeSegment;

typedef struct SnakeNode
{
    SnakeSegment segment;
    struct SnakeNode *next;
} SnakeNode;

typedef struct Food
{
    Vector2 position;
    Vector2 size;
    bool active;
    Texture2D sprite;
} Food;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 450;

static int framesCounter = 0;
static bool gameOver = false;
static bool pause = false;

static Food fruit = {0};
static SnakeNode *snakeHead = NULL;
static Vector2 offset = {0};
static int counterTail = 0;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);
static void UpdateGame(Sound eat);
static void DrawGame(Music defeat, Sound eat, Music music);
static void UnloadGame(void);
static void UpdateDrawFrame(Music defeat, Sound eat, Music music);
static void AddSegment(void);
static void FreeSnake(void);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Culebrita");

    InitAudioDevice();

    Music defeat = LoadMusicStream("..\\sonidos\\derrota.mp3");
    Sound eat = LoadSound("..\\sonidos\\comer.mp3");
    Music music = LoadMusicStream("..\\sonidos\\musica_snake.mp3");
    
    SetMusicVolume(defeat, 0.1f);
    SetSoundVolume(eat, 0.5f);
    SetMusicVolume(music, 0.05f);

    PlayMusicStream(defeat);
    PlayMusicStream(music);

    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame(defeat, eat, music);
    }


    UnloadMusicStream(defeat);
    UnloadGame();
    CloseWindow();

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------
static void InitGame(void)
{
    framesCounter = 0;
    gameOver = false;
    pause = false;

    counterTail = 1;
    offset.x = SCREEN_WIDTH % SQUARE_SIZE;
    offset.y = SCREEN_HEIGHT % SQUARE_SIZE;

    FreeSnake();

    snakeHead = (SnakeNode *)malloc(sizeof(SnakeNode));
    snakeHead->segment.position = (Vector2){offset.x / 2, offset.y / 2};
    snakeHead->segment.size = (Vector2){SQUARE_SIZE, SQUARE_SIZE};
    snakeHead->segment.speed = (Vector2){SQUARE_SIZE, 0};
    snakeHead->segment.sprite = LoadTexture("C:\\Users\\Mitillo\\Universidad\\4to. Semestre\\P.P\\Practica1\\cualquier\\texturas\\snake-head.png");
    snakeHead->next = NULL;

    fruit.size = (Vector2){SQUARE_SIZE, SQUARE_SIZE};
    fruit.sprite = LoadTexture("C:\\Users\\Mitillo\\Universidad\\4to. Semestre\\P.P\\Practica1\\cualquier\\texturas\\fruta.png");
    fruit.active = false;
    AddSegment();
}

static void UpdateGame(Sound eat)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P'))
        {
            pause = !pause;
        }

        if (!pause)
        {
            if (IsKeyPressed(KEY_RIGHT) && (snakeHead->segment.speed.x == 0))
            {
                snakeHead->segment.speed = (Vector2){SQUARE_SIZE, 0};
            }
            if (IsKeyPressed(KEY_LEFT) && (snakeHead->segment.speed.x == 0))
            {
                snakeHead->segment.speed = (Vector2){-SQUARE_SIZE, 0};
            }
            if (IsKeyPressed(KEY_UP) && (snakeHead->segment.speed.y == 0))
            {
                snakeHead->segment.speed = (Vector2){0, -SQUARE_SIZE};
            }
            if (IsKeyPressed(KEY_DOWN) && (snakeHead->segment.speed.y == 0))
            {
                snakeHead->segment.speed = (Vector2){0, SQUARE_SIZE};
            }

            if ((framesCounter % 5) == 0)
            {
                SnakeNode *current = snakeHead;
                Vector2 previousPosition = current->segment.position;
                Vector2 tempPosition;

                current->segment.position.x += current->segment.speed.x;
                current->segment.position.y += current->segment.speed.y;

                while (current->next != NULL)
                {
                    current = current->next;
                    tempPosition = current->segment.position;
                    current->segment.position = previousPosition;
                    previousPosition = tempPosition;
                }
            }

            if ((snakeHead->segment.position.x >= SCREEN_WIDTH - offset.x) ||
                (snakeHead->segment.position.y >= SCREEN_HEIGHT - offset.y) ||
                (snakeHead->segment.position.x < 0) || (snakeHead->segment.position.y < 0))
            {
                gameOver = true;
            }

            SnakeNode *current = snakeHead->next;
            while (current != NULL)
            {
                if ((snakeHead->segment.position.x == current->segment.position.x) &&
                    (snakeHead->segment.position.y == current->segment.position.y))
                {
                    gameOver = true;
                    break;
                }
                current = current->next;
            }

            if (!fruit.active)
            {
                fruit.active = true;
                fruit.position = (Vector2){GetRandomValue(0, (SCREEN_WIDTH / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2,
                                           GetRandomValue(0, (SCREEN_HEIGHT / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2};

                current = snakeHead;
                while (current != NULL)
                {
                    while ((fruit.position.x == current->segment.position.x) &&
                           (fruit.position.y == current->segment.position.y))
                    {
                        fruit.position = (Vector2){GetRandomValue(0, (SCREEN_WIDTH / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2,
                                                   GetRandomValue(0, (SCREEN_HEIGHT / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2};
                        current = snakeHead;
                    }
                    current = current->next;
                }
            }

            if ((snakeHead->segment.position.x < (fruit.position.x + fruit.size.x) &&
                 (snakeHead->segment.position.x + snakeHead->segment.size.x) > fruit.position.x) &&
                (snakeHead->segment.position.y < (fruit.position.y + fruit.size.y) &&
                 (snakeHead->segment.position.y + snakeHead->segment.size.y) > fruit.position.y))
            {
                PlaySound(eat);
                AddSegment();
                fruit.active = false;
            }

            framesCounter++;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

static void AddSegment(void)
{
    SnakeNode *current = snakeHead;
    while (current->next != NULL)
    {
        current = current->next;
    }

    SnakeNode *newSegment = (SnakeNode *)malloc(sizeof(SnakeNode));
    newSegment->segment.position = current->segment.position;
    newSegment->segment.size = (Vector2){SQUARE_SIZE, SQUARE_SIZE};
    newSegment->segment.speed = (Vector2){0, 0};
    newSegment->segment.sprite = LoadTexture("C:\\Users\\Mitillo\\Universidad\\4to. Semestre\\P.P\\Practica1\\cualquier\\texturas\\snake-body.png");
    newSegment->next = NULL;

    current->next = newSegment;
    counterTail++;
}

static void FreeSnake(void)
{
    SnakeNode *current = snakeHead;
    SnakeNode *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    snakeHead = NULL;
}

static void DrawGame(Music defeat, Sound eat, Music music)
{
    Rectangle frameRec = {0.0f, 0.0f, (float)SQUARE_SIZE, (float)SQUARE_SIZE};
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!gameOver)
    {
        UpdateMusicStream(music);

        for (int i = 0; i < SCREEN_WIDTH / SQUARE_SIZE + 1; i++)
        {
            DrawLineV((Vector2){SQUARE_SIZE * i + offset.x / 2, offset.y / 2},
                      (Vector2){SQUARE_SIZE * i + offset.x / 2, SCREEN_HEIGHT - offset.y / 2}, LIGHTGRAY);
        }

        for (int i = 0; i < SCREEN_HEIGHT / SQUARE_SIZE + 1; i++)
        {
            DrawLineV((Vector2){offset.x / 2, SQUARE_SIZE * i + offset.y / 2},
                      (Vector2){SCREEN_WIDTH - offset.x / 2, SQUARE_SIZE * i + offset.y / 2}, LIGHTGRAY);
        }

        SnakeNode *current = snakeHead;
        while (current != NULL)
        {
            DrawTextureRec(current->segment.sprite, frameRec, Vector2{current->segment.position.x, current->segment.position.y}, RAYWHITE);
            current = current->next;
        }

        DrawTextureRec(fruit.sprite, frameRec, Vector2{fruit.position.x, fruit.position.y}, RAYWHITE);

        if (pause)
        {
            DrawText("GAME PAUSED", SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GRAY);
        }
    }
    else
    {

        UpdateMusicStream(defeat);
        DrawText("PRESS [ENTER] TO PLAY AGAIN", SCREEN_WIDTH / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, SCREEN_HEIGHT / 2 - 50, 20, GRAY);
    }

    EndDrawing();
}

static void UnloadGame(void)
{
    FreeSnake();
}

static void UpdateDrawFrame(Music defeat, Sound eat, Music music)
{

    UpdateGame(eat);
    DrawGame(defeat, eat, music);
}
