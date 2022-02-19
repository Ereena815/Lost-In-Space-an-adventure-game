#ifndef POWER_UP
#define POWER_UP

#include "splashkit.h"

/**
 * Different options for the kind of power up.
 * Adjusts the image used.
 */
enum power_up_kind
{
    FUEL,
    CASH,
    STAR,
    TIME,
    LEVEL,
    EARTH,
    MARS,
    JUPITER,
    SATURN
};

/**
 * The power up data keeps track of all of the information related to the power up used.
 * 
 * @field   power_up_sprite The power_up's sprite - used to track position and movement
 * @field   kind            Current kind of power_up
 */
struct power_up_data
{
    sprite power_up_sprite;
    power_up_kind kind;
};

/**
 * Creates a new random power_up on the screen with a speed i.e. change in dx and dy.
 * @param       x,y--> position of power_up
 * @returns     The new power_up
 */
power_up_data new_power_up(double x, double y);

/**
 * Draws the power_up to the screen. 
 * 
 * @param power_up_to_draw    The power_up to draw to the screen
 */
void draw_power_up(const power_up_data &power_up_to_draw);

/**
 * Actions a step update of the power_up.
 * 
 * @param player_to_update      The power_up being updated
 */
void update_power_up(power_up_data &power_up_to_update);

#endif