#include <raylib.h>
#include "funcoesjogo2periodo.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>



int main(void)
{
    short ordemBoss = 1;
    short *hpPlayer = malloc(sizeof(short));
    short *hpBoss =  malloc(sizeof(short));
    *hpPlayer = 30;
    *hpBoss = 30;
    char HpPlayerText[4];
    char HpBossText[4];
    char tempoRoundText[4];
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 700;
    const int screenHeight = 500;
    const int EixoXimagem = 253;
    const int EixoYimagem = 12; 
    
    InitWindow(screenWidth, screenHeight, "Dungeons & Dragons");
    InitAudioDevice();
    SetTargetFPS(60);               
    //--------------------------------------------------------------------------------------
    
    // Primeira config da imagem do Boss
    char fundoBoss1[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\fundodarkcanv.png";
    char fundoBoss2[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\fundoBoss2.png";
    char fundoBoss3[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\fundoBoss3.png";
    Texture2D Fundo; // LoadTexture(fundoBoss1);
    
    char Boss1[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\Boss3.png";
    char Boss2[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\Boss2.png";
    char Boss3[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\Boss1.png";
    Texture2D Boss; // LoadTexture(Boss1); 
    
    // Primeira config da musica do Boss
    char musica1[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\Boss1Music.mp3";
    char musica2[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\Boss2Music.mp3";
    char musica3[] = "C:\\Users\\Marcelo\\Downloads\\AnexosJogo\\AnexosJogo\\Boss3Music.mp3";
    Sound musica; //LoadSound(musica1);
    
    SaveConfig *Carregar = malloc(sizeof(SaveConfig));
    Carregar = Load();
    if (Carregar->bossordem == 1){
        Fundo = LoadTexture(fundoBoss1);
        Boss = LoadTexture(Boss1); 
        musica = LoadSound(musica1);
    }
    else if (Carregar->bossordem == 2){
        ordemBoss = 2;
        Fundo = LoadTexture(fundoBoss2);
        Boss = LoadTexture(Boss2); 
        musica = LoadSound(musica2);
        *hpBoss = Carregar->bossHP;
        *hpPlayer = Carregar->jogadorhp;
    }
    else if (Carregar->bossordem == 3){
        ordemBoss = 3;
        Fundo = LoadTexture(fundoBoss3);
        Boss = LoadTexture(Boss3); 
        musica = LoadSound(musica3);
        *hpBoss = Carregar->bossHP;
        *hpPlayer = Carregar->jogadorhp;
    }
    
    free(Carregar);
    
    // config do jogador e dos círculos do oponente
    Vector2 ballPosition = { 400, 350 };
    Vector2 *ballPositionCopy= malloc(sizeof(Vector2));
      
    Circulos *InicioCirculos = malloc(sizeof(Circulos));
    InicioCirculos->Proximo = NULL;
    PreencherLista(&InicioCirculos);
    
    float tempo = 0,tempoRound=0;
    
    PlaySound(musica);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        tempo +=GetFrameTime();
        tempoRound+= GetFrameTime();
        if (IsKeyDown(KEY_RIGHT) && ballPosition.x < 492) ballPosition.x += 3;
        if (IsKeyDown(KEY_LEFT) &&  ballPosition.x > 213) ballPosition.x -= 3;
        if (IsKeyDown(KEY_UP) && ballPosition.y > 202 ) ballPosition.y -= 3;
        if (IsKeyDown(KEY_DOWN) &&  ballPosition.y+3 < 388) ballPosition.y += 3;
        
        if (IsKeyDown(KEY_S)) Save(hpBoss, hpPlayer, ordemBoss);
        
        ballPositionCopy = &ballPosition;
        sprintf(HpPlayerText, "%d", *hpPlayer);
        sprintf(HpBossText, "%d", *hpBoss);
       
        
        if ( tempo >= 5 ){
            InicioCirculos = malloc(sizeof(Circulos));
            InicioCirculos->Proximo = NULL;
            PreencherLista(&InicioCirculos);
            tempo = 0.0f;
        }
        
        if ( *hpPlayer ==0 ){
            UnloadSound(musica);
            FimJogo();
        }
        if ( *hpBoss <=0 ){
            BeginDrawing();
            ClearBackground(WHITE);
            UnloadSound(musica);
            UnloadTexture(Boss);
            UnloadTexture(Fundo);
            if ( ordemBoss == 1 ){
                Fundo = LoadTexture(fundoBoss2);
                //LoadTexture(Fundo);
                musica = LoadSound(musica2); 
                PlaySound(musica);
                Boss = LoadTexture(Boss2);
                ordemBoss +=1;
                *hpBoss = 40;
            }
            else if (ordemBoss ==2){
                Fundo = LoadTexture(fundoBoss3);
                //LoadTexture(Fundo);
                musica = LoadSound(musica3);
                PlaySound(musica);
                Boss = LoadTexture(Boss3);
                ordemBoss +=1;
                *hpBoss = 50;
            }
            else { Win(); }
        EndDrawing();
        
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();        
        
            ClearBackground(BALLBOSS);
            DrawTexture(Fundo, 0,0, WHITE);
            DrawTexture(Boss, EixoXimagem,EixoYimagem, WHITE);
            DrawRectangle(220, 420, 120, 38, ColorRectangle);
            DrawRectangle(370, 420, 120,38, ColorRectangle);
            DrawRectangle(119, 180, 74, 24, ColorRectangle);
            DrawRectangle(513, 385, 74,24, ColorRectangle);
            DrawRectangle(EixoXretangulo-2, EixoYretangulo-2, 324, 229, BLACK);
            DrawRectangle(EixoXretangulo, EixoYretangulo, 320, 225, ColorRectangle);
             
            DrawText("Atacar", 245, 430, 20, WHITE);
            DrawText("Item", 410, 430,20, WHITE);
            DrawText("HP", 137, 160, 20, WHITE);
            DrawText("HP", 537, 363,20, WHITE);
            // transformar variaveis com int e passar para texto no HP
            DrawText(HpBossText, 140,183,22,RED);
            DrawText("  /30", 535, 388,17, WHITE);
            DrawText(HpPlayerText, 520,388,20,RED);
            
            DrawCircleV(ballPosition, 20, ColorBall);
            
            InicioCirculos = DesenharCirculos(InicioCirculos, ballPositionCopy, hpPlayer);
            if (tempoRound >=9){
                AtaqueJogador(hpBoss);
                tempoRound = 0.0f;
            }
        
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }
    

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(Boss);  // Unload texture from VRAM
    UnloadTexture(Fundo);
    UnloadSound(musica);

    CloseAudioDevice();
    CloseWindow();           // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

}