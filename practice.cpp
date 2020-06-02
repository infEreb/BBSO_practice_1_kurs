#include <iostream>
#include <cctype>
#include <algorithm>
#include "practice.h"
#include "D:\C++\practice\sown.h"

//================ARMY===================
Army::Army() {

    setArmyCount(0);
    setArmyHealth(0);
    setArmyDamage(0);
    
    filename = "basic_army.txt";
    ofstream b(filename);
    b.close();
    
    army_if = ifstream(filename);
    army_of = ofstream(filename);
}
Army::Army(const string& armyFileName, char mode) {
    
    if(mode == 'e')
    {
        filename = armyFileName;
        army_if.open(armyFileName);
        
        setArmyCount(0);
        
        vector<string> line;
        string str;
        int c;
        while((c = army_if.get()) != EOF)
        {
            if(c != '\n')
                str.push_back((char)c);
            else
            {
                line = split(str, ' ');
                str = "";
                
                addUnit(unitConstruct(line));
                
            }
                
        }
        
        if(!str.empty()) {
            line = split(str, ' ');
            addUnit(unitConstruct(line));
        }
            
        int sum_hel = 0;
        int sum_def = 0;
        int sum_dam = 0;
        for(int i = 0; i < count_army; i++)
        {
            sum_hel+=army[i]->getHealth();
            sum_def+=army[i]->getArmor()->getDefence();
            sum_dam += army[i]->getDamageValue();
        }
        setArmyHealth(sum_hel);
        setArmyDefence(sum_def);
        setArmyDamage(sum_dam);
        
        army_of = ofstream(armyFileName);
    }
    else if(mode == 'n')
    {
        setArmyCount(0);
        setArmyHealth(0);
        setArmyDefence(0);
        setArmyDamage(0);
        
        
        filename = armyFileName;
        army_if = ifstream(armyFileName);
        army_of = ofstream(armyFileName);
    }
    else
    {
        setArmyCount(0);
        setArmyDefence(0);
        setArmyHealth(0);
        setArmyDamage(0);
    
        filename = "basic_army.txt";
        army_of = ofstream(filename);
        army_if = ifstream(filename);
    }
    
}
Army::~Army() {
    
    army_if.close();
    army_of.close();
    
    for(auto & i : army)
    {
        delete i;
    }
    
}

void Army::setArmyCount(unsigned int c) {
    
    count_army = c;
}
unsigned int Army::getArmyCount() { return count_army; }
void Army::setArmyHealth(unsigned int h) {
    
    health_army = h;
}
unsigned int Army::getArmyHealth() { return health_army; }
void Army::setArmyDefence(unsigned int d) {

    defence_army = d;
}
unsigned int Army::getArmyDefence() { return defence_army; }
void Army::setArmyDamage(unsigned int d) {
    
    damage_army = d;
}
unsigned int Army::getArmyDamage() { return damage_army; }



unsigned int Army::addUnit(Unit *unit) {
    
    army.push_back(unit);
    /*
    setArmyHealth(getArmyHealth() + unit->getHealth());
    setArmyDefence(getArmyDefence() + unit->getArmor()->getDefence());
    setArmyDamage(getArmyDamage() + unit->getDamageValue());
    */
    health_army += unit->getHealth();
    defence_army += unit->getArmor()->getDefence();
    damage_army += unit->getDamageValue();
    
    
    return count_army++;
}

int Army::writeUnit(Unit *unit) {

    if(!army_of)
        return 1;
    string name = unit->getName();
    army_of << '*' << ' ' <<
    unit->getName() << ' ';
    
    if(name == "Cannon")
    {
        auto *unitMech = dynamic_cast<Mechanism *>(unit);
        if(unitMech)
        {
            army_of << unitMech->getHealth() << ' ' <<
            unitMech->getAmmo()->getName() << ' ' <<
            unitMech->getAmmo()->getSkillName() << ' ' <<
            unitMech->getDamageValue() << ' ' <<
            unitMech->getAmmoCount() << '\n';
        }
    }
    else if(name == "Catapult")
    {
        auto *unitMech = dynamic_cast<Mechanism *>(unit);
        if(unitMech)
        {
            army_of << unitMech->getHealth() << ' ' <<
            unitMech->getAmmo()->getName() << ' ' <<
            unitMech->getAmmo()->getSkillName() << ' ' <<
            unitMech->getDamageValue() << ' ' <<
            unitMech->getAmmoCount() << '\n';
        }
    }
    else if(name == "Barbarian")
    {
        army_of << unit->getHealth() << ' ' <<
        unit->getDamageValue() << ' ' <<
        unit->getArmor()->getName() << ' ' <<
        unit->getArmor()->getDefence() << '\n';
    }
    else if(name == "Rider")
    {
        Soldier *unitR = dynamic_cast<Rider *>(unit)->getSoldier();
        Animal *anim = dynamic_cast<Rider *>(unit)->getAnimal();
        
        army_of << unitR->getName() << ' ' <<
        unitR->getHealth() << ' ' <<
        unitR->getDamageValue() << ' ' <<
        unitR->getArmor()->getName() << ' ' <<
        unitR->getArmor()->getDefence() << ' ' <<
        anim->getName() << ' ' <<
        anim->getHealth() << ' ' <<
        anim->getSpeed() << ' ' <<
        anim->getDamageValue() << '\n';
    }
    return 0;
}

void Army::takeDamage(unsigned int damage) {

    damage = damage > getArmyDefence() ? damage - getArmyDefence() : 0;
    
    auto check = [&](Unit *u){
        if(damage >= u->getHealth())
        {
            count_army--;
            health_army -= u->getHealth();
            defence_army -= u->getArmor()->getDefence();
            damage_army -= u->getDamageValue();
            
            damage -= u->getHealth();
            return true;
        }
        else
        {
            if(u->getName() == "Rider")
            {
                auto *ur = dynamic_cast<Rider *>(u);
                if(ur->getAnimal()->getHealth() > damage)
                {
                    ur->setHealth(ur->getHealth() - damage);
                    ur->getAnimal()->setHealth(ur->getAnimal()->getHealth() - damage);
                    health_army -= damage;
                }
                else
                {
                    ur->setHealth(ur->getHealth() - damage);
                    health_army -= damage;
                    damage -= ur->getAnimal()->getHealth();
                    ur->getAnimal()->setHealth(0);
                    ur->getSoldier()->setHealth(ur->getSoldier()->getHealth() - damage);
                }
            }
            else
            {
                u->setHealth(u->getHealth() - damage);
                health_army -= damage;
                damage = 0;
            }
            
            return false;
        }
    };
    
    army.erase(std::remove_if(army.begin(), army.end(), check), army.end());
    /*
    army_of.close();
    army_of.open(filename, ios::trunc);
    for(int i = 0; i < army.size(); i++)
    {
        writeUnit(army[i]);
    }
    //army_f.close();
    //army_f.open(filename, ios::in | ios::out);
    */
}

Unit *Army::unitConstruct(vector<string> unit_info) {

    Unit *unit;
    unit = nullptr;
    
    string u_name = unit_info[1];
    
    if(u_name == "Cannon") //==================CANNON
    {
        auto health = (unsigned int)stoi(unit_info[2]);
        
        if(unit_info[3] == "NoneAmmo")
        {
            unit = new Cannon(health, new NoneAmmo(), (unsigned int)stoi(unit_info[6]));
        }
        else if(unit_info[3] == "Stone")
        {
            unit = new Cannon(health, new Stone(unit_info[4], (unsigned int)stoi(unit_info[5])), (unsigned int)stoi(unit_info[6]));
        }
        else if(unit_info[3] == "Bullet")
        {
            unit = new Cannon(health, new Bullet(unit_info[4], (unsigned int)stoi(unit_info[5])), (unsigned int)stoi(unit_info[6]));
        }
    }
    else if(u_name == "Catapult") // =======================CATAPULT
    {
        auto health = (unsigned int)stoi(unit_info[2]);
        
        if(unit_info[3] == "NoneAmmo")
        {
            unit = new Catapult(health, new NoneAmmo(), (unsigned int)stoi(unit_info[6]));
        }
        else if(unit_info[3] == "Stone")
        {
            unit = new Catapult(health, new Stone(unit_info[4], (unsigned int)stoi(unit_info[5])), (unsigned int)stoi(unit_info[6]));
        }
        else if(unit_info[3] == "Bullet")
        {
            unit = new Catapult(health, new Bullet(unit_info[4], (unsigned int)stoi(unit_info[5])), (unsigned int)stoi(unit_info[6]));
        }
    }
    else if(u_name == "Elephant") // =======================ELEPHANT
    {
        
        auto health = (unsigned int)stoi(unit_info[2]);
        
        unit = new Elephant(health, (unsigned int)stoi(unit_info[3]), (unsigned int)stoi(unit_info[4]));
    }
    else if(u_name == "Barbarian") // =======================BARBARIAN
    {
        auto health = (unsigned int)stoi(unit_info[2]);
        
        auto damage = (unsigned int)stoi(unit_info[3]);
        
        if(unit_info[4] == "NoneArmor")
        {
            unit = new Barbarian(health, damage, new NoneArmor());
        }
        else if(unit_info[4] == "IronArmor")
        {
            unit = new Barbarian(health, damage, new IronArmor((unsigned int)stoi(unit_info[5])));
        }
    }
    else if(u_name == "Rider") // ======================RIDER
    {
        
        if(unit_info[5] == "NoneArmor")
            unit = new Rider(new Barbarian((unsigned int)stoi(unit_info[3]), (unsigned int)stoi(unit_info[4]), new NoneArmor()), new Elephant((unsigned int)stoi(unit_info[8]), (unsigned int)stoi(unit_info[9]), (unsigned int)stoi(unit_info[10])));
        else if(unit_info[5] == "IronArmor")
            unit = new Rider(new Barbarian((unsigned int)stoi(unit_info[3]), (unsigned int)stoi(unit_info[4]), new IronArmor((unsigned int)stoi(unit_info[6]))), new Elephant((unsigned int)stoi(unit_info[8]), (unsigned int)stoi(unit_info[9]), (unsigned int)stoi(unit_info[10])));
        
    }
    return unit;
}

Unit *Army::operator [](size_t idx)
{
    return count_army > 0 && idx >= 0 && idx < count_army ? army[idx] : nullptr;
}

//======================ENDofARMY==========================


//=======ARMOR===========
//--Armor
Armor::Armor()
{
	setDefence(0);
}
Armor::Armor(unsigned int def)
{
	setDefence(def);
}
Armor::~Armor() = default;

unsigned int Armor::getDefence() { return def; }
void Armor::setDefence(unsigned int def) { this->def = def; }

string Armor::getName() { return name; }
void Armor::setName(string name) { this->name = name; }
//----

//--NoneArmor
NoneArmor::NoneArmor() : Armor() { setName("NoneArmor"); }
NoneArmor::~NoneArmor() = default;
//----

//--IronArmor
IronArmor::IronArmor() : Armor() { setName("IronArmor"); }
IronArmor::IronArmor(unsigned int def) : Armor(def) { setName("IronArmor"); }
IronArmor::~IronArmor() = default;
//----
//=============END OF ARMOR==============


//=========AMMO=============
//--Ammo
Ammo::Ammo()
{
	setSkillName("None");
	setDamageValue(0);
}
Ammo::Ammo(string skillName, unsigned int damageValue)
{
	setSkillName(skillName);
	setDamageValue(damageValue);
}
Ammo::~Ammo() = default;

string Ammo::getSkillName() { return skill_name; }
void Ammo::setSkillName(string skillName) { skill_name = skillName; }

unsigned int Ammo::getDamageValue() { return damage; }
void Ammo::setDamageValue(unsigned int damage) { this->damage = damage; }

string Ammo::getName() { return name; }
void Ammo::setName(string name) { this->name = name; }
//----

//--NoneAmmo
NoneAmmo::NoneAmmo() : Ammo() { setName("NoneAmmo"); }
NoneAmmo::~NoneAmmo() = default;
//----

//--Stone
Stone::Stone() : Ammo() { setName("Stone"); }
Stone::Stone(string skillName, unsigned int damageValue) : Ammo(skillName, damageValue) { setName("Stone"); }
Stone::~Stone() = default;
//----

//--Bullet
Bullet::Bullet() : Ammo() { setName("Bullet"); }
Bullet::Bullet(string skillName, unsigned int damageValue) : Ammo(skillName, damageValue) { setName("Bullet"); }
Bullet::~Bullet() = default;
//----
//=========END OF AMMO=======================


//===============UNIT===============
Unit::Unit(unsigned int health, unsigned int damage)
{
	setHealth(health);
	setArmor(new NoneArmor());
	setDamageValue(damage);
}
Unit::Unit(unsigned int health, Armor *armor, unsigned int damage)
{
	setHealth(health);
	setArmor(armor);
	setDamageValue(damage);
}
Unit::~Unit()
{
	delete armor;
}

unsigned int Unit::getHealth() { return health; }
void Unit::setHealth(unsigned int value) { health = value; }
Armor *Unit::getArmor() { return armor; }
void Unit::setArmor(Armor *armor) { this->armor = armor; }
unsigned int Unit::getDamageValue() { return damage; }
void Unit::setDamageValue(unsigned int damage) { this->damage = damage; }

string Unit::getName() { return name; }
void Unit::setName(string name) { this->name = name; }


//===============END OF UNIT====================


//=================ANIMALS=====================
//--Animal
Animal::Animal(unsigned health, unsigned int speed, unsigned int damage) : Unit(health, damage)
{
	setSpeed(speed);

}
Animal::~Animal()
{
	delete getArmor();
}

//unsigned int Animal::getDamageValue() { return damage; }
//void Animal::setDamageValue(unsigned int damage) { this->damage = damage; }

unsigned int Animal::getSpeed() { return speed; }
void Animal::setSpeed(unsigned int speed) { this->speed = speed; }

unsigned int Animal::attack() { return getDamageValue(); }
string Animal::getInfo() { return ""; }

//----

//--Elephant
Elephant::Elephant(unsigned health, unsigned int speed, unsigned int damage) : Animal(health, speed, damage)
{
	setName("Elephant");
}
Elephant::~Elephant()
{
	delete getArmor();
}

//----
//==============END OF ANIMALS=====================



//===============MECHANISM===================
Mechanism::Mechanism(unsigned int health, Ammo *ammo, unsigned int count) : Unit(health, ammo->getDamageValue())
{
	setAmmo(ammo);
	setAmmoCount(count);
}
Mechanism::~Mechanism()
{
	delete ammo;
}

//unsigned int Mechanism::getDamageValue() { return damage; }
//void Mechanism::setDamageValue(unsigned int damage) { this->damage = damage; }

Ammo *Mechanism::getAmmo() { return ammo; }
void Mechanism::setAmmo(Ammo *ammo) { this->ammo = ammo; }

unsigned int Mechanism::getAmmoCount() { return ammo_count; }
void Mechanism::setAmmoCount(unsigned int count) { ammo_count = count; }

unsigned int Mechanism::attack()
{
	if(ammo_count > 0)
	{
		ammo_count--;
		return ammo_count;
	}
	return getAmmo()->getDamageValue();
}

string Mechanism::getInfo()
{
    stringstream info_s;
    info_s << "Mechanism type: " << getName() << "\n" <<
    "Ammo type: " << getAmmo()->getName() << "\n" <<
	"\tSkill name: " << getAmmo()->getSkillName() << "\n" <<
	"\tDamage: " << getAmmo()->getDamageValue() << "\n" <<
	"Ammo count: " << getAmmoCount() << "\n" <<
	"Health: " << getHealth() << "\n" <<
	"Defence: " << getArmor()->getDefence();
    
    return info_s.str();
}
//----

//--Cannon
Cannon::Cannon(unsigned int health, Ammo *at, unsigned int ammoCount) : Mechanism(health, at, ammoCount) { setName("Cannon"); }
Cannon::~Cannon() = default;
//----

//--Catapult
Catapult::Catapult(unsigned int health, Ammo *at, unsigned int ammoCount) : Mechanism(health, at, ammoCount) { setName("Catapult"); }
Catapult::~Catapult() = default;
//----


//==================SOLDERS AND RIDERS==================================
//--Soldier
Soldier::Soldier(unsigned int health, unsigned int damage, Armor *armor) : Unit(health, armor, damage) {}
Soldier::~Soldier() = default;

//unsigned int Soldier::getDamageValue() { return damage; }
//void Soldier::setDamageValue(unsigned int damage) { this->damage = damage; }

unsigned int Soldier::attack() { return getDamageValue(); }

string Soldier::getInfo()
{   
    stringstream info_s;
	info_s << "Soldier: " << getName() << "\n" <<
	"Health: " << getHealth() << "\n" <<
	"Armor: " << getArmor()->getName() << "\n" <<
	"\tDefence: " << getArmor()->getDefence() << "\n" <<
	"Damage: " << getDamageValue();
    return info_s.str();

}

//----

//--Barbarian
Barbarian::Barbarian(unsigned int health, unsigned int damage, Armor *armor) : Soldier(health, damage, armor)
{ 
	setName("Barbarian");
}
Barbarian::~Barbarian() {}
//----

//--Rider
Rider::Rider(Soldier *solder, Animal *animal) : Unit(solder->getHealth() + animal->getHealth(), solder->getArmor(), solder->getDamageValue() + animal->getDamageValue())
{
setName("Rider");
    
	setSoldier(solder);
	setAnimal(animal);
}
Rider::~Rider() = default;

//unsigned int Rider::getDamageValue() { return damage; }
//void Rider::setDamageValue(unsigned int damage) { this->damage = damage; }

Soldier *Rider::getSoldier() { return solder; }
void Rider::setSoldier(Soldier *solder) { this->solder = solder; }

Animal *Rider::getAnimal() { return animal; }
void Rider::setAnimal(Animal *animal) { this->animal = animal; }

unsigned int Rider::attack() { return getSoldier()->getDamageValue() + getAnimal()->getDamageValue(); }

string Rider::getInfo()
{
	stringstream info_s;
	info_s << "Rider: " << getSoldier()->getName() << "\n" <<
	"Health: " << getHealth() << '\n' << 
	"Animal: " << getAnimal()->getName() << "\n" <<
	"Damage: " << attack() << "\n" <<
	"Defence: " << getSoldier()->getArmor()->getDefence();
    return info_s.str();
}

//----






