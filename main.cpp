//Including libraries for my code.
#include <iostream>
#include <cmath>
//DEclaring constants for calculating Gauss Law and Amperes Law.
const double EPSILON_0 = 8.854e-12;
const double MU_0 = 4 * M_PI * 1e-7;
//Declaring classes both public and private for use in my code.
class Field {
protected:
    double* value;

public:
    Field() {
        value = new double[3]{0.0, 0.0, 0.0};
    }

    Field(double x, double y, double z) {
        value = new double[3]{x, y, z};
    }

    Field(const Field& other) {
        value = new double[3]{other.value[0], other.value[1], other.value[2]};
    }

    virtual ~Field() {
        delete[] value;
    }

    void printMagnitude() const {
        std::cout << "Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")\n";
    }
};
//More class declaration.
class Electric_Field : public Field {
private:
    double E;

public:
    Electric_Field() : Field(), E(0) {}
    Electric_Field(double x, double y, double z) : Field(x, y, z), E(0) {}
    Electric_Field(const Electric_Field& other) : Field(other), E(other.E) {}
//Calculating Gauss law for the electric field.
    void calculateElectricField(double Q, double r) {
        if (r != 0) E = Q / (4 * M_PI * EPSILON_0 * r * r);
        else E = 0;
    }

    Electric_Field operator+(const Electric_Field& other) const {
        return Electric_Field(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }
//Not sure if I overloaded operators correctly but I used friend.
    friend std::ostream& operator<<(std::ostream& out, const Electric_Field& e) {
        out << "Electric Field: (" << e.value[0] << ", " << e.value[1] << ", " << e.value[2] << ")";
        return out;
    }
};
//Same thing as the electric field but for magnetic field and Amperes Law.
class Magnetic_Field : public Field {
private:
    double B;

public:
    Magnetic_Field() : Field(), B(0) {}
    Magnetic_Field(double x, double y, double z) : Field(x, y, z), B(0) {}
    Magnetic_Field(const Magnetic_Field& other) : Field(other), B(other.B) {}

    void calculateMagneticField(double I, double r) {
        if (r != 0) B = (MU_0 * I) / (2 * M_PI * r);
        else B = 0;
    }

    Magnetic_Field operator+(const Magnetic_Field& other) const {
        return Magnetic_Field(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }

    friend std::ostream& operator<<(std::ostream& out, const Magnetic_Field& m) {
        out << "Magnetic Field: (" << m.value[0] << ", " << m.value[1] << ", " << m.value[2] << ")";
        return out;
    }
};


int main() {
//Making output pretty and neat in main function before terminating.
    Electric_Field E1(0, 1e5, 1e3);
    Magnetic_Field B1(0, 2e-5, 5e-6);

    std::cout << "Initial Fields:\n";
    E1.printMagnitude();
    B1.printMagnitude();

    E1.calculateElectricField(1e-6, 0.05);
    B1.calculateMagneticField(10, 0.05);

    Electric_Field E2(1e4, 2e5, 3e3);
    Magnetic_Field B2(3e-5, 1e-5, 2e-6);

    Electric_Field E3 = E1 + E2;
    Magnetic_Field B3 = B1 + B2;

    std::cout << "\nAfter Addition:\n";
    std::cout << E3 << "\n";
    std::cout << B3 << "\n";

    return 0;
}

