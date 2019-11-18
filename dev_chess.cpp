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

void load_position()
{
    int k = 0;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            int n = board[i][j];
            if(!n) continue;

            int x = abs(n)-1;
            int y = n > 0 ? 1:0;
            fig[k].setTextureRect(IntRect(sze*x, sze*y, sze, sze));
            printf("%d %d %d %d\n", sze*x, sze*y, sze, sze);
            fig[k].setPosition(sze*j, sze*i);
            printf("set position = %d %d\n", sze*j, sze*i);
            k++;
        }
    }
}
main()
{
    RenderWindow window(VideoMode(453,454), "My board", Style::Default);
    Texture pieces, board,trial;
    //trial.loadFromFile("images/figures4.png");
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
                    if(s.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        isMove = true;
                        dx = pos.x - s.getPosition().x;
                        dy = pos.y - s.getPosition().y;
                    }
                }
            }
            if(evnt.type == Event::MouseButtonReleased)
            {
                if(evnt.key.code == Mouse::Left)
                {
                    isMove = false;
                }
            }

        }
        if(isMove)
        {
            s.setPosition(pos.x-dx, pos.y-dy);
        }
        window.clear();
        window.draw(sp_brd);
        for(int i=0; i<32; i++) window.draw(fig[i]);
        window.display();
    }

}
