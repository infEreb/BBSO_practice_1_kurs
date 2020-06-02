#ifndef PRACT_H_
#define PRACT_H_

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


//Armor classes ======================
class Armor { 
	unsigned int def{};
	string name;
	protected:
		void setName(string ch);

	public:
		Armor();
		explicit Armor(unsigned int d);
		virtual ~Armor();

		unsigned int getDefence();
		void setDefence(unsigned int d);

		string getName();
};
class NoneArmor : public Armor {
	
	public:
		NoneArmor();
		~NoneArmor() override;

};
class IronArmor : public Armor {
	public:
		IronArmor();
		explicit IronArmor(unsigned int d);
		~IronArmor() override;

};


//Ammo classes ===============================
class Ammo {
	string name;

	string skill_name;
	unsigned int damage{};
	
	protected:
		void setName(string ch);

	public:
		Ammo();
		explicit Ammo(string sn, unsigned int d);
		virtual ~Ammo();

		string getSkillName();
		void setSkillName(string sn);
		unsigned int getDamageValue();
		void setDamageValue(unsigned int d);

		string getName();
};
class NoneAmmo : public Ammo {
	
	public:
		NoneAmmo();
		~NoneAmmo() override;
};
class Stone : public Ammo {

	public:
		Stone();
		Stone(string sn, unsigned int d);
		~Stone() override;
};
class Bullet : public Ammo {

	public:
		Bullet();
		Bullet(string sn, unsigned int d);
		~Bullet() override;
};

// Units primary class =========================
class Unit {
	string name;

	unsigned int health;
	Armor *armor;
    unsigned int damage;
    
	protected:
		void setName(string n);
        void setDamageValue(unsigned int d);

	public:
		explicit Unit(unsigned int h, unsigned int d);
		Unit(unsigned int h, Armor *at, unsigned int d);
		virtual ~Unit();

		unsigned int getHealth();
		void setHealth(unsigned int h);
        unsigned int getDamageValue();
		Armor *getArmor();
		void setArmor(Armor *at);

		virtual unsigned int attack() = 0;
        virtual string getInfo() = 0;

		string getName();
};
// Animal classes ============================
class Animal : public Unit {

	unsigned int speed;
	
	public:
		Animal(unsigned int h, unsigned int s, unsigned int d);
		~Animal() override;
        
        //unsigned int getDamageValue();
        //void setDamageValue(unsigned int d);
		unsigned int getSpeed();
		void setSpeed(unsigned int s);
        
        unsigned int attack() final;
        string getInfo() final;
};
class Elephant : public Animal {

	public:
		Elephant(unsigned int h, unsigned int s, unsigned int d);
		~Elephant() final;

};

// Mechanism classes ============================
class Mechanism : public Unit {

	Ammo *ammo;
	unsigned int ammo_count;

	public:
		Mechanism(unsigned int h, Ammo *at, unsigned int c);
		~Mechanism() override;

		
		Ammo *getAmmo();
		void setAmmo(Ammo *at);

        //unsigned int getDamageValue();
        //void setDamageValue(unsigned int d);
        
		unsigned int getAmmoCount();
		void setAmmoCount(unsigned int c);

		unsigned int attack() final;
        string getInfo() final;

};
class Cannon : public Mechanism {
	public:
		Cannon(unsigned int h, Ammo *at, unsigned int c);
		~Cannon() final;
};
class Catapult : public Mechanism {
	public:
		Catapult(unsigned int h, Ammo *at, unsigned int c);
		~Catapult() final;
};

//Soldiers =================================
class Soldier : public Unit {
	

	public:
		Soldier(unsigned int h, unsigned int d, Armor *a);
		~Soldier() override;
        
        //unsigned int getDamageValue();
        //void setDamageValue(unsigned int d);
        
		unsigned int attack() final;
        string getInfo() final;
};
class Barbarian : public Soldier{
	
	public:
	Barbarian(unsigned int h, unsigned int d, Armor *a);
	~Barbarian() final;
};

//Riders ===============================
class Rider : public Unit {
	
	Soldier *solder;
	Animal *animal;

	public:
		Rider(Soldier *s, Animal *a);
		~Rider() final;

		Soldier *getSoldier();
		void setSoldier(Soldier *s);
		Animal *getAnimal();
		void setAnimal(Animal *a);
        
        //unsigned int getDamageValue();
        //void setDamageValue(unsigned int d);
		
		unsigned int attack() final;
        string getInfo() final;
};

//Army class
class Army {
    
    string filename;
    ifstream army_if;
    ofstream army_of;
    vector<Unit *> army;
    
    unsigned int count_army{};
    unsigned int health_army{};
    unsigned int defence_army{};
    unsigned int damage_army{};
    
    void setArmyCount(unsigned int c);
    void setArmyHealth(unsigned int h);
    void setArmyDefence(unsigned int d);
    void setArmyDamage(unsigned int d);
    
    static Unit *unitConstruct(vector<string> unit_info);
    
    public:
        Army();
        Army(const string& armyFileName, char mode);
        ~Army();
        
        unsigned int getArmyCount();
        unsigned int getArmyHealth();
        unsigned int getArmyDefence();
        unsigned int getArmyDamage();
        
        unsigned int addUnit(Unit *u);
        int writeUnit(Unit *u);
        
        void takeDamage(unsigned int d);
        
        Unit *operator [](size_t idx);
};





#endif
