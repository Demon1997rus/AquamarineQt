#ifndef TARGET_H
#define TARGET_H

class Target
{
public:
    Target();
    Target(int id, double distance, double peleng);

    int getId() const;

    double getDistance() const;
    void setDistance(double value);

    double getPeleng() const;
    void setPeleng(double value);

private:
    int id;
    double distance;
    double peleng;
};

#endif  // TARGET_H
