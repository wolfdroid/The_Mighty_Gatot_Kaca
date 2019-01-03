#include "raylib.h"
#define PHYSAC_IMPLEMENTATION
#include "physac.h"
#include "raymath.h"

#define VELOCITY    0.5f
#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1
#define MAXSIZE 3

typedef struct Player{
    Rectangle hitbox;
    Vector2 offset;
} Player;

typedef struct Slash{
    Rectangle rec;
    Vector2 poff;
    Rectangle out;
    Vector2 soff;
    bool sho;
    bool active;
    bool anim;
    bool anom;
    int fly;
} Slash;

typedef struct Obs{
    Rectangle gndR0;
    Rectangle gndR1;
    Rectangle gndR2;
    Rectangle plaR0;
    Rectangle plaR1;
    Rectangle plaR2;
    Rectangle plaR3;
    Rectangle plaR4;
    Rectangle walR0;
    Rectangle walR1;
    Rectangle gndL0;
    Rectangle gndL1;
    Rectangle gndL2;
    Rectangle plaL0;
    Rectangle plaL1;
    Rectangle plaL2;
    Rectangle plaL3;
    Rectangle plaL4;
    Rectangle walL0;
    Rectangle walL1;
    Rectangle endL;
    Rectangle endR;
    int moveX;
    int moveY;
} Obs;

typedef struct Enemy{
    Rectangle ene0;
    bool act0;
    Vector2 e0off;
    Rectangle ene1;
    bool act1;
    Vector2 e1off;
    Rectangle ene2;
    bool act2;
    Vector2 e2off;
    Rectangle ene3;
    bool act3;
    Vector2 e3off;
    Rectangle ene4;
    bool act4;
    Vector2 e4off;
    Rectangle ene5;
    bool act5;
    Vector2 e5off;
    Rectangle boss;
    Vector2 boff;
    int beat;
    int bjum;
    bool brig;
    bool blef;
    Rectangle batt;   
    Vector2 baoff;
    Rectangle bitt;
    Vector2 bioff;
    Rectangle bsta;
    int catt;
    int matt;
    bool patt;
    bool tact;
    bool ract;
    bool fact;
    Rectangle left;
    Rectangle right;
    int time;
    int moveX;
    int moveY;
} Enemy;

typedef struct Items{
    Rectangle hea0;
    bool lth0;
    Vector2 h0off;
} Items;

typedef struct stack{
    int stk[MAXSIZE];
    int top;
} SCORE;

SCORE s;
int stack_full;
int stack_empty;
 
static Player player;
static Slash slash;
static Obs obs;
static Enemy enemy;
static Items items;

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 900;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "The Mighty Gatot Kaca");                          //Judul
    Image WI = LoadImage("resources/img/WindowsIcon.png");
    SetWindowIcon(WI);
    
    int transCounter = 0;                                                                   //Variable Penghitung Frames keseluruhan
    
    InitAudioDevice();                                                                      //Inisialisasi Audio

    //Frames Counter
    int splashCounter = 0;                                                                   //Variable Penghitung Frames untuk Animasi Text
     
    //Screen Variables
    typedef enum {LOGO, TRIBUTE, DISCLAIMER, TITLE, TS1, TS2, TS3, TS4, BGAMING, GAMING, EXIT, CREDITS} GameScreen;                       //Membuat Definisi 
    GameScreen gameScreen = LOGO;                                                          //Men-set screen awal = screen LOGOTitleScreen titleScreen = TS1;
    int state = 0;                                                                         //Variable untuk Black Screen
    float alpha = 0.0;                                                                     //Variable Switch dari Black Screen ke Texture
    
    //Quit Game
    bool quitGame = false;                                                                 //Inisialisasi Fungsi Quit Game 
    
    //Logo Enveriesage
    Texture2D BL = LoadTexture("resources/img/Logo.png");                                          //Inisialisasi Background Logo
    Texture2D BS = LoadTexture("resources/img/blank.png");                                         //Inisialisasi Black Screen
    const char desc[25] = "Redefined your Envisage";                                           //Animasi Text
    Sound LS = LoadSound("resources/sound/Enveriesage.ogg");                                                   //Inisialisasi suara Logo
    SetSoundVolume(LS, 3.0);
    Music MS = LoadMusicStream("resources/Sound/ms.ogg");
    
    //Logo Raylib
    Texture2D RL = LoadTexture("resources/img/raylib_logo.png");   
    
    //Background Title
    Texture2D mainTB = LoadTexture("resources/img/MainBG.png");
    bool mtitle_a = false;
    Sound mainsfx1 = LoadSound("resources/Sound/mainsfx1.ogg");
    Sound mainsfx2 = LoadSound("resources/Sound/mainsfx2.ogg");
    SetSoundVolume(mainsfx1, 2.0);
    SetSoundVolume(mainsfx2, 4.0);
    Texture2D TSB1 = LoadTexture("resources/img/TS1.png");
    Texture2D TSB2 = LoadTexture("resources/img/TS2.png");
    Texture2D TSB3 = LoadTexture("resources/img/TS3.png");
    Texture2D TSB4 = LoadTexture("resources/img/TS4.png");
    
    //BGAMING Screen
    Texture2D bgaming1 = LoadTexture("resources/img/BGAMING1.png");
    Texture2D btrans1 = LoadTexture("resources/img/trans1.png");
    bool btrans1_a = false;
    Texture2D bgaming2 = LoadTexture("resources/img/BGAMING2.png");
    Texture2D btrans2 = LoadTexture("resources/img/trans2.png");
    Sound mainsfx3 = LoadSound("resources/Sound/mainsfx3.ogg");
    SetSoundVolume(mainsfx3, 1.2);
    
    s.top = -1;
    //Powerup Position
    Vector2 pos1, pos2, pos3;
    pos1.x = 0;
    pos1.y = 0;
    pos2.x = 0;
    pos2.y = 0;
    pos3.x = 0;
    pos3.y = 0;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    //Power Up Bar Texture
    Texture2D power_up = LoadTexture("resources/img/PUS.png");
    Texture2D power_upb = LoadTexture("resources/img/PUB.png");
    
    // Images Background initialization
    Vector2 bgv1, bgv2, bgv3, bgv4;
    bgv1.x = 0;
    bgv1.y = 0;
    bgv2.x = 0;
    bgv2.y = 0;
    bgv3.x = 0;
    bgv3.y = 0;
    bgv4.x = 0;
    bgv4.y = 0;
    Texture2D bg0 = LoadTexture("resources/img/bg_0.png");
    Texture2D bg1 = LoadTexture("resources/img/bg_1.png");
    Texture2D bg2 = LoadTexture("resources/img/bg_2.png");
    Texture2D bg3 = LoadTexture("resources/img/bg_3.png");
    Texture2D bg4 = LoadTexture("resources/img/bg_4.png");
    
    //Tile 1
    Image imgTile0 = LoadImage("resources/img/tile1.png");
    ImageResize(&imgTile0, 800, 100);
    Texture2D tile1 = LoadTextureFromImage(imgTile0);
    //Tile 2
    Texture2D tile2 = LoadTexture("resources/img/tile2.png");
    //Tile 3
    Image imgTile3 = LoadImage("resources/img/tile2.png");
    ImageResize(&imgTile3, 400, 100);
    Texture2D tile3 = LoadTextureFromImage(imgTile3); 
    //Platform Texture
    Texture2D platform_tex = LoadTexture("resources/img/platform.png");
    //Wall Left Texture
    Texture2D wall_1 = LoadTexture("resources/img/Wall1.png");
    //Wall Mid Texture
    Image imgwall2 = LoadImage("resources/img/Wall1.png");
    ImageResize (&imgwall2, 100, 450);
    Texture2D wall_2 = LoadTextureFromImage(imgwall2);
    Music game_bgm = LoadMusicStream("resources/Sound/game_bgm.ogg");
    SetMusicVolume (game_bgm, 1.1);
    
    //Gatot Move
    Texture2D gatotR = LoadTexture("resources/img/gatot_moveR.png");
    Texture2D gatotL = LoadTexture("resources/img/gatot_moveL.png");
    Rectangle gatotR_rec = { 0.0f, 0.0f, (float)gatotR.width/7, (float)gatotR.height };
    Rectangle gatotL_rec = { 0.0f, 0.0f, (float)gatotL.width/7, (float)gatotL.height };
    
    //Gatot Idle
    Texture2D gatotiR = LoadTexture("resources/img/gatot_idleR.png");
    Texture2D gatotiL = LoadTexture("resources/img/gatot_idleL.png");
    Rectangle gatotiR_rec = { 0.0f, 0.0f, (float)gatotiR.width/7, (float)gatotiR.height };
    Rectangle gatotiL_rec = { 0.0f, 0.0f, (float)gatotiL.width/7, (float)gatotiL.height };
    
    //Gatot Jump
    Texture2D gatotjR = LoadTexture("resources/img/gatot_jumpR.png");
    Texture2D gatotjL = LoadTexture("resources/img/gatot_jumpL.png");
    Rectangle gatotjR_rec = { 0.0f, 0.0f, (float)gatotjR.width/2, (float)gatotjR.height };
    Rectangle gatotjL_rec = { 0.0f, 0.0f, (float)gatotjL.width/2, (float)gatotjL.height };
    
    //Gatot Punch
    Texture2D gatotpR = LoadTexture("resources/img/gatot_punchR.png");
    Texture2D gatotpL = LoadTexture("resources/img/gatot_punchL.png");
    Rectangle gatotpR_rec = { 0.0f, 0.0f, (float)gatotpR.width, (float)gatotpR.height };
    Texture2D gatotjpR = LoadTexture("resources/img/punch_jumpR.png");
    Texture2D gatotjpL = LoadTexture("resources/img/punch_jumpL.png");    
    Rectangle gatotjpR_rec = { 0.0f, 0.0f, (float)gatotjpR.width, (float)gatotjpR.height };
    
    Texture2D powerPunchR = LoadTexture("resources/img/powerpunchR.png");
    Texture2D powerPunchL = LoadTexture("resources/img/powerpunchL.png");
    Rectangle ppR_rec =  { 0.0f, 0.0f, (float)powerPunchR.width/2, (float)powerPunchR.height };
    Rectangle ppL_rec =  { 0.0f, 0.0f, (float)powerPunchL.width/2, (float)powerPunchL.height };
    
    //Item box
    Texture2D chestC = LoadTexture("resources/img/chest_closed.png");
    Texture2D chestO = LoadTexture("resources/img/chest_open.png");
    
    //Enemies
    Texture2D jetL  = LoadTexture("resources/img/jetL.png");
    Texture2D jetR  = LoadTexture("resources/img/jetR.png");
    Texture2D tankL  = LoadTexture("resources/img/tankL.png");
    Texture2D tankR  = LoadTexture("resources/img/tankR.png");
    Texture2D spike = LoadTexture("resources/img/spike.png");
    Texture2D bossR = LoadTexture("resources/img/bossR.png");
    Texture2D bossL = LoadTexture("resources/img/bossL.png");
    Texture2D bulletR = LoadTexture("resources/img/bulletR.png");
    Texture2D bulletL = LoadTexture("resources/img/bulletL.png");
    
    //Gatot SFX
    Sound punchsfx = LoadSound("resources/Sound/punchsfx.ogg");
    Sound jumpsfx = LoadSound("resources/Sound/jumpsfx.ogg");
    Sound jumpsfx1 = LoadSound("resources/Sound/jumpsfx1.ogg");
    Sound hitten = LoadSound("resources/Sound/hitten.ogg");
    Sound gettingpu = LoadSound("resources/Sound/gettingpu.ogg");
    SetSoundVolume(jumpsfx, 0.3);
    SetSoundVolume(punchsfx, 0.3);
    SetSoundVolume(jumpsfx1, 0.3);
    SetSoundVolume(hitten,0.3);
    SetSoundVolume(gettingpu, 1.2);
    
    //Win SFX
    Sound WIN = LoadSound("resources/Sound/win.ogg");
    
    //Animation frames
    int currentFrame = 0;
    int framesCounter = 0;
    int fc = 0;
    int framesSpeed = 7;
    bool anim = false;      //state of movement
    bool right = true;      //direction of sprite
    int slashTime = 0;      //Duration of attack
    int shootTime = 0;
    
    // Initialize physics and default physics bodies
    InitPhysics();

    // Create floor and walls rectangle physics body
    //Tutor Level
    PhysicsBody ground0 = CreatePhysicsBodyRectangle((Vector2){ 400, 450 }, 800, 45, 10);
    PhysicsBody ground1 = CreatePhysicsBodyRectangle((Vector2){ 1200, 450 }, 600, 100, 10);
    PhysicsBody ground2 = CreatePhysicsBodyRectangle((Vector2){ 1800, 450 }, 400, 100, 10);
    PhysicsBody platform0 = CreatePhysicsBodyRectangle((Vector2){ 1150, 270 }, 150, 10, 10);
    PhysicsBody platform1 = CreatePhysicsBodyRectangle((Vector2){ -600, 270 }, 150, 10, 10);
    PhysicsBody platform2 = CreatePhysicsBodyRectangle((Vector2){ 5000, 300}, 150, 10, 10);
    PhysicsBody platform3 = CreatePhysicsBodyRectangle((Vector2){ 5300, 200 }, 150, 10, 10);
    PhysicsBody platform4 = CreatePhysicsBodyRectangle((Vector2){ 5800, 300}, 150, 10, 10);
    PhysicsBody wallLeft = CreatePhysicsBodyRectangle((Vector2){ -45, 200 }, 100, 450, 10);
    PhysicsBody wallMid = CreatePhysicsBodyRectangle((Vector2){ 1500, 300 }, 200, 450, 10);
    PhysicsBody item0 = CreatePhysicsBodyRectangle((Vector2){ 1750, 360 }, 50, 50, 10);
    
    // Disable dynamics to floor and walls physics bodies
    ground0->enabled = false;
    ground1->enabled = false;
    ground2->enabled = false;
    platform0->enabled = false;
    platform1->enabled = false;
    platform2->enabled = false;
    platform3->enabled = false;
    platform4->enabled = false;
    wallLeft->enabled = false;
    wallMid->enabled = false;
    item0->enabled = true;
    item0->freezeOrient = true;
    
    // Create movement physics body
    PhysicsBody body = CreatePhysicsBodyRectangle((Vector2){ 400, 225 }, 50, 50, 1);
    body->freezeOrient = true;  // Constrain body rotation to avoid little collision torque amounts
    
    //Camera Initialization
    Camera2D camera;
    camera.target = (Vector2){ body->position.x + 20, body->position.y + 20 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;
    
    //Player Hitbox
    player.hitbox.width = 50;
    player.hitbox.height = 50;
    player.hitbox.x = body->position.x - 50;
    player.hitbox.y = body->position.y - 25;
    
    //Obstacle Hitbox
    //Camera Hitbox
    obs.gndR0.width = 800;
    obs.gndR0.height = 90;
    obs.gndR0.x = ground0->position.x - 400;
    obs.gndR0.y = ground0->position.y - 45;
    
    obs.gndR1.width = 600;
    obs.gndR1.height = 90;
    obs.gndR1.x = ground1->position.x - 300;
    obs.gndR1.y = ground1->position.y - 45;
    
    obs.gndR2.width = 400;
    obs.gndR2.height = 90;
    obs.gndR2.x = ground2->position.x - 200;
    obs.gndR2.y = ground2->position.y - 45;
    
    obs.plaR0.width = 150;
    obs.plaR0.height = 6;
    obs.plaR0.x = platform0->position.x - 75;
    obs.plaR0.y = platform0->position.y;
    
    obs.plaR1.width = 150;
    obs.plaR1.height = 6;
    obs.plaR1.x = platform1->position.x - 75;
    obs.plaR1.y = platform1->position.y;
    
    obs.plaR2.width = 150;
    obs.plaR2.height = 6;
    obs.plaR2.x = platform1->position.x - 75;
    obs.plaR2.y = platform1->position.y;
    
    obs.plaR3.width = 150;
    obs.plaR3.height = 6;
    obs.plaR3.x = platform1->position.x - 75;
    obs.plaR3.y = platform1->position.y;
    
    obs.plaR4.width = 150;
    obs.plaR4.height = 6;
    obs.plaR4.x = platform1->position.x - 75;
    obs.plaR4.y = platform1->position.y;
    
    obs.walR0.width = 100;
    obs.walR0.height = 440;
    obs.walR0.x = wallLeft->position.x - 50;
    obs.walR0.y = wallLeft->position.y - 220;
    
    obs.walR1.width = 200;
    obs.walR1.height = 440;
    obs.walR1.x = wallMid->position.x - 100;
    obs.walR1.y = wallMid->position.y - 220;
    
    //Animation Hitbox
    obs.gndL0.width = 780;
    obs.gndL0.height = 100;
    obs.gndL0.x = ground0->position.x - 390;
    obs.gndL0.y = ground0->position.y - 55;
    
    obs.gndL1.width = 580;
    obs.gndL1.height = 100;
    obs.gndL1.x = ground1->position.x - 290;
    obs.gndL1.y = ground1->position.y - 55;
    
    obs.gndL2.width = 380;
    obs.gndL2.height = 100;
    obs.gndL2.x = ground2->position.x - 190;
    obs.gndL2.y = ground2->position.y - 50;
    
    obs.plaL0.width = 130;
    obs.plaL0.height = 10;
    obs.plaL0.x = platform0->position.x - 65;
    obs.plaL0.y = platform0->position.y - 5;
    
    obs.plaL1.width = 130;
    obs.plaL1.height = 10;
    obs.plaL1.x = platform1->position.x - 65;
    obs.plaL1.y = platform1->position.y - 5;
    
    obs.plaL2.width = 130;
    obs.plaL2.height = 10;
    obs.plaL2.x = platform1->position.x - 65;
    obs.plaL2.y = platform1->position.y - 5;
    
    obs.plaL3.width = 130;
    obs.plaL3.height = 10;
    obs.plaL3.x = platform1->position.x - 65;
    obs.plaL3.y = platform1->position.y - 5;
    
    obs.plaL4.width = 130;
    obs.plaL4.height = 10;
    obs.plaL4.x = platform1->position.x - 65;
    obs.plaL4.y = platform1->position.y - 5;
    
    obs.walL0.width = 80;
    obs.walL0.height = 450;
    obs.walL0.x = wallLeft->position.x - 40;
    obs.walL0.y = wallLeft->position.y - 225;
    
    obs.walL1.width = 180;
    obs.walL1.height = 450;
    obs.walL1.x = wallMid->position.x - 80;
    obs.walL1.y = wallMid->position.y - 225;
    
    bool onGround = true;
    
    obs.endL.width = 450;
    obs.endL.height = 450;
    obs.endL.x = 0;
    obs.endL.y = 0;
    
    obs.endR.width = 600;
    obs.endR.height = 450;
    obs.endR.x = 6300;
    obs.endR.y = 0;
    
    obs.moveX = 2;      //Platform movement in X direction
    obs.moveY = 2;      //Platform movement in Y direction
    
    //Enemy Initialization
    enemy.ene0.width = 250;
    enemy.ene0.height = 50;
    enemy.ene0.x = 1000;
    enemy.ene0.y = 350;
    enemy.act0 = true;
    
    enemy.ene1.width = 250;
    enemy.ene1.height = 50;
    enemy.ene1.x = 1800;
    enemy.ene1.y = 250;
    enemy.act1 = true;
    
    enemy.ene2.width = 250;
    enemy.ene2.height = 50;
    enemy.ene2.x = 3000;
    enemy.ene2.y = 250;
    enemy.act2 = true;
    
    enemy.ene3.width = 50;
    enemy.ene3.height = 50;
    enemy.ene3.x = 4250;
    enemy.ene3.y = 350;
    enemy.act3 = true;
    
    enemy.boss.width = 200;
    enemy.boss.height = 200;
    enemy.boss.x = 7650;
    enemy.boss.y = -600;
    enemy.beat = 500;
    enemy.bjum = 15;
    enemy.fact = false;
    
    enemy.batt.width = 35;
    enemy.batt.height = 35;
    enemy.batt.x = enemy.boss.x - 25;
    enemy.batt.y = -200;
    enemy.bitt.width = 35;
    enemy.bitt.height = 35;
    enemy.bitt.x = enemy.boss.x - 25;
    enemy.bitt.y = -200;
    enemy.matt = 20;
    enemy.catt = 0;
    enemy.tact = false;
    enemy.ract = true;
    
    enemy.bsta.width = 25;
    enemy.bsta.height = 720;
    enemy.bsta.x = 7000;
    enemy.bsta.y = 0;
    enemy.brig = false;
    enemy.blef = false;
    
    enemy.left.width = 26;
    enemy.left.height = 26;
    enemy.left.x = enemy.ene0.x - 1;
    enemy.left.y = enemy.ene0.y - 1;
    
    enemy.right.width = 26;
    enemy.right.height = 26;
    enemy.right.x = enemy.ene0.x + 25;
    enemy.right.y = enemy.ene0.y - 1;
    
    enemy.time = 0;
    enemy.moveX = 2;        //Enemy movement in X direction
    enemy.moveY = 7;
    
    //Item Initialization
    items.hea0.width = 50;
    items.hea0.height = 45;
    items.hea0.x = item0->position.x - 25;
    items.hea0.y = item0->position.y - 20;
    items.lth0 = true;
    
    //Attack Initialization
    slash.rec.width = 30;
    slash.rec.height = 30;
    slash.out.width = 30;
    slash.out.height = 30;
    slash.out.x = body->position.x + 30;
    slash.out.y = body->position.y;
    slash.fly = 15;
    slash.sho = false;
    slash.active = false;
    
    //Platform Y position
    platform1->position.y = 200;
    platform2->position.y = 350;
    platform4->position.y = 150;
    
    //Multipurpose Rectangle
    Rectangle mBox;
    mBox.width = 50;
    mBox.height = 50;
    mBox.x = 0;
    mBox.y = 0;
    
    //enemy moving box
    Rectangle eBox;
    eBox.width = 122;
    eBox.height = 50;
    eBox.x = 0;
    eBox.y = 0;
    
    //enemy moving box
    Rectangle eBox1;
    eBox1.width = 122;
    eBox1.height = 33;
    eBox1.x = 0;
    eBox1.y = 0;
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !quitGame)    // Detect window close button or ESC key
    {
        // Texture Update
        //----------------------------------------------------------------------------------
        framesCounter++;
        fc ++;
        
        //General Updates
        splashCounter +=4;                          //Pengatur Kecepatan Text
        transCounter ++;                          //Pengatur Transisi Antar Layar
        UpdateMusicStream(MS);
        UpdateMusicStream(game_bgm);
        
        //GameScreen Updates
        switch(gameScreen){
            
            case LOGO   : {
                //Black Screen before image
                if(state == 0) {
                    if(alpha<1.0)alpha += 0.05;                         //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if (state == 1){
                    alpha = 1.0;
                    if(transCounter % 150==0) state = 2;               //Durasi untuk Menampilkan Layer Logo
                }
                else if (state == 2){
                    if(alpha>0.0)alpha -= 0.05;                         //Pengatur Kecepatan Black Screen
                    else{
                        gameScreen = TRIBUTE;
                        state = 0;
                    }
                }
            }break;
            
            case TRIBUTE: {
                //Black Screen before image
                if(state == 0) {
                    if(alpha<1.0)alpha += 0.05;              //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if (state == 1){
                    alpha = 1.0;
                    if(transCounter % 150==0) state = 2;    //Lamanya Durasi Logo Raylib Ditampilkan
                }
                else if (state == 2){
                    if(alpha>0.0)alpha -= 0.05;              //Pengatur Kecepatan Black Screen
                    else{
                        gameScreen = DISCLAIMER;
                        state = 0;
                    }
                }
            }break;
            
            case DISCLAIMER : {
                //Black Screen before image
                if(state == 0) {
                    if(alpha<1.0)alpha += 0.05;              //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if (state == 1){
                    alpha = 1.0;
                    if(transCounter % 300 == 0) state = 2;    //Lamanya Durasi Discalimer Ditampilkan
                }
                else if (state == 2){
                    if(alpha>0.0)alpha -= 0.05;              //Pengatur Kecepatan Black Screen
                    else{
                        gameScreen = TITLE;
                        state = 0;
                    }
                }
            } break;
            
            case TITLE : {
                if(state == 0) {
                    PauseMusicStream(game_bgm);
                    ResumeMusicStream(MS);
                    if(alpha<1.0)alpha += 0.05;              //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if(state == 1) {
                    alpha = 1.0;
                    if( (fc%50) == 0) mtitle_a = !mtitle_a;             //Setiap kelipatan x count maka gambar title 1 dan title 2 akan bergantian muncul
                    if(IsKeyPressed(KEY_SPACE)) {
                        PlaySound(mainsfx1);
                        state = 2;
                    }
                }
                else if (state == 2) {
                    if(alpha>0.0)alpha -= 0.05;              //Pengatur Kecepatan Black Screen
                    else{
                        gameScreen = TS1;
                        state = 0;
                    }
                }
            } break;
            
            case TS1 : {
                if(state == 0) {
                    if(alpha<1.0)alpha += 0.05;              //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if(state == 1) {
                    alpha = 1.0;
                    if (IsKeyPressed(KEY_UP)) {
                        PlaySound(mainsfx2);
                        gameScreen = TS2;
                        state = 0;
                    }
                    else if (IsKeyPressed(KEY_DOWN)) {
                        PlaySound(mainsfx2);
                        gameScreen = TS3;
                        state = 0;
                    }
                    else if (IsKeyPressed(KEY_SPACE)) {
                        PlaySound(mainsfx1);
                        gameScreen = BGAMING;
                        state = 0;
                    }
                }
            } break;
            
            case TS2 : {
                if (IsKeyPressed(KEY_UP)) {
                    PlaySound(mainsfx2);
                    gameScreen = TS4;
                    state = 0;
                }
                else if (IsKeyPressed(KEY_DOWN)) {
                    PlaySound(mainsfx2);
                    gameScreen = TS1;
                    state = 1;
                }
            } break;
            
           
            case TS3 : {
                if (IsKeyPressed(KEY_UP)) {
                    PlaySound(mainsfx2);
                    gameScreen = TS1;
                    state = 1;
                }
                else if (IsKeyPressed(KEY_DOWN)) {
                    PlaySound(mainsfx2);
                    gameScreen = TS4;
                    state = 0;
                }
            } break;
            
            case TS4 : {
                if (IsKeyPressed(KEY_UP)) {
                    PlaySound(mainsfx2);
                    gameScreen = TS3;
                    state = 0;
                }
                else if (IsKeyPressed(KEY_DOWN)) {
                    PlaySound(mainsfx2);
                    gameScreen = TS2;
                    state = 0;
                }
                else if (IsKeyPressed(KEY_SPACE)) {
                    PlaySound(mainsfx2);
                    gameScreen = EXIT;
                    state = 0;
                }
            } break;
            
            case EXIT : {
                //Black Screen before image
                if(state == 0) {
                    if(alpha<1.0)alpha += 0.05;                         //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if (state == 1){
                    alpha = 1.0;
                    if(transCounter % 300==0) state = 2;               //Durasi untuk Menampilkan Layer Logo
                }
                else if (state == 2){
                    if(alpha>0.0)alpha -= 0.05;                         //Pengatur Kecepatan Black Screen
                    else{
                        quitGame = true;
                    }
                }
            }break;
            
            
            case BGAMING : {
                if (state == 0) {
                    if(alpha<1.0)alpha += 0.05;              //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if(state == 1) {
                    if( (fc%50) == 0) btrans1_a = !btrans1_a;
                    if (IsKeyPressed(KEY_SPACE)) {
                        PlaySound(mainsfx1);
                        gameScreen = GAMING;
                        state = 0;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE)){
                        PlaySound(mainsfx3);
                        gameScreen = TS1;
                        state = 0;
                    }
                    else if (IsKeyPressed(KEY_DOWN)) {
                        PlaySound(mainsfx2);
                        state = 2;
                    }
                }
                else if (state == 2) {
                    if( (fc%50) == 0) btrans1_a = !btrans1_a;
                    if(IsKeyPressed(KEY_UP)) {
                        PlaySound(mainsfx2);
                        state = 1;
                    }
                    else if (IsKeyPressed(KEY_BACKSPACE)){
                        PlaySound(mainsfx3);
                        gameScreen = TS1;
                        state = 0;
                    }
                    
                }
            } break;
            
            case CREDITS : {
                
                //Black Screen before image
                if(state == 0) {
                    PlaySound(WIN);
                    if(alpha<1.0)alpha += 0.05;                         //Pengatur Kecepatan Black Screen
                    else state = 1;
                }
                else if (state == 1){
                    alpha = 1.0;
                    if (IsKeyPressed(KEY_SPACE)) state = 2;
                }
                else if (state == 2){
                    if(alpha>0.0)alpha -= 0.05;                         //Pengatur Kecepatan Black Screen
                    else{
                        gameScreen = EXIT;
                        state = 0;
                    }
                }
            }break;
            
            case GAMING : {
                PauseMusicStream(MS);
                //Black Screen before image
                if(state == 0) {
                    PlayMusicStream(game_bgm);
                    if(alpha<1.0)alpha += 0.05;                         //Pengatur Kecepatan Black Screen
                    else if(transCounter % 100 == 0) state = 1;
                }
                else if(state == 1){
                    if (IsKeyPressed(KEY_BACKSPACE)){
                        PauseMusicStream(game_bgm);
                        gameScreen = TITLE;
                        state = 0;
                    }
                    
                    //Main Game
                    if(alpha>0.0)alpha -= 0.05;              //Pengatur Kecepatan Black Screen
                    if (framesCounter >= (60/framesSpeed)) {
                        framesCounter = 0;
                        currentFrame++;
                        
                        if (currentFrame > 6) currentFrame = 0;
                        gatotjR_rec.x = (float)currentFrame*(float)gatotjR.width/2;
                        gatotjL_rec.x = (float)currentFrame*(float)gatotjL.width/2;
                        gatotR_rec.x = (float)currentFrame*(float)gatotR.width/7;
                        gatotL_rec.x = (float)currentFrame*(float)gatotL.width/7;
                        gatotiR_rec.x = (float)currentFrame*(float)gatotiR.width/7;
                        gatotiL_rec.x = (float)currentFrame*(float)gatotiL.width/7;
                        ppR_rec.x = (float)currentFrame*(float)powerPunchR.width/2;
                        ppL_rec.x = (float)currentFrame*(float)powerPunchL.width/2;
                    }
                
                    if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
                    else if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;
                    
                    //texture offset
                    player.offset.x = body->position.x - 25;
                    player.offset.y = body->position.y - 25;
                    
                    player.hitbox.x = body->position.x - 25;
                    player.hitbox.y = body->position.y - 25;
                    
                    
                    //Enemy Offset
                    enemy.e0off.x = enemy.ene0.x;
                    enemy.e0off.y = enemy.ene0.y;
                    enemy.e1off.x = enemy.ene1.x;
                    enemy.e1off.y = enemy.ene1.y;
                    enemy.e2off.x = enemy.ene2.x;
                    enemy.e2off.y = enemy.ene2.y;
                    enemy.e3off.x = enemy.ene3.x;
                    enemy.e3off.y = enemy.ene3.y;
                    enemy.e4off.x = enemy.ene4.x;
                    enemy.e4off.y = enemy.ene4.y;
                    enemy.e5off.x = enemy.ene5.x;
                    enemy.e5off.y = enemy.ene5.y;
                    enemy.boff.x = enemy.boss.x;
                    enemy.boff.y = enemy.boss.y;
                    enemy.baoff.x = enemy.batt.x;
                    enemy.baoff.y = enemy.batt.y;
                    enemy.bioff.x = enemy.bitt.x;
                    enemy.bioff.y = enemy.bitt.y;
                    
                    //Item Offset
                    items.h0off.x = item0->position.x - 25;
                    items.h0off.y = item0->position.y - 25;
                    
                    //----------------------------------------------------------------------------------
                    
                    // Game Update
                    //----------------------------------------------------------------------------------
                    if (IsKeyPressed('R') || player.hitbox.y + player.hitbox.height > 750 || state == 0)    // Reset physics input
                    {
                        //Reset movement physics body position, velocity and rotation
                        body->position = (Vector2){ 400, 225 };
                        body->velocity = (Vector2){ 0, 0 };
                        camera.target = (Vector2){ body->position.x + 20, body->position.y + 20 };
                        camera.offset = (Vector2){ 0, 0 };
                        camera.zoom = 1.50f;
                        camera.rotation = 0.0f;
                        SetPhysicsBodyRotation(body, 0);
                        
                        bgv1.x = 0;
                        bgv1.y = 0;
                        bgv2.x = 0;
                        bgv2.y = 0;
                        bgv3.x = 0;
                        bgv3.y = 0;
                        bgv4.x = 0;
                        bgv4.y = 0;
                        
                        enemy.ene0.y = 350;
                        enemy.ene1.y = 250;
                        enemy.ene2.y = 250;
                        
                        enemy.fact = false;
                        enemy.tact = false;
                        enemy.ract = true;
                        
                        platform0->position.x = 1120;
                        platform1->position.y = 200;
                        platform2->position.y = 350;
                        platform4->position.y = 150;
                        wallMid->position.y = 300;
                    }

                    // Horizontal movement input
                    anim = false;       //freeze animation
                    if (IsKeyDown(KEY_RIGHT)) {
                        body->position.x += 6.75;
                        //body->velocity.x = VELOCITY;
                        camera.offset.x -= 6.75;       // Camera displacement with player movement
                        bgv1.x -= 0.1f;
                        bgv2.x -= 0.2f;
                        bgv3.x -= 0.4f;
                        bgv4.x -= 0.8f;                        
                        if (!slash.anim || !slash.anom) anim = true;
                        right = true;       //face right
                        if (CheckCollisionRecs(player.hitbox,obs.endL) || CheckCollisionRecs(player.hitbox,obs.endR) || CheckCollisionRecs(player.hitbox,obs.walR0) || CheckCollisionRecs(player.hitbox,obs.walR1) || CheckCollisionRecs(player.hitbox,obs.gndR1) || CheckCollisionRecs(player.hitbox,obs.gndR2) ||CheckCollisionRecs(player.hitbox,obs.plaR0) || CheckCollisionRecs(player.hitbox,obs.plaR1) || CheckCollisionRecs(player.hitbox,items.hea0)) {
                            camera.offset.x += 6.75;
                            bgv1.x += 0.1f;
                            bgv2.x += 0.2f;
                            bgv3.x += 0.4f;
                            bgv4.x += 0.8f;
                        }
                    }
                    else if (IsKeyDown(KEY_LEFT)) {
                        body->position.x -= 6.75;
                        //body->velocity.x = -VELOCITY;
                        camera.offset.x += 6.75;       // Camera displacement with player movement
                        bgv1.x += 0.1f;
                        bgv2.x += 0.2f;
                        bgv3.x += 0.4f;
                        bgv4.x += 0.8f;
                        if (!slash.anim || !slash.anom) anim = true;
                        right = false;      //face left
                        if (CheckCollisionRecs(player.hitbox,obs.endL) || CheckCollisionRecs(player.hitbox,obs.endR) || CheckCollisionRecs(player.hitbox,obs.walR0) || CheckCollisionRecs(player.hitbox,obs.walR1) || CheckCollisionRecs(player.hitbox,obs.gndR1) || CheckCollisionRecs(player.hitbox,obs.gndR2) ||CheckCollisionRecs(player.hitbox,obs.plaR0) || CheckCollisionRecs(player.hitbox,obs.plaR1) || CheckCollisionRecs(player.hitbox,items.hea0)) {
                            camera.offset.x -=6.75;
                            bgv1.x -= 0.1f;
                            bgv2.x -= 0.2f;
                            bgv3.x -= 0.4f;
                            bgv4.x -= 0.8f;
                    }   }
                    
                    if (CheckCollisionRecs(player.hitbox,obs.walL0) || CheckCollisionRecs(player.hitbox,obs.walL1) || CheckCollisionRecs(player.hitbox,obs.gndL0) || CheckCollisionRecs(player.hitbox,obs.gndL1) || CheckCollisionRecs(player.hitbox,obs.gndL2) || CheckCollisionRecs(player.hitbox,obs.plaL0) || CheckCollisionRecs(player.hitbox,obs.plaL1) || CheckCollisionRecs(player.hitbox,obs.plaL2) || CheckCollisionRecs(player.hitbox,obs.plaL3) || CheckCollisionRecs(player.hitbox,obs.plaL4) || CheckCollisionRecs(player.hitbox,items.hea0)) {
                        onGround = true;
                    } else {
                        onGround = false;
                    }
                    
                    // Vertical movement input checking if player physics body is grounded
                    if (IsKeyDown(KEY_UP) && body->isGrounded && body->position.x > 1300 && body->position.x < 1400) {
                        body->velocity.y = -VELOCITY*5;
                        PlaySound(jumpsfx);
                    } else if (IsKeyDown(KEY_UP) && body->isGrounded && body->position.x > 3900 && body->position.x < 4000) {
                        body->velocity.y = -VELOCITY*5;
                        PlaySound(jumpsfx);
                    }
                    else if (IsKeyDown(KEY_UP) && body->isGrounded) {
                        PlaySound(jumpsfx1);
                        body->velocity.y = -VELOCITY*4;
                    }
                    
                    //Skip to Boss
                    if (IsKeyPressed(KEY_P) ){
                        body->position.x = 6000;
                        body->position.y = 300;
                        camera.offset.x = -5700;
                        camera.offset.y = 50;
                        enemy.fact = false;
                        enemy.tact = false;
                        enemy.ract = true;
                    }
                    
                    //Attack initialization
                    if (IsKeyPressed(KEY_D)){
                        slash.active = true;
                        slash.rec.y = body->position.y + 5;
                        PlaySound(punchsfx);
                    }
                    
                    if (slash.active){
                        if (slashTime < 10){
                            slashTime++;
                            slash.anim = true;
                            slash.rec.y = body->position.y - 12;
                            if (right) {
                                slash.rec.x = body->position.x + 15;
                                slash.poff.x = slash.rec.x - 65;
                            } else if (!right){
                                slash.rec.x = body->position.x - 55;
                                slash.poff.x = slash.rec.x;
                            }
                        } else if (slashTime >= 10){
                            slash.active = false;
                            slash.anim = false;
                            slashTime = 0;
                        }                        
                    }   
                    
                    //Punch Offset
                    
                    slash.poff.y = slash.rec.y - 13;
                    slash.soff.x = slash.out.x;
                    slash.soff.y = slash.out.y - 13;
                    
                    //Item Behavior
                    items.hea0.x = item0->position.x - 25;
                    items.hea0.y = item0->position.y - 20;
                    
                    //If slash get power up
                    if (CheckCollisionRecs(slash.rec,items.hea0)) {
                        PlaySound(gettingpu);
                        item0->position.y = 1000;
                        if (s.top == (MAXSIZE - 1) ) stack_full = 1;
                        else {
                            s.top = s.top + 1;
                            s.stk[s.top] = s.stk[s.top] + 1;
                        }       
                    }
                    
                    
                    if (slash.sho){
                        if (shootTime < 50){                            
                            shootTime++;
                            slash.anom = true;
                            slash.out.y = body->position.y - 12;
                            slash.fly += 15;
                            if (right) {
                                slash.out.x = body->position.x + 25 + slash.fly;
                            } else if (!right){
                                slash.out.x = body->position.x - 55 - slash.fly;
                            }
                        } else if (shootTime >= 50){
                            slash.sho = false;
                            slash.anom = false;
                            slash.fly = 0;
                            slash.out.y = 0;
                            shootTime = 0;
                        }
                    }   
                    
                    if (s.top == -1) {
                        pos1.x = -1000;
                        pos1.y = -1000;
                        pos2.x = -2000;
                        pos2.y = -2000;
                        pos3.x = -2000;
                        pos3.y = -2000;
                    }
                    if (s.top == 0) {
                        pos1.x = 80;
                        pos1.y = 87;
                        pos2.x = -2000;
                        pos2.y = -2000;
                        pos3.x = -2000;
                        pos3.y = -2000;
                    }
                    if (s.top == 1) {
                        pos1.x = 80;
                        pos1.y = 87;
                        pos2.x = 124;
                        pos2.y = 87;
                        pos3.x = -1000;
                        pos3.y = -1000;
                    }
                    if (s.top == 2) {
                        pos1.x = 80;
                        pos1.y = 87;
                        pos2.x = 124;
                        pos2.y = 87;
                        pos3.x = 168;
                        pos3.y = 87;    
                    }   
                    
                    //Enemy Encounter                
                    if (CheckCollisionRecs(player.hitbox,enemy.left) || CheckCollisionRecs(player.hitbox,enemy.batt)){
                        PlaySound(hitten);
                        if (IsKeyDown(KEY_RIGHT)) {
                            body->position.x -= 6.75;
                            camera.offset.x += 6.75;      
                        }
                        body->velocity.x = -VELOCITY*2;
                        body->velocity.y = VELOCITY*2;
                        camera.offset.x += 100;      
                    } 
                    
                    if (CheckCollisionRecs(player.hitbox,enemy.right) || CheckCollisionRecs(player.hitbox,enemy.bitt)){
                        PlaySound(hitten);
                        if (IsKeyDown(KEY_LEFT)) {
                            body->position.x += 6.75;
                            camera.offset.x -= 6.75;      
                        }
                        body->velocity.x = VELOCITY*2;
                        body->velocity.y = VELOCITY*2;
                        camera.offset.x -= 100;     
                    }
                    
                    // Camera target follows player
                    camera.target = (Vector2){ body->position.x + 20, body->position.y + 20 };
                    
        
                    if (camera.zoom > 3.0f) camera.zoom = 3.0f;
                    else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
                    
                    //Enemy behavior
                    enemy.ene0.x += enemy.moveX;
                    if (enemy.ene0.x > 1400 || enemy.ene0.x < 800) enemy.moveX *=-1;
                    if (CheckCollisionRecs(slash.rec,enemy.ene0) || CheckCollisionRecs(slash.out,enemy.ene0)) enemy.ene0.y = -1000;
                    
                    enemy.ene1.x += enemy.moveX;
                    if (enemy.ene1.x > 1900  || enemy.ene1.x < 1700) enemy.moveX *=-1; 
                    if (CheckCollisionRecs(slash.rec,enemy.ene1) || CheckCollisionRecs(slash.out,enemy.ene1)) enemy.ene1.y = -1000;       

                    enemy.ene2.x += enemy.moveX;
                    if (enemy.ene2.x > 3300  || enemy.ene2.x < 2700) enemy.moveX *=-1; 
                    if (CheckCollisionRecs(slash.rec,enemy.ene2) || CheckCollisionRecs(slash.out,enemy.ene2)) enemy.ene2.y = -1000;   

                    enemy.ene3.y += enemy.moveY;
                    if (enemy.ene3.y > 400  || enemy.ene3.y < -100) enemy.moveY *=-1; 
                    if (CheckCollisionRecs(slash.rec,enemy.ene2) || CheckCollisionRecs(slash.out,enemy.ene2)) enemy.ene2.y = -1000;           
                    
                    //Platform hitbox
                    obs.plaR0.x = platform0->position.x - 75;
                    obs.plaR0.y = platform0->position.y - 3;
                    obs.plaR1.x = platform1->position.x - 75;
                    obs.plaR1.y = platform1->position.y - 3;
                    obs.plaR2.x = platform2->position.x - 75;
                    obs.plaR2.y = platform2->position.y - 3;
                    obs.plaR3.x = platform3->position.x - 75;
                    obs.plaR3.y = platform3->position.y - 3;
                    obs.plaR4.x = platform4->position.x - 75;
                    obs.plaR4.y = platform4->position.y - 3;
                    obs.gndR0.x = ground0->position.x - 400;
                    obs.gndR0.y = ground0->position.y - 45;
                    obs.gndR1.x = ground1->position.x - 300;
                    obs.gndR1.y = ground1->position.y - 45;
                    obs.gndR2.x = ground2->position.x - 200;
                    obs.gndR2.y = ground2->position.y - 45;
                    obs.walR0.x = wallLeft->position.x - 50;
                    obs.walR0.y = wallLeft->position.y - 220;
                    obs.walR1.x = wallMid->position.x - 100;
                    obs.walR1.y = wallMid->position.y - 220;
                    
                    //animation hitbox
                    obs.plaL0.x = platform0->position.x - 70;
                    obs.plaL0.y = platform0->position.y - 10;
                    obs.plaL1.x = platform1->position.x - 70;
                    obs.plaL1.y = platform1->position.y - 10;
                    obs.plaL2.x = platform2->position.x - 70;
                    obs.plaL2.y = platform2->position.y - 10;
                    obs.plaL3.x = platform3->position.x - 70;
                    obs.plaL3.y = platform3->position.y - 10;
                    obs.plaL4.x = platform4->position.x - 70;
                    obs.plaL4.y = platform4->position.y - 10;
                    obs.gndL0.x = ground0->position.x - 390;
                    obs.gndL0.y = ground0->position.y - 55;
                    obs.gndL1.x = ground1->position.x - 290;
                    obs.gndL1.y = ground1->position.y - 55;
                    obs.gndL2.x = ground2->position.x - 190;
                    obs.gndL2.y = ground2->position.y - 55;
                    obs.walL0.x = wallLeft->position.x - 40;
                    obs.walL0.y = wallLeft->position.y - 235;
                    obs.walL1.x = wallMid->position.x - 90;
                    obs.walL1.y = wallMid->position.y - 235;
                    
                    //Tutorial level
                    if (body->position.x < 1500){
                        platform0->position.x += obs.moveX;
                        if (platform0->position.x > 1200 || platform0->position.x < 1000) obs.moveX *= -1;
                        ground0->position.x = 400;
                        ground0->position.y = 450;
                        ground1->position.x = 1200;
                        ground1->position.y = 450;
                        ground2->position.x = 1800;
                        ground2->position.y = 450;     
                        wallMid->position.x = 1500;
                        wallLeft->position.x = -45;
                        enemy.left.x = enemy.ene0.x - 1;
                        enemy.left.y = enemy.ene0.y - 1;
                        enemy.right.x = enemy.ene0.x + 25;
                        enemy.right.y = enemy.ene0.y - 1;
                    }
                    
                    //Level 1
                    if (body->position.x >= 1500 && body->position.x < 3500){
                        platform1->position.x = 2000;
                        platform1->position.y += obs.moveY;
                        if (platform1->position.y > 250|| platform1->position.y < 100) obs.moveY *= -1;
                        ground1->position.x = 2500;
                        ground1->position.y = 200;
                        ground0->position.x = 3000;
                        ground0->position.y = 350;       
                        ground2->position.x = 1800;
                        ground2->position.y = 400;         
                        wallMid->position.x = 1500;
                        enemy.left.x = enemy.ene1.x - 1;
                        enemy.left.y = enemy.ene1.y - 1;
                        enemy.right.x = enemy.ene1.x + 25;
                        enemy.right.y = enemy.ene1.y - 1;
                        if (body->position.x >= 2000){
                        enemy.left.x = enemy.ene2.x - 1;
                        enemy.left.y = enemy.ene2.y - 1;
                        enemy.right.x = enemy.ene2.x + 25;
                        enemy.right.y = enemy.ene2.y - 1;                        
                        }
                    }
                    if (body->position.x >= 3500){
                        ground2->position.x = 3800;
                        ground2->position.y = 400;  
                        wallLeft->position.x = 4400;
                        wallLeft->position.y = 300;
                        wallMid->position.x = 4100;
                        platform1->position.x = 4700;
                        platform1->position.y += obs.moveY;
                        if (platform1->position.y > 300 || platform1->position.y < 0) obs.moveY *= -1;
                        platform2->position.y += obs.moveY;
                        if (platform2->position.y > 500 || platform2->position.y < 200) obs.moveY *= -1;
                        platform3->position.x += obs.moveX;
                        if (platform3->position.x > 5600 || platform3->position.x < 5200) obs.moveX *= -1;
                        platform4->position.y += obs.moveY;
                        if (platform4->position.y > 300 || platform4->position.y < 0) obs.moveY *= -1;
                        enemy.left.x = enemy.ene3.x - 1;
                        enemy.left.y = enemy.ene3.y - 1;
                        enemy.right.x = enemy.ene3.x + 25;
                        enemy.right.y = enemy.ene3.y - 1;
                    }
                    if (body->position.x >= 5000){
                        wallLeft->position.x = 6000;
                        wallLeft->position.y = 500;
                        ground2->position.x = 6300;
                        ground2->position.y = 400; 
                        ground1->position.x = 6800;
                        ground1->position.y = 400;
                    }
                    if (body->position.x >= 7050){      //Boss Level
                        camera.offset.x = -7035;
                        ground0->position.x = 7500;
                        ground0->position.y = 375;
                        wallLeft->position.x = 7050;
                        wallLeft->position.y = 225;
                        wallMid->position.x = 7950;
                        wallMid->position.y = 225;
                        enemy.fact = true;      
                        enemy.tact = true;     
                    }
                    
                    //Boss Behavior
                    if(CheckCollisionRecs(slash.rec, enemy.boss)) enemy.beat -= 2;
                    if(CheckCollisionRecs(slash.out, enemy.boss)) enemy.beat -= 10;
                    if(CheckCollisionRecs(player.hitbox, enemy.bsta)){
                        enemy.boss.x = 7650;
                        enemy.boss.y = 150;
                        enemy.batt.x = enemy.boss.x + 100;
                        enemy.batt.y = 175;
                        enemy.bitt.x = enemy.boss.x + 100;
                        enemy.bitt.y = 175;              
                        enemy.beat = 500;
                    }
                    if (enemy.fact){
                        enemy.time++;
                        enemy.catt++;
                        if (enemy.tact){
                            if (enemy.ract){
                                enemy.batt.x -= enemy.matt; 
                            } else {
                                enemy.bitt.x += enemy.matt;
                            }
                        }
                        if (CheckCollisionRecs(obs.walR0, enemy.batt) || CheckCollisionRecs(obs.walR1, enemy.batt)){
                            enemy.batt.x = enemy.boss.x + 100;
                            enemy.batt.y += 50;
                        }
                        if (CheckCollisionRecs(obs.walR0, enemy.bitt) || CheckCollisionRecs(obs.walR1, enemy.bitt)){
                            enemy.bitt.x = enemy.boss.x + 100;
                            enemy.bitt.y += 50;
                        }   
                        if (enemy.catt >= 100){
                            enemy.batt.y = enemy.boss.y + 25;
                            enemy.bitt.y = enemy.boss.y + 25;
                            enemy.catt = 0;
                        }
                        
                        if (enemy.time < 100){
                            if (CheckCollisionRecs(player.hitbox,enemy.boss)){
                                PlaySound(hitten);
                                if (IsKeyDown(KEY_RIGHT)) {
                                    body->position.x -= 6.75;
                                    camera.offset.x += 6.75;      
                                }   
                            }
                        } else if (enemy.time >= 100 && enemy.time < 600){   
                            if (CheckCollisionRecs(player.hitbox,enemy.boss)){
                                PlaySound(hitten);
                                if (IsKeyDown(KEY_LEFT)) {
                                    body->position.x += 6.75;
                                    camera.offset.x -= 6.75;      
                                }
                            }                        
                            enemy.boss.x = 7100;
                            enemy.ract = false;
                            enemy.batt.y = -500;
                        } else if (enemy.time >= 600){                            
                            enemy.boss.x = 7650;
                            enemy.ract = true;     
                            enemy.bitt.y = -500;
                            enemy.time = 0;
                        }
                    }
                    if (enemy.beat <= 0) {
                        enemy.boss.y = -1000;
                        gameScreen = CREDITS;
                        PauseMusicStream(game_bgm);
                        state = 0;
                    }
                }
            }
        }
        
        
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(WHITE);
                switch(gameScreen){
                    
                    //Untuk Layer Logo
                    case LOGO   : {
                        switch(state)   {
                            case 0 :{ 
                            DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            PlaySound(LS);
                            } break;
                            case 1 :{
                            DrawText(SubText(desc,0,splashCounter/13)                                                                       //Penulisan Animasi Text(dimulai dari index text nomor 0 dan mulai hingga setiap splashCounter/13)
                            ,screenWidth/3 + 25, screenHeight*2/3 + 18, 23, BLACK);
                            DrawTexture(BL,screenWidth/3 + 25, screenHeight/4,RAYWHITE);
                            } break;
                            case 2 :{ 
                            DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            } break;
                        }
                    }break;
                    
                    //Untuk Layer Tribute
                    case TRIBUTE : {
                        switch(state)   {
                            case 1 :{
                               DrawText("Powered by", screenWidth/3 + 25, screenHeight/5 - 5, 20, BLACK);
                               DrawTexture(RL, screenWidth/2 - RL.width/2 + 5, screenHeight/2 - RL.height/2 + screenHeight/35, RAYWHITE);
                            } break;
                            case 2 :{
                                DrawTexture(BS,0,0,Fade(BLACK,alpha));
                                PlayMusicStream(MS);
                            } break;
                        }
                    }break;
                    
                    //Untuk Layer Disclaimer
                    case DISCLAIMER : {
                        switch(state)   {
                            case 1 : {
                                DrawText("© 2018 Enveriesage Studios.", screenWidth/4 + 13, screenHeight/3 + 50, 30, BLACK);
                                DrawText("All rights Reserved.", screenWidth/3 + 8, screenHeight/2 + 10, 30, BLACK);
                            } break;
                            case 2 : {
                                DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            } break;
                        }
                    }break;
                    
                    case TITLE : {
                        switch (state) {
                            case 1 : {
                                if (mtitle_a) {
                                    DrawTexture(mainTB, 0, 0, RAYWHITE);
                                }
                                else {
                                    DrawTexture(mainTB, 0, 0, RAYWHITE);
                                    DrawText("Press SPACE BAR to continue", screenWidth/3 + 50, screenHeight*5/7 + 10, 15, Fade(GRAY,alpha));    
                                } 
                            } break;
                            case 2 : {
                                DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            } break;
                        }
                    } break;
                    
                    case TS1 : {
                        switch (state) {
                            case 1 : {
                                DrawTexture(TSB1, 0, 0, RAYWHITE);
                            }break;
                        }
                    } break;
                    
                    case TS2 : {
                        switch (state) {
                            case 0 : {
                                DrawTexture(TSB2, 0, 0, RAYWHITE);
                            } break;
                        }
                    } break;
                    
                    case TS3 : {
                        switch (state) {
                            case 0 : {
                                DrawTexture(TSB3, 0, 0, RAYWHITE);
                            } break;
                        }
                    } break;
                       
                    case TS4 : {
                        switch (state) {
                            case 0 : {
                                DrawTexture(TSB4, 0, 0, RAYWHITE);
                            } break;
                        }
                    } break;
                
                    case BGAMING : {
                        switch(state)   {
                            case 1 : {
                                if (btrans1_a) {
                                    DrawTexture(bgaming1, 1, 1, RAYWHITE);
                                    DrawTexture(btrans1, screenWidth/2 - 10, screenHeight * 2/3, RAYWHITE);
                                }
                                else {
                                    DrawTexture(bgaming1, 1, 1, RAYWHITE);
                                    DrawTexture(btrans1, screenWidth/2 - 10, screenHeight * 2/3 + 20, RAYWHITE);
                                }
                            } break;
                            case 2 : {
                                if (btrans1_a) {
                                    DrawTexture(bgaming2, 1, 1, RAYWHITE);
                                    DrawTexture(btrans2, screenWidth/2 - 10, screenHeight * 1/5, RAYWHITE);
                                }
                                else {
                                    DrawTexture(bgaming2, 1, 1, RAYWHITE);
                                    DrawTexture(btrans2, screenWidth/2 - 10, screenHeight * 1/5 - 20, RAYWHITE);
                                }
                            } break;
                        }
                    } break;
                    
                    case GAMING : {
                        switch (state) {
                            case 0 : {
                                DrawTexture(BS, 0, 0, RAYWHITE);
                                DrawText("Chapter 1", screenWidth/3 + 20, screenHeight/2 - 10, 50, RAYWHITE);
                            } break;
                            case 1 : {  
                                DrawTexture(bg0, 0, 0, WHITE);
                                DrawTexture(bg1, bgv1.x, bgv1.y, RAYWHITE);
                                DrawTexture(bg2, bgv2.x, bgv2.y, RAYWHITE);
                                DrawTexture(bg3, bgv3.x, bgv3.y, RAYWHITE);
                                DrawTexture(bg4, bgv4.x, bgv4.y, RAYWHITE);
                            
                                BeginMode2D(camera);
                                    // Draw created physics bodies
                                    
                                    /*
                                    int bodiesCount = GetPhysicsBodiesCount();
                                    for (int i = 0; i < bodiesCount; i++)
                                    {
                                        PhysicsBody body = GetPhysicsBody(i);

                                        int vertexCount = GetPhysicsShapeVerticesCount(i);
                                        for (int j = 0; j < vertexCount; j++)
                                        {
                                            // Get physics bodies shape vertices to draw lines
                                            // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                                            Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                                            int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                                            Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                                            DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
                                        }
                                    }
                                    */
                                    
                                    DrawTexture(tile1, ground0->position.x - 400, ground0->position.y - 80, RAYWHITE);
                                    DrawTexture(tile2, ground1->position.x - 300, ground1->position.y - 58, RAYWHITE);
                                    DrawTexture(tile3, ground2->position.x - 200, ground2->position.y - 60, RAYWHITE);
                                    DrawTexture(platform_tex, platform0->position.x - 75, platform0->position.y, RAYWHITE);
                                    DrawTexture(platform_tex, platform1->position.x - 75, platform1->position.y, RAYWHITE);
                                    DrawTexture(platform_tex, platform2->position.x - 75, platform2->position.y, RAYWHITE);
                                    DrawTexture(platform_tex, platform3->position.x - 75, platform3->position.y, RAYWHITE);
                                    DrawTexture(platform_tex, platform4->position.x - 75, platform4->position.y, RAYWHITE);
                                    DrawTexture(wall_1, wallMid->position.x - 100, wallMid->position.y - 230, RAYWHITE);
                                    DrawTexture(wall_2, wallLeft->position.x - 50, wallLeft->position.y - 230, RAYWHITE);
                                
                                    // Draw textures
                                    if(right){
                                        if(slash.anim) DrawTextureRec(powerPunchR, ppR_rec, slash.poff, RAYWHITE);
                                        if(slash.anom) DrawTextureRec(powerPunchR, ppR_rec, slash.soff, RAYWHITE);
                                        if((slash.anim || slash.anom) && onGround) {              // Draw part of the texture
                                            DrawTextureRec(gatotpR, gatotpR_rec, player.offset, WHITE);
                                        } else if (anim && onGround) {           
                                            DrawTextureRec(gatotR, gatotR_rec, player.offset, WHITE);
                                        } else if (!anim && onGround) {
                                            DrawTextureRec(gatotiR, gatotiR_rec, player.offset, WHITE);
                                        }  else if (!onGround && (slash.anim || slash.anom)) {
                                            DrawTextureRec(gatotjpR, gatotjpR_rec, player.offset, WHITE);
                                        } else {
                                            DrawTextureRec(gatotjR, gatotjR_rec, player.offset, WHITE);
                                        }  
                                        
                                        
                                    } else if (!right){                                          
                                        if(slash.anim) DrawTextureRec(powerPunchL, ppL_rec, slash.poff, RAYWHITE);
                                        if(slash.anom) DrawTextureRec(powerPunchL, ppL_rec, slash.soff, RAYWHITE);
                                        if((slash.anim || slash.anom) && onGround) {              // Draw part of the texture
                                            DrawTextureRec(gatotpL, gatotpR_rec, player.offset, WHITE);
                                        } else if(anim && onGround) {
                                            DrawTextureRec(gatotL, gatotL_rec, player.offset, WHITE);
                                        } else if (!anim && onGround) {
                                            DrawTextureRec(gatotiL, gatotiL_rec, player.offset, WHITE);
                                        } else if (!onGround && (slash.anim || slash.anom)) {
                                            DrawTextureRec(gatotjpL, gatotjpR_rec, player.offset, WHITE);
                                        } else {
                                            DrawTextureRec(gatotjL, gatotjL_rec, player.offset, WHITE);
                                        }
                                    }
                                       
                                    if (enemy.moveX > 0){
                                        if (enemy.act0) DrawTextureRec(tankR, eBox, enemy.e0off, WHITE);
                                        if (enemy.act1) DrawTextureRec(jetR, eBox1, enemy.e1off, WHITE);
                                        if (enemy.act2) DrawTextureRec(jetR, eBox1, enemy.e2off, WHITE);
                                    } else {
                                        if (enemy.act0) DrawTextureRec(tankL, eBox, enemy.e0off, WHITE);
                                        if (enemy.act1) DrawTextureRec(jetL, eBox1, enemy.e1off, WHITE);
                                        if (enemy.act2) DrawTextureRec(jetL, eBox1, enemy.e2off, WHITE);                                        
                                    }
                                    
                                    if (enemy.act3) DrawTextureRec(spike, mBox, enemy.e3off, WHITE);
                                    if (enemy.act4) DrawTextureRec(spike, mBox, enemy.e3off, WHITE);
                                    if (enemy.act5) DrawTextureRec(spike, mBox, enemy.e3off, WHITE);
                                    if (items.lth0) DrawTextureRec(chestC, mBox, items.h0off, WHITE);
                                    
                                    if (enemy.boss.x >= 7500){
                                        DrawTexture(bossL, enemy.boff.x, enemy.boss.y , RAYWHITE);
                                        if (enemy.tact) {
                                            DrawTexture(bulletL, enemy.baoff.x, enemy.baoff.y, RAYWHITE);
                                            
                                        }
                                    } else {
                                        DrawTexture(bossR, enemy.boff.x, enemy.boss.y , RAYWHITE);
                                        if (enemy.tact) {
                                            DrawTexture(bulletR, enemy.bioff.x, enemy.bioff.y, RAYWHITE);          
                                            
                                        }
                                    }                       
                                    
                                EndMode2D();
                                //Draw Power Ups
                                    
                                DrawTexture(power_up, 70, 80, RAYWHITE);
                                DrawTexture(power_upb, pos1.x, pos1.y, RAYWHITE);
                                DrawTexture(power_upb, pos2.x, pos2.y, RAYWHITE);
                                DrawTexture(power_upb, pos3.x, pos3.y, RAYWHITE);
                            } break;
                        }
                    
                    }break;
                    
                    case CREDITS : {
                         switch(state)   {
                            case 0 :{ 
                            DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            } break;
                            case 1 :{
                            DrawText("YOU WIN" ,screenWidth/2 - 120, screenHeight/2 - 20, 50, BLACK);
                            } break;
                            case 2 :{ 
                            DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            } break;
                        }
                    }break;
                    
                    case EXIT   : {
                        switch(state)   {
                            case 0 :{ 
                            DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            } break;
                            case 1 :{
                            DrawText("Redefined Your Envisage"                                                                       //Penulisan Animasi Text(dimulai dari index text nomor 0 dan mulai hingga setiap splashCounter/13)
                            ,screenWidth/3 + 25, screenHeight*2/3 + 18, 23, BLACK);
                            DrawTexture(BL,screenWidth/3 + 25, screenHeight/4,RAYWHITE);
                            } break;
                            case 2 :{ 
                            DrawTexture(BS,0,0,Fade(BLACK,alpha));
                            } break;
                        }
                    }break;
                    
                
                }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    ClosePhysics();       // Unitialize physics
    
    UnloadImage(WI);
    UnloadSound(WIN);
    //MAIN
    UnloadMusicStream(MS);
    UnloadSound(LS);
    UnloadTexture(BL);
    UnloadTexture(BS);
    UnloadTexture(RL);
    
    //Game Texture
    UnloadTexture(power_up);
    UnloadTexture(power_upb);
    UnloadImage(imgTile0);
    UnloadImage(imgTile3);
    UnloadTexture(tile1);
    UnloadTexture(tile2);
    UnloadTexture(tile3);
    UnloadTexture(bg0);
    UnloadTexture(bg1);
    UnloadTexture(bg2);
    UnloadTexture(bg3);
    UnloadTexture(bg4);
    UnloadTexture(platform_tex);
    UnloadTexture(wall_1);
    UnloadTexture(wall_2);
    UnloadMusicStream(game_bgm);
    
    //Unload Gatot Move
    UnloadTexture(gatotR);
    UnloadTexture(gatotL);
    //Unload Gatot Idle
    UnloadTexture(gatotiR);
    UnloadTexture(gatotiL);
    //Unload Gatot Jump
    UnloadTexture(gatotjR);
    UnloadTexture(gatotjL);
    //Unload Gatot Punch
    UnloadTexture(powerPunchR);
    UnloadTexture(powerPunchL);

    //Unload Items
    UnloadTexture(chestC);
    UnloadTexture(chestO);
    
    //Unload Enemies
    UnloadTexture(jetL);
    UnloadTexture(jetR);
    UnloadTexture(tankL);
    UnloadTexture(tankR);
    UnloadTexture(spike);
    UnloadTexture(bossL);
    UnloadTexture(bossR);
    UnloadTexture(bulletL);
    UnloadTexture(bulletR);

    //Unload Title Background
    UnloadTexture(mainTB);
    UnloadTexture(TSB1);
    UnloadTexture(TSB2);
    UnloadTexture(TSB3);
    UnloadTexture(TSB4);
    UnloadSound(mainsfx1);
    UnloadSound(mainsfx2);
    
    //Unload BGAMING Screen
    UnloadTexture(bgaming1);
    UnloadTexture(btrans1);
    UnloadTexture(bgaming2);
    UnloadTexture(btrans2);
    UnloadSound(mainsfx3);
    
    //Gatot SFX
    UnloadSound(punchsfx);
    UnloadSound(jumpsfx);
    UnloadSound(jumpsfx1);
    UnloadSound(hitten);
    UnloadSound(gettingpu);

    
    CloseAudioDevice();
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;

}