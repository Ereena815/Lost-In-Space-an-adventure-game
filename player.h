#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"
#include <vector>

using std::vector;

#define PLAYER_SPEED 1.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 100

/**
 * Different options for the kind of ship.
 * Adjusts the image used.
 */
enum ship_kind
{
    AQUARII,
    GLIESE,
    PEGASI
};

/**
 * The player data keeps track of all of the information related to the player.
 * 
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   score           The current score for the player
 * @field   kind            Current kind of player ship
 * @field   fuel_pct        Adjusts the percentage of fuel i.e. width of fuel bar
 * @field   time_pct        Adjusts the percentage of time i.e. width of time bar
 * @field   level           Player's level reached 
 */
struct player_data
{
    sprite player_sprite;
    int score;
    ship_kind kind;
    double fuel_pct;
    double time_pct;
    int level;
};

/**
 * Creates a new player in the centre of the screen with the default ship.
 * 
 * @returns     The new player data
 */
player_data new_player();

/**
 * Draws the player to the screen. 
 * 
 * @param player_to_draw    The player to draw to the screen
 */
void draw_player(const player_data &player_to_draw);

/**
 * Decreases fuel of player if the player moves. 
 * 
 * @param player
 */
void update_fuel_pct(player_data &player);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * 
 * @param player_to_update      The player being updated
 */
void update_player(player_data &player_to_update);

/**
 * Read user input and update the player based on this interaction.
 * 
 * @param player    The player to update
 */
void handle_input(player_data &player);

#endif