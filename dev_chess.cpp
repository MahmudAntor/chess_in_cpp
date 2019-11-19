#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace sf;
using namespace std;

Sprite fig[33];
int sze = 56;
int board[8][8] =
{
    -1,-2,-3,-4,-5,-3,-2,-1,
    -6,-6,-6,-6,-6,-6,-6,-6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 6, 6,
    1, 2, 3, 4, 5, 3, 2, 1
};

string to_chess_note(Vector2f p)
{
    string s = "";
    s += char(p.x/sze +97);
    s += char(7-p.y/sze + 49);
    return s;
}

Vector2f to_coordinate(char a, char b)
{
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x*sze, y*sze);
}

void move_new(string str)
{
    Vector2f old_pos = to_coordinate(str[0], str[1]);
    Vector2f new_pos = to_coordinate(str[2], str[3]);

    for(int i=0; i<32; i++)
    {
        if(fig[i].getPosition() == new_pos)
        {
            fig[i].setPosition(-100, -100);
        }
    }
    for(int i=0; i<32; i++)
    {
        if(fig[i].getPosition() == old_pos)
        {
            fig[i].setPosition(new_pos);
        }
    }
}

void load_position()
{
    int k = 0;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            int n = board[i][j];
            if(!n)
                continue;

            int x = abs(n)-1;
            int y = n > 0 ? 1:0;
            fig[k].setTextureRect(IntRect(sze*x, sze*y, sze, sze));
            //printf("%d %d %d %d\n", sze*x, sze*y, sze, sze);
            fig[k].setPosition(sze*j, sze*i);
            //printf("set position = %d %d\n", sze*j, sze*i);
            k++;
        }
    }
}
main()
{
    RenderWindow window(VideoMode(453,454), "My board", Style::Default);
    Texture pieces, board,trial;
    // trial.loadFromFile("images/figures4.png");
    board.loadFromFile("images/board0.png");
    pieces.loadFromFile("images/figures.png");
    for(int i=0; i<32; i++)
    {
        fig[i].setTexture(pieces);
    }

    Sprite s,sp_brd;
    sp_brd.setTexture(board);
    //s.setTexture(pieces);
    //s.setTextureRect(IntRect(0,0, 62, 61));
    //s.setColor(Color(255,255,200));

    load_position();

    bool isMove = false;
    float dx=0, dy=0;
    int n=0;
    Vector2f old_pos, new_pos;
    string str;

    while(window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Event evnt;
        while(window.pollEvent(evnt))
        {
            if(evnt.type == Event::Closed)
            {
                window.close();
            }

            if(evnt.type == Event::MouseButtonPressed)
            {
                if(evnt.key.code == Mouse::Left)
                {
                    for(int i=0; i<32; i++)
                    {
                        if(fig[i].getGlobalBounds().contains(pos.x, pos.y))
                        {
                            isMove = true;
                            n=i;
                            dx = pos.x - fig[i].getPosition().x;
                            dy = pos.y - fig[i].getPosition().y;
                            old_pos = fig[i].getPosition();
                        }
                    }
                }
            }
            if(evnt.type == Event::MouseButtonReleased)
            {
                if(evnt.key.code == Mouse::Left)
                {
                    isMove = false;
                    Vector2f p = fig[n].getPosition() + Vector2f(sze/2,sze/2);
                    new_pos = Vector2f( sze*int(p.x/sze), sze*int(p.y/sze));
                    str = to_chess_note(old_pos) + to_chess_note(new_pos);
                    move_new(str);
                    cout<<str<<endl;
                    fig[n].setPosition(new_pos);
                    //printf("%f %f %f %f\n", p.x, p.y, NewPos.x,NewPos.y);
                }
            }

        }

        if(isMove)
        {
            fig[n].setPosition(pos.x-dx, pos.y-dy);
        }
        window.clear();
        window.draw(sp_brd);
        for(int i=0; i<32; i++)
            window.draw(fig[i]);
        window.display();
    }

}
