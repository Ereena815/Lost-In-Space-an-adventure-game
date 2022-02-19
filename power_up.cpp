#include "splashkit.h"
#include "power_up.h"

/**
 * The power_up_bitmap function converts a power_up kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of power_up you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap power_up_bitmap(power_up_kind kind)
{
    switch (kind)
    {
    case FUEL:
        return bitmap_named("fuel");
    case CASH:
        return bitmap_named("cash");
    case STAR:
        return bitmap_named("star");
    case TIME:
        return bitmap_named("time");
    case LEVEL:
        return bitmap_named("level");
    case EARTH:
        return bitmap_named("earth");
    case MARS:
        return bitmap_named("mars");
    case JUPITER:
        return bitmap_named("jupiter");
    default:
        return bitmap_named("saturn");
    }
}

power_up_data new_power_up(double x, double y)
{
    power_up_data result;
    // Casts a random integer from 0 to 5 to enum power_up_kind
    result.kind = static_cast<power_up_kind>(rnd(9));

    // Creates a sprite by giving the power_up kind into power_up_bitmap function
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));

    // Sets the location of sprite by the parameters given
    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);

    // Sets the random speed of the power_up
    sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.power_up_sprite, rnd() * 4 - 2);

    return result;
}

void draw_power_up(const power_up_data &power_up_to_draw)
{
    draw_sprite(power_up_to_draw.power_up_sprite);
}

void update_power_up(power_up_data &power_up_to_update)
{
    update_sprite(power_up_to_update.power_up_sprite);
}
