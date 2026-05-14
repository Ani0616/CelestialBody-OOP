#include <iostream>
#include <string>

using namespace std;

//базов клас
class CelestialBody {
protected:
    string name;
    double mass;

public:
    CelestialBody() : name("Unknown"), mass(0.0) {}
    CelestialBody(string n, double m = 1.0) : name(n), mass(m) {}

    virtual ~CelestialBody() {}
    virtual void printInfo() const {
        cout << "Body: " << name << ", Mass: " << mass;
    }

    // абстрактен
    virtual void performAction() const = 0;

    // собствени методи
    void rename(string newName) { name = newName; }
    void displayStatus() const {
        if (mass > 1000) { cout << name << " is classified as a massive celestial object." << endl;}
        else { cout << name << " is classified as a medium-sized celestial object." << endl;}
    }
};

class Star : public CelestialBody {
protected:
    double temperature;
    string spectralType;

public:
    Star() : CelestialBody(), temperature(5000), spectralType("G") {}
    Star(string n, double m, double t, string s = "Main Sequence") : CelestialBody(n, m), temperature(t), spectralType(s) {}

    void printInfo() const override {
        CelestialBody::printInfo();
        cout << " | Temp: " << temperature << "K | Type: " << spectralType << endl;
    }

    void performAction() const override { fusion(); }

    // Собствени методи
    void fusion() const { cout << name << " is performing nuclear fusion." << endl; }
    void checkStability() const { cout << name << " is gravitationally stable." << endl; }
};

class Planet : public CelestialBody {
protected:
    int moons;
    bool hasAtmosphere;

public:
    Planet() : CelestialBody(), moons(0), hasAtmosphere(false) {}
    Planet(string n, double m, int mn, bool atm = true)
        : CelestialBody(n, m), moons(mn), hasAtmosphere(atm) {
    }

    void printInfo() const override {
        CelestialBody::printInfo();
        cout << " | Moons: " << moons << " | Atmosphere: " << (hasAtmosphere ? "Yes" : "No") << endl;
    }

    void performAction() const override { orbit(); }

    // Собствени методи
    void orbit() const { cout << name << " is orbiting its parent star." << endl; }
    void rotate() const { cout << name << " is rotating on its axis." << endl; }
};

// RedGiant - наследява Star
class RedGiant : public Star {
protected:
    double luminosity;

public:
    RedGiant() : Star(), luminosity(100.0) {}
    RedGiant(string n, double m, double t, double lum = 500.0) : Star(n, m, t, "Red Giant"), luminosity(lum) {}

    void printInfo() const override {
        Star::printInfo();
        cout << " Luminosity: " << luminosity << " Suns" << endl;
    }

    // собствени методи
    void expand() const { cout << name << " is expanding rapidly!" << endl; }
    void pulse() const { cout << name << " is pulsating light." << endl; }
};

// GasGiant - наследява Planet
class GasGiant : public Planet {
    string dominantGas;

public:
    GasGiant() : Planet(), dominantGas("Hydrogen") {}
    GasGiant(string n, double m, int mn, string gas = "Helium") : Planet(n, m, mn, true), dominantGas(gas) {}

    void printInfo() const override {
        Planet::printInfo();
        cout << " Dominant Gas: " << dominantGas << endl;
    }

    // собствени методи
    void triggerStorm() const { cout << " Great Storm active on " << name << "!" << endl; }
    void identifyRings() const { cout << " Rings detected around " << name << "." << endl; }
};


// Допълнителен клас, наследяващ от Planet
class TerrestrialPlanet : public Planet {
    string crustComposition;

public:
    TerrestrialPlanet() : Planet(), crustComposition("Silicate") {}
    TerrestrialPlanet(string n, double m, int mn, string crust = "Rocky") : Planet(n, m, mn, true), crustComposition(crust) {}

    void printInfo() const override {
        Planet::printInfo();
        cout << " Crust: " << crustComposition << endl;
    }

    // собствени методи
    void tectonicActivity() const { cout << " Tectonic plates shifting." << endl; }
    void volcanicEruption() const { cout << " Volcanic activity detected!" << endl; }
};

// Допълнителен клас, наследяващ от RedGiant
class Supernova : public RedGiant {
    double energyOutput;

public:
    Supernova() : RedGiant(), energyOutput(1e44) {}
    Supernova(string n, double m, double t, double energy = 5e44) : RedGiant(n, m, t, 10000.0), energyOutput(energy) {}

    void printInfo() const override {
        RedGiant::printInfo();
        cout << "  !!! STATUS: SUPERNOVA | Energy: " << energyOutput << " Joules" << endl;
    }

    // собствени методи
    void explode() const { cout << name << " HAS GONE SUPERNOVA!" << endl; }
    void createNeutronStar() const { cout << " A neutron star is forming at the core." << endl; }
};

int main() {
    //  Масив от обекти чрез указатели
    const int numBodies = 6;
    CelestialBody* universe[numBodies];

    universe[0] = new Star("Sun", 1.0, 5778);
    universe[1] = new Planet("Mars", 0.107, 2);
    universe[2] = new RedGiant("Betelgeuse", 11.6, 3500, 126000);
    universe[3] = new GasGiant("Jupiter", 317.8, 79, "Hydrogen/Helium");
    universe[4] = new TerrestrialPlanet("Earth", 1.0, 1, "Liquid Water/Basalt");
    universe[5] = new Supernova("SN 1987A", 20.0, 25000, 1e46);

    cout << "      GALAXY SYSTEM" << endl;

    for (int i = 0; i < numBodies; i++) {
        // изуализация на характеристиките
        universe[i]->printInfo();

        // Извикване на собствен метод 
        universe[i]->displayStatus();
        universe[i]->performAction();

        cout << "--------------------------------------------------" << endl;
    }

    // Освобождаване на динамичната памет
    for (int i = 0; i < numBodies; i++) {
        delete universe[i];
    }

    return 0;
}
