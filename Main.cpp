/*
                        Assalamo alaikum

                Developed by:
                    Anamul Hoque Emtiaj
                    BUET CSE 19
*/

# include "iGraphics.h"
# include "gl.h"

///declaring global variable & array
double x[16],y[16],x2[7],y2[7],x3[41],y3[41],v,xc,yc,r,add;
int lr[16],lr2[7],life,eat[2],c[2],index[2]= {1,9};
int i,j,balldirection,dead,score,sound=1,bmusic=1,nbox_mood,len,hscr,n;
int menu,menu_active,play,play_active,highscore,highscore_active,instruction,instruction_active;
int option,option_active,credit,credit_active,ext,ext_active,pause,gameover,hbox,resume,resume_active;
char scr[5],lf[1],name[30],hname[25],hscore[5];
FILE *file;

/*
    xc,yc~ball center point;
    r~ball radius
    x[],y[]~store rectangular blocks buttom left point
    x2[],y[]~store moveing spikes buttom left point
    x3[],y3[] store upper spike points
    lr[] & lr2[]~ help to update value of x co-ordinate after every repeat of rectangular block & moveing spike
    index[]~index of rectangular block where heart appear
    hname[],hscore[]~high scorar name & high score
    name[]~if the score is gather than highscore store his/her name
    scr[],lf[]~string of score & life
    eat[]~store if the heart already got eatten
    c[]~store heart repeat number to controll heart appear for creating dificulty
    n~controll number of heart at every repeat for creating dificulty
    v~valocity of ball,R. block,spike,side
    add~increament of valocity for dificulty
*/

///diplicate of arrays for reseting  pre-define value
///store pre-define value
double dx[16]= {280,220,80,20,60,200,170,150,290,130,30,45,180,120,50,150};
double dy[16]= {-840,-720,-660,-600,-480,-420,-300,-240,-180,-60,0,120,180,300,360,420};
int dlr[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

double dx2[7]= {120,50,160,170,115,150,200};
double dy2[7]= {-780,-540,-360,-120,60,240,480};
int dlr2[7]= {0,0,0,0,0,0,0};

int deat[2]= {0,0},dc[2]= {0,0};

///storeing path of background image
char bimg[12][20]= {"img\\0.bmp","img\\1.bmp","img\\2.bmp","img\\3.bmp","img\\4.bmp","img\\5.bmp",
                    "img\\6.bmp","img\\7.bmp","img\\8.bmp","img\\9.bmp","img\\10.bmp","img\\11.bmp"
                   };

///for reseting predefine value
void reset()
{
    ///rectangular block
    for(i=0; i<16; i++)
    {
        x[i]=dx[i];
        y[i]=dy[i];
        lr[i]=dlr[i];
    }
    ///spike
    for(i=0; i<7; i++)
    {
        x2[i]=dx2[i];
        y2[i]=dy2[i];
        lr2[i]=dlr2[i];
    }
    ///heart
    for(i=0; i<2; i++)
    {
        eat[i]=deat[i];
        c[i]=dc[i];
    }
    v=6,xc=70,yc=150,life=2,r=15;
    balldirection=1,dead=0,score=0;

    ///option
    menu=1,menu_active=0,play=0,play_active=0,highscore=0,highscore_active=0,instruction=0,instruction_active=0;
    option=0,option_active=0,credit=0,credit_active=0,ext=0,ext_active=0;
    pause=0,hbox=0,resume=0,resume_active=0,nbox_mood=0,len=0,scr[5]= {},lf[1]= {},n=2,add=0;

    memset(name,'\0',25);

    hscr=atoi(hscore);

    iResumeTimer(0);
}

void background_music()
{
    PlaySound("music\\1.wav", NULL, SND_LOOP || SND_ASYNC);
}

void moveing_sound()
{
    PlaySound("music\\2.wav", NULL, SND_ASYNC);
}

void dead_sound()
{
    PlaySound("music\\3.wav", NULL, SND_ASYNC);
}

void puthighscore()
{
    file=fopen("highscore.txt","w");
    fputs(name,file);
    fputs("\n",file);
    fputs(scr,file);
    fclose(file);
}

void gethighscore()
{
    file=fopen("highscore.txt","r");
    fgets(hname,25,file);
    fgets(hscore,5,file);
    fclose(file);
}

///structure for moveing spike
struct str
{
    double xi[11],yi[11];
};

struct str a[7];

///structure for heart
struct str2
{
    double xj[8],yj[8];
};

struct str2 b[2];

///structure for side
struct str3
{
    double y,x1,x2,x3,x4;
};

struct str3 cs[35];

///create play menu side
void side()
{
    for(i=0; i<35; i++)
    {
        cs[i].y=15*i;
        cs[i].x1=1;
        cs[i].x2=11;
        cs[i].x3=389;
        cs[i].x4=399;
    }
}

///create play menu upper spike
void upperblock()
{
    for(i=0; i<41; i++)
    {
        x3[i]=10*i;
        if((i+1)%2==0)
            y3[i]=480;
        else
            y3[i]=500;
    }
}

///create heart sign point
void createheart()
{

    for(i=0; i<2; i++)
    {
        b[i].xj[0]=x[index[i]]+50;
        b[i].yj[0]=y[index[i]]+20;
        b[i].xj[1]=x[index[i]]+40;
        b[i].yj[1]=y[index[i]]+26;
        b[i].xj[2]=x[index[i]]+40;
        b[i].yj[2]=y[index[i]]+32;
        b[i].xj[3]=x[index[i]]+45;
        b[i].yj[3]=y[index[i]]+38;
        b[i].xj[4]=x[index[i]]+50;
        b[i].yj[4]=y[index[i]]+32;
        b[i].xj[5]=x[index[i]]+55;
        b[i].yj[5]=y[index[i]]+38;
        b[i].xj[6]=x[index[i]]+60;
        b[i].yj[6]=y[index[i]]+32;
        b[i].xj[7]=x[index[i]]+60;
        b[i].yj[7]=y[index[i]]+26;
    }
}

///if the ball touch heart
void eatheart()
{
    for(i=0; i<n; i++)
    {
        if((xc>=(x[index[i]]+30))&&(xc<=(x[index[i]]+70))&&(yc>=(y[index[i]]+30))&&(yc<=(y[index[i]]+55)))
        {
            if(eat[i]==0)
            {
                life+=1;
                eat[i]=1;
                break;
            }
        }
        ///controll amount of heart appear for creating dificulty
        if(life<n)
        {
            eat[i]=0;
            c[i]=0;
        }
        else
        {
            if(y[index[i]]==0)
            {
                c[i]++;
                if(c[i]==8)
                {
                    eat[i]=0;
                    c[i]=0;
                }
            }
        }
    }
}

///controll ball activity
void ballcontroll()
{
    ///if the ball touch spike
    for(i=0; i<7; i++)
    {
        if(xc>x2[i]&&xc<(x2[i]+100))
        {
            if(yc>=(y2[i]+20+r-5)&&yc<=(y2[i]+20+r+5))
            {
                if(sound==1&&play==1)
                    dead_sound();
                life-=1;
                yc=y2[i]-30;
                xc=x2[i];
                ballcontroll();
                Sleep(250);
            }
        }
    }
    ///if the ball touch upper spike
    if(yc>=465)
    {
        if(sound==1&&play==1)
            dead_sound();
        life-=1;
        yc=300;
        xc=200;
        Sleep(250);
        ballcontroll();
    }
    ///if the ball touch rectangular block
    balldirection=1;
    for(i=0; i<16; i++)
    {
        if(xc>=x[i]&&xc<=(x[i]+100))
        {
            if(yc>=(y[i]+20+r-5)&&yc<=(y[i]+20+r+5))
            {
                balldirection=0;
                break;
            }
        }

    }
    if(balldirection==1)
    {
        yc-=(v+add);
        if(yc<0)
        {
            if(sound==1&&play==1)
                dead_sound();
            yc=300;
            xc=200;
            life-=1;
            Sleep(250);
            ballcontroll();
        }
        score+=1;
    }
    else
    {
        yc+=v+add;
    }
    if(dead==1||hbox==1)
    {
        iPauseTimer(0);
        gethighscore();
    }
}

///create point for moveing spike
void pointcreate()
{
    for(j=0; j<7; j++)
    {
        for(i=0; i<11; i++)
        {
            a[j].xi[i]=x2[j]+i*10;
            if((i+1)%2==0)
                a[j].yi[i]=y2[j]+20;
            else
                a[j].yi[i]=y2[j];
        }
    }
}

///change of play menu
void change()
{
     add=score/1000;
    ///rectangular block
    for(i=0; i<16; i++)
    {
        y[i]+=v+add;
        if(y[i]>=500) ///repeat
        {
            y[i]=-900;
            ///update x after every repeat
            if(x[i]>=250)
            {
                lr[i]=1;
                x[i]-=50;
            }
            else if(x[i]<=50)
            {
                lr[i]=0;
                x[i]+=50;
            }
            else if(lr[i]==0)
                x[i]+=50;
            else if(lr[i]==1)
                x[i]-=50;
        }
    }
    ///moveing spike
    for(i=0; i<7; i++)
    {
        y2[i]+=v+add;
        if(y2[i]>=500)
        {
            y2[i]=-900;
            if(x2[i]>=280)
            {
                lr2[i]=1;
                x2[i]-=20;
            }
            else if(x2[i]<=20)
            {
                lr2[i]=0;
                x2[i]+=20;
            }
            else if(lr2[i]==0)
                x2[i]+=20;
            else if(lr[i]==1)
                x2[i]-=20;
        }
    }
    pointcreate();
    if(score>1000)
        n=1;
    eatheart();

    if(life==-1)
        dead=1;
    createheart();
    ///ball
    ballcontroll();
    ///life
    itoa(life,lf,10);
    ///score
    itoa(score,scr,10);
    ///side changing at play menu
    for(i=0; i<35; i++)
    {
        cs[i].y+=v+add;
        if(cs[i].y>=500)
            cs[i].y=-10;
    }
}
/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    iClear();
    if(play==1)
    {
        iShowBMP(0,0,bimg[1]);
        iSetColor(0,0,255);
        ///draw rectangular block
        for(i=0; i<16; i++)
        {
            iFilledRectangle(x[i],y[i],100,20);
        }
        ///draw moveing spike
        iSetColor(0,0,0);
        for(i=0; i<7; i++)
        {
            iPolygon(a[i].xi,a[i].yi,11);
        }
        ///heart
        iSetColor(255,0,0);
        for(i=0; i<n; i++)
        {
            if(eat[i]==0)
            {
                iPolygon(b[i].xj,b[i].yj,8);
            }
        }
        ///ball
        iFilledCircle(xc,yc,r);
        ///Display score & life while playing
        iText(65,445,"X",GLUT_BITMAP_HELVETICA_18);
        iText(85,445,lf,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(140,445,"Score ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(205,445,scr,GLUT_BITMAP_HELVETICA_18);
        iSetColor(0,0,0);
        ///draw upper spike
        iPolygon(x3,y3,41);
        iSetColor(255,255,255);
        ///draw side
        iLine(1,0,1,500);
        iLine(11,0,11,500);
        iLine(399,0,399,500);
        iLine(389,0,389,500);
        for(i=0; i<35; i++)
        {
            iLine(cs[i].x1,cs[i].y,cs[i].x2,cs[i].y);
            iLine(cs[i].x3,cs[i].y,cs[i].x4,cs[i].y);
        }
        iShowBMP2(8,420,bimg[9],0);
        if(pause==0)
            iShowBMP2(320,415,bimg[11],0);
        ///if click pause button
        else
        {
            iShowBMP2(320,415,bimg[10],0);
            iShowBMP2(100,125,bimg[6],255);
            if(resume_active==1)
                iRectangle(110,235,175,60);
            else if(menu_active==1)
                iRectangle(110,175,175,60);
        }
        ///if no life remain
        if(dead==1)
        {
            iShowBMP(50,50,bimg[7]);
            iText(160,180,scr,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(212,122,hscore,GLUT_BITMAP_HELVETICA_18);
        }
        ///if you score highscore
        if(hbox==1)
        {
            iShowBMP(50,50,bimg[8]);
            iRectangle(65,160,240,60);
            ///take the highscorer name
            if(nbox_mood==1)
            {
                iText(85,180,name,GLUT_BITMAP_HELVETICA_18);
            }
        }
    }
    ///main menu
    else if(menu==1)
    {
        iShowBMP(0,0,bimg[0]);
        iSetColor(0,0,0);
        if(play_active==1)
            iRectangle(120,295,162,52);
        else if(highscore_active==1)
            iRectangle(120,241,162,52);
        else if(instruction_active==1)
            iRectangle(120,189,162,52);
        else if(option_active==1)
            iRectangle(120,133,162,52);
        else if(credit_active==1)
            iRectangle(120,76,162,52);
        else if(ext_active==1)
            iRectangle(120,17,162,52);
    }
    else if(highscore==1)
    {
        iShowBMP(0,0,bimg[2]);
        iText(155,155,hscore,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(205,89,hname,GLUT_BITMAP_HELVETICA_18);
    }
    else if(instruction==1)
    {
        iShowBMP(0,0,bimg[3]);
    }
    else if(option==1)
    {
        iShowBMP(0,0,bimg[4]);
        iRectangle(215,300,65,60);
        iRectangle(320,300,65,60);
        iRectangle(215,210,65,60);
        iRectangle(320,210,65,60);
    }
    else if(credit==1)
    {
        iShowBMP(0,0,bimg[5]);
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        ///at main menu
        if(menu==1)
        {
            if(mx>=120&&mx<=282&&my>=295&&my<=343)
            {
                if(play_active==0)
                {
                    play_active=1;
                    highscore_active=0;
                    instruction_active=0;
                    option_active=0;
                    credit_active=0;
                    ext_active=0;
                }
                else
                {
                    reset();
                    play=1;
                    menu=0;
                    play_active=0;
                }
            }
            else if(mx>=120&&mx<=282&&my>=241&&my<=293)
            {
                if(highscore_active==0)
                {
                    play_active=0;
                    highscore_active=1;
                    instruction_active=0;
                    option_active=0;
                    credit_active=0;
                    ext_active=0;
                }
                else
                {
                    gethighscore();
                    highscore=1;
                    highscore_active=0;
                    menu=0;
                }
            }
            else if(mx>=120&&mx<=282&&my>=189&&my<=241)
            {
                if(instruction_active==0)
                {
                    play_active=0;
                    highscore_active=0;
                    instruction_active=1;
                    option_active=0;
                    credit_active=0;
                    ext_active=0;
                }
                else
                {
                    instruction=1;
                    instruction_active=0;
                    menu=0;
                }
            }
            else if(mx>=120&&mx<=282&&my>=133&&my<=185)
            {
                if(option_active==0)
                {
                    play_active=0;
                    highscore_active=0;
                    instruction_active=0;
                    option_active=1;
                    credit_active=0;
                    ext_active=0;
                }
                else
                {
                    option=1;
                    option_active=0;
                    menu=0;
                }
            }
            else if(mx>=120&&mx<=282&&my>=76&&my<=128)
            {
                if(credit_active==0)
                {
                    play_active=0;
                    highscore_active=0;
                    instruction_active=0;
                    option_active=0;
                    credit_active=1;
                    ext_active=0;
                }
                else
                {
                    credit=1;
                    credit_active=0;
                    menu=0;
                }
            }
            else if(mx>=120&&mx<=282&&my>=17&&my<=69)
            {
                if(ext_active==0)
                {
                    play_active=0;
                    highscore_active=0;
                    instruction_active=0;
                    option_active=0;
                    credit_active=0;
                    ext_active=1;
                }
                else
                {
                    exit(0);
                }
            }
        }
        else if(highscore==1)
        {
            if(mx>=30&&mx<=115&&my>=15&&my<=50)
            {
                highscore=0;
                menu=1;
            }
        }
        else if(instruction==1)
        {
            if(mx>=15&&mx<=110&&my>=10&&my<=50)
            {
                instruction=0;
                menu=1;
            }
        }
        else if(credit==1)
        {
            if(mx>=30&&mx<=130&&my>=25&&my<=60)
            {
                credit=0;
                menu=1;
            }
        }
        else if(option==1)
        {
            if(mx>=215&&mx<=280&&my>=300&&my<=360)
            {
                background_music();
                bmusic=1;
            }
            if(mx>=320&&mx<=385&&my>=300&&my<=360)
            {
                moveing_sound();
                bmusic=0;
            }
            if(mx>=215&&mx<=280&&my>=210&&my<=270&&sound==0)
                sound=1;
            if(mx>=320&&mx<=385&&my>=210&&my<=270&&sound==1)
                sound=0;
            if(mx>=20&&mx<=115&&my>=32&&my<=72)
            {
                option=0;
                menu=1;
            }
        }
        ///at play menu
        else if(play==1)
        {
            if(mx>=320&&mx<=395&&my>=415&&my<=470)
            {
                pause=1;
                iPauseTimer(0);
            }
            ///if pause
            if(pause==1)
            {
                if(mx>=110&&mx<=285&&my>=235&&my<=295)
                {
                    if(resume_active==0)
                    {
                        resume_active=1;
                        menu_active=0;
                    }
                    else
                    {
                        iResumeTimer(0);
                        pause=0;
                    }
                }
                if(mx>=110&&mx<=285&&my>=175&&my<=235)
                {
                    if(menu_active==0)
                    {
                        menu_active=1;
                        resume_active=0;
                    }
                    else
                    {
                        reset();
                        if(bmusic==1)
                        {
                            background_music();
                        }
                    }
                }
            }
            ///when gameover box active
            if(dead==1)
            {
                if(mx>=50&&mx<=350&&my>=50&&my<=450)
                {
                    hscr=atoi(hscore);
                    if(score>hscr)
                    {
                        hbox=1;
                        dead=0;
                    }
                    else
                    {
                        reset();
                        if(bmusic==1)
                        {
                            background_music();
                        }
                    }
                }
            }
            ///if score is gather than highscore then the box active
            if(hbox==1)
            {
                if(mx>=65&&mx<=305&&my>=160&&my<=220&&nbox_mood==0)
                {
                    nbox_mood=1;
                }
                if(mx>=65&&mx<=185&&my>=85&&my<=125&&name[0]!='\0')
                {
                    puthighscore();
                    reset();
                    if(bmusic==1)
                    {
                        background_music();
                    }
                }
            }
        }
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    ///take hignscorar name
    if(nbox_mood==1)
    {
        name[len++]=key;
    }
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

///for ball's left & right move
void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_LEFT&&xc>=75)
    {
        xc-=50;
    }
    if(key == GLUT_KEY_RIGHT&&xc<=325)
    {
        xc+=50;
    }
    if(sound==1&&play==1)
    {
        moveing_sound();
    }
}


int main()
{
    background_music();
    gethighscore();
    pointcreate();
    upperblock();
    reset();
    side();
    iSetTimer(20,change);
    iInitialize(400, 500, "Rapid Roll");
    return 0;
}

