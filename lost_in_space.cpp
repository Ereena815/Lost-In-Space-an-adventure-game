#include "splashkit.h"
#include "lost_in_space.h"
#define MIN_POWER_UP_LOCATION -1500
#define MAX_POWER_UP_LOCATION 1500

game_data new_game()
{
    game_data result;
    // function call to initialize new player in the game
    result.player = new_player();
    // creating timer of game
    result.game_timer = create_timer("game_timer");
    return result;
}

void add_power_up(game_data &game)
{
    power_up_data result;
    // procedure call to initialize a power_up at random position
    result = new_power_up(rnd(MIN_POWER_UP_LOCATION, MAX_POWER_UP_LOCATION), rnd(MIN_POWER_UP_LOCATION, MAX_POWER_UP_LOCATION));
    game.power_ups.push_back(result);
}

void remove_power_up(game_data &game, int index)
{
    game.power_ups[index] = game.power_ups[game.power_ups.size() - 1];
    game.power_ups.pop_back();
}

void apply_power_up(game_data &game, int index)
{
    pause_music();
    // If player hits the power up with kind FUEL, the fuel gets increased.
    if (game.power_ups[index].kind == FUEL && game.player.fuel_pct <= 0.8)
    {
        play_sound_effect("power_up_sound_effect", 1, 1);
        game.player.fuel_pct += 0.25 * game.player.fuel_pct;
    }
    // If player hits the power up with kind CASH or STAR, the score gets increased.
    else if (game.power_ups[index].kind == CASH || game.power_ups[index].kind == STAR)
    {
        play_sound_effect("power_up_sound_effect", 1, 1);
        game.player.score += 2;
    }
    // If player hits the power up with kind LEVEL, the level of game gets increased.
    else if (game.power_ups[index].kind == LEVEL)
    {
        play_sound_effect("level_up", 1, 1);
        game.player.level += 1;
    }
    // If player hits the power up with kind EARTH, the fuel bar becomes full again.
    else if (game.power_ups[index].kind == EARTH)
    {
        play_sound_effect("power_up_sound_effect", 1, 1);
        game.player.fuel_pct = 1;
    }
    // If player hits the power up with kind TIME, the time of game gets increased.
    else if (game.power_ups[index].kind == TIME && game.player.time_pct <= 0.8)
    {
        play_sound_effect("power_up_sound_effect", 1, 1);
        game.player.time_pct += 0.25 * game.player.time_pct;
    }
    else
    {
        play_sound_effect("power_up_sound_effect", 1, 1);
    }
    resume_music();
}

void check_collisions(game_data &game)
{
    for (int i = game.power_ups.size() - 1; i >= 0; i -= 1)
    { // If a player hits a power_up
        if (sprite_collision(game.power_ups[i].power_up_sprite, game.player.player_sprite))
        {
            // procedure call to apply effect of power_up
            apply_power_up(game, i);
            // procedure call to remove power_up
            remove_power_up(game, i);
        }
    }
}

void timer_checker(game_data &game)
{
    if (timer_started("game_timer"))
    {
        // Decreases time bar while game is going on
        game.player.time_pct -= 0.0002;
    }
}

point_2d mini_map_coordinate(const power_up_data &power_up)
{
    // Minimap coordinates for a power_up
    double mini_map_x = (sprite_x(power_up.power_up_sprite) + 1500) / 3000 * 100;
    double mini_map_y = (sprite_y(power_up.power_up_sprite) + 1500) / 3000 * 100;
    if (mini_map_x < 100 && mini_map_y < 100)
    {
        return point_at(mini_map_x, mini_map_y);
    }
}

void draw_mini_map(const game_data &game)
{
    // Draws pixel for minimap coordinate of powerup
    for (int i = 0; i < game.power_ups.size(); i++)
    {
        draw_pixel(rgba_color(rnd(255), rnd(255), rnd(255), rnd(255)), mini_map_coordinate(game.power_ups[i]), option_to_screen());
    }
    // Draws pixel for minimap coordinate of player
    double player_minimap_x = (sprite_x(game.player.player_sprite) + 600) / 3000 * 100;
    double player_minimap_y = (sprite_y(game.player.player_sprite) + 300) / 3000 * 100;
    draw_pixel(COLOR_LIGHT_BLUE, point_at(player_minimap_x, player_minimap_y), option_to_screen());
}

string sprite_location(const game_data &game)
{
    int x, y;
    point_2d sprite_center = center_point(game.player.player_sprite);
    x = sprite_center.x;
    y = sprite_center.y;
    return std::to_string(x) + "  " + std::to_string(y);
}

void draw_hud(const game_data &game)
{
    double part_width_fuel = game.player.fuel_pct * bitmap_width("full bar");
    double part_width_time = game.player.time_pct * bitmap_width("full bar");

    draw_bitmap("hud", 0, 455, option_to_screen());
    draw_bitmap("empty bar", 160, 480, option_to_screen());
    draw_bitmap("full bar", 160, 480, option_part_bmp(0, 0, part_width_fuel, bitmap_height("full bar"), option_to_screen()));
    draw_bitmap("empty bar", 130, 535, option_to_screen());
    draw_bitmap("full bar", 130, 535, option_part_bmp(0, 0, part_width_time, bitmap_height("full bar"), option_to_screen()));

    draw_rectangle(COLOR_DARK_SLATE_GRAY, 0, 0, 100, 100, option_to_screen());

    draw_text("SCORE  ", COLOR_WHITE, "my_font1", 15, 115, 35, option_to_screen());
    draw_text(":   " + std::to_string(game.player.score), COLOR_WHITE, "my_font2", 17, 220, 32, option_to_screen());
    draw_text("LOCATION  ", COLOR_WHITE, "my_font1", 15, 115, 5, option_to_screen());
    draw_text(":   " + sprite_location(game), COLOR_WHITE, "my_font2", 17, 220, 2, option_to_screen());
    draw_text("LEVEL  ", COLOR_WHITE, "my_font1", 15, 115, 65, option_to_screen());
    draw_text(":   " + std::to_string(game.player.level), COLOR_WHITE, "my_font2", 17, 220, 62, option_to_screen());
    draw_text("FUEL  ", COLOR_BRIGHT_GREEN, "my_font1", 25, 85, 490, option_to_screen());
    draw_text("TIME  ", COLOR_BRIGHT_GREEN, "my_font1", 25, 52, 545, option_to_screen());

    // Procedure call to draw a minimap
    draw_mini_map(game);
}

void draw_game(const game_data &game_to_draw)
{
    // Redraw everything
    clear_screen(COLOR_BLACK);
    // Start game timer
    start_timer("game_timer");
    // Keeps on playing the background music
    if (not music_playing())
    {
        play_music("video_game_ringtone");
        set_music_volume(0.5);
    }
    // Procedure call to draw player
    draw_player(game_to_draw.player);
    for (int i = 0; i < game_to_draw.power_ups.size(); i++)
    {
        // procedure call to draw power_up
        draw_power_up(game_to_draw.power_ups[i]);
    }
    // procedure call to draw heads_up_display
    draw_hud(game_to_draw);
    refresh_screen(60);
}

void update_game(game_data &game_to_update)
{
    // procedure call to decrease game timer
    timer_checker(game_to_update);
    if (rnd() < 0.04)
    {
        // procedure call to add power ups randomly
        add_power_up(game_to_update);
    }
    // procedure call to check player and power_up collisions
    check_collisions(game_to_update);
    // Perform movement and update the camera
    update_player(game_to_update.player);
    for (int i = 0; i < game_to_update.power_ups.size(); i++)
    {
        // procedure call to update power_up
        update_power_up(game_to_update.power_ups[i]);
    }
}