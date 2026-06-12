#pragma once
#include <SFML/Graphics.hpp>
#include <map>

enum BodyPart{
    feet,
    legs,
    head,
    torso,
    hands
};

struct Money{
    int value;
    int amount;
    std::string name;
    sf::Sprite sprite;
};

struct Weapon{
    int id;
    int damage;
    int durability;
    int trade_value;
    bool one_hander;
    int required_strength;

    std::string name;
    sf::Sprite sprite;
};
struct Armour{
    int id;
    int protection;
    int durability;
    int trade_value;
    BodyPart body_part;
    int required_strenght;

    std::string name;
    sf::Sprite sprite;
};
struct QuestItem{
    int id;
    int quest_id;

    std::string name;
    sf::Sprite sprite;
};
struct Consumable{
    int id;
    int health;
    int stamina;
    int agility;
    int trade_value;

    std::string name;
    sf::Sprite sprite;
};

struct Inventory{
    int available_space;
    Money gold;
    std::map<int,Weapon> weapons;
    std::map<int,Armour> armour;
    std::map<int,QuestItem> quest_items;
    std::map<int,Consumable> potions;
    std::map<int,Consumable> food;
};

void collect_item_money(Inventory& inv,int amount);
void collect_item_food(Inventory& inv,Consumable food);
void collect_item_weapon(Inventory& inv,Weapon& weapon);
void collect_item_armour(Inventory& inv,Armour& armour);
void collect_item_potion(Inventory& inv,Consumable potion);
void collect_item_quest_item(Inventory& inv,QuestItem q_item);

void drop_item_food(Inventory& inv,int food_id);
void drop_item_money(Inventory& inv,int amount);
void drop_item_potion(Inventory& inv,int potion_id);
void drop_item_weapon(Inventory& inv,int weapon_id);
void drop_item_armour(Inventory& inv,int armour_id);
void drop_item_quest_item(Inventory& inv,int q_item_id);

sf::Text inventory_display_get(sf::Font font,Inventory inventory);
sf::Text inventory_display_update(sf::Font font,Inventory inventory);
