#include <SFML/Graphics.hpp>
#include "Inventory.h"

void collect_item_money(Inventory& inv,int amount)
{
    if(inv.available_space > 0)
    {
        inv.gold.amount += amount;
        inv.available_space--;
    }
}

void collect_item_food(Inventory& inv,Consumable food)
{
    if(inv.available_space > 0)
    {
        inv.food[food.id] = food;
        inv.available_space--;
    }
}

void collect_item_weapon(Inventory& inv,Weapon& weapon)
{
    if(inv.available_space > 0)
    {
        inv.weapons[weapon.id] = weapon;
        inv.available_space--;
    }
}

void collect_item_armour(Inventory& inv,Armour& armour)
{
    if(inv.available_space > 0)
    {
        inv.armour[armour.id] = armour;
        inv.available_space--;
    }
}

void collect_item_potion(Inventory& inv,Consumable potion)
{
    if(inv.available_space > 0)
    {
        inv.potions[potion.id] = potion;
        inv.available_space--;
    }
}

void collect_item_quest_item(Inventory inv,QuestItem q_item)
{
    if(inv.available_space > 0)
    {
        inv.quest_items[q_item.id] = q_item;
        inv.available_space--;
    }
}

void drop_item_money(Inventory& inv,int amount)
{
    inv.gold.amount -= amount;
}

void drop_item_food(Inventory& inv,int food_id)
{
    inv.food.erase(food_id);
}

void drop_item_potion(Inventory& inv,int potion_id)
{
    inv.potions.erase(potion_id);
}

void drop_item_weapon(Inventory& inv,int weapon_id)
{
    inv.weapons.erase(weapon_id);
}

void drop_item_armour(Inventory& inv,int armour_id)
{
    inv.armour.erase(armour_id);
}

void drop_item_quest_item(Inventory& inv,int q_item_id)
{
    inv.quest_items.erase(q_item_id);
}


