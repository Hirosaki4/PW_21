#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Інтерфейси
class IManageable {
public:
    virtual void manage() = 0;
    virtual ~IManageable() = default;
};

class IMaintainable {
public:
    virtual void maintain() = 0;
    virtual ~IMaintainable() = default;
};

class IReportable {
public:
    virtual void report() const = 0;
    virtual ~IReportable() = default;
};

// Абстрактний клас атракціону
class Attraction : public IManageable, public IMaintainable, public IReportable {
protected:
    std::string name;
    std::string type;
    int visitors;
    double revenue;

public:
    Attraction(std::string name, std::string type, int visitors, double revenue)
        : name(std::move(name)), type(std::move(type)), visitors(visitors), revenue(revenue) {}

    virtual void operate() = 0;

    virtual ~Attraction() = default;

    friend std::ostream& operator<<(std::ostream& os, const Attraction& attraction) {
        os << "Attraction: " << attraction.name << ", Type: " << attraction.type
            << ", Visitors: " << attraction.visitors << ", Revenue: $" << attraction.revenue;
        return os;
    }

    bool operator==(const Attraction& other) const {
        return (visitors == other.visitors) && (revenue == other.revenue);
    }
};

// Клас-нащадок для екологічного парку
class RecyclingRide : public Attraction {
    int recycledMaterials;

public:
    RecyclingRide(std::string name, int visitors, double revenue, int recycledMaterials)
        : Attraction(std::move(name), "Recycling Ride", visitors, revenue), recycledMaterials(recycledMaterials) {}

    void operate() override {
        std::cout << name << " is operating and promoting recycling awareness!\n";
    }

    void manage() override {
        std::cout << "Managing " << name << ". Adjusting recycling bins and schedules.\n";
    }

    void maintain() override {
        std::cout << "Performing maintenance on " << name << ". Ensuring recycling machines are operational.\n";
    }

    void report() const override {
        std::cout << name << " has recycled " << recycledMaterials << " items.\n";
    }
};

int main() {
    std::vector<std::shared_ptr<Attraction>> attractions;

    attractions.push_back(std::make_shared<RecyclingRide>("EcoWheel", 1200, 3000.50, 500));

    for (const auto& attraction : attractions) {
        attraction->operate();
        attraction->manage();
        attraction->maintain();
        attraction->report();
        std::cout << *attraction << "\n\n";
    }

    return 0;
}
