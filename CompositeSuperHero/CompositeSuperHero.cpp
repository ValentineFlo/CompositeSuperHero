// CompositeSuperHero.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>


class IHeroComponents
{
public:
    virtual std::string name() const = 0;
    virtual int counter() const = 0;
    virtual ~IHeroComponents() {} 
};

class Hero : public IHeroComponents 
{
public:
    explicit Hero(const std::string& NAME) : m_name(NAME) {}
    std::string name() const override
    {
        return "nom : " + m_name;
    }

    int counter() const override
    {
        return 1;
    }

private :
    std::string m_name;

};

class TeamHero : public IHeroComponents
{
public:
    explicit TeamHero(const std::string& NAMETEAM) : m_nameteam(NAMETEAM){}
    ~TeamHero()
    {
        for (IHeroComponents* component : components)
        {
            delete component;
        }
    }

    void add(IHeroComponents* component)
    {
        components.push_back(component);
    }

    std::string name() const override
    {
        return "\n Team Name : " + m_nameteam;
    }

    int counter() const override
    {
        int count = 0;
        for (const IHeroComponents* component : components)
        {
            count += component->counter();
        }
        return count;
    }

    void display() const
    {
        std::cout <<"nom de l'equipe " << m_nameteam <<" (Nombre de membres: " << counter() << ")\n";
        for (const IHeroComponents* component : components)
        {
            std::cout << " - " << component->name() << std::endl;
        }
    }

private:
    std::string m_nameteam;
    std::vector<IHeroComponents*> components;
};


int main()
{
    Hero* ironMan = new Hero("Iron Man");
    Hero* captainAmerica = new Hero("Captain America");
    Hero* thor = new Hero("Thor");
    Hero* spiderMan = new Hero("Spider-Man");
    Hero* hulk = new Hero("Hulk");
    TeamHero* avengers = new TeamHero("Avengers");
    avengers->add(ironMan);
    avengers->add(captainAmerica);
    avengers->add(thor);
    avengers->display();
    TeamHero* defenders = new TeamHero("Les Defenseurs");
    defenders->add(spiderMan);
    defenders->add(hulk);
    defenders->display();

    TeamHero* globalAlliance = new TeamHero("Alliance des Heros");
    globalAlliance->add(avengers);
    globalAlliance->add(defenders);

    globalAlliance->display();

    delete globalAlliance;

    return 0;
}

