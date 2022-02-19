/* Lost In Space Game *By Ereena Bagga* */
/* LINK FOR VIDEO : https://youtu.be/UXdBWTMSozY */

#include "splashkit.h"
#include "lost_in_space.h"
#include <string>
using namespace std;

/**
 * Load the game images,fonts, sounds, etc.
 **/
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");

    load_bitmap("hud", "hud.png");
    load_bitmap("full bar", "green_bar_bubbles.png");
    load_bitmap("empty bar", "empty_bar_transparent.png");

    load_font("my_font1", "pdark.ttf");
    load_font("my_font2", "zorque.ttf");

    load_sound_effect("power_up_sound_effect", "power_up_pop.mp3");
    load_sound_effect("level_up", "level_up.mp3");
    load_sound_effect("game_over", "game_over1.mp3");
    load_music("video_game_ringtone", "video_game_ringtone.mp3");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 1200, 600);

    // procedure call to load resources
    load_resources();

    game_data game;
    // procedure call to set up new game initializing the player
    game = new_game();

    play_music("video_game_ringtone");
    set_music_volume(0.5);

    while (not quit_requested())
    {
        process_events();

        // Handle input to adjust player movement
        handle_input(game.player);

        // Procedure call for updating game with player and different power_ups
        update_game(game);

        // Procedure call for drawing game as well as the player and power_ups in game who can move
        draw_game(game);

        // Ends the game if the fuel or the time gets over
        if (game.player.fuel_pct <= 0 || game.player.time_pct <= 0)
        {
            stop_music();
            play_sound_effect("game_over", 1, 1);
            break;
        }
    }

    return 0;
}