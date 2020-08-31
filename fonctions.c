#include "SDL/SDL.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonctions.h"

 SDL_Surface *screen=NULL; //reference the backbuffer
 Mix_Music *music;//Contruct Mix_Music pointer
 Mix_Music *musicgameover;
 SDL_Surface *mario=NULL; //reference our image
 SDL_Surface *luigi=NULL;
 SDL_Rect positionmario;
 SDL_Rect positionluigi;//rect to decribe the source destination region of out blit
 SDL_Rect positiontext;
 SDL_Rect positiontextgameover;
 SDL_Event event;
 TTF_Font *police = NULL;
 TTF_Font *policegameover=NULL;
 SDL_Surface *text;
 SDL_Surface *textgameover;
 int gameover=0;


int initialiser()
{

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)!=0)
    {
        printf("unable to initialize SDL: %s\n",SDL_GetError());
        return 1;
    }

    if(TTF_Init()== -1)
    {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return 1;
    }


    police = TTF_OpenFont("signature.ttf", 65);

    policegameover= TTF_OpenFont("gameover.ttf",50);

    SDL_Color couleurrouge = {250, 0, 0};

    text = TTF_RenderText_Blended(police,"Mario World",couleurrouge);

    textgameover = TTF_RenderText_Blended(policegameover,"Game Over",couleurrouge);

    //API Mixer Initialization
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
    {
        printf("%s",Mix_GetError());
    }


    music = Mix_LoadMUS("smbss_intro-cartoon.mp3");//load the music
    Mix_PlayMusic(music,-1);//play music forever("-1")

    musicgameover = Mix_LoadMUS("smb_gameover.wav");//load the music


    screen = SDL_SetVideoMode( 600, 400, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario World", NULL);

    if (screen==NULL)
    {
        printf("Unable to set video mode : %s\n",SDL_GetError());
        return 1;
    }

    //Load the bitmap into the image sureface,and check for success
    mario=SDL_LoadBMP("Mario.bmp"); //you can use IMG_load

    if (mario==NULL)
    {
        printf("Unable to load bitmap:%s\n",SDL_GetError());
        return 1;
    }

     luigi=SDL_LoadBMP("luigi.bmp"); //you can use IMG_load

    if (luigi==NULL)
    {
        printf("Unable to load bitmap:%s\n",SDL_GetError());
        return 1;
    }

    //Construct the source rectangle for our blit
    positionmario.x=0;
    positionmario.y=200;
    positionmario.w=mario->w;
    positionmario.h=mario->h;

    positionluigi.x=screen->w-luigi->w;
    positionluigi.y=200;
    positionluigi.w=luigi->w;
    positionluigi.h=luigi->h;

    positiontext.x=150;
    positiontext.y=0;

    positiontextgameover.x=150;
    positiontextgameover.y=150;

    SDL_EnableKeyRepeat(10, 10); /* Activation de la répétition des touches */
}

void afficher()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_BlitSurface(text, NULL, screen, &positiontext);

    //Blit the image to the backbuffer
    SDL_BlitSurface(mario, NULL, screen, &positionmario);

    SDL_BlitSurface(luigi, NULL, screen, &positionluigi);
    if(gameover==1)
    {
        SDL_BlitSurface(textgameover, NULL, screen, &positiontextgameover);
    }
    //flip the backbuffer to the primary Hardware Video Memory
    SDL_Flip(screen);

}

int deplacer()
{
    int done=0;
    while (SDL_PollEvent(&event))
    {   //check for messages
        switch(event.type)
        {
            case SDL_QUIT:
                done = 1;
                printf("Event SDLquit!\n");
                break;
                //check for keypresses
            case SDL_KEYDOWN:
                printf("Event SDL KeyDown!\n");
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done=1;
                        printf("Event SDLESCAPE!\n");
                        break;
                    case SDLK_UP:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionmario.y--;
                        printf("Event SDLK UP !\n");
                        break;
                    case SDLK_DOWN:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionmario.y++;
                        printf("Event SDLK DOWN!\n");
                        break;
                    case SDLK_RIGHT:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionmario.x++;
                        printf("Event SDLK RIGHT!\n");
                        break;
                    case SDLK_LEFT:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionmario.x--;
                        printf("Event SDLK LEFT!\n");
                        break;

                       //Deplacement luigi.
                    case SDLK_z:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionluigi.y--;
                        printf("Event SDLK UP !\n");
                        break;
                    case SDLK_s:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionluigi.y++;
                        printf("Event SDLK DOWN!\n");
                        break;
                    case SDLK_d:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionluigi.x++;
                        printf("Event SDLK RIGHT!\n");
                        break;
                    case SDLK_q:
                        if(gameover==1)
                        {
                            break;
                        }
                        positionluigi.x--;
                        printf("Event SDLK LEFT!\n");
                        break;
                }
                break;
            }

            if(collision(positionmario,positionluigi)==0)
            {
                printf("Il n y a pas de collision entre mario et luigi");

            }
            else
            {
                printf("I y a collision entre mario et luigi");

                gameover=1;

                Mix_HaltMusic();

                Mix_PlayMusic(musicgameover,0);
            }
    }
    return done;
}
/*
Implementation de la fonction collision .
*/
int collision(SDL_Rect p1, SDL_Rect p2)
{
    if(p2.y+p2.h<p1.y || p1.y+p1.h<p2.y||p1.x+p1.w<p2.x || p2.x+p2.w<p1.x)
    {
        return 0;//pas de collision.
    }
    else
    {
        return 1;//il y a collision.
    }

};

void freememory()
{   //Release the surface
    SDL_FreeSurface(mario);
    Mix_FreeMusic(music);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
}
