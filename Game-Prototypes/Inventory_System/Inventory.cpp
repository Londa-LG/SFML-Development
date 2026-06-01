#include <map>

enum ItemType { 
    armour, 
    consumable, 
    weapon, 
    quest, 
    money
};

class Item{
    public:
        int id;
        int value;
        ItemType type;
        sf::Sprite sprite;
};

class Armour: public Item{
    public:
        int protection;

        Armour(int p_id,ItemType p_type,sf::Sprite p_sprite,int p_protection){
            id = p_id;
            type = p_type;
            sprite = p_sprite;
            protection = p_protection;
        }
};

class Consumable: public Item{
    public:
        int health_inc;
        int stamina_inc;
        int agility_inc;
        int strength_inc;
        
        Consumable(int p_id,ItemType p_type,sf::Sprite p_sprite,int p_health_inc,int p_stamina_inc,int p_agility_inc,int p_strength_inc)
        {
            id = p_id;
            type = p_type;
            sprite = p_sprite;
            health_inc = p_health_inc;
            stamina_inc = p_stamina_inc;
            agility_inc = p_agility_inc;
            strength_inc = p_strength_inc;
        }
};

class Weapon: public Item{
    public:
        int required_strength;
        int damage;
        int durability;

        Weapon(int p_id,ItemType p_type,sf::Sprite p_sprite,int p_required_strength,int p_damage,int p_durability)
        {
            id = p_id;
            type = p_type;
            sprite = p_sprite;
            damage = p_damage;
            durability = p_durability;
            required_strength = p_required_strength;
        }
};

class QuestItem: public Item{
    public:
        int quest_id;

        QuestItem(int p_id,ItemType p_type,sf::Sprite p_sprite,int p_quest_id)
        {
            id = p_id;
            type = p_type;
            sprite = p_sprite;
            quest_id = p_quest_id;
        }
};

class Currency: public Item{
    public:
        int quantity;

        Currency(int p_id,ItemType p_type,sf::Sprite p_sprite,int p_quantity)
        {
            id = p_id;
            type = p_type;
            sprite = p_sprite;
            quantity = p_quantity;
        }
};

class Inventory
{
    public:
        int size;
        int item_count;
        std::map<int,Item> inventory;
        std::map<int,Item> equipment;
        
        Inventory(int p_size,int p_item_count,std::map<int,Item> p_inventory,std::map<int,Item> p_equipment)
        {
            size = p_size;
            inventory = p_inventory;
            equipment = p_equipment;
            item_count = p_item_count;
        }

        bool add_to_inventory(int location,Item item)
        {
           item_count++;
           if(item_count < size)
           {
               inventory[location] = item;
               return true;
           }
               
           return false;
        }
        bool equip_item(int location,Item item)
        {
           equipment[location] = item; 
           return true;
        }
};

