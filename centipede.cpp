#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX;
const int gameColumns = resolutionY / boxPixelsY;

int gameGrid[gameRows][gameColumns] = {};
int gameGrid2[gameRows][gameColumns]={};
int bulletHits[gameRows][gameColumns] = {};
int hits[gameRows][gameColumns]={};

const int x = 0;
const int y = 1;
const int exists = 2;

void drawPlayer(sf::RenderWindow &window, float player[], sf::Sprite &playerSprite);
void moveBullet(float bullet[], sf::Clock &bulletClock);
void drawBullet(sf::RenderWindow &window, float bullet[], sf::Sprite &bulletSprite);
void spawnMushrooms(int bulletHits[gameRows][gameColumns]);
void handleBulletCollision(float bullet[], sf::Sprite &bulletSprite, float xformushroom, float yformushroom, int i, int j, sf::RenderWindow &window);
void draw_centipede(int centipedex,int centipedey,sf::RenderWindow &window,sf::Sprite &CentipedeSprite);
void draw_centipede_head(int centipedex,int centipedey,sf::RenderWindow &window,sf::Sprite &CentipedeHeadSprite);
int* movement_keera(const int inputArray[]);
//void spawnMushroomsnew(int mushroom_array[][30]);
void draw_mushrooms (int mushroomx,int mushroomy,sf::RenderWindow &window,sf::Sprite &mushroomSprite);
void detectCentipedeMushroomCollision(int position_centipede[][12], int mushroom_array[][30], int direction_centipede[12], int mushroom_lives[30]);
void detectBulletandMushroom(float bullet[],int mushroom_array[][30], int mushroom_lives[30]);
void draw_mushrooms_half(int mushroomx,int mushroomy,sf::RenderWindow &window,sf::Sprite &fleaSprite);
void detectBulletandHalfMushroom(float bullet[],int half_mushroom_array[][30] ,int mushroom_lives[30], int score[]);
int CentipedeHitsPlayer(int position_centipede[][12], float player[2],sf::RenderWindow &window,sf::Sprite &gameoverSprite, int gameover);
void draw_gameover(sf::RenderWindow &window, sf::Sprite &gameoverSprite);
void BulletHitsCentipede(int position_centipede[][12], float bullet[], int centipede_death_array[12], int score[], sf::RenderWindow &window);
void display_score(sf::RenderWindow &window, int score[]);







int main()
{
    srand(time(0));
    

    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar);
    window.setSize(sf::Vector2u(640, 640));
    window.setPosition(sf::Vector2i(100, 0));

    sf::Music bgMusic;
    bgMusic.openFromFile("Music/field_of_hopes.ogg");
    bgMusic.play();
    bgMusic.setVolume(50);

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    backgroundTexture.loadFromFile("Textures/background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * 0.20));

    sf::Texture CentipedeTexture;
    sf::Sprite CentipedeSprite;
    CentipedeTexture.loadFromFile("Textures/c_body_left_walk.png");
    CentipedeSprite.setTexture(CentipedeTexture);
    CentipedeSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    sf::Texture CentipedeHeadTexture;
    sf::Sprite CentipedeHeadSprite;

    sf::Texture bulletTexture;
    sf::Sprite bulletSprite;
    bulletTexture.loadFromFile("Textures/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    sf::Texture mushroomTexture;
    sf::Sprite mushroomSprite;
    mushroomTexture.loadFromFile("Textures/mushroom.png");
    mushroomSprite.setTexture(mushroomTexture);
    mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
    mushroomSprite.setColor(sf::Color(255, 255, 255, 255));

    sf::Texture fleaTexture;
    sf::Sprite fleaSprite;
    fleaTexture.loadFromFile("Textures/flea.png");
    fleaSprite.setTexture(fleaTexture);
    fleaSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
    fleaSprite.setColor(sf::Color(255, 255, 255, 255));

    sf::Texture gameoverTexture;
    sf::Sprite gameoverSprite;
    gameoverTexture.loadFromFile("Textures/gameover.png");
    gameoverSprite.setTexture(gameoverTexture);
    gameoverSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
    gameoverSprite.setColor(sf::Color(255, 255, 255, 255));

    sf::Font font;
    font.loadFromFile("myfont.ttf"); 
 
    sf::Text text;
    text.setFont(font); // Set the font
    text.setCharacterSize(24); // Set the character size
    text.setFillColor(sf::Color::White);

    //float score_positionx= 100.0f;
    //float score_positiony= 200.0f;
    //text.setPosition(x, y);
    

    int detect_collision_mushroom_centipede=0;

    

    //int a = rand() % 12 + 9;
    //int b = rand() % 12 + 7;
    int a = 12;
    int b = 5;
    int gameover=0;

    const float centipedeSpeed = 4.0f;
    const float playerSpeed = 2.0f;
    int check_sprite_movement=0;
    //VARIABLES FOR CENTIPEDE
    int direction_centipede[12]={1,1,1,1,1,1,1,1,1,1,1,1};
    //int position_centipede[2][12]={{37,69,101,133,165,197,229,261,293,325,357,389},{5,5,5,5,5,5,5,5,5,5,5,5}};
    int position_centipede[2][12]={};
    int checker_array[12]={0,0,0,0,0,0,0,0,0,0,0,0};

    //position_centipede[1]=random_starting_position_y * boxPixelsY;
    /*for(int i=0; i<12;i++)
    {
        position_centipede[i]=random_starting_position_y;
    }*/


    int random_starting_position_y = rand()%7 + 2;
    int random_starting_position_x = rand()%15 + 2;

    position_centipede[0][0]=random_starting_position_x ;
    position_centipede[1][0]=random_starting_position_y*32 ;
    
    for(int i=1; i<12; i++)
    {      
            position_centipede[0][i] = position_centipede[0][i-1] + 1;
            position_centipede[1][i] = random_starting_position_y * 32;
    }

    for(int i=0; i<12; i++)
    {
        position_centipede[0][i] = position_centipede[0][i] * 32;
    }


    //scoring:
    int score[1];
    score[0]=5;


    
    
    int number_of_mushroom=30;
    int mushroom_array[2][30]={};
    int half_mushroom_array[2][30]={};
    int count=0;
    for(int i=0;i<30;++i)
    {
        mushroom_array[0][i] = (rand() % gameColumns) *32;
        mushroom_array[1][i] = (rand() % gameRows) *32;
        half_mushroom_array[0][i] = mushroom_array[0][i];
        half_mushroom_array[1][i] = mushroom_array[1][i];
    }
    


    //VARIABLES FOR MUSHROOM

    int mushroom_lives[30];
    for(int i=0; i<30; i++)
    {
        mushroom_lives[i]=2;
    }

    float player[2] = {};
    player[x] = (gameColumns / 2) * boxPixelsX;
    player[y] = (gameColumns * 3.5 / 4) * boxPixelsY;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    playerTexture.loadFromFile("Textures/player.png");
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    float bullet[3] = {};
    bullet[x] = player[x];
    bullet[y] = player[y] - boxPixelsY;
    bullet[exists] = false;
    sf::Clock bulletClock;
    bulletTexture.loadFromFile("Textures/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    //for centipede death
    int centipede_death_array[12]={1,1,1,1,1,1,1,1,1,1,1,1};


    //spawnMushrooms(bulletHits);
    //spawnMushroomsnew(mushroom_array);

    for(int i=0;i<gameRows;++i)
    {
        for(int j=0;j<gameColumns;++j)
        {
            //cout<<gameGrid[i][j];
            if(gameGrid[i][j]==1)
            {
                //cout<<"hi  ";}
            }
        //cout<<endl;
        }

        //int countmushcent=0;










    while (window.isOpen() )
    { 
        const float movementSpeed = playerSpeed;

        window.draw(backgroundSprite);
        drawPlayer(window, player, playerSprite);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !bullet[exists])
        {
            bullet[exists] = true;
            bullet[x] = player[x];
            bullet[y] = player[y] - boxPixelsY;
            bulletClock.restart();
        }

        
        sf::Texture CentipedeTexture;
        sf::Sprite CentipedeSprite;
        CentipedeTexture.loadFromFile("Textures/c_body_left_walk.png");
        CentipedeSprite.setTexture(CentipedeTexture);
        CentipedeSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

        CentipedeHeadTexture.loadFromFile("Textures/c_head_left_walk.png");
        CentipedeHeadSprite.setTexture(CentipedeHeadTexture);
        CentipedeHeadSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));




		sf::Texture bulletTexture;
        sf::Sprite bulletSprite;
        bulletTexture.loadFromFile("Textures/bullet.png");
        bulletSprite.setTexture(bulletTexture);
        bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


        sf::Texture mushroomTexture;
        sf::Sprite mushroomSprite;
        mushroomTexture.loadFromFile("Textures/mushroom.png");
        mushroomSprite.setTexture(mushroomTexture);
        mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY - 5));      

        sf::Texture gameoverTexture;
        sf::Sprite gameoverSprite;
        gameoverTexture.loadFromFile("Textures/gameover.png");
        gameoverSprite.setTexture(gameoverTexture);
        gameoverSprite.setTextureRect(sf::IntRect(255, 255, 255, 255));
        gameoverSprite.setColor(sf::Color(255, 255, 255, 255));   



        draw_centipede_head(position_centipede[0][11],position_centipede[1][11],window,CentipedeHeadSprite);
        for(int i=0;i<11;++i)
        {
            if(centipede_death_array[i]==1)
            {
                draw_centipede(position_centipede[0][i],position_centipede[1][i],window,CentipedeSprite);
            }
        }
        for(int i=0;i<12;++i)
        {
            int inputArray[4]={position_centipede[0][i],position_centipede[1][i],direction_centipede[i],checker_array[i]};
            int* resultArray  = movement_keera(inputArray);
            position_centipede[0][i]=resultArray[0];
            position_centipede[1][i]=resultArray[1];
            direction_centipede[i]=resultArray[2];
            checker_array[i]=resultArray[3];
            delete[] resultArray;
        }

        
        //DRAWING THE MUSHROOMS
        for(int i=0;i<30;++i)
        {
            if(mushroom_lives[i]==2)
            {
                draw_mushrooms(mushroom_array[0][i],mushroom_array[1][i],window,mushroomSprite);
            }
        }

        for(int i=0; i<30; i++)
        {
            if(mushroom_lives[i]==1)
            {
                //cout<<"ENTERED";
                draw_mushrooms_half(half_mushroom_array[0][i], half_mushroom_array[1][i], window, fleaSprite);
            }
        }

        if(gameover==1)
        {
            cout<<"HERJFR"<<"   ";
            draw_gameover(window, gameoverSprite);
            window.close();
        }

        display_score(window, score);

        //int* resultArray=detectCentipedeMushroomCollision(position_centipede,  mushroom_array,count, detect_collision_mushroom_centipede);
        //detect_collision_mushroom_centipede=detectCentipedeMushroomCollision(position_centipede,  mushroom_array,count, detect_collision_mushroom_centipede);
        detectCentipedeMushroomCollision(position_centipede,  mushroom_array, direction_centipede, mushroom_lives);
        detectBulletandMushroom(bullet, mushroom_array, mushroom_lives);
        detectBulletandHalfMushroom(bullet, half_mushroom_array, mushroom_lives, score);


        gameover= CentipedeHitsPlayer(position_centipede, player, window, gameoverSprite, gameover);
        CentipedeHitsPlayer(position_centipede, player, window, gameoverSprite, gameover);

        BulletHitsCentipede(position_centipede, bullet, centipede_death_array, score, window);


        
        if (bullet[exists])
        {
            moveBullet(bullet, bulletClock);
            drawBullet(window, bullet, bulletSprite);
        }

		

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player[x] > 0)
        {
            player[x] -= movementSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player[x] < resolutionX - boxPixelsX)
        {
            player[x] += movementSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player[y] > resolutionY - 5 * boxPixelsY)
        {
            player[y] -= movementSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player[y] < resolutionY - boxPixelsY)
        {
            player[y] += movementSpeed;
        }

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        window.display();
        window.clear();
    }
    
    }
    return 0;

}


















void draw_centipede(int centipedex,int centipedey,sf::RenderWindow &window,sf::Sprite &CentipedeSprite)
{
        CentipedeSprite.setPosition(centipedex, centipedey);
        window.draw(CentipedeSprite);
}

void draw_centipede_head(int centipedex,int centipedey,sf::RenderWindow &window,sf::Sprite &CentipedeHeadSprite)
{
        CentipedeHeadSprite.setPosition(centipedex, centipedey);
        window.draw(CentipedeHeadSprite);
}

int* movement_keera(const int inputArray[]){
        int* resultArray = new int[4];
        int dir_checker=1;
        int movement_speed=boxPixelsX;
        movement_speed=movement_speed-31;
        for (int i = 0; i < 4; ++i) {
        resultArray[i] = inputArray[i];
    }
    int our_checker=resultArray[3];
    //cout<<"OUR CHECKER"<<our_checker<<endl;
    if(resultArray[1] > resolutionY - (boxPixelsY))
    {
        our_checker=1;
        resultArray[3]=1;
    }
    if(resultArray[1] < resolutionY - (boxPixelsY*5))
    {
        our_checker=0;
        resultArray[3]=0;
      //  cout<<"Checker"<<our_checker<<endl;
    }
    if(our_checker==1)
    {
        dir_checker=-1;
    }
    
    if(our_checker==0)
    {
        dir_checker=1;
    }
    if (resultArray[0] < 0 || resultArray[0] > resolutionX - boxPixelsX)
        {
            resultArray[1] = resultArray[1] + (boxPixelsY*dir_checker);
            resultArray[2] = (resultArray[2]*(-1));
        }
    resultArray[0] = resultArray[0] + (movement_speed*resultArray[2]);
    return resultArray;
}

void drawPlayer(sf::RenderWindow &window, float player[], sf::Sprite &playerSprite)
{
    playerSprite.setPosition(player[x], player[y]);
    window.draw(playerSprite);
}

void moveBullet(float bullet[], sf::Clock &bulletClock)
{
    if (bulletClock.getElapsedTime().asMilliseconds() < 20)
        return;

    bulletClock.restart();
    bullet[y] -= 20;

    if (bullet[y] < -boxPixelsY)
    {
        bullet[exists] = false;
    }
}

void drawBullet(sf::RenderWindow &window, float bullet[], sf::Sprite &bulletSprite)
{
    bulletSprite.setPosition(bullet[x], bullet[y]);
    //cout<<bullet[x]<<endl<<bullet[y]<<endl;
    window.draw(bulletSprite);
}

void draw_mushrooms (int mushroomx,int mushroomy,sf::RenderWindow &window,sf::Sprite &mushroomSprite)
{
        mushroomSprite.setPosition(mushroomx, mushroomy);
        window.draw(mushroomSprite);
}

void draw_mushrooms_half (int mushroomx,int mushroomy,sf::RenderWindow &window,sf::Sprite &fleaSprite)
{
        fleaSprite.setPosition(mushroomx, mushroomy);
        window.draw(fleaSprite);
}

void spawnMushrooms(int bulletHits[gameRows][gameColumns])
{
    int mushrooms = rand() % 10 + 20;
    for (int i = 0; i < mushrooms; i++)
    {
        int xformushroom = rand() % gameColumns;
        int yformushroom = rand() % gameRows;

        gameGrid[xformushroom][yformushroom] = 1;
        bulletHits[xformushroom][yformushroom] = 0;
    }
}

void handleBulletCollision(float bullet[], sf::Sprite &bulletSprite, float xformushroom, float yformushroom, int i, int j, sf::RenderWindow &window)

{
    sf::Texture mushroom0Texture;
    sf::Sprite mushroom0Sprite;
    mushroom0Sprite.setTexture(mushroom0Texture);
    mushroom0Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY - 5));
    mushroom0Sprite.setPosition(xformushroom, yformushroom);
    window.draw(mushroom0Sprite);

    if (bullet[exists])

    {

        sf::FloatRect bulletBounds = bulletSprite.getGlobalBounds();

        sf::FloatRect mushroomBounds(xformushroom, yformushroom, boxPixelsX, boxPixelsY);


        if (bulletBounds.intersects(mushroomBounds))

        {

            bullet[exists] = false;


            if (!bulletHits[i][j])

            {

                bulletHits[i][j] = true;


                gameGrid[i][j] = 0;

                gameGrid[i + 1][j] = 1;

            }

            else

            {

                mushroom0Sprite.setPosition(xformushroom, yformushroom);

                window.draw(mushroom0Sprite);

            }

        }

    }
}

void detectCentipedeMushroomCollision(int position_centipede[][12], int mushroom_array[][30], int direction_centipede[12], int mushroom_lives[30])
{   
    for (int i = 0; i < 12; ++i)
    {
        int centipedeX = position_centipede[0][i] / 30;
        int centipedeY = position_centipede[1][i] / 30;

        for (int j = 0; j< 30; ++j)
        {
            int mushroomX = mushroom_array[0][j]/30;
            int mushroomY = mushroom_array[1][j]/30;
            if(mushroom_lives[j]>0)
            {if ( ((centipedeX == mushroomX)) && ( (centipedeY == mushroomY)))
                {
                    position_centipede[1][i] = position_centipede[1][i] +32;
                    direction_centipede[i]=direction_centipede[i] * (-1);
                }
            }
        }
    }
}

void detectBulletandMushroom(float bullet[],int mushroom_array[][30] ,int mushroom_lives[30])
{
    if(bullet[exists]==true)
    {
        int xforbullet = bullet[x] /30;
        int yforbullet = bullet[y] /30;
        //cout<<"mush  "<<mushroom_array[0][1]<<endl;
        for(int i=0; i<30; i++)
        {
            int xmushroom=mushroom_array[0][i] /30;
            int ymushroom=mushroom_array[1][i] /30;
            if(mushroom_lives[i]==2)
            {
                if ( ((xforbullet == xmushroom)) && ( (yforbullet == ymushroom)))
                {
                    mushroom_lives[i] = mushroom_lives[i] -1;
                    bullet[2]=false;
                }
            }
        }
    }
}

void BulletHitsCentipede(int position_centipede[][12], float bullet[], int centipede_death_array[12], int score[], sf::RenderWindow &window)
{
    int xforbullet = bullet[x] /30;
    int yforbullet = bullet[y] /30; 

    for(int i=0; i<12; i++)
    {
        int xcentipede =position_centipede[0][i] / 30;
        int ycentipede =position_centipede[1][i] / 30;
    
        if(xcentipede==xforbullet && ycentipede==yforbullet)
        {
            //cout<<"DEAD"<<endl;
            centipede_death_array[i]=0;
            bullet[2]=false;
            bullet[0]=213;
            bullet[1]=1524;
            score[0]=score[0] + 10;
        }
    }

    if(centipede_death_array[11]==0)
    {
        score[0]=score[0] + 20;
        window.close();
        
    }
}


void detectBulletandHalfMushroom(float bullet[],int half_mushroom_array[][30] ,int mushroom_lives[30], int score[]) 
{
    if(bullet[exists]==true)
    {
        int xforbullet = bullet[x] /30;
        int yforbullet = bullet[y] /30;
        //cout<<"mush  "<<mushroom_array[0][1]<<endl;
        for(int i=0; i<30; i++)
        {
            int xmushroom=half_mushroom_array[0][i] /30;
            int ymushroom=half_mushroom_array[1][i] /30;
            if(mushroom_lives[i]==1)
            {
                if ( ((xforbullet == xmushroom)) && ( (yforbullet == ymushroom)))
                {
                    mushroom_lives[i] = mushroom_lives[i] -1;
                    bullet[2]=false;
                    score[0]=score[0] + 1;
                }
            }
        }
    }
}

int CentipedeHitsPlayer(int position_centipede[][12], float player[2],sf::RenderWindow &window,sf::Sprite &gameoverSprite, int gameover)
{
    int xforplayer = player[0] / 30;
    int yforplayer= player[1] / 30; 

    for(int i=0; i<12; i++)
    {
        int xcentipede =position_centipede[0][i] / 30;
        int ycentipede =position_centipede[1][i] / 30;
    
        if(xcentipede==xforplayer && ycentipede==yforplayer)
        {
            gameover=1;
            gameoverSprite.setPosition(300,300);
            window.draw(gameoverSprite);
            window.close();
        }
    }
    return gameover;
}

void draw_gameover(sf::RenderWindow &window, sf::Sprite &gameoverSprite)
{
    gameoverSprite.setPosition(300, 300);
    gameoverSprite.setColor(sf::Color(255, 255, 255, 255 ));
    window.draw(gameoverSprite);
    
}

// void display_score(sf::RenderWindow &window, int score)
// {
//     sf::Font font;
//     //font.loadFromFile("myfont.ttf");
    

//     sf::Text text;
//     text.setFont(font); // Set the font
//     text.setCharacterSize(240); // Set the character size
//     text.setFillColor(sf::Color::White);

//     float score_positionx = 300.0;
//     float score_positiony = 300.0;
//     text.setPosition(score_positionx, score_positiony);
//     window.draw(text);
// }
void display_score(sf::RenderWindow &window, int score[])
{
    sf::Font font;
    
    // Load a font (replace "arial.ttf" with your font file)
    if (!font.loadFromFile("myfont.ttf"))
    {
        cout<<"FONT NOT FOUND";
        // If the font loading fails, handle the error
        return;
    }

    sf::Text text;
    text.setFont(font); // Set the font
    text.setCharacterSize(34); // Set the character size
    text.setFillColor(sf::Color::White);

    float score_positionx = 15.0;
    float score_positiony = 15.0;
    text.setPosition(score_positionx, score_positiony);

    // Convert integer to string
    std::string scoreStr = "Score: " + std::to_string(score[0]);
    text.setString(scoreStr);

    window.draw(text);
}