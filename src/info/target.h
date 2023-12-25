#ifndef TARGET_H
#define TARGET_H

/*!
 * \brief The Target class - класс цели
 */
class Target
{
public:
    Target();
    Target(double distance, double peleng);
    Target(const Target& other);
    Target& operator=(const Target& other);

    int getId() const;

    double getDistance() const;
    void setDistance(double value);

    double getPeleng() const;
    void setPeleng(double value);

private:
    int id;
    double distance;
    double peleng;

private:
    static int ID;  // автоинкремент для уникальности идентификатора цели
};

#endif  // TARGET_H
