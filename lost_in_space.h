#ifndef LOST_IN_SPACE_GAME_DATA
#define LOST_IN_SPACE_GAME_DATA

#include "splashkit.h"
#include "power_up.h"
#include "player.h"
#include <vector>

using std::vector;

/**
 * The game data keeps track of all of the information related to the game i.e the player and power_ups.
 * 
 * @field   player       struct player keeps track of all the informatin related to player
 * @field   power_ups    vector power_ups keeeps track of the power_ups added in the game
 * @field   game_timer   keeps track of time left in the game
 */
struct game_data
{
    player_data player;
    vector<power_up_data> power_ups;
    timer game_timer;
};

/**
 * Creates a new game with initialization of player and game_timer.
 * 
 * @returns     The new game data
 */
game_data new_game();

/**
 * Creates a random power_up and adds it into the game.
 * 
 * @param     game
 */
void add_power_up(game_data &game);

/**
 * Removes the power_up at the indicated index from the game's power ups vector
 * 
 * @param     game
 * @param     index
 */
void remove_power_up(game_data &game, int index);

/**
 * Applies the effects of different power_ups to the player
 * 
 * @param     game
 * @param     index
 */
void apply_power_up(game_data &game, int index);

/**
 * Checks if the player has hit a power_up. If it happens, the power_up is removed and has an effect on player.
 * 
 * @param     game
 */
void check_collisions(game_data &game);

/**
 * Reduces the time while the game is going on.
 * 
 * @param     game
 */
void timer_checker(game_data &game);

/**
 * Returns the minimap coordinate for a given power_up.
 * 
 * @param     power_up
 * @returns   minimap_coordinate
 */
point_2d mini_map_coordinate(const power_up_data &power_up);

/**
 * Draws a scaled down map by looping through each power_up and drawing its pixel on minimap.
 * 
 * @param     game
 */
void draw_mini_map(const game_data &game);

/**
 * Converts the sprite location in double into integers and returns the string with location
 * @param game
 * @returns  string with player location
 **/
string sprite_location(const game_data &game);

/**
 * Procedure to dislays the heads_up_display
 * Draws different bitmaps and texts including the minimap
 * @param  game
 **/
void draw_hud(const game_data &game);

/**
 * Draws the game to the screen including hud, player and power_ups. 
 * 
 * @param game_to_draw    The game to draw to the screen
 */
void draw_game(const game_data &game_to_draw);

/**
 * Actions a step update of the game which includes periodically creating power_ups, checking collisions between 
 * player and power_ups, updating player and updating power_ups.
 * 
 * @param game_to_update      The game being updated
 */
void update_game(game_data &game_to_update);

#endif