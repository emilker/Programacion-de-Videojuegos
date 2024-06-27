void player_IA(struct Pong* pong)
{
    if (pong->state == PLAY)
    {   
        if(  (pong->ball.x > TABLE_WIDTH / 2 ) && (pong->ball.vx > 0) )
        {
            if ( ( pong->player2.y < pong->ball.y )  &&  ( pong->ball.y < pong->player2.y + PADDLE_HEIGHT ) )
            {
                pong->player2.vy = 0;  
            }
            else if (pong->player2.y  + PADDLE_HEIGHT < pong->ball.y)
            {
                pong->player2.vy = PADDLE_SPEED;
            }
            else if (pong->player2.y   > pong->ball.y + BALL_SIZE) 
            {
                pong->player2.vy = -PADDLE_SPEED;   
            }
        }
        else 
        {
            pong->player2.vy = 0;
        }
            
    }
}
