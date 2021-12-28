#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell
{
private:
    string scrollName;

public:
    Spell() : scrollName("") {}
    Spell(string name) : scrollName(name) {}
    virtual ~Spell() {}
    string revealScrollName()
    {
        return scrollName;
    }
};

class Fireball : public Spell
{
private:
    int power;

public:
    Fireball(int power) : power(power) {}
    void revealFirepower()
    {
        cout << "Fireball: " << power << endl;
    }
};

class Frostbite : public Spell
{
private:
    int power;

public:
    Frostbite(int power) : power(power) {}
    void revealFrostpower()
    {
        cout << "Frostbite: " << power << endl;
    }
};

class Thunderstorm : public Spell
{
private:
    int power;

public:
    Thunderstorm(int power) : power(power) {}
    void revealThunderpower()
    {
        cout << "Thunderstorm: " << power << endl;
    }
};

class Waterbolt : public Spell
{
private:
    int power;

public:
    Waterbolt(int power) : power(power) {}
    void revealWaterpower()
    {
        cout << "Waterbolt: " << power << endl;
    }
};

class SpellJournal
{
public:
    static string journal;
    static string read()
    {
        return journal;
    }
};
string SpellJournal::journal = "";

#define max( a, b) ((a > b) ? a : b)

void counterspell(Spell *spell)
{
    std::string name = spell->revealScrollName();
    std::string journal = SpellJournal::read();
    size_t name_len = name.length();
    size_t journal_len = journal.length();

    Fireball *fireball = dynamic_cast<Fireball *>(spell);
    Frostbite *frostbite = dynamic_cast<Frostbite *>(spell);
    Waterbolt *waterbolt = dynamic_cast<Waterbolt *>(spell);
    Thunderstorm *thunderstorm = dynamic_cast<Thunderstorm *>(spell);

    if (fireball)
        fireball->revealFirepower();
    else if (frostbite)
        frostbite->revealFrostpower();
    else if (waterbolt)
        waterbolt->revealWaterpower();
    else if (thunderstorm)
        thunderstorm->revealThunderpower();
    else
    {
        int lcs[journal_len + 1][name_len + 1];

        for (int i = 0; i <= journal_len; i++)
        {
            for (int j = 0; j <= name_len ; j++)
            {
                if (i == 0 || j == 0)
                    lcs[i][j] = 0;

                else if (journal.at(i - 1) == name.at(j - 1))
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;

                else
                    lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
        std::cout << lcs[journal_len][name_len] << std::endl;
    }
}

class Wizard
{
public:
    Spell *cast()
    {
        Spell *spell;
        string s;
        cin >> s;
        int power;
        cin >> power;
        if (s == "fire")
        {
            spell = new Fireball(power);
        }
        else if (s == "frost")
        {
            spell = new Frostbite(power);
        }
        else if (s == "water")
        {
            spell = new Waterbolt(power);
        }
        else if (s == "thunder")
        {
            spell = new Thunderstorm(power);
        }
        else
        {
            spell = new Spell(s);
            cin >> SpellJournal::journal;
        }
        return spell;
    }
};

int main()
{
    int T;
    cin >> T;
    Wizard Arawn;
    while (T--)
    {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}